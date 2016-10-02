#include <ncurses.h>
#include <time.h>
#include <stdio.h>

#include <string>

#include "global/Global.h"  // includes difficulties

#include "game.h"
#include "menu.h"
#include "classes/Player.h"
#include "classes/Enemy.h"
#include "classes/Coin.h"
#include "classes/Window.h"
#include "classes/DiagWindow.h"

using namespace std;




int startGame() {

    // Retrieve global refs
    Global *global = Global::get();
    int numCoins   = global->getNoCoins();
    int numEnemies = global->getNoEnemies();

    // Declared internally, to prevent ctors from running before main
    DiagWindow diagWin_game = DiagWindow({{41, 1}, {80,10}});
    Window wgame = Window(game_area);

    // Actors know about game window for movement
    Player player = Player(wgame);

    std::vector<Enemy> enemies;
    for (int i = 0; i < numEnemies; i++)
        enemies.push_back(Enemy());
    std::vector<Coin> coins;
    for (int i = 0; i < numCoins; i++)
        coins.push_back(Coin());


    init_pair(2, COLOR_YELLOW, -1);

    /*
     * Check if Player & Enemy are too near each other.
     * `42' here is the maximum allowable value, given
     * that Player may spawn in the middle (39, 19) of
     * the game_area.
     */
    bool dangerClose = true;
    init_pair(3, COLOR_GREEN, -1);
    while (dangerClose == true) {
        for (Enemy &enemy : enemies) {
            enemy = Enemy(wgame, player);
            if (player.getDistance(enemy.getPos()) <= 42) {
                // XXX Display green shadow of enemies who were too close
                enemy.setColo(COLOR_PAIR(3));
                enemy.render();
                dangerClose = true;
                break;
            } else {
                dangerClose = false;
            }
        }
    }

    // Init placement of Player, Enemy, and Coins
    player.render();
    for (Enemy &enemy : enemies) {
        enemy.render();
    }
    for (auto &coin : coins) {
        wgame.draw(coin.getPos(), coin.getDispChar(), COLOR_PAIR(2));
    }

    int ch;
    string infoMsg = "";
    bool gameover = false;
    while (gameover == false) {
        // Advance record of world time
        global->tick();
        wgame.refresh();

        ch      = wgame.getChar();
        infoMsg = "";

        switch (ch) {
            /*
             * Diagonal keys
             */
            case 55:  // Key up-left
                player.moveNorthWest();
                break;
            case 57:  // Key up-right
                player.moveNorthEast();
                break;
            case 51:  // Key down-right
                player.moveSouthEast();
                break;
            case 49:  // Key down-left
                player.moveSouthWest();
                break;

            /*
             * Orthogonal keys
             */
            case KEY_UP:
            case 56:
            case 'k':
                 player.moveNorth();
                break;
            case KEY_DOWN:
            case 50:
            case 'j':
                 player.moveSouth();
                break;
            case KEY_LEFT:
            case 52:
            case 'h':
                 player.moveWest();
                break;
            case KEY_RIGHT:
            case 54:
            case 'l':
                 player.moveEast();
                break;
            case KEY_ENTER: /* numpad enter */
            case '\n':      /* keyboard return */
                break;
            default:
                player.wait();
                infoMsg = "waiting...";

        }

        wgame.update();

        // Draw Coins again, and check if player has landed on
        for (auto &coin : coins) {
            wgame.draw(coin.getPos(), coin.getDispChar(), COLOR_PAIR(2));
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
        string proximityAlert = "";
        for (Enemy &enemy : enemies) {
            enemy.move();
            enemy.render();
            if (enemy.isAdjacent(player.getPos())) {
                proximityAlert = "!";
            }
        }


        diagWin_game.push(
            + " nen: "
            + std::to_string(numEnemies)
            + " stp: "
            + std::to_string(player.getSteps())
            + " ptk: "
            + std::to_string(player.getTicks())
            + " gtk: "
            + std::to_string(global->getTicks())
            + " scr: "
            + std::to_string(player.getScore())
            + " dif: " + global->getDifficultyStr()
            + " nfo: " + infoMsg
            + " " + proximityAlert
        );

        wgame.refresh();


        for (Enemy &enemy : enemies) {
            // Game Over
            if (enemy.atop(player.getPos())) {
                gameover = true;
                wgame.coloSplash(COLOR_PAIR(1));
                diagWin_game.push("GAME OVER!");
                diagWin_game.push("Press `q' to quit.");

                while (wgame.getChar() != 'q');  // TODO prompt restart or quit
                break;
            }
        }
    }


    // TODO eventually return more information
    return (player.getScore() + player.getSteps()) * global->getDifficulty();
}

