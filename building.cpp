// Building object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "./building.h"

//** Public Default Constructors and Destructor.
Building::Building()
{
	postion = new Point( 0, 0, 0 );
}

Building::Building( float x, float y, float z )
{
	postion = new Point( x, y, z );
}

Building::~Building()
{
	delete postion;
	postion = NULL;
}

//** Rendering:

// Render a 3D Tree object
void Building::renderSelf(){}

//** Getters and Setters:

// Locations:

// Getters:
Point* Building::getPostion(){
	return( postion );
}

float Building::getX()
{
	return( postion->getX() );
}

float Building::getY()
{
	return( postion->getY() );
}
float Building::getZ()
{
	return( postion->getZ() );
}

// Setters:
void Building::setPostion( Point* newPostion ){
	delete postion;
	postion = newPostion;
}

void Building::setX( float newX ){
	postion->setX( newX );
}

void Building::setY( float newY ){
	postion->setY( newY );
}

void Building::setZ( float newZ ){
	postion->setZ( newZ );
}
