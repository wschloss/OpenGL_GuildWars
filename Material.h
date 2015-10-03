#pragma once
// Walter Schlosser
// CSCI441
//
// Encapsulates data for a material

// Color object
#include "Color.h"

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					    // else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class Material {
public:
  // Defaults to all white
  Material();
  // Set all three colors and shine
  Material(Color amb, Color dif, Color spec, float shine);
  // Sets up material with gl calls
  void set_as_current_material();
  
private:
  // Colors for three properties
  Color amb, dif, spec;
  // Shininess, defaults to 0
  float shine; 
  // alpha, defaults to one
  float alpha;
};
