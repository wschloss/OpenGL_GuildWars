// OpenGL / GLUT Libraries we need
// Author: Tyler Bank

#ifdef __APPLE__			// if compiling on Mac OS
	#include <GLUT/glut.h>
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#else					// else compiling on Linux OS
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <math.h>

#include "./CoolPants.h"
#include "./Material.h"

CoolPants::CoolPants()
{
	height = 10;
	position = Point(0, height, 0);
	angle = 0;
	polyCount = 50;
}

CoolPants::CoolPants( Point position )
{
	this->position = position;
	angle = 0;
	polyCount = 50;
}

void CoolPants::update()
{
	angle += 0.5;
	if(angle > 360.0)
		angle = 0;
}

void CoolPants::drawHorse()
{
	drawBody();
	
	// draw head
	glPushMatrix();{
		glTranslatef(0, 1, 1.7);
		glRotatef( -5*sin(angle/2), 1, 0, 0 );
		glScalef(0.65, 0.65, 0.65);
		drawHead();
	}glPopMatrix();
	
	// draw the tail
	glPushMatrix();{
		glTranslatef(0, 0.25, -2);
		glRotatef( -10*sin(angle/2 + 0.25), 1, 0, 0 );
		glRotatef( -10*cos(angle/2 + 0.25), 0, 0, 1 );
		glScalef(0.25, 0.25, 0.25);
		drawTail();
	}glPopMatrix();
	
	// back left leg
	glPushMatrix();
		glTranslatef(0, -0.35, -0.90);
		//glRotatef( -10*sin(angle) - 25, 1, 0, 0 );
		glScalef( 1, 0.9, 1 );
		drawLeftLeg();
	glPopMatrix();
	
	
	// back right leg
	glPushMatrix();
		glTranslatef(0, -0.35, -0.90);
		//glRotatef( -10*cos(angle) - 25, 1, 0, 0 );
		glScalef( 1, 0.9, 1 );
		drawRightLeg();
	glPopMatrix();
	
	// front left leg
	glPushMatrix();
		glTranslatef(0, -0.35, 1.25);
		//glRotatef( -5*cos(angle) + 330, 1, 0, 0 );
		glScalef( 1, 0.75, 0.75 );
		drawLeftLeg();
	glPopMatrix();
	
	// front right leg
	glPushMatrix();
		glTranslatef(0, -0.35, 1.25);
		//glRotatef( -10*sin(angle) + 330, 1, 0, 0 );
		glScalef( 1, 0.75, 0.75 );
		drawRightLeg();
	glPopMatrix();
	
	// draw wheels
	
	//back left
	glPushMatrix();
		glTranslatef(0.65, -1.25, -1.2);
		glRotatef( 90, 0, 1, 0 );
		glRotatef( 20, 0, 0, 1 );
		drawWheel();
	glPopMatrix();
	//back right
	glPushMatrix();
		glTranslatef(-0.65, -1.25, -1.2);
		glRotatef( 90, 0, 1, 0 );
		glRotatef( 20, 0, 0, 1 );
		drawWheel();
	glPopMatrix();	
	
	//front left
	glPushMatrix();
		glTranslatef(0.65, -1.25, 1.15);
		glRotatef( 90, 0, 1, 0 );
		glRotatef( 20, 0, 0, 1 );
		drawWheel();
	glPopMatrix();
	
	
	// front right
	glPushMatrix();
		glTranslatef(-0.65, -1.25, 1.15);
		glRotatef( 90, 0, 1, 0 );
		glRotatef( 20, 0, 0, 1 );
		drawWheel();
	glPopMatrix();
}

void CoolPants::drawBody()
{
	glPushMatrix();{
		////glColor3f( 173.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glTranslatef(0, 0, 1);
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
	
	glPushMatrix();{
		
		glTranslatef(0, 0, 0.5);
		glRotatef( 345, 1, 0, 0 );
		glScalef(1.0*5/6, 1.0*5/6, 1.5*5/6 );
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
	
	glPushMatrix();{
		
		glTranslatef(0, -0.25, 0.5);
		glScalef(1.0*5/6, 1.0*5/6, 1.5*5/6 );
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
	
	glPushMatrix();{
		
		glTranslatef(0, -0.25, 0.5);
		glScalef(1.0*5/6, 1.0*5/6, 1.5*5/6 );
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
	
	glPushMatrix();{
		
		glTranslatef(0, 0, -0.25);
		glRotatef( 15, 1, 0, 0 );
		glScalef(1.0*5/6, 1.0*5/6, 1.5*5/6 );
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
	
	glPushMatrix();{
		
		glTranslatef(0, 0.15, -0.75);
		glScalef(1, 0.85, 1);
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
	
}

void CoolPants::drawLeftLeg()
{
	glPushMatrix();{
		
		glTranslatef(0.5, 0, 0);
		glRotatef( 300, 1, 0, 0 );
		glScalef(1.0*5/12, 1.0*5/6, 1.5*5/6 );
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
}

void CoolPants::drawRightLeg()
{
	glPushMatrix();{
		
		glTranslatef(-0.5, 0, 0);
		glRotatef( 300, 1, 0, 0 );
		glScalef(1.0*5/12, 1.0*5/6, 1.5*5/6 );
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();
}

void CoolPants::drawTail()
{
	glPushMatrix();{
		////glColor3f( 172.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glTranslatef(0, 0, -cos(2*M_PI/3));
		glutSolidCone( sin(2*M_PI/3), 2.0, polyCount, polyCount);		
	}; glPopMatrix();
	
	glPushMatrix(); {
		//glColor3f( 172.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glutSolidSphere(1.0, polyCount, polyCount);		
	}; glPopMatrix();
		
	glPushMatrix();{
		//glColor3f( 172.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glTranslatef(0, -2, 0);
		glRotatef(90, 1, 0, 0 );
		glScalef(1, 1, 10);
		glutSolidTorus( 0.25, 0.75, polyCount, polyCount);		
	}; glPopMatrix();
	
	glPushMatrix();{
		//glColor3f( 172.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glTranslatef(0, -4, 0);
		glRotatef(90, 1, 0, 0 );
		glutSolidCone( 0.95, 2.0, polyCount, polyCount);		
	}; glPopMatrix();
}

// head centered around the neck
void CoolPants::drawHead()
{
	glPushMatrix();{
		
		glTranslatef(0, -0.25, -0.2);
		
		glutSolidSphere(0.85, polyCount, polyCount);
	};glPopMatrix();
	
	glPushMatrix();{
		//glColor3f( 172.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glTranslatef(0, 0.5, 0.25);
		glRotatef(-55, 1, 0, 0 );
		glScalef(1, 1, 4);
		glutSolidTorus( 0.25, 0.5, polyCount, polyCount);		
	}; glPopMatrix();
	
	glPushMatrix();{
		//glColor3f( 172.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glTranslatef(0, 1, 1);
		glRotatef(-15, 1, 0, 0 );
		glScalef(1, 1, 4);
		glutSolidTorus( 0.25, 0.5, polyCount, polyCount);		
	}; glPopMatrix();
	
	glPushMatrix();{
		
		glTranslatef(0, 1, 1.5);
		
		glutSolidSphere(0.95, polyCount, polyCount);
	};glPopMatrix();
	
	glPushMatrix();{
		
		glTranslatef(0, 0.9, 2.25);
		
		glutSolidSphere(0.5, polyCount, polyCount);
	};glPopMatrix();	
	
	glPushMatrix();{
		//glColor3f( 172.0 / 255.0, 111.0 / 255.0, 57.0 / 255.0 );
		glTranslatef(0, 0.75, 2.5);
		glRotatef(30, 1, 0, 0 );
		glScalef(1, 1, 6);
		glutSolidTorus( 0.25, 0.25, polyCount, polyCount);		
	}; glPopMatrix();
	
	glPushMatrix();{
		//glColor3f( 172.0 / 255.0 / 2, 111.0 / 255.0 / 2, 57.0 / 255.0 / 2 );
		glTranslatef(0, 0.5, 2.5);
		glRotatef(15, 1, 0, 0 );
		glScalef(1, 1, 4);
		glutSolidTorus( 0.25, 0.25, polyCount, polyCount);		
	}; glPopMatrix();
	
	
	glPushMatrix();{
		glTranslatef( 0.5, 1.55, 1.5 );
		glRotatef(210, 1, 0, 0 );
		glScalef(0.05, 0.15, 0.15);
		drawTail();
	}glPopMatrix();
	
	glPushMatrix();{
		glTranslatef( -0.5, 1.55, 1.5 );
		glRotatef(210, 1, 0, 0 );
		glScalef(0.05, 0.15, 0.15);
		drawTail();
	}glPopMatrix();	
}

void CoolPants::drawLimb()
{
	glPushMatrix();{
		
		glutSolidSphere(1.0, polyCount, polyCount);
	};glPopMatrix();

	glPushMatrix();{
		//glColor3f( 172.0 / 255.0 / 2, 111.0 / 255.0 / 2, 57.0 / 255.0 / 2 );
		glTranslatef(0, -1, 0.25);
		glRotatef(80, 1, 0, 0 );
		glScalef(1, 1, 6);
		glutSolidTorus( 0.25, 0.65, polyCount, polyCount);
	}; glPopMatrix();
}

void CoolPants::drawWheel()
{
	glPushMatrix();{
	    Material matCoolPants = Material(Color(0, 0, 0),
	                            Color(0.1, 0.1, 0.1),
	                            Color(0, 0, 0),
	                            0.11*128);
	    matCoolPants.set_as_current_material();
		glScalef( 1, 1, 0.25 );
		glutSolidSphere( 1, polyCount, polyCount );
	};glPopMatrix();
	
	glPushMatrix();{
		//glColor3f( 0, 0, 0 );
		glutSolidCube( 0.5 );
	};glPopMatrix();
}