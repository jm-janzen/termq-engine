#include <ncurses.h>
#include <time.h>
#include <stdio.h>

#include <string>

#include "global/Global.h"  // includes difficulties
#include "world/World.h"
#include "world/Map.h"

#include "game.h"
#include "menu.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Coin.h"
#include "windows/Window.h"
#include "windows/DiagWindow.h"

using namespace std;


int startGame() {

    /*
     * Pre-game loop init.
     * TODO
     *  1) Init entities.
     *  2) Init map with entities.
     *  3) draw map.
     */

    // Retrieve global refs
    Global *global = Global::get();
    int numCoins   = global->getNoCoins();
    int numEnemies = global->getNoEnemies();

    // Declared internally, to prevent ctors from running before main
    DiagWindow diagWin_game = DiagWindow({{41, 1}, {100,10}});
    Window wgame = Window(game_area);
    Map map = Map(&wgame);

    // Actors know about game window for movement
    Player player = Player();

    std::vector<Enemy> enemies;
    for (int i = 0; i < numEnemies; i++)
        enemies.push_back(Enemy());
    std::vector<Coin> coins;
    for (int i = 0; i < numCoins; i++)
        coins.push_back(Coin());


    /*
     * Check if Player & Enemy are too near or too far
     * from each other.  Somewhere between a quarter
     * of a screen and half of a screen.
     */
    uint_fast8_t quarterArea = (game_area.area() / 4);
    uint_fast8_t halfArea = (game_area.area() / 2);
    uint_fast8_t distance;
    bool dangerClose = true;
    init_pair(3, COLOR_GREEN, -1);
    while (dangerClose == true) {
        for (Enemy &enemy : enemies) {
            enemy = Enemy(player);
            distance = player.getDistance(enemy.getPos());
            if (distance > halfArea && distance < quarterArea) {
                // XXX Display green shadow of enemies who were too close
                enemy.setColo(COLOR_PAIR(3));
                enemy.render(wgame);
                dangerClose = true;
                break;
            } else {
                dangerClose = false;
            }
        }
    }

    /* Init placement of Player, Enemy, and Coins
     * Map prioritises drawing items in the reverse
     * of the order that they were added
     */
    map.push(player);
    for (Coin  &coin  : coins)   map.push(coin);
    for (Enemy &enemy : enemies) map.push(enemy);


    /*
     * Game loop begin.
     */

    int ch, coinsCollected = 0;
    string infoMsg = "";
    bool isGameover = false;
    while (isGameover == false) {
        // Advance record of world time
        global->tick();

        // Draw all entities
        map.draw();

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
            case 27:        /* ESC */
                isGameover = true;
            default:
                player.wait();
                infoMsg = player.getName();

        }

        // Draw Coins again, and check if player has landed on
        for (auto &coin : coins) {
            // Don't do anything unless coin 'belongs' to world
            if (coin.getOwnership() == WORLD) {
                if (player.atop(coin.getPos())) {
                    coin.setOwnership(PLAYER);
                    player.addItem(coin);
                    map.rm(coin);

                    if ( ++coinsCollected == numCoins) {
                        isGameover = true;
                    }
                }
            }
        }

        // Enemy, seek out player
        string proximityAlert = "";
        for (Enemy &enemy : enemies) {
            enemy.move();
            if (enemy.isAdjacent(player.getPos())) {
                proximityAlert = "!";
            }
        }


        diagWin_game.push(
            + " HP: "
            + std::to_string(player.getHP())
            + " DF: "
            + std::to_string(player.getDF())
            + " ATK: "
            + std::to_string(player.getATK())
            + " ACT: "
            + std::to_string(player.getACT())
            + " LCK: "
            + std::to_string(player.getLCK())
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

        for (Enemy &enemy : enemies) {
            // Game Over
            if (enemy.atop(player.getPos())) {
                wgame.coloSplash(COLOR_PAIR(1));

                diagWin_game.push("GAME OVER!");
                isGameover = true;
                break;
            }
        }
    }

    /*
     * Post-game loop operations.
     */
    map.draw();  // Draw last frame.

    // TODO eventually return more information
    return player.getScore();
}

