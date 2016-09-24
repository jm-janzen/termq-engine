#include <stdlib.h>

#include "Actor.h"
#include "Player.h"

Player::Player(Window &w) : Actor(&w) {
    setChar('@');

    int_fast8_t randx = (rand() % (game_area.right())   + 1);
    int_fast8_t randy = (rand() % (game_area.bot()) + 1);
    setPos({ randx, randy });
};

void Player::addScore(int newScore) {
    score += newScore;
}

int Player::getScore() {
    return score;
}

void Player::setScore(int newScore) {
    score = newScore;
}
