#include <iostream>
#include <vector>
#include <limits>

using namespace std;

vector<int> board(9, 2); // Initialize board with 2 (empty spaces)
int turn = 1;
int userSymbol;
int aiSymbol;
int total=0;

void display() {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) cout << endl;
        cout << (board[i] == 3 ? "X " : (board[i] == 5 ? "O " : "- "));
    }
    cout << endl;
}

int checkWin(const vector<int>& board) {
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (board[i * 3] == board[i * 3 + 1] && board[i * 3 + 1] == board[i * 3 + 2] && board[i * 3] != 2) {
            return board[i * 3];
        }
        // Check columns
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6] && board[i] != 2) {
            return board[i];
        }
    }
    // Check diagonals
    if (board[0] == board[4] && board[4] == board[8] && board[0] != 2) {
        return board[0];
    }
    if (board[2] == board[4] && board[4] == board[6] && board[2] != 2) {
        return board[2];
    }
    return 0; // No winner yet
}

bool isDraw() {
    for (int spot : board) {
        if (spot == 2) return false; 
    }
    return true;
}

int rate(const vector<int>& b) {
    int score = 0;

    if (checkWin(b) == aiSymbol) {         // Check complete Win.
        return 1000;
    } else if (checkWin(b) == userSymbol) {
        return -1000;
    }

    // PossWin feature: check for potential wins in rows, columns, and diagonals
    for (int i = 0; i < 3; i++) {
        if ((b[i * 3] == b[i * 3 + 1] && b[i * 3] != 2 && b[i * 3 + 2] == 2) ||
            (b[i * 3] == b[i * 3 + 2] && b[i * 3] != 2 && b[i * 3 + 1] == 2) ||
            (b[i * 3 + 1] == b[i * 3 + 2] && b[i * 3 + 1] != 2 && b[i * 3] == 2)) {
            if (b[i * 3] == aiSymbol || b[i * 3 + 1] == aiSymbol || b[i * 3 + 2] == aiSymbol) score += 500;
            if (b[i * 3] == userSymbol || b[i * 3 + 1] == userSymbol || b[i * 3 + 2] == userSymbol) score -= 500;
        }
        // Check columns for potential win
        if ((b[i] == b[i + 3] && b[i] != 2 && b[i + 6] == 2) ||
            (b[i] == b[i + 6] && b[i] != 2 && b[i + 3] == 2) ||
            (b[i + 3] == b[i + 6] && b[i + 3] != 2 && b[i] == 2)) {
            if (b[i] == aiSymbol || b[i + 3] == aiSymbol || b[i + 6] == aiSymbol) score += 500;
            if (b[i] == userSymbol || b[i + 3] == userSymbol || b[i + 6] == userSymbol) score -= 500;
        }
    }

        // Check diagonals for potential win
        if ((b[0] == b[4] && b[0] != 2 && b[8] == 2) ||
            (b[0] == b[8] && b[0] != 2 && b[4] == 2) ||
            (b[4] == b[8] && b[4] != 2 && b[0] == 2)) {
            if (b[0] == aiSymbol || b[4] == aiSymbol || b[8] == aiSymbol) score += 500;
            if (b[0] == userSymbol || b[4] == userSymbol || b[8] == userSymbol) score -= 500;
        }
        if ((b[2] == b[4] && b[2] != 2 && b[6] == 2) ||
            (b[2] == b[6] && b[2] != 2 && b[4] == 2) ||
            (b[4] == b[6] && b[4] != 2 && b[2] == 2)) {
            if (b[2] == aiSymbol || b[4] == aiSymbol || b[6] == aiSymbol) score += 500;
            if (b[2] == userSymbol || b[4] == userSymbol || b[6] == userSymbol) score -= 500;
        }

    // Strategic positions

    //Center Control.
    if (b[4] == aiSymbol) score += 4; 
    if (b[4] == userSymbol) score -= 4; 

    // Corner control
    int corners[] = {b[0], b[2], b[6], b[8]};
    for (int corner : corners) {
        if (corner == aiSymbol) score += 3; // AI in corner
        if (corner == userSymbol) score -= 3; // User in corner
    }

    // Edge control
    int edges[] = {b[1], b[3], b[5], b[7]};
    for (int edge : edges) {
        if (edge == aiSymbol) score += 1; // AI in edge
        if (edge == userSymbol) score -= 1; // User in edge
    }

    return score;
}

vector<int> move_gen(const vector<int>& board) {
    vector<int> moves;
    for (int i = 0; i < 9; i++) {
        if (board[i] == 2) { // If the spot is empty
            moves.push_back(i);
        }
    }
    return moves;
}

int minimax(vector<int>& board, int depth, bool isMaximizing, int maxDepth) {
    total++;
    int score = rate(board);
    if (score == 1000 || score == -1000) return score; // Return score if terminal state (win)
    if (isDraw()) return 0; // Draw
    if (depth >= maxDepth) return rate(board); // Return rating if max depth reached

    if (isMaximizing) {
        int bestScore = -1000;
        for (int move : move_gen(board)) {
            board[move] = aiSymbol; // AI's move
            bestScore = max(bestScore, minimax(board, depth + 1, false, maxDepth));
            board[move] = 2; // Undo the move
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int move : move_gen(board)) {
            board[move] = userSymbol; // User's move
            bestScore = min(bestScore, minimax(board, depth + 1, true, maxDepth));
            board[move] = 2; // Undo the move
        }
        return bestScore;
    }
}

void computermove(int maxDepth) {
    cout << "AI's turn..." << endl;
    int bestScore = -1000;
    int bestMove = -1;
    for (int move : move_gen(board)) {
        board[move] = aiSymbol; // AI's move
        int score = minimax(board, 0, false, maxDepth);
        board[move] = 2; // Undo the move
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }
    if (bestMove != -1) {
        board[bestMove] = aiSymbol;
    }
    cout<<bestScore<<endl;
    cout<<bestMove<<endl;
    display();
    if (checkWin(board) == aiSymbol) {
        cout << "Computer wins!" << endl;
        exit(0);
    }
}

void usermove() {
    int n;
    while (true) {
        cout << "Enter the block number for your move (1-9): ";
        cin >> n;
        n--;
        if (n >= 0 && n < 9 && board[n] == 2) {
            board[n] = userSymbol;
            display();
            if (checkWin(board) == userSymbol) {
                cout << "You win!" << endl;
                exit(0);
            }
            break;
        } else {
            cout << "Invalid move! Please try again." << endl;
        }
    }
}

void playGame() {
    char choice;
    cout << "Do you want to be X or O? Enter X or O: ";
    cin >> choice;
    userSymbol = (choice == 'X' || choice == 'x') ? 3 : 5;
    aiSymbol = (userSymbol == 3) ? 5 : 3;

    display();
    while (true) {
        usermove();
        computermove(4);
    }
}

int main() {
    playGame();
    cout<<"Total "<<total<<" times minimax was called.";
    return 0;
}
