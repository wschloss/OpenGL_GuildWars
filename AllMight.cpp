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

  // Set the following vars to false
  followMode = false;
  t = 0;
  path = NULL;
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
void AllMight::drawWheel() {
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
  // Set a material for now
  Material mat = Material(Color(0.1745, 0.01175, 0.01175),
                          Color(0.61424, 0.04136, 0.04136),
                          Color(0.727811, 0.626959, 0.626929),
                          0.6*128);
  mat.set_as_current_material();

  glPushMatrix(); {
    glTranslatef(x, y + 0.7, z);
    glRotatef(rot, 0, 1, 0);
    drawVehicle();
  } glPopMatrix();
}

// Draws with the surface as orientation
void AllMight::draw(BezierPatch* surface) {
  // Set a material for now
  Material mat = Material(Color(0.1745, 0.01175, 0.01175),
                          Color(0.61424, 0.04136, 0.04136),
                          Color(0.727811, 0.626959, 0.626929),
                          0.6*128);
  mat.set_as_current_material();

  glPushMatrix(); {
    glTranslatef(x, y + 0.7, z);
    // Orient with the surface, by applying rotation
    vector<float> orientation = surface->orient(x, z);
    glRotatef(orientation[1], orientation[2], orientation[3], orientation[4]);
    glRotatef(rot, 0, 1, 0);
    drawVehicle();
  } glPopMatrix();
}

// Finds heading direction based on rotation
void AllMight::calcDirection() {
    dirX = cos(rot * M_PI/180);
    dirZ = -sin(rot * M_PI/180);
} 

// Updates the state of the vehicle
void AllMight::update() {
  // follow mode moves along the curve instead
  if (followMode) {
    // increment follow parameter
    t += 0.01;
    // find the point on the curve
    Point pos = path->findCurvePointFromParameter(t);
    // find the heading for the curve
    Point dir = path->findCurveTangentFromParameter(t);
    // set this objects state now, y will be handled by the surface
    setX(pos.getX());
    setZ(pos.getZ());
    dirX = dir.getX();
    dirZ = dir.getZ();
    rot = -atan2(dirZ,dirX) * 180/M_PI;
  } else {
    // Update heading
    rot += deltaRot;
    calcDirection();
    // Update pos
    setX(x + speed*dirX);
    setZ(z + speed*dirZ);
  }
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

// Sets this hero to follow mode and follows the path on update
void AllMight::setFollowPath(BezierCurve* path) {
  this->path = path;
  followMode = true;
  t = 0;
  // set speed so the wheels turn
  setSpeed(2.5);
}
