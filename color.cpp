// Color Object source code
// Coded by: Zac McClain

//** Load Dependences:
#include "./color.h"

//** Public Default Constructors and Destructor

Color::Color()
{
	// default to white
	red = 0;
	green = 0;
	blue = 0;
}

Color::Color( float initRed, float initGreen, float initBlue ){
	red = initRed;
	green = initGreen;
	blue = initBlue;
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
	red = newRed;
}

void Color::set_green( float newGreen )
{
	green = newGreen;
}

void Color::set_blue( float newBlue )
{
	blue = newBlue;
}

