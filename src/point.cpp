/***********************************************************************
 * Source File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen, including
 *    the location and the bounds.
 ************************************************************************/

#include "../include/point.h"
#include <cassert>
#include "../include/uiDraw.h"
using namespace std;
/******************************************
 * POINT : CONSTRUCTOR WITH X,Y
 * Initialize the point to the passed position
 *****************************************/
Point::Point(float x, float y) : x(0.0), y(0.0)
{
   setX(x);
   setY(y);
}

/*******************************************
 * POINT : SET X
 * Set the x position if the value is within range
 *******************************************/
void Point::setX(float x)
{
   this->x = x;
}

/*******************************************
 * POINT : SET Y
 * Set the y position if the value is within range
 *******************************************/
void Point::setY(float y)
{
   this->y = y;
}

/******************************************
 * POINT insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream & operator << (std::ostream & out, const Point & pt)
{
   out << "(" << pt.getX() << ", " << pt.getY() << ")";
   return out;
}

/*******************************************
 * POINT extraction
 *       Prompt for coordinates
 ******************************************/
std::istream & operator >> (std::istream & in, Point & pt)
{
   float x;
   float y;
   in >> x >> y;

   pt.setX(x);
   pt.setY(y);

   return in;
}

bool Point::inRange( const Point &p, const float range )
{
    if ( ( fabs( getX() - p.getX() ) < range) &&
        ( fabs( getY() - p.getY() ) < range ) )
    {
        return true;
    }
    return false;
}
