// Walter Schlosser
// CSCI441
//
// Implementation of a light

#include "Light.h"

Light::Light(GLenum number) {
  this->number = number;
  float dif4[4] = { 1, 1, 1, 1}; 
  float spec4[4] = { 1, 1, 1, 1 };
  float amb4[4] = { 0.1, 0.1, 0.1, 1.0 }; 
  glLightfv(number, GL_AMBIENT, amb4);
  glLightfv(number, GL_DIFFUSE, dif4);
  glLightfv(number, GL_SPECULAR, spec4);
  x = y = z = 0;
  float pos[4] = { 0, 0, 0, 1 };
  glLightfv(number, GL_POSITION, pos);
}

// Sets the props on construction
Light::Light(GLenum number, Color amb, Color dif, Color spec) {
  this->number = number;
  this->amb = amb;
  this->dif = dif;
  this->spec = spec;
  float amb4[4] = { amb.get_red(), amb.get_green(), amb.get_blue(), 1 };
  float dif4[4] = { dif.get_red(), dif.get_green(), dif.get_blue(), 1 };
  float spec4[4] = { spec.get_red(), spec.get_green(), spec.get_blue(), 1 };
  glLightfv(number, GL_AMBIENT, amb4);
  glLightfv(number, GL_DIFFUSE, dif4);
  glLightfv(number, GL_SPECULAR, spec4);
  x = y = z = 0;
  float pos[4] = { 0, 0, 0, 1 };
  glLightfv(number, GL_POSITION, pos);
}

// Set the position for this light
void Light::setPosition(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
  float pos[4] = { x, y, z, 1 };
  glLightfv(number, GL_POSITION, pos);
}

// Reset the position if you want a static light (call after gluLookAt)
void Light::resetPosition() {
  float pos[4] = { x, y, z, 1 };
  glLightfv(number, GL_POSITION, pos);
}

// Enables this light
void Light::enable() {
  glEnable(number);
}

