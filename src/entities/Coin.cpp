#include <stdlib.h>
#include <time.h>

#include "Item.h"
#include "Coin.h"
#include "../game.h"

Coin::Coin() {
    switch(rand() % 3) {
        case 0:
            setChar('.');
            setValue(25);
            break;
        case 1:
            setChar('o');
            setValue(100);
            break;
        case 2:
            setChar('O');
            setValue(250);
            break;
    }

    setType("Coin");
    init_pair(2, COLOR_YELLOW, -1);
    setColo(COLOR_PAIR(2));
    setPosRand();
}
