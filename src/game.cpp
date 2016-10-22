#include <ncurses.h>
#include <time.h>
#include <stdio.h>

#include <string>
#include <algorithm>

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

    DiagWindow diagWin_game = DiagWindow({{41, 1}, {100,10}});
    Window wgame = Window(game_area);
    Map map = Map(&wgame);

    Player player = Player();

    std::vector<Enemy> enemies;
    for (int i = 0; i < numEnemies; i++)
        enemies.push_back(Enemy());
    std::vector<Coin> coins;
    for (int i = 0; i < numCoins; i++)
        coins.push_back(Coin());


    // Check if Player & Enemy are too near from each other.
    uint_fast8_t quarterArea = (game_area.area() / 4);
    for (Enemy &enemy : enemies) {
        enemy = Enemy(player);
        do {
            enemy.setPosRand();
        } while (player.getDistance(enemy.getPos()) < quarterArea);
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
        vec2ui prevPos = player.getPos();

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
        if (map.checkCell(player.getPos(), "Enemy")) {
            for (Enemy &enemy : enemies) {
                if (enemy.getPos() == player.getPos()) {
                    player.attack(enemy);
                }
            }
            player.setPos(prevPos);
        }

        // Draw Coins again, and check if player has landed on
        // TODO replace this for..range with std iter for loop
        for (auto &coin : coins) {
            if (player.atop(coin.getPos())) {
                coin.setOwnership(PLAYER);
                player.addItem(coin);

                // Erase this coin if owned by Player
                coins.erase(
                    std::remove_if(
                        coins.begin(),
                        coins.end(),
                        [](Coin& c) -> bool {
                            return c.getOwnership() == PLAYER;
                        }
                    ),
                    coins.end()
                );

                if ( ++coinsCollected == numCoins) {
                    isGameover = true;
                }
            }
        }

        // Enemy, seek out player
        string proximityAlert = "";
        for (size_t i = 0; i < enemies.size(); i++) {
            if (enemies[i].getHP() > 0) {  // TODO some sort of alive or dead flag
                enemies[i].move();
                if (enemies[i].isAdjacent(player.getPos())) {
                    proximityAlert += "!";
                }
            } else { // pop dead enemy
                diagWin_game.push(player.getName()
                        + " killed " + enemies[i].getType()
                        + " " + enemies[i].getName() + "!");
                enemies.erase(enemies.begin() + i);
            }
        }

        for (Enemy &enemy : enemies) {
            // Game Over
            if (enemy.atop(player.getPos())) {
                wgame.coloSplash(COLOR_PAIR(1));

                diagWin_game.push("GAME OVER!");
                isGameover = true;
                break;
            }
        }

        diagWin_game.push(
            + "HP: "
            + std::to_string(player.getHP())
            + " ST: "
            + std::to_string(player.getST())
            + " DEF: "
            + std::to_string(player.getDEF())
            + " ATK: "
            + std::to_string(player.getATK())
            + " ACT: "
            + std::to_string(player.getACT())
            + " LCK: "
            + std::to_string(player.getLCK())
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

        // Re-init map with refs to updated entities
        map = Map(&wgame);
        map.push(player);
        for (Coin  &coin  : coins)   map.push(coin);
        for (Enemy &enemy : enemies) map.push(enemy);
    }

    /*
     * Post-game loop operations.
     */
    map.draw();  // Draw last frame.

    // TODO eventually return more information
    return player.getScore();
}

