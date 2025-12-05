/*
================================================================================
                        N-QUEENS PROBLEM (LeetCode 51)
================================================================================

Problem: Place N queens on an N×N chessboard such that no two queens attack 
         each other. Queens attack on same row, column, or diagonal.

Example (N=4):
  . Q . .      . . Q .
  . . . Q      Q . . .
  Q . . .      . . . Q
  . . Q .      . Q . .

Key Insight:
  - Place one queen per row (row constraint automatically satisfied)
  - Check column and diagonal conflicts

Attack Check:
  - Same column: col[i] == col[j]
  - Same diagonal: |row_i - row_j| == |col_i - col_j|

Time: O(N!)  |  Space: O(N²) for solutions

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 1: Basic Backtracking                                              │
│ Time: O(N!)  |  Space: O(N) for recursion + O(N²) for solutions             │
└─────────────────────────────────────────────────────────────────────────────┘
*/

bool isValid(vector<int>& queens, int row, int col) {
    for (int i = 0; i < row; i++) {
        // Same column OR same diagonal
        if (queens[i] == col || abs(row - i) == abs(queens[i] - col)) {
            return false;
        }
    }
    return true;
}

void backtrack(int n, int row, vector<int>& queens, vector<vector<string>>& result) {
    if (row == n) {
        // Build board from queens positions
        vector<string> board(n, string(n, '.'));
        for (int i = 0; i < n; i++) {
            board[i][queens[i]] = 'Q';
        }
        result.push_back(board);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isValid(queens, row, col)) {
            queens[row] = col;
            backtrack(n, row + 1, queens, result);
            // No explicit undo needed - queens[row] will be overwritten
        }
    }
}

vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<int> queens(n, -1);  // queens[i] = column of queen in row i
    backtrack(n, 0, queens, result);
    return result;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 2: Optimized with Hash Sets - O(1) conflict check                  │
│ Time: O(N!)  |  Space: O(N)                                                 │
│                                                                             │
│ Track occupied columns and diagonals with sets:                             │
│ - cols: occupied columns                                                    │
│ - diag1: row - col (identifies one diagonal direction)                      │
│ - diag2: row + col (identifies other diagonal direction)                    │
└─────────────────────────────────────────────────────────────────────────────┘
*/

void backtrackOptimized(int n, int row, vector<int>& queens,
                        unordered_set<int>& cols,
                        unordered_set<int>& diag1,  // row - col
                        unordered_set<int>& diag2,  // row + col
                        vector<vector<string>>& result) {
    if (row == n) {
        vector<string> board(n, string(n, '.'));
        for (int i = 0; i < n; i++) {
            board[i][queens[i]] = 'Q';
        }
        result.push_back(board);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        // O(1) conflict check using sets
        if (cols.count(col) || diag1.count(row - col) || diag2.count(row + col)) {
            continue;
        }
        
        // Place queen in the current row and column
        queens[row] = col;
        cols.insert(col);
        diag1.insert(row - col);
        diag2.insert(row + col);
        
        backtrackOptimized(n, row + 1, queens, cols, diag1, diag2, result);
        
        // Remove queen (backtrack)
        cols.erase(col);
        diag1.erase(row - col);
        diag2.erase(row + col);
    }
}

vector<vector<string>> solveNQueensOptimized(int n) {
    vector<vector<string>> result;
    vector<int> queens(n, -1);
    unordered_set<int> cols, diag1, diag2;
    backtrackOptimized(n, 0, queens, cols, diag1, diag2, result);
    return result;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ MAIN                                                                        │
└─────────────────────────────────────────────────────────────────────────────┘
*/

void printSolutions(vector<vector<string>>& solutions) {
    cout << "Found " << solutions.size() << " solutions:\n\n";
    int count = 1;
    for (auto& board : solutions) {
        cout << "Solution " << count++ << ":\n";
        for (auto& row : board) {
            cout << "  " << row << "\n";
        }
        cout << "\n";
    }
}

int main() {
    cout << "=== N-Queens Problem ===\n\n";
    
    // Test N = 4
    cout << "N = 4:\n";
    auto solutions4 = solveNQueens(4);
    printSolutions(solutions4);
    
    // Test N = 8 (count only)
    auto solutions8 = solveNQueensOptimized(8);
    cout << "N = 8: " << solutions8.size() << " solutions\n";
    
    // Expected counts
    cout << "\nExpected solution counts:\n";
    cout << "  N=1: 1,  N=2: 0,  N=3: 0,  N=4: 2\n";
    cout << "  N=5: 10, N=6: 4,  N=7: 40, N=8: 92\n";
    
    return 0;
}

/*
================================================================================
                            KEY INSIGHTS
================================================================================

1. DIAGONAL TRICK:
   - All cells on same "/" diagonal have same (row + col)
   - All cells on same "\" diagonal have same (row - col)
   
   Example for N=4:
   
   row-col (\ diag):     row+col (/ diag):
   0  -1  -2  -3         0   1   2   3
   1   0  -1  -2         1   2   3   4
   2   1   0  -1         2   3   4   5
   3   2   1   0         3   4   5   6

2. WHY O(N!) TIME?
   - Row 0: N choices
   - Row 1: at most N-1 choices (one column blocked)
   - Row 2: at most N-2 choices
   - Total: N × (N-1) × (N-2) × ... = N!

3. OPTIMIZATION IMPACT:
   - Basic: O(N) per conflict check × N! placements
   - Optimized: O(1) per conflict check × N! placements

================================================================================
*/
