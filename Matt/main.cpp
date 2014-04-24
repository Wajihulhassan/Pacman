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
#include "sokobanHeader.h"

using namespace std;

void GameLoop(int LoopCounter);
void ColorChanger();
void breakTime(int seconds);
bool IsBigBlockOnBigHole(BigBlock TheBlock, BigBlockHole TheHole);
void Restart(int X, int Y, MainWindow& GameMap);
// holds the function to play sokoban.
void sokobanFunction();
// holds the function to play pacman.
void pacManFunction();
void splashscreen();
void initialization();
void gameOverWin();
void gameOverLose();
// This is where you choose to play sokoban or pacMan.
int main()
    {

    bool continuePlaying = true;
    char whatToPlay = 'n';

    while(continuePlaying)
        {

        cout << "What do you want to play?" << endl;

        cout << "P or p = pacMan" << endl;

        cout << "S or s = sokoban " << endl;

        cin >> whatToPlay;

        switch( whatToPlay )
            {

            case('p'):
                pacManFunction();
                break;

            case('P'):
                pacManFunction();
                break;

            case('s'):
                sokobanFunction();
                break;

            case('S'):
                sokobanFunction();
                break;

            default:
                cout << "That is not a choice." << endl;
                break;

            }// switch( whatToPlay )

            cout << "Do you want to stop? Enter N or n to stop." << endl;

            cin >> whatToPlay;

            if( whatToPlay == 'N' || whatToPlay == 'n' )
                {

                continuePlaying = false;

                }// if( whatToPlay == 'N' || whatToPlay == 'n' )

            else
                {

                continuePlaying = true;

                }// else of if( whatToPlay == 'N' || whatToPlay == 'n' )

        }// while(continuePlaying)

    return 0;

    }
// Location for the code to play pacMan.
void pacManFunction()
    {

    bool Playing=true;
    splashscreen();
    initialization();
    Maze* maze = new Maze();
    maze->showMaze();
    Pacman* pac = new Pacman(20,20,maze->maze1);
    pac->moveShow(36,13,'O');
    Ghost* ghost1 = new Ghost(9,36,'R','@' | COLOR_PAIR(2), '@' | COLOR_PAIR(3), '@' | COLOR_PAIR(6), ':' | COLOR_PAIR(6), maze->maze1);
    Ghost* ghost2 = new Ghost(11,35,'U','@' | COLOR_PAIR(4), '@' | COLOR_PAIR(3), '@' | COLOR_PAIR(6), ':' | COLOR_PAIR(6), maze->maze1);
    Ghost* ghost3 = new Ghost(11,36,'U','@' | COLOR_PAIR(9), '@' | COLOR_PAIR(3), '@' | COLOR_PAIR(6),  ':' | COLOR_PAIR(6), maze->maze1);
    Ghost* ghost4 = new Ghost(11,37,'U','@' | COLOR_PAIR(1), '@' | COLOR_PAIR(3), '@' | COLOR_PAIR(6),  ':' | COLOR_PAIR(6), maze->maze1);
    while (Playing){
        Playing = pac->movep();
        ghost1->moveG(pac -> bonus, pac -> bonusEnding, pac -> pacY, pac -> pacX );
        ghost2->moveG(pac -> bonus, pac -> bonusEnding, pac -> pacY, pac -> pacX );
        ghost3->moveG(pac -> bonus, pac -> bonusEnding, pac -> pacY, pac -> pacX );
        ghost4->moveG(pac -> bonus, pac -> bonusEnding, pac -> pacY, pac -> pacX );

        if(!(ghost1 -> playing && ghost2 -> playing && ghost3 -> playing && ghost4 -> playing))
        {
            Playing = false;
        }

        if( pac -> score >= 400 )
            {

            Playing = false;

            }//if( pac -> score >= 466 )

    }

    if( pac -> score >= 400 )
        {

        gameOverWin();

        }// if( pac -> score )

    else
        {

        gameOverLose();

        }// else of if( pac -> score == 466 )

    }// void pacManFunction()

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
// This is where the code begins for sokoban.
void sokobanFunction()
    {

    //init_pair(4,COLOR_GREEN,COLOR_GREEN);
    GameLoop(1);

    }// void sokobanFunction()

void GameLoop(int LoopCounter)
{
    int x=1;
    int y=1;
    int ch;
    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1,COLOR_BLUE,COLOR_BLACK);
    // Added Change
    init_pair( 2, COLOR_CYAN, COLOR_BLACK );
    init_pair( 3, COLOR_YELLOW, COLOR_BLACK );
    init_pair( 4, COLOR_GREEN, COLOR_BLACK );
    // Changes end
    wbkgd(stdscr, COLOR_PAIR(1));
    MainWindow NewWindow;
    /*
    Block FirstBlock(5,5,NewWindow);
    Block SecondBlock(17,17,NewWindow);

    BlockHole FirstBlockHole(10,15,NewWindow);
    BlockHole SecondBlockHole(15,3,NewWindow);
    */

    BigBlock FirstBigBlock(3,3,NewWindow);
    BigBlock SecondBigBlock(17,16,NewWindow);

    BigBlockHole FirstBigBlockHole(10,5,NewWindow);
    BigBlockHole SecondBigBlockHole(13,16,NewWindow);
    Cross GameCross(NewWindow);


    int LoopInt=1;
    //NewWindow.setInfo('#',5,5);
    while(LoopInt==1)
    {
        /*
        if(x==18&&y==23)
        {
            GameLoop(1);
        }
        */
        BigBlockHole FirstBigBlockHole(10,5,NewWindow);
        BigBlockHole SecondBigBlockHole(13,16,NewWindow);
        Cross GameCross(NewWindow);

        //BlockHole FirstBlockHole(10,15,NewWindow);
        //BlockHole SecondBlockHole(15,3,NewWindow);
        //int CountToWin=0;
        //ColorChanger();
        /*
        if(FirstBlock.ReturnX()==FirstBlockHole.ReturnY()&&FirstBlock.ReturnY()==FirstBlockHole.ReturnX()///if first block is on top of first block hole
           &&SecondBlock.ReturnX()==SecondBlockHole.ReturnY()&&SecondBlock.ReturnY()==SecondBlockHole.ReturnX()///and if second block is on top of second block hole
            ||FirstBlock.ReturnX()==SecondBlockHole.ReturnY()&&FirstBlock.ReturnY()==SecondBlockHole.ReturnX()///or if first block is on top of second block hole
           &&SecondBlock.ReturnX()==FirstBlockHole.ReturnY()&&SecondBlock.ReturnY()==FirstBlockHole.ReturnX())///and if second block is on top of first block hole


        {
            LoopInt++;
        }
        */
        if(((IsBigBlockOnBigHole(FirstBigBlock, FirstBigBlockHole)==true)
           ||(IsBigBlockOnBigHole(SecondBigBlock,FirstBigBlockHole)==true))
           &&
           ((IsBigBlockOnBigHole(FirstBigBlock,SecondBigBlockHole)==true)
           ||(IsBigBlockOnBigHole(SecondBigBlock,SecondBigBlockHole)==true)))
        {
            LoopInt++;
        }


        NewWindow.ShowWindow();
        wmove(stdscr,y,x);
        addch(ACS_BLOCK);
        ch=getch();

        if(ch==KEY_DOWN&&NewWindow.ReturnAt(y+1,x)!='='&&NewWindow.ReturnAt(y+1,x)!='H'&&y<23)
        {
            y++;

            if(FirstBigBlock.ReturnY()==y&&(FirstBigBlock.ReturnX()==x||FirstBigBlock.ReturnX()+1==x))
               {
                   FirstBigBlock.MoveDown(NewWindow);
               }
            if(SecondBigBlock.ReturnY()==y&&(SecondBigBlock.ReturnX()==x||SecondBigBlock.ReturnX()+1==x))
               {
                   SecondBigBlock.MoveDown(NewWindow);
               }


            /*
            if(FirstBlock.ReturnY()==y&&FirstBlock.ReturnX()==x)
            {
                FirstBlock.BlockMoveDown(NewWindow);
            }
            if(SecondBlock.ReturnY()==y&&SecondBlock.ReturnX()==x)
            {
                SecondBlock.BlockMoveDown(NewWindow);
            }
            */
            clear();

        }
        else
        {
            y=y;
            clear();
        }
        if(ch==KEY_UP&&NewWindow.ReturnAt(y-1,x)!='='&&NewWindow.ReturnAt(y-1,x)!='H'&&y>1)
        {
            y--;
            if(FirstBigBlock.ReturnY()+1==y&&(FirstBigBlock.ReturnX()==x||FirstBigBlock.ReturnX()==x-1))
            {
                FirstBigBlock.MoveUp(NewWindow);
            }
            if(SecondBigBlock.ReturnY()+1==y&&(SecondBigBlock.ReturnX()==x||SecondBigBlock.ReturnX()==x-1))
            {
                SecondBigBlock.MoveUp(NewWindow);
            }
            /*
            if(FirstBlock.ReturnY()==y&&FirstBlock.ReturnX()==x)
            {
                FirstBlock.BlockMoveUp(NewWindow);
            }
            if(SecondBlock.ReturnY()==y&&SecondBlock.ReturnX()==x)
            {
                SecondBlock.BlockMoveUp(NewWindow);
            }
            */
            clear();
        }
        else
        {
            y=y;
            clear();
        }
        if(ch==KEY_LEFT&&NewWindow.ReturnAt(y,x-1)!='='&&NewWindow.ReturnAt(y,x-1)!='H'&&x>1)
        {
            x--;
            if(FirstBigBlock.ReturnX()+1==x&&(FirstBigBlock.ReturnY()==y||FirstBigBlock.ReturnY()==y-1))
            {
                FirstBigBlock.MoveLeft(NewWindow);
            }
            if(SecondBigBlock.ReturnX()+1==x&&(SecondBigBlock.ReturnY()==y||SecondBigBlock.ReturnY()==y-1))
            {
                SecondBigBlock.MoveLeft(NewWindow);
            }
            /*
            if(FirstBlock.ReturnY()==y&&FirstBlock.ReturnX()==x)
            {
                FirstBlock.BlockMoveLeft(NewWindow);
            }
            if(SecondBlock.ReturnY()==y&&SecondBlock.ReturnX()==x)
            {
                SecondBlock.BlockMoveLeft(NewWindow);
            }
            */
            clear();
        }
        else
        {
        //x=x;int Counter=0;
        //int BiggerCounter=1;

        clear();
        }
        if(ch==KEY_RIGHT&&NewWindow.ReturnAt(y,x+1)!='='&&NewWindow.ReturnAt(y,x+1)!='H'&&x<18)
        {
            x++;
            if(FirstBigBlock.ReturnX()==x&&(FirstBigBlock.ReturnY()==y||FirstBigBlock.ReturnY()==y-1))
            {
                FirstBigBlock.MoveRight(NewWindow);
            }
            if(SecondBigBlock.ReturnX()==x&&(SecondBigBlock.ReturnY()==y||SecondBigBlock.ReturnY()==y-1))
            {
                SecondBigBlock.MoveRight(NewWindow);
            }
            /*
            if(FirstBlock.ReturnY()==y&&FirstBlock.ReturnX()==x)
            {
                FirstBlock.BlockMoveRight(NewWindow);
            }
            if(SecondBlock.ReturnY()==y&&SecondBlock.ReturnX()==x)
            {
                SecondBlock.BlockMoveRight(NewWindow);
            }
            */
            clear();
        }
        else
        {
            x=x;
            clear();
        }
        refresh();

}
endwin();
cout<<"You Win!"<<endl;
}

void ColorChanger()
{
    int Counter=2;
    int BiggerCounter=3;

    while(Counter<BiggerCounter)
        {
            if(Counter%2==0)
            {
                init_pair(1,COLOR_BLUE,COLOR_BLACK);
                breakTime(1);

            }
            if(Counter%3==0)
            {
                init_pair(1,COLOR_RED,COLOR_BLACK);
                breakTime(1);


            }
            if(Counter%4==0)
            {
                init_pair(1,COLOR_GREEN,COLOR_BLACK);
                breakTime(1);

            }
            Counter++;
            BiggerCounter++;

        }
}

void breakTime( int seconds)
{
    clock_t temp;
    temp = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < temp) {}
}



bool IsBigBlockOnBigHole(BigBlock TheBlock, BigBlockHole TheHole)
{
    if(TheBlock.ReturnX()==TheHole.ReturnX()&&
       TheBlock.ReturnX()+1==TheHole.ReturnX()+1&&
       TheBlock.ReturnY()==TheHole.ReturnY()&&
       TheBlock.ReturnY()+1==TheHole.ReturnY()+1)
    {
        return true;
    }
    else
    {
        return false;
    }

}
