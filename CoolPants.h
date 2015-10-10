// Author: Tyler Bank
#ifndef _COOLPANTS_H
#define _COOLPANTS_H

#include <GL/glui.h>        // include GLUI header

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "./point.h"

class CoolPants
{
	private:
		Point position;
		float angle;
		float height;
		int polyCount;
		
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
		
		void update();
		
		Point getPosition(){return position;}
		
		float getX(){return position.getX();}
		float getY(){return position.getY();}
		float getZ(){return position.getZ();}
		float getH(){return height;}
		
		void setX(float x){position.setX(x);}
		void setY(float y){position.setY(y);}
		void setZ(float z){position.setZ(z);}
		
		float getAngle(){return angle;}
		
		void setAngle(float angle){this->angle = angle;}
};

#endif