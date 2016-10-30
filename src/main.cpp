#include <stdio.h>
#include <time.h>

#include "spdlog/spdlog.h"

#include "menu.h"

using namespace std;

int main() {
    // Init basic log
    auto console = spdlog::basic_logger_mt("console", "logs/termq.log");
    console->info("Hello logging world!");

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
    printf("lifespan:   %d\n", -1);
    printf("score:      %d\n", playerScore);
    printf("~~~~~~~~~~~~~~~~~\n");

    return 0;
}
