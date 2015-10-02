#pragma once
// Walter Schlosser
// CSCI441
//
// This class represents a point in 3d space
class Point {
public:
  Point() : x(0), y(0), z(0) {}
  Point(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
  float getX() { return x; }
  float getY() { return y; }
  float getZ() { return z; }
  void setX(float x) { this->x = x; }
  void setY(float y) { this->y = y; }
  void setZ(float z) { this->z = z; }
private:
  float x, y, z;
};

// Multiplication of point by a float, rhs and lhs
Point operator*(Point p, float f);
Point operator*(float f, Point p);
// Addition of two points
Point operator+(Point a, Point b);
// Subtraction of two points
Point operator-(Point a, Point b);
