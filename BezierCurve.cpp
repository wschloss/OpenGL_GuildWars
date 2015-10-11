// Walter Schlosser
// CSCI441
//
// Implementation of a Bezier curve

#include "BezierCurve.h"

BezierCurve::BezierCurve() {
  // Nothing, vector of control points empty
}

BezierCurve::BezierCurve(const char* filename) {
  // load from file to vector
  loadControlPoints(filename);
}

// Loads control points from a file
// True if succesful, false if an error occured
bool BezierCurve::loadControlPoints(const char* filename) {
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

  // Go ahead and construct the arclength table
  constructArclengthTable(arclengthTable, 100);
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

// Returns the point of the curve given parameter t.  t can be any value, it
// is mapped to the correct range calculated from the number of control points
Point BezierCurve::findCurvePointFromParameter(float t) {
  // Calculate number of valid sections
  int n = (controlPoints.size() - 4) / 3 + 1;
  // Find the section we're in based on t ([0,1] is 1, [1,2] is 2, etc...)
  int section = (int) (t + 1);
  // Cut down to the number of valid sections, this makes the parameter wrap
  // around the curve so following is as easy as t += dt each frame
  section = section % n;
  // calculate the point the correct section of control points
  
  return (
    evaluateBezierCurve(
      controlPoints[ 3*section ],
      controlPoints[ 3*section + 1],
      controlPoints[ 3*section + 2],
      controlPoints[ 3*section + 3],
      t - (int) t
    )
  );
}

// Returns the tangent on the curve given parameter t.  t can be any value, it
// is mapped to the correct range calculated from the number of control points
Point BezierCurve::findCurveTangentFromParameter(float t) {
  // Calculate number of valid sections
  int n = (controlPoints.size() - 4) / 3 + 1;
  // Find the section we're in based on t ([0,1] is 1, [1,2] is 2, etc...)
  int section = (int) (t + 1);
  // Cut down to the number of valid sections, this makes the parameter wrap
  // around the curve so following is as easy as t += dt each frame
  section = section % n;
  // calculate the point the correct section of control points
  
  return (
    evaluateCurveTangent(
      controlPoints[ 3*section ],
      controlPoints[ 3*section + 1],
      controlPoints[ 3*section + 2],
      controlPoints[ 3*section + 3],
      t - (int) t
    )
  );
}

// Constructs the arc length table, rows of (t, s), so that parameters can
// be translated
void BezierCurve::constructArclengthTable(vector< vector<float> >& table, int resolution) {
  // find the number of sections that make up the curve
  int n = (controlPoints.size() - 4) / 3 + 1;
  // Find the initial point
  Point prev = findCurvePointFromParameter(0);
  // Push the initial row
  vector<float> row;
  row.push_back(0);
  row.push_back(0);
  table.push_back(row);

  // counting and tracking variables
  int rowcount = 1;
  Point current;
  // iterate t over the entire range of the curve
  for (float t = 1.0/resolution; t < n; t += 1.0/resolution) {
    // find the new point on the curve
    current = findCurvePointFromParameter(t);
    // Find the distance to this new point
    float ds = pointDistance(prev, current);
    // push back the new entry
    float s = table[rowcount - 1][1] + ds;
    row.clear();
    row.push_back(t);
    row.push_back(s);
    table.push_back(row);

    // Update count vars for next iteration
    rowcount++;
    prev = current;
  }

  // push that last entry since the float precision will probably miss it in the loop
  current = findCurvePointFromParameter(n);
  float ds = pointDistance(prev, current);
  float s = table[rowcount - 1][1] + ds;
  row.clear();
  row.push_back(n);
  row.push_back(s);
  table.push_back(row);
}

// Translates an arc length value s to the corresponding parameter t for the
// curve.  s can be any value - it is mapped to the range appropriate
float BezierCurve::translateArclengthToT(float s) {
  // Map s to the correct range, [0, total length]
  float sprime = s - arclengthTable.back()[1] * ( (int) (s / arclengthTable.back()[1]) );
  // Binary search for the correct table row
  int first = 0;
  int last = arclengthTable.size() - 1;
  int current = (first + last) / 2;
  while (last - first > 1) {
    if (sprime > arclengthTable[current][1])
     first = current;
    else if (sprime < arclengthTable[current][1])
     last = current;
    // off chance we hit s exactly
    else {
     // return the corresponding t
     return arclengthTable[current][0];
    }

    // update search position
    current = (first + last) / 2; 
  } 

  // narrowed down to two rows, pick the closest one
  if (sprime - arclengthTable[first][1] < arclengthTable[last][1] - sprime)
    return arclengthTable[first][1];
  else
    return arclengthTable[last][1];
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
