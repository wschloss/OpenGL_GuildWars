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
  glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
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
  Material mat(
      Color(0.35, 0.07, 0.01),
      Color(0.35, 0.07, 0.01),
      Color(0.35, 0.07, 0.01),
      0.5);
  mat.set_as_current_material();
  glPushMatrix(); {
    glScalef(2, 0.5, 0.5);
    glutSolidCube(5);
  } glPopMatrix();
}

void Campfire::draw() {
  glPushMatrix(); {
    glTranslatef(0, orientation[0] + 2.5, 0);
    glRotatef(
      orientation[1],
      orientation[2],
      orientation[3],
      orientation[4]
    );
    light->resetPosition();
    drawLog();
  } glPopMatrix();
}

// Sets the rotation and y translate to be on the surface
void Campfire::setOrientation(BezierPatch* surface) {
  orientation = surface->orient(0, 0);
}
