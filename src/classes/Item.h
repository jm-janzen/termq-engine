#ifndef ITEM_H
#define ITEM_H

#include "../game.h"

class Item {
    public:
        void  setPos(vec2i newPos);
        void  setChar(char newChar);
        void  setValue(int newValue);

        vec2i getPos();
        char  getDispChar();
        int   getValue();

    protected:
        vec2i       pos;
        char        disp_char;
        int_fast8_t value;
};

#endif

