#include "Maze.h"

Maze::Maze():

    maze1
	  {   "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",
	      "S##############################            ###############################S",
	      "S# *************************  ##############  ************************** #S",
	      "S# *###########*###########********************############*###########* #S",
	      "S# *#+++++++++#*#+++++++++#********###########*#++++++++++#*#+++++++++#* #S",
	      "S# *#+++#######*#######+++#*********** ##+++##*#+++########*#######+++#* #S",
	      "S# *#+++#******%***** #####* ########* #######*#####  *****%******#+++#* #S",
	      "S# *#+++#*##########******** ##XXXX##******************##########*#+++#* #S",
	      "S# *#####*#XXXXXXXX#*#####*  #################  *#####*#XXXXXXXX#*#####* #S",
	      "S#********##########*##+##***********************##+##*##########********#S",
	      "S#*##### ************#+++#*  ######     ######  *#+++#************ #####*#S",
	      "S#*#+++#######*#######+++#*  ##             ##  *#+++#######*#######+++#*#S",
	      "S#*#+++++++++#*#+++++++++#*  #################  *#+++++++++#*#+++++++++#*#S",
	      "S#*#+++#######*#######+++#***********************#+++#######*#######+++#*#S",
	      "S#*##### ************#+++#* ######## * ######## *#+++#************ #####*#S",
	      "S#********##########*##+##* ##XXXX## * ##XXXX## *##+##*##########********#S",
	      "S# *#####*#XXXXXXXX#*#####* ######## * ######## *#####*#XXXXXXXX#*#####* #S",
	      "S# *#+++#*##########******* ##XXXX## * ##XXXX## *******##########*#+++#* #S",
	      "S# *#+++#******%*****  ############# * #############  *****%******#+++#* #S",
	      "S# *#+++#######*   ####+++#********************#+++#####   *#######+++#* #S",
	      "S# *#+++++++++#*  ##++++++#*##################*#+++++++##  *#+++++++++#* #S",
	      "S# *###########* ##########*#                #*########### *###########* #S",
	      "S# *************************#                #************************** #S",
	      "S############################                #############################S",
	      "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",
	      "S                                S      S                                 S",
	      "S                                S      S                                 S",
	      "S                                S      S                                 S",
	      "S                                S      S                                 S",
	      "SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS",

	  }{

}

Maze::~Maze()
{
    //dtor
}
void Maze::showMaze(){
        start_color();
        init_pair(1, COLOR_YELLOW , COLOR_BLACK);// food
	    init_pair(2, COLOR_RED , COLOR_BLACK);// monsters
	    init_pair(3, COLOR_BLUE , COLOR_BLACK);// time period u can eat monster
	    init_pair(4, COLOR_CYAN  , COLOR_BLACK);
	    init_pair(5, COLOR_GREEN  , COLOR_BLACK);
	    init_pair(6, COLOR_WHITE  , COLOR_BLACK);
	    init_pair(7, COLOR_YELLOW  , COLOR_BLACK);
	    init_pair(8, COLOR_WHITE  , COLOR_RED);
	    init_pair( 9, COLOR_MAGENTA, COLOR_BLACK );
	  char  bound = char(219);
	  	// Making overall maze
	for (int i=0;i<30;i++){
	  for(int k=0;k<75;k++){
		if (maze1[i][k]=='#'){
		  	attron(COLOR_PAIR(5)|A_STANDOUT|A_DIM |A_INVIS );
			mvaddch(i,k,maze1[i][k]);
			attroff(COLOR_PAIR(5)|A_STANDOUT|A_DIM |A_INVIS );
		}
		else if(maze1[i][k]=='S'){
		  	// attron(A_STANDOUT);
            attron(COLOR_PAIR(5));
		  	 mvaddch(i,k,bound);
			 attroff(COLOR_PAIR(5));
		  	// attroff(A_STANDOUT);
		}
		else if(maze1[i][k]=='%'){

		  	attron(COLOR_PAIR(4)|A_STANDOUT);
		  	 mvaddch(i,k,'%');
			 attroff(COLOR_PAIR(4)|A_STANDOUT);

		}
		else if(maze1[i][k]=='*'){
		   	attron(COLOR_PAIR(1));
		   	mvaddch(i,k,maze1[i][k]);
			attroff(COLOR_PAIR(1)); }
		else{
		  	mvaddch(i,k,maze1[i][k]);
		}
	  }// inner loop ends

	}// outer loops ends
	// COPYRIGHTS and Instructions
	refresh();
    move(24,5);
	attron((A_REVERSE)|COLOR_PAIR(1));
	printw("INSTRUCTIONS");
	attroff((A_REVERSE)|COLOR_PAIR(1));
	attron(COLOR_PAIR(7));
	mvprintw(25,1,"1)Press q key to quit the game  ");
	mvprintw(26,1,"2)Eat monster when they are BLUE");
	mvprintw(27,1,"3)After eating ghost it reapper ");
	mvprintw(28,1,"4)Boast your points by eating $ ");
	attroff(COLOR_PAIR(7));
	refresh();
	move(0,26);
	attron(A_REVERSE|COLOR_PAIR(5));
	printw("PACMAN BY WAJIH UL HASSAN");
	attroff(A_REVERSE|COLOR_PAIR(5));
}

