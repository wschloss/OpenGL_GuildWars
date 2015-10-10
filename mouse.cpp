// Mouse object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "./mouse.h"

//** Public Default Constructors and Destructor:
Mouse::Mouse(){
	myX = 0;
	myY = 0;
	zoomMode = false;
}

Mouse::~Mouse() {}

//** Getters and Setters:

// State:

// Getters:
GLint Mouse::getLeftMouseButton()
{
	return( leftMouseButton );
}

bool Mouse::getZoomMode()
{
	return( zoomMode );
}

// Setters:
void Mouse::setLeftMouseButton( GLint newLeftMouseButton )
{
	leftMouseButton = newLeftMouseButton;
}

void Mouse::setZoomMode( bool newZoomMode )
{
	zoomMode = newZoomMode;
}

void Mouse::toggleZoomMode()
{
	zoomMode = !zoomMode;
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
