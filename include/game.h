/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "bullet.h"
#include "ship.h"
#include "rocks.h"
#include "uiDraw.h"
#include "uiInteract.h"

#define CLOSE_ENOUGH 15

using namespace std;

class Game
{
private:
    Point topLeft;
    Point bottomRight;
    vector<Rock *> rocks;
    vector<Bullet *> bullets;
    Ship* ship;
	int level = 0;

    float getClosestDistance( const FlyingObject &obj1 , const FlyingObject &obj2 ) const;

    vector<Rock *> createRocks();

    void advanceBullets();
    void advanceAsteroids();
    void advanceShip();

    void cleanUpZombies();

    void handleCollisions();

    void drawBullets();
    void drawRocks();
    void drawShip();
public:
    Game ( const Point &tl , const Point &br );
    void handleInput ( const Interface &ui );
    void draw ( const Interface &ui );
    void advance();
};


#endif /* GAME_H */
