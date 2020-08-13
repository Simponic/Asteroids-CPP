#include "../include/velocity.h"

// Default velocity constructor
Velocity :: Velocity ()
{
   setDx ( 0.0 );
   setDy ( 0.0 );
}

// Velocity constructor with data
Velocity :: Velocity ( float dx , float dy )
{
   setDx ( dx );
   setDy ( dy );
}

// Get Velocity dx
float Velocity :: getDx() const
{
   return dx;
}

// Get Velocity dy
float Velocity :: getDy() const
{
   return dy;
}

// Set Velocity dx
void Velocity :: setDx( float dx )
{
   this->dx = dx;
}

// Set Velocity dy
void Velocity :: setDy( float dy )
{
   this->dy = dy;
}

// Add dy Velocity
void Velocity :: addDy ( const float dy )
{
   this->dy += dy;
}

// Add dx Velocity
void Velocity :: addDx ( const float dx )
{
   this->dx += dx;
}

// Update a point
Point Velocity :: updatePoint ( Point &point )
{
   point.addX ( dx );
   point.addY ( dy );
   return point;
}
