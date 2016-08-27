#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>

#include "game.h"
#include "Winfo.h"

Winfo::Winfo() {

    initscr();
    winfo = newwin(10, 80, 40 + 1, 1);
    box(winfo, 0, 0);
};

void Winfo::bindWindow(WINDOW& w) {
    winfo = &w;
};

void Winfo::update() {
    /* TODO refresh and display new messages */
    wrefresh(winfo);
};

void Winfo::clear() {
    wmove(winfo, 1, 1);
    wrefresh(winfo);
    werase(winfo);
}

void Winfo::delete_w() {
    delwin(winfo);
}

void Winfo::push(std::string msg) {
    /* TODO push new message line to info panel */
    box(winfo, 0, 0);
    wmove(winfo, 1, 1);
    wprintw(winfo, msg.c_str());
};

void Winfo::setBounds(rect a) {
    bounds = a;
};

rect Winfo::getBounds() {
    return bounds;
};

