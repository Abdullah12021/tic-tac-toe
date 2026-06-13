#include <iostream>
#include <unistd.h>
#include <termios.h>
using namespace std;
// ANSI COLOR CODE DEFINITIONS
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define CREAM       "\033[38;5;230m" // Warm white/cream for text
#define AMBER       "\033[38;5;215m" // Cozy warm orange/amber for the board frame
#define TEAL        "\033[48;5;30m"  // Soft Teal background for the active cursor
#define CORAL       "\033[1;38;5;203m" // Vibrant Coral Red for X
#define SAGE        "\033[1;38;5;150m" // Soft Sage Green for O
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"


char getRawChar(){

    char buffer = 0;

    termios old = {0};
    tcgetattr(0, &old);
    termios current = old;

    current.c_lflag &= ~ICANON;
    current.c_lflag &= ~ECHO;

    current.c_cc[VMIN] = 1;
    current.c_cc[VTIME] = 0;

    tcsetattr(0, TCSANOW, &current);
    if (read(0, &buffer, 1) < 0) {
        perror("read()");
    }

    tcsetattr(0, TCSANOW, &old);
    return buffer;
}

void printMenu() {
    
    cout << "\033[2J\033[H\033[?25l"; // Clear screen, home cursor and hide the blinking cursor

    cout << AMBER << "=========================================\n";
    cout << BOLD << CREAM << "             TIC TAC TOE v1.0          \n";
    cout << AMBER << "=========================================\n\n";
    
    cout << CREAM << "  How to Play:\n";
    cout << "  - Use " << AMBER << "ARROW KEYS" << CREAM << " (or " << AMBER << "IJKL" << CREAM << ") to move your cursor.\n";
    cout << "  - Press " << AMBER << "SPACE" << CREAM << " or " << AMBER << "ENTER" << CREAM << " to lock in your position.\n";
    cout << "  - Alternates between " << CORAL << "X" << CREAM << " and " << SAGE << "O" << CREAM << " automatically.\n";
    cout << "  - Press 'q' at any time to exit the system window.\n\n";
    
    cout << BOLD << SAGE << "  >>> Press ANY KEY to start... <<<\n" << RESET;
    getRawChar(); // Pause until they press a key
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
        // opening bracket
        if (i == cursor) {
            cout << TEAL << "[ ";
        } else {
            cout << AMBER << "[ ";
        }

        // mark ('X', 'O', or blank space)
        if (board[i] == 'X') {
            cout << CORAL << "X";
        } else if (board[i] == 'O') {
            cout << SAGE << "O";
        } else {
            cout << " ";
        }

        // closing bracket
        if (i == cursor) {
            cout << TEAL << " ]" << RESET;
        } else {
            cout << AMBER << " ]" << RESET;
        }

        // row spacing
        if ((i + 1) % 3 == 0) {
            cout << "\n\n";
        }
    }
    cout << CREAM << "Press 'q' to quit.\n" << RESET;
}


void cursorMovement(char input, int& cursor) {
    // Check if an Arrow key sequence is starting
    if (input == 27) {
        char secondByte = getRawChar(); // Read and discard the '['
        char thirdByte = getRawChar();  // Grab the critical direction byte ('A', 'B', 'C', 'D')
        
        if (secondByte == '[') {
            // Move UP (Byte 3 is 'A')
            if (thirdByte == 'A') {
                if (cursor < 3) {
                    cursor += 6;
                } else {
                    cursor -= 3;
                }
            }
            // Move DOWN (Byte 3 is 'B')
            else if (thirdByte == 'B') {
                if (cursor > 5) {
                    cursor -= 6;
                } else {
                    cursor += 3;
                }
            }
            // Move RIGHT (Byte 3 is 'C')
            else if (thirdByte == 'C') {
                if (cursor % 3 == 2) {
                    cursor -= 2;
                } else {
                    cursor += 1;
                }
            }
            // Move LEFT (Byte 3 is 'D')
            else if (thirdByte == 'D') {
                if (cursor % 3 == 0) {
                    cursor += 2;
                } else {
                    cursor -= 1;
                }
            }
        }
    }
}

void placeMark(int cursor, char board[9], char& turn) {
    if (board[cursor] == ' ') {
        board[cursor] = turn;

        // Swap turn
        if (turn == 'X') {
            turn = 'O';
        } else {
            turn = 'X';
        }
    }
}

char checkWin(char board[9]) {
    // 1. Check Rows
    for (int i = 0; i < 9; i += 3) {
        if (board[i] != ' ' && board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
            return board[i]; // Returns 'X' or 'O' depending on who is in that row
        }
    }

    // 2. Check Columns
    for (int i = 0; i < 3; ++i) {
        if (board[i] != ' ' && board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            return board[i]; // Returns 'X' or 'O'
        }
    }

    // 3. Check Diagonals
    if (board[0] != ' ' && board[0] == board[4] && board[4] == board[8]) {
        return board[0];
    }
    if (board[2] != ' ' && board[2] == board[4] && board[4] == board[6]) {
        return board[2];
    }

    return ' '; // Returns a blank space if there is no winner yet
}



int main(){

    int cursor = 0;
    char input = ' ';
    char turn = 'X';
    char winner = ' ';
    int moveCount = 0;
    char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}; // Fresh empty board

    printMenu();
    printBoard(cursor, board, turn);

    while (input != 'q' && winner == ' ' && moveCount < 9) {
        input = getRawChar();
        cursorMovement(input, cursor);
        if (input == ' ' || input == 10 || input == 13) {
            // ONLY proceed if the board slot is actually empty
            if (board[cursor] == ' ') { 
                placeMark(cursor, board, turn);
                moveCount++;
                winner = checkWin(board);
            }
        }
        printBoard(cursor, board, turn);
        
    }

    system("clear");

    if (winner == 'X') {
        cout << CORAL << BOLD << "\n  >>> CONGRATULATIONS! Player X Wins! <<<  \n\n" << RESET;
    } 
    else if (winner == 'O') {
        cout << SAGE << BOLD << "\n  >>> CONGRATULATIONS! Player O Wins! <<<  \n\n" << RESET;
    } 
    else {
        cout << CREAM << "\n -- Game Over. Thanks for playing! -- \n\n" << RESET;
    }


    cout << SHOW_CURSOR; // Show the cursor again before exiting
}
