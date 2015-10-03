// Walter Schlosser
// CSCI441
//
// Material object implementation


#include "Material.h"

// Defaults to all white
Material::Material() {
  amb = Color();
  dif = Color();
  spec = Color();
  shine = 0;
  alpha = 1;
}

// Set colors and shine on construction
Material::Material(Color amb, Color dif, Color spec, float shine) {
  this->amb = amb;
  this->dif = dif;
  this->spec = spec;
  // Clamped to range
  this->shine = fmax(0, fmin(128, shine));
  this->alpha = 1;
}

// Sets up material props with gl calls
void Material::set_as_current_material() {
  float amb4[4] = { amb.get_red(), amb.get_green(), amb.get_blue(), alpha };
  float dif4[4] = { dif.get_red(), dif.get_green(), dif.get_blue(), alpha };
  float spec4[4] = { spec.get_red(), spec.get_green(), spec.get_blue(), alpha };
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb4);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif4);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec4);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shine);
}
