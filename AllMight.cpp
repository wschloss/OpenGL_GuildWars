// Walter Schlosser
// CSCI441
//
// All Might implementation

#include "AllMight.h"

// Default params are all 0, flame base set to 1
AllMight::AllMight() {
    x = y = z = 0;
    wheelRot = rot = 0;
    // Find the dir vectors
    calcDirection();
    // Update amounts
    speed = deltaRot = 0;
    flameBase = 1;
}

// Draws the main body of the car
void AllMight::drawBody() {
    glColor3f(1,0,0);
    // main body
    glPushMatrix(); {
        glScalef(3,1,2);
        glutSolidCube(1);
    } glPopMatrix();

    // front hood
    glPushMatrix(); {
        glTranslatef(1.5,0.5,0);
        glRotatef(45,0,0,-1);
        glScalef(1,0.5,2.5);
        glutSolidCube(1);
    } glPopMatrix();

    // Spoiler
    glPushMatrix(); {
        glTranslatef(-1,1,0);
        glRotatef(20,0,0,-1);
        glScalef(1.1,0.25,2.5);
        glutSolidCube(1);
    } glPopMatrix();

    // Spoiler cylinders
    glColor3f(0.1,0.1,0.1);
    GLUquadric* quad = gluNewQuadric();
    glPushMatrix(); {
        glTranslatef(-1,0.5,-0.5);
        glRotatef(90,-1,0,0);
        gluCylinder(quad, 0.25, 0.25, 0.5,10,10);   
    } glPopMatrix();

    glPushMatrix(); {
        glTranslatef(-1,0.5,0.5);
        glRotatef(90,-1,0,0);
        gluCylinder(quad, 0.25, 0.25, 0.5,10,10);   
    } glPopMatrix();
    gluDeleteQuadric(quad);
}

// Draws on wheel
void AllMight:: drawWheel() {
    glColor3f(0,0,1);
    glPushMatrix(); {
        glRotatef(wheelRot,0,0,-1);
        glutSolidTorus(0.1,0.5,10,6);
    } glPopMatrix();
}

// Draws the exhaust
void AllMight::drawExhaust() {
    // Draw the cone flame
    glColor3f(1,0.65,0);
    glPushMatrix(); {
        glTranslatef(0,0,-0.5);
        glutSolidCone(flameBase,1,10,10);
    } glPopMatrix();

    // draw the cylinder
    glColor3f(0.1,0.1,0.1);
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.25, 0.25, 0.75, 10, 10);
    gluDeleteQuadric(quad);

}

// Draws entire vehicle (no transforms for location besides height)
void AllMight::drawVehicle() {
  glPushMatrix(); {
    glTranslatef(0,0.7,0);
    drawBody();
    // Draw the wheels
    glPushMatrix(); {
        glTranslatef(0.9,-0.2,-1.2);
        drawWheel();
    } glPopMatrix();
    
    glPushMatrix(); {
        glTranslatef(-0.9,-0.2,-1.2);
        drawWheel();
    } glPopMatrix();

    glPushMatrix(); {
        glTranslatef(0.9,-0.2,1.2);
        drawWheel();
    } glPopMatrix();

    glPushMatrix(); {
        glTranslatef(-0.9,-0.2,1.2);
        drawWheel();
    } glPopMatrix();

    // Draw the exhaust
    glPushMatrix(); {
        glTranslatef(-2.25,0,0);
        glRotatef(90,0,1,0);
        drawExhaust();
    } glPopMatrix();
  } glPopMatrix();

}

// Draws vehicle with coord transforms
void AllMight::draw() {
    glPushMatrix(); {
        glTranslatef(x, y + 0.7, z);
        glRotatef(-rot, 0, 1, 0);
        drawVehicle();
    } glPopMatrix();
}

// Finds heading direction based on rotation
void AllMight::calcDirection() {
    dirX = cos(rot * M_PI/180);
    dirZ = -sin(rot* M_PI/180);
} 

// Updates the state of the vehicle
void AllMight::update() {
    // Update heading
    rot += deltaRot;
    calcDirection();
    // Update pos
    setX(x + speed*dirX);
    setZ(z + speed*dirZ);
    // Wheel update
    if (speed > 0)
        wheelRot += 3;
    else if (speed < 0)
        wheelRot -= 3;
    // Flame anim
    flameBase += 0.1;
    if (flameBase > 1.5) flameBase = 0.5;
}

// Key response functions
void AllMight::respondKeyDown(unsigned char key) {
  if (speed == 0 && key == 'w')
    setSpeed(2.5);
  if (speed == 0 && key == 's')
    setSpeed(-2.5);
  if (deltaRot == 0 && key == 'a')
    setDeltaRot(5);
  if (deltaRot == 0 && key == 'd')
    setDeltaRot(-5);
}

void AllMight::respondKeyUp(unsigned char key) {
  if (speed != 0 && (key == 'w' || key == 's'))
    setSpeed(0);
  if (deltaRot != 0 && (key == 'a' || key == 'd'))
    setDeltaRot(0);
}