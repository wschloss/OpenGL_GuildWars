// Walter Schlosser
// CSCI441
//
// ArcBallCamera implementation

#include "FreeCamera.h"

// Default 'scenic' viewpoint of the origin
FreeCamera::FreeCamera() {
  this->x = this->y = this->z = 100;
  this->r = 20;
  this->theta = -M_PI/3.0;
  this->phi = M_PI/2.0;
  this->upX = this->upZ = 0;
  this->upY = 1;
  //this->speed = 0.0;
  
  recomputeCamDir();
}

// Sets new camera position, recomputes direction
void FreeCamera::recomputeCamDir() {
  
  //directional vector
	dirX =  r*sin(theta)*sin(phi);
	dirY = -r*cos(phi);
	dirZ = -r*cos(theta)*sin(phi);

  //and normalize this vector
  float mag = sqrt( dirX*dirX + dirY*dirY + dirZ*dirZ );
  dirX /= mag;  dirY /= mag;  dirZ /= mag;
  
  // The actual look at point is:
  lookX = x + dirX;
  lookY = y + dirY;
  lookZ = z + dirZ;
}

void FreeCamera::respondKeyDown( unsigned char key )
{
	if(key == 'w')
	{
		speed = 5.0f;
	}
	if(key == 's')
	{
		speed = -5.0f;
	}
}

void FreeCamera::respondKeyUp( unsigned char key )
{
	if (speed != 0 && (key == 'w' || key == 's')){
    	speed = 0;
	}
}

void FreeCamera::updatePos()
{
	this->x += dirX*speed;
	this->y += dirY*speed;
	this->z += dirZ*speed;
	
    lookX = x + dirX;
    lookY = y + dirY;
    lookZ = z + dirZ;
}
