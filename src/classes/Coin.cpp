#include <stdlib.h>
#include <time.h>

#include "Item.h"
#include "Coin.h"
#include "../game.h"

Coin::Coin() {
    setChar('o');
    setValue(100);

    srand(time(NULL));  // Init random seed
    int_fast8_t randx = (rand() % 15 + 1);
    int_fast8_t randy = (rand() % 15 + 1);
    setPos({ randx, randy });
};
