#include <string>

#include "menu.h"

using namespace std;

int main() {
    srand(time(0));

    int playerScore = 0;

    if (init() == 0) {
        playerScore = run();
    }

    close();

    /*
     * TODO
     *  1)  Calculate score.
     *  2)  Display score here.
     */
    printf("\n~~~ GAME OVER ~~~\n");
    printf("lifespan:   %d\n", 0);
    printf("score:      %d\n", playerScore);
    printf("~~~~~~~~~~~~~~~~~\n");

    return 0;
}
