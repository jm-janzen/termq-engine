#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <cmath>

#include "Entity.h"

void Entity::render(Window &w) {
    w.draw(getPos(), getDispChar(), getDispColo());
}

/*
 * Ray computation
 */

Direction Entity::getDirection(Entity &a) {  // TODO add ref to target to Entity class (from Enemy)
    int degrees = 0;

    vec2ui selfPos   = this->getPos();
    vec2ui targetPos = a.getPos();

    // Target is under me!
    if ( ! (selfPos == targetPos)) {
        float rads = atan2((selfPos.y - targetPos.y), (selfPos.x - targetPos.x));
        int degs   = static_cast<int>((rads * 180.0) / M_PI);

        if (degs < 0.0) degs += 360.0;

        degrees = degs;
    }

    return static_cast<Direction>(degrees);
}

/*
 * Comparison
 *  with other Entitys' positions
 */

bool Entity::isNorth(Entity &target) {
    return (getDirection(target) == N);
}
bool Entity::isSouth(Entity &target) {
    return (getDirection(target) == S);
}
bool Entity::isWest(Entity &target) {
    return (getDirection(target) == W);
}
bool Entity::isEast(Entity &target) {
    return (getDirection(target) == E);
}

bool  Entity::isNorthEast(Entity &target) {
    int d = getDirection(target);
    return (d > N && d < E);
}
bool  Entity::isSouthEast(Entity &target) {
    int d = getDirection(target);
    return (d > E && d < S);
}
bool  Entity::isSouthWest(Entity &target) {
    int d = getDirection(target);
    return (d > S && d > W);
}
bool  Entity::isNorthWest(Entity &target) {
    int d = getDirection(target);
    return (d > W && d < N);
}


bool Entity::atop(vec2ui const targetPos) {
    return (getPos() == targetPos);
}

bool Entity::isAdjacent(vec2ui const targetPos) {
    return (getDistanceX(targetPos) <= 1 && getDistanceY(targetPos) <= 1);
}

int_fast8_t Entity::getDistance(vec2ui const targetPos) {
    return sqrt(
        std::pow(getDistanceY(targetPos), 2) + std::pow(getDistanceX(targetPos), 2)
    );
}

int_fast8_t Entity::getDistanceX(vec2ui const targetPos) {
    int_fast8_t result;

    // Check for greatest unsigned value
    if (getPos().x > targetPos.x) {
        result = std::abs(getPos().x - targetPos.x);
    } else {
        result = std::abs(targetPos.x - getPos().x);
    }

    return result;
}

int_fast8_t Entity::getDistanceY(vec2ui const targetPos) {
    return std::abs(getPos().y - targetPos.y);
}

/*
 * Setters
 */

void Entity::setPos(vec2ui newPos) {
    pos = newPos;
}

void Entity::setPosRand() {
    uint_fast8_t randx = (rand() % (game_area.right() -1) + 1);
    uint_fast8_t randy = (rand() % (game_area.bot()   -1) + 1);
    setPos({ randx, randy });
}

void Entity::setColo(chtype newColo) {
    disp_colo = newColo;
}

void Entity::setChar(char newChar) {
    disp_char = newChar;
}

/*
 * Getters
 */

vec2ui Entity::getPos() {
    return pos;
}

char Entity::getDispChar() {
    return disp_char;
}

int Entity::getDispColo() {
    return disp_colo;
}

