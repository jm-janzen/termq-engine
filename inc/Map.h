#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include "game.h"
#include "Window.h"
#include "Actor.h"
#include "Cell.h"

using namespace std;

class Map {
    public:
        Map(Window *newW);
       ~Map();

        void draw();

        void setCell(vec2ui vec, Cell cell);
        void push(Entity &e);
        void rm(Entity &e);
        Entity pop(int key);

        bool checkCell(vec2ui const vec, std::string type);
        Entity getEntity(vec2ui const vec);
    private:
        Window *w;
        map<int, Cell*> cells;
        int iter = 0;

};

#endif
