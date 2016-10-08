#include <stdlib.h>
#include <ncurses.h>

#include "../global/Global.h"

#include "../game.h"
#include "Actor.h"
#include "Enemy.h"

// Who is my enemy?
Enemy::Enemy(Actor &a) : Actor() {
    setChar('X');
    setType("Enemy");
    init_pair(1, COLOR_RED, -1);
    disp_colo = COLOR_PAIR(1);

    target = &a;
    computeAggro();
    setPosRand();
}

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
    // NB: `modifier' in `pool' chance of being `lucky'

    int modifier = (100 - getDistance(target->getPos()) * 4.2);
    if (modifier < 0) modifier = 0;  // Clamp

    int pool     = (100 + target->getChance() - g->getDifficulty());
    int roll     = (rand() % pool);
    bool lucky   = (roll < modifier);

    // Check if target is within range
    if (getDistance(target->getPos()) <= 1) {
        setPos(target->getPos());
    } else if (getDistance(target->getPos()) <= aggro) {
        // If target unlucky, seek
        if (lucky) seek();
    } else {
        mill();
    }
}

void Enemy::mill() {
    switch(rand() % 20) {
        case 1:
            moveNorth();
            break;
        case 2:
            moveNorthEast();
            break;
        case 3:
            moveEast();
            break;
        case 4:
            moveSouthEast();
            break;
        case 5:
            moveSouth();
            break;
        case 6:
            moveSouthWest();
            break;
        case 7:
            moveWest();
            break;
        case 8:
            moveNorthWest();
            break;
        default:
            break;
    }
}

vec2ui Enemy::seek() {

    // Target above, below, left, or right of me
    if (isSouth(*target)) {
        this->moveSouth();
    } else if (isNorth(*target)) {
        this->moveNorth();
    } else if (isEast(*target)) {
        this->moveEast();
    } else if (isWest(*target)) {
        this->moveWest();
    }

    // Target diagonal to me
    else if(isNorthEast(*target)) {
        this->moveNorthEast();
    } else if(isSouthEast(*target)) {
        this->moveSouthEast();
    } else if(isSouthWest(*target)) {
        this->moveSouthWest();
    } else {
        this->moveNorthWest();
    }

    return this->getPos();
}
