#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "../menu.h"
#include "Window.h"

/*
 * TODO
 *  use rect dim to dynamically place elements
 *  if there is room
 */
class MenuWindow : public Window {
    public:
        MenuWindow(rect dim);

        uint8_t updateMenu();
        uint8_t updateMenu(int newSelection);

        std::string  getSelection();
        void    add(std::string item);
        void    up();
        void    down();
    private:
        std::string menuItems[3];  // XXX reflects noItems
        uint8_t noItems       = 0;
        std::string selection = "";
        uint8_t position      = 0;
};

#endif

