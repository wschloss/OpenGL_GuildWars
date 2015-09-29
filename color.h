// Color object header file.
// Coded by: Zac McClain

#ifndef COLOR_H
#define COLOR_H

//** Load Dependences:
#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					    // else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

class Color
{
	public:

	//** Public Default Constructors and Destructor:
		Color();
		Color( float initRed, float initGreen, float initBlue );
		~Color();

	//** Helper Methods:

		void set_as_current_color();

	//** Getters and Setters:

		// Getters:
		float get_red();
		float get_green();
		float get_blue();

		// Setters:
		void set_red( float newRed );
		void set_green( float newGreen );
		void set_blue( float newBlue );


	private:

	//** Variables:
		float red;
		float green;
		float blue;
		
};

#endif // COLOR_H