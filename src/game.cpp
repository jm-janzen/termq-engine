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


int startGame() {

    // Declared internally, to prevent ctors from running before main
    InfoPanel *infoPanel_game = new InfoPanel();
    Player player;
    Enemy  enemy;
    Coin   coins[numCoins];

    WINDOW *wgame = newwin(game_area.height(), game_area.width(), 1, 1);
    box(wgame, 0, 0);
    keypad(wgame, true);

    // Init placement of Player, Enemy, and Coins
    wmove(wgame, player.getPos().y, player.getPos().x);
    waddch(wgame, player.getDispChar());

    wmove(wgame, enemy.getPos().y, enemy.getPos().x);
    waddch(wgame, enemy.getDispChar());

    for (auto &coin : coins) {
        wmove(wgame, coin.getPos().y, coin.getPos().x);
        waddch(wgame, coin.getDispChar());
    }

    int ch, steps = 0, difficulty = 1;
    string infoKey, infoMsg = "";
    bool gameover = false;
    while (( ch = wgetch(wgame)) != 'q') {

        infoKey = to_string(ch);

        steps++;

        werase(wgame);
        box(wgame, 0, 0);


        int px = player.getPos().x;
        int py = player.getPos().y;

        switch (ch) {
            case KEY_UP:
            case 'k':
                if (py > (int) game_area.top()) player.moveUp();
                infoMsg = "up(" + to_string(py) + " > " + to_string(game_area.top()) + ")";
                break;
            case KEY_DOWN:
            case 'j':
                if (py < (int) game_area.bot()) player.moveDown(); // want bot:40
                infoMsg = "down(" + to_string(py) + " < " + to_string(game_area.bot()) + ")";
                break;
            case KEY_LEFT:
            case 'h':
                if (px > (int) game_area.left()) player.moveLeft();
                infoMsg = "left(" + to_string(px) + " > " + to_string(game_area.left()) + ")";
                break;
            case KEY_RIGHT:
            case 'l':
                if (px < (int) game_area.right()) player.moveRight(); // want right:80
                infoMsg = "right(" + to_string(px) + " < " + to_string(game_area.right()) + ")";
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;
            default:
                player.wait();
                infoMsg = "waiting...";

        }

        // Draw Coins again, and check if player has landed on
        for (auto &coin : coins) {
            wmove(wgame, coin.getPos().y, coin.getPos().x);
            waddch(wgame, coin.getDispChar());
            if (player.atop(coin.getPos())) {
                player.addScore(coin.getValue());

                // Just zero out coin value and display for now
                coin.setValue(0);
                coin.setChar(' ');
            }
        }

        // Move Player to indicated position
        wmove(wgame, player.getPos().y, player.getPos().x);
        waddch(wgame, player.getDispChar());

        // Enemy, seek out player
        enemy.seek(player);  // Discard return (updated pos)
        wmove(wgame, enemy.getPos().y, enemy.getPos().x);
        waddch(wgame, enemy.getDispChar());

        string proximityAlert = "";
        if (enemy.isAdjacent(player.getPos())) {
            proximityAlert = "!";
        }
        infoPanel_game->push('{'
            + std::to_string(player.getPos().x) + ','
            + std::to_string(player.getPos().y) + '}'
            + '{'
            + std::to_string(enemy.getPos().x) + ','
            + std::to_string(enemy.getPos().y) + '}'
            + " steps: "
            + std::to_string(player.getSteps())
            + " ticks: "
            + std::to_string(player.getTicks())
            + " score: "
            + std::to_string(player.getScore())
            + " info: " + infoMsg
            + " " + proximityAlert
        );

        wrefresh(wgame);

        if (enemy.atop(player.getPos())) {
            // Game Over
            gameover = true;
            infoPanel_game->push("GAME OVER!");
            infoPanel_game->push("Press `q' to quit.");
            while (wgetch(wgame) != 'q');  // TODO prompt restart or quit
            break;
        }
    }

    delwin(wgame);
    return player.getScore() + steps * difficulty;  // TODO eventually return more information
}

