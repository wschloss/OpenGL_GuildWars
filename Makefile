TARGET = guildwars
OBJECTS = main.o Point.o ArcBallCamera.o BezierCurve.o BezierSurface.o

CXX    = g++
CFLAGS = -Wall -g

#############################
## SETUP GLUI
##      We must link against
##  GLUI before we link against
##  GLUT.
##
##     If you want to build
##  on your own machine, you
##  need to change the
##  appropriate paths.
#############################

# Windows Lab builds 
ifeq ($(OS), Windows_NT)
	INCPATH += -IZ:/CSCI441GFx/include/
	LIBPATH += -LZ:/CSCI441GFx/lib/

# Non-Windows build
else
# INCPATH += -I/Users/jpaone/Desktop/include/
# LIBPATH += -L/Users/jpaone/Desktop/lib
# GLUI located one directory up for my setup
	INCPATH += -I../include/
	LIBPATH += -L../lib/
endif

LIBS += -lglui

#############################
## SETUP OpenGL & GLUT 
#############################

# Windows builds 
ifeq ($(OS), Windows_NT)
	INCPATH += -IC:/Strawberry/c/include/
	LIBS += -lglut -lopengl32 -lglu32 -LC:/Strawberry/c/lib/

# Mac builds
else ifeq ($(shell uname), Darwin)
	LIBS += -framework GLUT -framework OpenGL

# Linux and all other builds
else
	LIBS += -lglut -lGL -lGLU
endif

#############################
## COMPILATION INSTRUCTIONS 
#############################

all: $(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

depend:
	rm -f Makefile.bak
	mv Makefile Makefile.bak
	sed '/^# DEPENDENCIES/,$$d' Makefile.bak > Makefile
	echo '# DEPENDENCIES' >> Makefile
	$(CXX) $(INCPATH) -MM *.cpp >> Makefile

.c.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cc.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

.cpp.o: 	
	$(CXX) $(CFLAGS) $(INCPATH) -c -o $@ $<

$(TARGET): $(OBJECTS) 
	$(CXX) $(CFLAGS) $(INCPATH) -o $@ $^ $(LIBPATH) $(LIBS)

# DEPENDENCIES
main.o: main.cpp
Point.o: Point.cpp Point.h
ArcBallCamera.o: ArcBallCamera.cpp ArcBallCamera.h
BezierCurve.o: BezierCurve.cpp BezierCurve.h
BezierSurface.o: BezierSurface.cpp BezierSurface.h
