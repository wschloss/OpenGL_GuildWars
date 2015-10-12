// Walter Schlosser
// CSCI441
//
// All Might implementation

#include "AllMight.h"

// Default params are all 0, flame base set to 1
AllMight::AllMight() {
  x = y = z = 0;
  hairRot = legRot = rot = 0;
  // Find the dir vectors
  calcDirection();
  // Update amounts
  speed = deltaRot = 0;

  // Set the following vars to false
  followMode = false;
  t = 0;
  path = NULL;
}

// Draws the main body of the car
void AllMight::drawBody() {
  // Steel Material
  Material mat(
    Color(0.192, 0.192, 0.192),
    Color(0.508, 0.508, 0.508),
    Color(0.508, 0.508, 0.508),
    51.2
  );
  mat.set_as_current_material();

  // body box
  glPushMatrix(); {
    glScalef(2, 3, 3);
    glutSolidCube(1); 
  } glPopMatrix();

  // Arm boxes
  glPushMatrix(); {
    glTranslatef(0, 0.75, 3);
    glScalef(0.5, 0.5, 3);
    glutSolidCube(1);
  } glPopMatrix();

  glPushMatrix(); {
    glTranslatef(0, 0.75, -3);
    glScalef(0.5, 0.5, 3);
    glutSolidCube(1);
  } glPopMatrix();
}

// draws a leg - cone and foot box
void AllMight::drawLeg() {
  // Steel Material
  Material mat(
    Color(0.192, 0.192, 0.192),
    Color(0.508, 0.508, 0.508),
    Color(0.508, 0.508, 0.508),
    51.2
  );
  mat.set_as_current_material();

  // cone
  glPushMatrix(); {
    glTranslatef(0, 2, 0);
    glRotatef(90, 1, 0, 0);
    glutSolidCone(0.5, 2, 10, 10);
  } glPopMatrix();

  // foot
  glPushMatrix(); {
    glTranslatef(0.25, 0, 0);
    glScalef(1, 0.5, 0.5);
    glutSolidCube(1);
  } glPopMatrix();
}

// draws a head - box and hair cone and eye spheres
void AllMight::drawHead() {
  // Steel Material
  Material mat(
    Color(0.192, 0.192, 0.192),
    Color(0.508, 0.508, 0.508),
    Color(0.508, 0.508, 0.508),
    51.2
  );
  mat.set_as_current_material();

  // head box
  glPushMatrix(); {
    glScalef(2,2,2);
    glutSolidCube(1);
  } glPopMatrix();

  // Red Material
  Material mat2(
    Color(0.35, 0.07, 0.01),
    Color(0.35, 0.07, 0.01),
    Color(0.35, 0.07, 0.01),
    0.5);
  mat2.set_as_current_material();

  // head cone
  glPushMatrix(); {
    glTranslatef(0,1,0);

    // Hair rotation
    glRotatef(45.0*sin(hairRot), 1, 0, 0);
    glTranslatef(0,1,0);

    glRotatef(90.0, 1, 0, 0);
    glTranslatef(0,0,-1);
    glutSolidCone(1, 2, 10, 10);
  } glPopMatrix();

  // Black Material
  Material mat3(
    Color(0.05, 0.05, 0.05),
    Color(0.05, 0.05, 0.05),
    Color(0.05, 0.05, 0.05),
  1);
  mat3.set_as_current_material();

  // Eyes
  glPushMatrix(); {
    glTranslatef(1, 0.5, -0.5);
    glutSolidSphere(0.25, 10, 10);
  } glPopMatrix();
  
  glPushMatrix(); {
    glTranslatef(1, 0.5, 0.5);
    glutSolidSphere(0.25, 10, 10);
  } glPopMatrix();
}

// Draws assembled character
void AllMight::drawComplete() {
  // body
  glPushMatrix(); {
    glTranslatef(0,4,0);
    drawBody();
  } glPopMatrix();

  // head
  glPushMatrix(); {
    glTranslatef(0,6.5,0);
    drawHead();
  } glPopMatrix();

  // Legs
  glPushMatrix(); {
    glTranslatef(0, 0.5, -1);

    // Leg rotation
    glTranslatef(0, 2.25, 0);
    glRotatef(45*sin(legRot), 0, 0, 1);
    glTranslatef(0, -2.25, 0);
    drawLeg();
  } glPopMatrix();

  glPushMatrix(); {
    glTranslatef(0, 0.5, 1);
    
    // Leg rotation
    glTranslatef(0, 2.25, 0);
    glRotatef(-45*sin(legRot), 0, 0, 1);
    glTranslatef(0, -2.25, 0);
    drawLeg();
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
    glTranslatef(x, y, z);
    // Orient with the surface, by applying rotation
    glRotatef(orientation[1], orientation[2], orientation[3], orientation[4]);
    glRotatef(rot, 0, 1, 0);
    drawComplete();
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
    glTranslatef(x, y, z);

    // Orient with the surface, by applying rotation
    orientation = surface->orient(x, z);
    glRotatef(orientation[1], orientation[2], orientation[3], orientation[4]);

    glRotatef(rot, 0, 1, 0);
    drawComplete();
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

  // every frame
  hairRot += 1;
  if (speed != 0) {
    legRot += 0.5;
  }
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

// Set the orientation vecotr to snap to the surfeace passed
void AllMight::setOrientation(BezierPatch* surface) {
  this->orientation = surface->orient(x, z);
  setY(orientation[0]);
}
