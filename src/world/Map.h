#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include "../game.h"
#include "Cell.h"

using namespace std;

class Map {
    Map(Window *newW);

    void setCell(vec2ui vec, Cell cell);
    private:
        Window *w;
        //vector<Cell> cells;
        map<vec2ui, Cell> cells;
};

#endif
