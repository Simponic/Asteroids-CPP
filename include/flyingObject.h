#ifndef flyingObject_h
#define flyingObject_h

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class FlyingObject
{
protected:
    Point point;
    Velocity velocity;
    bool alive;
public:
    FlyingObject() : point( Point() ) , velocity( Velocity() ) , alive( true ) {}
    Point getPoint() const { return this->point; }
    void setPoint( const Point &point ) { this->point = point; }
    Velocity getVelocity() const { return this->velocity; }
    void setVelocity( const Velocity &velocity) { this->velocity = velocity; }
    bool isAlive() { return this->alive; }
    void kill() { alive = false; };
    virtual void draw() { drawDot( point ); };
    virtual void advance();
};



#endif /* flyingObject_h */
