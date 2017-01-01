#include <string>

#include "game.h"
#include "DiagWindow.h"

DiagWindow::DiagWindow(rect dim) : Window(dim) {
    /* Just passing through */
}

void DiagWindow::push(std::string msg) {
    this->update();

    /*
     * increment cursor position, push old messages up
     */
    if (cursor_pos < (int) messages.max_size() - 1) {
        cursor_pos++;
    } else {
        for (int i = 0; i < (int) messages.max_size() - 1; i++) {
            messages[i] = messages[i + 1];
        }
    }

    messages[cursor_pos] = msg;

    /*
     * rewrite lines from top to bot
     */
    for (uint_fast8_t i = 1; i < messages.max_size(); i++) {
        this->cursorPos({1,i});
        this->write(messages[i]);
    }


    /*
     * place a box around info panel and signal changes
     */
    this->refresh();
}


