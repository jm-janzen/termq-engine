
#include "Actor.h"

/*
 * Comparison
 *  with other Actors' positions
 */

bool Actor::atop(vec2i const targetPos) {
    return (getPos() == targetPos);
};

// TODO check if two points are within a unit of each other.  Maybe yagni...
bool Actor::checkAdjacent(vec2i targetPos) {
    return false;
};

// TODO get absolute minimum distance between two points. Maybe yagni...
int_fast8_t Actor::getDistance(vec2i targetPos) {
    return 0;
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

