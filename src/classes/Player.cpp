#include "Actor.h"
#include "Player.h"

Player::Player() {
    setChar('@');
    setPos({ 0, 0 });
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
