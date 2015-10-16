// Walter Schlosser
// CSCI441
//
// Implementation for a campfire object

#include "Campfire.h"

Campfire::Campfire() {

}

// Enables the light for this object
void Campfire::enable() {
  this->light = new Light(GL_LIGHT1);
  light->setColors(Color(0.1,0.1,0.1), Color(0.1,0.1,0.1), Color(0.1,0.1,0.1));
  light->setPosition(0, 6, 0);
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.05);
  light->enable(); 
}

// Updates the light color props to flicker
void Campfire::update() {
  static int frames;
  frames++;
  // adjust frequency of the flicker here
  if (frames % 3 == 0) {
    // generate random light intensity
    float intensity = rand() % 100;
    intensity /= 100.0;
    light->setColors(
      Color(intensity, intensity, intensity),
      Color(intensity, intensity, intensity),
      Color(intensity, intensity, intensity)
    );
  }
}

// Draws a brown log
void Campfire::drawLog() { 
  // Woody material
  Material mat = Material(Color(0.1745, 0.01175, 0.01175),
                          Color(0.61424, 0.04136, 0.04136),
                          Color(0.727811, 0.626959, 0.626929),
                          0.5);
  mat.set_as_current_material();
  glPushMatrix(); {
    glScalef(2, 0.5, 0.5);
    glutSolidCube(5);
  } glPopMatrix();
}

void Campfire::draw() {
  glPushMatrix(); {
    // Surface transforms
    glTranslatef(0, orientation[0] + 2.5, 0);
    glRotatef(
      orientation[1],
      orientation[2],
      orientation[3],
      orientation[4]
    );
    
    // scale a little bigger
    glScalef(4,4,4);

    // place the light at 0,6,0
    light->resetPosition();
  
    // draw three logs in triangle
    glPushMatrix(); {
      glTranslatef(0,0,4);
      drawLog();
    } glPopMatrix();

    glPushMatrix(); {
      glRotatef(120, 0, 1, 0);
      glTranslatef(0,0,4);
      drawLog();
    } glPopMatrix();

    glPushMatrix(); {
      glRotatef(240, 0, 1, 0);
      glTranslatef(0,0,4);
      drawLog();
    } glPopMatrix();

    // Set reddish material for the fire cone
    Material mat(
      Color(0.35, 0.07, 0.01),
      Color(0.35, 0.07, 0.01),
      Color(0.35, 0.07, 0.01),
      0.5);
    mat.set_as_current_material();
    // fire cone
    glPushMatrix(); {
      glRotatef(90, -1, 0, 0);
      glutSolidCone(4, 6, 10, 10);
    } glPopMatrix();
      
  } glPopMatrix();
}

// returns a pointer to this campfire
Campfire* Campfire::self()
{
  return( this );
}

// Sets the rotation and y translate to be on the surface
void Campfire::setOrientation(BezierPatch* surface) {
  orientation = surface->orient(0, 0);
}
