#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <cmath>

#include "Actor.h"

Actor::Actor(Window *newW) {
    w = newW;
    disp_colo = COLOR_PAIR(0);
}

/*
 * Ray computation
 */

Direction Actor::getDirection(Actor &a) {  // TODO add ref to target to Actor class (from Enemy)
    int degrees = 0;

    vec2ui selfPos   = this->getPos();
    vec2ui targetPos = a.getPos();

    // Target is under me!
    if ( ! (selfPos == targetPos)) {
        float rads = atan2((selfPos.y - targetPos.y), (selfPos.x - targetPos.x));
        int degs   = static_cast<int>((rads * 180.0) / M_PI);

        if (degs < 0.0) degs += 360.0;

        //printf("rads: %f, degs: %d  \n", rads, degs);

        degrees = degs;
    }

    return static_cast<Direction>(degrees);
}

/*
 * Comparison
 *  with other Actors' positions
 */

bool Actor::isNorth(Actor &target) {
    return (getDirection(target) == N);
}
bool Actor::isSouth(Actor &target) {
    return (getDirection(target) == S);
}
bool Actor::isWest(Actor &target) {
    return (getDirection(target) == W);
}
bool Actor::isEast(Actor &target) {
    return (getDirection(target) == E);
}

bool  Actor::isNorthEast(Actor &target) {
    int d = getDirection(target);
    return (d > N && d < E);
};
bool  Actor::isSouthEast(Actor &target) {
    int d = getDirection(target);
    return (d > E && d < S);
};
bool  Actor::isSouthWest(Actor &target) {
    int d = getDirection(target);
    return (d > S && d > W);
};
bool  Actor::isNorthWest(Actor &target) {
    int d = getDirection(target);
    return (d > W && d < N);
};


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

void Actor::setPosRand() {
    int_fast8_t randx = (rand() % (game_area.right() -1) + 1);
    int_fast8_t randy = (rand() % (game_area.bot()   -1) + 1);
    setPos({ static_cast<uint_fast8_t>(randx), static_cast<uint_fast8_t>(randy) });
};

void Actor::setColo(chtype newColo) {
    disp_colo = newColo;
}

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

