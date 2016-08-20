#include <ncurses.h>

#include <string>

#include "game.h"

using namespace std;

int main(int argc, char **argv) {

    int initStatus = init();
    if (initStatus == 0) run();

    close();

    printf("GAME OVER\n");

    return 0;
}
