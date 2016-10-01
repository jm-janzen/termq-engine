#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "../game.h"
#include "../global/Global.h"

#include "Actor.h"
#include "Window.h"

//class Target : public Actor {};

class Enemy : public Actor {
    public:
        /*
         * NB:
         *  Here, we are preventing compiler from generating
         *  default ctor, so we need to implement it (ie: `{}`).
         */
        Enemy() {};
        Enemy(Window &w, Actor &a);

        void   computeAggro();

        void   move();
        void   mill();
        vec2ui seek();

    private:
        Global *g           = Global::get();
        Actor *target       = NULL;
        int aggro;

};

#endif

