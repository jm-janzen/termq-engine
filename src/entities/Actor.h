
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <cstdlib>
#include <ncurses.h>

#include "../directions.h"
#include "../game.h"
#include "../windows/Window.h"
#include "Entity.h"

struct Attributes {
    uint_fast8_t ATK = 0;
    uint_fast8_t ACT = 1;
    uint_fast8_t LCK = 1;
    uint_fast8_t HP = 100;
    uint_fast8_t DF = 0;
};

class Actor : public Entity {
    public:

        Actor();
        Actor(Window *newW);

        // Movement
        // TODO maybe combine these and accept a Direction
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
        void  tick();
        void  step();
        void  move();  // tick + step

        int   getSteps() { return steps; }
        int   getTicks() { return ticks; }

        uint_fast8_t getATK() { return attr.ATK; }
        uint_fast8_t getACT() { return attr.ACT; }
        uint_fast8_t getLCK() { return attr.LCK; }
        uint_fast8_t getHP() { return attr.HP; }
        uint_fast8_t getDF() { return attr.DF; }

        uint_fast8_t getChance() { return attr.LCK * 10; }

    protected:
        int   steps = 0;
        int   ticks = 0;
        Attributes attr;
};

#endif

