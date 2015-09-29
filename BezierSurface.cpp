// CSCI441
//
// Implementation of bezier surface methods

#include "BezierSurface.h"

// Default - doesn't load any points
BezierSurface::BezierSurface() {

}

// Auto loads control points
BezierSurface::BezierSurface(char* filename) {
  loadControlPoints(filename);
  // Compute the surface points
  computeSurface(computedPoints, 20);
}

// Loads points from a file
bool BezierSurface::loadControlPoints(char* filename) {
  // Open a file stream
  ifstream input;
  input.open(filename);
  if (input.fail()) {
    // clean up and return
    input.close();
    return false;
  }
  
  // Get the number of points, read the points into the 2d vector
  int numPoints;
  input >> numPoints;
  float x, y, z;
  char comma;
  // Iterate over the rows (note the rounding down of num/4 matters)
  for (int i = 0; i < numPoints/4; i++) {
    vector<Point> row;
    // Read 4 points for this row
    for (int j = 0; j < 4; j++) {
      input >> x >> comma >> y >> comma >> z;        
      row.push_back(Point(x,y,z));
    }
    controlPoints.push_back(row);
  }
  input.close();

  // Compute the surface points
  computeSurface(computedPoints, 20);

  return true;
}

// Computes all points on the surface and stores them in the passed vector
void BezierSurface::computeSurface(vector< vector<Point> >& computedPoints, int resolution) {
  // Iterate over u parameter for the row and v for the columns
  for (float v = 0; v <= 1; v += 1.0/resolution) {
    // Compute a row of points on the surface
    vector<Point> row;
    for (float u = 0; u <= 1; u += 1.0/resolution) {
      Point point = BezierCurve::evaluateBezierCurve(
                BezierCurve::evaluateBezierCurve(controlPoints[0][0],
                                                  controlPoints[0][1],
                                                  controlPoints[0][2],
                                                  controlPoints[0][3],
                                                  u),
                BezierCurve::evaluateBezierCurve(controlPoints[1][0],
                                                  controlPoints[1][1],
                                                  controlPoints[1][2],
                                                  controlPoints[1][3],
                                                  u),
                BezierCurve::evaluateBezierCurve(controlPoints[2][0],
                                                  controlPoints[2][1],
                                                  controlPoints[2][2],
                                                  controlPoints[2][3],
                                                  u),
                BezierCurve::evaluateBezierCurve(controlPoints[3][0],
                                                  controlPoints[3][1],
                                                  controlPoints[3][2],
                                                  controlPoints[3][3],
                                                  u),
                v);
      // Add point to the surface
      row.push_back(point);
    }
    // Add row of points to surface
    computedPoints.push_back(row);
  }
}

// Draws a surface over all computed points as a wire frame
void BezierSurface::renderBezierSurfaceWireframe(vector< vector<Point> >& computedPoints) {
  // Points to draw lines between
  Point* current, *right, *up;
  // Setup color, width, no lighting
  glDisable(GL_LIGHTING);
  glColor3f(0,0,1);
  glLineWidth(2.0);

  glBegin(GL_LINES);
  // Iterate over the 2d vector and draw lines
  for (int i = 0; i < computedPoints.size() - 1; i++) {

    for (int j = 0; j < computedPoints[i].size() - 1; j++) {
      current = &computedPoints[i][j];
      right = &computedPoints[i][j+1];
      up = &computedPoints[i+1][j];
      
      // Line to the right
      glVertex3f(current->getX(), current->getY(), current->getZ());
      glVertex3f(right->getX(), right->getY(), right->getZ());
      //Line up
      glVertex3f(current->getX(), current->getY(), current->getZ());
      glVertex3f(up->getX(), up->getY(), up->getZ());
    }

  }
  glEnd();

  // Restore defaults
  glLineWidth(1.0);
  glEnable(GL_LIGHTING);
}

// Draws a surface over all computed points as filled
void BezierSurface::renderBezierSurfaceFilled(vector< vector<Point> >& computedPoints) {

}

// Convenience method draws the filled surface
void BezierSurface::drawFilled() {
  renderBezierSurfaceFilled(computedPoints);
}

// convenience method draws the wireframe
void BezierSurface::drawWireframe() {
  renderBezierSurfaceWireframe(computedPoints);
}

// computes the y value (height) given an x and z in the plane
float BezierSurface::computeY(float x, float z) {

}
