#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include "Actor.h"
#include "Enemy.h"
#include "Item.h"

class Player : public Actor {
    public:
        Player();

        void addItem(Item &i);
        std::vector<Item> getItems() { return items; }

        int  getScore();
    private:
        std::vector<Item> items;
};

#endif

