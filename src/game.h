#ifndef GAME_H
#define GAME_H

#include <stdint.h> // Use <inttype.h> if portability important

struct vec2ui {
    uint_fast8_t x;
    uint_fast8_t y;
};

struct vec2i {
    int_fast8_t x;
    int_fast8_t y;

    bool operator==(const vec2i &a) const {
        return (a.x == x && a.y == y);
    }
};

struct rect {
    vec2i offset;
    vec2i bounds;

    int_fast8_t top()     const { return offset.y; }
    int_fast8_t bot()     const { return height() - offset.y ; }
    int_fast8_t left()    const { return offset.x; }

    int_fast8_t right()   const { return width() - offset.x; }

    int_fast8_t width()   const { return bounds.x; }
    int_fast8_t height()  const { return bounds.y; }

    bool contains(vec2i a)  const {
        return (a.x >= offset.x && a.x < right())
            && (a.y >= offset.y && a.y < bot());
    }

};

const rect game_area = {
    {2, 2},
    {80, 40}
};


int startGame();

// TODO check if two points occupy the same space
bool checkSuperposition(vec2i a, vec2i b);

// TODO check if two points are within a unit of each other
//   maybe yagni...
bool checkAdjacent(vec2i a, vec2i b);

// TODO get absolute minimum distance between two points
//  maybe yagni...
int_fast8_t getDistance(vec2i a, vec2i b);

#endif

