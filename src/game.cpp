#include <ncurses.h>
#include <time.h>
#include <stdio.h>

#include <string>

#include "game.h"
#include "menu.h"
#include "classes/Player.h"
#include "classes/Enemy.h"
#include "classes/Coin.h"
#include "classes/InfoPanel.h"

using namespace std;

const int numCoins = 10;

InfoPanel *infoPanel_game = new InfoPanel();
Player player;
Enemy  enemy;
Coin   coins[numCoins];


int startGame() {

    WINDOW *wgame = newwin(40, 80, 1, 1);
    box(wgame, 0, 0);
    keypad(wgame, true);

    /*
     * Randomly place player anywhere in game area
     */
    int_fast8_t randx = rand() % game_area.right() + game_area.left();
    int_fast8_t randy = rand() % game_area.bot() + game_area.top();

    vec2i initPos = {
        randx, randy
    };
    player.setPos(initPos);

    // Init placement of Player, Enemy, and Coins
    wmove(wgame, player.getPos().y, player.getPos().x);
    waddch(wgame, player.getDispChar());

    wmove(wgame, enemy.getPos().y, enemy.getPos().x);
    waddch(wgame, enemy.getDispChar());

    for (auto &coin : coins) {
        wmove(wgame, coin.getPos().x, coin.getPos().y);
        waddch(wgame, coin.getDispChar());
    }

    int ch;
    string infoKey, infoMsg;
    while (( ch = wgetch(wgame)) != 'q') {

        infoMsg = "";
        infoKey = to_string(ch);

        werase(wgame);
        box(wgame, 0, 0);

        vec2ui coinsPos[numCoins];
        for (int i = 0; i < numCoins; i++) {
            coinsPos[i] = { coins[i].getPos().x, coins[i].getPos().y};
        }


        int px = player.getPos().x;
        int py = player.getPos().y;

        // Check if Player is on Coin
        for (auto &cp : coinsPos) {
            if ((cp.x, cp.y) == (px, py)) {
                player.addScore(100);  // TODO get value of coin
                // TODO rm this Coin from game area
            }
        }

        // Enemy only reacts to previous move
        enemy.seek(player);  // Discard return (updated pos)
        int ex = enemy.getPos().x;
        int ey = enemy.getPos().y;

        switch (ch) {
            case KEY_UP:
            case 'k':
                if (py > (int) game_area.top() + 1) player.setPosY(py - 1);
                break;
            case KEY_DOWN:
            case 'j':
                if (py < (int) game_area.bot() - 2) player.setPosY(py + 1);
                break;
            case KEY_LEFT:
            case 'h':
                if (px > (int) game_area.left() + 1) player.setPosX(px - 1);
                break;
            case KEY_RIGHT:
            case 'l':
                if (px < (int) game_area.right() - 2) player.setPosX(px + 1);
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;

        }

        // Draw Coins again (no changes)
        for (auto &coin : coins) {
            wmove(wgame, coin.getPos().x, coin.getPos().y);
            waddch(wgame, coin.getDispChar());
        }

        // Move Player to indicated position
        wmove(wgame, player.getPos().y, player.getPos().x);
        waddch(wgame, player.getDispChar());

        // Enemy, seek out player
        wmove(wgame, ey, ex);
        waddch(wgame, enemy.getDispChar());

        infoPanel_game->push('{'
            + std::to_string(px) + ','
            + std::to_string(py) + '}'
            + '{'
            + std::to_string(ex) + ','
            + std::to_string(ey) + '}'
        );

        wrefresh(wgame);

    }

    delwin(wgame);
    return player.getScore();
}

