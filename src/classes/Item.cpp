#include "Item.h"

void Item::setPos(vec2i newPos) {
    pos = newPos;
};

vec2i Item::getPos() {
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

