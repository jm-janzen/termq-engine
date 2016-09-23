#include <stdlib.h>

#include "../game.h"
#include "Actor.h"
#include "Enemy.h"

Enemy::Enemy() {
    setChar('X');

    int_fast8_t randx = (rand() % (game_area.right())   + 1);
    int_fast8_t randy = (rand() % (game_area.bot()) + 1);
    setPos({ randx, randy });
};

vec2i Enemy::seek(Actor a) {
    vec2i selfPos   = this->getPos();
    vec2i targetPos = a.getPos();

    // Target on same row
    if (targetPos.x == selfPos.x) {
        // Target below
        if (targetPos.y > selfPos.y) { this->moveDown(); }
        // Target above
        if (targetPos.y < selfPos.y) { this->moveUp(); }
    }

    // Target on same col
    else if (targetPos.y == selfPos.y) {
        // Target right
        if (targetPos.x > selfPos.x) { this->moveRight(); }
        // Target left
        if (targetPos.x < selfPos.x) { this->moveLeft(); }
    }

    // Target diagonal
    else if (targetPos.x > selfPos.x) {
        this->moveRight();
        if (targetPos.y > selfPos.y) {
            this->moveDown();
        } else {
            this->moveUp();
        }

    } else {
        this->moveLeft();
        if (targetPos.y > selfPos.y) {
            this->moveDown();
        } else {
            this->moveUp();
        }
    }

    return this->getPos();
}
