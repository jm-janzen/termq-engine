#include "Player.h"

Player::Player() {
    setChar('@');
    setPos({ 0, 0 });
};

void Player::setPos(vec2i newPos) {
    pos = newPos;
};

void Player::setPosX(int_fast8_t newXPos) {
    pos.x = newXPos;
};

void Player::setPosY(int_fast8_t newYPos) {
    pos.y = newYPos;
};

void Player::setChar(char newChar) {
    disp_char = newChar;
};

vec2i Player::getPos() {
    return pos;
}

char Player::getDispChar() {
    return disp_char;
}

