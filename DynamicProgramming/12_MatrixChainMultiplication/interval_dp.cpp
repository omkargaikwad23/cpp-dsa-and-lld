/*
================================================================================
                    PATTERN 12: MATRIX CHAIN MULTIPLICATION / INTERVAL DP
================================================================================

When to use:
- Optimal order of operations
- Combining elements pairwise with cost
- Interval-based problems

LeetCode Problems:
- 1039. Minimum Score Triangulation of Polygon
- 312. Burst Balloons
- 1000. Minimum Cost to Merge Stones

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Matrix Chain Multiplication (Classic) ⭐
──────────────────────────────────────────────────
Minimize scalar multiplications to compute A1 * A2 * ... * An.
dims[i-1] x dims[i] is dimension of matrix i.

dp[i][j] = min cost to multiply matrices i to j
dp[i][j] = min(dp[i][k] + dp[k+1][j] + dims[i-1]*dims[k]*dims[j])

Time: O(n³) | Space: O(n²)
*/
int matrixChainMultiplication(vector<int>& dims) {
    int n = dims.size() - 1;  // Number of matrices
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    
    for (int len = 2; len <= n; len++) {
        for (int i = 1; i <= n - len + 1; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + dims[i-1] * dims[k] * dims[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    
    return dp[1][n];
}


/*
PROBLEM 2: Burst Balloons (LeetCode 312) ⭐ GOOGLE FAVORITE
──────────────────────────────────────────────────────────
Burst balloons to maximize coins (nums[i-1] * nums[i] * nums[i+1]).

Key insight: Think of last balloon to burst in range.

dp[i][j] = max coins from bursting balloons in (i, j) exclusive

Time: O(n³) | Space: O(n²)
*/
// ─────────────────────────────────────────────────────────────────────────────
// APPROACH 1: Iterative Bottom-Up DP (with virtual balloons)
// ─────────────────────────────────────────────────────────────────────────────
int maxCoinsIterative(vector<int>& nums) {
    int n = nums.size();
    
    // Step 1: Add virtual balloons with value 1 at both ends
    // Original: [3, 1, 5, 8]  →  Modified: [1, 3, 1, 5, 8, 1]
    // This simplifies boundary handling (no special cases for edges)
    vector<int> arr(n + 2, 1);
    for (int i = 0; i < n; i++) arr[i + 1] = nums[i];
    
    // Step 2: dp[i][j] = max coins for bursting all balloons in range (i, j) EXCLUSIVE
    // Note: (i, j) exclusive means balloons at index i and j are NOT burst
    // Example: dp[0][3] = max coins from bursting balloons at indices 1, 2 (not 0 or 3)
    vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
    
    // Step 3: Build solution bottom-up by increasing window length
    // len = number of balloons to burst in the range
    for (int len = 1; len <= n; len++) {
        // i = left boundary (exclusive), j = right boundary (exclusive)
        // We need j = i + len + 1 to have 'len' balloons between i and j
        for (int i = 0; i + len + 1 <= n + 1; i++) {
            int j = i + len + 1;
            
            // Step 4: Try each balloon k as the LAST one to burst in range (i, j)
            // Key insight: When k is burst last, arr[i] and arr[j] are its neighbors
            // because all other balloons between them are already gone
            for (int k = i + 1; k < j; k++) {
                // Coins from bursting k last = arr[i] * arr[k] * arr[j]
                // Plus: coins from bursting left subproblem + right subproblem
                int coins = arr[i] * arr[k] * arr[j];
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + coins);
            }
        }
    }
    
    // Answer: max coins for bursting all balloons between virtual boundaries
    return dp[0][n + 1];
}

// ─────────────────────────────────────────────────────────────────────────────
// APPROACH 2: Recursive Top-Down with Memoization (simpler, no virtual balloons)
// ─────────────────────────────────────────────────────────────────────────────
class BurstBalloonsMemo {
    vector<vector<int>> memo;
    
    // Returns max coins for bursting all balloons in range [left, right] INCLUSIVE
    int dfs(vector<int>& nums, int left, int right) {
        // Base case: no balloons in range
        if (left > right) return 0;
        
        if (memo[left][right] != -1) return memo[left][right];
        
        int maxCoins = 0;
        
        // Try each balloon i as the LAST one to burst in range [left, right]
        for (int i = left; i <= right; i++) {
            // When balloon i is burst last in [left, right]:
            // - All balloons in [left, i-1] are already burst
            // - All balloons in [i+1, right] are already burst
            // - So neighbors of i are nums[left-1] and nums[right+1]
            //   (or 1 if out of bounds)
            
            int leftNeighbor = (left > 0) ? nums[left - 1] : 1;
            int rightNeighbor = (right < nums.size() - 1) ? nums[right + 1] : 1;
            
            // Coins from bursting balloon i last
            int coins = leftNeighbor * nums[i] * rightNeighbor;
            
            // Add coins from left and right subproblems
            coins += dfs(nums, left, i - 1) + dfs(nums, i + 1, right);
            
            maxCoins = max(maxCoins, coins);
        }
        
        return memo[left][right] = maxCoins;
    }
    
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        memo.assign(n, vector<int>(n, -1));
        return dfs(nums, 0, n - 1);
    }
};


/*
PROBLEM 3: Minimum Score Triangulation of Polygon (LeetCode 1039)
─────────────────────────────────────────────────────────────────
Triangulate polygon, minimize sum of triangle scores.

dp[i][j] = min score to triangulate vertices i to j

Time: O(n³) | Space: O(n²)
*/
int minScoreTriangulation(vector<int>& values) {
    int n = values.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i + 1; k < j; k++) {
                int score = values[i] * values[k] * values[j];
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j] + score);
            }
        }
    }
    
    return dp[0][n - 1];
}


/*
PROBLEM 4: Minimum Cost to Merge Stones (LeetCode 1000)
───────────────────────────────────────────────────────
Merge k consecutive piles into one, cost = sum of stones.

dp[i][j][m] = min cost to merge stones[i..j] into m piles

Time: O(n³ * k) | Space: O(n² * k)
*/
int mergeStones(vector<int>& stones, int k) {
    int n = stones.size();
    if ((n - 1) % (k - 1) != 0) return -1;
    
    // Prefix sum
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) prefix[i + 1] = prefix[i] + stones[i];
    
    // dp[i][j] = min cost to merge i to j as much as possible
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int len = k; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            for (int m = i; m < j; m += k - 1) {
                dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
            }
            
            // If can merge to one pile
            if ((j - i) % (k - 1) == 0) {
                dp[i][j] += prefix[j + 1] - prefix[i];
            }
        }
    }
    
    return dp[0][n - 1];
}


/*
PROBLEM 5: Minimum Cost Tree From Leaf Values (LeetCode 1130)
─────────────────────────────────────────────────────────────
Build binary tree, cost = sum of (max_left * max_right) for each internal node.

Time: O(n³) | Space: O(n²)
*/
int mctFromLeafValues(vector<int>& arr) {
    int n = arr.size();
    
    // maxVal[i][j] = max value in arr[i..j]
    vector<vector<int>> maxVal(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        maxVal[i][i] = arr[i];
        for (int j = i + 1; j < n; j++) {
            maxVal[i][j] = max(maxVal[i][j-1], arr[j]);
        }
    }
    
    // dp[i][j] = min cost for arr[i..j]
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i; k < j; k++) {
                int cost = dp[i][k] + dp[k+1][j] + maxVal[i][k] * maxVal[k+1][j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    
    return dp[0][n - 1];
}


/*
PROBLEM 6: Strange Printer (LeetCode 664)
─────────────────────────────────────────
Printer can print sequence of same character.
Min turns to print string.

dp[i][j] = min turns for s[i..j]

Time: O(n³) | Space: O(n²)
*/
int strangePrinter(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 1;
        for (int j = i + 1; j < n; j++) {
            dp[i][j] = dp[i][j-1] + 1;  // Print s[j] separately
            
            for (int k = i; k < j; k++) {
                if (s[k] == s[j]) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + (k+1 <= j-1 ? dp[k+1][j-1] : 0));
                }
            }
        }
    }
    
    return dp[0][n - 1];
}


/*
PROBLEM 7: Optimal Binary Search Tree (Classic)
───────────────────────────────────────────────
Build BST to minimize expected search cost.
Keys have frequencies.

Time: O(n³) | Space: O(n²)
*/
int optimalBST(vector<int>& keys, vector<int>& freq) {
    int n = keys.size();
    
    // sum[i][j] = sum of freq[i..j]
    vector<vector<int>> sum(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        sum[i][i] = freq[i];
        for (int j = i + 1; j < n; j++) {
            sum[i][j] = sum[i][j-1] + freq[j];
        }
    }
    
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) dp[i][i] = freq[i];
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            for (int r = i; r <= j; r++) {  // r as root
                int cost = sum[i][j];  // All nodes contribute to their level
                if (r > i) cost += dp[i][r-1];
                if (r < j) cost += dp[r+1][j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }
    
    return dp[0][n - 1];
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Interval DP ===\n\n";
    
    // Matrix Chain
    vector<int> dims = {10, 30, 5, 60};
    cout << "1. Matrix chain: " << matrixChainMultiplication(dims) << "\n";
    
    // Burst Balloons
    vector<int> balloons = {3, 1, 5, 8};
    cout << "2. Burst balloons: " << maxCoins(balloons) << "\n";
    
    // Triangulation
    vector<int> values = {1, 2, 3};
    cout << "3. Min triangulation: " << minScoreTriangulation(values) << "\n";
    
    // MCT from Leaf
    vector<int> arr = {6, 2, 4};
    cout << "5. MCT from leaves: " << mctFromLeafValues(arr) << "\n";
    
    // Strange Printer
    cout << "6. Strange printer 'aaabbb': " << strangePrinter("aaabbb") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

INTERVAL DP TEMPLATE:
    for len = 2 to n:
        for i = 0 to n - len:
            j = i + len - 1
            for k = i to j - 1:  // Split point
                dp[i][j] = optimal(dp[i][k] + dp[k+1][j] + cost)

KEY INSIGHT: Think of the LAST operation (merge/burst/split).

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Split Decision                                 |
+───────────────────────────────+────────────────────────────────────────────────+
| Matrix Chain                  | Where to split multiplication                  |
| Burst Balloons                | Which balloon to burst LAST                    |
| Triangulation                 | Which vertex forms triangle with i,j           |
| Merge Stones                  | Where to divide for merge                      |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

