#include <iostream>
#include <conio.h>   // Windows alternative for instant keypresses
#include <cstdlib>   // Needed for system("cls")
using namespace std;

// ANSI COLOR CODE DEFINITIONS
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define CREAM       "\033[38;5;230m" 
#define AMBER       "\033[38;5;215m" 
#define TEAL        "\033[48;5;30m"  
#define CORAL       "\033[1;38;5;203m" 
#define SAGE        "\033[1;38;5;150m" 
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

// Windows version of the character reader
char getRawChar(){
    return _getch(); // Instantly reads a key without waiting for 'Enter'
}

void printMenu() {
    cout << "\033[2J\033[H\033[?25l"; 
    cout << AMBER << "=========================================\n";
    cout << BOLD << CREAM << "            TIC TAC TOE v1.0          \n";
    cout << AMBER << "=========================================\n\n";
    
    cout << CREAM << "  How to Play:\n";
    cout << "  - Use " << AMBER << "ARROW KEYS" << CREAM << " to move your cursor.\n";
    cout << "  - Press " << AMBER << "SPACE" << CREAM << " or " << AMBER << "ENTER" << CREAM << " to lock in your position.\n";
    cout << "  - Alternates between " << CORAL << "X" << CREAM << " and " << SAGE << "O" << CREAM << " automatically.\n";
    cout << "  - Press 'q' at any time to exit the system window.\n\n";
    
    cout << BOLD << SAGE << "  >>> Press ANY KEY to start... <<<\n" << RESET;
    getRawChar(); 
}

void printBoard(int cursor, char board[9], char current_turn) {
    cout << "\033[2J\033[H\033[?25l";
    cout << CREAM << "Current Turn: ";
    if (current_turn == 'X') {
        cout << CORAL << "X\n\n" << RESET;
    } else {
        cout << SAGE << "O\n\n" << RESET;
    }

    for (int i = 0; i < 9; ++i) {
        if (i == cursor) cout << TEAL << "[ ";
        else cout << AMBER << "[ ";

        if (board[i] == 'X') cout << CORAL << "X";
        else if (board[i] == 'O') cout << SAGE << "O";
        else cout << " ";

        if (i == cursor) cout << TEAL << " ]" << RESET;
        else cout << AMBER << " ]" << RESET;

        if ((i + 1) % 3 == 0) cout << "\n\n";
    }
    cout << CREAM << "Press 'q' to quit.\n" << RESET;
}

void cursorMovement(char input, int& cursor) {
    // Windows arrow keys send a special code starting with 0 or -32
    if (input == 0 || input == -32) {
        char directionByte = getRawChar(); // Grab the second byte
        
        if (directionByte == 'H') { // UP Arrow
            if (cursor < 3) cursor += 6;
            else cursor -= 3;
        }
        else if (directionByte == 'P') { // DOWN Arrow
            if (cursor > 5) cursor -= 6;
            else cursor += 3;
        }
        else if (directionByte == 'M') { // RIGHT Arrow
            if (cursor % 3 == 2) cursor -= 2;
            else cursor += 1;
        }
        else if (directionByte == 'K') { // LEFT Arrow
            if (cursor % 3 == 0) cursor += 2;
            else cursor -= 1;
        }
    }
}

void placeMark(int cursor, char board[9], char& turn) {
    if (board[cursor] == ' ') {
        board[cursor] = turn;
        turn = (turn == 'X') ? 'O' : 'X';
    }
}

char checkWin(char board[9]) {
    for (int i = 0; i < 9; i += 3) {
        if (board[i] != ' ' && board[i] == board[i + 1] && board[i + 1] == board[i + 2]) return board[i];
    }
    for (int i = 0; i < 3; ++i) {
        if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) return board[i];
    }
    if (board[0] != ' ' && board[0] == board[4] && board[4] == board[8]) return board[0];
    if (board[2] != ' ' && board[2] == board[4] && board[4] == board[6]) return board[2];
    return ' ';
}

int main(){
    int cursor = 0;
    char input = ' ';
    char turn = 'X';
    char winner = ' ';
    int moveCount = 0;
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

    printMenu();
    printBoard(cursor, board, turn);

    while (input != 'q' && winner == ' ' && moveCount < 9) {
        input = getRawChar();
        cursorMovement(input, cursor);
        if (input == ' ' || input == 10 || input == 13) {
            if (board[cursor] == ' ') { 
                placeMark(cursor, board, turn);
                moveCount++;
                winner = checkWin(board);
            }
        }

    system("cls"); // Windows clear screen command

    if (winner == 'X') {
        cout << CORAL << BOLD << "\n  >>> CONGRATULATIONS! Player X Wins! <<<  \n\n" << RESET;
    } 
    else if (winner == 'O') {
        cout << SAGE << BOLD << "\n  >>> CONGRATULATIONS! Player O Wins! <<<  \n\n" << RESET;
    } 
    else {
        cout << CREAM << "\n -- Game Over. Thanks for playing! -- \n\n" << RESET;
    }

    cout << SHOW_CURSOR; 
}
