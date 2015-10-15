// Castamere character header file.
// Coded by: Zac McClain

#ifndef CASTAMERECASTELLI_H
#define CASTAMERECASTELLI_H

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

#include <GL/glui.h>        // include GLUI header

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Point.h"
#include "Material.h"
#include "BezierPatch.h"
#include "Color.h"

class CastamereCastelli
{
	public:

	//** Public Default Constructors and Destructor:
		CastamereCastelli();
		~CastamereCastelli();

	//** Rendering:

		// render a 3D CastamereCastelli character.
		void draw();
    // re-redraw self.
		void update();

	//** Keyboard:
    	void respondKeyDown(unsigned char key);
    	void respondKeyUp(unsigned char key);

	//** Mouse:
		// nothing for now.

	//** Getters and Setters:

		// Locations:

		// Getters:
		Point* getPosition();
		float getX();
		float getY();
		float getZ();
		float getRotationAngle();
		float getHeight();
    	void setOrientation( BezierPatch* surface );

		// Setters:
		void setX( float newX );
		void setY( float newY );
		void setZ( float newZ );

		// Animations:

		// Getters:
		float getArmSwingCount();

		// Setters:
		void setArmSwingCount( float newArmSwingCount );

		// Colors:

		// Getters:
		Color getSkinColor();
		Color getEyeColor();
		Color getHatColor();
		Color getShirtColor();
		Color getPantsColor();
		
		// get y component of orientation
		vector<float> getOrientation(){ return orientation; }

		// Setters:
		void setSkinColor( Color newSkinColor );
		void setEyeColor( Color newEyeColor );
		void setHairColor( Color newHatColor );
		void setShirtColor( Color newShirtColor );
		void setPantsColor( Color newPantsColor );

		// Getters:
		float getStepSize();
		
		// Setters:
		void setStepSize();


	private:


	//** Variables

		// Location:
		Point* position; 
		
		// bool array for keys
		bool key[128];

		// Orientation:
		float xHeading, zHeading;
		float height;
		float rotation_angle, alt_rot;

	    // Surface orientation:
	    vector<float> orientation;

	    // Scale for drawing
	    float scale;

		// Body position:
		float horizontal_look_angle, vertical_look_angle;
		float left_arm_angle, right_arm_angle;

		// Colors:
		Color skinColor, eyeColor, hatColor;
		Color shirtColor, pantsColor, beardColor;

		// Materials:
		Material skinMat, eyeMat, hatMat;
		Material shirtMat, pantsMat, hairMat;
		Material shoesMat;

		// Movement:
		float step;
		float stepSize;
		bool is_moving;
		int arm_swing_count;

		// Animation:
		int eye_motion_count;


	//** Functions:

		// Setup:
		void setupPointers();

		// Movement:
		void moveForward();
		void moveBackward();
		void ternLeft();
		void ternRight();
		void calcHeading();

		// Animations:
		void stepForward();
		void stepBackward();
		void swingArms();
		void lookBackAndForth();

		// Rendering:

		// General
		void assembleSelf();
		void renderJoint();
		// Head
		void renderHead();
		void renderEye();
		void renderHat();
		void renderBeard();
		void renderNose();
		void renderEar();
		// Body
		void renderBody();
		// Upper body
		void renderNeck();
		void renderUpperBody();
		void renderTorso();
		// Arms
		void renderArm();
		void renderBiceps();
		void renderForarm();
		void renderHand();
		// Lower body
		void renderLowerBody();
		void renderPelvis();
		void renderHips();
		// Legs
		void renderLeg();
		void renderThigh();
		void renderCalf();
		void renderFoot();


}; ///*** END CastamereCastelli

#endif // CASTAMERECASTELLI_H
