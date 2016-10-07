#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "Window.h"
#include "../menu.h"
#include "../global/difficulty-levels.h"

class MenuWindow : public Window {
    public:
        MenuWindow(rect dim);

        void         updateMenu();
        void         updateMenu(int newSelection);

        std::string  getSelection();
        void         setPosition(int newPosition);
        void         add(std::string item);
    private:
        std::vector<std::string> menuItems;
        uint8_t noItems       = 0;
        uint8_t position      = 0;
        std::string selection = "";
};

#endif

