// Walter Schlosser
// CSCI441
//
// Encapsulates functionality for a light

#pragma once

#include "Color.h"

#ifdef __APPLE__      // if compiling on Mac OS
  #include <GLUT/glut.h>
  #include <OpenGL/gl.h>
  #include <OpenGL/glu.h>
#else         // else compiling on Linux OS
  #include <GL/glut.h>
  #include <GL/gl.h>
  #include <GL/glu.h>
#endif

class Light {
public:
  // Defaults to a white light, but must specify the light number
  // Defaults position to 0,0,0
  Light(GLenum number);
  // Set this lights colors during construction
  Light(GLenum number, Color amb, Color dif, Color spec);
  // Set the position
  void setPosition(float x, float y, float z);
  // Reset the position if you want a static light (call after gluLookAt)
  void resetPosition();
  // Enable this light
  void enable();
  // Set the colors
  void setColors(Color amb, Color dif, Color spec);
  
private:
  // The number of this light
  GLenum number;
  // Color properties
  Color amb, dif, spec;
  // Position
  float x, y, z;
};
