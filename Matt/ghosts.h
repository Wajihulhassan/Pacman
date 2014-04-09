#ifndef GHOSTS_H
#define GHOSTS_H
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
#include "maze.h"


using namespace std;

/*This .h file holds all the ghost characters and methods that effect them.*/

class blinky
    {

    public:
        blinky();
        void ghostBuild();
        void blinkyMaker();

    protected:
        int ghostColor1;
        int ghostColor2;
        int ghostColor3;
        int ghostColor4;
        int ghostBlinky;
        int ghostInky;
        int ghostPinky;
        int ghostClyde;
        int blinkyX;
        int blinkyY;
        int inkyX;
        int inkyY;
        int pinkyX;
        int pinkyY;
        int clydeX;
        int clydeY;
        int colorChoice;

    };

class inky : public blinky
    {

    public:
        inky();
        void inkyMaker();

    };

class pinky : public blinky
    {

    public:
        pinky();
        void pinkyMaker();

    };

class clyde : blinky
    {

    public:
        clyde();
        void clydeMaker();

    };

blinky::blinky()
    {

    ghostColor1 = 1;

    ghostColor2 = 2;

    ghostColor3 = 3;

    ghostColor4 = 4;

    blinkyX = 35;

    blinkyY = 14;

    inkyX = 34;

    inkyY = 15;

    pinkyX = 35;

    pinkyY = 15;

    clydeX = 36;

    clydeY = 15;

    cout << "Ghost test" << endl;

    }// blinky::blinky()

inky::inky()
    {

    }// inky::inky()

pinky::pinky()
    {

    }// pinky::pinky()

clyde::clyde()
    {

    }// clyde::clyde()

void blinky::blinkyMaker()
    {

    colorChoice = ghostColor1;

    ghostBuild();

    }// void blinky::blinkyMaker()

void inky::inkyMaker()
    {

    colorChoice = ghostColor2;

    ghostBuild();

    }// void inky::inkyMaker()

void pinky::pinkyMaker()
    {

    colorChoice = ghostColor3;

    ghostBuild();

    }// void pinky::pinkyMaker()

void clyde::clydeMaker()
    {

    colorChoice = ghostColor4;

    ghostBuild();

    }// void clyde::clydeMaker()



void blinky::ghostBuild()
    {


    switch( colorChoice )
        {

        case(1):
            mvaddch( blinkyY, blinkyX, '@' | COLOR_PAIR(1) );
            break;

        case(2):
            mvaddch( inkyY, inkyX, '@' | COLOR_PAIR(2) );
            break;

        case(3):
            mvaddch( pinkyY, pinkyX, '@' | COLOR_PAIR(3) );
            break;

        case(4):
            mvaddch( clydeY, clydeX, '@' | COLOR_PAIR(4) );
            break;

        default:
            cout << "unkown ghost." << endl;

        }// switch( colorChoice )

    refresh();

    }

#endif // GHOSTS_H
