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
		float orien;
		int polyCount;
    // rotation in the xz plane
    float xzrot;
    // True if follows the path
    bool followMode;
    // Path to follow
    BezierCurve* path;
    // Parameter (arclength) to denote position on curve
    float s;
    
		
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
    void draw(BezierPatch* surface);

    // Sets the path to follow and turns on follow mode
    void setFollowPath(BezierCurve* path);
		
		void update();
		
		Point getPosition(){return position;}
		
		float getX(){return position.getX();}
		float getY(){return position.getY();}
		float getZ(){return position.getZ();}
		
		float getRotation(){ return xzrot; }
		float getOrient(){ return orien; }
		
		float getH(){ return height; }
		
		void setX(float x){position.setX(x);}
		void setY(float y){position.setY(y);}
		void setZ(float z){position.setZ(z);}
		
		float getAngle(){return angle;}
		
		void setAngle(float angle){this->angle = angle;}
};

#endif
