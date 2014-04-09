#ifndef MAZE_H
#define MAZE_H
#include <math.h>  // Bunch of Libraries
#include <iostream>
#include <time.h>
#include <iomanip> // end of libiaries
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "PacManCharacters.h"
#include "ghosts.h"

/* This .h file makes the maze */

class maze
    {

    public:
        maze();
        ~maze();
        void makeMaze();

    protected:
        char mazeDesign[60][60];
        int x;
        int y;
        int colSize;
        int rowSize;
    };

maze::maze()
    {

    colSize = 15;

    rowSize = 20;

    }// maze::maze()


void maze::makeMaze()
    {

    int counterY = 5;

    int counterX = 5;

    //const char mazePrint;

    wbkgd( stdscr, COLOR_PAIR(6) );


        for( x = 0; x < rowSize ; x++ )
            {
            for( y = 0; y < colSize ; y++ )
                {

                mazeDesign[y][x] = 0;

                }// for( y = 0; y < colSize; y++ )

             }// for( x = 0; x < rowSize ; x++ )

    mazeDesign[0][0] = '+';

    mazeDesign[rowSize - 1][0] = '+';

    mazeDesign[0][colSize - 1] = '+';

    mazeDesign[rowSize - 1][colSize - 1] = '+';

        for( x = 1; x < rowSize - 1; x++ )
            {

            mazeDesign[x][colSize - 1] = '|';

            mazeDesign[x][0] = '|';

            }// for( x = 1; x < rowSize - 1; x++ )

        for( y = 0; y < colSize - 1; y++ )
            {

            mazeDesign[0][y] = '-';

            mazeDesign[rowSize - 1][y] = '-';

            }// for( y = 0; y < colSize; y++ )


        for( x = 0; x < rowSize - 1; x++ )
            {
            for( y = 0; y < colSize; y++ )
                {

                 //mazePrint = mazeDesign[y][x];

                wmove( stdscr, counterY, counterX );

                addch( mazeDesign[y][x] );

                }// for( y = 0; y < colSize; y++ )

                counterY++;

            }// for( x = 1; x < rowSize - 1; x++ )

    }// void maze::makeMaze()

maze::~maze()
    {

    }// maze::~maze()


#endif // MAZE_H
