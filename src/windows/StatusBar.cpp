
#include <string>

#include "game.h"
#include "StatusBar.h"

void StatusBar::refresh() {
    Window::update();
    write({1,0}, actor.getName());
    write({1,1}, " HP: " + std::to_string(actor.getHP())
            + "/" + std::to_string(actor.getMaxHP()) + " "
            + "ST: " + std::to_string(actor.getST())
            + "/" + std::to_string(actor.getMaxST()));
    Window::refresh();
}

