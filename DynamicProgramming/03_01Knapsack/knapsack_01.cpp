/*
================================================================================
                    PATTERN 3: 0/1 KNAPSACK
================================================================================

When to use:
- Set of items with weight/value
- Select subset with constraint
- Each item can be chosen only ONCE
- Maximize/minimize total value

LeetCode Problems:
- 416. Partition Equal Subset Sum
- 494. Target Sum
- 1049. Last Stone Weight II

================================================================================
                    WHY REVERSE ITERATION? (CRITICAL CONCEPT!)
================================================================================

When converting 2D DP to 1D, iteration direction determines item reuse:

┌─────────────────────────────────────────────────────────────────────────────┐
│  REVERSE (right→left): 0/1 Knapsack - each item used AT MOST ONCE          │
│  FORWARD (left→right): Unbounded Knapsack - each item used UNLIMITED times │
└─────────────────────────────────────────────────────────────────────────────┘

EXAMPLE: nums = [2], target = 4
─────────────────────────────────

REVERSE (CORRECT for 0/1):
    Initial:  dp = [T, F, F, F, F]  (indices 0-4)
    j=4: dp[4] = dp[4] || dp[2] = F || F = F
    j=3: dp[3] = dp[3] || dp[1] = F || F = F
    j=2: dp[2] = dp[2] || dp[0] = F || T = T  ✓
    Result:   dp = [T, F, T, F, F]
    → dp[4] = FALSE (can't make 4 with single item 2) ✓ CORRECT!

FORWARD (WRONG for 0/1):
    Initial:  dp = [T, F, F, F, F]
    j=2: dp[2] = dp[2] || dp[0] = F || T = T  ✓
    j=3: dp[3] = dp[3] || dp[1] = F || F = F
    j=4: dp[4] = dp[4] || dp[2] = F || T = T  ✗ WRONG!
    Result:   dp = [T, F, T, F, T]
    → dp[4] = TRUE (used item 2 TWICE: 2+2=4) ✗ INCORRECT!

WHY THIS HAPPENS:
─────────────────
• REVERSE: When computing dp[j], dp[j-num] still has OLD value (before current item)
           → Each item considered only ONCE

• FORWARD: When computing dp[j], dp[j-num] may have NEW value (already updated)
           → Same item can be used MULTIPLE times

MEMORY TRICK:
─────────────
    "0/1 = Only once = gO back"     (REVERSE)
    "Unlimited = go Forward"         (FORWARD)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Classic 0/1 Knapsack
───────────────────────────────
Given weights and values, maximize value with capacity W.

2D Recurrence (conceptual):
    dp[i][w] = max value using first i items with capacity w
    dp[i][w] = max(dp[i-1][w], dp[i-1][w-wt[i]] + val[i])
                   ↑ skip item    ↑ take item (uses PREVIOUS row)

1D Space Optimization (code below):
    dp[w] = max(dp[w], dp[w - wt[i]] + val[i])
    Key: Iterate w BACKWARDS so dp[w-wt[i]] still has previous row's value

Time: O(n*W) | Space: O(W)
*/
int knapsack(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        // Iterate backwards to avoid using same item twice
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    
    return dp[W];
}


/*
────────────────────────────────────────────────────────────────────────────────
RECURSIVE + MEMOIZATION APPROACH (for understanding)
────────────────────────────────────────────────────────────────────────────────

This shows the INTUITION behind 0/1 knapsack:
- At each item, we have 2 choices: PICK or SKIP
- State: (index, remaining_capacity)
- Memoize to avoid recomputation

Recursive → Memoization → Bottom-up DP → Space Optimized 1D DP
*/
int knapsackMemo(vector<int>& wt, vector<int>& val, int i, int w, 
                 vector<vector<int>>& memo) {
    // Base case: no items left OR no capacity
    if (i < 0 || w == 0) return 0;
    
    // Already computed?
    if (memo[i][w] != -1) return memo[i][w];
    
    // Choice 1: SKIP current item
    int skip = knapsackMemo(wt, val, i - 1, w, memo);
    
    // Choice 2: PICK current item (only if it fits)
    int pick = 0;
    if (wt[i] <= w) {
        pick = val[i] + knapsackMemo(wt, val, i - 1, w - wt[i], memo);
    }
    
    // Take the better choice
    memo[i][w] = max(skip, pick);
    return memo[i][w];
}

int knapsackRecursive(vector<int>& wt, vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<int>> memo(n, vector<int>(W + 1, -1));
    return knapsackMemo(wt, val, n - 1, W, memo);
}

/*
UNDERSTANDING THE CONVERSION:
─────────────────────────────
Recursive:   knapsackMemo(wt, val, i-1, w, memo)        → uses previous item's result
                                  ↓
Bottom-up:   dp[i][w] = max(dp[i-1][w], ...)            → row i depends on row i-1
                                  ↓
1D Space:    for w = W to wt[i]:                        → iterate BACKWARDS
             dp[w] = max(dp[w], dp[w-wt[i]] + val[i])     so dp[w-wt[i]] has old value

The BACKWARDS iteration in 1D simulates accessing "previous row" in 2D!
*/


/*
PROBLEM 2: Partition Equal Subset Sum (LeetCode 416) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────
Can array be partitioned into two subsets with equal sum?

Convert to: Can we select items to reach sum/2?

Time: O(n*sum) | Space: O(sum)
*/
bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (int num : nums) sum += num;
    
    if (sum % 2 != 0) return false;
    int target = sum / 2;
    
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    
    for (int num : nums) {
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }
    
    return dp[target];
}


/*
PROBLEM 3: Target Sum (LeetCode 494)
────────────────────────────────────
Assign + or - to each number to reach target.

Let P = sum of positives, N = sum of negatives
P - N = target
P + N = total
=> P = (target + total) / 2

Count subsets with sum P.

Time: O(n*sum) | Space: O(sum)
*/
int findTargetSumWays(vector<int>& nums, int target) {
    int total = 0;
    for (int num : nums) total += num;
    
    if ((total + target) % 2 != 0 || total + target < 0) return 0;
    int P = (total + target) / 2;
    
    vector<int> dp(P + 1, 0);
    dp[0] = 1;
    
    for (int num : nums) {
        for (int j = P; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }
    
    return dp[P];
}


/*
PROBLEM 4: Last Stone Weight II (LeetCode 1049)
───────────────────────────────────────────────
Smash stones, difference remains. Minimize final weight.

Partition into two groups, minimize |sum1 - sum2|.
Find max sum <= total/2, answer = total - 2*sum.

Time: O(n*sum) | Space: O(sum)
*/
int lastStoneWeightII(vector<int>& stones) {
    int total = 0;
    for (int s : stones) total += s;
    
    int target = total / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    
    for (int stone : stones) {
        for (int j = target; j >= stone; j--) {
            dp[j] = dp[j] || dp[j - stone];
        }
    }
    
    // Find max achievable sum <= target
    for (int j = target; j >= 0; j--) {
        if (dp[j]) return total - 2 * j;
    }
    
    return total;
}


/*
PROBLEM 5: Ones and Zeroes (LeetCode 474)
─────────────────────────────────────────
Find max strings from array using at most m 0s and n 1s.

2D knapsack: dp[i][j] = max strings using i 0s and j 1s.

Time: O(len * m * n) | Space: O(m * n)
*/
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (const string& s : strs) {
        int zeros = count(s.begin(), s.end(), '0');
        int ones = s.size() - zeros;
        
        // Iterate backwards (0/1 knapsack)
        for (int i = m; i >= zeros; i--) {
            for (int j = n; j >= ones; j--) {
                dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1);
            }
        }
    }
    
    return dp[m][n];
}


/*
PROBLEM 6: Profitable Schemes (LeetCode 879)
────────────────────────────────────────────
Choose schemes with at most n members to get at least minProfit.

3D DP: dp[i][j][k] = ways using i members, j schemes, k profit.

Time: O(n * len * minProfit) | Space: O(n * minProfit)
*/
int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
    const int MOD = 1e9 + 7;
    // dp[members][profit] = number of ways
    vector<vector<int>> dp(n + 1, vector<int>(minProfit + 1, 0));
    
    for (int i = 0; i <= n; i++) dp[i][0] = 1;
    
    for (int k = 0; k < group.size(); k++) {
        int g = group[k], p = profit[k];
        
        for (int i = n; i >= g; i--) {
            for (int j = minProfit; j >= 0; j--) {
                int newProfit = min(minProfit, j + p);
                dp[i][newProfit] = (dp[i][newProfit] + dp[i - g][j]) % MOD;
            }
        }
    }
    
    return dp[n][minProfit];
}


/*
PROBLEM 7: Number of Ways to Earn Points (LeetCode 2585)
────────────────────────────────────────────────────────
Each type has count[i] questions worth marks[i]. Get exactly target points.

Bounded knapsack: each item has limited quantity.

Time: O(n * target * maxCount) | Space: O(target)
*/
int waysToReachTarget(int target, vector<vector<int>>& types) {
    const int MOD = 1e9 + 7;
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    
    for (auto& type : types) {
        int count = type[0], marks = type[1];
        
        for (int j = target; j >= 0; j--) {
            for (int k = 1; k <= count && k * marks <= j; k++) {
                dp[j] = (dp[j] + dp[j - k * marks]) % MOD;
            }
        }
    }
    
    return dp[target];
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== 0/1 Knapsack Pattern ===\n\n";
    
    // Classic Knapsack
    vector<int> wt = {1, 2, 3};
    vector<int> val = {6, 10, 12};
    cout << "1. Classic knapsack (W=5): " << knapsack(wt, val, 5) << "\n";
    
    // Partition Equal Subset
    vector<int> nums1 = {1, 5, 11, 5};
    cout << "2. Can partition [1,5,11,5]: " << (canPartition(nums1) ? "Yes" : "No") << "\n";
    
    // Target Sum
    vector<int> nums2 = {1, 1, 1, 1, 1};
    cout << "3. Ways to reach target 3: " << findTargetSumWays(nums2, 3) << "\n";
    
    // Last Stone Weight II
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << "4. Min last stone weight: " << lastStoneWeightII(stones) << "\n";
    
    // Ones and Zeroes
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    cout << "5. Max form (m=5, n=3): " << findMaxForm(strs, 5, 3) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

0/1 KNAPSACK TEMPLATE (Space Optimized):
    vector<int> dp(W + 1, 0);
    for each item i:
        for w = W down to wt[i]:  // BACKWARDS!
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i])
    return dp[W]

KEY: Iterate BACKWARDS to avoid reusing same item.

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Transformation                                 |
+───────────────────────────────+────────────────────────────────────────────────+
| Partition Equal Subset        | target = sum/2, check if reachable             |
| Target Sum                    | P = (target + sum)/2, count subsets            |
| Last Stone Weight II          | Minimize |sum1 - sum2| = sum - 2*maxHalf       |
| Ones and Zeroes               | 2D knapsack (0s and 1s as constraints)         |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

