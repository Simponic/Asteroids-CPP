#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "flyingObject.h"
#include <vector>

using namespace std;

class Rock : public FlyingObject
{
protected:
    int rotationDegPerFrame;
    int size;
    float angle;
public:
    Rock() : FlyingObject() , rotationDegPerFrame ( 0 ) , size ( 1 ) , angle ( 0 ) {}
    Rock ( int degPerFrame , int size , float angle ) : rotationDegPerFrame ( degPerFrame ) , size ( size ) , angle ( angle ) {}

    int getRotationDegPerFrame() { return rotationDegPerFrame; }
    int getSize () { return size; }
    float getAngle() { return angle; }

    void setAngle ( const float angle ) { this->angle = angle; }
    void setRotationDegPerFrame ( const int degPerFrame ) { this->rotationDegPerFrame = degPerFrame; }
    void setSize ( const int size ) { this->size = size; }
    void advance() { this->angle += rotationDegPerFrame; FlyingObject::advance(); }
    virtual void draw() {};
    virtual vector<Rock *> destroy() = 0;
};

class BigRock : public Rock
{
public:
    BigRock ( const Point &point , const Velocity &velocity )
    {
        setPoint ( point );
        setAngle ( 0 );
        setSize ( BIG_ROCK_SIZE );
        setRotationDegPerFrame ( BIG_ROCK_SPIN );
        setAngle ( random ( 0 , 360 ) );
        setVelocity ( velocity );
    }

   vector<Rock *> destroy();
   void draw();
};

class MediumRock : public Rock
{
public:
   MediumRock ( const Point &point , const Velocity &vel ) {
      this->point = point;
      this->velocity = vel;
      setAngle ( 0 );
      setRotationDegPerFrame ( MEDIUM_ROCK_SPIN );
      setSize ( MEDIUM_ROCK_SIZE );
   }
   vector<Rock *> destroy();
   void draw();
};

class SmallRock : public Rock
{
public:
   SmallRock( const Point &point , const Velocity &vel ) {
      this->point = point;
      this->velocity = vel;
      setAngle ( 0 );
      setRotationDegPerFrame ( SMALL_ROCK_SPIN );
      setSize ( SMALL_ROCK_SIZE );
   }
   vector<Rock *> destroy();
   void draw();
};

#endif /* rocks_h */
