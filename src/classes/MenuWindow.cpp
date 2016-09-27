#include <string>

#include "../game.h"
#include "MenuWindow.h"

template <typename T,unsigned S>
inline unsigned array_size(const T (&v)[S]) { return S; }

MenuWindow::MenuWindow(rect dim) : Window(dim) {
    wborder(w,
        ACS_BULLET, ACS_BULLET, ACS_BULLET, ACS_BULLET,     /* ls, rs, ts, bs */
        '+', '+', '+', '+'                                  /* tl, tr, bl, br */
    );
};

uint8_t MenuWindow::updateMenu() {
    for (int i = 0; i < noItems; i++) {
        if (i == 0) wattron(w, A_STANDOUT);
        else wattroff(w, A_STANDOUT);

        write({3, static_cast<uint_fast8_t>(i + 1)}, menuItems[i]);
    }
    return position;
};

uint8_t MenuWindow::updateMenu(int newPosition) {
    for (int i = 0; i < noItems; i++) {
        if (i == newPosition) wattron(w, A_STANDOUT);
        else wattroff(w, A_STANDOUT);

        write({3, static_cast<uint_fast8_t>(i + 1)}, menuItems[i]);
    }
    return position;
};

void MenuWindow::add(std::string item) {
    menuItems.push_back(item);
    noItems++;
};

std::string MenuWindow::getSelection() {
    int ch, noElements, idx;
    bool itemSelected = false;
    while ( ! itemSelected) {

        ch = wgetch(w);

        switch (ch) {
            case KEY_UP:
            case 56:
            case 'k':
                position--;
                break;
            case KEY_DOWN:
            case 50:
            case 'j':
                position++;
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                itemSelected = true;
                break;

        }

        // TODO put these in method(s)
        idx        = (position % menuItems.size());
        selection  = menuItems[idx];

        updateMenu(idx);
    }

    return selection;
};

