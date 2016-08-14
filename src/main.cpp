#include <ncurses.h>

#include <string>

using namespace std;

void menuShow(string title);
void menuAdd(int pos, string str);
void menuDone();


int main() {

    /*
     * init term
     */

    initscr();
    cbreak();
    noecho();
    clear();

    /*
     * init title
     */
    menuShow("TERMINAL QUEST");

    refresh();
    while(true);

    /*
     * exit
     */

    return 0;
}

void menuShow(string title) {

    move(5, 5); // move cursor to (x,y)

    for (size_t i = 0; i < title.size(); i++) {
        addch(title[i]);
        addch(' ');
    }

    menuAdd(1, "start");
    menuAdd(2, "quit");
    menuDone();

    refresh();

    while(1);
}

void close() {
    endwin();
}

// Private functions

void menuAdd(int pos, string str) {
    if (pos > 0 && str.length() > 0) {
        move((pos + 6), 8);
        addstr(str.c_str());
    }
}

void menuDone() {
    move(7, 6);
}
