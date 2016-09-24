#include <stdio.h>
#include <cmath>

#include "Actor.h"

/*
 * Comparison
 *  with other Actors' positions
 */

bool Actor::atop(vec2i const targetPos) {
    return (getPos() == targetPos);
};

bool Actor::isAdjacent(vec2i const targetPos) {
    return (getDistanceX(targetPos) <= 1 && getDistanceY(targetPos) <= 1);
};

int_fast8_t Actor::getDistance(vec2i const targetPos) {
    return sqrt(
        std::pow(getDistanceY(targetPos), 2) + std::pow(getDistanceX(targetPos), 2)
    );
};

int_fast8_t Actor::getDistanceX(vec2i const targetPos) {
    return std::abs(getPos().x - targetPos.x);
};

int_fast8_t Actor::getDistanceY(vec2i const targetPos) {
    return std::abs(getPos().y - targetPos.y);
};

/*
 * Movement
 */

void  Actor::moveLeft() {
    move();
    pos.x--;
};

void  Actor::moveRight() {
    move();
    pos.x++;
};

void  Actor::moveUp() {
    move();
    pos.y--;
};

void  Actor::moveDown() {
    move();
    pos.y++;
};

void Actor::wait() {
    tick();
}

void Actor::move() {
    tick();
    step();
}

void Actor::step() {
    steps++;
}

void Actor::tick() {
    ticks++;
}

/*
 * Setters
 */

void Actor::setPos(vec2i newPos) {
    pos = newPos;
};

void Actor::setChar(char newChar) {
    disp_char = newChar;
};

/*
 * Getters
 */

vec2i Actor::getPos() {
    return pos;
}

char Actor::getDispChar() {
    return disp_char;
}

