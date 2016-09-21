#include <string>

#include "menu.h"

using namespace std;

int main() {
    srand(time(0));

    if (init() == 0) run();

    close();

    /*
     * TODO
     *  1)  Calculate score.
     *  2)  Display score here.
     */
    printf("\n~~~ GAME OVER ~~~\n");
    printf("lifespan:   %d\n", 0);
    printf("score:      %d\n", 0);
    printf("~~~~~~~~~~~~~~~~~\n");

    return 0;
}
