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
#include "FreeCamera.h"
#include "BezierPatch.h"
#include "Material.h"
#include "Color.h"
#include "Light.h"
#include "AllMight.h"
#include "mouse.h"
#include "castamere_castelli.h"
#include "CoolPants.h"

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

<<<<<<< HEAD
// Camera instance
ArcBallCamera cam;
=======
// Campfire, draws and also flickers a light
Campfire campfire;

// Camera instances
ArcBallCamera arcballCam;
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647

// Free cam which can move with wasd
FreeCamera freeCam;

// Free cam used for the first person view for each hero
FreeCamera firstPerson;

// Surface instance
BezierPatch* bezierPatch; 

// All Might instance
AllMight allMight;

// Make a global CastamereCastelli character instance
CastamereCastelli castamere;

// CoolPants instance
CoolPants coolPants;

// Enum for the target a camera should be based on
enum CharacterTarget { ALL_MIGHT, CASTAMERE, COOL_PANTS };

// Enum for the current camera to render
enum CameraTarget { ARCBALL, FREE, FIRST_PERSON };

// The current target for the arcball camera, init to castamere
CharacterTarget arcballTarget = CASTAMERE;

// The current target for the first person camera, init to castamere
CharacterTarget fpTarget = CASTAMERE;

// Defaultly initialize main camera to Arcball
CameraTarget camTarget = ARCBALL;

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
<<<<<<< HEAD
      cam.incrementTheta( 0.005 * dy );
      cam.incrementPhi( 0.005 * dx );
    }
    mouse.setX( x );
    mouse.setY( y );
    // update camera (x,y,z) based on (radius,theta,phi)
    cam.recomputeCamPosition(
      allMight.getX(), 
      allMight.getY(), 
      allMight.getZ()
    );
    // cam.recomputeCamPosition( 
    //   castamere.getX(), 
    //   castamere.getY(), 
    //   castamere.getZ() 
    // );           
=======
      if( camTarget == ARCBALL ){
        arcballCam.incrementTheta( 0.005 * dy );
        arcballCam.incrementPhi( 0.005 * dx );
      }
      else if( camTarget == FREE ){
        freeCam.incrementTheta( 0.005 * dx );
        freeCam.incrementPhi( 0.005 * dy );
      }
    }
    mouse.setX( x );
    mouse.setY( y );

    // update the arcball cam based on the target
    float tx, ty, tz;
    switch ( arcballTarget ) {
      case ALL_MIGHT:
        tx = allMight.getX(); ty = allMight.getY(); tz = allMight.getZ();
        break;
      case CASTAMERE:
        tx = castamere.getX(); ty = castamere.getY(); tz = castamere.getZ();
        break;
      case COOL_PANTS:
        tx = coolPants.getX(); ty = coolPants.getY(); tz = coolPants.getZ();
        break;
      default:
        // Shouldn't get here
        tx = ty = tz = 0;
    }
	
    arcballCam.recomputeCamPosition( tx, ty, tz );
    freeCam.recomputeCamDir();
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647
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

  // Enable backface culling
  glEnable( GL_CULL_FACE );
  glFrontFace( GL_CCW );
  glCullFace( GL_BACK );

  //update the modelview matrix based on the camera's position 
  //make sure we aren't changing the projection matrix!
  glMatrixMode( GL_MODELVIEW );

  glLoadIdentity();
  
<<<<<<< HEAD
  gluLookAt( 
    cam.getX(), cam.getY(), cam.getZ(),             // camera pos
    cam.getLookX(), cam.getLookY(), cam.getLookZ(), // camera lookat
    cam.getUpX(), cam.getUpY(),  cam.getUpZ()       // up vector
  );    
  // Reset point light placement
=======
  if( camTarget == ARCBALL )
  {
	  gluLookAt(
	    arcballCam.getX(), arcballCam.getY(), arcballCam.getZ(),             // camera pos
	    arcballCam.getLookX(), arcballCam.getLookY(), arcballCam.getLookZ(), // camera lookat
	    arcballCam.getUpX(), arcballCam.getUpY(),  arcballCam.getUpZ()       // up vector
	  );
  }
  else if( camTarget == FREE )
  {
	  gluLookAt( 
	    freeCam.getX(), freeCam.getY(), freeCam.getZ(),             // camera pos
	    freeCam.getLookX(), freeCam.getLookY(), freeCam.getLookZ(), // camera lookat
	    freeCam.getUpX(), freeCam.getUpY(),  freeCam.getUpZ()       // up vector
	  ); 
  }   
  else if( camTarget == FIRST_PERSON )
  {
	  gluLookAt( 
      firstPerson.getX() + (firstPerson.getLookX() - firstPerson.getX())/4, 
      firstPerson.getY() + (firstPerson.getLookY() - firstPerson.getY())/4, 
      firstPerson.getZ() + (firstPerson.getLookZ() - firstPerson.getZ())/4,             // camera pos
	    firstPerson.getLookX(), firstPerson.getLookY(), firstPerson.getLookZ(), // camera lookat
	    firstPerson.getUpX(), firstPerson.getUpY(),  firstPerson.getUpZ()       // up vector
	  ); 
  }  
  // Reset point light placement
  // NOTE: This light call looks like it doesn't even matter
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647
  pointLight->resetPosition();

  // Draws surface
  glCallList( environmentDL ); 
  
  
  // DEBUG: draw a line to show first person cam direction
  glDisable(GL_LIGHTING);
  
  glBegin(GL_LINES);
  glColor3f(0,1,0);
  glVertex3f(firstPerson.getX() + (firstPerson.getLookX() - firstPerson.getX())/4, 
		firstPerson.getY() + (firstPerson.getLookY() - firstPerson.getY())/4, 
		firstPerson.getZ() + (firstPerson.getLookZ() - firstPerson.getZ())/4);
  glVertex3f(firstPerson.getLookX(), firstPerson.getLookY(), firstPerson.getLookZ());
  glEnd();
  
  glEnable(GL_LIGHTING);
  // END DEBUG

<<<<<<< HEAD
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
    // Move to location
    glTranslatef(coolPants.getX(), coolPants.getY(), coolPants.getZ());
    // Orient with the surface, by applying rotation
    vector<float> orientation = bezierPatch->orient(coolPants.getX(), coolPants.getZ());
    glRotatef(orientation[1], orientation[2], orientation[3], orientation[4]);
    coolPants.drawHorse();
  } glPopMatrix();
  
  // END DRAW COOLPANTS
=======
  // DRAW THE THREE CHARACTERS
  castamere.renderSelf(); 
  allMight.draw(); 
  coolPants.draw();  
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647

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
void normalKeysDown( unsigned char key, int x, int y ) { 
  if( (key == 'q') || (key == 'Q') || (key == 27) ) {
    // clean up
    cleanup();
    exit( 0 );
  }
<<<<<<< HEAD
  castamere.respondKeyDown( key );
  allMight.respondKeyDown( key );
=======
  if( camTarget == ARCBALL || (camTarget == FIRST_PERSON && fpTarget == CASTAMERE ))
  	castamere.respondKeyDown( key );
  else if( camTarget == FREE )
  	freeCam.respondKeyDown( key );
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647
} 

// normalKeysUp() /////////////////////////////
//
// Callback for key up
//
/////////////////////////////////////////////
void normalKeysUp( unsigned char key, int x, int y ) {
  castamere.respondKeyUp( key );
<<<<<<< HEAD
  allMight.respondKeyUp( key );
=======
  freeCam.respondKeyUp( key );
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647
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
<<<<<<< HEAD
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
  
  // // Cam update
  cam.recomputeCamPosition(
    allMight.getX(), 
    allMight.getY(),
    allMight.getZ()
  );

  // cam.recomputeCamPosition(
  //   castamere.getX(), 
  //   castamere.getY(),
  //   castamere.getZ()
  // );
=======
  allMight.setOrientation(bezierPatch); 

  castamere.update();
  castamere.setOrientation(bezierPatch);
   
  coolPants.update();
  coolPants.setOrientation(bezierPatch);

  // campfire light update
  campfire.update();
  
  // Free wasd cam update
  freeCam.updatePos();
  
  // update the arcball cam based on the target
  float tx, ty, tz;
  switch ( arcballTarget ) {
    case ALL_MIGHT:
      tx = allMight.getX(); ty = allMight.getY(); tz = allMight.getZ();
      break;
    case CASTAMERE:
      tx = castamere.getX(); ty = castamere.getY(); tz = castamere.getZ();
      break;
    case COOL_PANTS:
      tx = coolPants.getX(); ty = coolPants.getY(); tz = coolPants.getZ();
      break;
    default:
      // Should get here
      tx = ty = tz = 0;
  }
  arcballCam.recomputeCamPosition( tx, ty, tz );
  
  // update the first person cam based on the target
  float fx, fy, fz, dirX, dirY, dirZ, mag;
  switch ( fpTarget ) {
    case ALL_MIGHT:
      fx = allMight.getX(); fy = allMight.getY() + 4.0; fz = allMight.getZ();
	    //directional vector
	  	dirX = cos(allMight.getRot() * M_PI/180);
      dirY = 0;
	  	dirZ = -sin(allMight.getRot() * M_PI/180);

	    //and normalize this vector
	    mag = sqrt( dirX*dirX + dirY*dirY + dirZ*dirZ );
	    dirX /= mag; dirY /= mag; dirZ /= mag;
	
      firstPerson.setLookX(fx + dirX*firstPerson.getRad());
      firstPerson.setLookY(fy + dirY*firstPerson.getRad()); 
      firstPerson.setLookZ(fz + dirZ*firstPerson.getRad());	  
      break;

    case CASTAMERE:
      fx = castamere.getX(); fy = castamere.getY(); fz = castamere.getZ();
	    //directional vector
	  	dirX = cos(castamere.getRotationAngle() * M_PI/180);
      dirY = 0;
	  	dirZ = -sin(castamere.getRotationAngle() * M_PI/180);

	    //and normalize this vector
	    mag = sqrt( dirX*dirX + dirY*dirY + dirZ*dirZ );
	    dirX /= mag; dirY /= mag; dirZ /= mag;
      firstPerson.setLookX(fx + dirX*firstPerson.getRad());
      firstPerson.setLookY(fy + dirY*firstPerson.getRad()); 
      firstPerson.setLookZ(fz + dirZ*firstPerson.getRad());
      break;
  	
    case COOL_PANTS:
      fx = coolPants.getX(); fy = coolPants.getY() + coolPants.getH(); fz = coolPants.getZ();
	    //directional vector
	  	dirX = cos(coolPants.getRotation() * M_PI/180);
      dirY = 0;
	  	dirZ = -sin(coolPants.getRotation() * M_PI/180);

	    //and normalize this vector
	    mag = sqrt( dirX*dirX + dirY*dirY + dirZ*dirZ );
	    dirX /= mag; dirY /= mag; dirZ /= mag;
		
      firstPerson.setLookX(fx + dirX*firstPerson.getRad());
      firstPerson.setLookY(fy + dirY*firstPerson.getRad()); 
      firstPerson.setLookZ(fz + dirZ*firstPerson.getRad());
      break;
  	
    default:
      // Shouldn't get here
      fx = fy = fz = 0;
  }
  
  // Set correct first person cam position
  firstPerson.setX(fx); firstPerson.setY(fy); firstPerson.setZ(fz);
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647

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
<<<<<<< HEAD
  // Quit
  if( value == 0 ) { 
=======
  if ( value == 0 ) {
    // switch to arcball on allmight
    arcballTarget = ALL_MIGHT;
    camTarget = ARCBALL;
  }
  else if ( value == 1 ) {
    // switch to arcball on castamere
    arcballTarget = CASTAMERE;
    camTarget = ARCBALL;
  }
  else if ( value == 2 ) {
    // switch to arcball on coolpants
    arcballTarget = COOL_PANTS;
    camTarget = ARCBALL;
  }
  else if ( value == 3 ) {
    // toggle first person viewport on all might
    fpTarget = ALL_MIGHT;
  	camTarget = FIRST_PERSON;
  }
  else if ( value == 4 ) {
    // toggle first person viewport on castamere
    fpTarget = CASTAMERE;
    camTarget = FIRST_PERSON;
  }
  else if ( value == 5 ) {
    // toggle first person viewport on coolpants
    fpTarget = COOL_PANTS;
    camTarget = FIRST_PERSON;
  }
  else if ( value == 6 ) {
    // main view to free camera with wasd controls
	  camTarget = FREE;
  }
  else if( value == 7 ) { 
    // quit
    cleanup();
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647
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
    printf( "Usage: %s worldfile.csv\n", argv[0] );
    exit( 1 );
  }

  // TESTING //////////////////
  // load up the surface points
  bezierPatch = new BezierPatch();
  if ( !bezierPatch->loadControlPoints(argv[1]) ) {
    printf( "Could not load file: %s\n", argv[1] );
    exit( 1 );
  }

<<<<<<< HEAD
  // Set the material as green plastic
  bezierPatch->setMaterial( 
    Material(
      Color(0,0,0),
      Color(0.1, 0.35, 0.1),
      Color(0.45, 0.55, 0.45),
      (0.25 * 128)
    )
  );
  // Initial orient (to set y)
  allMight.setY( bezierPatch->orient(allMight.getX(), allMight.getZ())[0] );
  castamere.setY( 
    bezierPatch->orient(castamere.getX(), castamere.getZ())[0] 
      + (castamere.getHeight()/2)
  );

  // END TESTING //////////////////
=======
  // Set AllMight to follow by parameter t
  allMight.setFollowPath(bezierCurve);
  // Set CoolPants to follow by arclength s 
  coolPants.setFollowPath(bezierCurve);
  // Move Castamere out of the fire
  castamere.setX(-40);

  // initial orient
  campfire.setOrientation( bezierPatch );
  allMight.setOrientation( bezierPatch );
  castamere.setOrientation( bezierPatch );
  coolPants.setOrientation( bezierPatch );
>>>>>>> b1ff7d451d4e45026eeddce72c752c427610c647

  // create a double-buffered GLUT window at (50,50) with predefined windowsize 
  glutInit( &argc, argv ); 
  glutInitDisplayMode( GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA ); 
  glutInitWindowPosition( 50, 50 ); 
  glutInitWindowSize( windowWidth, windowHeight ); 
  windowId = glutCreateWindow( "Guild Wars" ); 

  // Init cam coords to look at all might
  cam.recomputeCamPosition(
    allMight.getX(), 
    allMight.getY(), 
    allMight.getZ()
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
