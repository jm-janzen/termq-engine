
#ifndef ACTOR_H
#define ACTOR_H

#include "../game.h"

class Actor {
    public:
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

