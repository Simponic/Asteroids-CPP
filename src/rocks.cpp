#include "../include/rocks.h"
#include "../include/uiDraw.h"
#include <cmath>
#define M_PI 3.14159265

// Destroy Big Rock and return vector of new *rocks
vector<Rock *> BigRock :: destroy()
{
   vector<Rock *> rocks;
   Velocity rockVel = this->velocity;
   Point rockPoint = this->point;
   
   rockVel.addDy ( 1 );
   rocks.push_back ( new MediumRock ( rockPoint , rockVel ) );

   rockVel.addDy ( -2 ); // Original rockvel dy - 1
   rocks.push_back ( new MediumRock ( rockPoint , rockVel ) );

   rockVel.addDy ( 1 ); // Original rockvel dy
   rockVel.addDx ( (float) random ( 1.0 , 3.0 ) );
   rocks.push_back ( new SmallRock ( rockPoint , rockVel ) );

   return rocks;
}

// Draw big rock
void BigRock :: draw()
{
   drawLargeAsteroid ( this->point , this->angle );
}

// Destroy Medium Rock and return vector of new *rocks
vector<Rock *> MediumRock :: destroy()
{
   vector<Rock *> rocks;
   Velocity rockVel = this->velocity;
   Point rockPoint = this->point;

   rockVel.addDx ( 3 );
   rocks.push_back ( new SmallRock ( rockPoint , rockVel ) );
   rockVel.addDx ( -6 );
   rocks.push_back ( new SmallRock ( rockPoint , rockVel ) );

   return rocks;
}

// Draw Medium Rock
void MediumRock :: draw()
{
   drawMediumAsteroid ( this->point , this->angle );
}

// Destroy Small Rock and return an empty *rock vector
vector<Rock *> SmallRock :: destroy()
{
   return vector<Rock *>();
}

// Draw small rock
void SmallRock :: draw()
{
   drawSmallAsteroid ( this->point , this->angle );
}
