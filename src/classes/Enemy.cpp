#include <stdlib.h>
#include <ncurses.h>

#include "../global/Global.h"

#include "../game.h"
#include "Actor.h"
#include "Enemy.h"

// Where am I drawn; who is my enemy?
Enemy::Enemy(Window &w, Actor &a) : Actor(&w) {
    setChar('X');
    init_pair(1, COLOR_RED, -1);
    disp_colo = COLOR_PAIR(1);

    target = &a;
    computeAggro();

    setPosRand();
};

void Enemy::computeAggro() {
    switch(g->getDifficulty()) {
        case CHEAT:
            aggro = 0;
            break;
        case EASY:
            aggro = 20;
            break;
        case MEDIUM:
            aggro = 30;
            break;
        case HARD:
            aggro = 50;
            break;
        case NIGHTMARE:
            aggro = 100;
            break;
    }
}

void Enemy::move() {
    // Check if target is within aggro range
    if (getDistance(target->getPos()) <= aggro) {
        targetAware = true;  // XXX unused
        seek();
    } else {
        mill();
    }
}

void Enemy::mill() {
    int targetDirection = getDirection(*target);
}

// TODO refactor to use getDirection
vec2ui Enemy::seek() {

    // Target above, below, left, or right of me
    if (isSouth(*target)) {
        this->moveDown();
    } else if (isNorth(*target)) {
        this->moveUp();
    } else if (isEast(*target)) {
        this->moveRight();
    } else if (isWest(*target)) {
        this->moveLeft();
    }

    // Target diagonal to me
    else if(isNorthEast(*target)) {
        this->moveRight();
        this->moveUp();
    } else if(isSouthEast(*target)) {
        this->moveRight();
        this->moveDown();
    } else if(isSouthWest(*target)) {
        this->moveDown();
        this->moveLeft();
    } else {
        this->moveUp();
        this->moveLeft();
    }

    return this->getPos();
}
