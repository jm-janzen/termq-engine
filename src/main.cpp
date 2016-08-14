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

    /*
     * init title
     */

    move(5, 5);
    std::string title = "TERMINAL QUEST";
    for (int i; i < title.size(); i++) {
        addch(title[i]);
        addch(' ');
    }

    refresh();
    while(true);

    /*
     * exit
     */

    return 0;
}

