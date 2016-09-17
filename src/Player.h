#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "menu.h"

//struct {
//    vec2i pos;
//    char disp_char;
//} player;

class Player {
    public:
        Player(); // ctor

        void  setPos(vec2i newPos);
        void  setPosX(int_fast8_t newXPos);
        void  setPosY(int_fast8_t newYPos);
        void  setChar(char newChar);

        vec2i getPos();
        char  getDispChar();

    private:
        rect player;

        vec2i pos;
        rect bounds;
        char disp_char;
};

#endif

