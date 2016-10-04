#ifndef PLAYER_H
#define PLAYER_H

#include "../game.h"
#include "Actor.h"
#include "Item.h"

class Player : public Actor {
    public:
        Player(Window &w);

        void addItem(Item &i);

        int  getScore();
    private:
        std::vector<Item> items;
};

#endif

