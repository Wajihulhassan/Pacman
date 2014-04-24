#ifndef PACMAN_H
#define PACMAN_H
#include "Character.h"
#include "curses.h"
#include "Maze.h"
#include "iostream"
class Pacman :public Character
{
    public:
        Pacman(int , int,char c[][80]);
        ~Pacman();
        void moveShow(int, int , char);
        bool movep();
        char dir ;
        bool collision();
        bool collisionM;
        int eatMonster;
        int score;
        int repeater;
        char maze[30][80];
        bool alive;
        bool bonus;
        bool bonusEnding;
        bool ghostEaten;
        bool player;
        int pacX;
        int pacY;
        int x;
        int y;
        time_t current, timer, flickerTimer;
    protected:
    private:
};

#endif // PACMAN_H
