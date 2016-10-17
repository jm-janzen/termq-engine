#ifndef CELL_H
#define CELL_H

#include "../game.h"
#include "../entities/Entity.h"
#include <tr1/memory>

class Cell {
    public:
        Cell(Entity &e) : entity(e){};

        void addEntity(Entity &e);
        void rmEntity();

        Entity getEntity()     { return entity; }
        vec2ui getEntityPos()  { return entity.getPos(); }
        char   getEntityChar() { return entity.getDispChar(); }
        int    getEntityColo() { return entity.getDispColo(); }
    private:
        /*
         * Use entity to derive pos, char, colo; other...
         */
        // TODO maybe use a shared pointer here
        Entity &entity;
};

#endif
