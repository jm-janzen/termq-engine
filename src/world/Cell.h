#ifndef CELL_H
#define CELL_H

#include "../game.h"
#include "../entities/Entity.h"

class Cell {
    public:
        Cell();
        Cell(Entity *e) { entity = e; }
        void addEntity(Entity *e);
        void rmEntity();

        /*
         * TODO guard against nullptr entity
         */
        Entity getEntity();
        vec2ui getEntityPos();
        char   getEntityChar();
        int    getEntityColo();
    private:
        /*
         * Use entity to derive pos, char, colo; other...
         */
        Entity *entity;
        // XXX probably does not need `pos' key (this is held in Map)
};

#endif
