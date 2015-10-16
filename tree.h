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
#include <iostream>
#include <math.h>
#include "BezierPatch.h"
#include "Point.h"
#include "Material.h"

using namespace std;


class Tree
{
	public:
	//** Enumerated types
		enum Type { PINE, DECIDUOUS, BUSH };

	//** Public Default Constructors and Destructor:
		Tree();
		~Tree();

	//** Rendering:

		// render a 3D Tree object
		void draw();
		void renderSelf();

	//** Getters and Setters:

		//** Locations:

		// Getters:
		Point* getPostion();
		float getX();
		float getY();
		float getZ();
		float getHeight();
		float getWidth();
		Tree::Type getType();
		Tree* self();

		// Setters:
		void setPostion( Point* newPostion );
		void setX( float newX );
		void setY( float newY );
		void setZ( float newZ );
		void setType( Tree::Type newType );
		void setOrientation( BezierPatch* surface );
		void setHight( float newHeight );
		void setWidth( float newWidth );

	private:

	//** Variables:

		// Location:
		Point* postion;
		float height, width;

		// Typing:
		Type type;

		// Scale for drawing
	    float scale;

		// Materials:
		Material barkMat, leafMat;

		// Surface orientation:
	    vector<float> orientation;

	//** Functions:

		// set up:
		void setup();

		// Rendering:
		void assembleBush();
		void assemblePineTree();
		void assembleDeciduousTree();
		void renderTrunk();
		void renderCone();
		void renderPineLevel( float radus );
		void renderBranch( float length );
		void renderMidBranch( float lenght );
		void renderEndBranch( float lenght );
		void renderLeaf( float lenght );
};

#endif // TREE_H