#include <iostream>
#include <string>
using namespace std;

int main(){


    int row, col, turn = 0, i, j;
    string currentMarker;
    
    string board[3][3] = {
        {"   ", "   ", "   "},
        {"   ", "   ", "   "},
        {"   ", "   ", "   "}
    };

    while(turn < 9){

        system("clear");

        cout << "\n\n============   TIC-TAC-TOE   ============" << endl;
        cout << "Instructions:" << endl;
        cout << "Decide who is X and who is O NOW !!" << endl;    
        cout << "Enter Row (1-3) and Col (1-3) to place your mark (X or O)." << "\n\n";

        if(turn % 2 == 0){
            currentMarker = "X";
        }else{
            currentMarker = "O";
        }

        for(i=0; i<3; i++){

            for(j=0; j<3; j++){
                
                cout << board[i][j];
                if(j<2){
                    cout << "|";
                }
            }
            cout << "\n";
            if(i<2){
                cout << "-----------\n";
            }
        }

        cout << "\n\nPLAYER-" << currentMarker << ", Enter Row and Column: ";
        cin >> row >> col;
        board[row-1][col-1] = " " + currentMarker + " ";
        turn++;


        for(i=0; i<3; i++){
            // For Row 
            if(board[i][0] != "   " && board[i][0] == board[i][1] && board[i][1] == board[i][2]){
                cout << "\n\n* * * * * * * * * * * * * *\n";
                cout << "* PLAYER-" << currentMarker << " is the WINNER! *\n";
                cout << "* * * * * * * * * * * * * *\n"; 
                return 0;
            }
            // For Column
            if(board[0][i] != "   " && board[0][i] == board[1][i] && board[1][i] == board[2][i]){
                cout << "\n\n* * * * * * * * * * * * * *\n";
                cout << "* PLAYER-" << currentMarker << " is the WINNER! *\n";
                cout << "* * * * * * * * * * * * * *\n";
                return 0;
            }
        }
            // For Diagonal
        if(board[0][0] != "   " && board[0][0] == board[1][1] && board[1][1] == board[2][2]){
            cout << "\n\n* * * * * * * * * * * * * *\n";
            cout << "* PLAYER-" << currentMarker << " is the WINNER! *\n";
            cout << "* * * * * * * * * * * * * *\n";       
            return 0;
        }
        if(board[0][2] != "   " && board[0][2] == board[1][1] && board[1][1] == board[2][0]){
            cout << "\n\n* * * * * * * * * * * * * *\n";
            cout << "* PLAYER-" << currentMarker << " is the WINNER! *\n";
            cout << "* * * * * * * * * * * * * *\n";         
            return 0;
        }

        if (turn == 9) {
            cout << "It's a DRAW!\n";
        }
    }
}


//    |   |   
// -----------
//    |   |   
// -----------
//    |   |  


//  [0 0] [0 1] [0 2]
//
//  [1 0] [1 1] [1 2]
//
//  [2 0] [2 1] [2 2]
