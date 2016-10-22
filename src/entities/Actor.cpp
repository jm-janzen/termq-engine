#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <cmath>

#include "Actor.h"

Actor::Actor() {
    disp_colo = COLOR_PAIR(0);
}

int_fast8_t Actor::defend(uint_fast8_t dmg) {
    int_fast8_t effectiveDMG = std::abs((getDEF()) + dmg);
    attr.HP -= effectiveDMG;

    if (attr.HP <= 0) {
        return -1;
    } else {
        return effectiveDMG;
    }
}

void Actor::attack(Actor &a) {
    /*
     * TODO Compute chance of attack succeeding
     *
     *  Attacker unlucky = `miss'
     *  Defender lucky   = `dodge'
     */
    int_fast8_t dmgDealt = a.defend(getATK());
    if (dmgDealt == -1) target = NULL;
}

void Actor::addTarget(Actor *a) {
    if (a) {
        target = a;
    }
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

