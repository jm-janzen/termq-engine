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

const typedef struct {
    vec2i offset;
    vec2i bounds;

    uint_fast16_t top()     const { return offset.y; }
    uint_fast16_t bot()     const { return offset.y + bounds.y; }
    uint_fast16_t left()    const { return offset.x; }
    uint_fast16_t right()   const { return offset.x + bounds.x; }

    uint_fast16_t width()   const { return bounds.x; }
    uint_fast16_t height()  const { return bounds.y; }

    bool contains(vec2i a)  const {
        return (a.x >= offset.x && a.x < right())
            && (a.y >= offset.y && a.y < bot());
    }

} rect;

const rect game_area = {
    {0, 0},
    {80, 40}
};


int startGame();

#endif

