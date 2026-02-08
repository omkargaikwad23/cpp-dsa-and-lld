/*
================================================================================
            GRID PATHS WITH COINS (Google Interview)
================================================================================

PROBLEM (Part 1):
Calculate distinct paths from bottom-left to bottom-right corner.
Allowed moves: up-right, down-right, direct-right

PROBLEM (Part 2 - Follow-up):
Grid contains coins (0 or 1 at each cell).
Find the total number of paths where you collect ALL coins.

================================================================================
                         EXAMPLES
================================================================================

Part 1: n=4 rows, m=5 columns
From (3,0) to (3,4)
Multiple paths possible using the three moves.

Part 2: grid = [[0,1,0,0,1],
                [1,0,1,0,0],
                [0,0,1,1,0],
                [1,0,0,0,1]]
Count paths that visit ALL cells with 1.

================================================================================
                         APPROACH
================================================================================

PART 1:
- dp[i][j] = number of ways to reach cell (i, j) from bottom-left
- Transition: dp[i][j] = dp[i][j-1] + dp[i-1][j-1] + dp[i+1][j-1]
- Process column by column (left to right)

PART 2:
- Need to track which coins have been collected
- 3D DP: dp[i][j][coins_collected]
- If totalCoins small, use bitmask for coins

TIME:  Part 1: O(n × m)
       Part 2: O(n × m × 2^coins) or O(n × m × totalCoins)
SPACE: Part 1: O(n) with space optimization
       Part 2: O(n × m × coins)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// PART 1: Count distinct paths
// ═══════════════════════════════════════════════════════════════════════════

int countPaths(int n, int m) {
    // dp[i] = ways to reach row i in current column
    vector<int> dp(n, 0);
    dp[n - 1] = 1;  // Start at bottom-left (row n-1, col 0)
    
    for (int j = 1; j < m; j++) {
        vector<int> newDp(n, 0);
        
        for (int i = 0; i < n; i++) {
            // From left (same row)
            newDp[i] += dp[i];
            
            // From up-left (row i-1 in previous column)
            if (i > 0) newDp[i] += dp[i - 1];
            
            // From down-left (row i+1 in previous column)
            if (i + 1 < n) newDp[i] += dp[i + 1];
        }
        
        dp = newDp;
    }
    
    return dp[n - 1];  // End at bottom-right
}

// ═══════════════════════════════════════════════════════════════════════════
// PART 2: Count paths collecting ALL coins
// ═══════════════════════════════════════════════════════════════════════════

int countPathsWithAllCoins(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    
    // Count total coins
    int totalCoins = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            totalCoins += grid[i][j];
        }
    }
    
    // dp[i][j][c] = ways to reach (i,j) with exactly c coins collected
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(totalCoins + 1, 0)));
    
    // Start at bottom-left
    int startCoins = grid[n - 1][0];
    dp[n - 1][0][startCoins] = 1;
    
    // Process column by column
    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            int coinHere = grid[i][j];
            
            // Iterate all possible coin counts collected BEFORE reaching this cell
            // Upper bound: can't have collected more than (total - coins_here) before
            for (int c = 0; c <= totalCoins - coinHere; c++) {
                int newC = c + coinHere;  // Coins after picking up coin at current cell
                
                // From left (same row, previous column)
                dp[i][j][newC] += dp[i][j - 1][c];
                
                // From up-left (row above, previous column)
                if (i > 0) {
                    dp[i][j][newC] += dp[i - 1][j - 1][c];
                }
                
                // From down-left (row below, previous column)
                if (i + 1 < n) {
                    dp[i][j][newC] += dp[i + 1][j - 1][c];
                }
            }
        }
    }
    
    // Answer: paths reaching bottom-right with ALL coins
    return dp[n - 1][m - 1][totalCoins];
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Part 1 tests
    cout << "=== PART 1: Count Paths ===\n";
    cout << "Grid 4x5: " << countPaths(4, 5) << " paths\n";
    cout << "Grid 1x1: " << countPaths(1, 1) << " paths\n";
    cout << "Grid 2x3: " << countPaths(2, 3) << " paths\n\n";
    
    // Part 2 test
    cout << "=== PART 2: Paths Collecting All Coins ===\n";
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {1, 0, 0, 0, 1}
    };
    
    cout << "Grid:\n";
    for (auto& row : grid) {
        for (int x : row) cout << x << " ";
        cout << "\n";
    }
    
    cout << "\nPaths collecting all coins: " << countPathsWithAllCoins(grid) << "\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

PART 1:
- Time: O(n × m) - process each cell once
- Space: O(n) with column optimization

PART 2:
- Time: O(n × m × totalCoins)
- Space: O(n × m × totalCoins)
- If coins sparse, can optimize with bitmask DP

VARIATIONS:
1. What if we need to find the path itself? → Track parent pointers
2. What if coins have different values? → Track sum instead of count
3. What if there are obstacles? → Skip blocked cells in transitions

================================================================================
*/

