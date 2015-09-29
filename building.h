// Building object header file.
// Coded by: Zac McClain

#ifndef BUILDING_H
#define BUILDING_H

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					    // else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./Point.h"

class Building
{
	public:

	//** Public Default Constructors and Destructor:
		Building();
		Building( float x, float y, float z );
		~Building();

	//** Rendering:

		// render a 3D Tree object
		void renderSelf();

	//** Getters and Setters:

		//** Locations:

		// Getters:
		Point* getPostion();
		float getX();
		float getY();
		float getZ();

		// Setters:
		void setPostion( Point* newPostion );
		void setX( float newX );
		void setY( float newY );
		void setZ( float newZ );

	private:

	//** Variables:

		// Location:
		Point* postion;
};

#endif // BUILDING_H