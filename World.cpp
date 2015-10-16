// Vect object header file.
// Coded by: Zac McClain

//** Load Dependences:
#include "World.h"

World::World()
{
	// FileIO:
	WorldLoader loader;
	// Boolean to that will restricted functionality until
	is_configured = false;
}

World::~World()
{
	// delete surface;
	// surface = NULL;
}

void World::draw()
{}

void World::loadWorld( char* world_file_name )
{
	loader.loadWorldComponentFilenames( world_file_name );
	
	surface = loader.constructSurface();
	path = loader.constructCurve();
	treeLocations = loader.constructTreePoints();

	configure();
}

void World::configure()
{
	tree_count = treeLocations.size();
	campfire.setOrientation( surface );
}

void World::drawForest()
{
	for( int i = 0; i < tree_count; i++ ) {
		float x = treeLocations[i].getX();
		float z = treeLocations[i].getZ();
		if( (i % 2) == 0 ) {
			tree.setType( Tree::BUSH );
		} else {
			tree.setType( Tree::PINE );
		}
		tree.setX( x );
		tree.setZ( z );
		tree.setOrientation( getSurface() );
  		tree.draw();
	}
}

//  Simple helper function to return a random number between 0.0f and 1.0f.
float World::getRand() {
   	return rand() / (float)RAND_MAX;
}

// Getters:
BezierPatch* World::getSurface()
{
	return( surface );
}

Campfire* World::getCompfire()
{
	return( campfire.self() );
}

BezierCurve* World::getPath()
{
	return( path );
}

// Setters:
void World::setSurface( BezierPatch* newSurface )
{
	surface = newSurface;
}
