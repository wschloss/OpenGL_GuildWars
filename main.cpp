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

using namespace std;
// GLOBAL VARIABLES //////////////////////////////////////////////////////////// 
GLuint environmentDL;                       // display list for the grid
 
static size_t windowWidth  = 640; 
static size_t windowHeight = 480; 
static float aspectRatio; 
 
GLint leftMouseButton = GLUT_UP;                    // status of the mouse buttons 
int mouseX = 0, mouseY = 0;                         // last known X and Y of the mouse 

// Zoom mode flag set on the ctrl key
bool zoomMode = false;

// Camera instance
ArcBallCamera cam; 
// Surface instance
BezierPatch bezierPatch;

// generateEnvironmentDL() ///////////////////////////////////////////////////// 
// 
//  This function creates a display list with the code to draw a simple  
//      environment for the user to navigate through. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void generateEnvironmentDL() {
    environmentDL = glGenLists(1);
    glNewList(environmentDL, GL_COMPILE); {
      // TESTING ///////////
      bezierPatch.drawFilled();
      // END TESTING ///////
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
  if(button == GLUT_LEFT_BUTTON) {
    mouseX = thisX;
    mouseY = thisY;
    leftMouseButton = state;     
    if (state == GLUT_DOWN) {
      if (glutGetModifiers() == GLUT_ACTIVE_CTRL)
        zoomMode = true;
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
  if(leftMouseButton == GLUT_DOWN) { 
    int dx = x - mouseX;
    int dy = mouseY - y;  
    // Check for zoom
    if (zoomMode) {
      cam.incrementRadius(dy, 5);
    } else {
      cam.incrementTheta(-0.005*dy);
      cam.incrementPhi(0.005*dx);
    }
    mouseX = x;
    mouseY = y;

    cam.recomputeCamPosition(0, 0, 0);     // update camera (x,y,z) based on (radius,theta,phi)
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

  //****************************************************************** 
  // this is some code to enable a default light for the scene; 
  // feel free to play around with this, but we won't talk about 
  // lighting in OpenGL for another couple of weeks yet. 
  float lightCol[4] = { 1, 1, 1, 1}; 
  float ambientCol[4] = { 0.0, 0.0, 0.0, 1.0 }; 
  float lPosition[4] = { 10, 10, 10, 1 }; 
  glLightfv( GL_LIGHT0, GL_POSITION,lPosition ); 
  glLightfv( GL_LIGHT0, GL_DIFFUSE,lightCol ); 
  glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol ); 
  glEnable( GL_LIGHTING ); 
  glEnable( GL_LIGHT0 ); 
 
  // tell OpenGL not to use the material system; just use whatever we  
  // pass with glColor*() 
  glEnable( GL_COLOR_MATERIAL ); 
  glColorMaterial( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ); 
  //******************************************************************

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
  //clear the render buffer glDrawBuffer( GL_BACK ); 
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //update the modelview matrix based on the camera's position 
  glMatrixMode(GL_MODELVIEW);              //make sure we aren't changing the projection matrix! 
  glLoadIdentity();
  gluLookAt( cam.getX(), cam.getY(), cam.getZ(),      // camera pos
              cam.getLookX(), cam.getLookY(), cam.getLookZ(),     // camera lookat
              cam.getUpX(), cam.getUpY(),  cam.getUpZ());     // up vector

  glCallList(environmentDL); 


  //push the back buffer to the screen 
  glutSwapBuffers(); 
} 
 
 
// normalKeysDown() //////////////////////////////////////////////////////////// 
// 
//  GLUT keyboard callback
// 
//////////////////////////////////////////////////////////////////////////////// 
void normalKeysDown(unsigned char key, int x, int y) { 
  if(key == 'q' || key == 'Q' || key == 27) 
    exit(0); 
} 

// normalKeysUp() /////////////////////////////
//
// Callback for key up
//
/////////////////////////////////////////////
void normalKeysUp(unsigned char key, int x, int y) {

}

// update(int val) //////////////////////////////
//
// The timer func, runs at 60 fps, updates object positions.
//
//////////////////////////////////// 
void update(int val) {
  // Cam update
  cam.recomputeCamPosition(0,0,0);
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
  if (!bezierPatch.loadControlPoints(argv[1])) {
    printf("Could not load file: %s\n", argv[1]);
    exit(1);
  }
  // END TESTING //////////////////

  // create a double-buffered GLUT window at (50,50) with predefined windowsize 
  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA); 
  glutInitWindowPosition(50,50); 
  glutInitWindowSize(windowWidth,windowHeight); 
  glutCreateWindow("Guild Wars"); 

  // Init cam coords to look at origin
  cam.recomputeCamPosition(0,0,0);

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
