// Mouse object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "./mouse.h"

//** Public Default Constructors and Destructor:
Mouse::Mouse(){
	myX = 0;
	myY = 0;
}

Mouse::~Mouse(){}

//** Getters and Setters:

// State:

// Getters:
GLint Mouse::getLeftMouseButton()
{
	return( leftMouseButton );
}

// Setters:
void Mouse::setLeftMouseButton( GLint newLeftMouseButton )
{
	leftMouseButton = newLeftMouseButton;
}

//** Locations:

// Getters:
float Mouse::getX()
{
	return( myX );
}

float Mouse::getY()
{
	return( myY );
}

// Setters
void Mouse::setX( float newX )
{
	myX = newX;
}

void Mouse::setY( float newY )
{
	myY = newY;
}
