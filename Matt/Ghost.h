#ifndef GHOST_H
#define GHOST_H
#include "Character.h"
#include "curses.h"
#include <cstdlib> // for RANODM function
class Ghost
{
    public:
        Ghost(int , int , char, int, int , int, int, char m[][80]);
        ~Ghost();
        void moveG( bool, bool, int, int );
        bool collisionM( int, int );
        char maze[30][80];
        char arrdirm[4]= {'R','L','U','D'};
        bool playing;
    protected:
    private:
        char dir;
        int icon;
        int x;
        int y;
        int checkY;
        int checkX;
        int newGhost;
        int cautionGhost;
        int eyesOfGhosts;
        bool ghostEaten;
        bool chkfood;
        bool chkbonus;
        bool spaceChecker; // Keeps the spaces that are empty from being filled with pellets.
        void foodPutter(int , int );
};

#endif // GHOST_H
