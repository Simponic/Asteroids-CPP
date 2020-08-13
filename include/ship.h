#ifndef ship_h
#define ship_h

#define SHIP_SIZE 10
#define ROTATE_AMOUNT 6
#define THRUST_AMOUNT 0.5

#include "flyingObject.h"
#include "uiDraw.h"
#include "uiInteract.h"

using namespace std;

class Ship : public FlyingObject
{
private:
   float angle;
   bool isThrusting;
   int fuel;
public:
   Ship( const Point &point ) : FlyingObject() , fuel ( 1000 ) , angle ( 90.0 ) , isThrusting( false ) { setPoint ( point ); }
   float getAngle() const { return this->angle; }
   float getFuel() { return this->fuel; }
   void setFuel ( const int fuel ) { this->fuel - fuel; }
   void thrust( const bool isUp );
   void rotate( const bool isRight );
   bool getIsThrusting() { return isThrusting; }
   void setThrusting( const bool isThrusting ) { this->isThrusting = isThrusting; }
   void draw() const;
};

#endif /* ship_h */
