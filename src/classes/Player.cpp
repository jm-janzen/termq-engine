#include <stdlib.h>

#include "Actor.h"
#include "Player.h"
#include "Item.h"
#include "../global/Global.h"

Player::Player(Window &w) : Actor(&w) {
    setChar('@');

    setPosRand();
};


void Player::addItem(Item &i) {
    items.push_back(i);
};

int Player::getScore() {
    /*
     * TODO
     *  Return computed score - something like:
     *      score = (steps - ticks) + (coins / GameWorld::numCoins) * GameWorld::difficulty;
     *  rather than score simply reflecting the value
     *  of collected coins.
     */
    Global *g = Global::get();
    int computedScore = 0;
    for (Item &item : items) {
        score += item.getValue();  // XXX coin score not being added until game over
    }
    return (computedScore + getSteps() * g->getDifficulty());
}

