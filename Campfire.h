// Walter Schlosser
// CSCI441
//
// A dynamic light which also draws a campfire.

#pragma once

#ifdef __APPLE__      // if compiling on Mac OS
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else         // else compiling on Linux OS
  #include <GL/glut.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

#include "Light.h"
#include "Material.h"
#include "Color.h"
#include "BezierPatch.h"

class Campfire {
public:
  // Defaults
  Campfire();

  // Enables the light properties for this object
  void enable();

  // Updates the light color props so that the light flickers
  void update();

  // Draws a brown log
  void drawLog();

  // Draws the campfire
  void draw();

  // Sets up the rotation and y translate to be on the surface
  void setOrientation(BezierPatch* surface);

  // returns a pointer to this campfire
  Campfire* self();

private:
  // The light this object uses
  Light* light;
  // surface orientation
  vector<float> orientation;
};
