/*
 *  CSCI 441, Computer Graphics, Fall 2015
 *
 *  Project: Guild Wars
 *  File: main.cpp
 *
 *  Authors: Walter Carl Schlosser ( All Might )
 *           Tyler M. Bank ( CoolPantsBro )
 *           Zac McClain ( Castamere Castelli )
 *
 *  Description: 
 *
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
#include "mouse.h"
#include "castamere_castelli.h"
#include "CoolPants.h"
#include "WorldLoader.h"

using namespace std;

// GLOBAL VARIABLES //////////////////////////////////////////////////////////// 

// display list for the surface
static GLuint environmentDL; 
 
// id for the main window
static GLint windowId;  
// widow dimensions                           
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

// Camera instance
ArcBallCamera cam;

// Surface instance
BezierPatch* bezierPatch; 

// Curve instance for the track
BezierCurve* bezierCurve;

// All Might instance
AllMight allMight;

// Make a global CastamereCastelli character instance
CastamereCastelli castamere;

// CoolPants instance
CoolPants coolPants;


// generateEnvironmentDL() ///////////////////////////////////////////////////// 
// 
//  This function creates a display list with the code to draw a simple  
//      environment for the user to navigate through. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void generateEnvironmentDL() {
    environmentDL = glGenLists( 1 );
    glNewList( environmentDL, GL_COMPILE ); {
      bezierPatch->drawFilled();
      bezierCurve->draw();
    } glEndList();
} 

// resizeWindow() ////////////////////////////////////////////////////////////// 
// 
//  GLUT callback for window resizing. Resets GL_PROJECTION matrix and viewport. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void resizeWindow( int w, int h ) { 
  aspectRatio = ( w / (float)h ); 

  windowWidth = w; 
  windowHeight = h; 

  //update the viewport to fill the window 
  glViewport( 0, 0, w, h ); 

  //update the projection matrix with the new window properties 
  glMatrixMode( GL_PROJECTION ); 
  glLoadIdentity(); 
  gluPerspective( 45.0, aspectRatio, 0.1, 100000 ); 
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
        mouse.setZoomMode( true );
      }
    }
    else mouse.setZoomMode( false );
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
void mouseMotion( int x, int y ) { 
  if( mouse.getLeftMouseButton() == GLUT_DOWN ) { 
    int dx = ( x - mouse.getX() );
    int dy = ( mouse.getY() - y );  
    // Check for zoom
    if( mouse.getZoomMode() ) {
      cam.incrementRadius( dy, 5 );
    } else {
      cam.incrementTheta( 0.005 * dy );
      cam.incrementPhi( 0.005 * dx );
    }
    mouse.setX( x );
    mouse.setY( y );
    // update camera (x,y,z) based on (radius,theta,phi)
    cam.recomputeCamPosition(
      coolPants.getX(), 
      coolPants.getY(), 
      coolPants.getZ()
    );
    // cam.recomputeCamPosition( 
    //   castamere.getX(), 
    //   castamere.getY(), 
    //   castamere.getZ() 
    // );           
  }
} 
 
 
// initScene() ///////////////////////////////////////////////////////////////// 
// 
//  A basic scene initialization function; should be called once after the 
//      OpenGL context has been created. Doesn't need to be called further. 
// 
//////////////////////////////////////////////////////////////////////////////// 
void initScene()  { 
  glEnable( GL_DEPTH_TEST ); 

  glEnable( GL_LIGHTING ); 
  // Enable the light
  pointLight = new Light( GL_LIGHT0 );
  pointLight->enable();
  // Set position of the point light
  pointLight->setPosition(0, 1000, 0);

  glShadeModel( GL_FLAT ); 

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
  //make sure we aren't changing the projection matrix!
  glMatrixMode( GL_MODELVIEW );

  glLoadIdentity();
  
  gluLookAt( 
    cam.getX(), cam.getY(), cam.getZ(),             // camera pos
    cam.getLookX(), cam.getLookY(), cam.getLookZ(), // camera lookat
    cam.getUpX(), cam.getUpY(),  cam.getUpZ()       // up vector
  );    
  // Reset point light placement
  pointLight->resetPosition();

  // Draws surface
  glCallList( environmentDL ); 

  // DRAW CASTAMERE

  // glPushMatrix();
  // {
  //     castamere.renderSelf( bezierPatch );
  // };
  // glPopMatrix();

  // END DRAW CASTAMERE
  
  // DRAW ALLMIGHT
  Material mat = Material(Color(0.1745, 0.01175, 0.01175),
                          Color(0.61424, 0.04136, 0.04136),
                          Color(0.727811, 0.626959, 0.626929),
                          0.6*128);
  mat.set_as_current_material();
  glPushMatrix(); {
    allMight.draw( bezierPatch );
  } glPopMatrix();
  // END DRAW ALLMIGHT
  
  // DRAW COOLPANTS
  Material matCoolPants = Material(Color(0.329412, 0.223529, 0.027451),
                          Color(0.780392, 0.568627, 0.113725),
                          Color(0.05, 0.05, 0.05),
                          0.005*128);
  matCoolPants.set_as_current_material();
  glPushMatrix(); {
    coolPants.draw(bezierPatch);
  } glPopMatrix();
  
  // END DRAW COOLPANTS

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
  delete bezierCurve;
  // destroy our window
  glutDestroyWindow( windowId );
}
 
 
// normalKeysDown() //////////////////////////////////////////////////////////// 
// 
//  GLUT keyboard callback
// 
//////////////////////////////////////////////////////////////////////////////// 
void normalKeysDown( unsigned char key, int x, int y ) { 
  if( (key == 'q') || (key == 'Q') || (key == 27) ) {
    // clean up
    cleanup();
    exit( 0 );
  }
  castamere.respondKeyDown( key );
} 

// normalKeysUp() /////////////////////////////
//
// Callback for key up
//
/////////////////////////////////////////////
void normalKeysUp( unsigned char key, int x, int y ) {
  castamere.respondKeyUp( key );
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
  double newt = glutGet( GLUT_ELAPSED_TIME );
  double deltat = newt - current_time;
  // Only update every second
  if (deltat > 1000.0) {
    // update and reset frame counter
    fps = ( (double)numframes/(deltat /1000.0) ); 
    printf( "fps: %.2f\n", fps ); 
    current_time = newt;
    numframes = 0;
  } 
}

// update(int val) //////////////////////////////
//
// The timer func, runs at 60 fps, updates object positions.
//
//////////////////////////////////// 
void update( int val ) {
  // Hero update
  allMight.update();
  allMight.setY(
    bezierPatch->orient(allMight.getX(), allMight.getZ())[0]
  );

  castamere.update();
  castamere.setY(
    bezierPatch->orient(castamere.getX(), castamere.getZ())[0] 
      + (castamere.getHeight()/2)
  );
   
  coolPants.update();
  coolPants.setY(
    bezierPatch->orient(coolPants.getX(), coolPants.getZ() + coolPants.getH())[0]
  );
  
  // Cam update
  cam.recomputeCamPosition(
    coolPants.getX(), 
    coolPants.getY(),
    coolPants.getZ()
  );

  // cam.recomputeCamPosition(
  //   castamere.getX(), 
  //   castamere.getY(),
  //   castamere.getZ()
  // );

  // FPS update
  fpsUpdate();

  glutPostRedisplay();
  glutTimerFunc( 1000/60.0, update, 0 );
}

 
// myMenu() ////////////////////
//
// callback for the glui menu
//
////////////////////////////////
void myMenu( int value ) {
  // Quit
  if( value == 0 ) { 
    exit( 0 );
  }
}

// createMenus() //////////////////////////
//
// creates glui menu, options, and attaches to the right mouse button
//
///////////////////////////////////////////
void createMenus() {

  // create with the passed callback glutCreateMenu(myMenu);
  glutCreateMenu( myMenu );

  // add options
  glutAddMenuEntry( "Quit", 0 );

  // Attach to right mouse
  glutAttachMenu( GLUT_RIGHT_BUTTON );
}


// main() ////////////////////////////////////////////////////////////////////// 
// 
//  Program entry point
// 
//////////////////////////////////////////////////////////////////////////////// 
int main( int argc, char **argv ) { 
  // Get file from passed argument
  if( argc != 2 ) {
    printf( "Usage: %s worldfile.txt\n", argv[0] );
    exit( 1 );
  }

  // Read the world file into a loader
  WorldLoader loader( argv[1] );
  // Construct object from the data files
  bezierPatch = loader.constructSurface();
  bezierCurve = loader.constructCurve();

  // TESTING //////////////////
  // Set AllMight to follow by parameter t
  allMight.setFollowPath(bezierCurve);
  // Set CoolPants to follow by arclength s 
  coolPants.setFollowPath(bezierCurve);
  // Initial orient (to set y)
  castamere.setY( 
    bezierPatch->orient(castamere.getX(), castamere.getZ())[0] 
      + (castamere.getHeight()/2)
  );
  // END TESTING //////////////////

  // create a double-buffered GLUT window at (50,50) with predefined windowsize 
  glutInit( &argc, argv ); 
  glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA ); 
  glutInitWindowPosition( 50, 50 ); 
  glutInitWindowSize( windowWidth, windowHeight ); 
  windowId = glutCreateWindow( "Guild Wars" ); 

  // Init cam coords to look at all might
  cam.recomputeCamPosition(
    coolPants.getX(), 
    coolPants.getY(), 
    coolPants.getZ()
  );

  // cam.recomputeCamPosition(
  //   castamere.getX(), 
  //   castamere.getY(), 
  //   castamere.getZ()
  // );

  // register callback functions... 
  glutSetKeyRepeat( GLUT_KEY_REPEAT_OFF );
  glutKeyboardFunc( normalKeysDown ); 
  glutKeyboardUpFunc( normalKeysUp );
  glutDisplayFunc( renderScene ); 
  glutReshapeFunc( resizeWindow ); 
  glutMouseFunc( mouseCallback ); 
  glutMotionFunc( mouseMotion ); 
  
  // Setup menu
  createMenus();

  // do some basic OpenGL setup 
  initScene(); 

  // schedule first update
  glutTimerFunc( (1000/60.0), update, 0 ); 

  // and enter the GLUT loop, never to exit. 
  glutMainLoop(); 

  return( 0 ); 
} 
