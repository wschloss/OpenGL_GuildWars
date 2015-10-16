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
#include "BezierCurve.h"
#include "BezierPatch.h"
#include "WorldLoader.h"
#include "Campfire.h"
#include "Light.h"
#include "Tree.h"
#include "Building.h"

using namespace std;

class World
{
	public:

		//** Public Default Constructors and Destructor:
		World();
		~World();

		// Configuration
		void loadWorld( char* world_file_name );
		void configure();

		// Rendering
		void draw();
		void drawForest();

		// Getters:
		BezierPatch* getSurface();
		BezierCurve* getPath();
		Campfire* getCompfire();

		// Setters:
		void setSurface( BezierPatch* newSurface );



	private:

	//** Variables:

		int tree_count, building_count;
		float xBound, zBound;
		bool is_configured;

		//** Surface:

		// Instance:
		BezierPatch* surface;
		BezierCurve* path;

		//** Objects:

		// FileIO:
		WorldLoader loader;

		// Campfire, draws and also flickers a light
		Campfire campfire;
		Tree pinTree;
		Tree bush;

	//** Functions:
		float getRand();

};

#endif // TREE_H