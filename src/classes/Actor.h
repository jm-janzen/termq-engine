
#ifndef ACTOR_H
#define ACTOR_H

#include <ncurses.h>

#include "../game.h"

class Actor {
    public:
        Actor(WINDOW *newW);

        void render();

        bool atop(vec2i const targetPos);
        bool isAdjacent(vec2i const targetPos);
        int_fast8_t getDistance(vec2i const targetPos);
        int_fast8_t getDistanceX(vec2i const targetPos);
        int_fast8_t getDistanceY(vec2i const targetPos);


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
        int   disp_colo;
        int   steps = 0;
        int   ticks = 0;
        WINDOW *w;
};

#endif

