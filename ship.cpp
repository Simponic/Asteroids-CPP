#include "ship.h"
#include "bullet.h"

#include <cmath>

#define M_PI 3.14159265
// Put your ship methods here

// Apply thrust to ship
void Ship :: thrust ( const bool isUp )
{
   float thrust = THRUST_AMOUNT * ( isUp ? 1 : -1 );
   fuel -= 3;
   if ( fuel >= 0 )
   {
        velocity.addDx ( thrust * ( -cos ( M_PI / 180 * angle ) ) );
        velocity.addDy ( thrust * ( sin ( M_PI / 180 * angle ) ) );
   }
   else
   {
       fuel = 0; // In the case of negative fuel
   }
}

// Rotate ship
void Ship :: rotate ( const bool isRight )
{
   angle += ROTATE_AMOUNT * ( isRight ? -1 : 1 );
   fuel -= 1;
}

// Draw ship
void Ship :: draw ( ) const
{
   drawShip ( getPoint() , -(angle - 90) , isThrusting );
}
