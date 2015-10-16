// Walter Schlosser
// CSCI441
//
// Implementation of object that loads the world file

#include "WorldLoader.h"

WorldLoader::WorldLoader()
{
  surfaceFilename = new string();
  curveFilename = new string();
  is_configured = false;
}

// Read filenames on construct
WorldLoader::WorldLoader( char* worldfilename ) {
  surfaceFilename = new string();
  curveFilename = new string();
  is_configured = false;
  loadWorldComponentFilenames( worldfilename );
}

WorldLoader::~WorldLoader()
{
  delete surfaceFilename;
  surfaceFilename = NULL;
  delete curveFilename;
  curveFilename = NULL;
}

// Loads the file lines into memory, exits program if an error occurs
void WorldLoader::loadWorldComponentFilenames( char* worldfilename ) {
  // open up the file
  ifstream input;
  input.open( worldfilename );
  if ( input.fail() ) {
    // exit
    printf("The file %s was not found\n", worldfilename);
    exit( 1 );
  }

  // Get the first line, which corresponds to the surface file name
  if ( !getline(input, *surfaceFilename) ) {
    // exit
    printf("The world file format is incorrect (line 1)\n");
    exit( 1 );
  }

  // Get the second line, which corresponds to the curve file name
  if ( !getline(input, *curveFilename) ) {
    // exit
    printf("The world file format is incorrect (line 2)\n");
    exit( 1 );
  }

  // clean up the input stream
  input.close();
  is_configured = true;
}

// Constructs the surface and returns it.  Exits on file read fail
BezierPatch* WorldLoader::constructSurface() {

  if( !is_configured ) exit( 1 );

  // Allocate
  BezierPatch* patch = new BezierPatch();
  
  // Load file
  if( !patch->loadControlPoints(surfaceFilename->c_str()) ) {
    // exit
    printf( "Could not process file: %s\n", surfaceFilename->c_str() );
    exit( 1 );
  }

  // Set the material REFACTOR TO PASS THIS IN IF NEEDED
  patch->setMaterial( 
    Material(
      Color(0,0,0),
      Color(0.1, 0.35, 0.1),
      Color(0.45, 0.55, 0.45),
      (0.25 * 128)
    )
  );

  // return the constructed patch
  return patch;
}

// Constructs the curve and returns it. Exits on file read fail or if the 
BezierCurve* WorldLoader::constructCurve() {

  if( !is_configured ) exit( 1 );

  // Allocate
  BezierCurve* curve = new BezierCurve();
  // Load file
  if( !curve->loadControlPoints(curveFilename->c_str()) ) {
    // exit
    printf( "Could not process file: %s\n", curveFilename->c_str() );
    exit( 1 );
  }

  // return the constructed curve
  return curve;
}
