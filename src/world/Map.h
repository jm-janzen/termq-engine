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

        void draw();

        void setCell(vec2ui vec, Cell cell);
        void push(Entity &e);
        void rm(Entity &e);
        Entity pop(int key);
    private:
        Window *w;
        map<int, Cell*> cells;
        int iter = 0;

};

#endif
