/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "../include/game.h"
#include "../include/uiDraw.h"
#include "../include/bullet.h"
// These are needed for the getClosestDistance function...
#include <limits>
#include <iostream>
#include <algorithm>
#define CLOSE_ENOUGH 15
using namespace std;

// Game non-default constructor
Game :: Game ( const Point &tl , const Point &br ) : topLeft ( tl ) , bottomRight ( br )
{
   rocks = createRocks();
   ship = new Ship ( Point() );
}

// Create rocks for the game
vector<Rock *> Game :: createRocks()
{
   vector<Rock *> initRocks;
   for ( int i = 0; i < random ( 5 + 2 * this->level , 8 + 2 * this->level ); i++ )
   {
      Point rockPoint = Point ( random( -190 , 190 ) , random ( -190 , 190 ) );
      Velocity velocity;
      velocity.setDx ( random ( -3.0 , 3.0 ) );
      velocity.setDy ( random ( -2.0 , 2.0 ) );
      // Make sure spawn is safe on start by calculating if
      // The rock is on a trajectory to the ship
      float m = velocity.getDy() / velocity.getDx();

      if ( fabs ( rockPoint.getY() - m * rockPoint.getX() ) >= 50 )
      {
         switch ( random( 1 , 5 ) ) {
            case 1:
            case 2:
            case 3:
               initRocks.push_back ( new BigRock ( rockPoint , velocity ) );
               break;
            case 4:
               initRocks.push_back ( new MediumRock ( rockPoint , velocity ) );
               break;
            case 5:
               initRocks.push_back ( new SmallRock ( rockPoint , velocity ) );
               break;
            default:
               break;
         }
      }
   }
   return initRocks;
}

// Get closest distance between two flying objects
float Game :: getClosestDistance(const FlyingObject &obj1, const FlyingObject &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));

      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();

      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);

      distMin = min(distMin, distSquared);
   }

   return sqrt(distMin);
}

// Advance everything in the game
void Game :: advance()
{
   cleanUpZombies();
   advanceShip();
   advanceBullets();
   advanceAsteroids();

   handleCollisions();
}

// Advance all asteroids in game
void Game :: advanceAsteroids()
{
   for ( int i = 0; i < rocks.size(); i++ )
   {
      rocks[i]->advance();
   }
}

// Advance all the bullets
void Game :: advanceBullets()
{
   for ( int i = 0; i < bullets.size(); i++ )
   {
      bullets[i]->advance();
   }
}

// Advance the ship
void Game :: advanceShip()
{
   if ( ship->isAlive() && ship->getFuel() >= 0 )
   {
      ship->advance();
   }
}

// Clean up memory
void Game :: cleanUpZombies()
{
   for ( int i = 0; i < bullets.size(); i++ )
   {
      if ( !bullets[i]->isAlive() )
      {
         delete bullets[i];
         bullets[i] = NULL;
         bullets.erase( bullets.begin() + i );
      }
   }
   if (rocks.size() > 0) {
	  for ( int i = 0; i < rocks.size(); i++ )
	  {
		  if ( !rocks[i]->isAlive() )
		  {
			 delete rocks[i];
			 rocks[i] = NULL;
			 rocks.erase( rocks.begin() + i );
		  }
	  }
   }
}

// Handle all collisions
void Game :: handleCollisions()
{
   // Handle bullet collisions
   for ( int i = 0; i < rocks.size(); i++ )
    {
        Rock * rock = rocks[i];
        if ( rock->isAlive() )
        {
            for ( int j = 0; j < bullets.size(); j++ )
            {
                Bullet * bullet = bullets[j];
                if ( bullet->isAlive() )
                {
                    float allowedRange = rock->getSize() + CLOSE_ENOUGH;
                    if ( fabs( getClosestDistance( *bullet , *rock ) ) < allowedRange
                    || bullet->getPoint().inRange( rock->getPoint() , allowedRange ) )
                    {
                        vector<Rock *> newRocks = rock->destroy();
                        for ( int i = 0; i < newRocks.size(); i++ )
                        {
                            rocks.push_back ( newRocks[i] );
                        }
                        rock->kill();
                        bullet->kill();
                    }
                }
            }
        }
    }

   // Handle ship collisions
   for ( int i = 0; i < rocks.size(); i++ )
   {
      Rock * rock = rocks[i];
      if ( rock->isAlive() && ship->isAlive() )
      {
         float allowedRange = rock->getSize() + CLOSE_ENOUGH;
         if ( fabs( getClosestDistance( *ship , *rock ) ) < allowedRange
              || ship->getPoint().inRange( rock->getPoint() , allowedRange ) )
            {
                vector<Rock *> newRocks = rock->destroy();
                for ( int i = 0; i < newRocks.size(); i++ )
            {
               rocks.push_back ( newRocks[i] );
            }
                rock->kill();
                ship->kill();
            }
      }
   }
   cleanUpZombies();
}

// Draw everything
void Game :: draw ( const Interface &ui )
{
   drawRocks();
   drawShip();
   drawBullets();
   drawNumber ( Point ( -170 , 170 ) , (int) ship->getFuel() );
   drawText ( Point ( -170 , 180 ) , "FUEL:" );
   drawNumber ( Point (-170, 130) , (int) level);
   drawText ( Point(-170, 140), "LEVEL:");
   if (!ship->isAlive()) {
      drawText( Point ( -90 , 0 ) , "Play again? (space to continue)");
   }
   if (rocks.size() == 0 && ship->isAlive()) {
      drawText( Point ( -90 , 0 ) , "Press space to continue to next level ");
   } 
}

// Draw rocks
void Game :: drawRocks()
{
   for ( int i = 0; i < rocks.size(); i++ )
   {
      rocks[i]->draw();
   }
}

// Draw ship
void Game :: drawShip()
{
   if ( ship->isAlive() )
   {
       ship->draw();
   }
}

// Draw bullets
void Game :: drawBullets()
{
   for ( int i = 0; i < bullets.size(); i++ )
   {
      bullets[i]->draw();
   }
}

// Handle in-game input
void Game::handleInput(const Interface & ui)
{
    if ( ship->isAlive() && rocks.size() > 0 )
    {
        if ( ui.isUp() )
        {
            ship->setThrusting ( true );
            ship->thrust( true );
        }
        if ( ui.isDown() )
        {
            ship->setThrusting ( true );
            ship->thrust( false );
        }
        if ( ui.isLeft() )
        {
            ship->setThrusting ( true );
            ship->rotate( true );
        }
        if ( ui.isRight() )
        {
            ship->setThrusting ( true );
            ship->rotate( false );
        }
        if ( ui.isSpace() )
        {
            Bullet * newBullet = new Bullet( ship->getPoint() );
            newBullet->fire( ship->getVelocity(), ship->getAngle() );
            bullets.push_back( newBullet );
        }
        if ( !ui.isRight() && !ui.isUp() && !ui.isDown() && !ui.isLeft() )
        {
            ship->setThrusting ( false );
        }
    }
	else if ( !ship->isAlive() && rocks.size() > 0){
		if ( ui.isSpace() ) {
			rocks = createRocks();
		    ship = new Ship ( Point() );	
			level = 0;
		}
	}
	else if ( ship->isAlive() && rocks.size() == 0) {
		if ( ui.isSpace() ) {
			rocks = createRocks();
			ship = new Ship ( Point() );
			level++;
		}
	}
}
