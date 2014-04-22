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

    playing = true;

    checkY = 0;

    checkX = 0;

    chkfood= false;

    spaceChecker = false;

}
void Ghost::moveG(bool bonus, bool bonusEnding, int pacX, int pacY ){
    if (dir=='R'){
	    if(!collisionM()){

                mvaddch( y, x, ' ' );

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

        checkY = pacY;

        checkX = pacX;

		}
	  refresh();
	  }
	else if(dir=='L')
	 	{
		if(!collisionM()){

            mvaddch( y, x, ' ' );

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

        checkY = pacY;

        checkX = pacX;

		}
		refresh();
	 }
	else if(dir == 'U')
	    {
		if(!collisionM()){

            mvaddch( y, x, ' ' );

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

            checkY = pacY;

            checkX = pacX;

		    }
	      refresh();
	    }
	  else if (dir =='D')
	     {
	       if(!collisionM()){

            mvaddch( y, x, ' ' );

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


             checkY = pacY;

             checkX = pacX;

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

    if((mvinch(iy,ix)== '<' | COLOR_PAIR(1) ) ||(mvinch(iy,ix)== '>' | COLOR_PAIR(1) ) ||(mvinch(iy,ix)== 'V' | COLOR_PAIR(1) ) ||(mvinch(iy,ix)== 'O' | COLOR_PAIR(1) ) ||(mvinch(iy,ix)=='^' | COLOR_PAIR(1) ) )
        {

        if(!ghostEaten)
            {

            playing = false;

            //mvaddch( y, x, eyesOfGhosts );

            }// if(ghostEaten)

        //else
        //{

        //playing = false;

        //}// else of if (!ghostEaten)


        }// if((mvinch(iy,ix)== mvinch( checkY, checkX )))

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

    //This statement checks if there is an empty space.
    if( chkfood != true && chkbonus != true )
        {

        spaceChecker = true;

        }// if( chkfood != true && chkbonus != true )


    else
        {

        spaceChecker = false;

        }// else of if( chkfood != true && chkbonus != true )


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
    // This makes sure that the space is not overwritten
    if( spaceChecker == true )
        {

        mvaddch( j, k, ' ' );

        }// if( spaceChecker )

  }
Ghost::~Ghost()
{
    //dtor
}

