#include <ncurses.h>

#include <string>
#include <random>

#include "game.h"
#include "menu.h"
#include "InfoPanel.h"

using namespace std;

InfoPanel *infoPanel_game = new InfoPanel();

struct {
    vec2i pos;
    rect bounds;
    char disp_char;
} player;

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

        infoPanel_game->push('{'
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

