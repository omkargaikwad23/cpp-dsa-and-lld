/*
================================================================================
                    RECTANGLE CUTTING INTO SQUARES
================================================================================

Problem: Given an a×b rectangle, cut it into squares using minimum cuts.
         Each cut splits a rectangle into two smaller rectangles.
         Count the minimum number of cuts needed.

Example: 3×5 rectangle → Answer: 3 cuts

    ┌─────────────┐      ┌───┬───┬───┐
    │             │      │   │   │   │
    │    3×5      │  →   │3×3│   │   │  (2 vertical cuts)
    │             │      │   │   │   │
    └─────────────┘      └───┴───┴───┘
                              ↓
                         ┌───┬───┬───┐
                         │   │ 2 │   │
                         │3×3├───┤   │  (1 horizontal cut on 3×2)
                         │   │ 1 │   │
                         └───┴───┴───┘
    
    Total: 3 cuts → Four squares (3×3, 2×2, 1×1, 1×1)

Recurrence:
  dp[h][w] = minimum cuts to make h×w rectangle into squares
  
  if h == w: dp[h][w] = 0  (already a square!)
  else:
    - Try all vertical cuts:   dp[h][w] = min(1 + dp[h][i] + dp[h][w-i])
    - Try all horizontal cuts: dp[h][w] = min(1 + dp[i][w] + dp[h-i][w])

Time: O(h × w × (h + w))  |  Space: O(h × w)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 1: Tabulation (Bottom-Up)                                          │
│ Time: O(h × w × (h + w))  |  Space: O(h × w)                                │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int minCutsTabu(int height, int width) {
    vector<vector<int>> dp(height + 1, vector<int>(width + 1, 0));
    
    for (int h = 1; h <= height; h++) {
        for (int w = 1; w <= width; w++) {
            if (h == w) {
                dp[h][w] = 0;  // Already a square
                continue;
            }
            
            int minCuts = INT_MAX;
            
            // Try all vertical cuts (split width)
            for (int i = 1; i < w; i++) {
                minCuts = min(minCuts, 1 + dp[h][i] + dp[h][w - i]);
            }
            
            // Try all horizontal cuts (split height)
            for (int i = 1; i < h; i++) {
                minCuts = min(minCuts, 1 + dp[i][w] + dp[h - i][w]);
            }
            
            dp[h][w] = minCuts;
        }
    }
    
    return dp[height][width];
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 2: Memoization (Top-Down)                                          │
│ Time: O(h × w × (h + w))  |  Space: O(h × w)                                │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int solve(int h, int w, vector<vector<int>>& memo) {
    if (h == w) return 0;  // Already a square
    if (memo[h][w] != -1) return memo[h][w];
    
    int minCuts = INT_MAX;
    
    // Vertical cuts
    for (int i = 1; i < w; i++) {
        minCuts = min(minCuts, 1 + solve(h, i, memo) + solve(h, w - i, memo));
    }
    
    // Horizontal cuts
    for (int i = 1; i < h; i++) {
        minCuts = min(minCuts, 1 + solve(i, w, memo) + solve(h - i, w, memo));
    }
    
    return memo[h][w] = minCuts;
}

int minCutsMemo(int height, int width) {
    vector<vector<int>> memo(height + 1, vector<int>(width + 1, -1));
    return solve(height, width, memo);
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ MAIN                                                                        │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int main() {
    cout << "=== Rectangle Cutting into Squares ===\n\n";
    
    // Test cases
    vector<tuple<int, int, int>> tests = {
        {3, 5, 3},   // 3×5 → 3 cuts
        {2, 2, 0},   // Already a square
        {1, 5, 4},   // 1×5 → 4 cuts (cut into five 1×1)
        {3, 3, 0},   // Already a square
        {4, 6, 3},   // 4×6 → 3 cuts
        {5, 7, 4},   // 5×7 → 4 cuts
    };
    
    for (auto [h, w, expected] : tests) {
        int result = minCutsTabu(h, w);
        cout << h << "×" << w << " → " << result << " cuts";
        cout << (result == expected ? " ✓" : " ✗") << "\n";
    }
    
    cout << "\nVerify with memoization:\n";
    cout << "3×5 → " << minCutsMemo(3, 5) << " cuts\n";
    cout << "5×7 → " << minCutsMemo(5, 7) << " cuts\n";
    
    return 0;
}

/*
================================================================================
                            DRY RUN: 3×5
================================================================================

dp[1][1] = 0 (square)
dp[2][2] = 0 (square)
dp[3][3] = 0 (square)

dp[1][2] = 1 (one cut → two 1×1)
dp[1][3] = 2 (two cuts → three 1×1)
dp[2][3] = min(1+dp[2][1]+dp[2][2], 1+dp[2][2]+dp[2][1], 1+dp[1][3]+dp[1][3])
         = min(1+1+0, 1+0+1, 1+2+2) = 2

dp[3][5]:
  Vertical cuts:
    i=1: 1 + dp[3][1] + dp[3][4] = 1 + 2 + 2 = 5
    i=2: 1 + dp[3][2] + dp[3][3] = 1 + 2 + 0 = 3 ← minimum!
    i=3: 1 + dp[3][3] + dp[3][2] = 1 + 0 + 2 = 3
    i=4: 1 + dp[3][4] + dp[3][1] = 1 + 2 + 2 = 5
  
  Horizontal cuts:
    i=1: 1 + dp[1][5] + dp[2][5] = 1 + 4 + 3 = 8
    i=2: 1 + dp[2][5] + dp[1][5] = 1 + 3 + 4 = 8

  Result: dp[3][5] = 3 ✓

================================================================================
*/
