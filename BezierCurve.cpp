// Walter Schlosser
// CSCI441
//
// Implementation of a Bezier curve

#include "BezierCurve.h"

BezierCurve::BezierCurve() {
  // Nothing, vector of control points empty
}

BezierCurve::BezierCurve(char* filename) {
  // load from file to vector
  loadControlPoints(filename);
}

// Loads control points from a file
// True if succesful, false if an error occured
bool BezierCurve::loadControlPoints(char* filename) {
  // Open a file stream
  ifstream input;
  input.open(filename);
  if (input.fail()) {
    // clean up and return
    input.close();
    return false;
  }
  // Get the number of points, read the points into the vector
  int numPoints;
  input >> numPoints;
  float x, y, z;
  char comma;
  for (int i = 0; i < numPoints; i++) {
      input >> x >> comma >> y >> comma >> z;        
      controlPoints.push_back(Point(x,y,z));
  }
  input.close();

  return true;
}

// Computes a point on the curve given 4 control points and parameter t [0,1]
Point BezierCurve::evaluateBezierCurve( Point p0, Point p1, Point p2, Point p3, float t ) {
  // Use the cubic function for a bezier curve
  Point f = pow((1 - t), 3)*p0 + 3*pow((1 - t), 2)*t*p1 +
              3*(1 - t)*pow(t, 2)*p2 + pow(t, 3)*p3;
  return f;
}

// Computes the tangent vector at the given control and parameter
// Note this returns a vector technically, but the Point class is just x,y,z
Point BezierCurve::evaluateCurveTangent(Point p0, Point p1, Point p2, Point p3, float t) {
  Point fprime = 3*pow(1 - t, 2)*(p1 - p0) + 6*(1 - t)*t*(p2 - p1) +
                  3*pow(t, 2)*(p3 - p2);
  return fprime;
}

// Renders curve in 'resolution' segments for the 4 points passed
void BezierCurve::renderBezierCurve( Point p0, Point p1, Point p2, Point p3, int resolution ) {
  glDisable(GL_LIGHTING);
  glColor3f(0,0,1);
  glLineWidth(2.0);

  glBegin(GL_LINE_STRIP); {  
    // Iterate t from 0 to 1 in steps of 1/resolution
    for (float t = 0; t <= 1; t += 1.0f/resolution) {
      Point p = evaluateBezierCurve(p0, p1, p2, p3, t);
      glVertex3f(p.getX(), p.getY(), p.getZ());  
    }
    // Draw the last strip since float precision will probably skip it
    glVertex3f(p3.getX(), p3.getY(), p3.getZ());
  } glEnd();

  glLineWidth(1.0);
  glEnable(GL_LIGHTING);
}

// Draws the cage (connected control points) that define the curve
void BezierCurve::renderCage() {
  // Draw all points in vector as green spheres of radius 0.2
  glColor3f(0,1,0);
  for (size_t i = 0; i < controlPoints.size(); i++) {
    Point p = controlPoints[i];
    glPushMatrix(); {
      glTranslatef(p.getX(), p.getY(), p.getZ());
      glutSolidSphere(0.2, 20, 20);
    } glPopMatrix();
  }

  // Disable lighting for lines
  glDisable(GL_LIGHTING);
  // Yellow and 3 times as thick
  glColor3f(1,1,0);
  glLineWidth(3.0);

  // Iterate over points
  glBegin(GL_LINE_STRIP); {
    for (size_t i = 0; i < controlPoints.size(); i++) {
      Point p = controlPoints[i];
      glVertex3f(p.getX(), p.getY(), p.getZ());
    }
  } glEnd();

  // Restore default width and lighting
  glLineWidth(1.0f);
  glEnable(GL_LIGHTING);

}

// Renders the entire curve in sets of 4 control points for C0 continuity
void BezierCurve::draw() {
  // Resolution of 20, so step size on t is 1/20
  // Break into sets of 4 points
  for (size_t i = 0; i+3 < controlPoints.size(); i += 3) {
    renderBezierCurve(controlPoints[i], controlPoints[i+1],
                        controlPoints[i+2], controlPoints[i+3], 20);
  }
}
