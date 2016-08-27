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

    /*
     * increment cursor position, push old messages up
     */
    if (cursor_pos < messages.max_size() - 1) {
        cursor_pos++;
    } else {
        for (int i = 0; i < messages.max_size() - 1; i++) {
            messages[i] = messages[i + 1];
        }
    }

    messages[cursor_pos] = msg;

    /*
     * rewrite lines from top to bot
     */
    for (int i = 1; i < messages.max_size(); i++) {
        wmove(winfo, i, 1);
        wprintw(winfo, messages[i].c_str());
    }


    /*
     * place a box around info panel and signal changes
     */
    box(winfo, 0, 0);
    wrefresh(winfo);
};

void Winfo::setBounds(rect a) {
    bounds = a;
};

rect Winfo::getBounds() {
    return bounds;
};

