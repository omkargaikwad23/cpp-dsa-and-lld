/*
================================================================================
DICE COMBINATIONS (CSES / Similar to LeetCode 1155)
================================================================================

Problem: Count ways to make sum n by throwing a dice (faces 1-6).
         Order matters: 1+2 and 2+1 are different ways.

Example: n = 3
Ways: {1,1,1}, {1,2}, {2,1}, {3} → 4 ways

This is PERMUTATION counting (order matters) → Amount in outer loop!

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

/*
────────────────────────────────────────────────────────────────────────────────
APPROACH 1: Recursion + Memoization (Top-Down)
────────────────────────────────────────────────────────────────────────────────

State: dp[sum] = number of ways to reach this sum
Transition: Try each dice face (1-6), add ways from remaining sum

Time: O(n * 6) | Space: O(n)
*/
vector<long long> memo;

long long diceCombMemo(int n) {
    // Base cases
    if (n == 0) return 1;  // Found a valid way!
    if (n < 0) return 0;   // Overshot, invalid
    
    // Already computed?
    if (memo[n] != -1) return memo[n];
    
    // Try all dice faces (1 to 6)
    long long ways = 0;
    for (int face = 1; face <= 6; face++) {
        ways = (ways + diceCombMemo(n - face)) % MOD;
    }
    
    memo[n] = ways;
    return ways;
}

long long diceCombRecursive(int n) {
    memo.assign(n + 1, -1);
    return diceCombMemo(n);
}


/*
────────────────────────────────────────────────────────────────────────────────
APPROACH 2: Bottom-Up DP (Tabulation) ⭐ RECOMMENDED
────────────────────────────────────────────────────────────────────────────────

dp[i] = number of ways to make sum i
dp[i] = dp[i-1] + dp[i-2] + dp[i-3] + dp[i-4] + dp[i-5] + dp[i-6]

Note: This is like Fibonacci but with 6 previous states instead of 2!

Time: O(n * 6) | Space: O(n)
*/
long long diceCombTabulation(int n) {
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;  // Base: 1 way to make sum 0 (use nothing)
    
    // For each sum, try all dice faces
    // AMOUNT FIRST → counts PERMUTATIONS (order matters)
    for (int sum = 1; sum <= n; sum++) {
        for (int face = 1; face <= 6; face++) {
            if (face <= sum) {
                dp[sum] = (dp[sum] + dp[sum - face]) % MOD;
            }
        }
    }
    
    return dp[n];
}


/*
────────────────────────────────────────────────────────────────────────────────
WHY AMOUNT FIRST? (PERMUTATIONS vs COMBINATIONS)
────────────────────────────────────────────────────────────────────────────────

This problem wants PERMUTATIONS (1+2 ≠ 2+1), so we use:
    for (sum = 1 to n):          // Amount FIRST
        for (face = 1 to 6):     // Then dice faces
            dp[sum] += dp[sum - face]

If we wanted COMBINATIONS (1+2 = 2+1), we'd swap loops:
    for (face = 1 to 6):         // Dice FIRST
        for (sum = face to n):   // Then amounts
            dp[sum] += dp[sum - face]

────────────────────────────────────────────────────────────────────────────────
*/


int main() {
    cout << "=== Dice Combinations ===\n\n";
    
    vector<int> testCases = {1, 2, 3, 5, 10};
    // Expected: 1, 2, 4, 16, 492
    
    for (int n : testCases) {
        cout << "n = " << n << ":\n";
        cout << "  Recursive: " << diceCombRecursive(n) << "\n";
        cout << "  Tabulation: " << diceCombTabulation(n) << "\n\n";
    }
    
    // Interactive input
    int n;
    cout << "Enter n: ";
    cin >> n;
    cout << "Ways to make " << n << ": " << diceCombTabulation(n) << "\n";
    
    return 0;
}

/*
================================================================================
TEST CASES
================================================================================
n = 1  → 1   (just {1})
n = 2  → 2   ({1,1}, {2})
n = 3  → 4   ({1,1,1}, {1,2}, {2,1}, {3})
n = 5  → 16
n = 10 → 492

================================================================================
BUG IN ORIGINAL CODE
================================================================================
The original recursive solution had:
    for(int i=1; i<=n; i++)  // ❌ WRONG: should be i<=6 (dice faces)
        memo[n] += dice_comb(n-i);

Fixed version:
    for(int face=1; face<=6; face++)  // ✓ CORRECT: dice has faces 1-6
        ways += diceCombMemo(n - face);

================================================================================
*/
