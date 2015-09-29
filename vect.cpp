// Vect object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "./vect.h"

//** Public Default Constructors and Destructor.
Vect::Vect() {}

Vect::Vect( float newI, float newJ, float newK )
{
	i = newI;
	j = newJ;
	k = newK;
	calculate_magnitude();
}

// Direction is important here the is a vector from a -> b
Vect::Vect( Point a, Point b )
{
	i = ( b.getX() - a.getX() );
	j = ( b.getY() - a.getY() );
	k = ( b.getZ() - a.getZ() );

	calculate_magnitude();
}

Vect::~Vect() {}

//** Operations:
bool Vect::is_normalized() 
{
	if( magnitude == 1 ) {
		
		return( true );
	} else {
		return( false );
	}
}

void Vect::normalize()
{
	if( !(is_normalized()) ) {
		i = ( i / magnitude );
		j = ( j / magnitude );
		k = ( k / magnitude );
	}
}

void Vect::calculate_magnitude()
{
	magnitude = ( sqrt(pow(i, 2) + pow(j, 2) + pow(k, 2)) );
}

//** Getters and Setters:

// Locations:

// Getters:
float Vect::getI()
{
	return( i );
}

float Vect::getJ()
{
	return( j );
}

float Vect::getK()
{
	return( k );
}

float Vect::getMagnitude()
{
	return( magnitude );
}


// Setters:
void Vect::setI( float newI ){
	i = newI;
}

void Vect::setJ( float newJ ){
	j = newJ;
}

void Vect::setK( float newK ){
	k = newK;
}
