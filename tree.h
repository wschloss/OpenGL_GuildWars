// Tree object header file.
// Coded by: Zac McClain

#ifndef TREE_H
#define TREE_H

//** Load Dependences:
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

class Tree
{
	public:

	//** Public Default Constructors and Destructor:
		Tree();
		Tree( float x, float y, float z );
		~Tree();

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

#endif // TREE_H
