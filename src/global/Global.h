#ifndef GLOBAL_H
#define GLOBAL_H

/*
 * TODO
 *  Eventually define some useful structs for
 *  passing pack more complex information, but
 *  for now just use `int difficulty.'
 */

class Global {
    public:
        /* Singleton */
        static Global *get() {
            if ( ! instance) instance = new Global();
            return instance;
        };

        void tick() { ticks++; }

        void setDifficulty(int initDifficulty) { difficulty = initDifficulty; };

        int  getDifficulty() { return difficulty; }
        int  getTicks() { return ticks; }

    private:
        static Global *instance;

        int difficulty = 0;
        int ticks      = 0;

};

#endif
