
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <cstdlib>
#include <ncurses.h>

#include "../directions.h"
#include "../game.h"
#include "../windows/Window.h"
#include "Entity.h"

class Actor : public Entity {
    public:

        Actor() {};
        Actor(Window *newW);

        // Movement
        void  moveNorth();
        void  moveNorthEast();
        void  moveEast();
        void  moveSouthEast();
        void  moveSouth();
        void  moveSouthWest();
        void  moveWest();
        void  moveNorthWest();


        // Iterators
        void  wait();
        void  move();
        void  tick();
        void  step();

        int   getSteps() { return steps; }
        int   getTicks() { return ticks; }

    protected:
        int   steps = 0;
        int   ticks = 0;
};

#endif

