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

        void cursorPos(vec2ui pos);

        void draw(vec2ui pos, char ch, chtype colo);
        void write(std::string str);
        void coloSplash(chtype colo);

        rect getDim() { return dim; }

    protected:
        WINDOW *w;
        rect dim;

};

#endif

