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
     * TODO
     *  1) Compute chance of attack succeeding
     *  2) Compute damage done
     *  3) Send results to target Actor
     *
     *  Attacker unlucky = `miss'
     *  Defender lucky   = `dodge'
     */
    int_fast8_t dmgDealt = a.defend(getATK());
    if (dmgDealt == -1) target = NULL;
}

void Actor::addTarget(Actor *a) {
    //printf("target added\n");
    //targets->push_back(*a);
    if (a) {
        target = a;
    }
}

// XXX garbage
//bool Actor::hasTarget(vec2ui cell) {
//    bool yes = false;
//    for (auto &t : *targets) {
//        printf("%d,%d; %d,%d\n\r", t.getPos().x, t.getPos().y, cell.x, cell.y);
//        if (cell == t.getPos()) {  // XXX segfault?
//            yes = true;
//            //*target = t;  // XXX this causes segfault?
//            printf("target assigned\n");
//        } else {
//
//            printf("no target\n");
//        }
//    }
//    return yes == true;
//}

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
        if (target == 0) {
            if (atop(target->getPos())) {
                pos.x++;
                attack(*target);

                if (target->getHP() <= 0) {
                    target->setChar('x');
                    target = 0;
                }
            }
        } else {
            move();
        }
    }
}

void  Actor::moveEast() {
    if (pos.x < game_area.right() - 1) {
        pos.x++;
        if (target) {
            if (target->getPos() == getPos()) {
                pos.x--;
                attack(*target);
            }
        }
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
    // TODO place attack checking logic here, and move to prev if actor ?
    tick();
    step();
}

void Actor::step() {
    steps++;
}

void Actor::tick() {
    ticks++;
}

