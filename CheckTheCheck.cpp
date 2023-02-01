#include <stdio.h>
#include <iostream>

using namespace std;


bool isEmpty(char chess_board[][15]){

    for(int i = 2; i < 10; i++)
        for(int j = 2; j < 10; j++)
            if( chess_board[i][j] != '.')
                return false;
    return true;
}


bool is_white_check(char chess_board[][15],int x,int y){
    int i,j;
    int x_cross_moves[4] = {-1, -1, 1, 1};
    int y_cross_moves[4] = {-1, 1, -1, 1};
    int x_straight_moves[4] = {-1, 1, 0, 0};
    int y_straight_moves[4] = {0, 0, -1, 1};

    for(int k = 0; k < 4; k++){
        i = x;
        j = y;
        while (i >= 2 && i < 10 && j >= 2 && j < 10) {
            i += x_cross_moves[k]; 
            j += y_cross_moves[k];
            if (chess_board[i][j]!='.'){ 
                if (i == x-1 && (j == y+1 || j == y-1) && chess_board[i][j]=='p') 
                    return true;
                else if (chess_board[i][j] == 'q' || chess_board [i][j] == 'b') 
                    return true; 
                else
                    break;
            }
        }
    }

    for(int k = 0; k < 4; k++){
        i = x;
        j = y;
        while (i >= 2 && i < 10 && j >= 2 && j < 10) {
            i += x_straight_moves[k]; 
            j += y_straight_moves[k];
            if (chess_board[i][j] != '.') {
                if (chess_board[i][j] == 'q' || chess_board[i][j] == 'r') 
                    return true;
                else
                    break;
            }
        }
    }

    if (chess_board[x-2][y-1]=='n' || chess_board[x-2][y+1]=='n' || chess_board[x-1][y-2]=='n' || chess_board[x-1][y+2]=='n' || chess_board[x+1][y-2]=='n' || chess_board[x+1][y+2]=='n' || chess_board[x+2][y-1]=='n' || chess_board[x+2][y+1]=='n')
       return true;
    else 
        return false;
}

bool is_black_check(char chess_board[][15],int x,int y){
    int i,j;
    int x_cross_moves[4] = {-1, -1, 1, 1};
    int y_cross_moves[4] = {-1, 1, -1, 1};
    int x_straight_moves[4] = {-1, 1, 0, 0};
    int y_straight_moves[4] = {0, 0, -1, 1};

    for(int k = 0; k<4; k++){
        i = x;
        j = y;
        while (i >= 2 && i < 10 && j >= 2 && j < 10) {
            i += x_cross_moves[k]; 
            j += y_cross_moves[k];
            if (chess_board[i][j] != '.') {
                if (i == x+1 && (j == y+1 || j == y-1) && chess_board[i][j] == 'P') 
                    return true;
                else if (chess_board[i][j] == 'Q' || chess_board [i][j] == 'B') 
                    return true;
                else 
                    break;
            }
        }
    }

    for(int k = 0; k<4; k++){
        i = x;
        j = y;
        while (i >= 2 && i < 10 && j >= 2 && j < 10) {
            i += x_straight_moves[k]; 
            j += y_straight_moves[k];
            if (chess_board[i][j] != '.') {
                if (chess_board[i][j] == 'Q' || chess_board[i][j] == 'R') 
                    return true;
                else 
                    break;
            }
        }
    }
    
    if (chess_board[x-2][y-1]=='N' || chess_board[x-2][y+1]=='N' || chess_board[x-1][y-2]=='N' || chess_board[x-1][y+2]=='N' || chess_board[x+1][y-2]=='N' || chess_board[x+1][y+2]=='N' || chess_board[x+2][y-1]=='N' || chess_board[x+2][y+1]=='N')
       return true;
    else 
        return false;
}


int main()
{
    int i,j;
    char chess_board[15][15];
    int inp, game_number = 0;

    int whiteKing_x = 0, whiteKing_y = 0, blackKing_x = 0, blackKing_y = 0;
    bool black_check = false, white_check = false;
      
    
    for (inp = 2;inp < 11; inp++)                  
        fgets(chess_board[inp] + 2, 15, stdin);
    
    if(isEmpty(chess_board))
        return 0;
    

    while (true)
    {
        white_check = false;
        black_check = false;
        
        game_number++;

        whiteKing_x = 0;
        blackKing_x = 0;

        for (i = 2; i < 10; i++)                     
            for (j = 2; j < 10; j++) {
                if (chess_board[i][j] == 'K') {
                    whiteKing_x = i; 
                    whiteKing_y = j;
                }
                else if (chess_board[i][j] == 'k') {
                    blackKing_x = i; 
                    blackKing_y = j;
                }
               
                if (whiteKing_x && blackKing_x) 
                    break;
            }
            
        if(is_white_check(chess_board, whiteKing_x, whiteKing_y))
            cout << "Game #" << game_number << ": white king is in check."<< endl;
        else if(is_black_check(chess_board, blackKing_x, blackKing_y))
            cout << "Game #" << game_number << ": black king is in check."<< endl;
        else
            cout << "Game #" << game_number << ": no king is in check."<< endl;
        
        for (inp = 2; inp < 11; inp++)                  
            fgets(chess_board[inp] + 2, 15, stdin);

        if(isEmpty(chess_board))
            break;

      }
}
