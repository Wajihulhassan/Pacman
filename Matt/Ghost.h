#ifndef GHOST_H
#define GHOST_H
#include "Character.h"
#include "curses.h"
#include <cstdlib> // for RANODM function
class Ghost
{
    public:
        Ghost(int , int , char, int, char m[][80]);
        ~Ghost();
        void moveG();
        bool collisionM();
        char maze[30][80];
        char arrdirm[4]= {'R','L','U','D'};
    protected:
    private:
        char dir;
        int icon;
        int x;
        int y;
        bool chkfood;
        bool chkbonus;
        void foodPutter(int , int );
};

#endif // GHOST_H