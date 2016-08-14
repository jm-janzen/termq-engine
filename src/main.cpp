#include <ncurses.h>

#include <string>

int main() {

    /*
     * init term
     */

    initscr();
    cbreak();
    noecho();
    clear();

    return 0;
}

