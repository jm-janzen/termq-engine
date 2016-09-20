#ifndef ENEMY_H
#define ENEMY_H

#include "../game.h"
#include "Actor.h"

class Enemy : public Actor {
    public:
        Enemy(); // ctor

        vec2i seek(Actor a);
};

#endif

