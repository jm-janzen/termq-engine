#ifndef ENEMY_H
#define ENEMY_H

#include "../game.h"
#include "Actor.h"
#include "Window.h"

class Enemy : public Actor {
    public:
        /*
         * NB:
         *  Here, we are preventing compiler from generating
         *  default ctor, so we need to implement it (ie: `{}`).
         */
        Enemy() {};
        Enemy(Window &w);

        vec2ui seek(Actor a);
};

#endif

