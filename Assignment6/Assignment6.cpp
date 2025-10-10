#include <iostream>
#include <vector>
using namespace std;

// Function to check if a queen can be safely placed
bool isSafe(const vector<vector<char>>& board, int row, int col) {
    int n = board.size();

    // Check vertically upward
    for (int i = row - 1; i >= 0; i--) {
        if (board[i][col] == 'Q')
            return false;
    }

    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 'Q')
            return false;
    }

    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 'Q')
            return false;
    }

    return true;
}

// Recursive function to solve N-Queens
bool nQueens(vector<vector<char>>& board, int row) {
    int n = board.size();

    if (row == n) {
        // Print the final board configuration
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return true; // Stop after the first solution
    }

    for (int i = 0; i < n; i++) {
        if (isSafe(board, row, i)) {
            board[row][i] = 'Q';          // Place the queen
            if (nQueens(board, row + 1))  // Recurse for the next row
                return true;              // Stop after finding one solution
            board[row][i] = '.';          // Backtrack
        }
    }

    return false; // No valid position found in this configuration
}

int main() {
    int n = 8;
    vector<vector<char>> board(n, vector<char>(n, '.'));

    if (!nQueens(board, 0)) {
        cout << "No solution found." << endl;
    }

    return 0;
}