/*
================================================================================
                    DYNAMIC PROGRAMMING - MASTER GUIDE
================================================================================

Based on 20 Essential DP Patterns for Interview Preparation
Reference: https://blog.algomaster.io/p/20-patterns-to-master-dynamic-programming

================================================================================
                           DP FUNDAMENTALS
================================================================================

WHEN TO USE DP:
1. Optimal substructure - optimal solution contains optimal solutions to subproblems
2. Overlapping subproblems - same subproblems solved multiple times
3. Keywords: "minimum", "maximum", "count ways", "is it possible"

APPROACHES:
1. Top-Down (Memoization): Recursive with cache
2. Bottom-Up (Tabulation): Iterative, fill table

STEPS TO SOLVE:
1. Define state - what changes? (index, remaining capacity, etc.)
2. Define recurrence relation
3. Identify base cases
4. Determine iteration order (for bottom-up)
5. Optimize space if possible

================================================================================
                           20 DP PATTERNS
================================================================================

PATTERN                         | EXAMPLE PROBLEMS                    | DIFFICULTY
────────────────────────────────|─────────────────────────────────────|───────────
01. Fibonacci Sequence          | Climbing Stairs, Fib Number         | Easy
02. Kadane's Algorithm          | Max Subarray, Max Product Subarray  | Easy-Med
03. 0/1 Knapsack                | Partition Equal Subset, Target Sum  | Medium
04. Unbounded Knapsack          | Coin Change, Perfect Squares        | Medium
05. LCS (Longest Common Subseq) | LCS, Delete Operations              | Medium
06. LIS (Longest Incr Subseq)   | LIS, Russian Doll Envelopes         | Medium
07. Palindromic Subsequence     | Longest Palindromic Subseq          | Medium
08. Edit Distance               | Edit Distance, Min Delete Sum       | Medium
09. Subset Sum                  | Partition Equal Subset              | Medium
10. String Partition            | Word Break, Palindrome Partition    | Medium
11. Catalan Numbers             | Unique BSTs, Generate Parentheses   | Medium
12. Matrix Chain Multiplication | Burst Balloons, Merge Stones        | Hard
13. Count Distinct Ways         | Decode Ways, Count Texts            | Medium
14. DP on Grids                 | Unique Paths, Min Path Sum          | Easy-Med
15. DP on Trees                 | House Robber III, Tree Cameras      | Medium-Hard
16. DP on Graphs                | Cheapest Flights K Stops            | Medium
17. Digit DP                    | Numbers with Unique Digits          | Hard
18. Bitmask DP                  | TSP, Shortest Path All Nodes        | Hard
19. Probability DP              | Knight Probability                  | Medium
20. State Machine DP            | Stock Buy Sell with Cooldown        | Medium

================================================================================
                           FOLDER STRUCTURE
================================================================================

DynamicProgramming/
├── 00_DPOverview.cpp
├── 01_Fibonacci/
├── 02_Kadane/
├── 03_01Knapsack/
├── 04_UnboundedKnapsack/
├── 05_LCS/
├── 06_LIS/
├── 07_Palindrome/
├── 08_EditDistance/
├── 09_SubsetSum/
├── 10_StringPartition/
├── 11_CatalanNumbers/
├── 12_MatrixChainMultiplication/
├── 13_CountDistinctWays/
├── 14_DPOnGrids/
├── 15_DPOnTrees/
├── 16_DPOnGraphs/
├── 17_DigitDP/
├── 18_BitmaskDP/
├── 19_ProbabilityDP/
└── 20_StateMachineDP/

================================================================================
                           QUICK TEMPLATES
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// TEMPLATE 1: Top-Down Memoization
// ─────────────────────────────────────────────────────────────────────────────
int dp[1001];
int solve(int n) {
    if (n <= 1) return n;  // Base case
    if (dp[n] != -1) return dp[n];  // Already computed
    return dp[n] = solve(n-1) + solve(n-2);  // Recurrence
}

// ─────────────────────────────────────────────────────────────────────────────
// TEMPLATE 2: Bottom-Up Tabulation
// ─────────────────────────────────────────────────────────────────────────────
int fibonacci(int n) {
    vector<int> dp(n + 1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

// ─────────────────────────────────────────────────────────────────────────────
// TEMPLATE 3: Space Optimized (when only prev states needed)
// ─────────────────────────────────────────────────────────────────────────────
int fibOptimized(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// ─────────────────────────────────────────────────────────────────────────────
// TEMPLATE 4: 2D DP (Knapsack style)
// ─────────────────────────────────────────────────────────────────────────────
int knapsack2D(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i-1][w];  // Don't take
            if (wt[i-1] <= w) {
                dp[i][w] = max(dp[i][w], dp[i-1][w - wt[i-1]] + val[i-1]);  // Take
            }
        }
    }
    return dp[n][W];
}

// ─────────────────────────────────────────────────────────────────────────────
// TEMPLATE 5: String DP (LCS style)
// ─────────────────────────────────────────────────────────────────────────────
int lcs(string& s1, string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[m][n];
}

int main() {
    cout << "=== DP Master Guide ===" << endl;
    
    memset(dp, -1, sizeof(dp));
    cout << "Fibonacci(10) Top-Down: " << solve(10) << endl;
    cout << "Fibonacci(10) Bottom-Up: " << fibonacci(10) << endl;
    cout << "Fibonacci(10) Optimized: " << fibOptimized(10) << endl;
    
    return 0;
}

/*
================================================================================
                           COMPLEXITY PATTERNS
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Pattern                       | Time / Space                                   |
+───────────────────────────────+────────────────────────────────────────────────+
| Linear DP (Fibonacci)         | O(n) / O(n) or O(1)                            |
| Kadane                        | O(n) / O(1)                                    |
| 0/1 Knapsack                  | O(n*W) / O(n*W) or O(W)                        |
| LCS                           | O(m*n) / O(m*n) or O(n)                        |
| LIS                           | O(n²) or O(n log n) / O(n)                     |
| Edit Distance                 | O(m*n) / O(m*n) or O(n)                        |
| Grid DP                       | O(m*n) / O(m*n) or O(n)                        |
| Bitmask DP                    | O(n * 2^n) / O(2^n)                            |
| Interval DP                   | O(n³) / O(n²)                                  |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

