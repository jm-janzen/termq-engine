#include <ncurses.h>

#include <string>

using namespace std;

void menuShow(WINDOW *wnd, string title);
void startGame();

WINDOW *wmenu, *wmain, *winfo;

int init() {

    initscr();

    /*
     * init main window
     */

    wmain = newwin(40, 80, 1, 1);
    box(wmain, 0, 0);

    /*
     * init info window
     * TODO
     *  [_] allow multiple info lines
     *  [_] delete oldest line when full
     *  [_] don't clear borders
     */

    winfo = newwin(10, 80, 40 + 1, 1);
    box(winfo, 0, 0);

    /*
     * init menu window
     */

    wmenu = newwin(10, 12, 10, 10);
    wborder(wmenu,
            ACS_BULLET, ACS_BULLET, ACS_BULLET, ACS_BULLET,     /* ls, rs, ts, bs */
            '+', '+', '+', '+');                                /* tl, tr, bl, br */

    return 0;
}

void run() {
    char menuItems[2][10] = {
        "start",
        "quit"
    };
    char menuItem[7];
    int ch, i = 0, width = 7;


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
    wrefresh(winfo);
    menuShow(wmain, "TERMINAL QUEST");
    i = 0;
    noecho();
    keypad(wmenu, true);
    curs_set(0);

    string infoPos, infoKey, infoMsg;
    bool exitRequested = false, gameRequested = false;
    while (( ch = wgetch(wmenu)) != 'q') {
        infoPos = to_string(ch);
        infoKey = to_string(i);

        box(winfo, 0, 0);
        wmove(winfo, 1, 1);
        wprintw(winfo, (infoPos + ' ' + infoKey + ' ' + infoMsg).c_str());

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
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                if (i == 1) exitRequested = true;
                else if (i == 0) gameRequested = true;
                break;

        }
        wmove(winfo, 1, 1);
        wrefresh(winfo);
        werase(winfo);

        wattron(wmenu, A_STANDOUT);
        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
        wattroff(wmenu, A_STANDOUT);

        if (exitRequested == true) {
            break;
        } else if (gameRequested) {
            delwin(wmenu);
            delwin(wmain);
            delwin(winfo);
            startGame();
            break;
        }
    }

    /*
     * exit
     */

    endwin();

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

void startGame() {
    endwin();

    WINDOW *wgame = newwin(40, 80, 1, 1);
    box(wgame, '-', '.');
    wrefresh(wgame);

    keypad(wgame, true);

    wmove(wgame, 1, 1);
    int ch, i;
    while (( ch = wgetch(wgame)) != 'q') {
        waddstr(wgame, to_string(ch).c_str());
        wmove(wgame, 1, 1);
    }
    delwin(wgame);
}

