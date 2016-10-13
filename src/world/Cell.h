#ifndef CELL_H
#define CELL_H

#include "../game.h"
#include "../entities/Entity.h"

class Cell {
    private:
        /*
         * Use entity to derive pos, char, colo; other...
         */
        Entity *entity;
};

#endif
