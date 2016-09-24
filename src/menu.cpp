#include <ncurses.h>

#include <string>
#include <random>

#include "menu.h"
#include "game.h"
#include "classes/DiagWindow.h"

using namespace std;

void menuShow(WINDOW *wnd, string title);

WINDOW *wmenu, *wmain;

int init() {

    initscr();

    /*
     * init main window
     */

    wmain = newwin(40, 80, 1, 1);
    box(wmain, 0, 0);

    /*
     * init menu window
     */

    wmenu = newwin(10, 12, 10, 10);
    wborder(wmenu,
            ACS_BULLET, ACS_BULLET, ACS_BULLET, ACS_BULLET,     /* ls, rs, ts, bs */
            '+', '+', '+', '+');                                /* tl, tr, bl, br */

    noecho();
    keypad(wmenu, true);
    curs_set(0);

    return 0;
}

int run() {
    DiagWindow infoPanel_menu = DiagWindow({{41, 1}, {80,10}});

    int playerScore = 0;
    char menuItems[2][10] = {
        "start",
        "quit"
    };
    char menuItem[7];
    int ch, i = 0;


    /*
     * init title, menu
     */

    for (i = 0; i < 2; i++) {
        if (i == 0) wattron(wmenu, A_STANDOUT);
        else wattroff(wmenu, A_STANDOUT);

        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
    }

    wrefresh(wmain);
    wrefresh(wmenu);
    infoPanel_menu.refresh();
    menuShow(wmain, "TERMINAL QUEST");
    i = 0;

    string infoPos, infoKey, infoMsg;
    bool exitRequested = false, gameRequested = false;
    while (( ch = wgetch(wmenu)) != 'q') {
        infoMsg = "";
        infoPos = to_string(ch);
        infoKey = to_string(i);

        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);

        switch (ch) {
            case KEY_UP:
            case 56:
            case 'k':
                i--;
                i = (i < 0) ? 1 : i;
                infoMsg = "up";
                break;
            case KEY_DOWN:
            case 50:
            case 'j':
                i++;
                i = (i > 1) ? 0: i;
                infoMsg = "down";
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                exitRequested = (i == 1) ? true : false;
                gameRequested = (i == 0) ? true : false;
                break;

        }

        infoPanel_menu.push((infoPos + ' ' + infoKey + ' ' + infoMsg));
        infoPanel_menu.refresh();  // Text will now show without this!

        wattron(wmenu, A_STANDOUT);
        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
        wattroff(wmenu, A_STANDOUT);

        if (exitRequested == true) {
            break;
        } else if (gameRequested) {
            delwin(wmenu);
            delwin(wmain);

            playerScore = startGame();
            break;
        }
    }

    /*
     * exit
     */

    endwin();

    return playerScore;
}

void close() {
    endwin();
}

void menuShow(WINDOW *wnd, string title) {

    wmove(wnd, 5, 5);

    for (size_t i = 0; i < title.size(); i++) {
        waddch(wnd, title[i]);
        waddch(wnd, ' ');
    }

    wrefresh(wnd);
}

