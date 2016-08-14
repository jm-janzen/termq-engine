#include <ncurses.h>

#include <string>

using namespace std;

void menuShow(string title);


int main(int argc, char **argv) {

    WINDOW *wmenu, *wmain;
    char menuItems[2][10] = {
        "start",
        "quit"
    };
    char menuItem[7];
    int ch, i = 0, width = 7;

    /*
     * init term
     */

    initscr();

    wmenu = newwin(10, 12, 10, 10);

    for (i = 0; i < 2; i++) {
        if (i == 0) wattron(wmenu, A_STANDOUT);
        else wattroff(wmenu, A_STANDOUT);

        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
    }

    /*
     * init title, menu
     */
    menuShow("TERMINAL QUEST");

    wrefresh(wmenu);
    i = 0;
    noecho();
    keypad(wmenu, true);
    curs_set(0);

    while (( ch = wgetch(wmenu)) != 'q') {
        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
        switch (ch) {
            case KEY_UP:
            case 'k':
                i--;
                i = (i < 0) ? 1 : i;
                break;
            case KEY_DOWN:
            case 'j':
                i++;
                i = (i > 1) ? 0: i;
                break;
        }
        wattron(wmenu, A_STANDOUT);
        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
        wattroff(wmenu, A_STANDOUT);
    }

    /*
     * exit
     */

    delwin(wmenu);
    delwin(wmain);
    endwin();
    return 0;
}

void menuShow(string title) {

    move(5, 5);

    for (size_t i = 0; i < title.size(); i++) {
        addch(title[i]);
        addch(' ');
    }

    refresh();
}

