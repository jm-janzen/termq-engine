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
    WINDOW *wgame = newwin(game_area.height(), game_area.width(), 1, 1);

    // Actors know about game window for movement
    Player player = Player(*wgame);
    Enemy  enemy  = Enemy(*wgame);

    Coin   coins[numCoins];

    initscr();
    start_color();
    use_default_colors();
    init_pair(2, COLOR_YELLOW, -1);
    box(wgame, 0, 0);
    keypad(wgame, true);

    /*
     * Check if Player & Enemy are too near each other.
     * `42' here is the maximum allowable value, given
     * that Player may spawn in the middle (39, 19) of
     * the game_area.
     */
    while (player.getDistance(enemy.getPos()) <= 42) {
        // Reroll ctor for new random start
        enemy = Enemy(*wgame);
    }

    // Init placement of Player, Enemy, and Coins
    player.render();
    enemy.render();
    for (auto &coin : coins) {
        wmove(wgame, coin.getPos().y, coin.getPos().x);
        waddch(wgame, coin.getDispChar() | COLOR_PAIR(2));
    }

    int ch, difficulty = 1;
    string infoKey, infoMsg = "";
    bool gameover = false;
    while (( ch = wgetch(wgame)) != 'q') {

        infoKey = to_string(ch);
        infoMsg = "";

        werase(wgame);
        box(wgame, 0, 0);


        int px = player.getPos().x;
        int py = player.getPos().y;

        switch (ch) {
            /*
             * Diagonal keys
             */
            case 55:  // Key up-left
                if (py > (int) game_area.top() && px > (int) game_area.left()) {
                    player.moveUp();
                    player.moveLeft();
                }
                break;
            case 57:  // Key up-right
                if (py > (int) game_area.top() && px < (int) game_area.right()) {
                    player.moveUp();
                    player.moveRight();
                }
                break;
            case 51:  // Key down-right
                if (py < (int) game_area.bot() && px < (int) game_area.right()) {
                    player.moveDown();
                    player.moveRight();
                }
                break;
            case 49:  // Key down-left
                if (py < (int) game_area.bot() && px > (int) game_area.left()) {
                    player.moveDown();
                    player.moveLeft();
                }
                break;

            /*
             * Orthogonal keys
             */
            case KEY_UP:
            case 56:
            case 'k':
                if (py > (int) game_area.top()) player.moveUp();
                infoMsg = "up(" + to_string(py) + " > " + to_string(game_area.top()) + ")";
                break;
            case KEY_DOWN:
            case 50:
            case 'j':
                if (py < (int) game_area.bot()) player.moveDown();
                infoMsg = "down(" + to_string(py) + " < " + to_string(game_area.bot()) + ")";
                break;
            case KEY_LEFT:
            case 52:
            case 'h':
                if (px > (int) game_area.left()) player.moveLeft();
                infoMsg = "left(" + to_string(px) + " > " + to_string(game_area.left()) + ")";
                break;
            case KEY_RIGHT:
            case 54:
            case 'l':
                if (px < (int) game_area.right()) player.moveRight();
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
            waddch(wgame, coin.getDispChar() | COLOR_PAIR(2));
            if (player.atop(coin.getPos())) {
                player.addScore(coin.getValue());

                // Just zero out coin value and display for now
                coin.setValue(0);
                coin.setChar(' ');
            }
        }


        // Display Player to indicated position
        player.render();

        // Enemy, seek out player
        enemy.seek(player);  // Discard return (updated pos)
        enemy.render();

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
            + " dist: "
            + std::to_string(player.getDistance(enemy.getPos()))
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
            wbkgd(wgame, COLOR_PAIR(1));  // Colour entire window red
            gameover = true;
            infoPanel_game->push("GAME OVER!");
            infoPanel_game->push("Press `q' to quit.");
            while (wgetch(wgame) != 'q');  // TODO prompt restart or quit
            break;
        }
    }

    delwin(wgame);
    return player.getScore() + player.getSteps() * difficulty;  // TODO eventually return more information
}

