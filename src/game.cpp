#include <ncurses.h>

#include <string>
#include <random>

#include "game.h"
#include "menu.h"
#include "Player.h"
#include "InfoPanel.h"

using namespace std;

InfoPanel *infoPanel_game = new InfoPanel();
Player player;


rect game_area;

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

    // Cast int to vector's expected type

    vec2i initPos = {
        (int_fast8_t) randx, (int_fast8_t) randy
    };
    player.setPos(initPos);

    wmove(wgame, player.getPos().y, player.getPos().x);
    waddch(wgame, player.getDispChar());

    int ch;
    string infoKey, infoMsg;
    while (( ch = wgetch(wgame)) != 'q') {

        infoMsg = "";
        infoKey = to_string(ch);

        werase(wgame);
        box(wgame, 0, 0);

        int_fast8_t x = player.getPos().x;
        int_fast8_t y = player.getPos().y;

        switch (ch) {
            case KEY_UP:
            case 'k':
                if (y > game_area.top() + 1) player.setPosY(y - 1);
                break;
            case KEY_DOWN:
            case 'j':
                if (y < game_area.bot() - 2) player.setPosY(y + 1);
                break;
            case KEY_LEFT:
            case 'h':
                if (x > game_area.left() + 1) player.setPosX(x - 1);
                break;
            case KEY_RIGHT:
            case 'l':
                if (x < game_area.right() - 2) player.setPosX(x + 1);
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;

        }

        // Move to updates position
        wmove(wgame, player.getPos().y, player.getPos().x);
        waddch(wgame, player.getDispChar());

        infoPanel_game->push('{'
            + std::to_string(x) + ','
            + std::to_string(y) + '}'
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

