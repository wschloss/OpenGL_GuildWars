// Walter Schlosser
// CSCI441
//
// ArcBallCamera implementation

#include "ArcBallCamera.h"

// Default 'scenic' viewpoint of the origin
ArcBallCamera::ArcBallCamera() {
  this->x = this->y = this->z = 0;
  this->lookX = this->lookY = this->lookZ = 0;
  this->r = 200;
  this->theta = -M_PI/3.0f;
  this->phi = M_PI/2.8f;
  this->upX = this->upZ = 0;
  this->upY = 1;
}

// Sets new look at point, recomputes cartesian position
void ArcBallCamera::recomputeCamPosition(float lx, float ly, float lz) {
  this->lookX = lx;
  this->lookY = ly;
  this->lookZ = lz;

  // Compute cartesion coords
  x = r * sin(theta) * cos(phi);
  y = r * cos(theta);
  z = r * sin(theta) * sin(phi);

  // Add to car position to get actual position
  x += lx;
  y += ly;
  z += lz;
}
