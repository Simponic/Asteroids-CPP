#include "../include/bullet.h"
#include "../include/ship.h"
#include <cmath>

#define M_PI 3.14159265

// Bullet non-default constructor
Bullet :: Bullet( const Point &point ) : FlyingObject() , framesAlive( 0 )
{
   setPoint ( point );
}

// Fire Bullet
void Bullet :: fire ( const Velocity &vel , const float angle )
{
   velocity.setDx ( BULLET_SPEED * ( -cos ( M_PI / 180 * angle ) ) );
   velocity.setDy ( BULLET_SPEED * ( sin ( M_PI / 180 * angle ) ) );
}

// Advance Bullet
void Bullet :: advance ()
{
   framesAlive++;
   if ( framesAlive >= 40 )
   {
      kill();
   }
   FlyingObject :: advance();
}
