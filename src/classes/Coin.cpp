#include <stdlib.h>
#include <time.h>

#include "Item.h"
#include "Coin.h"
#include "../game.h"

Coin::Coin() {
    setChar('o');
    setValue(100);

    int_fast8_t randx = (rand() % (game_area.right() -1) + 1);
    int_fast8_t randy = (rand() % (game_area.bot()   -1) + 1);
    setPos({ randx, randy });
};
