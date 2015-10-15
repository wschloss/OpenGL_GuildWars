// Tree object header file.
// Coded by: Zac McClain

#ifndef WORLD_H
#define WORLD_H

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
#include "Point.h"
#include "Material.h"
#include "WorldLoader.h"
#include "Campfire.h"
#include "Light.h"
#include "Tree.h"
#include "Building.h"
#include "BezierPatch.h"

using namespace std;

class World
{
	public:

		//** Public Default Constructors and Destructor:
		World( float xBound, float zBound );
		~World();

		// Getters:
		BezierPatch* getSurface();

		// Setters:
		void setSurface( BezierPatch* newSurface );

		void drawForest();

	private:

	//** Variables:

		int tree_count, building_count;
		float xBound, zBound;

		//** Surface:

		// Instance:
		BezierPatch* surface;

		//** Objects:

		// Campfire, draws and also flickers a light
		Campfire campfire;
		Tree pinTree;
		Tree bush;

	//** Functions:
		float getRand();

};

#endif // TREE_H