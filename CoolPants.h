// Author: Tyler Bank
#ifndef _COOLPANTS_H
#define _COOLPANTS_H

#include <GL/glui.h>        // include GLUI header

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "./Point.h"
#include "./BezierCurve.h"
#include "./BezierPatch.h"

class CoolPants
{
	private:
		Point position;
		float angle;
		float height;
		int polyCount;
    // rotation in the xz plane
    float xzrot;
    // surface orientaion
    vector<float> orientation;
    // True if follows the path
    bool followMode;
    // Path to follow
    BezierCurve* path;
    // Parameter (arclength) to denote position on curve
    float s;
    // Scale to draw at
    float scale;
    
		
		void drawBody();
		void drawLeftLeg();
		void drawRightLeg();
		void drawTail();
		void drawHead();
		void drawLimb();
		void drawWheel();

	public:
		CoolPants();
		CoolPants( Point position );
		
		void drawHorse();

    // Draws with the surface orientation
    void draw();

    // Sets the path to follow and turns on follow mode
    void setFollowPath(BezierCurve* path);

    // Sets the surface orientation vector
    void setOrientation(BezierPatch* surface);
		
		void update();
		
		Point getPosition(){return position;}
		
		float getX(){return position.getX();}
		float getY(){return position.getY();}
		float getZ(){return position.getZ();}
		
		// return y component of orientation.
		vector<float> getOrientation(){ return orientation; }
		
		float getRotation(){ return xzrot; }
		
		float getH(){ return height; }
		
		void setX(float x){position.setX(x);}
		void setY(float y){position.setY(y);}
		void setZ(float z){position.setZ(z);}
		
		float getAngle(){return angle;}
		
		void setAngle(float angle){this->angle = angle;}
};

#endif
