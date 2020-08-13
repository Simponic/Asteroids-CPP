#include "../include/flyingObject.h"
#include <iostream>

// Advance flyingobjects
void FlyingObject::advance()
{
    point.addX( getVelocity().getDx() );
    point.addY( getVelocity().getDy() );

    if ( point.getX() > 200 )
        point.setX( -200 );
    else if ( point.getX() < -200 )
        point.setX( 200 );

    if ( point.getY() > 200 )
        point.setY( -200 );
    else if ( point.getY() < -200 )
        point.setY( 200 );

}
