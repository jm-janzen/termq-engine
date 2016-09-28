#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "Window.h"
#include "../menu.h"
#include "../global/difficulty-levels.h"

/*
 * XXX bug repro
 *  1) select "options"
 *  2) select last option "nightmare"
 *  3) select "options" again
 *
 *  Result: bg and fg colour pair have swapped
 */

class MenuWindow : public Window {
    public:
        MenuWindow(rect dim);

        uint8_t updateMenu();
        uint8_t updateMenu(int newSelection);

        std::string  getSelection();
        void         setPosition(int newPosition);
        void    add(std::string item);
        void    up();
        void    down();
        void    clear();
    private:
        std::vector<std::string> menuItems;
        uint8_t noItems       = 0;
        uint8_t position      = 0;
        std::string selection = "";
        Border border = {
            ACS_BULLET, ACS_BULLET, ACS_BULLET, ACS_BULLET,
            '+', '+', '+', '+'
        };
};

#endif

