#include <stdio.h>
#include <ncurses.h>
#include <cmath>

#include "Actor.h"

Actor::Actor(WINDOW *newW) {
    initscr();
    w = newW;

    // Set default color (white foreground)
    init_pair(0, COLOR_WHITE, -1);
    disp_colo = COLOR_PAIR(0);
}

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
    wmove(w, getPos().y, getPos().x);
    waddch(w, getDispChar() | disp_colo);
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

