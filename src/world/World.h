#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Map.h"

/*
 * Singleton candidate
 * XXX unused for the nonse, just got through Map
 */
class World {
    public:
        static World *get() {
            if ( ! instance) instance = new World();
            return instance;
        };
        void pushMap(Map map);

    private:
        static World *instance;
        std::vector<Map> maps;
};

#endif
