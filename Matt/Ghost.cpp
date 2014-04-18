#include <time.h>
#include "Ghost.h"

Ghost::Ghost(int a, int b, char c, int d, int blueGhost, int whiteGhost,int ghostConsumed, char m[][80]): y(a), x(b)
{
    dir  = c;
    icon = d;
    newGhost = blueGhost;
    cautionGhost = whiteGhost;
    eyesOfGhosts = ghostConsumed;
    mvaddch(a,b,icon);
    for(int i =0 ;i < 30 ; i++){
        for(int k=0;k<80;k++){
            maze[i][k]= m[i][k];
        }
    }

    ghostEaten = false;

    chkfood= false;
}
void Ghost::moveG(bool bonus, bool bonusEnding ){
    if (dir=='R'){
	    if(!collisionM()){
	      	mvaddch(y,x,' ');
	     	foodPutter(y,x);
	      	++x;

             // The if, else if, and else determine the color of the ghosts.
		 	 if(bonus)
                {

                mvaddch( y, x, newGhost );

                ghostEaten = true;

                }// if(bonus)

            else if(bonusEnding)
                {

                mvaddch( y, x, cautionGhost );

                ghostEaten = true;

                }// else if(bonusEnding)

             else
                {

                mvaddch( y, x, icon );

                ghostEaten = false;

                }// else of if(bonus)

		}
	  refresh();
	  }
	else if(dir=='L')
	 	{
		if(!collisionM()){
			mvaddch(y,x,' ');
			foodPutter(y,x);
			--x;

		 	 if(bonus)
                {

                mvaddch( y, x, newGhost );

                ghostEaten = true;

                }// if(bonus)

             else if(bonusEnding)
                {

                mvaddch( y, x, cautionGhost );

                ghostEaten = true;

                }// else if(bonusEnding)

             else
                {

                mvaddch( y, x,icon );

                ghostEaten = false;

                }// else of if(bonus)

		}
		refresh();
	 }
	else if(dir == 'U')
	    {
		if(!collisionM()){
		  	mvaddch(y,x,' ');
            foodPutter(y,x);
		  	--y;

		 	 if(bonus)
                {

                mvaddch( y, x, newGhost );

                ghostEaten = true;

                }// if(bonus)

             else if(bonusEnding)
                {

                mvaddch( y, x, cautionGhost );

                ghostEaten = true;

                }// else if(bonusEnding)

             else
                {

                mvaddch( y, x, icon );

                ghostEaten = false;

                }// else of if(bonus)

		    }
	      refresh();
	    }
	  else if (dir =='D')
	     {
	       if(!collisionM()){
		  	mvaddch(y,x,' ');
            foodPutter(y,x);
		 	 ++y;
		 	 //attron(COLOR_PAIR(colorswitch));

		 	 if(bonus)
                {

                mvaddch( y, x, newGhost );

                ghostEaten = true;

                }// if(bonus)

             else if(bonusEnding)
                {

                mvaddch( y, x, cautionGhost );

                ghostEaten = true;

                }// else if(bonusEnding)

             else
                {

                mvaddch( y, x, icon );

                ghostEaten = false;

                }// else of if(bonus)

		 	 //attroff(COLOR_PAIR(colorswitch));

		 	 }
	      refresh();
	     }
	    int  t=rand()%20;
	     if (t==0){
	       dir = arrdirm[(rand()%4)];
	    }

}
bool Ghost::collisionM(){
    //if it collides with wall move randomly to other direction and do it again and again
    int ix;
    int iy;
    int r;
    char arrdirm[4]= {'R','L','U','D'};
	if(dir=='R'){
        ix=x+1;
        iy=y;
	}
	if (dir == 'L'){
        ix=x-1;
        iy=y;
    }
	if (dir=='D'){
        iy=y+1;
        ix=x;
    }
	if (dir=='U'){
        iy=y-1;
        ix=x;
    }
	if(maze[y][x]=='*'){
        chkfood=true;
	    }else{
		chkfood=false;
        };
	if(maze[y][x]=='%'){
        chkbonus=true;
	    }else{
		chkbonus=false;
		  };

    if(ghostEaten)
        {

        if((mvinch(iy,ix)=='<')||(mvinch(iy,ix)=='>')||(mvinch(iy,ix)=='V')||(mvinch(iy,ix)=='O')||(mvinch(iy,ix)=='^'))
            {

            mvaddch( y, x, eyesOfGhosts );

            }// if((mvinch(iy,ix)=='<')||(mvinch(iy,ix)=='>')||(mvinch(iy,ix)=='V')||(mvinch(iy,ix)=='O')||(mvinch(iy,ix)=='^'))

        else
            {



            } // else of if((mvinch(iy,ix)=='<')||(mvinch(iy,ix)=='>')||(mvinch(iy,ix)=='V')||(mvinch(iy,ix)=='O')||(mvinch(iy,ix)=='^'))

        if ((mvinch(y,x)=='<')||(mvinch(y,x)=='>')||(mvinch(y,x)=='V')||(mvinch(y,x)=='O')||(mvinch(y,x)=='^'))
            {

            mvaddch( y, x, eyesOfGhosts );

            }// if ((mvinch(y,x)=='<')||(mvinch(y,x)=='>')||(mvinch(y,x)=='V')||(mvinch(y,x)=='O')||(mvinch(y,x)=='^'))

        else
            {

            // collisionmp=true;

            }// else of if ((mvinch(y,x)=='<')||(mvinch(y,x)=='>')||(mvinch(y,x)=='V')||(mvinch(y,x)=='O')||(mvinch(y,x)=='^'))

        }// if(ghostEaten)

	// Wall checking
	 //attron(COLOR_PAIR(4));
	if (maze[iy][ix]=='#'){
	   do{
            r=(rand()%4);
	  }while(arrdirm[r]==dir);
	// assigning new direction to ghost
        dir=arrdirm[r];
	 //attroff(COLOR_PAIR(4));
	  return true;
	  }
    return false; // nothing collides returning false


}
void Ghost::foodPutter(int j,int k){
    if(chkfood){
        attron(COLOR_PAIR(1));
        mvaddch(j,k,'*');
        attroff(COLOR_PAIR(1));
    }
    if(chkbonus){
        attron(COLOR_PAIR(8)|A_STANDOUT);
        mvaddch(j,k,'%');
        attroff(COLOR_PAIR(8)|A_STANDOUT);
    }

  }
Ghost::~Ghost()
{
    //dtor
}

