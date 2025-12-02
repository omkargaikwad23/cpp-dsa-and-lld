/*
================================================================================
                    PREFIX SUM - 2D PROBLEMS
================================================================================

2D prefix sum for matrix region queries.

Build: prefix[i][j] = sum of rectangle from (0,0) to (i-1, j-1)
Query: sum of rectangle (r1,c1) to (r2,c2)

Time: O(m*n) build, O(1) query | Space: O(m*n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Range Sum Query 2D - Immutable (LeetCode 304)
────────────────────────────────────────────────────────
Answer multiple 2D range sum queries efficiently.

Time: O(m*n) build, O(1) query | Space: O(m*n)
*/
class NumMatrix {
private:
    vector<vector<int>> prefix;
    
public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        
        int m = matrix.size(), n = matrix[0].size();
        prefix.resize(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1] 
                             + prefix[i-1][j] 
                             + prefix[i][j-1] 
                             - prefix[i-1][j-1];
            }
        }
    }
    
    int sumRegion(int r1, int c1, int r2, int c2) {
        return prefix[r2+1][c2+1] - prefix[r1][c2+1] 
             - prefix[r2+1][c1] + prefix[r1][c1];
    }
};


/*
PROBLEM 2: Matrix Block Sum (LeetCode 1314)
───────────────────────────────────────────
For each cell, sum all cells within distance k.

Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
Output: [[12,21,16],[27,45,33],[24,39,28]]

Time: O(m*n) | Space: O(m*n)
*/
vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
    int m = mat.size(), n = mat[0].size();
    
    // Build 2D prefix sum
    vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = mat[i-1][j-1] + prefix[i-1][j] 
                         + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }
    
    vector<vector<int>> result(m, vector<int>(n, 0));
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int r1 = max(0, i - k), c1 = max(0, j - k);
            int r2 = min(m - 1, i + k), c2 = min(n - 1, j + k);
            
            result[i][j] = prefix[r2+1][c2+1] - prefix[r1][c2+1] 
                         - prefix[r2+1][c1] + prefix[r1][c1];
        }
    }
    
    return result;
}


/*
PROBLEM 3: Count Square Submatrices with All Ones (LeetCode 1277) ⭐
────────────────────────────────────────────────────────────────────
Count total square submatrices of all 1s.

Approach: DP where dp[i][j] = max square size ending at (i,j)

Time: O(m*n) | Space: O(m*n) or O(n) optimized
*/
int countSquares(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    int count = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]}) + 1;
                }
                count += dp[i][j];  // Add all squares ending here
            }
        }
    }
    
    return count;
}


/*
PROBLEM 4: Maximal Square (LeetCode 221)
────────────────────────────────────────
Find largest square containing only 1s.

Same DP approach as above, track maximum.

Time: O(m*n) | Space: O(n)
*/
int maximalSquare(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<int> dp(n + 1, 0);
    int maxSide = 0, prev = 0;
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int temp = dp[j];
            if (matrix[i-1][j-1] == '1') {
                dp[j] = min({dp[j], dp[j-1], prev}) + 1;
                maxSide = max(maxSide, dp[j]);
            } else {
                dp[j] = 0;
            }
            prev = temp;
        }
        prev = 0;
    }
    
    return maxSide * maxSide;
}


/*
PROBLEM 5: Largest Plus Sign (LeetCode 764)
───────────────────────────────────────────
Find largest axis-aligned plus sign of 1s.

Build 4 prefix arrays (up, down, left, right).

Time: O(n²) | Space: O(n²)
*/
int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
    vector<vector<int>> grid(n, vector<int>(n, 1));
    for (auto& mine : mines) {
        grid[mine[0]][mine[1]] = 0;
    }
    
    // dp[i][j] = min arm length of plus centered at (i,j)
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int i = 0; i < n; i++) {
        // Left to right
        int count = 0;
        for (int j = 0; j < n; j++) {
            count = grid[i][j] ? count + 1 : 0;
            dp[i][j] = count;
        }
        
        // Right to left
        count = 0;
        for (int j = n - 1; j >= 0; j--) {
            count = grid[i][j] ? count + 1 : 0;
            dp[i][j] = min(dp[i][j], count);
        }
    }
    
    int maxOrder = 0;
    
    for (int j = 0; j < n; j++) {
        // Top to bottom
        int count = 0;
        for (int i = 0; i < n; i++) {
            count = grid[i][j] ? count + 1 : 0;
            dp[i][j] = min(dp[i][j], count);
        }
        
        // Bottom to top
        count = 0;
        for (int i = n - 1; i >= 0; i--) {
            count = grid[i][j] ? count + 1 : 0;
            dp[i][j] = min(dp[i][j], count);
            maxOrder = max(maxOrder, dp[i][j]);
        }
    }
    
    return maxOrder;
}


/*
PROBLEM 6: Number of Submatrices That Sum to Target (LeetCode 1074) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────────────────
Count submatrices with sum equal to target.

Approach: Fix top and bottom rows, reduce to 1D subarray sum problem.

Time: O(m² * n) | Space: O(n)
*/
int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    
    // Build row prefix sums
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            matrix[i][j] += matrix[i][j-1];
        }
    }
    
    int count = 0;
    
    // Fix left and right columns
    for (int c1 = 0; c1 < n; c1++) {
        for (int c2 = c1; c2 < n; c2++) {
            // Reduce to 1D problem
            unordered_map<int, int> prefixCount;
            prefixCount[0] = 1;
            int prefixSum = 0;
            
            for (int r = 0; r < m; r++) {
                int rowSum = matrix[r][c2] - (c1 > 0 ? matrix[r][c1-1] : 0);
                prefixSum += rowSum;
                
                if (prefixCount.count(prefixSum - target)) {
                    count += prefixCount[prefixSum - target];
                }
                prefixCount[prefixSum]++;
            }
        }
    }
    
    return count;
}


/*
PROBLEM 7: Max Sum of Rectangle No Larger Than K (LeetCode 363)
───────────────────────────────────────────────────────────────
Find max sum rectangle with sum <= k.

Time: O(m² * n * log n) | Space: O(n)
*/
int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m = matrix.size(), n = matrix[0].size();
    int maxSum = INT_MIN;
    
    // Fix top and bottom rows
    for (int r1 = 0; r1 < m; r1++) {
        vector<int> rowSum(n, 0);
        
        for (int r2 = r1; r2 < m; r2++) {
            for (int c = 0; c < n; c++) {
                rowSum[c] += matrix[r2][c];
            }
            
            // Find max subarray sum <= k
            set<int> prefixSet;
            prefixSet.insert(0);
            int prefixSum = 0;
            
            for (int sum : rowSum) {
                prefixSum += sum;
                
                // Find smallest prefix >= prefixSum - k
                auto it = prefixSet.lower_bound(prefixSum - k);
                if (it != prefixSet.end()) {
                    maxSum = max(maxSum, prefixSum - *it);
                }
                
                prefixSet.insert(prefixSum);
            }
        }
    }
    
    return maxSum;
}


/*
PROBLEM 8: Stamping the Grid (LeetCode 2132)
────────────────────────────────────────────
Check if we can stamp all 0s using stampHeight x stampWidth stamps.

Uses 2D prefix sum + 2D difference array.

Time: O(m*n) | Space: O(m*n)
*/
bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
    int m = grid.size(), n = grid[0].size();
    
    // 2D prefix sum of grid (to count 1s in rectangle)
    vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = grid[i-1][j-1] + prefix[i-1][j] 
                         + prefix[i][j-1] - prefix[i-1][j-1];
        }
    }
    
    // Check if rectangle (r1,c1) to (r2,c2) is all 0s
    auto sumRegion = [&](int r1, int c1, int r2, int c2) {
        return prefix[r2+1][c2+1] - prefix[r1][c2+1] 
             - prefix[r2+1][c1] + prefix[r1][c1];
    };
    
    // 2D difference array to mark stampable cells
    vector<vector<int>> diff(m + 2, vector<int>(n + 2, 0));
    
    for (int i = 0; i <= m - stampHeight; i++) {
        for (int j = 0; j <= n - stampWidth; j++) {
            int r2 = i + stampHeight - 1;
            int c2 = j + stampWidth - 1;
            
            if (sumRegion(i, j, r2, c2) == 0) {
                // Can place stamp
                diff[i][j]++;
                diff[i][c2 + 1]--;
                diff[r2 + 1][j]--;
                diff[r2 + 1][c2 + 1]++;
            }
        }
    }
    
    // Convert difference to prefix sum (stamp count at each cell)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            diff[i][j + 1] += diff[i][j];
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < m; i++) {
            diff[i + 1][j] += diff[i][j];
        }
    }
    
    // Check all 0s are covered
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && diff[i][j] == 0) {
                return false;
            }
        }
    }
    
    return true;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== 2D Prefix Sum ===\n\n";
    
    // Range Sum 2D
    vector<vector<int>> matrix1 = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}
    };
    NumMatrix nm(matrix1);
    cout << "1. Sum (2,1)-(4,3) = " << nm.sumRegion(2, 1, 4, 3) << "\n";
    cout << "   Sum (1,1)-(2,2) = " << nm.sumRegion(1, 1, 2, 2) << "\n";
    
    // Count Squares
    vector<vector<int>> matrix2 = {{0,1,1,1},{1,1,1,1},{0,1,1,1}};
    cout << "3. Count squares with all 1s: " << countSquares(matrix2) << "\n";
    
    // Maximal Square
    vector<vector<char>> matrix3 = {{'1','0','1','0','0'},
                                    {'1','0','1','1','1'},
                                    {'1','1','1','1','1'},
                                    {'1','0','0','1','0'}};
    cout << "4. Maximal square area: " << maximalSquare(matrix3) << "\n";
    
    // Submatrix Sum Target
    vector<vector<int>> matrix4 = {{0,1,0},{1,1,1},{0,1,0}};
    cout << "6. Submatrices with sum 0: " << numSubmatrixSumTarget(matrix4, 0) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

2D PREFIX SUM FORMULA:
─────────────────────
Build: prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]
Query: sum(r1,c1,r2,c2) = prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Technique                                      |
+───────────────────────────────+────────────────────────────────────────────────+
| Range Sum Query 2D            | Direct 2D prefix sum                           |
| Matrix Block Sum              | 2D prefix sum with bounds                      |
| Count Squares                 | DP: dp[i][j] = min(neighbors) + 1              |
| Submatrix Sum = Target        | Fix columns + 1D hashmap                       |
| Max Sum <= K                  | Fix rows + ordered set                         |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

