#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 10
#define BULLET_LIFE 40

#include "point.h"
#include "velocity.h"
#include "flyingObject.h"

class Bullet : public FlyingObject
{
private:
    int framesAlive;

public:
    Bullet( const Point &point );
    int getFramesAlive() const { return framesAlive; };
    void fire( const Velocity &velocity , const float angle );
    void advance();
};


#endif /* bullet_h */
