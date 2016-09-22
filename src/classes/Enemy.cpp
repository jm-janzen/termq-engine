#include <stdlib.h>

#include "Actor.h"
#include "Enemy.h"

Enemy::Enemy() {
    setChar('X');
    setPosX(rand() % 15 + 1);
    setPosY(rand() % 15 + 1);
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
