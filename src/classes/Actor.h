
#ifndef ACTOR_H
#define ACTOR_H

#include "../game.h"

class Actor {
    public:

        bool atop(vec2i targetPos);
        bool isAdjacent(vec2i targetPos);
        int_fast8_t getDistanceX(vec2i targetPos);
        int_fast8_t getDistanceY(vec2i targetPos);


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

