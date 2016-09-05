#include <ncurses.h>

#include <string>

#include "menu.h"
#include "game.h"

using namespace std;

int main(int argc, char **argv) {

    if (init() == 0) run();

    close();

    printf("GAME OVER\n");

    return 0;
}
