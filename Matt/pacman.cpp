#include <time.h>
#include "pacman.h"


Pacman::Pacman(int a, int b, char c[][80]):x(a), y(b)
{
    for(int i =0 ;i < 30 ; i++){
        for(int k=0;k<80;k++){
            maze[i][k]= c[i][k];
        }
    }
    alive = true;

    bonus = false;

    bonusEnding = false;

    ghostEaten = false;

    current = 0;

    flickerTimer = 0;

    pacX = 0;

    pacY = 0;

}
void Pacman::moveShow(int a, int b, char c){

    this->x =a;
    this->y =b;
    move(b,a);
    addch(c);
    dir = 'r';
    score =0;
    repeater =0;
}
bool Pacman::movep(){
     // initialization of character
    wtimeout(stdscr,170);
    move(1,31);

    // This checks if the ghosts change back to normal.

    if( time(NULL) >= timer )
        {

        bonus = false;

        bonusEnding = false;

        current = 0;

        flickerTimer = 0;

        }// if( time(NULL) >= timer )

    // This if statement makes the ghosts flicker color to indicate that they will
    // change back soon.

    if( flickerTimer != 0 && time(NULL) >= flickerTimer )
        {


        if( time(NULL) % 2 == 1 )
            {

            bonusEnding = true;

            bonus = false;

            }// if( time(NULL) % 2 == 0 )

        else
            {

            bonusEnding = false;

            bonus = true;

            ghostEaten = false;

            }// else of if( time(NULL) % 2 == 0 )

        }// if( time(NULL) >= flickerTimer )

    // score displaying
    attron(A_REVERSE|COLOR_PAIR(1));
    printw(" SCORE = %d ",score);
    attroff(A_REVERSE|COLOR_PAIR(1));
       int g=getch();
     //attron(COLOR_PAIR(1));
      if(g==ERR){
	  	switch(dir){
	    	case('r'):
	    		if(!collision()){
	      			mvaddch(y,x,' ');
	      			++x;
	      			pacX = x;
	      			move(y,x);
		  		if (repeater%2==0){
		  			addch('<' | COLOR_PAIR(1));
		  			repeater++;
		  			}
	      		else{
					addch('O' | COLOR_PAIR(1));
					repeater--;
	      			}
	    		}
	    		refresh();
	    		break;
	    	case('l'):
				if(!collision()){
		    		mvaddch(y,x,' ');
		    		--x;
		    		pacX = x;
		    		move(y,x);
		    	if (repeater%2==0){
		    		addch('>' | COLOR_PAIR(1));
		      		repeater++;
					}
	      		else{
					addch('O' | COLOR_PAIR(1));
					repeater--;
	      			}
	   			 }
	    		refresh();
	    		break;
	    	case('u'):
				if(!collision()){
		    		mvaddch(y,x,' ');
		    		--y;
		    		pacY = y;
		    		move(y,x);
		  		if (repeater%2==0){
		      		addch('V' | COLOR_PAIR(1));
		      		repeater++;
		      			}
				else{
			  		addch('O' | COLOR_PAIR(1));
			  		repeater--;
			    }
				}
	      		refresh();
	      		break;
	    case('d'):
	       if(!collision()){
		  		mvaddch(y,x,' ');
		  		++y;
		  		pacY = y;
		  		move(y,x);
		  if (repeater%2==0){
				addch('^' | COLOR_PAIR(1));
				repeater++;
			  }
		   else{
				addch('O' | COLOR_PAIR(1));
		      	repeater--;
				}
	     	}
	      //attroff(COLOR_PAIR(1));
	      refresh();
	      break;
    }// End of switch conditions
      // checking if player press q
  }else if (g=='q'){
	return false;
      }
      // Getting keyboard inputs
  else{

	    switch(g){
	      case KEY_LEFT:
	      dir='l';
	      mvaddch(y,x,' ');
	      move(y, x);
	      	addch('>');
	     if(!collision()){
		    		mvaddch(y,x,' ');
		    		--x;
		    		pacX = x;
		    		move(y,x);
		    	if (repeater%2==0){
		    		addch('>');
		      		repeater++;
					}
	      		else{
					addch('O');
					repeater--;
	      			}
	   			 }
	    		refresh();
	    		break;

	      case KEY_RIGHT:
	      dir='r';
	      mvaddch(y,x,' ');
	      move(y,x);
	      	addch('<');
	      if(!collision()){
	      			mvaddch(y,x,' ');
	      			++x;
	      			pacX = x;
	      			move(y,x);
		  		if (repeater%2==0){
		  			addch('<');
		  			repeater++;
		  			}
	      		else{
					addch('O');
					repeater--;
	      			}
	    		}
	    		refresh();
	      break;
	      case KEY_UP:
	      dir='u';
	      mvaddch(y,x,' ');
	      move(y, x);
	      addch('V');
            if(!collision()){
		    		mvaddch(y,x,' ');
		    		--y;
		    		pacY = y;
		    		move(y,x);
		  		if (repeater%2==0){
		      		addch('V');
		      		repeater++;
		      			}
				else{
			  		addch('O');
			  		repeater--;
			    }
				}
	      		refresh();
	      break;
	      case KEY_DOWN:
	      dir='d';
	      mvaddch(y,x,' ');
	      move(y,x);
	      addch('^');
	      if(!collision()){
		  		mvaddch(y,x,' ');
		  		++y;
		  		pacY = y;
		  		move(y,x);
		  if (repeater%2==0){
				addch('^');
				repeater++;
			  }
		   else{
				addch('O');
		      	repeater--;
				}
	     	}
	     // attroff(COLOR_PAIR(1));
	      refresh();
	      break;
	  }
    }
  refresh();
  return true; // player doesnt press q

}
bool Pacman::collision(){
    int xx;
	int yy;
	if(dir=='r'){
	  xx=x+1;
	  yy=y;

	  pacX = x;

	  pacY = y;

	  }
	if(dir=='l'){
	  xx=x-1;
	  yy=y;

	  pacX = x;

	  pacY = y;

	  }
	if (dir=='d'){
	  yy=y+1;
	  xx=x;

	  pacX = x;

	  pacY = y;

	  }
	if(dir=='u'){
	  yy=y-1;
	  xx=x;

	  pacX = x;

	  pacY = y;

	  }
	  // collision with walls
	if (dir!='n'){
	    if (maze[yy][xx]=='#'){
	    dir='n';// making it still at a position
	    return true;
	    }
	  }
    char g= mvinch(yy,xx);
    char k= mvinch(y,x);
	refresh();
	// checking collision with monster
// 	 if(maze[pac.y][pac.x]== '$'){
// 	 	 score=score+10;
// 	}
	if(maze[yy][xx]== '$'){
	 	 score=score+10;
	}
	if(maze[y][x]== '%'){


        bonus = true;

        time(&current);

        timer = current + 20;

        flickerTimer = current + 10;

		maze[y][x]= ' ';
	}
	if(maze[yy][xx]== '%'){
	 	// score=score+10;
	}
     if (g =='@'){
       if(eatMonster==0){
            collisionM=true;
       }

     else if(eatMonster==1){
	 		//score=score+10;
      		}
    	}
     if (k=='@'){
       if(eatMonster==0){
            collisionM=true;
        }
     }

    // checking collision with food and incrementing score
      if (maze[y][x]=='*'){
			score++;

            maze[y][x] = ' ';

        //checks if your score is high enough for a win.

	    if (score>=400){

            ghostEaten = false;

	    }
		return false;
		}

      return false;// overall returning false if nothing is collided with pacman
}
Pacman::~Pacman()
{
    //dtor
}

