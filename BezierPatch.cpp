// CSCI441
//
// Implementation of bezier patch methods

#include "BezierPatch.h"

// Default - doesn't load any points
BezierPatch::BezierPatch() {

}

// Auto loads control points
BezierPatch::BezierPatch(char* filename) {
  loadControlPoints(filename);
}

// Loads points from a file
bool BezierPatch::loadControlPoints(char* filename) {
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
void BezierPatch::computeSurface(vector< vector<Point> >& computedPoints, int resolution) {
  // Iterate over u parameter for the row and v for the columns
  for (float v = 0; v <= 1; v += 1.0/resolution) {
    // Compute a row of points on the surface
    vector<Point> row;
    // And a row of normals
    vector<Point> normalRow;
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
      
      // Compute partial w/r/t u
      Point dsdu = pow(1 - v, 3)*BezierCurve::evaluateCurveTangent(
                                                controlPoints[0][0],
                                                controlPoints[0][1],
                                                controlPoints[0][2],
                                                controlPoints[0][3],
                                                u)
                + 3*pow(1 - v, 2)*v*BezierCurve::evaluateCurveTangent(
                                                controlPoints[1][0],
                                                controlPoints[1][1],
                                                controlPoints[1][2],
                                                controlPoints[1][3],
                                                u)
                + 3*(1 - v)*pow(v, 2)*BezierCurve::evaluateCurveTangent(
                                                controlPoints[2][0],
                                                controlPoints[2][1],
                                                controlPoints[2][2],
                                                controlPoints[2][3],
                                                u)
                + pow(v, 3)*BezierCurve::evaluateCurveTangent(
                                                controlPoints[3][0],
                                                controlPoints[3][1],
                                                controlPoints[3][2],
                                                controlPoints[3][3],
                                                u);

      // Compute partial w/r/t v
      Point dsdv = 3*pow(1 - v, 2)*(BezierCurve::evaluateBezierCurve(
                                                controlPoints[1][0],
                                                controlPoints[1][1],
                                                controlPoints[1][2],
                                                controlPoints[1][3],
                                                u) -
                                    BezierCurve::evaluateBezierCurve(
                                                controlPoints[0][0],
                                                controlPoints[0][1],
                                                controlPoints[0][2],
                                                controlPoints[0][3],
                                                u))
                + 6*(1 - v)*v*(BezierCurve::evaluateBezierCurve(
                                                controlPoints[2][0],
                                                controlPoints[2][1],
                                                controlPoints[2][2],
                                                controlPoints[2][3],
                                                u) - 
                              BezierCurve::evaluateBezierCurve(
                                                controlPoints[1][0],
                                                controlPoints[1][1],
                                                controlPoints[1][2],
                                                controlPoints[1][3],
                                                u))
                + 3*pow(v, 2)*(BezierCurve::evaluateBezierCurve(
                                                controlPoints[3][0],
                                                controlPoints[3][1],
                                                controlPoints[3][2],
                                                controlPoints[3][3],
                                                u) -
                              BezierCurve::evaluateBezierCurve(
                                                controlPoints[2][0],
                                                controlPoints[2][1],
                                                controlPoints[2][2],
                                                controlPoints[2][3],
                                                u));

      // Cross to find the normal
      float nx = dsdu.getY()*dsdv.getZ() - dsdu.getZ()*dsdv.getY();
      float ny = dsdu.getZ()*dsdv.getX() - dsdu.getX()*dsdv.getZ();
      float nz = dsdu.getX()*dsdv.getY() - dsdu.getY()*dsdv.getX();

      // push new normal
      normalRow.push_back(Point(nx,ny,nz));
    }
    // Add row of points to surface
    computedPoints.push_back(row);
    // Add row of normals to the surface
    computedNormals.push_back(normalRow);
  }
}

// Draws a surface over all computed points as a wire frame
void BezierPatch::renderBezierPatchWireframe(vector< vector<Point> >& computedPoints) {
  // Points to draw lines between
  Point* current, *right, *up, *diag;
  // Setup color, width, no lighting
  glDisable(GL_LIGHTING);
  glColor3f(0,1,0);
  glLineWidth(2.0);

  // Iterate over the 2d vector and draw lines
  for (size_t i = 0; i < computedPoints.size() - 1; i++) {

    glBegin(GL_LINE_STRIP);
    for (size_t j = 0; j < computedPoints[i].size() - 1; j++) {
      current = &computedPoints[i][j];
      right = &computedPoints[i][j+1];
      up = &computedPoints[i+1][j];
      diag = &computedPoints[i+1][j+1];
      
      // CCW square
      glVertex3f(current->getX(), current->getY(), current->getZ());
      glVertex3f(right->getX(), right->getY(), right->getZ());
      glVertex3f(diag->getX(), diag->getY(), diag->getZ());
      glVertex3f(up->getX(), up->getY(), up->getZ());
      glVertex3f(current->getX(), current->getY(), current->getZ());
    }
    glEnd();

  }

  // Restore defaults
  glLineWidth(1.0);
  glEnable(GL_LIGHTING);
}

// Draws a surface over all computed points as filled
void BezierPatch::renderBezierPatchFilled(vector< vector<Point> >& computedPoints) {
  // Points to draw the quad
  Point* current, *right, *up, *diag;
  // Iterate over all computed points and draw quads
  glColor3f(0,1,0);
  glBegin(GL_QUADS); 
  for (size_t i = 0; i < computedPoints.size() - 1; i++) {
    for (size_t j = 0; j < computedPoints[i].size() - 1; j++) {
      current = &computedPoints[i][j];
      right = &computedPoints[i+1][j];
      up = &computedPoints[i][j+1];
      diag = &computedPoints[i+1][j+1];

      // CCW square
      glVertex3f(current->getX(), current->getY(), current->getZ());
      glVertex3f(right->getX(), right->getY(), right->getZ());
      glVertex3f(diag->getX(), diag->getY(), diag->getZ());
      glVertex3f(up->getX(), up->getY(), up->getZ());
    }
  }
  glEnd();
}

// Convenience method draws the filled surface
void BezierPatch::drawFilled() {
  renderBezierPatchFilled(computedPoints);
}

// convenience method draws the wireframe
void BezierPatch::drawWireframe() {
  renderBezierPatchWireframe(computedPoints);
}

// computes the y value (height) given an x and z in the plane
float BezierPatch::computeY(float x, float z) {
  // TODO
  // Search through computed points to find closest to x,z, return the y
  // OR invert the function on paper to find u,v for the x,z and compute the y
  return 0;
}
