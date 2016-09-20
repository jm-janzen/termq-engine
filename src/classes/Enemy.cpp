#include <stdlib.h>
#include <time.h>

#include "Actor.h"
#include "Enemy.h"

Enemy::Enemy() {
    setChar('X');
    srand(time(NULL));
    setPosX(rand() % 15 + 1);
    setPosY(rand() % 15 + 1);
};
