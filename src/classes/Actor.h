
#ifndef ACTOR_H
#define ACTOR_H

#include "../game.h"

class Actor {
    public:

        bool atop(vec2i targetPos);

        // TODO check if two points are within a unit of each other.  Maybe yagni...
        bool checkAdjacent(vec2i targetPos);

        // TODO get absolute minimum distance between two points. Maybe yagni...
        int_fast8_t getDistance(vec2i targetPos);

        void  moveLeft();
        void  moveRight();
        void  moveUp();
        void  moveDown();

        void  wait();
        void  move();
        void  tick();
        void  step();

        void  setPos(vec2i newPos);
        void  setChar(char newChar);

        vec2i getPos();
        char  getDispChar();
        int   getSteps() { return steps; }
        int   getTicks() { return ticks; }

    protected:
        vec2i pos;
        char  disp_char;
        int   steps = 0;
        int   ticks = 0;
};

#endif

