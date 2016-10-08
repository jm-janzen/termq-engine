#include <stdlib.h>

#include "Actor.h"
#include "Player.h"
#include "Item.h"
#include "../global/Global.h"

Player::Player(Window &w) : Actor(&w) {
    setChar('@');

    setPosRand();
}


void Player::addItem(Item &i) {
    items.push_back(i);
}

int Player::getScore() {
    Global *g = Global::get();
    int computedScore = 0;
    for (Item &item : items) {
        computedScore += item.getValue();
    }
    return (computedScore * g->getDifficulty() + getSteps());
}

