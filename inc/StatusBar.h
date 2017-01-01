#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <string>
#include "Window.h"
#include "Actor.h"
#include "game.h"

class StatusBar : public Window {
    public:
        // ctor - implicitly init Window, Actor
        StatusBar(rect dim, Actor &a) : Window(dim), actor(a){}

        void refresh();

    private:
        Actor &actor;
};

#endif

