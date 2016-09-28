#include <stdlib.h>

#include "Actor.h"
#include "Player.h"

Player::Player(Window &w) : Actor(&w) {
    setChar('@');

    setPosRand();
};

void Player::addScore(int newScore) {
    score += newScore;
}

int Player::getScore() {
    /*
     * TODO
     *  Return computed score - something like:
     *      score = (steps - ticks) + (coins / GameWorld::numCoins) * GameWorld::difficulty;
     *  rather than score simply reflecting the value
     *  of collected coins.
     */
    return score;
}

void Player::setScore(int newScore) {
    score = newScore;
}
