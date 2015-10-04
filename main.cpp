/*
 *  CSCI 441, Computer Graphics, Fall 2015
 *
 *  Project: Guild Wars
 *  File: main.cpp
 *
 *  Author: 
 *
 *  Description:
 */

#ifdef __APPLE__      // if compiling on Mac OS
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else         // else compiling on Linux OS
  #include <GL/glut.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

// GLUI for right click menu
#include <GL/glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
 
#include <fstream> // world read from file
#include <string>
#include <vector>

// Files we wrote
#include "ArcBallCamera.h"
#include "BezierPatch.h"
#include "Material.h"
#include "Color.h"
#include "Light.h"
#include "AllMight.h"
#include "./mouse.h"

using namespace std;
// GLOBAL VARIABLES //////////////////////////////////////////////////////////// 
static GLuint environmentDL;                       // display list for the grid
 
static GLint windowId;                             // id for our main window
static size_t windowWidth  = 640; 
static size_t windowHeight = 480; 
static float aspectRatio; 
// current time in ms, used to find fps
static double current_time = 0;
// Number of elapsed frames since last measure
static int numframes = 0;
// current fps
static double fps;

// global mouse object
Mouse mouse;
// Point light - default color is white
Light* pointLight;

// Zoom mode flag set on the ctrl key
static bool zoomMode = false;

// Camera instance
ArcBallCamera cam; 
// Surface instance
BezierPatch* bezierPatch; 

// All Might instance
AllMight allMight;

// generateEnvironmentDL() ///////////////////////////////////////////////////// 
// 
//  This function creates a display list with the code to draw a simple  
//      environment for the user to navigate through. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void generateEnvironmentDL() {
    environmentDL = glGenLists(1);
    glNewList(environmentDL, GL_COMPILE); {
      bezierPatch->drawFilled();
    } glEndList();
} 

// resizeWindow() ////////////////////////////////////////////////////////////// 
// 
//  GLUT callback for window resizing. Resets GL_PROJECTION matrix and viewport. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void resizeWindow(int w, int h) { 
  aspectRatio = w / (float)h; 

  windowWidth = w; 
  windowHeight = h; 

  //update the viewport to fill the window 
  glViewport(0, 0, w, h); 

  //update the projection matrix with the new window properties 
  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); 
  gluPerspective(45.0,aspectRatio,0.1,100000); 
}  
 
// mouseCallback() ///////////////////////////////////////////////////////////// 
// 
//  GLUT callback for mouse clicks. We save the state of the mouse button 
//      when this is called so that we can check the status of the mouse 
//      buttons inside the motion callback (whether they are up or down). 
// 
//////////////////////////////////////////////////////////////////////////////// 
void mouseCallback(int button, int state, int thisX, int thisY) { 
  // update the left mouse button states, if applicable 
  if( button == GLUT_LEFT_BUTTON ) {
    mouse.setX( thisX );
    mouse.setY( thisY );
    mouse.setLeftMouseButton( state );    
    if( state == GLUT_DOWN ) 
    {
      if( glutGetModifiers() == GLUT_ACTIVE_CTRL )
      {
        zoomMode = true;
      }
    }
    else zoomMode = false;
  }
} 
 
// mouseMotion() /////////////////////////////////////////////////////////////// 
// 
//  GLUT callback for mouse movement. We update cameraPhi, cameraTheta, and/or 
//      cameraRadius based on how much the user has moved the mouse in the 
//      X or Y directions (in screen space) and whether they have held down 
//      the left or right mouse buttons. If the user hasn't held down any 
//      buttons, the function just updates the last seen mouse X and Y coords. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void mouseMotion(int x, int y) { 
  if( mouse.getLeftMouseButton() == GLUT_DOWN ) { 
    int dx = ( x - mouse.getX() );
    int dy = ( mouse.getY() - y );  
    // Check for zoom
    if (zoomMode) {
      cam.incrementRadius(dy, 5);
    } else {
      cam.incrementTheta(0.005*dy);
      cam.incrementPhi(0.005*dx);
    }
    mouse.setX( x );
    mouse.setY( y );
    // update camera (x,y,z) based on (radius,theta,phi)
    cam.recomputeCamPosition(allMight.getX(), allMight.getY(), allMight.getZ());      
  }
} 
 
 
// initScene() ///////////////////////////////////////////////////////////////// 
// 
//  A basic scene initialization function; should be called once after the 
//      OpenGL context has been created. Doesn't need to be called further. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void initScene()  { 
  glEnable(GL_DEPTH_TEST); 

  glEnable( GL_LIGHTING ); 
  // Enable the light
  pointLight = new Light(GL_LIGHT0);
  pointLight->enable();
  // Set position of the point light
  pointLight->setPosition(0, 1000, 0);

  glShadeModel(GL_FLAT); 

  generateEnvironmentDL(); 
} 
 
// renderScene() /////////////////////////////////////////////////////////////// 
// 
//  GLUT callback for scene rendering. Sets up the modelview matrix, renders 
//      a scene to the back buffer, and switches the back buffer with the 
//      front buffer (what the user sees). 
// 
//////////////////////////////////////////////////////////////////////////////// 
void renderScene(void)  { 
  //clear the render buffer (sky blue)
  glClearColor(0.53, 0.808, 0.922, 1);
  glDrawBuffer( GL_BACK ); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //update the modelview matrix based on the camera's position 
  glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix! 
  glLoadIdentity();
  gluLookAt( cam.getX(), cam.getY(), cam.getZ(),      // camera pos
              cam.getLookX(), cam.getLookY(), cam.getLookZ(),     // camera lookat
              cam.getUpX(), cam.getUpY(),  cam.getUpZ());     // up vector
  // Reset point light placement
  pointLight->resetPosition();

  // Draws surface
  glCallList(environmentDL); 


  
  // DRAW ALLMIGHT
  Material mat = Material(Color(0.1745, 0.01175, 0.01175),
                          Color(0.61424, 0.04136, 0.04136),
                          Color(0.727811, 0.626959, 0.626929),
                          0.6*128);
  mat.set_as_current_material();
  glPushMatrix(); {
    // Move to location
    glTranslatef(allMight.getX(), allMight.getY(), allMight.getZ());
    // Orient with the surface, by applying rotation
    vector<float> orientation = bezierPatch->orient(allMight.getX(), allMight.getZ());
    glRotatef(orientation[1], orientation[2], orientation[3], orientation[4]);
    // rotation in the x,z plane
    glRotatef(allMight.getRot(), 0, 1, 0);
    allMight.drawVehicle();
  } glPopMatrix();
  // END DRAW ALLMIGHT

  //push the back buffer to the screen 
  glutSwapBuffers(); 
} 

// cleanup()////////////////////////////////////////////////////////////////////
//
// Deallocates all dynamic memory
//
///////////////////////////////////////////////////////////////////////////////
void cleanup() {
  delete pointLight;
  delete bezierPatch;
  glutDestroyWindow( windowId );  // destroy our window
}
 
 
// normalKeysDown() //////////////////////////////////////////////////////////// 
// 
//  GLUT keyboard callback
// 
//////////////////////////////////////////////////////////////////////////////// 
void normalKeysDown(unsigned char key, int x, int y) { 
  if(key == 'q' || key == 'Q' || key == 27) {
    // clean up
    cleanup();
    exit(0);
  }
  allMight.respondKeyDown(key);
} 

// normalKeysUp() /////////////////////////////
//
// Callback for key up
//
/////////////////////////////////////////////
void normalKeysUp(unsigned char key, int x, int y) {
  allMight.respondKeyUp(key);
}

// fpsUpdate() ///////////////////////////////
//
// Updates fps every second
//
//////////////////////////////////////////////
void fpsUpdate() {
  // increment frames
  numframes++;
  // get new time
  double newt = glutGet(GLUT_ELAPSED_TIME);
  double deltat = newt - current_time;
  // Only update every second
  if (deltat > 1000.0) {
    // update and reset frame counter
    fps = (double)numframes/(deltat /1000.0); 
    printf("fps: %.2f\n", fps); 
    current_time = newt;
    numframes = 0;
  } 
}

// update(int val) //////////////////////////////
//
// The timer func, runs at 60 fps, updates object positions.
//
//////////////////////////////////// 
void update(int val) {
  // Hero update
  allMight.update();
  allMight.setY(bezierPatch->orient(allMight.getX(), allMight.getZ())[0]);
  // Cam update
  cam.recomputeCamPosition(allMight.getX(), allMight.getY(),allMight.getZ());

  // FPS update
  fpsUpdate();

  glutPostRedisplay();
  glutTimerFunc(1000/60.0, update, 0);
}

 
// myMenu() ////////////////////
//
// callback for the glui menu
//
////////////////////////////////
void myMenu(int value) {
  // Quit
  if (value == 0) exit(0);
}

// createMenus() //////////////////////////
//
// creates glui menu, options, and attaches to the right mouse button
//
///////////////////////////////////////////
void createMenus() {
  // create with the passed callback glutCreateMenu(myMenu);
  glutCreateMenu(myMenu);
  // add options
  glutAddMenuEntry("Quit", 0);
  // Attach to right mouse
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// main() ////////////////////////////////////////////////////////////////////// 
// 
//  Program entry point
// 
//////////////////////////////////////////////////////////////////////////////// 
int main(int argc, char **argv) { 
  // Get file from passed argument
  if (argc != 2) {
    printf("Usage: %s worldfile.csv\n", argv[0]);
    exit(1);
  }
  // TESTING //////////////////
  // load up the surface points
  bezierPatch = new BezierPatch();
  if (!bezierPatch->loadControlPoints(argv[1])) {
    printf("Could not load file: %s\n", argv[1]);
    exit(1);
  }
  // Set the material as green plastic
  bezierPatch->setMaterial(Material(Color(0,0,0),
                                    Color(0.1, 0.35, 0.1),
                                    Color(0.45, 0.55, 0.45),
                                    0.25*128));
  // Initial orient (to set y)
  allMight.setY(bezierPatch->orient(allMight.getX(), allMight.getZ())[0]);
  // END TESTING //////////////////

  // create a double-buffered GLUT window at (50,50) with predefined windowsize 
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
  glutInitWindowPosition(50,50); 
  glutInitWindowSize(windowWidth,windowHeight); 
  windowId = glutCreateWindow("Guild Wars"); 

  // Init cam coords to look at all might
  cam.recomputeCamPosition(allMight.getX(), allMight.getY(), allMight.getZ());

  // register callback functions... 
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutKeyboardFunc(normalKeysDown); 
  glutKeyboardUpFunc(normalKeysUp);
  glutDisplayFunc(renderScene); 
  glutReshapeFunc(resizeWindow); 
  glutMouseFunc(mouseCallback); 
  glutMotionFunc(mouseMotion); 
  
  // Setup menu
  createMenus();

  // do some basic OpenGL setup 
  initScene(); 

  // schedule first update
  glutTimerFunc(1000/60.0, update, 0); 

  // and enter the GLUT loop, never to exit. 
  glutMainLoop(); 

  return(0); 
} 
