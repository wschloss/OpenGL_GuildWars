#pragma once

// CSCI441
//
// Encapsulates a bezier patch.  Allows loading of control points,
// drawing of the cage, and drawing of the surface in wireframe or
// filled.

// To load from file
#include <fstream>
// Vector and math
#include <vector>
#include <math.h>
#include "Point.h"
#include "BezierCurve.h"
#include "Material.h"

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

class BezierPatch {
public:
  // Default - does not load any points
  BezierPatch();
  // Constructs and loads from the file automatically
  BezierPatch(char* filename);
  // Loads point from the file
  bool loadControlPoints(char* filename);
  // Computes points on the surface so drawing with triangle strips is easy
  void computeSurface(vector< vector<Point> >& computedPoints, int resolution);
  // Draws a surface over all computed points as a wireframe
  void renderBezierPatchWireframe(vector< vector<Point> >& computedPoints);
  // Draws a surface over all computed points as filled
  void renderBezierPatchFilled(vector< vector<Point> >& computedPoints);
  // Convenience method to draw the whole patch filled
  void drawFilled();
  // Convenience method to draw the whole patch wireframe
  void drawWireframe();

  // Calls gl transforms to rotate the objects up vector (assumed 0,1,0) to the
  // surface normal and translate the y up to the surface.
  // Pass the x, z coord of the obejct
  // NOTE: Push matrix before this call and pop after
  float orient(float x, float z);

  // SETTERS
  void setMaterial(Material mat);

private:
  // 2d vector of control points
  vector< vector<Point> > controlPoints;
  // All points computed to be on the surface
  vector< vector<Point> > computedPoints;
  // The associated normal at each computed point
  vector< vector<Point> > computedNormals;
  // The material used for drawing this surface filled
  Material mat;
};

