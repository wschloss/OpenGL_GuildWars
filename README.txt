
Names: 
	Walter Carl Schlosser ( All Might ) 
	Tyler M. Bank ( CoolPantsBro )
	Zac McClain ( Castamere Castelli )

Program Title:
	Midterm Project: Guild Wars	

Description:
        This program creates a virtual world and utilizes, techniques such as
        hierarchal assembly, 3D drawing, lighting, animation, user interaction, 
        fileIO, Bezier curves, Bezier surfaces, and arc length parameterization,
        to showcase the knowledge gained by and the understanding of its Anthers.

Usage:
        Menu: (Right click to view the pop up menu.)
        When the menu is displayed you will see four options

        Arcball:        
                Selecting this option will show an additional menu of each
                hero that can be selected. Clicking on a hero name will update
                the camera to an ArcBall model and set that hero to become its 
                focus.
                -> The user can rotation the camera about the would with by 
                holding and dragging the left mouse button.
                -> CTRL + click and drag left button zooms the camera.
        First Person: 
                Selecting this option will show an additional menu of each
                hero that can be selected. Clicking on a hero name will update
                the camera to an first person model and set that hero to become
                its focus.
        Free Cam:
                This Selection will allow you to fly freely in the would by setting
                the camera model to a free cam implementation.
                -> 'w' will allow you to move forward.
                -> 'd' will move you backward.
                -> The clicking and dragging the mouse will control you direction.
        Quit:
                This will exit the application.

        When controlling the wondering hero ( Castamere ):

Build Instructions:

        Compilation:

                ~/path/to/main.cpp $ make
                if( OS X or *nix )
                        ~/path/to/main.cpp $ ./guildwars world.txt
                else
                        ~/path/to/main.cpp $ ./guildwars.exe  world.txt
                end

        Input File Format:
        
        world.txt ~ This file is simply a list of paths to all other needed
        world building files. The first line contains a valid file path to a 
        file file of valid format. This file will be used to create the world
        surface, the second line is the a curve.csv. The third line specify 
        the trees.csv or were the trees will be placed. This file must be in the 
        same directory as the guildWars exhaustible, it is passed into the 
        program as it only argument. 

        surface16.csv ~ The first line of this file is the number of points
        That the file contains. The subsequent lines contain each point in
        x,y,z order. This number must be 16, any other number of
        points will file to build a reasonable surface. This file can be
        named anything so long as it matches the first line world.txt.

        curve.csv ~ The first line in this file is the number of points. 
        The first line of this file is the number of points
        That the file contains. The subsequent lines contain each point in
        x,y,z order. This file can handle any number of points needed to create
        a valid BezierCurve. This curve is then used to create a path for the
        two the our hero's to fallow.

        trees.csv ~ This file specify the x,z positions of all the trees in the
        world, as well as the number of trees to be created. The first line is
        the number of trees. All subsequent lines are the in x,z data format.

Notes:
        Bugs:
                The arcball cam has a tendency to sub duct under the surface.
        Implementation Details:

Stats:
        Time Investment: (zac 10-20 hours)
        Learning Score[0, 10]: (zac 10)
        Entertainment Score[0, 10]: (zac 8)
        