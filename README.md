# "Guild Wars" project

## Names: 
* Walter Carl Schlosser ( All Might ) 
* Tyler M. Bank ( CoolPantsBro )
* Zac McClain ( Castamere Castelli )

## Description:
This program uses OpenGL to render the area for the three heroes listed above to 
train for their guild. The program demonstrates bezier curves and surfaces,
lighting and materials, 3d primitives and animation, as well as various camera
models.  This code was produced for the midterm project in Computer Graphics.

## Usage:
* Menu: (Right click to view the pop up menu.)
* When the menu is displayed you will see four options

* Arcball:        
  * Selecting this option will show an additional menu of each
  hero that can be selected. Clicking on a hero name will update
  the camera to an ArcBall model and set that hero to become its 
  focus.
  * -> The user can rotate the camera about the hero by 
  holding and dragging the left mouse button.
  * -> CTRL + click and drag left button zooms the camera.
  * -> Castamere can be controlled with 'wasd' when he is the arcball focus
* First Person: 
  * Selecting this option will show an additional menu which will
  allow the user to toggle a picture in picture display
  of that character's first person view. Clicking on a hero name 
  will update the camera to a first person model and set that hero
  to become its focus.
* Free Cam:
  * This Selection will allow you to fly freely in the would by setting
  the camera model to a free cam implementation.
  * -> 'w' will allow you to move forward.
  * -> 'd' will move you backward.
  * -> clicking and dragging the mouse will control you direction.
* Quit:
  * This will exit the application.

## Build Instructions:
This program requires GLUI to build, edit the makefile to reflect your include
and lib path.
### Compilation:
* ~/path/to/main.cpp $ make

* if( OS X or *nix )
      ~/path/to/main.cpp $ ./guildwars world.txt
  else
      ~/path/to/main.cpp $ ./guildwars.exe world.txt
  end
