#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

/*
 * COIN CHANGE - Minimum Coins Problem
 * ===================================
 * 
 * Problem: Return the fewest number of coins needed to make up the amount.
 * You have infinite number of each kind of coin.
 * 
 * Example:
 * Input: coins = [1, 2, 5], amount = 11
 * Output: 3
 * Explanation: 11 = 5 + 5 + 1 (3 coins)
 * 
 * Approach:
 * - Bottom-up (Tabulation): Build solution from 0 to amount
 * - Top-down (Memoization): Recursive with memoization
 * 
 * Time Complexity: O(amount * coins.size())
 * Space Complexity: O(amount)
 */

// Bottom-up approach (Tabulation)
int coinChangeBottomUp(vector<int>& coins, int amount) {
    // dp[i] = minimum coins needed to make amount i
    vector<int> dp(amount + 1, INT_MAX - 1);
    dp[0] = 0;  // Base case: 0 coins needed for amount 0
    
    // For each amount from 1 to target amount
    for (int i = 1; i <= amount; i++) {
        // Try each coin
        for (int j = 0; j < coins.size(); j++) {
            if (i - coins[j] >= 0) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1); // taking the coin: dp[i - coins[j]] + 1
            }
        }
    }
    
    return (dp[amount] == INT_MAX - 1) ? -1 : dp[amount];
}

// Top-down approach (Memoization)
int minCoins(const vector<int>& coins, int amount, map<int, int>& memo) {
    // Base cases
    if (amount < 0) return -1;  // Invalid amount
    if (amount == 0) return 0;   // No coins needed
    
    // Check memoization
    if (memo.count(amount) != 0)
        return memo[amount];
    
    int minValue = INT_MAX; // initialize the minimum value to the maximum integer value
    
    // Try each coin
    for (const auto& coin : coins) {
        int count = minCoins(coins, amount - coin, memo);
        if (count != -1) {
            minValue = min(minValue, count + 1);
        }
    }
    
    // Store result in memo
    return memo[amount] = (minValue == INT_MAX) ? -1 : minValue;
}

int coinChangeTopDown(vector<int>& coins, int amount) {
    map<int, int> memo;
    return minCoins(coins, amount, memo);
}

int main() {
    // Example: coins = [1, 2, 5], amount = 11
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    
    cout << "Coins: [1, 2, 5], Amount: 11" << endl;
    cout << "Bottom-up result: " << coinChangeBottomUp(coins, amount) << endl;
    cout << "Top-down result: " << coinChangeTopDown(coins, amount) << endl;
    cout << "Expected: 3 (5 + 5 + 1)" << endl;
    
    return 0;
}