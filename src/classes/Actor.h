
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <ncurses.h>

#include "../directions.h"
#include "../game.h"

#include "Window.h"

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


        /*
         * TODO
         *  Add move diagonal methods, as presently these
         *  count as _two_ moves by the Actor.
         */
        void  moveLeft();
        void  moveRight();
        void  moveUp();
        void  moveDown();

        bool  isNorth(Actor &target);
        bool  isSouth(Actor &target);
        bool  isEast(Actor &target);
        bool  isWest(Actor &target);

        // Returns ranges between cardinal directions
        bool  isNorthEast(Actor &target);
        bool  isSouthEast(Actor &target);
        bool  isSouthWest(Actor &target);
        bool  isNorthWest(Actor &target);

        Direction getDirection(Actor &a);  // Get ray from previous two vectors

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

        // TODO history of own previous moves
        std::vector<vec2ui> footsteps;

        Direction direction = H;
};

#endif

