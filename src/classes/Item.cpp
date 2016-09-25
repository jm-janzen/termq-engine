#include "Item.h"

void Item::setPos(vec2ui newPos) {
    pos = newPos;
};

void Item::setChar(char newChar) {
    disp_char = newChar;
};

vec2ui Item::getPos() {
    return pos;
}

char Item::getDispChar() {
    return disp_char;
}

int Item::getValue() {
    return value;
}

void Item::setValue(int newValue) {
    value = newValue;
}

