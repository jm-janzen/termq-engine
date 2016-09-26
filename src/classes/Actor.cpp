#include <stdio.h>
#include <ncurses.h>
#include <cmath>

#include "Actor.h"

Actor::Actor() {
}

Actor::Actor(Window *newW) {
    w = newW;
    disp_colo = COLOR_PAIR(0);
}

/*
 * Comparison
 *  with other Actors' positions
 */

bool Actor::atop(vec2ui const targetPos) {
    return (getPos() == targetPos);
};

bool Actor::isAdjacent(vec2ui const targetPos) {
    return (getDistanceX(targetPos) <= 1 && getDistanceY(targetPos) <= 1);
};

int_fast8_t Actor::getDistance(vec2ui const targetPos) {
    return sqrt(
        std::pow(getDistanceY(targetPos), 2) + std::pow(getDistanceX(targetPos), 2)
    );
};

int_fast8_t Actor::getDistanceX(vec2ui const targetPos) {
    int_fast8_t result;

    // Check for greatest unsigned value
    if (getPos().x > targetPos.x) {
        result = std::abs(getPos().x - targetPos.x);
    } else {
        result = std::abs(targetPos.x - getPos().x);
    }

    return result;
};

int_fast8_t Actor::getDistanceY(vec2ui const targetPos) {
    return std::abs(getPos().y - targetPos.y);
};

/*
 * Movement
 */

void  Actor::moveLeft() {
    pos.x--;
    move();
};

void  Actor::moveRight() {
    pos.x++;
    move();
};

void  Actor::moveUp() {
    pos.y--;
    move();
};

void  Actor::moveDown() {
    pos.y++;
    move();
};

void Actor::wait() {
    tick();
}

void Actor::move() {
    tick();
    step();
}

void Actor::render() {
    w->draw(getPos(), getDispChar(), getDispColo());
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

void Actor::setPos(vec2ui newPos) {
    pos = newPos;
};

void Actor::setChar(char newChar) {
    disp_char = newChar;
};

/*
 * Getters
 */

vec2ui Actor::getPos() {
    return pos;
}

char Actor::getDispChar() {
    return disp_char;
}

int Actor::getDispColo() {
    return disp_colo;
}

