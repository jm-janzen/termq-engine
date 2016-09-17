
#include "Actor.h"

void Actor::setPos(vec2i newPos) {
    pos = newPos;
};

void Actor::setPosX(int_fast8_t newXPos) {
    pos.x = newXPos;
};

void Actor::setPosY(int_fast8_t newYPos) {
    pos.y = newYPos;
};

void Actor::setChar(char newChar) {
    disp_char = newChar;
};

vec2i Actor::getPos() {
    return pos;
}

char Actor::getDispChar() {
    return disp_char;
}

