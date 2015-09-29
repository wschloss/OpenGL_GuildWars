// Vect object header file.
// Coded by: Zac McClain

//** Load Dependences:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./point.h"

#ifndef VECT_H
#define VECT_H

class Vect
{
	public:

	//** Public Default Constructors and Destructor:
		Vect();
		Vect( float newI, float newJ, float newK );
		Vect( Point a, Point b );
		~Vect();

	//** Operations:
		bool is_normalized();
		void calculate_magnitude();
		void normalize();

	//** Getters and Setters:

		//** Locations:

		// Getters:
		float getI();
		float getJ();
		float getK();
		float getMagnitude();

		// Setters:
		void setI( float newI );
		void setJ( float newJ );
		void setK( float newK );




	private:

	//** Variables:

		// Components:
		float i;
		float j; 
		float k;
		
		// Magnitude
		float magnitude;
};

#endif // VECT_H