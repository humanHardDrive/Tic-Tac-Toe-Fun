ai.h
#include<iostream> 
#include<cstdlib> 
#include<ctime> 
#include<vector> 
 
class tictacAI 
{ 
    public: 
    tictacAI(char marker, char opMarker) 
    { 
        this->marker = marker; 
        this->opMarker = opMarker; 
 
        moveToWinFlag = false; 
        moveToBlockFlag = false; 
 
        for(int x = 0; x < 3; x++) 
        { 
            for(int y = 0; y < 3; y++) 
            { 
                winGrid[x][y] = 0; 
                blockGrid[x][y] = 0; 
            } 
        } 
    } 
 
    void calcWinGrid(char grid[][3]) 
    { 
        for(int x = 0; x < 3; x++) 
        { 
            for(int y = 0; y < 3; y++) 
            { 
                winGrid[x][y] = horizontalCount(grid,x,y, marker, opMarker, true) + verticalCount(grid,x,y, marker, opMarker, true) + diagonalCount(grid,x,y, marker, opMarker, false, true) + diagonalCount(grid,x,y, marker, opMarker, true, true); 
            } 
        } 
    } 
 
    void calcBlockGrid(char grid[][3]) 
    { 
        for(int x = 0; x < 3; x++) 
        { 
            for(int y = 0; y < 3; y++) 
            { 
                blockGrid[x][y] = horizontalCount(grid,x,y, opMarker, marker, false) + verticalCount(grid,x,y, opMarker, marker, false) + diagonalCount(grid,x,y, opMarker, marker, false, false) + diagonalCount(grid,x,y, opMarker, marker, true, false); 
            } 
        } 
    } 
 
    int nextMove(char grid[][3]) 
    { 
        std::vector<int> moves; 
        std::srand(std::time(0)); 
         
        if(moveToWinFlag) 
        { 
            moveToWinFlag = false; 
            return moveToWin; 
        } 
 
        if(moveToBlockFlag) 
        { 
            moveToBlockFlag = false; 
            return moveToBlock; 
        } 
 
        int square = 0; 
        int potential = 0; 
 
        for(int x = 0; x < 3; x++) 
        { 
            for(int y = 0; y < 3; y++) 
            { 
                if(winGrid[x][y] > potential) 
                { 
                    potential = winGrid[x][y]; 
                    moves.clear(); 
                    square = xyToSquare(x,y); 
                    moves.push_back(xyToSquare(x,y)); 
                } 
                else if(winGrid[x][y] == potential) 
                { 
                    moves.push_back(xyToSquare(x,y)); 
                } 
            } 
        } 
 
        if(square == 0) 
        { 
            for(int x = 0; x < 3; x++) 
            { 
                for(int y = 0; y < 3; y++) 
                { 
                    if(grid[x][y] == ' ') 
                    { 
                        return xyToSquare(x,y); 
                    } 
                } 
            }         
        } 
 
        //add some randomnessness 
        if(moves.size() == 1) 
        { 
            return square; 
        } 
        else 
        { 
            int index = (std::rand()/(float)RAND_MAX)*moves.size(); 
            return moves.at(index); 
        } 
    } 
 
    void printWinGrid() 
    { 
        for(int y = 2; y >= 0; y--) 
        { 
            for(int x = 0; x < 3; x++) 
            { 
                std::cout<<winGrid[x][y]<<'\t'; 
            } 
            std::cout<<'\n'; 
        } 
 
        std::cout<<'\n'; 
    } 
 
    void printBlockGrid() 
    { 
        for(int y = 2; y >= 0; y--) 
        { 
            for(int x = 0; x < 3; x++) 
            { 
                std::cout<<blockGrid[x][y]<<'\t'; 
            } 
            std::cout<<'\n'; 
        } 
 
        std::cout<<'\n'; 
    } 
 
    private: 
    bool isBlocked(char grid[][3], char axis, int x, int y, char marker, char otherMarker) 
    { 
        if(axis == 'x') 
        { 
            for(int tX = 0; tX < 3; tX++) 
            { 
                if(grid[tX][y] == otherMarker) 
                { 
                    return true; 
                } 
            } 
        } 
        else if(axis == 'y') 
        { 
            for(int tY = 0; tY < 3; tY++) 
            { 
                if(grid[x][tY] == otherMarker) 
                { 
                    return true; 
                } 
            } 
        } 
        else if(axis == 'p') 
        { 
            if(!isOnDiagonal(x,y,true)) 
            { 
                return true; 
            } 
 
            for(int tX = 0; tX < 3; tX++) 
            { 
                if(grid[tX][2 - tX] == otherMarker) 
                { 
                    return true; 
                } 
            } 
        } 
        else if(axis == 'n') 
        { 
            if(!isOnDiagonal(x,y,false)) 
            { 
                return true; 
            } 
 
            for(int tX = 0; tX < 3; tX++) 
            { 
                if(grid[tX][tX] == otherMarker) 
                { 
                    return true; 
                } 
            }        
        } 
 
        return false; 
    } 
 
    bool isOnDiagonal(int x, int y, bool up) 
    { 
        if(x == y && !up) 
        { 
            return true; 
        } 
        else if(y == 2 - x && up) 
        { 
            return true; 
        } 
 
        return false; 
    } 
 
    int horizontalCount(char grid[][3], int x, int y, char marker, char otherMarker, bool predict=false) 
    { 
        if(isBlocked(grid, 'x',x, y, marker, otherMarker)) 
        { 
            return 0; 
        } 
 
        if(grid[x][y] == marker) 
        { 
            return 0; 
        } 
 
        int ret = 0; 
 
        for(int tX = 0; tX < 3; tX++) 
        { 
            if(predict) 
            { 
                if(tX == x) 
                { 
                    ret++; 
                } 
            } 
 
            if(grid[tX][y] == marker) 
            { 
                ret++; 
            } 
        } 
 
        if(ret == 3) 
        { 
            if(predict) 
            { 
                moveToWinFlag = true; 
                moveToWin = xyToSquare(x, y); 
            } 
        } 
        else if(ret == 2) 
        { 
            if(!predict) 
            { 
                moveToBlockFlag = true; 
                moveToBlock = xyToSquare(x, y); 
            } 
        } 
 
        return ret; 
    } 
 
    int verticalCount(char grid[][3], int x, int y, char marker, char otherMarker, bool predict=false) 
    { 
        if(isBlocked(grid, 'y',x, y, marker, otherMarker)) 
        { 
            return 0; 
        } 
 
        if(grid[x][y] == marker) 
        { 
            return 0; 
        } 
 
        int ret = 0; 
 
        for(int tY = 0; tY < 3; tY++) 
        { 
            if(predict) 
            { 
                if(tY == y) 
                { 
                    ret++; 
                } 
            } 
 
            if(grid[x][tY] == marker) 
            { 
                ret++; 
            } 
        } 
 
        if(ret == 3) 
        { 
            if(predict) 
            { 
                moveToWinFlag = true; 
                moveToWin = xyToSquare(x, y); 
            } 
          } 
          else if(ret == 2) 
          { 
            if(!predict) 
            { 
                moveToBlockFlag = true; 
                moveToBlock = xyToSquare(x, y); 
            } 
        } 
 
        return ret; 
    } 
 
    int diagonalCount(char grid[][3], int x, int y, char marker, char otherMarker, bool up, bool predict=false) 
    { 
        char slope = ' '; 
         
        if(up) 
        { 
            slope = 'p'; 
        } 
        else 
        { 
            slope = 'n'; 
        } 
     
        if(isBlocked(grid, slope, x, y, marker, otherMarker)) 
        { 
            return 0; 
        } 
 
        if(grid[x][y] == marker) 
        { 
            return 0; 
        } 
 
        int ret = 0; 
         
        for(int tX = 0; tX < 3; tX++) 
        { 
            if(up) 
            { 
                if(predict) 
                { 
                    if(x == tX && y == 2 - tX) 
                    { 
                        ret++; 
                    } 
                } 
                 
                if(grid[tX][2 -tX] == marker) 
                { 
                    ret++; 
                } 
            } 
            else 
            { 
                if(predict) 
                { 
                    if(x == tX && y == tX) 
                    { 
                        ret++; 
                    } 
                } 
                 
                if(grid[tX][tX] == marker) 
                { 
                    ret++; 
                }             
            } 
        } 
 
        if(ret == 3) 
        { 
            if(predict) 
            { 
                moveToWinFlag = true; 
                moveToWin = xyToSquare(x, y); 
            } 
        } 
           else if(ret == 2) 
           { 
               if(!predict) 
               { 
                moveToBlockFlag = true; 
                moveToBlock = xyToSquare(x, y); 
            } 
        } 
 
        return ret; 
    } 
 
    int xyToSquare(int x, int y) 
    { 
        return (y*3) + x + 1; 
    } 
 
    int winGrid[3][3]; 
    int blockGrid[3][3]; 
 
    char marker; 
    char opMarker; 
 
    bool moveToWinFlag; 
    int moveToWin; 
 
    bool moveToBlockFlag; 
    int moveToBlock; 
};