#include <stdlib.h>

#include "Actor.h"
#include "Player.h"
#include "Item.h"
#include "../global/Global.h"

Player::Player() : Actor() {
    init_pair(0, COLOR_WHITE, -1);
    setColo(COLOR_PAIR(0));
    setChar('@');
    setType("Player");
    setName("Noop");

    attr.LCK = (rand() % 3);  // Player luck 0 to 3

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

