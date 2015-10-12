#pragma once
// Free camera class

// Math
#include <math.h>

class FreeCamera {
public:
  // Default
  FreeCamera();

  // recomputes direction vector
  void recomputeCamDir();
  
  // Respond to keys
  void respondKeyDown( unsigned char key );
  void respondKeyUp( unsigned char key );
  
  // update position based on key inputs
  void updatePos();

  // Get and set
  float getX() { return x; }
  float getY() { return y; }
  float getZ() { return z; }
  float getDirX() { return dirX; }
  float getDirY() { return dirY; }
  float getDirZ() { return dirZ; }
  float getLookX() { return lookX; }
  float getLookY() { return lookY; }
  float getLookZ() { return lookZ; }
  float getUpX() { return upX; }
  float getUpY() { return upY; }
  float getUpZ() { return upZ; }
  float getRad() { return r; }
  void setX(float x) { this->x = x; }
  void setY(float y) { this->y = y; }
  void setZ(float z) { this->z = z; }
  
  // Incrementers
  void incrementTheta(float dT) { 
    this->theta += dT;
  }
  void incrementPhi(float dP) { 
	  this->phi += dP;
      if(this->phi <= 0)
          this->phi = 0+0.001;
      if(this->phi >= M_PI)
          this->phi = M_PI-0.001;
  }
  void incrementRadius(float delta, float lowerbound) { 
    this->r += delta;
    if (this->r < lowerbound) this->r = lowerbound;
  }
private:
  // Coords in cartesian
  float x, y, z;
  // direction 
  float dirX, dirY, dirZ;
  // speed
  float speed;
  // Coords in spherical relative to the target
  float r, theta, phi; 
  // Look at point
  float lookX, lookY, lookZ;
  // Up vector
  float upX, upY, upZ;
};
