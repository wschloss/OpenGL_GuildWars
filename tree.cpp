// Tree object source code.
// Coded by: Zac McClain

//** Load Dependences:
#include "Tree.h"

// set temp branch threshold
float branch_threshold = 20;
float branch_deflection = 30;
float branch_rot = 20;

Tree::Tree()
{
	bool failed = false;
	type = PINE;
	postion = new Point( 0, 0, 0 );

	setup();
}

Tree::~Tree()
{
	delete postion;
	postion = NULL;
}

void Tree::setup()
{
	// Tree scale
	scale = 1;

	// Materials:
	barkMat = Material(
		Color( 0.21, 0.16, 0.10 ),
		Color( 0.21, 0.16, 0.10 ),
		Color( 0.21, 0.16, 0.10 ),
		51.2
	);

	leafMat = Material(
		Color( 0, 1, 0 ),
		Color( 0, 1, 0 ),
		Color( 0, 1, 0 ),
		51.2
	);

	switch( type ){
		case PINE:
			width = 30;
			height = 100;
			break;
		case BUSH:
			width = 20;
			height = 50;
			break;
	}
}

//** Rendering:
void Tree::draw()
{
	renderSelf();
}

// Render a 3D Tree object
void Tree::renderSelf()
{
	glPushMatrix();
	{
	    glTranslatef( getX(), getY(), getZ() );
	    glScalef( scale, scale, scale );
	    glRotatef( 90, 0, 1, 0 );

		switch( type ) {
		case PINE:
			assemblePineTree();
			break;
		case DECIDUOUS:
			assembleDeciduousTree();
			break;
		case BUSH:
			assembleBush();
			break;
		}
	};
    glPopMatrix();
}

void Tree::assembleBush()
{
	// create the trunk
	renderTrunk();

	leafMat.set_as_current_material();
	glPushMatrix();
	{
		glTranslatef( 0, (height/1.65), 0 );
		glScalef( 0.75, 1.1, 0.75 );
		glutSolidSphere( (width/1.2), 20, 20 );
	};
	glPopMatrix();

}

void Tree::assemblePineTree()
{
	// create the trunk
	renderTrunk();

	leafMat.set_as_current_material();

	// make the top of the pine tree
	glPushMatrix();
	{
		glTranslatef( 0, (height-1), 0 );
		glRotatef( -90, 1, 0, 0 );
		glutSolidCone( (width/3.8), (height/8), 20, 20 );
	};
	glPopMatrix();

	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	// close bottom of top cone
	glPushMatrix();
	{
		glTranslatef( 0, (height-1), 0 );
		glRotatef( 90, 1, 0, 0 );
		gluDisk( myQuad, 0, (width/4), 20, 20 );
	};
	glPopMatrix();

	// we are done with the myQuad object.
	gluDeleteQuadric( myQuad );

	// render the bottom level
	glPushMatrix();
	{
		glTranslatef( 0, (height/3), 0 );
		renderPineLevel( width );
	};
	glPopMatrix();

	// 2nd form bottom
	glPushMatrix();
	{
		glTranslatef( 0, (height/2), 0 );
		renderPineLevel( width/1.28 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( 0, (height/1.48), 0 );
		renderPineLevel( width/1.68 );
	};
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef( 0, (height/1.2), 0 );
		renderPineLevel( width/2.16 );
	};
	glPopMatrix();

	// next to top code
	glPushMatrix();
	{
		glTranslatef( 0, (height - 3), 0 );
		renderPineLevel( width/2.68 );
	};
	glPopMatrix();
	
}

void Tree::assembleDeciduousTree()
{
	renderTrunk();
}
		
void Tree::renderTrunk()
{
	barkMat.set_as_current_material();

	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	float trunk_radus = ( width/4 );

	glPushMatrix();
	{
		glRotatef( -90, 1, 0, 0 );
		gluCylinder( myQuad, trunk_radus, 0, height, 20, 20 );
	};
	glPopMatrix();

	// close lower
	glPushMatrix();
	{
		glRotatef( 90, 1, 0, 0 );
		gluDisk( myQuad, 0, trunk_radus, 20, 20 );
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}
		
void Tree::renderPineLevel( float radus )
{
	leafMat.set_as_current_material();

	GLUquadricObj *myQuad = gluNewQuadric();
	gluQuadricDrawStyle( myQuad, GLU_FILL );

	float res = 20;
	float upper_radus = ( radus/1.2 );
	float section_height = ( height/8.2 );

	glPushMatrix();
	{
		glRotatef( 90, 1, 0, 0 );
		glPushMatrix();
		{
			gluCylinder( 
				myQuad, 
				upper_radus, 
				radus, 
				section_height, 
				res, 
				res 
			);
		};
		glPopMatrix();

		// close upper
		glPushMatrix();
		{
			glRotatef( 180, 1, 0, 0 );
			gluDisk( myQuad, 0, upper_radus, res, res );
		};
		glPopMatrix();

		// close lower
		glPushMatrix();
		{
			glTranslatef( 0, 0, section_height );
			gluDisk( myQuad, 0, radus, res, res );
		};
		glPopMatrix();
	};
	glPopMatrix();

	gluDeleteQuadric( myQuad );
}

void Tree::renderBranch( float length )
{
	if( length >= branch_threshold ) {
		// recursive call
		glPushMatrix();
		{
			glRotatef( branch_deflection, 1, 0, 0 );
			glRotatef( branch_rot, 0, 1, 0 );
			renderBranch( length - 5 );
		};
		glPopMatrix();
	} else if( length < branch_threshold ) {
		// will end recursion
		renderMidBranch( length );
	}
}

void Tree::renderMidBranch( float length )
{
	if( length >= (branch_threshold/2) ) {
		renderMidBranch( length - 5 );
	} else {
		renderEndBranch( length );
	}
}

void Tree::renderEndBranch( float length )
{
	glPushMatrix();
	{
		glTranslatef( 0, 0, length/2 );
		renderEndBranch( length - 5 );
	};
	glPopMatrix();
	glPushMatrix();
	{
		glTranslatef( 0, 0, length );
		renderLeaf( length );
	};
	glPopMatrix();
		renderLeaf( length );
}

void Tree::renderLeaf( float length )
{
	leafMat.set_as_current_material();
	glPushMatrix();
	{
		glTranslatef( 0, 0, length );
		glutSolidSphere( 1, 20, 20 );
	};
	glPopMatrix();
}

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

Tree::Type Tree::getType()
{
	return( this->type );
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

void Tree::setType( Tree::Type newType )
{
	this->type = newType;
	setup();
}

//** Dimensions

// Getters:
float Tree::getHeight()
{
	return( height );
}

float Tree::getWidth()
{
	return( width );
}

// Setters:
void Tree::setHight( float newHeight )
{
	height = newHeight;
}

void Tree::setWidth( float newWidth )
{
	width = newWidth;
}

//** Orientation:

// Cache the orientation to cut down number of calls
void Tree::setOrientation( BezierPatch* surface )
{
  this->orientation = surface->orient( getX(), getZ() );
  this->setY( orientation[0] - 5 );
}
