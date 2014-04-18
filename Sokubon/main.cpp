#include <iostream>
#include <curses.h>
#include <vector>
#include <ctime>


using namespace std;




void GameLoop(int LoopCounter);
void ColorChanger();
void breakTime(int seconds);


class MainWindow
{
public:
    MainWindow();

    void ShowWindow();
    void HideWindow();
    void MoveWindow();
    ~MainWindow()
    {
        std::cout << "Destroying Window." << std::endl;
    }

    void FillMapWithZeros();
    void PrintMap();
    char ReturnAt(int x, int y)
    {
        return Window[x][y];
    }
    void setInfo(char info, int Xlocation, int Ylocation)
    {
        Window[Xlocation][Ylocation] = info;
    }


private:
    vector< vector<int> > Window;
    vector<int> subVector;
    //char Window[20][20];

};

MainWindow::MainWindow()
{
    FillMapWithZeros();
    Window[0][0]='8';
    Window[24][19]='8';
    Window[0][19]='8';
    Window[24][0]='8';

    for(int i=0; i<18; i++)
    {
        Window[0][i+1]='=';
        Window[24][i+1]='=';
    }
    for(int i=0; i<23; i++)
    {
        Window[i+1][0]='H';
        Window[i+1][19]='H';

    }

}

void MainWindow::ShowWindow()
{
    //cout << "Showing Window." << endl;
    PrintMap();
}

void MainWindow::HideWindow()
{
    cout << string(100,'\n');
    cout << "Hiding window." << endl;
}

void MainWindow::FillMapWithZeros()
{
    for(int i=0; i<20; i++)
    {
        subVector.push_back(' ');
    }
    for(int i=0; i<25; i++)
    {
        Window.push_back(subVector);
    }
}

void MainWindow::PrintMap()
{
    for(int i=0; i<Window.size(); i++)
    {
        for(int j=0; j<subVector.size(); j++)
        {
            addch(Window[i][j]);
            //addch(' ');
        }
        addstr("\n");
    }
}


class BigBlockHole
{
public:
    BigBlockHole(int Y, int X, MainWindow& GameMap);
    int ReturnY()
    {
        return TopY;
    }
    int ReturnX()
    {
        return LeftX;
    }
private:
    int TopY;
    int LeftX;
};

BigBlockHole::BigBlockHole(int Y, int X, MainWindow& GameMap)
{
    TopY=Y;
    LeftX=X;
    GameMap.setInfo('*',TopY,LeftX);
    GameMap.setInfo('*',TopY,LeftX+1);
    GameMap.setInfo('*',TopY+1,LeftX);
    GameMap.setInfo('*',TopY+1,LeftX+1);
}

class BigBlock
{
public:
    BigBlock(int LeftX, int TopY, MainWindow& GameMap);
    void MoveDown(MainWindow& GameMap);
    void MoveUp(MainWindow& GameMap);
    void MoveLeft(MainWindow& GameMap);
    void MoveRight(MainWindow& GameMap);
    int ReturnY()
    {
        return TopY;
    }
    int ReturnX()
    {
        return LeftX;
    }
private:
    int TopY;
    int BotY=TopY+1;
    int LeftX;
    int RightX=LeftX+1;
};

BigBlock::BigBlock(int Y, int X, MainWindow& GameMap)
{
    TopY=Y;
    LeftX=X;
    GameMap.setInfo('#',TopY,LeftX);
    GameMap.setInfo('#',TopY,LeftX+1);
    GameMap.setInfo('#',TopY+1,LeftX);
    GameMap.setInfo('#',TopY+1,LeftX+1);
}

void BigBlock::MoveDown(MainWindow& GameMap)
{
    int BlockPrevPos=TopY;
    TopY++;
    GameMap.setInfo('#', TopY+1, LeftX);
    GameMap.setInfo('#',TopY+1,LeftX+1);

    GameMap.setInfo(' ',BlockPrevPos,LeftX);
    GameMap.setInfo(' ',BlockPrevPos,LeftX+1);

}

void BigBlock::MoveUp(MainWindow& GameMap)
{
    int BlockPrevPos=TopY;
    TopY--;
    GameMap.setInfo('#', TopY, LeftX);
    GameMap.setInfo('#',TopY,LeftX+1);

    GameMap.setInfo(' ',BlockPrevPos+1,LeftX);
    GameMap.setInfo(' ',BlockPrevPos+1,LeftX+1);

}

void BigBlock::MoveLeft(MainWindow& GameMap)
{
    int BlockPrevPos=LeftX;
    LeftX--;
    GameMap.setInfo('#', TopY, LeftX);
    GameMap.setInfo('#',TopY+1,LeftX);

    GameMap.setInfo(' ',TopY,BlockPrevPos+1);
    GameMap.setInfo(' ',TopY+1,BlockPrevPos+1);
}

void BigBlock::MoveRight(MainWindow& GameMap)
{
    int BlockPrevPos=LeftX;
    LeftX++;
    GameMap.setInfo('#' | COLOR_PAIR(4), TopY, LeftX+1);
    GameMap.setInfo('#',TopY+1,LeftX+1);

    GameMap.setInfo(' ',TopY,BlockPrevPos);
    GameMap.setInfo(' ',TopY+1,BlockPrevPos);
}
class Cross
{
public:
    Cross(MainWindow& GameMap);
};

Cross::Cross(MainWindow& GameMap)
{
    for(int i=4; i<20; i++)
    {
        GameMap.setInfo('H',i,9);
    }
    for(int i=10; i<19; i++)
    {
        GameMap.setInfo('=',15,i);
    }
    for(int i=13; i<19; i++)
    {
        GameMap.setInfo('=',6,i);
    }
    //GameMap.setInfo('R',23,18);
    GameMap.setInfo('H',23,9);
    GameMap.setInfo('H',22,9);

}

class BlockHole
{
public:
    BlockHole(int XPos, int YPos, MainWindow& GameMap);
    int ReturnX()
    {
        return BlockHoleXPos;
    }
    int ReturnY()
    {
        return BlockHoleYPos;
    }
    void ChangeBlockHoleSymbol(char NewSymbol)
    {
        BlockHoleSymbol=NewSymbol;
    }
private:
    char BlockHoleSymbol='@';
    int BlockHoleXPos;
    int BlockHoleYPos;
};

BlockHole::BlockHole(int XPos, int YPos, MainWindow& GameMap)
{
    BlockHoleXPos=XPos;
    BlockHoleYPos=YPos;
    GameMap.setInfo(BlockHoleSymbol, BlockHoleXPos, BlockHoleYPos);
}
class Block
{
public:
    Block();
    Block(int XPos, int YPos, MainWindow& GameMap);
    void BlockMoveDown(MainWindow& GameMap);
    void BlockMoveLeft(MainWindow& GameMap);
    void BlockMoveUp(MainWindow& GameMap);
    void BlockMoveRight(MainWindow& GameMap);
    int ReturnX()
    {
        return BlockXPos;
    }
    int ReturnY()
    {
        return BlockYPos;
    }
    void SetXPos(int NewPos)
    {
        BlockYPos==NewPos;
    }

private:
    char BlockSymbol='#';
    int BlockXPos;
    int BlockYPos;
};


Block::Block(int XPos, int YPos, MainWindow& GameMap)
{
    BlockYPos=YPos;
    BlockXPos=XPos;
    GameMap.setInfo(BlockSymbol, XPos, YPos);
}

void Block::BlockMoveDown(MainWindow& GameMap)
{
    int BlockPrevPos=BlockYPos;
    BlockYPos++;
    GameMap.setInfo(BlockSymbol, BlockYPos, BlockXPos);
    GameMap.setInfo(' ',BlockPrevPos,BlockXPos);
}

void Block::BlockMoveUp(MainWindow& GameMap)
{
    int BlockPrevPos=BlockYPos;
    BlockYPos--;
    GameMap.setInfo(BlockSymbol, BlockYPos, BlockXPos);
    GameMap.setInfo(' ',BlockPrevPos,BlockXPos);
}

void Block::BlockMoveLeft(MainWindow& GameMap)
{
    int BlockPrevPos=BlockXPos;
    BlockXPos--;
    GameMap.setInfo(BlockSymbol, BlockYPos, BlockXPos);
    GameMap.setInfo(' ',BlockYPos,BlockPrevPos);
}

void Block::BlockMoveRight(MainWindow& GameMap)
{
    int BlockPrevPos=BlockXPos;
    BlockXPos++;
    GameMap.setInfo(BlockSymbol, BlockYPos, BlockXPos);
    GameMap.setInfo(' ',BlockYPos,BlockPrevPos);
}

bool IsBigBlockOnBigHole(BigBlock TheBlock, BigBlockHole TheHole);
void Restart(int X, int Y, MainWindow& GameMap);

int main()
{
    init_pair(4,COLOR_GREEN,COLOR_GREEN);
    GameLoop(1);
    return 0;
}





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
        int CountToWin=0;
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
            x=x;int Counter=0;
        int BiggerCounter=1;

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


