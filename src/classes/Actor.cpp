
#include "Actor.h"

/*
 * Comparison
 *  with other Actors' positions
 */

bool Actor::atop(vec2i targetPos) {
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
    pos.x--;
};

void  Actor::moveRight() {
    pos.x++;
};

void  Actor::moveUp() {
    pos.y--;
};

void  Actor::moveDown() {
    pos.y++;
};

/*
 * Setters
 */

void Actor::setPos(vec2i newPos) {
    pos = newPos;
};

void Actor::setPosX(int_fast8_t newXPos) {
    pos.x = newXPos;
};

void Actor::setPosY(int_fast8_t newYPos) {
    pos.y = newYPos;
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

