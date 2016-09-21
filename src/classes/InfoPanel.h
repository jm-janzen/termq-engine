#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <ncurses.h>
#include <array>

#include "../game.h"

class InfoPanel {
    public:
        InfoPanel(); // ctor

        void update();
        void clear();
        void delete_w();

        void push(std::string);

    private:
        WINDOW *winfo;

        int cursor_pos = 0;
        std::array<std::string, 9> messages;
};

#endif

