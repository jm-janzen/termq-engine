#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>
#include <string>
#include <array>

#include "../game.h"

// Used to define a datatype for calls to wborder
struct Border {
    chtype ls, rs, ts, bs;
    chtype tl, tr, bl, br;
};

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

        void draw(vec2ui pos, char ch);
        void draw(vec2ui pos, char ch, chtype colo);
        void draw(vec2ui pos, char ch, chtype colo, int attr);
        void drawBorder();
        void drawBox();
        void write(std::string str);
        void write(vec2ui pos, std::string str);
        void coloSplash(chtype colo);

        rect getDim() { return dim; }

        void setBorder(Border b);

    protected:
        WINDOW *w;
        rect dim;
        Border border = { 0,0,0,0,0,0,0,0 };  // Init to default

};

#endif

