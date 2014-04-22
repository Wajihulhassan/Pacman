#ifndef SOKOBANHEADER_H
#define SOKOBANHEADER_H
#include <iostream>
#include <curses.h>
#include <vector>
#include <ctime>


using namespace std;

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
    int BotY;
    int LeftX;
    int RightX;
};

BigBlock::BigBlock(int Y, int X, MainWindow& GameMap)
{
    TopY=Y;
    LeftX=X;
    BotY=TopY+1;
    RightX=LeftX+1;
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
    char BlockHoleSymbol;
    int BlockHoleXPos;
    int BlockHoleYPos;
};

BlockHole::BlockHole(int XPos, int YPos, MainWindow& GameMap)
{
    BlockHoleSymbol='@';
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
    char BlockSymbol;
    int BlockXPos;
    int BlockYPos;
};


Block::Block(int XPos, int YPos, MainWindow& GameMap)
{

    BlockSymbol='#';
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

#endif // SOKOBANHEADER_H
