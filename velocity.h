#ifndef VELOCITY_H
#define VELOCITY_H

#include "point.h"

class Velocity
{
   public:
      Velocity();
      Velocity( float dx , float dy );
      float getDx() const;
      float getDy() const;
      void addDy( const float dy );
      void addDx( const float dx );
      void setDx( float dx );
      void setDy( float dy );
      Point updatePoint ( Point &point );
   private:
      float dx;
      float dy;
};

#endif
