
#ifndef ACTOR_H
#define ACTOR_H

#include "../game.h"

class Actor {
    public:
        // TODO check if two points occupy the same space
        bool atop(vec2i targetPos);

        // TODO check if two points are within a unit of each other.  Maybe yagni...
        bool checkAdjacent(vec2i targetPos);

        // TODO get absolute minimum distance between two points. Maybe yagni...
        int_fast8_t getDistance(vec2i targetPos);

        void  moveLeft();
        void  moveRight();
        void  moveUp();
        void  moveDown();

        void  setPos(vec2i newPos);
        void  setPosX(int_fast8_t newXPos);
        void  setPosY(int_fast8_t newYPos);
        void  setChar(char newChar);

        vec2i getPos();
        char  getDispChar();

    protected:
        vec2i pos;
        char disp_char;
};

#endif

