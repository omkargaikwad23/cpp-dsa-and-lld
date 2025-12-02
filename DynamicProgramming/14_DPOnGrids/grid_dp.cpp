/*
================================================================================
                    PATTERN 14: DP ON GRIDS
================================================================================

When to use:
- Navigate or optimize paths in 2D grid
- Count paths, min/max path cost
- Robot movement problems

LeetCode Problems:
- 62. Unique Paths
- 64. Minimum Path Sum
- 63. Unique Paths II
- 120. Triangle
- 931. Minimum Falling Path Sum

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Unique Paths (LeetCode 62) ⭐ CLASSIC
────────────────────────────────────────────────
Count paths from top-left to bottom-right.
Can only move right or down.

dp[i][j] = dp[i-1][j] + dp[i][j-1]

Time: O(m*n) | Space: O(n)
*/
int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);
    
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[j] += dp[j-1];
        }
    }
    
    return dp[n-1];
}


/*
PROBLEM 2: Unique Paths II (LeetCode 63)
────────────────────────────────────────
Same as above, but with obstacles.

Time: O(m*n) | Space: O(n)
*/
int uniquePathsWithObstacles(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    if (grid[0][0] == 1) return 0;
    
    vector<long long> dp(n, 0);
    dp[0] = 1;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                dp[j] = 0;
            } else if (j > 0) {
                dp[j] += dp[j-1];
            }
        }
    }
    
    return dp[n-1];
}


/*
PROBLEM 3: Minimum Path Sum (LeetCode 64) ⭐ CLASSIC
────────────────────────────────────────────────────
Find path with minimum sum from top-left to bottom-right.

dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])

Time: O(m*n) | Space: O(n)
*/
int minPathSum(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                dp[j] = grid[i][j];
            } else if (i == 0) {
                dp[j] = dp[j-1] + grid[i][j];
            } else if (j == 0) {
                dp[j] = dp[j] + grid[i][j];
            } else {
                dp[j] = min(dp[j], dp[j-1]) + grid[i][j];
            }
        }
    }
    
    return dp[n-1];
}


/*
PROBLEM 4: Triangle (LeetCode 120)
──────────────────────────────────
Min path sum from top to bottom in triangle.
Can move to adjacent in next row.

Time: O(n²) | Space: O(n)
*/
int minimumTotal(vector<vector<int>>& triangle) {
    int n = triangle.size();
    vector<int> dp = triangle[n-1];  // Start from bottom
    
    for (int i = n - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
        }
    }
    
    return dp[0];
}


/*
PROBLEM 5: Minimum Falling Path Sum (LeetCode 931)
──────────────────────────────────────────────────
Min path sum starting from any cell in first row.
Can move down, down-left, or down-right.

Time: O(m*n) | Space: O(n)
*/
int minFallingPathSum(vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<int> dp = matrix[0];
    
    for (int i = 1; i < n; i++) {
        vector<int> newDp(n);
        for (int j = 0; j < n; j++) {
            int minPrev = dp[j];
            if (j > 0) minPrev = min(minPrev, dp[j-1]);
            if (j < n-1) minPrev = min(minPrev, dp[j+1]);
            newDp[j] = matrix[i][j] + minPrev;
        }
        dp = newDp;
    }
    
    return *min_element(dp.begin(), dp.end());
}


/*
PROBLEM 6: Minimum Falling Path Sum II (LeetCode 1289)
──────────────────────────────────────────────────────
Can move to any column in next row EXCEPT same column.

Track min and second min for O(n²) instead of O(n³).

Time: O(n²) | Space: O(1)
*/
int minFallingPathSumII(vector<vector<int>>& grid) {
    int n = grid.size();
    int min1 = 0, min2 = 0, minIdx = -1;
    
    for (int i = 0; i < n; i++) {
        int newMin1 = INT_MAX, newMin2 = INT_MAX, newMinIdx = -1;
        
        for (int j = 0; j < n; j++) {
            int val = grid[i][j] + (j != minIdx ? min1 : min2);
            
            if (val < newMin1) {
                newMin2 = newMin1;
                newMin1 = val;
                newMinIdx = j;
            } else if (val < newMin2) {
                newMin2 = val;
            }
        }
        
        min1 = newMin1;
        min2 = newMin2;
        minIdx = newMinIdx;
    }
    
    return min1;
}


/*
PROBLEM 7: Dungeon Game (LeetCode 174)
──────────────────────────────────────
Find min initial HP to reach bottom-right with HP > 0.
Work backwards from destination.

Time: O(m*n) | Space: O(n)
*/
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = dungeon.size(), n = dungeon[0].size();
    vector<int> dp(n + 1, INT_MAX);
    dp[n-1] = 1;
    
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            int minNext = min(dp[j], dp[j+1]);
            dp[j] = max(1, minNext - dungeon[i][j]);
        }
        dp[n] = INT_MAX;  // Reset boundary
    }
    
    return dp[0];
}


/*
PROBLEM 8: Cherry Pickup (LeetCode 741)
───────────────────────────────────────
Two traversals: (0,0)→(n-1,n-1)→(0,0).
Equivalent to two people walking simultaneously.

dp[r1][c1][c2]: r2 = r1 + c1 - c2

Time: O(n³) | Space: O(n²)
*/
int cherryPickup(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, INT_MIN)));
    dp[0][0][0] = grid[0][0];
    
    for (int r1 = 0; r1 < n; r1++) {
        for (int c1 = 0; c1 < n; c1++) {
            for (int c2 = 0; c2 < n; c2++) {
                int r2 = r1 + c1 - c2;
                if (r2 < 0 || r2 >= n) continue;
                if (grid[r1][c1] == -1 || grid[r2][c2] == -1) continue;
                
                int cherries = grid[r1][c1];
                if (c1 != c2) cherries += grid[r2][c2];
                
                // Previous states
                for (int pr1 : {r1, r1-1}) {
                    for (int pc2 : {c2, c2-1}) {
                        int pc1 = c1 - (r1 - pr1);  // From same step
                        int pr2 = r2 - (c2 - pc2);
                        if (pr1 >= 0 && pc1 >= 0 && pr2 >= 0 && pc2 >= 0) {
                            if (dp[pr1][pc1][pc2] != INT_MIN) {
                                dp[r1][c1][c2] = max(dp[r1][c1][c2], 
                                                    dp[pr1][pc1][pc2] + cherries);
                            }
                        }
                    }
                }
            }
        }
    }
    
    return max(0, dp[n-1][n-1][n-1]);
}


/*
PROBLEM 9: Cherry Pickup II (LeetCode 1463)
───────────────────────────────────────────
Two robots start at (0,0) and (0,n-1).
Move down-left, down, or down-right.

Time: O(m*n²) | Space: O(n²)
*/
int cherryPickupII(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    dp[0][n-1] = grid[0][0] + grid[0][n-1];
    
    for (int row = 1; row < m; row++) {
        vector<vector<int>> newDp(n, vector<int>(n, -1));
        
        for (int c1 = 0; c1 < n; c1++) {
            for (int c2 = c1; c2 < n; c2++) {
                int cherries = grid[row][c1] + (c1 != c2 ? grid[row][c2] : 0);
                
                for (int pc1 = c1-1; pc1 <= c1+1; pc1++) {
                    for (int pc2 = c2-1; pc2 <= c2+1; pc2++) {
                        if (pc1 >= 0 && pc1 < n && pc2 >= 0 && pc2 < n && dp[pc1][pc2] != -1) {
                            newDp[c1][c2] = max(newDp[c1][c2], dp[pc1][pc2] + cherries);
                        }
                    }
                }
            }
        }
        
        dp = newDp;
    }
    
    int result = 0;
    for (int c1 = 0; c1 < n; c1++) {
        for (int c2 = c1; c2 < n; c2++) {
            result = max(result, dp[c1][c2]);
        }
    }
    
    return result;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Grid DP ===\n\n";
    
    // Unique Paths
    cout << "1. Unique paths (3x7): " << uniquePaths(3, 7) << "\n";
    
    // Minimum Path Sum
    vector<vector<int>> grid1 = {{1,3,1},{1,5,1},{4,2,1}};
    cout << "3. Min path sum: " << minPathSum(grid1) << "\n";
    
    // Triangle
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};
    cout << "4. Triangle min: " << minimumTotal(triangle) << "\n";
    
    // Falling Path
    vector<vector<int>> matrix = {{2,1,3},{6,5,4},{7,8,9}};
    cout << "5. Min falling path: " << minFallingPathSum(matrix) << "\n";
    
    // Dungeon Game
    vector<vector<int>> dungeon = {{-2,-3,3},{-5,-10,1},{10,30,-5}};
    cout << "7. Min HP for dungeon: " << calculateMinimumHP(dungeon) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

GRID DP TEMPLATE:
    for i = 0 to m-1:
        for j = 0 to n-1:
            dp[i][j] = grid[i][j] + optimal(dp[i-1][j], dp[i][j-1])

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Movement                                       |
+───────────────────────────────+────────────────────────────────────────────────+
| Unique Paths                  | Right, Down                                    |
| Min Path Sum                  | Right, Down                                    |
| Falling Path                  | Down, Down-Left, Down-Right                    |
| Dungeon Game                  | Work backwards from destination                |
| Cherry Pickup                 | Two simultaneous traversals                    |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

