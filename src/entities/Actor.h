
#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <cstdlib>
#include <ncurses.h>

#include "../directions.h"
#include "../game.h"
#include "../windows/Window.h"
#include "Entity.h"

struct Attributes {
    uint_fast8_t ATK = 1;
    uint_fast8_t DEF = 0;
    uint_fast8_t ACT = 1;
    uint_fast8_t LCK = 1;
    int_fast8_t HP = 100;
    int_fast8_t ST = 100;  // Attacking/Defending uses stamina, which is required to move
};

class Actor : public Entity {
    public:

        Actor();
        Actor(Window *newW);

        // Movement
        // TODO maybe combine these and accept a Direction
        void  moveNorth();
        void  moveNorthEast();
        void  moveEast();
        void  moveSouthEast();
        void  moveSouth();
        void  moveSouthWest();
        void  moveWest();
        void  moveNorthWest();


        // Iterators
        void  wait();
        void  tick();
        void  step();
        void  move();  // tick + step

        int   getSteps() { return steps; }
        int   getTicks() { return ticks; }

        uint_fast8_t getATK() { return attr.ATK * 10; }
        uint_fast8_t getDEF() { return attr.DEF; }
        uint_fast8_t getACT() { return attr.ACT; }
        uint_fast8_t getLCK() { return attr.LCK; }
        int_fast16_t getHP() { return attr.HP; }
        int_fast16_t getST() { return attr.ST; }

        void attack(Actor &a);
        void attack(Entity *e);
        int_fast8_t defend(uint_fast8_t dmg);

        uint_fast8_t getChance() { return attr.LCK * 10; }

        std::string getStatus();  // TODO return text summary of HP, ST, etc

        void addTarget(Actor *a);
        bool hasTarget(vec2ui cell);

    protected:
        int   steps = 0;
        int   ticks = 0;
        Attributes attr;
        std::vector<Actor> *targets;
        Actor *target = 0;
};

#endif

