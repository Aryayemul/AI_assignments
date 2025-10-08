#include <bits/stdc++.h>
using namespace std;

// Define grid size
#define ROW 9
#define COL 10

// Structure to hold cell details
struct Cell {
    int parent_i, parent_j;
    double f, g, h;
    Cell() {
        parent_i = -1;
        parent_j = -1;
        f = g = h = FLT_MAX;
    }
};

// Utility function to check if a cell is valid (within grid)
bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Utility function to check if a cell is unblocked (1 = path, 0 = blocked)
bool isUnBlocked(int grid[][COL], int row, int col) {
    return (grid[row][col] == 1);
}

// Utility function to check if the cell is the destination
bool isDestination(int row, int col, pair<int, int> dest) {
    return (row == dest.first && col == dest.second);
}

// Heuristic function — Euclidean distance
double calculateHValue(int row, int col, pair<int, int> dest) {
    return sqrt((row - dest.first) * (row - dest.first) +
                (col - dest.second) * (col - dest.second));
}

// Trace path from destination to source
void tracePath(Cell cellDetails[][COL], pair<int, int> dest) {
    cout << "\nThe Path is:\n";
    stack<pair<int, int>> Path;
    int row = dest.first;
    int col = dest.second;

    while (!(cellDetails[row][col].parent_i == row && 
             cellDetails[row][col].parent_j == col)) {
        Path.push({row, col});
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push({row, col});
    while (!Path.empty()) {
        pair<int, int> p = Path.top();
        Path.pop();
        cout << "-> (" << p.first << "," << p.second << ") ";
    }
    cout << endl;
}

// A* Search Algorithm
void aStarSearch(int grid[][COL], pair<int, int> src, pair<int, int> dest) {
    // If source or destination is invalid
    if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second)) {
        cout << "Source or destination is invalid\n";
        return;
    }

    // If source or destination is blocked
    if (!isUnBlocked(grid, src.first, src.second) ||
        !isUnBlocked(grid, dest.first, dest.second)) {
        cout << "Source or destination is blocked\n";
        return;
    }

    // If source and destination are the same
    if (isDestination(src.first, src.second, dest)) {
        cout << "We are already at the destination\n";
        return;
    }

    // Initialize closed list (visited cells)
    bool closedList[ROW][COL];
    memset(closedList, false, sizeof(closedList));

    // Cell details array
    Cell cellDetails[ROW][COL];

    int i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    // Open list: set of cells to be evaluated
    set<pair<double, pair<int, int>>> openList;
    openList.insert({0.0, {i, j}});

    bool foundDest = false;

    // Directions (8 neighbors)
    int dir[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1},
                     {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    while (!openList.empty()) {
        pair<double, pair<int, int>> p = *openList.begin();
        openList.erase(openList.begin());

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        // Explore neighbors
        for (int d = 0; d < 8; d++) {
            int new_i = i + dir[d][0];
            int new_j = j + dir[d][1];

            if (isValid(new_i, new_j)) {
                // If destination is found
                if (isDestination(new_i, new_j, dest)) {
                    cellDetails[new_i][new_j].parent_i = i;
                    cellDetails[new_i][new_j].parent_j = j;
                    cout << "The destination cell is found\n";
                    tracePath(cellDetails, dest);
                    foundDest = true;
                    return;
                }
                // If the successor is unblocked and not in closed list
                else if (!closedList[new_i][new_j] &&
                         isUnBlocked(grid, new_i, new_j)) {
                    double gNew = cellDetails[i][j].g + 1.0;
                    double hNew = calculateHValue(new_i, new_j, dest);
                    double fNew = gNew + hNew;

                    // If this path is better (smaller f)
                    if (cellDetails[new_i][new_j].f == FLT_MAX ||
                        cellDetails[new_i][new_j].f > fNew) {
                        openList.insert({fNew, {new_i, new_j}});
                        cellDetails[new_i][new_j].f = fNew;
                        cellDetails[new_i][new_j].g = gNew;
                        cellDetails[new_i][new_j].h = hNew;
                        cellDetails[new_i][new_j].parent_i = i;
                        cellDetails[new_i][new_j].parent_j = j;
                    }
                }
            }
        }
    }

    // If destination not found
    if (!foundDest)
        cout << "Failed to find the destination cell\n";
}

// ------------------ Driver Code ------------------
int main() {
    int grid[ROW][COL] = {
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}
    };

    pair<int, int> src = make_pair(8, 0);
    pair<int, int> dest = make_pair(0, 0);

    aStarSearch(grid, src, dest);

    return 0;
}
