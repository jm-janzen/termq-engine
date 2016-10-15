#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "../game.h"
#include "../global/Global.h"

#include "../windows/Window.h"
#include "Actor.h"

class Enemy : public Actor {
    public:
        /*
         * NB:
         *  Here, we are preventing compiler from generating
         *  default ctor, so we need to implement it (ie: `{}`).
         */
        Enemy() {}
        Enemy(Actor &a);

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

