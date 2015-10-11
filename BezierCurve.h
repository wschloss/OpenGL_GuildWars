#pragma once
// Walter Schlosser
// CSCI441
//
// Data for a bezier curve, computer from control points
// Load control points from a file to use.

// To load from file
#include <fstream>
// Store control points
#include <vector>
#include <math.h>

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

#include "Point.h"
using namespace std;

class BezierCurve {
public:
  // Default constructor, must load control points manually
  BezierCurve();
  // Constructs and loads from a csv file
  BezierCurve(const char* filename);

  // Loads control points from a csv file
  bool loadControlPoints(const char* filename);

  // Computes point along curve given 4 control points and parameter t [0,1]
  static Point evaluateBezierCurve(Point p0, Point p1, Point p2, Point p3, float t);

  // Evaluates the tangent with the control points and the parameter t [0,1]
  static Point evaluateCurveTangent(Point p0, Point p1, Point p2, Point p3, float t);

  // Returns the correct point of the curve given a parameter t.
  // t can be any positive value - it will be mapped to the range
  // that is appropriate for this curve (calculated from num control points
  Point findCurvePointFromParameter(float t);

  // Returns the tangent for the curve gicen parameter t.
  // t can be any positive value, it will be mapped to the range
  // that is appropriate for the number of control points
  Point findCurveTangentFromParameter(float t);

  // Constructs an arc length table which stores (t, s) values for translation
  void constructArclengthTable(vector< vector<float> >& table, int resolution);

  // Translates an arc length value s to the corresponding parameter t for the
  // curve.  s can be any value - it is mapped to the range appropriate
  float translateArclengthToT(float s);

  // Renders curve given four control points
  void renderBezierCurve(Point p0, Point p1, Point p2, Point p3, int resolution);

  // Renders the cage that defines the curve (connected control points
  void renderCage();

  // Renders the entire curve in sets of 4 points for C0 continuity
  void draw();

  /* GETTERS */
  vector<Point> getControlPoints() { return controlPoints; }

private:
  // Stores control points
  vector<Point> controlPoints;

  // Stores the arclength table, each row is (t, s)
  vector< vector<float> > arclengthTable;
};
