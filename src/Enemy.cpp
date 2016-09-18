#include <stdlib.h>

#include "Actor.h"
#include "Enemy.h"

Enemy::Enemy() {
    setChar('X');
    setPosX(rand() % 15 + 1);
    setPosY(rand() % 15 + 1);
};
