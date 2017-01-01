#ifndef DIAGWINDOW_H
#define DIAGWINDOW_H

#include "Window.h"

class DiagWindow : public Window {
    public:
        DiagWindow(rect dim);

        void push(std::string msg);

    private:
        int cursor_pos = 0;
        std::array<std::string, 9> messages;
};

#endif

