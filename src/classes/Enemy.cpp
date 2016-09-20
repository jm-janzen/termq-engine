#include <stdlib.h>
#include <time.h>

#include "Actor.h"
#include "Enemy.h"

Enemy::Enemy() {
    setChar('X');
    srand(time(NULL));  // Init random seed
    setPosX(rand() % 15 + 1);
    setPosY(rand() % 15 + 1);
};

vec2i Enemy::seek(Actor a) {
    vec2i selfPos   = this->getPos();
    vec2i targetPos = a.getPos();

    int_fast8_t newX = (targetPos.x >= selfPos.x) ? selfPos.x + 1 : selfPos.x - 1;
    int_fast8_t newY = (targetPos.y >= selfPos.y) ? selfPos.y + 1 : selfPos.y - 1;

    vec2i newPos = {
        newX, newY
    };
    this->setPos(newPos);

    return newPos;
}
