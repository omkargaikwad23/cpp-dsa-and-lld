/*
================================================================================
COIN COMBINATIONS II (CSES) / Combination Sum IV (LeetCode 377)
================================================================================

Problem: Count distinct ways to make sum using coins (unlimited supply).
         ORDER MATTERS: 2+5 and 5+2 are counted as DIFFERENT ways.

Example: coins = {2, 3, 5}, sum = 9
Ways (8 total):
    Using 2,2,5: {2+2+5}, {2+5+2}, {5+2+2}     → 3 ways
    Using 3,3,3: {3+3+3}                        → 1 way
    Using 2,2,2,3: {2+2+2+3}, {2+2+3+2}, {2+3+2+2}, {3+2+2+2} → 4 ways

This is PERMUTATION counting → Amount in OUTER loop, Coins in INNER loop!

Related: See unbounded_knapsack.cpp for detailed explanation of
         Combinations vs Permutations loop order.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

/*
────────────────────────────────────────────────────────────────────────────────
APPROACH: Bottom-Up DP (Permutations - Order Matters)
────────────────────────────────────────────────────────────────────────────────

dp[i] = number of ways to make sum i (counting different orderings)

Loop Order (CRITICAL!):
    AMOUNT first → COINS second = PERMUTATIONS (2+5 ≠ 5+2)
    COINS first → AMOUNT second = COMBINATIONS (2+5 = 5+2)

Time: O(sum * n) | Space: O(sum)
*/
long long coinCombPermutations(vector<int>& coins, int sum) {
    vector<long long> dp(sum + 1, 0);
    dp[0] = 1;  // Base: 1 way to make sum 0
    
    // AMOUNT FIRST → counts PERMUTATIONS (order matters)
    for (int amount = 1; amount <= sum; amount++) {
        // Try each coin as the LAST coin used
        for (int coin : coins) {
            if (coin <= amount) {
                dp[amount] = (dp[amount] + dp[amount - coin]) % MOD;
            }
        }
    }
    
    return dp[sum];
}


/*
────────────────────────────────────────────────────────────────────────────────
COMPARISON: Permutations vs Combinations
────────────────────────────────────────────────────────────────────────────────

For coins = {2, 3, 5}, sum = 9:

PERMUTATIONS (this problem - order matters):
    {2+2+5}, {2+5+2}, {5+2+2} are 3 DIFFERENT ways
    Answer: 8 ways

COMBINATIONS (Coin Change II - order doesn't matter):
    {2+2+5}, {2+5+2}, {5+2+2} are the SAME way (just {2,2,5})
    Answer: 3 ways

────────────────────────────────────────────────────────────────────────────────
*/

// For comparison: Combinations version (order doesn't matter)
long long coinCombCombinations(vector<int>& coins, int sum) {
    vector<long long> dp(sum + 1, 0);
    dp[0] = 1;
    
    // COINS FIRST → counts COMBINATIONS (order doesn't matter)
    for (int coin : coins) {
        for (int amount = coin; amount <= sum; amount++) {
            dp[amount] = (dp[amount] + dp[amount - coin]) % MOD;
        }
    }
    
    return dp[sum];
}


int main() {
    cout << "=== Coin Combinations (Permutations vs Combinations) ===\n\n";
    
    // Example: coins = {2, 3, 5}, sum = 9
    vector<int> coins = {2, 3, 5};
    int sum = 9;
    
    cout << "Coins: {2, 3, 5}, Sum: 9\n\n";
    cout << "Permutations (order matters):     " << coinCombPermutations(coins, sum) << "\n";
    cout << "Combinations (order doesn't matter): " << coinCombCombinations(coins, sum) << "\n\n";
    
    // Interactive input
    int n, m;
    cout << "Enter n (number of coins) and sum: ";
    cin >> n >> m;
    
    coins.resize(n);
    cout << "Enter " << n << " coin values: ";
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }
    
    cout << "\nPermutations: " << coinCombPermutations(coins, m) << "\n";
    cout << "Combinations: " << coinCombCombinations(coins, m) << "\n";
    
    return 0;
}

/*
================================================================================
QUICK REFERENCE: Loop Order
================================================================================

┌─────────────────────────────────────────────────────────────────────────────┐
│  COINS FIRST, AMOUNT SECOND → COMBINATIONS (order doesn't matter)          │
│  for (coin : coins)                                                         │
│      for (amount = coin to sum)                                             │
│                                                                             │
│  AMOUNT FIRST, COINS SECOND → PERMUTATIONS (order matters)                 │
│  for (amount = 1 to sum)                                                    │
│      for (coin : coins)                                                     │
└─────────────────────────────────────────────────────────────────────────────┘

Example: coins = {2,3,5}, sum = 9
    Permutations: 8 ways  (LeetCode 377)
    Combinations: 3 ways  (LeetCode 518)

================================================================================
*/
