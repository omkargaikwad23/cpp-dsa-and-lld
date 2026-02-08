/*
================================================================================
                        0/1 KNAPSACK PROBLEM
================================================================================

Problem: Given n items with weights and profits, maximize profit within capacity W.
         Each item can be taken at most ONCE (0/1 choice).

Example: W=50, items: [(wt=10, profit=60), (wt=20, profit=100), (wt=30, profit=120)]
         Answer: 220 (take items with wt=20 and wt=30)

Recurrence:
  dp[i][w] = max profit using first i items with capacity w
  
  if wt[i-1] > w:  dp[i][w] = dp[i-1][w]           // Can't take item i
  else:            dp[i][w] = max(dp[i-1][w],       // Don't take
                                  dp[i-1][w-wt[i-1]] + profit[i-1])  // Take

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 1: Memoization (Top-Down)                                          │
│ Time: O(n × W)  |  Space: O(n × W)                                          │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int knapsackMemo(vector<int>& wt, vector<int>& profit, int W, int i,
                 vector<vector<int>>& dp) {
    // Base: no items left or no capacity
    if (i == 0 || W == 0) return 0;
    
    if (dp[i][W] != -1) return dp[i][W];
    
    // Can't take item i (too heavy)
    if (wt[i-1] > W) {
        return dp[i][W] = knapsackMemo(wt, profit, W, i-1, dp);
    }
    
    // Choice: take or skip
    int skip = knapsackMemo(wt, profit, W, i-1, dp);
    int take = profit[i-1] + knapsackMemo(wt, profit, W - wt[i-1], i-1, dp);
    
    return dp[i][W] = max(skip, take);
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 2: Tabulation (Bottom-Up)                                          │
│ Time: O(n × W)  |  Space: O(n × W)                                          │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int knapsackTabu(vector<int>& wt, vector<int>& profit, int W) {
    int n = wt.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i-1] > w) {
                dp[i][w] = dp[i-1][w];  // Can't take
            } else {
                dp[i][w] = max(dp[i-1][w],                        // Skip
                               dp[i-1][w - wt[i-1]] + profit[i-1]); // Take
            }
        }
    }
    
    return dp[n][W];
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 3: Space Optimized (1D DP)                                         │
│ Time: O(n × W)  |  Space: O(W)                                              │
│                                                                             │
│ KEY: Process weights RIGHT to LEFT to avoid using updated values            │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int knapsackOptimized(vector<int>& wt, vector<int>& profit, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        // RIGHT to LEFT: ensures we use previous row's values
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], dp[w - wt[i]] + profit[i]);
        }
    }
    
    return dp[W];
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ MAIN                                                                        │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int main() {
    cout << "=== 0/1 Knapsack ===\n\n";
    
    vector<int> profit = {60, 100, 120};
    vector<int> wt = {10, 20, 30};
    int W = 50;
    int n = wt.size();
    
    // Memoization
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));
    cout << "Memoization: " << knapsackMemo(wt, profit, W, n, dp) << "\n";
    
    // Tabulation
    cout << "Tabulation:  " << knapsackTabu(wt, profit, W) << "\n";
    
    // Space Optimized
    cout << "Optimized:   " << knapsackOptimized(wt, profit, W) << "\n";
    
    cout << "\nExpected: 220 (items with wt=20,30 → profit=100+120)\n";
    
    return 0;
}


/*
================================================================================
                            VARIATIONS
================================================================================

┌────────────────────────┬─────────────────────────────────────────────────────┐
│ 0/1 Knapsack           │ Each item used at most ONCE                         │
│ Unbounded Knapsack     │ Each item can be used UNLIMITED times               │
│ Bounded Knapsack       │ Each item has a specific count limit                │
│ Subset Sum             │ Special case: profit[i] = wt[i], target = W         │
└────────────────────────┴─────────────────────────────────────────────────────┘

SPACE OPTIMIZATION KEY INSIGHT:
─────────────────────────────────
• 0/1 Knapsack:     Loop W → 0  (right to left)  - use OLD values
• Unbounded:        Loop 0 → W  (left to right)  - use NEW values

================================================================================
*/
