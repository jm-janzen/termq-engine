#include <ncurses.h>
#include <array>

#ifndef INFOPANEL_H
#define INFOPANEL_H

class InfoPanel {
    public:
        InfoPanel(); // ctor

        void update();
        void clear();
        void delete_w();

        void push(std::string);

        void setBounds(rect);
        rect getBounds();
    private:
        rect bounds; // see game.h
        WINDOW *winfo;

        int cursor_pos = 0;
        std::array<std::string, 9> messages;
};

#endif

