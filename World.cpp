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

	configure();
}

void World::configure()
{
	campfire.setOrientation( surface );
}

void World::drawForest()
{
  Tree tree;

  tree.setX( 50 );
  tree.setZ( 50 );
  tree.setOrientation( getSurface() );
  tree.draw();

  tree.setX( -50 );
  tree.setZ( 50 );
  tree.setOrientation( getSurface() );
  tree.draw();

  tree.setType( Tree::BUSH );
  tree.setX( -50 );
  tree.setZ( -50 );
  tree.setOrientation( getSurface() );
  tree.draw();
	// for( int i = 0; i < tree_count; i++ ) {
	// 	if( (i % 2) == 0 ) {
	// 		pinTree.setX( i );
	// 		pinTree.setY( i );
	// 		pinTree.draw();
	// 	} else {
	// 		bush.setX( i );
	// 		bush.setY( i );
	// 		bush.draw();
	// 	}
	// }
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
