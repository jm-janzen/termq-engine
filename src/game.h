#ifndef GAME_H
#define GAME_H

#include <stdint.h> // Use <inttype.h> if portability important

typedef struct {
    uint_fast8_t x;
    uint_fast8_t y;
} vec2ui;

typedef struct {
    int_fast8_t x;
    int_fast8_t y;
} vec2i;

typedef struct {
    vec2i offset;
    vec2i bounds;

    uint_fast16_t top()     { return offset.y; }
    uint_fast16_t bot()     { return offset.y + bounds.y; }
    uint_fast16_t left()    { return offset.x; }
    uint_fast16_t right()   { return offset.x + bounds.x; }

    uint_fast16_t width()   { return bounds.x; }
    uint_fast16_t height()  { return bounds.y; }

    bool contains(vec2i a) {
        return (a.x >= offset.x && a.x < right())
            && (a.y >= offset.y && a.y < bot());
    }

} rect;

void startGame();

#endif

