
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>

#include "../game.h"
#include "Window.h"

/**
 * rect: {
 *   { top   , left   }
 *   { width , height }
 * }
 */
Window::Window(rect dim) {
    w = newwin(dim.height(), dim.width(), dim.offset.x, dim.offset.y);
    initscr();
    start_color();
    use_default_colors();
    box(w, 0, 0);
    keypad(w, true);
};

Window::~Window() {
    delwin(w);
};

void Window::cursorPos(vec2ui pos) {
    wmove(w, pos.y, pos.x);
};

void Window::draw(vec2ui pos, char ch, chtype colo) {
    wmove(w, pos.y, pos.x);
    waddch(w, ch | colo);
};

void Window::write(std::string str) {
    wprintw(w, str.c_str());
};
void Window::write(vec2ui pos, std::string str) {
    mvwprintw(w, pos.y, pos.x, str.c_str());
};

void Window::coloSplash(chtype colo) {
    wbkgd(w, colo);
};

int Window::getChar() {
    return wgetch(w);
}

/*
 * NB:
 *      Do _NOT_ call `wrefresh(w)' directly within derived
 *      classed - use this instead!
 */
void Window::refresh() {
    wrefresh(w);
};

void Window::update() {
    werase(w);
    box(w, 0, 0);
};

void Window::clear() {
    werase(w);
};

