#include "Map.h"

Map::Map(Window *newW) {
    w = newW;
}

/**
 * Draw all entities in cells.
 */
void Map::draw() {
    w->update();
    for (auto const &c : cells) {
        vec2ui pos = c.second->getEntityPos();
        char   cha = c.second->getEntityChar();
        int    col = c.second->getEntityColo();
        w->draw(pos, cha, col);
    }
    w->refresh();
}

// FIXME return int key for pop reference?
void Map::push(Entity &e) {
    Cell *c = new Cell(e);  // XXX don't forget to clean up these ptrs !
    cells.insert(std::make_pair(++iter, c));
}

/**
 * Remove an Entity from within map by its equality.
 */
void Map::rm(Entity &e) {
    for (auto const &c : cells) {
        Entity t = c.second->getEntity();
        if (e == t) {
            cells.erase(c.first);
            break;
        }
    }
}

/**
 * Get Cell's entity at `key' and delete it.
 */
Entity Map::pop(int key) {
    auto i = cells.find(key)->first;
    Entity e = cells[i]->getEntity();
    cells.erase(i);

    return e;
}
