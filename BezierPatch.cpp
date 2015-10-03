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
  computeSurface(computedPoints, 200);

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
      // Normalize
      float mag2 = pow(nx, 2) + pow(ny, 2) + pow(nz, 2);
      nx /= sqrt(mag2);
      ny /= sqrt(mag2);
      nz /= sqrt(mag2);

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
  // Normals to set for the quad
  Point* nc, *nr, *nu, *nd;
  // Iterate over all computed points and draw quads
  glBegin(GL_QUADS); 
  for (size_t i = 0; i < computedPoints.size() - 1; i++) {
    for (size_t j = 0; j < computedPoints[i].size() - 1; j++) {
      current = &computedPoints[i][j];
      right = &computedPoints[i+1][j];
      up = &computedPoints[i][j+1];
      diag = &computedPoints[i+1][j+1];

      nc = &computedNormals[i][j];
      nr = &computedNormals[i+1][j];
      nu = &computedNormals[i][j+1];
      nd = &computedNormals[i+1][j+1];

      // CCW square
      glNormal3f(nc->getX(), nc->getY(), nc->getZ());
      glVertex3f(current->getX(), current->getY(), current->getZ());

      glNormal3f(nr->getX(), nr->getY(), nr->getZ());
      glVertex3f(right->getX(), right->getY(), right->getZ());

      glNormal3f(nd->getX(), nd->getY(), nd->getZ());
      glVertex3f(diag->getX(), diag->getY(), diag->getZ());

      glNormal3f(nu->getX(), nu->getY(), nu->getZ());
      glVertex3f(up->getX(), up->getY(), up->getZ());
    }
  }
  glEnd();
}

// Convenience method draws the filled surface
void BezierPatch::drawFilled() {
  // Set material props
  mat.set_as_current_material();
  renderBezierPatchFilled(computedPoints);
}

// convenience method draws the wireframe
void BezierPatch::drawWireframe() {
  renderBezierPatchWireframe(computedPoints);
}

// Computes the height and necessary rotation and returns a vector in the format
// [ ytranslate, degrees, axisX, axisY, axisZ ]
// To orient, call:
// glTranslatef(0,ytranslate,0);
// glRotatef(degrees, axisX, axisY, axisZ);
vector<float> BezierPatch::orient(float x, float z) {
  // Init vars to point at 0,0 in u,v space
  float closesti = 0;
  float closestj = 0;
  float closestXZDist = 1000000;
  // Search for the closest point in the x, z plane
  for (size_t i = 0; i < computedPoints.size(); i++) {
    for (size_t j = 0; j < computedPoints[i].size(); j++) {
      float cx = computedPoints[i][j].getX();
      float cz = computedPoints[i][j].getZ();
      if ( pointDistance(Point(x, 0, z), Point(cx, 0, cz)) < closestXZDist) {
        // Save as new closest
        closestXZDist = pointDistance(Point(x, 0, z), Point(cx, 0, cz));
        closesti = i;
        closestj = j;
      }
    }
  }
  
  // Now get the surface height
  float surfaceY = computedPoints[closesti][closestj].getY();

  // Find the rotation variables
  Point normal = computedNormals[closesti][closestj];
  // Rotation axis ( 0,1,0 cross normal )
  float ux = normal.getZ();
  float uy = 0;
  float uz = -normal.getX();
  // Angle (from 0,1,0 dot normal) in radians
  float angle = acos(normal.getY());
  //convert
  angle *= 180.0/M_PI;

  // Package the values
  vector<float> ret;
  ret.push_back(surfaceY);
  ret.push_back(angle);
  ret.push_back(ux);
  ret.push_back(uy);
  ret.push_back(uz);

  return ret;
}

// Sets the material
void BezierPatch::setMaterial(Material mat) {
  this->mat = mat;
}
