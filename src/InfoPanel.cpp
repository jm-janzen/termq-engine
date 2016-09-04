#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>

#include "menu.h"
#include "InfoPanel.h"

InfoPanel::InfoPanel() {

    initscr();
    winfo = newwin(10, 80, 40 + 1, 1);
    box(winfo, 0, 0);
};

void InfoPanel::update() {
    wrefresh(winfo);
};

void InfoPanel::clear() {
    wmove(winfo, 1, 1);
    wrefresh(winfo);
    werase(winfo);
}

void InfoPanel::delete_w() {
    delwin(winfo);
}

void InfoPanel::push(std::string msg) {
    InfoPanel::clear();

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

void InfoPanel::setBounds(rect a) {
    bounds = a;
};

rect InfoPanel::getBounds() {
    return bounds;
};

