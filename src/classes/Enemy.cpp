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

/*
 * TODO
 *  Move toward target actor, rather
 *  than simply to the passed coordinates
 */
vec2i Enemy::seek(Actor a) {
    // XXX just send back Actor target coords for now
    vec2i targetPos = a.getPos();
    vec2i newPos = {
        targetPos.x, targetPos.y
    };
    return newPos;
}
