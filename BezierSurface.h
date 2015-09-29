#pragma once

// CSCI441
//
// Encapsulates a bezier surface.  Allows loading of control points,
// drawing of the cage, and drawing of the surface in wireframe or
// filled.

// To load from file
#include <fstream>
// Vector and math
#include <vector>
#include <math.h>
#include "Point.h"
#include "BezierCurve.h"

// OpenGL / GLUT Libraries we need
#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

using namespace std;

class BezierSurface {
public:
  // Default - does not load any points
  BezierSurface();
  // Constructs and loads from the file automatically
  BezierSurface(char* filename);
  // Loads point from the file
  bool loadControlPoints(char* filename);
  // Computes points on the surface so drawing with triangle strips is easy
  void computeSurface(vector< vector<Point> >& computedPoints, int resolution);
  // Draws a surface over all computed points as a wireframe
  void renderBezierSurfaceWireframe(vector< vector<Point> >& computedPoints);
  // Draws a surface over all computed points as filled
  void renderBezierSurfaceFilled(vector< vector<Point> >& computedPoints);
  // Draws entire surface in sets of 16 points filled
  void drawFilled();
  // Draws entire surface in sets of 16 points wire
  void drawWireframe();

  // Computes the y value for the surface given an x and z
  float computeY(float x, float z);

private:
  // 2d vector of control points
  vector< vector<Point> > controlPoints;
  // All points computed to be on the surface
  vector< vector<Point> > computedPoints;
};
