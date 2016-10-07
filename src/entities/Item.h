#ifndef ITEM_H
#define ITEM_H

#include "../game.h"

enum Ownership {
    PLAYER, WORLD,
};

class Item {
    public:
        void  setPos(vec2ui newPos);
        void  setChar(char newChar);
        void  setValue(int newValue);

        void      setOwnership(Ownership own) { ownership = own; }
        Ownership getOwnership() { return ownership; }

        vec2ui getPos();
        char  getDispChar();
        int   getValue();

    protected:
        vec2ui      pos;
        char        disp_char;
        uint_fast16_t value;
        Ownership ownership = WORLD;
};

#endif

