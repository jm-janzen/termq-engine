#include "Map.h"

Map::Map(Window *newW) {
    this->w = newW;
}

void Map::setCell(vec2ui vec, Cell cell) {
    cells[vec] = cell;
}
