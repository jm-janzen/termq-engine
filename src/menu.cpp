#include <ncurses.h>
#include <algorithm> // for std::find

#include <string>
#include <random>

#include "global/Global.h"

#include "menu.h"
#include "game.h"
#include "classes/DiagWindow.h"
#include "classes/MenuWindow.h"

using namespace std;


/*
 * Init Global ptr
 */

Global *Global::instance = 0;

void menuShow(WINDOW *wnd, string title);


int init() {

    /*
     * Init global ptr - discard return.
     */

    Global::get();

    /*
     * Init ncurses for session.
     */

    initscr();
    noecho();
    curs_set(0);
    use_default_colors();
    start_color();

    return 0;
}

int run() {
    Global *g = Global::get();
    g->setDifficulty(MEDIUM);

    int playerScore = 0;

    WINDOW *wmain = newwin(40, 80, 1, 1);
    box(wmain, 0, 0);

    /*
     * init title, menu
     */

    MenuWindow menuWin = MenuWindow({{10, 6}, {20, 12}});
    MenuWindow optsWin = MenuWindow({{13, 14}, {16, 10}});

    const std::vector<string> menuItems {
        "start",
        "quit",
        "opts",
    };
    const std::vector<string> optsItems {
        "cheat",
        "easy",
        "medium",
        "hard",
        "nightmare",
    };

    for (auto &item : menuItems) {
        menuWin.add(item);
    }
    for (auto &item : optsItems) {
        optsWin.add(item);
    }

    wrefresh(wmain);
    menuShow(wmain, "TERMINAL QUEST");

    /*
     * TODO
     *  Look into ncurses' panels, menus libs
     *  for this stuff - might be better.
     */
    menuWin.updateMenu();
    menuWin.refresh();

    /*
     * Get menu selection
     */

    std::string selection = "";
    std::string optsSelection = "";

    while ( selection.length() < 1 || optsSelection.length() < 1) {
        selection = menuWin.getSelection();
        if (in_array(selection, menuItems)) {

            if (selection == "quit") {
                break;
            } else if (selection == "start") {

                // TODO choose difficulty

                playerScore = startGame();
                break;
            } else if (selection == "opts") {
                optsWin.updateMenu();
                optsWin.refresh();
                while (optsSelection.length() < 1) {
                    optsSelection = optsWin.getSelection();
                }
                selection = "";
                if (optsSelection == "easy") {
                    g->setDifficulty(EASY);
                } else if (optsSelection == "medium") {
                    g->setDifficulty(MEDIUM);
                } else if (optsSelection == "hard") {
                    g->setDifficulty(HARD);
                }
            }
        }
    }

    /*
     * exit
     */

    close();

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

bool in_array(const string &value, const std::vector<string> &array) {
    return std::find(array.begin(), array.end(), value) != array.end();
}

