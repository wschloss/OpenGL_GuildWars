// Vect object header file.
// Coded by: Zac McClain

//** Load Dependences:
#include "World.h"

World::World( float xBound, float zBound )
{
	this->xBound = xBound;
	this->zBound = zBound;

	// Surface instance
	surface = new BezierPatch();	

	// Campfire, draws and also flickers a light
	Campfire campfire;
}

World::~World()
{
	delete surface;
	surface = NULL;
}

void World::drawForest()
{
	for( int i = 0; i < tree_count; i++ ) {
		if( (i % 2) == 0 ) {
			pinTree.setX( i );
			pinTree.setY( i );
			pinTree.draw();
		} else {
			bush.setX( i );
			bush.setY( i );
			bush.draw();
		}
	}
}

// Getters:
BezierPatch* World::getSurface()
{
	return( surface );
}

//  Simple helper function to return a random number between 0.0f and 1.0f.
float World::getRand() {
   	return rand() / (float)RAND_MAX;
}

// Setters:
void World::setSurface( BezierPatch* newSurface )
{
	surface = newSurface;
}
