#ifndef EDIBLE_H
#define EDIBLE_H
#include <math.h>  // Bunch of Libraries
#include <iostream>
#include <time.h>
#include <iomanip> // end of libiaries
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <curses.h>
#include "Ghost.h"
#include "Maze.h"

class eat
    {

    public:
        eat();
        void safeToEat();

    protected:

    };

eat::eat()
    {

    }// eat::eat()

void eat::safeToEat()
    {

    Maze* maze = new Maze();
    maze->showMaze();

    Ghost* ghost1 = new Ghost(9,36,'R','@' | COLOR_PAIR(3),maze->maze1);

    Ghost* ghost2 = new Ghost(11,35,'U','@' | COLOR_PAIR(3),maze->maze1);

    Ghost* ghost3 = new Ghost(11,36,'U','@' | COLOR_PAIR(3),maze->maze1);

    Ghost* ghost4 = new Ghost(11,37,'U','@' | COLOR_PAIR(3),maze->maze1);

    }// void eat::safeToEat()

#endif // EDIBLE_H
