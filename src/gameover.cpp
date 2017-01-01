#include <string>

#include "MenuWindow.h"


bool gameover() {
    MenuWindow gameoverWin = MenuWindow({{20, 30}, {20, 6}});
    const std::vector<std::string> gameoverItems {
        "restart",
        "quit",
    };
    for (auto &item : gameoverItems) {
        gameoverWin.add(item);
    }

    gameoverWin.updateMenu();
    gameoverWin.drawBorder(); // Also refreshes

    // Get selection
    std::string selection = "";
    while ((selection = gameoverWin.getSelection()).length() < 1);

    return (selection == "quit");  // c++ is weird...
}
