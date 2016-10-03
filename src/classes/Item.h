#ifndef ITEM_H
#define ITEM_H

#include "../game.h"

class Item {
    public:
        void  setPos(vec2ui newPos);
        void  setChar(char newChar);
        void  setValue(int newValue);

        vec2ui getPos();
        char  getDispChar();
        int   getValue();

    protected:
        vec2ui      pos;
        char        disp_char;
        int_fast16_t value;
};

#endif

