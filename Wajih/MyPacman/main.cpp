#include <iostream>
#include <curses.h>// importing curses library
#include <cstdlib> // for RANODM function
#include <fstream> // for input and output of files which stores history of game
#include <string.h> // using string object
#include <time.h>
#include <unistd.h>
#include "pacman.h"
#include "Ghost.h"
#include "Maze.h"
using namespace std;


void splashscreen();
void initialization();
void gameOverWin();
void gameOverLose();
int main()
{

    bool Playing= true;
    splashscreen();
    initialization();
    Maze* maze = new Maze();
    maze->showMaze();
    Pacman* pac = new Pacman(20,20,maze->maze1);
    pac->moveShow(20,20,'<');
    Ghost* ghost1 = new Ghost(2,50,'R','@',maze->maze1);
    Ghost* ghost2 = new Ghost(22,15,'L','@',maze->maze1);
    Ghost* ghost3 = new Ghost(3,15,'U','@',maze->maze1);
    Ghost* ghost4 = new Ghost(22,50,'D','@',maze->maze1);
    while (Playing){
        Playing= pac->movep();
        ghost1->moveG();
        ghost2->moveG();
        ghost3->moveG();
        ghost4->moveG();
    }
    return 0;
}
void splashscreen(){
    string name;
     cout<<"*****************************************************************************************"<< endl;
     cout<<"*****************************************************************************************"<< endl;
     cout<<"*****************************************************************************************"<< endl;
    cout<<"  ______   ______    _______   _______     __    __       ___      .______       _______  "<< endl;
    cout<<" /      | /  __  /  |       / |   ____|   |  |  |  |     /   /     |   _  /     |       / "<< endl;
    cout<<"|  ,----'|  |  |  | |  .--.  ||  |__      |  |__|  |    /  ^  /    |  |_)  |    |  .--.  |"<< endl;
    cout<<"|  |     |  |  |  | |  |  |  ||   __|     |   __   |   /  /_/  /   |      /     |  |  |  |"<< endl;
    cout<<"|  `----.|  `--'  | |  '--'  ||  |____    |  |  |  |  /  _____  /  |  |/  /----.|  '--'  |"<< endl;
    cout<<" /______| /______/  |_______/ |_______|   |__|  |__| /__/     /__/ | _| `._____||_______/ " << endl;
       cout<<"  "<< endl;
    cout<<"******************************************************************************************"<< endl;
    cout<<"******************************************************************************************"<< endl;
    cout<<"******************************************************************************************";
    cout<<""<< endl;
    cout << " --------------------------- -----------------  "<< endl;
    cout<< "ENTER YOUR NAME : Atmost 10 letters"<< endl;
    cin>> name;
  }
void initialization(){
    // ncurese must initials
	    initscr();
	    raw();
	    keypad(stdscr,TRUE);
	    noecho();
	    curs_set(0);
	   // seeding random function
	    srand(time(NULL));
	    start_color();

}
void gameOverWin(){
    for(int i=1; i<=10 ; i++) {
		attron(A_REVERSE|COLOR_PAIR(i%2+2));
		mvprintw(5,5,"********************************************************");
        mvprintw(6,5,"********************************************************");
		mvprintw(8,5,"********************************************************");
		mvprintw(9,5,"********************************************************");
        attroff(COLOR_PAIR(i%2+2));
        mvprintw(7,5,"                  WINNER                               ");
        refresh();
		attroff(A_REVERSE);
        usleep(179999);
    } //pausing after game over
}
void gameOverLose(){
    for(int i=1; i<=10 ; i++) {
		attron(A_REVERSE|COLOR_PAIR(i%2+2));
		mvprintw(5,5,"********************************************************");
        mvprintw(6,5,"********************************************************");
		mvprintw(8,5,"********************************************************");
		mvprintw(9,5,"********************************************************");
        attroff(COLOR_PAIR(i%2+2));
        mvprintw(7,5,"                  You Lose                           ");
        refresh();
		attroff(A_REVERSE);
        usleep(179999);
    }
}
