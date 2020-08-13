# Author:
#     Logan Hunt
# Summary:
#     Play the game asteroids
# Above and Beyond (Extra Credit)
#	  Changed colors
#     Added fuel
#        rotation: -1 units/frame
#        movement: -3 units/frame
#     Made sure that initially, trajectories of spawned rocks will
#        not hit ship
#     There's a chance of medium asteroids spawning at the start
#     The initial amount of large rocks is random
###############################################################

LFLAGS = -lglut -lGLU -lGL

###############################################################
# Build the main game
###############################################################
a.out: driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o
	g++ driver.o game.o uiInteract.o uiDraw.o point.o velocity.o flyingObject.o ship.o bullet.o rocks.o $(LFLAGS)

###############################################################
# Individual files
#    uiDraw.o       Draw polygons on the screen and do all OpenGL graphics
#    uiInteract.o   Handles input events
#    point.o        The position on the screen
#    game.o         Handles the game interaction
#    velocity.o     Velocity (speed and direction)
#    flyingObject.o Base class for all flying objects
#    ship.o         The player's ship
#    bullet.o       The bullets fired from the ship
#    rocks.o        Contains all of the Rock classes
###############################################################
uiDraw.o: uiDraw.cpp ../include/uiDraw.h
	g++ -c uiDraw.cpp

uiInteract.o: uiInteract.cpp ../include/uiInteract.h
	g++ -c uiInteract.cpp

point.o: point.cpp ../include/point.h
	g++ -c point.cpp

driver.o: driver.cpp ../include/game.h
	g++ -c driver.cpp

game.o: game.cpp ../include/game.h ../include/uiDraw.h ../include/uiInteract.h ../include/point.h ../include/velocity.h ../include/flyingObject.h ../include/bullet.h ../include/rocks.h ../include/ship.h
	g++ -c game.cpp

velocity.o: velocity.cpp ../include/velocity.h ../include/point.h
	g++ -c velocity.cpp

flyingObject.o: flyingObject.cpp ../include/flyingObject.h ../include/point.h ../include/velocity.h ../include/uiDraw.h
	g++ -c flyingObject.cpp

ship.o: ship.cpp ../include/ship.h ../include/flyingObject.h ../include/point.h ../include/velocity.h ../include/uiDraw.h
	g++ -c ship.cpp

bullet.o: bullet.cpp ../include/bullet.h ../include/flyingObject.h ../include/point.h ../include/velocity.h ../include/uiDraw.h
	g++ -c bullet.cpp

rocks.o: rocks.cpp ../include/rocks.h ../include/flyingObject.h ../include/point.h ../include/velocity.h ../include/uiDraw.h
	g++ -c rocks.cpp

###############################################################
# General rules
###############################################################
clean:
	rm a.out *.o
