#include<thread>
#include <stdio.h>
#include <time.h>

#include "spdlog/spdlog.h"
#include "menu.h"

using namespace std;

int main() {
    // Init basic log
    auto daily_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/termq", "log", 1024 * 24, 0);
    auto logger = std::make_shared<spdlog::logger>("termq", daily_sink);
    spdlog::register_logger(logger);

    spdlog::get("termq")->info(" --- START ---");

    srand(time(0));

    int playerScore = 0;

    if (init() == 0) {
        playerScore = run();
    }

    close();

    printf("\n~~~ GAME OVER ~~~\n");
    printf("lifespan:   %d\n", -1);
    printf("score:      %d\n", playerScore);
    printf("~~~~~~~~~~~~~~~~~\n");

    spdlog::get("termq")->info(" --- STOP ---");
    return 0;
}
