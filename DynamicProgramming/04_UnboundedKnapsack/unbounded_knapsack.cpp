/*
================================================================================
                    PATTERN 4: UNBOUNDED KNAPSACK
================================================================================

When to use:
- Items can be selected MULTIPLE times (infinite supply)
- Coin change variants
- Rod cutting, ribbon cutting

Key difference from 0/1: Iterate FORWARDS (can reuse items)

LeetCode Problems:
- 322. Coin Change
- 518. Coin Change II
- 279. Perfect Squares

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Coin Change - Minimum Coins (LeetCode 322) ⭐ CLASSIC
───────────────────────────────────────────────────────────────
Find minimum coins to make amount.

dp[i] = min coins to make amount i
dp[i] = min(dp[i - coin] + 1) for all coins

Time: O(n * amount) | Space: O(amount)
*/
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);  // amount+1 as "infinity"
    dp[0] = 0;
    
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return dp[amount] > amount ? -1 : dp[amount];
}


/*
PROBLEM 2: Coin Change II - Count Ways (LeetCode 518)
─────────────────────────────────────────────────────
Count number of combinations to make amount.

dp[i] = number of ways to make amount i
Order matters: iterate coins first (combinations), then amounts.

Time: O(n * amount) | Space: O(amount)
*/
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    
    // Coins first = combinations (order doesn't matter)
    for (int coin : coins) {
        for (int i = coin; i <= amount; i++) {  // FORWARDS (unlimited)
            dp[i] += dp[i - coin];
        }
    }
    
    return dp[amount];
}

// If we want permutations (order matters), swap loops
int changePermutations(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    
    // Amount first = permutations (1,2 and 2,1 are different)
    for (int i = 1; i <= amount; i++) {
        for (int coin : coins) {
            if (coin <= i) {
                dp[i] += dp[i - coin];
            }
        }
    }
    
    return dp[amount];
}

/*
────────────────────────────────────────────────────────────────────────────────
        COMBINATIONS vs PERMUTATIONS: WHY LOOP ORDER MATTERS (CRITICAL!)
────────────────────────────────────────────────────────────────────────────────

Example: amount = 3, coins = [1, 2]
- COMBINATIONS (order doesn't matter): {1,1,1}, {1,2}           → 2 ways
- PERMUTATIONS (order matters):        {1,1,1}, {1,2}, {2,1}    → 3 ways

────────────────────────────────────────────────────────────────────────────────
COINS FIRST → COMBINATIONS (LeetCode 518: Coin Change II)
────────────────────────────────────────────────────────────────────────────────

    for (int coin : coins) {                    // Process coin 1 fully, THEN coin 2
        for (int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }

Trace (amount=3, coins=[1,2]):

    Initial:    dp = [1, 0, 0, 0]

    Process coin=1 COMPLETELY:
      i=1: dp[1] += dp[0] → dp[1] = 1    (ways: {1})
      i=2: dp[2] += dp[1] → dp[2] = 1    (ways: {1,1})
      i=3: dp[3] += dp[2] → dp[3] = 1    (ways: {1,1,1})
      
    After coin 1: dp = [1, 1, 1, 1]

    Process coin=2:
      i=2: dp[2] += dp[0] → dp[2] = 2    (ways: {1,1}, {2})
      i=3: dp[3] += dp[1] → dp[3] = 2    (ways: {1,1,1}, {1,2})
      
    Final: dp = [1, 1, 2, 2]   →   dp[3] = 2 ✓

WHY? Once done with coin 1, we NEVER go back. So {2,1} is impossible.
     We're essentially saying: "use all 1s first, then all 2s"

────────────────────────────────────────────────────────────────────────────────
AMOUNT FIRST → PERMUTATIONS (LeetCode 377: Combination Sum IV)
────────────────────────────────────────────────────────────────────────────────

    for (int i = 1; i <= amount; i++) {         // For each amount, try ALL coins
        for (int coin : coins) {
            if (coin <= i) dp[i] += dp[i - coin];
        }
    }

Trace (amount=3, coins=[1,2]):

    Initial: dp = [1, 0, 0, 0]

    i=1: Try ALL coins
      coin=1: dp[1] += dp[0] → dp[1] = 1    (ways: {1})
      coin=2: skip (2 > 1)
      
    i=2: Try ALL coins
      coin=1: dp[2] += dp[1] → dp[2] = 1    (ways: {1,1})
      coin=2: dp[2] += dp[0] → dp[2] = 2    (ways: {1,1}, {2})
      
    i=3: Try ALL coins
      coin=1: dp[3] += dp[2] → dp[3] = 2    (ways: {1,1,1}, {2,1})
      coin=2: dp[3] += dp[1] → dp[3] = 3    (ways: {1,1,1}, {2,1}, {1,2})
      
    Final: dp = [1, 1, 2, 3]   →   dp[3] = 3 ✓

WHY? At each amount, we consider ALL coins. The LAST coin can be anything.
     {1,2} and {2,1} are different sequences → both counted!

────────────────────────────────────────────────────────────────────────────────
VISUAL SUMMARY
────────────────────────────────────────────────────────────────────────────────

┌──────────────────────────────────────────────────────────────────────────────┐
│  COINS FIRST:   Use all coin[0], then all coin[1], then all coin[2]...      │
│                 → Fixed order of coin types → COMBINATIONS                   │
│                                                                              │
│  AMOUNT FIRST:  For each amount, "what was the LAST coin used?"             │
│                 → Any coin can be last → All ORDERINGS counted               │
└──────────────────────────────────────────────────────────────────────────────┘

MEMORY TRICK:
    "Coins first = Committed order = Combinations"
    "Amount first = Any last coin = All arrangements (Permutations)"

+─────────────────────────+─────────────────────────+─────────────────────────+
| Aspect                  | Combinations            | Permutations            |
+─────────────────────────+─────────────────────────+─────────────────────────+
| Outer Loop              | Coins                   | Amount                  |
| Inner Loop              | Amount                  | Coins                   |
| {1,2} vs {2,1}         | Same (counted once)     | Different (counted 2x)  |
| LeetCode                | 518. Coin Change II     | 377. Combination Sum IV |
+─────────────────────────+─────────────────────────+─────────────────────────+

================================================================================
*/


/*
PROBLEM 3: Perfect Squares (LeetCode 279)
─────────────────────────────────────────
Min perfect squares that sum to n.

Same as coin change with coins = [1, 4, 9, 16, ...]

Time: O(n * sqrt(n)) | Space: O(n)
*/
int numSquares(int n) {
    vector<int> dp(n + 1, n + 1);
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j * j <= i; j++) {
            dp[i] = min(dp[i], dp[i - j * j] + 1);
        }
    }
    
    return dp[n];
}


/*
PROBLEM 4: Combination Sum IV (LeetCode 377)
────────────────────────────────────────────
Count permutations (order matters) that sum to target.

Time: O(n * target) | Space: O(target)
*/
int combinationSum4(vector<int>& nums, int target) {
    vector<unsigned int> dp(target + 1, 0);
    dp[0] = 1;
    
    for (int i = 1; i <= target; i++) {
        for (int num : nums) {
            if (num <= i) {
                dp[i] += dp[i - num];
            }
        }
    }
    
    return dp[target];
}


/*
PROBLEM 5: Integer Break (LeetCode 343)
───────────────────────────────────────
Break n into sum of positive integers (at least 2 parts), maximize product.

Key Insight:
- dp[i] = max product we can get by breaking i (or keeping i as-is for internal use)
- For num >= 4: try all first pieces i, multiply by dp[num-i]
- Base cases: dp[1]=1, dp[2]=2, dp[3]=3 (these are optimal pieces to use internally)
- Edge case: n=2 → must break → 1*1=1, n=3 → must break → 1*2=2

Why start loop from i=2?
- Breaking off 1 is never optimal (1 * rest < rest)
- 2 and 3 are the "magic" numbers that maximize products

Time: O(n²) | Space: O(n)
*/
int integerBreak(int n) {
    // Edge cases: must break into at least 2 parts
    // n=2: 1+1 → product=1, n=3: 1+2 → product=2
    if (n <= 3) return n - 1;
    
    vector<int> dp(n + 1, 0);
    
    // Base cases: dp[1]=1, dp[2]=2, dp[3]=3
    for(int num = 1; num <= 3; num++) 
        dp[num] = num;
    
    // For num >= 4, breaking always helps
    for (int num = 4; num <= n; num++) {
        int ans = num;  // Start with num itself (used when num is a piece, not the final answer)
        
        // Try breaking off piece of size i, multiply by optimal product of remaining
        for (int i = 2; i < num; i++) {
            ans = max(ans, i * dp[num - i]);
        }
        
        dp[num] = ans;
    }
    
    return dp[n];
}


/*
PROBLEM 6: Minimum Cost For Tickets (LeetCode 983)
──────────────────────────────────────────────────
Buy 1-day, 7-day, or 30-day pass. Minimize cost to cover all travel days.

Time: O(last_day) | Space: O(last_day)
*/
int mincostTickets(vector<int>& days, vector<int>& costs) {
    int lastDay = days.back();
    vector<int> dp(lastDay + 1, 0);
    unordered_set<int> travelDays(days.begin(), days.end());
    
    for (int i = 1; i <= lastDay; i++) {
        if (!travelDays.count(i)) {
            dp[i] = dp[i - 1];  // No travel needed
        } else {
            dp[i] = min({
                dp[i - 1] + costs[0],
                dp[max(0, i - 7)] + costs[1],
                dp[max(0, i - 30)] + costs[2]
            });
        }
    }
    
    return dp[lastDay];
}


/*
PROBLEM 7: Rod Cutting (Classic)
────────────────────────────────
Cut rod of length n, price[i] for length i. Maximize profit.

Time: O(n²) | Space: O(n)
*/
int rodCutting(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = max(dp[i], price[j - 1] + dp[i - j]);
        }
    }
    
    return dp[n];
}


/*
PROBLEM 8: Number of Dice Rolls With Target Sum (LeetCode 1155)
───────────────────────────────────────────────────────────────
n dice with k faces. Count ways to get target sum.

Time: O(n * target * k) | Space: O(target)
*/
int numRollsToTarget(int n, int k, int target) {
    const int mod = 1e9 + 7;
    vector<int> dp(target + 1);
    dp[0] = 1;
    
    for(int d = 1; d <= n; d++) { // number of dice
        vector<int> dp1(target + 1);

        // number of faces on each die
        for(int j = 1; j <= k; j++) { 
            // target sum we need to achieve by rolling n dice
            for(int i = j; i <= target; i++) { 
                dp1[i] = (dp1[i] + dp[i - j]) % mod;
            }
        }
        swap(dp, dp1); 
    }
    return dp[target];
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Unbounded Knapsack Pattern ===\n\n";
    
    // Coin Change Min
    vector<int> coins1 = {1, 2, 5};
    cout << "1. Min coins for 11: " << coinChange(coins1, 11) << "\n";
    
    // Coin Change Count
    vector<int> coins2 = {1, 2, 5};
    cout << "2. Ways to make 5: " << change(5, coins2) << "\n";
    
    // Perfect Squares
    cout << "3. Min squares for 12: " << numSquares(12) << "\n";
    
    // Combination Sum IV
    vector<int> nums = {1, 2, 3};
    cout << "4. Combination Sum IV (target=4): " << combinationSum4(nums, 4) << "\n";
    
    // Integer Break
    cout << "5. Integer Break (10): " << integerBreak(10) << "\n";
    
    // Travel Tickets
    vector<int> days = {1, 4, 6, 7, 8, 20};
    vector<int> costs = {2, 7, 15};
    cout << "6. Min ticket cost: " << mincostTickets(days, costs) << "\n";
    
    // Rod Cutting
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20};
    cout << "7. Rod cutting (n=8): " << rodCutting(price, 8) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

UNBOUNDED KNAPSACK TEMPLATE:
    vector<int> dp(target + 1, 0);
    dp[0] = base_case;
    
    for each item:
        for i = item to target:  // FORWARDS (can reuse)
            dp[i] = f(dp[i], dp[i - item])
    return dp[target]

+───────────────────────────────+────────────────────────────────────────────────+
| Problem Type                  | Loop Order                                     |
+───────────────────────────────+────────────────────────────────────────────────+
| 0/1 Knapsack                  | items -> capacity BACKWARDS                    |
| Unbounded (combinations)      | items -> capacity FORWARDS                     |
| Unbounded (permutations)      | capacity -> items FORWARDS                     |
+───────────────────────────────+────────────────────────────────────────────────+

COMBINATIONS vs PERMUTATIONS:
- Combinations (1,2 = 2,1): Items in outer loop
- Permutations (1,2 ≠ 2,1): Target in outer loop

================================================================================
*/

