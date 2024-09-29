#include <iostream>
using namespace std;

char board[3][3] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

void print_board() {
    cout << "  0 1 2\n";
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) // check rows
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) // check columns
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) // check first diagonal
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) // check second diagonal
        return true;
    return false;
}

bool checkTie() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true; 
}

bool Move(int row, int col, char player) {
    if (board[row][col] == ' ') { 
        board[row][col] = player;
        return true;
    }
    return false;
}

int main() {
    char player = 'X';
    int row, col;

    while (true) {
        print_board();

        cout << "Player " << player << ":\nEnter row (0, 1, 2): ";
        cin >> row;
        cout << "Enter column (0, 1, 2): ";
        cin >> col;

        if (Move(row, col, player)) {
            if (checkWin(player)) {
                print_board();
                cout << "Player " << player << " won!\n";
                break;
            }

            if (checkTie()) {
                print_board();
                cout << "It's a tie!\n";
                break;
            }

            player = (player == 'X') ? 'O' : 'X';
        } else {
            cout << "Invalid move, try again.\n";
        }
    }

    return 0;
}
