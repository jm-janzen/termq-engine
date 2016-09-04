#include <ncurses.h>

#include <string>
#include <random>

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

/*
 * TODO
 *  Split off into own source file
 */
void startGame() {

    game_area = {
        {0, 0},
        {80, 40}
    };

    WINDOW *wgame = newwin(40, 80, 1, 1);
    box(wgame, 0, 0);
    keypad(wgame, true);

    /*
     * Randomly place player anywhere in game area
     */
    random_device rd;
    uniform_int_distribution<int> distx(game_area.left(), game_area.right());
    uniform_int_distribution<int> disty(game_area.top(), game_area.bot());
    int randx = distx(rd) + 1;
    int randy = disty(rd) + 1;
    player.pos = {
        randx, randy
    };
    player.disp_char = '@';

    wmove(wgame, player.pos.y, player.pos.x);
    waddch(wgame, player.disp_char);

    int ch, i;
    string infoKey, infoMsg;
    vec2i infoPos;
    while (( ch = wgetch(wgame)) != 'q') {

        infoMsg = "";
        infoKey = to_string(ch);

        werase(wgame);
        box(wgame, 0, 0);

        switch (ch) {
            case KEY_UP:
            case 'k':
                if (player.pos.y > game_area.top() + 1) player.pos.y--;
                break;
            case KEY_DOWN:
            case 'j':
                if (player.pos.y < game_area.bot() - 2) player.pos.y++;
                break;
            case KEY_LEFT:
            case 'h':
                if (player.pos.x > game_area.left() + 1) player.pos.x--;
                break;
            case KEY_RIGHT:
            case 'l':
                if (player.pos.x < game_area.right() - 2) player.pos.x++;
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;

        }

        wmove(wgame, player.pos.y, player.pos.x);
        waddch(wgame, player.disp_char);

        infoPanel->push('{'
            + std::to_string(player.pos.x) + ','
            + std::to_string(player.pos.y) + '}'
            + " - right & left: {"
            + std::to_string(game_area.right()) + ','
            + std::to_string(game_area.left()) + '}'
            + " top & bot: {"
            + std::to_string(game_area.top()) + ','
            + std::to_string(game_area.bot()) + '}'
        );

        wrefresh(wgame);

    }

    delwin(wgame);
}

