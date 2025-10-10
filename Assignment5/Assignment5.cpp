#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char EMPTY = '.';

// Function to print the game board
void printBoard(const vector<vector<char>>& board) {
    for (const auto& row : board) {
        for (char cell : row)
            cout << cell << " ";
        cout << endl;
    }
    cout << endl;
}

// Function to evaluate the board and return a score
int evaluateBoard(const vector<vector<char>>& board) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY)
            return (board[i][0] == PLAYER_X) ? 10 : -10;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY)
            return (board[0][i] == PLAYER_X) ? 10 : -10;
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY)
        return (board[0][0] == PLAYER_X) ? 10 : -10;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY)
        return (board[0][2] == PLAYER_X) ? 10 : -10;

    return 0; // No winner yet
}

// Function to check if the game is over
bool isGameOver(const vector<vector<char>>& board) {
    if (evaluateBoard(board) != 0)
        return true;
    for (const auto& row : board)
        for (char cell : row)
            if (cell == EMPTY)
                return false;
    return true; // Draw
}

// Minimax algorithm
int minimax(vector<vector<char>>& board, int depth, bool isMaximizing) {
    int score = evaluateBoard(board);

    // Terminal states
    if (score == 10 || score == -10)
        return score;

    if (isGameOver(board))
        return 0; // Draw

    if (isMaximizing) {
        int bestScore = numeric_limits<int>::min();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_X;
                    bestScore = max(bestScore, minimax(board, depth + 1, false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = numeric_limits<int>::max();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER_O;
                    bestScore = min(bestScore, minimax(board, depth + 1, true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return bestScore;
    }
}

// Function to find the best move for the computer
pair<int, int> findBestMove(vector<vector<char>>& board) {
    int bestValue = numeric_limits<int>::min();
    pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = PLAYER_X;
                int moveValue = minimax(board, 0, false);
                board[i][j] = EMPTY;

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }
    return bestMove;
}

// Main game loop
void playGame() {
    vector<vector<char>> board(3, vector<char>(3, EMPTY));
    cout << "Tic-Tac-Toe: Player X (you) vs Player O (computer)\n";
    printBoard(board);

    while (true) {
        int row, col;
        cout << "Enter your move row (0, 1, or 2): ";
        cin >> row;
        cout << "Enter your move column (0, 1, or 2): ";
        cin >> col;

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            cout << "Invalid input! Please enter 0, 1, or 2 for both row and column.\n";
            continue;
        }

        if (board[row][col] != EMPTY) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = PLAYER_X;

        if (isGameOver(board)) {
            printBoard(board);
            if (evaluateBoard(board) == 10)
                cout << "You win!\n";
            else
                cout << "It's a draw!\n";
            break;
        }

        cout << "Computer's turn...\n";
        pair<int, int> bestMove = findBestMove(board);
        board[bestMove.first][bestMove.second] = PLAYER_O;

        printBoard(board);

        if (isGameOver(board)) {
            if (evaluateBoard(board) == -10)
                cout << "Computer wins!\n";
            else
                cout << "It's a draw!\n";
            break;
        }
    }
}

int main() {
    playGame();
    return 0;
}
