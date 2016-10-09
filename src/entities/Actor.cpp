#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <cmath>

#include "Actor.h"

Actor::Actor() {
    disp_colo = COLOR_PAIR(0);
}

int_fast8_t Actor::takeDMG(uint_fast8_t dmg) {
    attr.HP -= (getDEF()) + dmg;
    // TODO check if dead
    return -1;
}

void Actor::attack(Actor &a) {
    /*
     * TODO
     *  1) Compute chance of attack succeeding
     *  2) Compute damage done
     *  3) Send results to target Actor
     *
     *  Attacker unlucky = `miss'
     *  Defender lucky   = `dodge'
     */
    int_fast8_t dmg = a.takeDMG(getATK());
    dmg++; // XXX silence Wunused
}

void Actor::addTarget(Actor *a) {
    //printf("target added\n");
    //targets->push_back(a);
    target = a;
}

// TODO
bool Actor::hasTarget(vec2ui cell) {
    for (auto &t : *targets) {
        printf("%d,%d; %d,%d\n\r", t.getPos().x, t.getPos().y, cell.x, cell.y);
        *target = t;  // XXX this causes segfault?
        printf("target assigned\n");
    }
    return false;  // XXX temp
}

/*
 * Movement
 */

// TODO check for other actor here?
/*
 * TODO
 * XXX just one target for now
 * 1) check adjacent
 * 2) check direction (moving to?)
 * 3) don't move -- attack!
 */

void  Actor::moveWest() {
    if (pos.x > game_area.left()) {
        pos.x--;
        if (atop(target->getPos())) {
            pos.x++;
            printf("ATTACK!\n");
            attack(*target);
            if (target->getHP() <= 0) {
                target->setChar('x');
            }
        } else {
            move();
        }
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

