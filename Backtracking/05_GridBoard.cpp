/*
================================================================================
                    BACKTRACKING - GRID & BOARD PROBLEMS
================================================================================

Explore paths or place elements on 2D grids/boards.

Key Techniques:
- Mark cells as visited during exploration
- Unmark cells when backtracking
- Try all 4 (or 8) directions

Time: Varies | Space: O(m*n) or O(path_length)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: N-Queens (LeetCode 51)
─────────────────────────────────
Place n queens on n×n board so no two attack each other.

Input: n = 4
Output: [[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]

Time: O(n!) | Space: O(n)
*/
class NQueens {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<string> board(n, string(n, '.'));
        vector<bool> cols(n, false);
        vector<bool> diag1(2 * n - 1, false);  // row - col + n - 1
        vector<bool> diag2(2 * n - 1, false);  // row + col
        
        backtrack(board, 0, cols, diag1, diag2, result);
        return result;
    }
    
private:
    void backtrack(vector<string>& board, int row,
                   vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2,
                   vector<vector<string>>& result) {
        int n = board.size();
        
        if (row == n) {
            result.push_back(board);
            return;
        }
        
        for (int col = 0; col < n; col++) {
            int d1 = row - col + n - 1;
            int d2 = row + col;
            
            if (cols[col] || diag1[d1] || diag2[d2]) continue;
            
            // Place queen
            board[row][col] = 'Q';
            cols[col] = diag1[d1] = diag2[d2] = true;
            
            backtrack(board, row + 1, cols, diag1, diag2, result);
            
            // Remove queen
            board[row][col] = '.';
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }
};

// Count solutions only
int totalNQueens(int n) {
    vector<bool> cols(n, false);
    vector<bool> diag1(2 * n - 1, false);
    vector<bool> diag2(2 * n - 1, false);
    
    function<int(int)> backtrack = [&](int row) -> int {
        if (row == n) return 1;
        
        int count = 0;
        for (int col = 0; col < n; col++) {
            int d1 = row - col + n - 1, d2 = row + col;
            if (cols[col] || diag1[d1] || diag2[d2]) continue;
            
            cols[col] = diag1[d1] = diag2[d2] = true;
            count += backtrack(row + 1);
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
        return count;
    };
    
    return backtrack(0);
}


/*
PROBLEM 2: Sudoku Solver (LeetCode 37)
──────────────────────────────────────
Fill 9×9 grid so each row, column, and 3×3 box contains 1-9.

Time: O(9^(empty_cells)) | Space: O(81)
*/
class SudokuSolver {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }
    
private:
    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] != '.') continue;
                
                for (char c = '1'; c <= '9'; c++) {
                    if (isValid(board, i, j, c)) {
                        board[i][j] = c;
                        
                        if (solve(board)) return true;
                        
                        board[i][j] = '.';  // Backtrack
                    }
                }
                
                return false;  // No valid digit found
            }
        }
        return true;  // All cells filled
    }
    
    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            // Check row
            if (board[row][i] == c) return false;
            // Check column
            if (board[i][col] == c) return false;
            // Check 3x3 box
            int boxRow = 3 * (row / 3) + i / 3;
            int boxCol = 3 * (col / 3) + i % 3;
            if (board[boxRow][boxCol] == c) return false;
        }
        return true;
    }
};


/*
PROBLEM 3: Word Search (LeetCode 79)
────────────────────────────────────
Check if word exists in grid by adjacent cells.

Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true

Time: O(m * n * 4^L) | Space: O(L) where L = word length
*/
class WordSearch {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(), n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    
private:
    int dirs[5] = {0, 1, 0, -1, 0};
    
    bool backtrack(vector<vector<char>>& board, const string& word,
                   int row, int col, int index) {
        if (index == word.size()) return true;
        
        if (row < 0 || row >= board.size() || 
            col < 0 || col >= board[0].size() ||
            board[row][col] != word[index]) {
            return false;
        }
        
        char temp = board[row][col];
        board[row][col] = '#';  // Mark visited
        
        for (int d = 0; d < 4; d++) {
            if (backtrack(board, word, row + dirs[d], col + dirs[d + 1], index + 1)) {
                return true;
            }
        }
        
        board[row][col] = temp;  // Unmark
        return false;
    }
};


/*
PROBLEM 4: Word Search II (LeetCode 212)
────────────────────────────────────────
Find all words from dictionary that exist in grid.

Approach: Build Trie + DFS from each cell

Time: O(m * n * 4^L * W) | Space: O(total_chars_in_words)
*/
class WordSearchII {
    struct TrieNode {
        TrieNode* children[26] = {};
        string word = "";
    };
    
    int dirs[5] = {0, 1, 0, -1, 0};
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Build Trie
        TrieNode* root = new TrieNode();
        for (const string& word : words) {
            TrieNode* node = root;
            for (char c : word) {
                if (!node->children[c - 'a']) {
                    node->children[c - 'a'] = new TrieNode();
                }
                node = node->children[c - 'a'];
            }
            node->word = word;
        }
        
        vector<string> result;
        int m = board.size(), n = board[0].size();
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                backtrack(board, i, j, root, result);
            }
        }
        
        return result;
    }
    
private:
    void backtrack(vector<vector<char>>& board, int row, int col,
                   TrieNode* node, vector<string>& result) {
        if (row < 0 || row >= board.size() || 
            col < 0 || col >= board[0].size() ||
            board[row][col] == '#') {
            return;
        }
        
        char c = board[row][col];
        TrieNode* next = node->children[c - 'a'];
        if (!next) return;
        
        if (!next->word.empty()) {
            result.push_back(next->word);
            next->word = "";  // Avoid duplicates
        }
        
        board[row][col] = '#';
        
        for (int d = 0; d < 4; d++) {
            backtrack(board, row + dirs[d], col + dirs[d + 1], next, result);
        }
        
        board[row][col] = c;
    }
};


/*
PROBLEM 5: Rat in a Maze
────────────────────────
Find all paths from (0,0) to (n-1,n-1) in a maze.

Input: maze = [[1,0,0,0],[1,1,0,1],[0,1,0,0],[1,1,1,1]]
Output: ["DDRDRR", "DRDDRR"] (D=Down, R=Right, U=Up, L=Left)

Time: O(4^(n²)) | Space: O(n²)
*/
class RatInMaze {
public:
    vector<string> findPath(vector<vector<int>>& maze) {
        int n = maze.size();
        vector<string> result;
        
        if (maze[0][0] == 0 || maze[n-1][n-1] == 0) return result;
        
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        backtrack(maze, 0, 0, "", visited, result);
        return result;
    }
    
private:
    // Order: D, L, R, U (lexicographical)
    int dr[4] = {1, 0, 0, -1};
    int dc[4] = {0, -1, 1, 0};
    char dir[4] = {'D', 'L', 'R', 'U'};
    
    void backtrack(vector<vector<int>>& maze, int row, int col,
                   string path, vector<vector<bool>>& visited,
                   vector<string>& result) {
        int n = maze.size();
        
        if (row == n - 1 && col == n - 1) {
            result.push_back(path);
            return;
        }
        
        visited[row][col] = true;
        
        for (int d = 0; d < 4; d++) {
            int nr = row + dr[d], nc = col + dc[d];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < n &&
                maze[nr][nc] == 1 && !visited[nr][nc]) {
                backtrack(maze, nr, nc, path + dir[d], visited, result);
            }
        }
        
        visited[row][col] = false;
    }
};


/*
PROBLEM 6: Unique Paths III (LeetCode 980)
──────────────────────────────────────────
Walk over every non-obstacle cell exactly once, from start to end.

1 = start, 2 = end, 0 = empty, -1 = obstacle

Time: O(4^(m*n)) | Space: O(m*n)
*/
class UniquePaths3 {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int startR, startC, emptyCells = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    startR = i; startC = j;
                } else if (grid[i][j] == 0) {
                    emptyCells++;
                }
            }
        }
        
        return backtrack(grid, startR, startC, emptyCells);
    }
    
private:
    int dirs[5] = {0, 1, 0, -1, 0};
    
    int backtrack(vector<vector<int>>& grid, int row, int col, int remaining) {
        if (row < 0 || row >= grid.size() || 
            col < 0 || col >= grid[0].size() ||
            grid[row][col] == -1) {
            return 0;
        }
        
        if (grid[row][col] == 2) {
            return remaining == 0 ? 1 : 0;  // Must have visited all empty cells
        }
        
        int count = 0;
        int original = grid[row][col];
        grid[row][col] = -1;  // Mark visited
        
        int newRemaining = (original == 0) ? remaining - 1 : remaining;
        
        for (int d = 0; d < 4; d++) {
            count += backtrack(grid, row + dirs[d], col + dirs[d + 1], newRemaining);
        }
        
        grid[row][col] = original;  // Unmark
        return count;
    }
};


/*
PROBLEM 7: Android Unlock Patterns (LeetCode 351)
─────────────────────────────────────────────────
Count valid Android unlock patterns using m to n keys.

Keys: 1-9 in 3x3 grid. Can't skip a key on the same line unless visited.

Time: O(n!) | Space: O(9)
*/
class AndroidUnlock {
public:
    int numberOfPatterns(int m, int n) {
        // skip[i][j] = key between i and j (if any)
        vector<vector<int>> skip(10, vector<int>(10, 0));
        skip[1][3] = skip[3][1] = 2;
        skip[1][7] = skip[7][1] = 4;
        skip[3][9] = skip[9][3] = 6;
        skip[7][9] = skip[9][7] = 8;
        skip[1][9] = skip[9][1] = skip[3][7] = skip[7][3] = 5;
        skip[2][8] = skip[8][2] = skip[4][6] = skip[6][4] = 5;
        
        vector<bool> visited(10, false);
        int count = 0;
        
        for (int len = m; len <= n; len++) {
            // By symmetry: 1,3,7,9 are equivalent; 2,4,6,8 are equivalent
            count += backtrack(skip, visited, 1, len - 1) * 4;
            count += backtrack(skip, visited, 2, len - 1) * 4;
            count += backtrack(skip, visited, 5, len - 1);
        }
        
        return count;
    }
    
private:
    int backtrack(vector<vector<int>>& skip, vector<bool>& visited,
                  int curr, int remaining) {
        if (remaining == 0) return 1;
        
        visited[curr] = true;
        int count = 0;
        
        for (int next = 1; next <= 9; next++) {
            if (!visited[next]) {
                // Can move if no skip required OR skip key already visited
                if (skip[curr][next] == 0 || visited[skip[curr][next]]) {
                    count += backtrack(skip, visited, next, remaining - 1);
                }
            }
        }
        
        visited[curr] = false;
        return count;
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Grid & Board Problems ===\n\n";
    
    // 1. N-Queens
    NQueens sol1;
    auto res1 = sol1.solveNQueens(4);
    cout << "1. N-Queens (n=4): " << res1.size() << " solutions\n";
    
    // 3. Word Search
    WordSearch sol3;
    vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
    cout << "3. Word 'ABCCED' exists: " << (sol3.exist(board, "ABCCED") ? "true" : "false") << "\n";
    
    // 6. Unique Paths III
    UniquePaths3 sol6;
    vector<vector<int>> grid = {{1,0,0,0},{0,0,0,0},{0,0,2,-1}};
    cout << "6. Unique paths covering all cells: " << sol6.uniquePathsIII(grid) << "\n";
    
    // 7. Android Unlock
    AndroidUnlock sol7;
    cout << "7. Android patterns (m=1, n=2): " << sol7.numberOfPatterns(1, 2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| N-Queens                      | Row-by-row, track cols & diagonals             |
| Sudoku                        | Cell-by-cell, validate row/col/box             |
| Word Search                   | DFS from each cell, mark/unmark visited        |
| Word Search II                | Trie + DFS for multiple words                  |
| Rat in Maze                   | DFS with 4 directions, track path string       |
| Unique Paths III              | Count empty cells, validate at end             |
| Android Unlock                | Track skip rules, use symmetry                 |
+───────────────────────────────+────────────────────────────────────────────────+

KEY INSIGHT: Grid backtracking = Mark visited → Explore → Unmark visited

================================================================================
*/

