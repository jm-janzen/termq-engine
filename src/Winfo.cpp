#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>

#include "game.h"
#include "Winfo.h"

Winfo::Winfo() {
}

void Winfo::bindWindow(WINDOW& w) {
    winfo = w;
}

void Winfo::update() {
    /* TODO refresh and display new messages */
    wrefresh(&winfo);
};
void Winfo::push(std::string msg) {
    /* TODO push new message line to info panel */
}

void Winfo::setBounds(rect a) {
    bounds = a;
};

rect Winfo::getBounds() {
    return bounds;
};

