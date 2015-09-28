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
