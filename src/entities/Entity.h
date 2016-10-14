
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <cstdlib>
#include <ncurses.h>

#include "../directions.h"
#include "../game.h"

#include "../windows/Window.h"
#include "Entity.h"

class Entity {

    public:
        void render();

        // Check cardinal, intercardinal direction
        bool  isNorth(Entity &target);
        bool  isSouth(Entity &target);
        bool  isEast(Entity &target);
        bool  isWest(Entity &target);
        bool  isNorthEast(Entity &target);
        bool  isSouthEast(Entity &target);
        bool  isSouthWest(Entity &target);
        bool  isNorthWest(Entity &target);

        bool atop(vec2ui const targetPos);
        bool isAdjacent(vec2ui const targetPos);
        int_fast8_t getDistance(vec2ui const targetPos);
        int_fast8_t getDistanceX(vec2ui const targetPos);
        int_fast8_t getDistanceY(vec2ui const targetPos);

        void  setPosRand();
        void  setPos(vec2ui newPos);
        void  setChar(char newChar);
        void  setColo(chtype newColo);

        Direction getDirection(Entity &a);  // Get ray from self to target

        vec2ui getPos();
        char  getDispChar();
        int   getDispColo();

    protected:
        Window *w;  // TODO rm and place in Map
        vec2ui pos;
        char  disp_char;
        int   disp_colo;

        Direction direction = H;
};

#endif
