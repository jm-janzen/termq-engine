#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <cmath>

#include "Actor.h"

Actor::Actor() {
    disp_colo = COLOR_PAIR(0);
}

// TODO implement chance to block
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
    drainST(10);
    int_fast8_t dmgDealt = a.defend(getATK());
    if (dmgDealt == -1) {  // Target is dead
        target = NULL;
        messages[++lastMessage] = getType() + " " + getName() + " kills " + a.getType();
    } else {
        messages[++lastMessage] = getType() + " " + getName()
            + " attacks " + a.getType() + " for "
            + std::to_string(dmgDealt) + " damage";
    }
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
        if (move()) pos.x--;
    }
}

void  Actor::moveEast() {
    if (pos.x < game_area.right() - 1) {
        if (move()) pos.x++;
    }
}

void  Actor::moveNorth() {
    if (pos.y > game_area.top()) {
        if (move()) pos.y--;
    }
}

void  Actor::moveSouth() {
    if (pos.y < game_area.bot() - 1) {
        if (move()) pos.y++;
    }
}

void  Actor::moveNorthEast() {
    if (pos.x < game_area.right() -1 && pos.y > game_area.top()) {
        if (move()) {
            pos.x++;
            pos.y--;
        }
    }
}
void  Actor::moveSouthEast() {
    if (pos.x < game_area.right() - 1 && pos.y < game_area.bot() - 1) {
        if (move()) {
            pos.x++;
            pos.y++;
        }
    }
}
void  Actor::moveSouthWest() {
    if (pos.x > game_area.left() && pos.y < game_area.bot() - 1) {
        if (move()) {
            pos.x--;
            pos.y++;
        }
    }
}
void  Actor::moveNorthWest() {
    if (pos.x > game_area.left() && pos.y > game_area.top()) {
        if (move()) {
            pos.x--;
            pos.y--;
        }
    }
}

void Actor::wait() {
    // Prevent stamina from rising above 100
    if (getST() > 95) {
        attr.ST += (getST() - 100) * -1;
    } else if (getST() < 100) {
        attr.ST += 5;
    }
    tick();
}

/**
 * If have stamina move/attack,
 * else do nothing.
 *
 * Return bool canMove
 */
bool Actor::move() {
    tick();
    if (getST() > 0) step();

    return (getST() > 0);
}

void Actor::step() {
    if (getST() > 50) {
        drainST(1);
    }
    steps++;
}

void Actor::tick() {
    ticks++;
}

