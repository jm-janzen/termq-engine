
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <cstdlib>
#include <ncurses.h>

#include "../directions.h"
#include "../game.h"

#include "../windows/Window.h"

class Actor {
    public:

        Actor() {};
        Actor(Window *newW);

        void render();

        bool atop(vec2ui const targetPos);
        bool isAdjacent(vec2ui const targetPos);
        int_fast8_t getDistance(vec2ui const targetPos);
        int_fast8_t getDistanceX(vec2ui const targetPos);
        int_fast8_t getDistanceY(vec2ui const targetPos);

        void  moveNorth();
        void  moveNorthEast();
        void  moveEast();
        void  moveSouthEast();
        void  moveSouth();
        void  moveSouthWest();
        void  moveWest();
        void  moveNorthWest();


        // Check cardinal direction
        bool  isNorth(Actor &target);
        bool  isSouth(Actor &target);
        bool  isEast(Actor &target);
        bool  isWest(Actor &target);

        // Returns ranges between cardinal directions
        bool  isNorthEast(Actor &target);
        bool  isSouthEast(Actor &target);
        bool  isSouthWest(Actor &target);
        bool  isNorthWest(Actor &target);

        Direction getDirection(Actor &a);  // Get ray from self to target

        void  wait();
        void  move();
        void  tick();
        void  step();

        void  setPosRand();
        void  setPos(vec2ui newPos);
        void  setChar(char newChar);
        void  setColo(chtype newColo);

        vec2ui getPos();
        char  getDispChar();
        int   getDispColo();
        int   getSteps() { return steps; }
        int   getTicks() { return ticks; }

    protected:
        vec2ui pos;
        char  disp_char;
        int   disp_colo;
        int   steps = 0;
        int   ticks = 0;
        Window *w;

        Direction direction = H;
};

#endif

