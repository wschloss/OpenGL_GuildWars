#pragma once
// Walter Schlosser
// CSCI441
//
// This class encapsulates an arcball camera

// Math
#include <math.h>

class ArcBallCamera {
public:
  // Default, set 'scenic' view looking at 0,0,0
  ArcBallCamera();

  // Updates look at point, and computes x, y, z
  void recomputeCamPosition(float lx, float ly, float lz);

  // Get and set
  float getX() { return x; }
  float getY() { return y; }
  float getZ() { return z; }
  float getLookX() { return lookX; }
  float getLookY() { return lookY; }
  float getLookZ() { return lookZ; }
  float getUpX() { return upX; }
  float getUpY() { return upY; }
  float getUpZ() { return upZ; }
  void setX(float x) { this->x = x; }
  void setY(float y) { this->y = y; }
  void setZ(float z) { this->z = z; }
  // Incrementers
  void incrementTheta(float delta) { 
    this->theta += delta;
    this->theta = fmax(0.001, fmin(M_PI - 0.001, this->theta));
  }
  void incrementPhi(float delta) { this->phi += delta; }
  void incrementRadius(float delta, float lowerbound) { 
    this->r += delta;
    if (this->r < lowerbound) this->r = lowerbound;
  }
private:
  // Coords in cartesian
  float x, y, z;
  // Coords in spherical relative to the target
  float r, theta, phi; 
  // Look at point
  float lookX, lookY, lookZ;
  // Up vector
  float upX, upY, upZ;
};
