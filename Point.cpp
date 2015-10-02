// Walter Schlosser
// CSCI441
//
// Point class implementation

#include "Point.h"

Point operator*(Point p, float f) {
  return Point(p.getX() * f, p.getY() * f, p.getZ() * f);
}

Point operator*(float f, Point p) {
  return Point(p.getX() * f, p.getY() * f, p.getZ() * f);
}

Point operator+(Point a, Point b) {
  return Point(a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}

Point operator-(Point a, Point b) {
  return Point(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());
}

// compute distance between two points
float pointDistance(Point a, Point b) {
  float dis2 = pow(a.getX() - b.getX(), 2) +
              pow(a.getY() - b.getY(), 2) +
              pow(a.getZ() - b.getZ(), 2);
  return sqrt(dis2);
}
