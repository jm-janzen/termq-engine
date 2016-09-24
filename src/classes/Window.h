#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <array>

#include "../game.h"

class Window {
    public:
        Window(rect dim); // ctor
       ~Window();         // dtor

        void bindWin(WINDOW *newW);

        int getChar();

        void refresh();
        void update();
        void clear();
        void close();

        void draw(vec2ui pos, char ch, chtype colo);
        void coloSplash(chtype colo);

    private:
        WINDOW *w;
        vec2ui dim;

};

#endif

