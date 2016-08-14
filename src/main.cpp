#include <ncurses.h>

#include <string>

using namespace std;

void menuShow(WINDOW *wnd, string title);


int main(int argc, char **argv) {

    WINDOW *wmenu, *wmain, *winfo;
    char menuItems[2][10] = {
        "start",
        "quit"
    };
    char menuItem[7];
    int ch, i = 0, width = 7;


    initscr();

    /*
     * init main window
     */

    wmain = newwin(40, 80, 1, 1);
    box(wmain, 0, 0);

    /*
     * init info window
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

    for (i = 0; i < 2; i++) {
        if (i == 0) wattron(wmenu, A_STANDOUT);
        else wattroff(wmenu, A_STANDOUT);

        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
    }

    /*
     * init title, menu
     */

    wrefresh(wmain);
    wrefresh(wmenu);
    wrefresh(winfo);
    menuShow(wmain, "TERMINAL QUEST");
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
            default: // XXX only displays on second input
                string msg = "ch:" + to_string(ch) + ", i:" +to_string(i);
                wmove(winfo, 1, 1);
                wrefresh(winfo);
                wprintw(winfo, msg.c_str());
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
    delwin(winfo);
    endwin();
    return 0;
}

void menuShow(WINDOW *wnd, string title) {

    wmove(wnd, 5, 5);

    for (size_t i = 0; i < title.size(); i++) {
        waddch(wnd, title[i]);
        waddch(wnd, ' ');
    }

    wrefresh(wnd);
}

