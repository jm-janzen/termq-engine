#include "Map.h"

Map::Map(Window *newW) {
    w = newW;
}

void Map::draw() {
    // POC TODO get map to draw contents of cells
    init_pair(6, COLOR_YELLOW, -1);
    w->draw({0,0}, 'J');
    w->refresh();

    vec2ui pos;
    auto it = cells.begin();
    for (auto const &v: cells) {
        pos = it->first;
    }
}

void Map::setCell(vec2ui vec, Cell cell) {
    cells[vec] = cell;
}

void Map::adds(Entity *e) {
    vec2ui v = e->getPos();
    cells[v] = Cell(e);
}
