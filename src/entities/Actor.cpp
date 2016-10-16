#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <cmath>

#include "Actor.h"

Actor::Actor() {
    disp_colo = COLOR_PAIR(0);
}

/*
 * Movement
 */

void  Actor::moveWest() {
    if (pos.x > game_area.left()) {
        pos.x--;
        move();
    }
}

void  Actor::moveEast() {
    if (pos.x < game_area.right() - 1) {
        pos.x++;
        move();
    }
}

void  Actor::moveNorth() {
    if (pos.y > game_area.top()) {
        pos.y--;
        move();
    }
}

void  Actor::moveSouth() {
    if (pos.y < game_area.bot() - 1) {
        pos.y++;
        move();
    }
}

void  Actor::moveNorthEast() {
    if (pos.x < game_area.right() -1 && pos.y > game_area.top()) {
        move();
        pos.x++;
        pos.y--;
    }
}
void  Actor::moveSouthEast() {
    if (pos.x < game_area.right() - 1 && pos.y < game_area.bot() - 1) {
        move();
        pos.x++;
        pos.y++;
    }
}
void  Actor::moveSouthWest() {
    if (pos.x > game_area.left() && pos.y < game_area.bot() - 1) {
        move();
        pos.x--;
        pos.y++;
    }
}
void  Actor::moveNorthWest() {
    if (pos.x > game_area.left() && pos.y > game_area.top()) {
        move();
        pos.x--;
        pos.y--;
    }
}

void Actor::wait() {
    tick();
}

// TODO maybe check other Actor here, and move back ?
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

