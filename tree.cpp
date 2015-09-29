// Tree object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "./tree.h"


//** Public Default Constructors and Destructor.
Tree::Tree()
{
	postion = new Point( 0, 0, 0 );
}

Tree::Tree( float x, float y, float z )
{
	postion = new Point( x, y, z );
}

Tree::~Tree()
{
	delete postion;
	postion = NULL;
}

//** Rendering:

// Render a 3D Tree object
void Tree::renderSelf(){}

//** Getters and Setters:

// Locations:

// Getters:
Point* Tree::getPostion(){
	return( postion );
}

float Tree::getX()
{
	return( postion->getX() );
}

float Tree::getY()
{
	return( postion->getY() );
}
float Tree::getZ()
{
	return( postion->getZ() );
}

// Setters:
void Tree::setPostion( Point* newPostion ){
	delete postion;
	postion = newPostion;
}

void Tree::setX( float newX ){
	postion->setX( newX );
}

void Tree::setY( float newY ){
	postion->setY( newY );
}

void Tree::setZ( float newZ ){
	postion->setZ( newZ );
}
