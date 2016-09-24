#ifndef ENEMY_H
#define ENEMY_H

#include "../game.h"
#include "Actor.h"
#include "Window.h"

class Enemy : public Actor {
    public:
        Enemy(Window &w); // ctor

        vec2ui seek(Actor a);
};

#endif

