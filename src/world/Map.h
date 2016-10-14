#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include "../game.h"
#include "../windows/Window.h"
#include "Cell.h"

using namespace std;

class Map {
    public:
        Map(Window *newW);

        void draw();  // TODO draw contents of cells to w

        void setCell(vec2ui vec, Cell cell);
        void adds(Entity *e);
    private:
        Window *w;
        map<vec2ui, Cell> cells;

};

#endif
