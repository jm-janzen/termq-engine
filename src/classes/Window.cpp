
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <string>

#include "../game.h"
#include "Window.h"

Window::Window(rect dim) {
    w = newwin(dim.height(), dim.width(), 1, 1);
    initscr();
    start_color();
    use_default_colors();
    box(w, 0, 0);
    keypad(w, true);
};

Window::~Window() {
    delwin(w);
};

void Window::draw(vec2ui pos, char ch, chtype colo) {
    wmove(w, pos.y, pos.x);
    waddch(w, ch | colo);
};

void Window::coloSplash(chtype colo) {
    wbkgd(w, colo);
};

int Window::getChar() {
    return wgetch(w);
}

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

