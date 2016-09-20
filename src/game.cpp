#include <ncurses.h>
#include <time.h>

#include <string>

#include "game.h"
#include "menu.h"
#include "classes/Player.h"
#include "classes/Enemy.h"
#include "classes/InfoPanel.h"

using namespace std;

InfoPanel *infoPanel_game = new InfoPanel();
Player player;
Enemy  enemy;


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
    srand(time(NULL));
    int randx = rand() % game_area.right() + game_area.left();
    int randy = rand() % game_area.bot() + game_area.top();

    // Cast int to vector's expected type
    vec2i initPos = {
        (int_fast8_t) randx, (int_fast8_t) randy
    };
    player.setPos(initPos);

    wmove(wgame, player.getPos().y, player.getPos().x);
    waddch(wgame, player.getDispChar());

    wmove(wgame, enemy.getPos().y, enemy.getPos().x);
    waddch(wgame, enemy.getDispChar());

    int ch;
    string infoKey, infoMsg;
    while (( ch = wgetch(wgame)) != 'q') {

        infoMsg = "";
        infoKey = to_string(ch);

        werase(wgame);
        box(wgame, 0, 0);

        int x = player.getPos().x;
        int y = player.getPos().y;

        switch (ch) {
            case KEY_UP:
            case 'k':
                if (y > (int) game_area.top() + 1) player.setPosY(y - 1);
                break;
            case KEY_DOWN:
            case 'j':
                if (y < (int) game_area.bot() - 2) player.setPosY(y + 1);
                break;
            case KEY_LEFT:
            case 'h':
                if (x > (int) game_area.left() + 1) player.setPosX(x - 1);
                break;
            case KEY_RIGHT:
            case 'l':
                if (x < (int) game_area.right() - 2) player.setPosX(x + 1);
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;

        }

        // Move to updates position (Player & Enemy)
        wmove(wgame, player.getPos().y, player.getPos().x);
        waddch(wgame, player.getDispChar());

        wmove(wgame, enemy.getPos().y, enemy.getPos().x);
        waddch(wgame, enemy.getDispChar());

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

