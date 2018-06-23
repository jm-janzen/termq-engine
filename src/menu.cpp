#include <ncurses.h>

#include <algorithm> // for std::find
#include <string>
#include <random>

#include "Global.h"
#include "World.h"

#include "menu.h"
#include "game.h"
#include "gameover.h"
#include "DiagWindow.h"
#include "MenuWindow.h"

using namespace std;


/*
 * Init Global, World singletons
 */

Global *Global::instance = 0;
World  *World::instance = 0;

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
    start_color();

    return 0;
}

int run() {

    Global *g = Global::get();
    g->setDifficulty(MEDIUM);

    int playerScore = 0;

    // TODO use our Window class for this as well.
    WINDOW *wmain = newwin(40, 80, 1, 1);
    box(wmain, 0, 0);

    /*
     * init title, menu
     */

    MenuWindow menuWin = MenuWindow({{10, 6}, {20, 12}});
    MenuWindow optsWin = MenuWindow({{13, 16}, {20, 12}});

    const std::vector<string> menuItems {
        "start",
        "quit",
        "options",
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

    menuWin.updateMenu();
    menuWin.refresh();

    /*
     * Get menu selection
     */

    std::string selection = "";
    std::string optsSelection = "";
    while ( selection != "start" || selection != "quit") {
        menuWin.drawBorder();
        selection = menuWin.getSelection();
        if (in_array(selection, menuItems)) {

            if (selection == "quit") {  // Exit
                break;
            } else if (selection == "start") {  // Start playing
                do {  // Play until player chooses to stop
                    playerScore = startGame();
                } while ( ! gameover() );
                break;  // Skips menu, and exits game
            } else if (selection == "options") {  // Select difficulty
                /*
                 * Populate menu with opts and set highlighted
                 * selection to default, or previously selected
                 * difficulty.
                 */
                optsWin.updateMenu(g->getDifficulty());
                optsWin.drawBorder(); // Also refreshes

                // Get new difficulty selection
                while ((optsSelection = optsWin.getSelection()).length() < 1);

                // Reset main menu selection and parse difficulty selection
                selection = "";
                if (optsSelection == "cheat") {
                    g->setDifficulty(CHEAT);
                } else if (optsSelection == "easy") {
                    g->setDifficulty(EASY);
                } else if (optsSelection == "medium") {
                    g->setDifficulty(MEDIUM);
                } else if (optsSelection == "hard") {
                    g->setDifficulty(HARD);
                } else if (optsSelection == "nightmare") {
                    g->setDifficulty(NIGHTMARE);
                }

                // Clear out opts window (hide it), and show main menu
                optsWin.clear();

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

