// Catamere charater source code.
// Coded by: Zac McClain

//** Load Dependences:  
#include "./castamere_castelli.h"

//** Public Default Constructors and Destructor.

CastamereCastelli::CastamereCastelli()
{
	// Set height
	height = 10;

  // Set final drawing scale
  scale = 3;

	// Setup the location:
	// default to the origin if no parameters are given.
	position = new Point( 0, (height/2), 0 );

	// set up body position:
	horizontal_look_angle = vertical_look_angle = 0;
	left_arm_angle = right_arm_angle = 0;
	setArmSwingCount( 0 );

	// Heading
	rotation_angle = 0;

	// Movement scale (speed)
    step = 0;
    stepSize = 2.5;
    is_moving = false;

    // Animation:
    eye_motion_count = 0;

	// Setup our Colors:
	skinColor = Color( 1, 0.79, 0.75 ); // pinkish
	eyeColor = Color( 0, 0, 0 ); // black
	hatColor = Color( 0.9, 0.2, 0 ); // red-ish
	beardColor = Color( 0.7, 0.7, 0.7 ); // gray
	shirtColor = Color( 0.3, 0.2, 1 ); // blue
	pantsColor = Color( 0.21, 0.16, 0.10 ); // brown

	// Make sure Castamere is up to date before we draw him.
	update();
}

// Clean up memory when Castamere is done existing.
CastamereCastelli::~CastamereCastelli()
{
	delete position;
	position = NULL;
}

//** Rendering

// General
void CastamereCastelli::renderSelf()
{
 
	// Draw the all of Castamere to his current position,
	// rotate him to his current heading and orient him with respect
	// to the surface he is standing on.
	glPushMatrix();
	{
	    glTranslatef( getX(), getY() + 2, getZ() );
	    glRotatef(
	    	orientation[1], 
	    	orientation[2], 
	    	orientation[3], 
	    	orientation[4]
	    );
	    glRotatef( (getRotationAngle() + 90), 0, 1, 0 );

      // Set the final scale
      glScalef(scale, scale, scale);
	    assembleSelf();
	};
  glPopMatrix();
}

void CastamereCastelli::update()
{
    if( step == 0 ) {
    	is_moving = false;
    } else {
    	is_moving = true;
    }
    if( is_moving ) {
    	swingArms();
    }
	setX( getX() + (step * xHeading) );
    setZ( getZ() + (step * zHeading) );

	calcHeading();
}

void CastamereCastelli::assembleSelf()
{
  // Draw the name tag
  // White Material, no shine
  Material mat(
    Color(1,1,1),
    Color(1,1,1),
    Color(1,1,1),
    0
  );
  mat.set_as_current_material();

  glPushMatrix(); {
    glTranslatef(-5, 8, 0);
    glScalef(0.01, 0.01, 0.01);
    string name = "Castamere Castelli";
    for (int i = 0; i < name.length(); i++) {
      glutStrokeCharacter(GLUT_STROKE_ROMAN, name.at(i));
    }
  } glPopMatrix();

  // Set a material for the rest for now
  Material matCoolPants = Material(Color(0.329412, 0.223529, 0.027451),
                          Color(0.780392, 0.568627, 0.113725),
                          Color(0.05, 0.05, 0.05),
                          0.005*128);
  matCoolPants.set_as_current_material();

	// draw the head
	glPushMatrix();
	{
	    glTranslatef( 0, 2.4, 0.4 );
	    renderHead();
	};
    glPopMatrix();

    // Draw the body
	glPushMatrix();
	{
	    glTranslatef( 0, 0, 0 );
	    renderBody();
	};
 	glPopMatrix();
}

void CastamereCastelli::renderJoint()
{
	glutSolidSphere( 1, 20, 20 );
}

// Head
void CastamereCastelli::renderHead()
{
	float head_hight = 1.4;
	float head_width = 1.2;
	float head_depth = 1;
	float primitive_rad = 1;

	// head
	glPushMatrix();
	{
		skinColor.set_as_current_color();
	    glScalef(  head_width, head_hight, head_depth );
	    glutSolidSphere( primitive_rad, 20, 20 );
	};
    glPopMatrix();

    // left eye
    glPushMatrix();
    {
    	glTranslatef( 
    		(head_width/2.2), 
    		(head_hight/3.8), 
    		(head_depth/1.4) 
    	);
    	glScalef( 0.8, 0.8, 0.8 );
    	glRotatef( horizontal_look_angle, 0, 1, 0 );
    	glRotatef( vertical_look_angle, 1, 0, 0 );
    	renderEye();
    };
    glPopMatrix();

    // right eye
    glPushMatrix();
	{
		glTranslatef( 
			-(head_width/2.2), 
			(head_hight/3.8), 
			(head_depth/1.4) 
		);
		glScalef( 0.8, 0.8, 0.8 );
		glRotatef( horizontal_look_angle, 0, 1, 0 );
    	glRotatef( vertical_look_angle, 1, 0, 0 );
		renderEye();
	};
    glPopMatrix();
    
    // hat
    glPushMatrix();
    {
    	renderHat();
    };
    glPopMatrix();

    // beard
    glPushMatrix();
    {
    	glTranslatef( 0, -0.15, 0.42 );
    	renderBeard();
    };
    glPopMatrix();

    // Nose
    glPushMatrix();
    {
    	glRotatef( -28, 1, 0, 0 );
    	glTranslatef( 0, 0.4, (head_depth-0.1) );
    	glScalef( 0.2, 0.2, 0.2 );
    	renderNose();
    };
    glPopMatrix();

    // left ear
    glPushMatrix();
    {
    	glTranslatef( -head_width, (head_hight/3.8), 0 );
    	glRotatef( -5, 0, 0, 1 );
    	glScalef( 0.35, 0.35, 0.35 );
    	renderEar();
    };
    glPopMatrix();

    // right ear
    glPushMatrix();
    {
    	glTranslatef( head_width, (head_hight/3.8), 0 );
    	glRotatef( -5, 0, 0, 1 );
    	glScalef( 0.35, 0.35, 0.35 );
    	renderEar();
    };
    glPopMatrix();
}

void CastamereCastelli::renderEye()
{
	// used so the size of the eye and the pupil are drawn relative
	// to one another.
	float eyeRadius = 0.5;

	// eye ball / eye whites
	glPushMatrix();
	{
		glColor3f( 1, 1, 1 ); // white
	    glutSolidSphere( eyeRadius, 20, 20 );
	};
	glPopMatrix();

	// pupil
	glPushMatrix();
	{
		glColor3f( 0, 0, 0 ); // black
		glTranslatef( 0, 0, (eyeRadius-0.03) );
		glScalef( 2, 2, 1 );
	    glutSolidSphere( 0.1, 20, 20 );
	};
	glPopMatrix();
}

void CastamereCastelli::renderHat()
{
	hatColor.set_as_current_color();

	glPushMatrix();
	{
		glRotatef( -90, 1, 0, 0 );
		glTranslatef( 0, 0, 1 );
		glutSolidCone( 0.8, 2.2, 20, 20 );
	};
	glPopMatrix();

	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	float brim_hight = 0.30;
	float birm_rad = 1.25;
	float hat_res = 20;

	glPushMatrix();
	{
		glTranslatef( 0, 1.15, 0 );
		glPushMatrix();
		{
			glRotatef( 90, 1, 0, 0 );
			gluCylinder( 
				myQuad, 
				(birm_rad - 0.2), 
				birm_rad, 
				brim_hight, 
				hat_res, 
				hat_res 
			);
		};
		glPopMatrix();

		// close upper rim
		glPushMatrix();
		{
			glRotatef( 90, 1, 0, 0 );
			gluDisk( myQuad, 0, (birm_rad - 0.2), hat_res, hat_res );
		};
		glPopMatrix();

		// close lower rim
		glPushMatrix();
		{
			glRotatef( 90, 1, 0, 0 );
			glTranslatef( 0, 0, brim_hight );
			gluDisk( myQuad, 0, birm_rad, hat_res, hat_res );
		};
		glPopMatrix();
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderBeard()
{
	beardColor.set_as_current_color();

	// Lower beard
	glPushMatrix();
	{
		glRotatef( 90, 1, 0, 0 );
		glScalef( 1.25, 0.7, 2 );
		glutSolidCone( 1, 1, 20, 20 );
	};
	glPopMatrix();

	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	// Top part
	glPushMatrix();
	{
		glRotatef( 90, 1, 0, 0 );
		glScalef( 1.25, 0.7, 2 );
		glTranslatef( 0, 0, -0.2 );
		gluCylinder( myQuad, 0.6, 1, 0.2, 20, 20 );
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderNose()
{
	skinColor.set_as_current_color();
	
	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	glPushMatrix();
	{
		glRotatef( 90, 1, 0, 0 );
		gluCylinder( myQuad, 1, 0.8, 5, 20, 20 );
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );

	glPushMatrix();
	{
		glTranslatef( 0, -5, 0 );
		glScalef( 1.2, 1, 1.2 );
	    glutSolidSphere( 1, 20, 20 );
	};
	glPopMatrix();
}

void CastamereCastelli::renderEar()
{
	glPushMatrix();
	{
		glScalef( 1, 1.4, 0.4 );
	    glutSolidSphere( 1, 20, 20 );
	};
	glPopMatrix();
}

// Body
void CastamereCastelli::renderBody()
{
	// Neck
    glPushMatrix();
    {
    	glTranslatef( 0, 1.6, 0.2 );
    	glScalef( 0.7, 1, 0.6 );
    	glRotatef( 90, 1, 0, 0 );
    	renderNeck();
    };
    glPopMatrix();

	// Upper body
    glPushMatrix();
    {
    	glTranslatef( 0, 1, 0 );
    	renderUpperBody();
    };
    glPopMatrix();

    // Lower body
    glPushMatrix();
    {
    	glRotatef( -90, 1, 0, 0 );
    	glTranslatef( 0, 0, -2.36 );
    	renderLowerBody();
    };
    glPopMatrix();
}

// Upper body
void CastamereCastelli::renderUpperBody()
{
	// Torso
    glPushMatrix();
    {
    	glScalef( 1.6, 1.6, 0.7 );
    	glRotatef( 90, 1, 0, 0 );
    	renderTorso();
    };
    glPopMatrix();
    
    // left shoulder
    glPushMatrix();
    {
    	glTranslatef( -1.6, 0, 0 );
    	glScalef( 0.7, 0.7, 0.7 );
    	renderJoint();
    };
    glPopMatrix();

    // right shoulder
    glPushMatrix();
    {
    	glTranslatef( 1.6, 0, 0 );
    	glScalef( 0.7, 0.7, 0.7 );
    	renderJoint();
    };
    glPopMatrix();

    // left arm
    glPushMatrix();
    {
    	glRotatef( left_arm_angle, 1, 0, 0 );
	    glPushMatrix();
	    {
	    	glTranslatef( -1.6, 0, 0 );
	    	glRotatef( -22, 0, 0, 1 );
	    	renderArm();
	    };
	    glPopMatrix();
	};
	glPopMatrix();

    // right arm
    glPushMatrix();
    {
    	glRotatef( right_arm_angle, 1, 0, 0 );
	    glPushMatrix();
	    {
	    	glTranslatef( 1.6, 0, 0 );
	    	glRotatef( 22, 0, 0, 1 );
	    	renderArm();
	    };
	    glPopMatrix();
	};
	glPopMatrix();
}

void CastamereCastelli::renderNeck()
{
	skinColor.set_as_current_color();

	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	glPushMatrix();
	{
		gluCylinder( myQuad, 1, 1, 1, 20, 20 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		gluDisk( myQuad, 0, 1, 20, 20 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( 0, 0, 1 );
		gluDisk( myQuad, 0, 1, 20, 20 );
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderTorso()
{
	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	shirtColor.set_as_current_color();

	glPushMatrix();
	{
		gluCylinder( myQuad, 1.2, 0.8, 1.4, 20, 20 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		gluDisk( myQuad, 0, 1.2, 20, 20 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( 0, 0, 1.4 );
		gluDisk( myQuad, 0, 0.8, 20, 20 );
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

// Arms
void CastamereCastelli::renderArm()
{
	// Biceps
	glPushMatrix();
	{
		renderBiceps();	
	};
	glPopMatrix();
}

void CastamereCastelli::renderBiceps()
{
	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	shirtColor.set_as_current_color();

	// Biceps
	glPushMatrix();
	{
		glRotatef( 90, 1, 0, 0 );
		gluCylinder( myQuad, 0.6, 0.4, 1.6, 20, 20 );
	};
	glPopMatrix();

	// Elbow
    glPushMatrix();
    {
    	glTranslatef( 0, -1.6, 0 );
    	glScalef( 0.5, 0.5, 0.5 );
    	renderJoint();
    };
    glPopMatrix();

    // Forearm
	glPushMatrix();
	{
		glTranslatef( 0, -1.6, 0 );
		glRotatef( 45, 1, 0, 0 );
		renderForarm();	
	};
	glPopMatrix();

    gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderForarm()
{
	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	// Forearm 
	glPushMatrix();
	{	
		gluCylinder( myQuad, 0.4, 0.35, 1.45, 20, 20 );
	};
	glPopMatrix();

	// Hand
	glPushMatrix();
	{
		glTranslatef( 0, 0, 1.45 );
		renderHand();	
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderHand()
{
	skinColor.set_as_current_color();
	// hand
    glPushMatrix();
    {
    	glScalef( 0.5, 0.5, 0.5 );
    	renderJoint();
    };
    glPopMatrix();
}

// Lower body
void CastamereCastelli::renderLowerBody()
{
	pantsColor.set_as_current_color();

	glPushMatrix();
	{
		glScalef( 1.6, 0.7, 1.6 );
		renderPelvis();
	};
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( 0, 0, -0.1 );
		renderHips();
	};
	glPopMatrix();

	// Left leg
	glPushMatrix();
	{
		glTranslatef( -0.7, 0, 0.1 );
		glRotatef( 90, 1, 0, 0 );
		glRotatef( -5, 0, 0, 1 );
		renderLeg();
	};
	glPopMatrix();

	// Right leg
	glPushMatrix();
	{
		glTranslatef( 0.7, 0, 0.1 );
		glRotatef( 90, 1, 0, 0 );
		glRotatef( 5, 0, 0, 1 );
		renderLeg();
	};
	glPopMatrix();
}

void CastamereCastelli::renderPelvis()
{
	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	pantsColor.set_as_current_color();

	glPushMatrix();
	{
		glRotatef( 180, 1, 0, 0 );
		glTranslatef( 0, 0, -0.4 );
		gluCylinder( myQuad, 1, 0.3, 0.5, 20, 20 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( 0, 0, 0.4 );
		gluCylinder( myQuad, 1, 0.8, 0.3, 20, 20 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( 0, 0, -0.1 );
		gluDisk( myQuad, 0, 0.3, 20, 20 );
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderHips()
{
	// left hip
	glPushMatrix();
	{
		glTranslatef( -0.7, 0, 0.3 );
		glScalef( 0.7, 0.7, 0.7 );
		renderJoint();
	};
	glPopMatrix();

	// right hip
	glPushMatrix();
	{
		glTranslatef( 0.7, 0, 0.3 );
		glScalef( 0.7, 0.7, 0.7 );
		renderJoint();
	};
	glPopMatrix();
}

// Legs
void CastamereCastelli::renderLeg()
{
	glPushMatrix();
	{
		renderThigh();
	};
	glPopMatrix();
}

void CastamereCastelli::renderThigh()
{
	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	// Thigh
	glPushMatrix();
	{
		glRotatef( 90, 1, 0, 0 );
		gluCylinder( myQuad, 0.7, 0.5, 1, 20, 20 );
	};
	glPopMatrix();

	// Knee
    glPushMatrix();
    {
    	glTranslatef( 0, -1, 0 );
    	glScalef( 0.6, 0.6, 0.6 );
    	renderJoint();
    };
    glPopMatrix();

    // Calf
	glPushMatrix();
	{
		glTranslatef( 0, -1, 0 );
		glRotatef( 90, 1, 0, 0 );
		renderCalf();	
	};
	glPopMatrix();

    gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderCalf()
{
	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	// Calf 
	glPushMatrix();
	{	
		gluCylinder( myQuad, 0.6, 0.48, 0.8, 20, 20 );
	};
	glPopMatrix();

	// ankle
	glPushMatrix();
	{
		glTranslatef( 0, 0, 1 );
		glScalef( 0.5, 0.5, 0.5 );
		renderJoint();
	};
	glPopMatrix();

	// foot
	glPushMatrix();
	{
		glTranslatef( 0, 0.2, 1.2 );
		renderFoot();	
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

void CastamereCastelli::renderFoot() 
{
	glPushMatrix();
	{
		glScalef( 0.5, 0.8, 0.4 );
		renderJoint();
	};
	glPopMatrix();
}

//** Keyboard:
void CastamereCastelli::respondKeyDown( unsigned char key )
{
	if( key == 'w' ) {
    	moveForward();
	}
  	if( key == 's' ) {
    	moveBackward();
  	}
  	if( key == 'a' ) {
    	ternLeft();
  	}
  	if( key == 'd' ) {
    	ternRight();
  	}
}

void CastamereCastelli::respondKeyUp( unsigned char key )
{
	if (step != 0 && (key == 'w' || key == 's')){
    	step = 0;
	}
}

//** Movement

void CastamereCastelli::moveForward()
{
	step = stepSize;
}

void CastamereCastelli::moveBackward()
{
	step = -stepSize;
}

void CastamereCastelli::ternLeft()
{
	rotation_angle += 90;
}

void CastamereCastelli::ternRight()
{
	rotation_angle -= 90;
}

void CastamereCastelli::calcHeading()
{
	xHeading = cos( rotation_angle * M_PI/180 );
    zHeading = -sin( rotation_angle * M_PI/180 );
}

// Animations

void CastamereCastelli::stepForward()
{}

void CastamereCastelli::stepBackward()
{}

void CastamereCastelli::swingArms()
{
	if( ((arm_swing_count < 9) && (arm_swing_count > 0)) ) {
		left_arm_angle += 10;
		right_arm_angle -= 10;
		arm_swing_count++;
	} else if( ((arm_swing_count < 18) && (arm_swing_count > 9)) ) {
		left_arm_angle -= 10;
		right_arm_angle += 10;
		arm_swing_count++;
	} else {
		arm_swing_count = 0;
	}
}

void CastamereCastelli::lookBackAndForth()
{
	if( (eye_motion_count > 0) && (eye_motion_count < 6) ) {
		horizontal_look_angle += 5;
		eye_motion_count++;
	} else if( (eye_motion_count > 6) && (eye_motion_count < 12) ) {
		horizontal_look_angle -= 5;
		eye_motion_count++;
	} else {
		eye_motion_count = 0;
	}
}

//** Getters and Setters

// Locations

// Getters
Point* CastamereCastelli::getPosition(){
	return( position );
}

float CastamereCastelli::getX()
{
	return( position->getX() );
}

float CastamereCastelli::getY()
{
	return( position->getY() );
}
float CastamereCastelli::getZ()
{
	return( position->getZ() );
}

float CastamereCastelli::getRotationAngle()
{
	return( rotation_angle );
}

// Setters
void CastamereCastelli::setX( float newX ){
  // Clamp to the surface [-600,600] plus a small correction
	position->setX( fmax(-590, fmin(590,newX)) );
}

void CastamereCastelli::setY( float newY )
{
	position->setY( newY );
}

void CastamereCastelli::setZ( float newZ )
{
  // Clamp to the surface [-600,600]
	position->setZ( fmax(-590, fmin(590,newZ)) );
}

float CastamereCastelli::getHeight()
{
	return( height );
}

// Animations:

// Getters:
float CastamereCastelli::getArmSwingCount()
{
	return( arm_swing_count );
}

// Setters:
void CastamereCastelli::setArmSwingCount( float newArmSwingCount )
{
	arm_swing_count = newArmSwingCount;
}

// Colors:

// Getters:
Color CastamereCastelli::getSkinColor()
{
	return( skinColor );
}

Color CastamereCastelli::getEyeColor()
{
	return( eyeColor );
}

Color CastamereCastelli::getHatColor()
{
	return( hatColor );
}

Color CastamereCastelli::getShirtColor()
{
	return( shirtColor );
}

Color CastamereCastelli::getPantsColor()
{
	return( pantsColor );
}

// Setters:
void CastamereCastelli::setSkinColor( Color newSkinColor )
{
	skinColor = newSkinColor;
}

void CastamereCastelli::setEyeColor( Color newEyeColor )
{
	eyeColor = newEyeColor;
}

void CastamereCastelli::setHairColor( Color newHatColor )
{
	hatColor = newHatColor;
}

void CastamereCastelli::setShirtColor( Color newShirtColor )
{
	shirtColor = newShirtColor;
}

void CastamereCastelli::setPantsColor( Color newPantsColor )
{
	pantsColor = newPantsColor;
}

// Cache the orientation to cut down number of calls
void CastamereCastelli::setOrientation( BezierPatch* surface )
{
  this->orientation = surface->orient( getX(), getZ() );
  this->setY( orientation[0] + scale*(getHeight()/2) );
}

/// END CastamereCastelli
