#ifndef ITEM_H
#define ITEM_H

#include "../game.h"
#include "Entity.h"

enum Ownership {
    PLAYER, WORLD,
};

class Item : public Entity {
    public:

        void  setValue(int newValue);
        int   getValue();

        void      setOwnership(Ownership own) { ownership = own; }
        Ownership getOwnership() { return ownership; }

    protected:
        uint_fast16_t value;
        Ownership ownership = WORLD;
};

#endif

