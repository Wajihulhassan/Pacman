#ifndef PACMANCHARACTERS_H
#define PACMANCHARACTERS_H
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
#include "ghosts.h"
#include "maze.h"

using namespace std;

/*This .h file contains all of the characters. The classes of pacman, ghosts, and fruit
are grouped together because they all have some form of connection. Pacman influences
the ghosts and fruits. The ghosts have no connection to the fruit. The ghost also influence
pacman.*/

class pacMan
    {

    public:
        pacMan();
        void pacManMover();// This will move pacman.
        int movementChecker( int, int );//This checks if the move is allowed.
        void pacManEat( char ); // This checks what pacman is eating.

    protected:
        int posX;
        int posY;
        int tempX;
        int tempY;
        int pacManChar;
        int pelletCounter;
        int scoreKeeper;
        bool alive;


    };

class fruit: public pacMan
    {

    public:
        fruit();

    protected:

    };


pacMan::pacMan()
    {

    cout << "Test" << endl;

    posX = 30;

    posY = 10;

    alive = true;

    }

void pacMan::pacManMover()
    {

    maze printMaze;
    blinky createBlinky;
    inky createInky;
    pinky createPinky;
    clyde createClyde;

    while( alive == true )
    {

    wbkgd( stdscr, COLOR_PAIR(5) );

    while( 5 )
        {

        printMaze.makeMaze();

        createBlinky.blinkyMaker();

        createBlinky.ghostBuild();

        createInky.inkyMaker();

        createBlinky.ghostBuild();

        createPinky.pinkyMaker();

        createBlinky.ghostBuild();

        createClyde.clydeMaker();

        createBlinky.ghostBuild();

        wmove( stdscr, posY, posX );

        addch('P' | COLOR_PAIR(5));

        pacManChar = getch();

        if( pacManChar == KEY_DOWN )
            {

            posY ++;

            clear();

            }// if( pacManChar == KEY_DOWN )

        if( pacManChar == KEY_UP )
            {

            posY --;

            clear();

            }// if( pacManChar == KEY_UP )

        if( pacManChar == KEY_LEFT )
            {

            posX --;

            clear();

            }// if( pacManChar == KEY_LEFT )

        if( pacManChar == KEY_RIGHT )
            {

            posX ++;

            clear();

            }// if( pacManChar == KEY_RIGHT )

        refresh();

        }// while( 6 )


    }// while( alive == true )

    }// void pacMan::pacManMover()

//int pacMan::movementChecker( int PosCalled, int newPos )
   // {



//}// int pacMan::movementChecker( int PosCalled, int newPos )

void pacMan::pacManEat( char edible )
    {
    //This is going to go into an if statement so it is not checked when there is nothing
    // in the space.
    int whatWasEaten = static_cast<int>(edible);

    switch( whatWasEaten )
        {

        case(79):
            cout << "PowerPellet" << endl;
            break;

        case(103):
            cout << "Ghost" << endl;
            break;

        case(111):
            cout << "Pellet" << endl;
            break;

        default:
            cout << "An error occured from the input." << endl;
            break;

        }// switch( whatWasEaten )

    }// void pacMan::pacManEat( char edible )

#endif // PACMANCHARACTERS_H
