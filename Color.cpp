// Color Object source code
// Coded by: Zac McClain

//** Load Dependences:
#include "./Color.h"

//** Public Default Constructors and Destructor

Color::Color()
{
	// default to white
	red = 1;
	green = 1;
	blue = 1;
}

Color::Color( float initRed, float initGreen, float initBlue ){
  // Set and clamp to range
	red = fmax(0, fmin(1, initRed));
	green = fmax(0, fmin(1, initGreen));
  blue = fmax(0, fmin(1, initBlue));
}

Color::~Color() {}

//** Helper methods:

void Color::set_as_current_color() 
{
	glColor3f( red, green, blue );
}

//** Getters and Setters:

//** Locations:

// Getters:
float Color::get_red()
{
	return( red );
}
		
float Color::get_green(){
	return( green );
}

float Color::get_blue()
{
	return( blue );
}

// Setters:
void Color::set_red( float newRed )
{
	red = fmax(0, fmin(1, newRed));
}

void Color::set_green( float newGreen )
{
	green = fmax(0, fmin(1, newGreen));
}

void Color::set_blue( float newBlue )
{
	blue = fmax(0, fmin(1, newBlue));
}

