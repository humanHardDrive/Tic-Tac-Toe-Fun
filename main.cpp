#include <iostream> 
#include <cstdlib> 
#include "ai.h" 
 
using namespace std; 
 
//- no winners 
//O O wins 
//X X wins 
char gameOver(char grid[][3]) 
{ 
    //Check columns 
    for(int x = 0; x < 3; x++) 
    { 
        char testChar = grid[x][0]; 
        bool win = true; 
 
        if(testChar == ' ') 
        { 
            continue; 
        } 
 
        for(int y = 1; y < 3; y++) 
        { 
            if(grid[x][y] != testChar) 
            { 
                win = false; 
                break; 
            } 
        } 
 
        if(win) 
        { 
            return testChar; 
        } 
    } 
 
    //Check rows 
    for(int y = 0; y < 3; y++) 
    { 
        char testChar = grid[0][y]; 
        bool win = true; 
 
        if(testChar == ' ') 
        { 
            continue; 
        } 
 
        for(int x = 1; x < 3; x++) 
        { 
            if(grid[x][y] != testChar) 
            { 
                win = false; 
                break; 
            } 
        } 
 
        if(win) 
        { 
            return testChar; 
        } 
    } 
 
    //Check diagonals 
    char testChar = grid[0][0]; 
    bool win = true; 
    if(testChar != ' ') 
    { 
        for(int x = 1; x < 3; x++) 
        { 
            if(grid[x][x] != testChar) 
            { 
                win = false; 
                break; 
            } 
        } 
        if(win) 
        { 
            return testChar; 
        } 
    } 
 
    testChar = grid[0][2]; 
    if(testChar != ' ') 
    { 
        win = true; 
        for(int x = 1; x < 3; x++) 
        { 
            if(grid[x][x - 2] != testChar) 
            { 
                win = false; 
                break; 
            } 
        } 
        if(win) 
        { 
            return testChar; 
        } 
    } 
 
    return '-'; 
} 
 
bool isValidMove(char grid[][3], int x, int y) 
{ 
    return (grid[x][y] == ' '); 
} 
 
bool stillValidMoves(char grid[][3]) 
{ 
    for(int x = 0; x < 3; x++) 
    { 
        for(int y = 0; y < 3; y++) 
        { 
            if(grid[x][y] == ' ') 
            { 
                return true; 
            } 
        } 
    } 
 
    return false; 
} 
 
void printGrid(char grid[][3]) 
{ 
    cout<<(grid[0][2]==' ' ? '7' :grid[0][2])<<'|'<<(grid[1][2]==' ' ? '8' :grid[1][2])<<'|'<<(grid[2][2]==' ' ? '9' :grid[2][2])<<'\n'; 
    cout<<"-----\n"; 
    cout<<(grid[0][1]==' ' ? '4' :grid[0][1])<<'|'<<(grid[1][1]==' ' ? '5' :grid[1][1])<<'|'<<(grid[2][1]==' ' ? '6' :grid[2][1])<<'\n'; 
    cout<<"-----\n"; 
    cout<<(grid[0][0]==' ' ? '1' :grid[0][0])<<'|'<<(grid[1][0]==' ' ? '2' :grid[1][0])<<'|'<<(grid[2][0]==' ' ? '3' :grid[2][0])<<'\n'; 
} 
 
int main(int argc, char** argv) 
{ 
    cout<<'\n'; 
    char grid[3][3]; 
 
    for(int x = 0; x < 3; x++) 
    { 
        for(int y = 0; y < 3; y++) 
        { 
            grid[x][y] = ' '; 
        } 
    } 
 
    tictacAI comp1('X','O'); 
    tictacAI comp2('O','X'); 
 
    bool playerXHuman = false; 
    bool playerOHuman = true; 
 
    if(argc < 2) 
    { 
        std::cout<<"NOT ENOUGH ARGUMENTS\n"; 
        return 0; 
    } 
     
    int numPlayers = atoi(argv[1]); 
     
    switch(numPlayers) 
    { 
        case 2: 
        playerXHuman = true; 
        playerOHuman = true; 
        break; 
         
        case 1: 
        if(argc >= 3) 
        { 
            char playerMarker = (char)argv[2][0]; 
             
            if(playerMarker == 'X' || playerMarker == 'x') 
            { 
                playerXHuman = true; 
                playerOHuman = false; 
            }else if(playerMarker == 'O' || playerMarker == 'o') 
            { 
                playerOHuman = true; 
                playerXHuman = false; 
            } 
        } 
        else 
        {
            std::cout<<"NOT ENOUGH ARGUMENTS\n"; 
            return 0; 
        } 
        break; 
    } 
 
    while(true) 
    { 
        int xCoord = 0; 
        int xXCoord = 0; 
        int yXCoord = 0; 
 
        int oCoord = 0; 
        int xOCoord = 0; 
        int yOCoord = 0; 
         
        comp1.calcWinGrid(grid); 
        comp1.calcBlockGrid(grid);         
         
        printGrid(grid); 
        if(playerXHuman) 
        { 
            cout<<"PLACE X: "; 
            cin>>xCoord; 
        } 
        else 
        { 
            xCoord = comp1.nextMove(grid); 
        } 
 
        xXCoord = (xCoord - 1)%3; 
        yXCoord = (xCoord - 1)/3; 
 
        while(!isValidMove(grid, xXCoord, yXCoord)) 
        { 
            cout<<"SPACE TAKEN. PLACE X: "; 
            cin>>xCoord; 
 
            xXCoord = (xCoord - 1)%3; 
            yXCoord = (xCoord - 1)/3; 
        } 
 
        grid[xXCoord][yXCoord] = 'X'; 
        cout<<'\n'; 
 
        if(gameOver(grid) != '-') 
        { 
            break; 
        } 
 
        if(!stillValidMoves(grid)) 
        { 
            break; 
        } 
 
        printGrid(grid); 
 
        comp2.calcWinGrid(grid); 
        comp2.calcBlockGrid(grid); 
 
        if(playerOHuman) 
        { 
            cout<<"PLACE O: "; 
            cin>>oCoord; 
        } 
        else 
        { 
            oCoord = comp2.nextMove(grid); 
        } 
 
        xOCoord = (oCoord - 1)%3; 
        yOCoord = (oCoord - 1)/3; 
 
        while(!isValidMove(grid, xOCoord, yOCoord)) 
        { 
            cout<<"SPACE TAKEN. PLACE O: "; 
            cin>>oCoord; 
 
            xOCoord = (oCoord - 1)%3; 
            yOCoord = (oCoord - 1)/3; 
        } 
 
        grid[xOCoord][yOCoord] = 'O'; 
        cout<<'\n'; 
 
        if(gameOver(grid) != '-') 
        { 
            break; 
        } 
    } 
 
    char winner = gameOver(grid); 
    printGrid(grid); 
     
    if(winner != '-') 
    { 
        cout<<'\n'; 
        cout<<"PLAYER "<<winner<<" WINS!\n"; 
    } 
    else 
    { 
        cout<<'\n'; 
        cout<<"ALL SPACES TAKEN. NO WINNERS.\n"; 
    } 
 
    return 0; 
}