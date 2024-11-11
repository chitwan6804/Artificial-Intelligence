#include <iostream>
#include <vector>

using namespace std;

vector<int> board(10, 2); // Initialize board with 2 (empty spaces)
int magic_square[10] = {0, 8, 3, 4, 1, 5, 9, 6, 7, 2};
int turn = 1;
int userSymbol;
int aiSymbol;

int Make2()
{
    if (board[5] == 2)
        return 5;
    if (board[2] == 2)
        return 2;
    if (board[4] == 2)
        return 4;
    if (board[6] == 2)
        return 6;
    if (board[8] == 2)
        return 8;
    return 0;
}

void Go(int n)
{
    board[n] = (turn % 2 != 0) ? userSymbol : aiSymbol;
    turn++;
}

int PossWin(int p)
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == p)
        {
            for (int j = i + 1; j <= 9; j++)
            {
                if (board[j] == p)
                {
                    int third_pos = 15 - (magic_square[i] + magic_square[j]);
                    for (int k = 1; k <= 9; k++)
                    {
                        if (magic_square[k] == third_pos && board[k] == 2)
                        {
                            return k;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

void print_board()
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == 2)
            cout << "- ";
        else if (board[i] == 3)
            cout << "X ";
        else if(board[i]==5)
            cout << "O ";

        if (i % 3 == 0)
            cout << endl;
    }
}

bool check_winner(int p)
{
    vector<vector<int>> winningCombos = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9}, {1, 5, 9}, {3, 5, 7}};

    for (const auto &combo : winningCombos)
    {
        if (board[combo[0]] == p && board[combo[1]] == p && board[combo[2]] == p)
        {
            return true;
        }
    }

    return false;
}

bool is_board_full()
{
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == 2)
            return false;
    }
    return true;
}

vector<int> Generate( vector<int> board){
    vector<int> generate;
    for (int i=1;i<=9;i++){
        if(board[i]==2){
            generate.push_back(i);
        }
    }
    return generate;
}

int rating(vector<int> board, int p){
    int rate=0;
    int user = p;
    int opponent;
    if(p==3){
        opponent=5;
    }
    else{
        opponent=3;
    }
    
    if(check_winner(user)){
        rate+=1000;
    }
    else if(check_winner(opponent)){
        rate-=1000;
    }

    if(PossWin(user)!=0){
        rate+=500;
    }
    else if(PossWin(opponent)!=0){
        rate-=500;
    }

    if(board[5]==user){
        rate+=10;
    }
    else if(board[5]==opponent){
        rate-=10;
    }

    if(board[1]==user || board[3] ==user || board[7]==user || board[9]==user){
        rate+=5;
    }
    else if(board[1] == opponent || board[3] == opponent || board[7] == opponent || board[9] == opponent){
        rate-=5;
    }

    if(board[2]==user || board[4] ==user || board[6]==user || board[8]==user){
        rate+=3;
    }
    else if(board[2] == opponent || board[4] == opponent || board[6] == opponent || board[8] == opponent){
        rate-=3;
    }

    return rate;
}

bool deep_enough(int curDepth,int Given_depth){
    if(curDepth==Given_depth){
        return true;
    }
    return false;
}

int minmax(vector<int> board,int depth,int p){
    
}

void AIMove(){
    int bestMove;
    bestMove=minmax(board,0,aiSymbol);
    Go(bestMove);
}


void PlayGame()
{
    char choice;
    do
    {
        cout << "Do you want to be X or O? Enter X or O: ";
        cin >> choice;
    } while (choice != 'X' && choice != 'x' && choice != 'O' && choice != 'o');

    userSymbol = (choice == 'O' || choice == 'o') ? 5 : 3;
    aiSymbol = (userSymbol == 3) ? 5 : 3;

    while (true)
    {
        print_board();

        if (turn % 2 != 0)
        {
            int move;
            cout << "Your turn (enter a number 1-9): ";
            cin >> move;
            if (move < 1 || move > 9 || board[move] != 2)
            {
                cout << "Invalid move, please try again." << endl;
                continue;
            }
            Go(move);
        }
        else
        {
            cout << "AI's turn..." << endl;
            AIMove();
        }

        if (check_winner(userSymbol))
        {
            print_board();
            cout << "Congratulations! You won!" << endl;
            break;
        }
        else if (check_winner(aiSymbol))
        {
            print_board();
            cout << "AI won! Better luck next time!" << endl;
            break;
        }

        if (is_board_full())
        {
            print_board();
            cout << "It's a draw!" << endl;
            break;
        }
    }
}

int main()
{
    int board_matrix[10]={0,5,2,5,2,3,2,3,2,3};
    for(int i=0;i<10;i++){
        board[i]=board_matrix[i];
    }
    int rank=rating(board,5);
    print_board();
    cout<<"rank for 5 is: "<<rank;
    rank=rating(board,3);
    cout<<"rank for 3 is: "<<rank;
    PlayGame();
    return 0;
}