#pragma once

// Walter Schlosser
// CSCI441
//
// The hero All Might for drawing

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif
#include <math.h>

#include "BezierPatch.h"


class AllMight {
public:
    // Default
    AllMight();

    // Draws main body - head, body, and spoiler
    void drawBody();
    // Draws one wheel - torus
    void drawWheel();
    // Draws the exhaust pipe and flame
    void drawExhaust();
    // Draws entire vehicle with no position transforms
    void drawVehicle();
    // Draws with position transforms
    void draw();
    // Draws at the surface
    void draw(BezierPatch* surface);
    // Updates the state of the car (pos, rot, wheelrot, flame, etc)
    void update();
    // Finds the heading direction from the rotation
    void calcDirection();

    // Reponse to key functions
    void respondKeyDown(unsigned char key);
    void respondKeyUp(unsigned char key);
    
    // Getters and setters
    
    // Sets this hero to follow mode and follows the passed curve
    void setFollowPath(BezierCurve* path);
    
    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }
    float getRot() { return rot; }
    float getSpeed() { return speed; }
    float getDeltaRot() { return deltaRot; }

    void setX(float x) { 
      this->x = x;
      this->x = fmax(-600, fmin(x, 600));
    }
    void setY(float y) { this->y = y; }
    void setZ(float z) {
      this->z = z;
      this->z = fmax(-600, fmin(z, 600));
    }
    void setSpeed(float speed) { this->speed = speed; }
    void setDeltaRot(float deltaRot) { this->deltaRot = deltaRot; }

private:
    // coords
    float x, y, z;
    // Direction
    float dirX, dirZ;
    // Rotation
    float rot, deltaRot;
    // Speed
    float speed;
    // Wheel vars
    float wheelRot;
    // Radius of the flame cone
    float flameBase;

    // True if should enter follow mode
    // Is set when setting a bezier curve path
    bool followMode;
    // Path to follow
    BezierCurve* path;
    // Parameter along the curve
    float t;
};
