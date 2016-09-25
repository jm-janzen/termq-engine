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

        int  getDifficulty() { return difficulty; }
        void setDifficulty(int initDifficulty) { difficulty = initDifficulty; };

    private:
        static Global *instance;

        int difficulty;

};

#endif
