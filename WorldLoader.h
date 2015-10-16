// Walter Schlosser
// CSCI441
//
// Reads the world file format and constructs/loads the surface and
// track.

#pragma once

// c++ file utilities
#include <fstream>
#include <iostream>
#include <string>

// Include the objects that will be constructed
#include "BezierPatch.h"
#include "BezierCurve.h"

// Dependencies
#include "Material.h"
#include "Point.h"
#include "Color.h"

using namespace std;

class WorldLoader {
public:

  // Default Constructor
  WorldLoader();
  // Construct with world file name
  WorldLoader( char* worldfilename );
  // Default Destructor
  ~WorldLoader();

  // Loads the file into memory, exits the program if an error occurs
  void loadWorldComponentFilenames( char* worldfilename );

  // Constructs the surface and returns it.  Exits on file read fail
  BezierPatch* constructSurface();

  // Constructs the curve and returns it.  Exits on file read fail
  BezierCurve* constructCurve();

  vector<Point> constructTreePoints();

private:

  // configured boolean:
  bool is_configured;

  // Stores the file names for objects to load from
  string* surfaceFilename;
  string* curveFilename;
  string* treeFileName;

};
