#include <stdlib.h>
#include <ncurses.h>

#include "../game.h"
#include "Actor.h"
#include "Enemy.h"

Enemy::Enemy(Window &w) : Actor(&w) {
    setChar('X');
    init_pair(1, COLOR_RED, -1);
    disp_colo = COLOR_PAIR(1);

    int_fast8_t randx = (rand() % (game_area.right() -1) + 1);
    int_fast8_t randy = (rand() % (game_area.bot()   -1) + 1);
    setPos({ randx, randy });
};

vec2ui Enemy::seek(Actor a) {
    vec2ui selfPos   = this->getPos();
    vec2ui targetPos = a.getPos();

    // Target on same row
    if (targetPos.x == selfPos.x) {
        // Target below
        if (targetPos.y > selfPos.y) { this->moveDown(); }
        // Target above
        if (targetPos.y < selfPos.y) { this->moveUp(); }
    }

    // Target on same col
    else if (targetPos.y == selfPos.y) {
        // Target right
        if (targetPos.x > selfPos.x) { this->moveRight(); }
        // Target left
        if (targetPos.x < selfPos.x) { this->moveLeft(); }
    }

    // Target diagonal
    else if (targetPos.x > selfPos.x) {
        this->moveRight();
        if (targetPos.y > selfPos.y) {
            this->moveDown();
        } else {
            this->moveUp();
        }

    } else {
        this->moveLeft();
        if (targetPos.y > selfPos.y) {
            this->moveDown();
        } else {
            this->moveUp();
        }
    }

    return this->getPos();
}
