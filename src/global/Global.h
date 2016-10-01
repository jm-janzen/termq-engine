#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>

#include <stdio.h>

#include "difficulty-levels.h"

class Global {
    public:
        /* Singleton */
        static Global *get() {
            if ( ! instance) instance = new Global();
            return instance;
        };

        void tick() { ticks++; }

        void setDifficulty(int initDifficulty) {
            difficulty = difficultyLevels(initDifficulty);
            switch (difficulty) {
                case CHEAT:
                    noCoins = 100;
                    noEnemies = 1;
                    break;
                case EASY:
                    noCoins = 50;
                    noEnemies = 1;
                    break;
                case MEDIUM:
                    noCoins = 10;
                    noEnemies = 1;
                    break;
                case HARD:
                    noCoins = 10;
                    noEnemies = 2;
                    break;
                case NIGHTMARE:
                    noCoins = 10;
                    noEnemies = 3;
                    break;
            }
        };

        int  getDifficulty() { return difficultyLevels(difficulty); }
        int  getNoCoins()    { return noCoins; }
        int  getNoEnemies()  { return noEnemies; }

        std::string getDifficultyStr() {
            std::string difficultyStr = "";
            switch (difficulty) {
                case CHEAT:
                    difficultyStr = "cht";
                    break;
                case EASY:
                    difficultyStr = "esy";
                    break;
                case MEDIUM:
                    difficultyStr = "med";
                    break;
                case HARD:
                    difficultyStr = "hrd";
                    break;
                case NIGHTMARE:
                    difficultyStr = "ngt";
                    break;
            }

            return difficultyStr;
        }
        int  getTicks() { return ticks; }

    private:
        static Global *instance;

        int noCoins    = 10;
        int difficulty = 2;
        int noEnemies  = 1;
        int ticks      = 0;

};

#endif
