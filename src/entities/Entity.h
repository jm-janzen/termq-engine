
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
        /**
         * Render this Entity explicitly to specific window.
         */
        void render(Window &w);

        bool operator==(Entity &e) {
            return (e.getPos() == getPos() && e.getDispChar() == getDispChar());
        }

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
        vec2ui pos      = {0, 0};
        char  disp_char = char(16);
        int   disp_colo = -1;

        Direction direction = H;
};

#endif
