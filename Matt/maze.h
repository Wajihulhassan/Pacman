#ifndef MAZE_H
#define MAZE_H
#include "curses.h"


class Maze
{
    public:
        Maze();
        ~Maze();
        void showMaze();
        char maze1[30][80];
        char maze2;
        char maze3;
    protected:
    private:

};

#endif // MAZE_H
