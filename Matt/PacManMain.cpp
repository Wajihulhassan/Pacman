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
#include "PacManCharacters.h"
#include "ghosts.h"
#include "maze.h"

using namespace std;

int main()
    {

    char input;
    pacMan game1;

    //blinky game2;
    //inky game3;
    //pinky game4;
    //clyde game5;

    initscr();

    curs_set(0);

    keypad( stdscr, TRUE );

    noecho();

    start_color();

    init_pair( 1, COLOR_RED, COLOR_BLACK );

    init_pair( 2, COLOR_CYAN, COLOR_BLACK );

    init_pair( 3, COLOR_MAGENTA, COLOR_BLACK );

    init_pair( 4, COLOR_YELLOW, COLOR_BLACK );

    init_pair( 5, COLOR_YELLOW, COLOR_BLACK );

    init_pair( 6, COLOR_WHITE, COLOR_BLACK );
    //game2.ghostBuild();

    //game2.blinkyMaker();

    //game3.inkyMaker();

    //game4.pinkyMaker();

    //game5.clydeMaker();

    game1.pacManMover();

    //cout << "enter a char." << endl;

    //cin >> input;

    //game.pacManEat( input );

    endwin();

    return 0;

    }// int main()
