#include <ncurses.h>

#include <string>

#include "game.h"
#include "InfoPanel.h"

using namespace std;

void menuShow(WINDOW *wnd, string title);
void startGame();

WINDOW *wmenu, *wmain;

InfoPanel *infoPanel = new InfoPanel();

struct {
    vec2i pos;
    rect bounds;
    char disp_char;
} player;

rect game_area;

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
    infoPanel->update();
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
            case 'k':
                i--;
                i = (i < 0) ? 1 : i;
                infoMsg = "up";
                break;
            case KEY_DOWN:
            case 'j':
                i++;
                i = (i > 1) ? 0: i;
                infoMsg = "down";
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                if (i == 1) exitRequested = true;
                else if (i == 0) gameRequested = true;
                break;

        }

        infoPanel->push((infoPos + ' ' + infoKey + ' ' + infoMsg));

        wattron(wmenu, A_STANDOUT);
        sprintf(menuItem, "%-7s", menuItems[i]);
        mvwprintw(wmenu, i + 1, 2, "%s", menuItem);
        wattroff(wmenu, A_STANDOUT);

        if (exitRequested == true) {
            break;
        } else if (gameRequested) {
            delwin(wmenu);
            delwin(wmain);

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

    player.pos = {1, 1};
    player.disp_char = '@';

    //endwin();
    game_area = {
        {1, 1},
        {40, 37} /* {40, 80} minus borders */
    };

    WINDOW *wgame = newwin(40, 80, 1, 1);
    box(wgame, '-', '.');
    keypad(wgame, true);
    wmove(wgame, 1, 1);

    int ch, i;
    string infoKey, infoMsg;
    vec2i infoPos;
    while (( ch = wgetch(wgame)) != 'q') {

        infoMsg = "";
        infoKey = to_string(ch);


        werase(wgame);
        box(wgame, '-', '.');

        switch (ch) {
            case KEY_UP:
            case 'k':
                /* TODO check for area bounds */
                if (player.pos.y > game_area.top()) player.pos.y--;
                break;
            case KEY_DOWN:
            case 'j':
                /* TODO check for area bounds */
                if (player.pos.y < game_area.bot()) player.pos.y++;
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;

        }

        wmove(wgame, player.pos.y, 1);
        waddch(wgame, player.disp_char);

        infoPanel->push('{'
            + std::to_string(player.pos.x) + ','
            + std::to_string(player.pos.y) + '}'
            + '{'
            + std::to_string(game_area.top()) + ','
            + std::to_string(game_area.bot()) + '}'
        );

        wrefresh(wgame);

    }

    delwin(wgame);
}

