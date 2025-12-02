/*
================================================================================
                    PATTERN 20: STATE MACHINE DP
================================================================================

When to use:
- Problem has clear states and transitions
- Making decisions that affect future states
- Stock buy/sell problems with cooldown or transaction limits

LeetCode Problems:
- 121. Best Time to Buy and Sell Stock
- 122. Best Time to Buy and Sell Stock II
- 123. Best Time to Buy and Sell Stock III
- 309. Best Time to Buy and Sell Stock with Cooldown
- 188. Best Time to Buy and Sell Stock IV

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Best Time to Buy and Sell Stock (LeetCode 121)
─────────────────────────────────────────────────────────
One transaction allowed.

Track min price seen, max profit possible.

Time: O(n) | Space: O(1)
*/
int maxProfit1(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    
    return maxProfit;
}


/*
PROBLEM 2: Best Time to Buy and Sell Stock II (LeetCode 122)
────────────────────────────────────────────────────────────
Unlimited transactions.

States: holding stock, not holding
hold[i] = max profit on day i while holding
noHold[i] = max profit on day i while not holding

Time: O(n) | Space: O(1)
*/
int maxProfit2(vector<int>& prices) {
    int hold = INT_MIN;  // Max profit while holding
    int noHold = 0;      // Max profit while not holding
    
    for (int price : prices) {
        int prevHold = hold;
        hold = max(hold, noHold - price);      // Buy or keep
        noHold = max(noHold, prevHold + price); // Sell or keep
    }
    
    return noHold;
}


/*
PROBLEM 3: Best Time to Buy and Sell Stock III (LeetCode 123) ⭐
───────────────────────────────────────────────────────────────
At most 2 transactions.

States: buy1, sell1, buy2, sell2

Time: O(n) | Space: O(1)
*/
int maxProfit3(vector<int>& prices) {
    int buy1 = INT_MIN, sell1 = 0;
    int buy2 = INT_MIN, sell2 = 0;
    
    for (int price : prices) {
        buy1 = max(buy1, -price);           // First buy
        sell1 = max(sell1, buy1 + price);   // First sell
        buy2 = max(buy2, sell1 - price);    // Second buy
        sell2 = max(sell2, buy2 + price);   // Second sell
    }
    
    return sell2;
}


/*
PROBLEM 4: Best Time to Buy and Sell Stock IV (LeetCode 188) ⭐
──────────────────────────────────────────────────────────────
At most k transactions.

States: buy[j] = max profit after j-th buy
        sell[j] = max profit after j-th sell

Time: O(n*k) | Space: O(k)
*/
int maxProfit4(int k, vector<int>& prices) {
    int n = prices.size();
    if (n == 0 || k == 0) return 0;
    
    // If k >= n/2, equivalent to unlimited transactions
    if (k >= n / 2) {
        int profit = 0;
        for (int i = 1; i < n; i++) {
            profit += max(0, prices[i] - prices[i-1]);
        }
        return profit;
    }
    
    vector<int> buy(k + 1, INT_MIN);
    vector<int> sell(k + 1, 0);
    
    for (int price : prices) {
        for (int j = 1; j <= k; j++) {
            buy[j] = max(buy[j], sell[j-1] - price);
            sell[j] = max(sell[j], buy[j] + price);
        }
    }
    
    return sell[k];
}


/*
PROBLEM 5: Best Time with Cooldown (LeetCode 309) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────────────
After selling, must wait one day before buying again.

States: hold, sold (just sold), rest (not holding, not in cooldown)

hold[i] = max(hold[i-1], rest[i-1] - price)
sold[i] = hold[i-1] + price
rest[i] = max(rest[i-1], sold[i-1])

Time: O(n) | Space: O(1)
*/
int maxProfitWithCooldown(vector<int>& prices) {
    int hold = INT_MIN;
    int sold = 0;
    int rest = 0;
    
    for (int price : prices) {
        int prevSold = sold;
        sold = hold + price;
        hold = max(hold, rest - price);
        rest = max(rest, prevSold);
    }
    
    return max(sold, rest);
}


/*
PROBLEM 6: Best Time with Transaction Fee (LeetCode 714)
────────────────────────────────────────────────────────
Pay fee for each transaction (buy-sell pair).

Time: O(n) | Space: O(1)
*/
int maxProfitWithFee(vector<int>& prices, int fee) {
    int hold = -prices[0];
    int noHold = 0;
    
    for (int i = 1; i < prices.size(); i++) {
        hold = max(hold, noHold - prices[i]);
        noHold = max(noHold, hold + prices[i] - fee);
    }
    
    return noHold;
}


/*
PROBLEM 7: House Robber (State Machine View) (LeetCode 198)
───────────────────────────────────────────────────────────
States: robbed last house, didn't rob last house

Time: O(n) | Space: O(1)
*/
int rob(vector<int>& nums) {
    int robbed = 0;    // Max if we robbed last house
    int notRobbed = 0; // Max if we didn't rob last house
    
    for (int num : nums) {
        int newRobbed = notRobbed + num;  // Rob current
        notRobbed = max(robbed, notRobbed); // Skip current
        robbed = newRobbed;
    }
    
    return max(robbed, notRobbed);
}


/*
PROBLEM 8: Paint House (LeetCode 256)
─────────────────────────────────────
Paint n houses with 3 colors, adjacent houses can't have same color.

States: last house painted red/blue/green

Time: O(n) | Space: O(1)
*/
int minCostPaintHouse(vector<vector<int>>& costs) {
    if (costs.empty()) return 0;
    
    int red = costs[0][0];
    int blue = costs[0][1];
    int green = costs[0][2];
    
    for (int i = 1; i < costs.size(); i++) {
        int newRed = costs[i][0] + min(blue, green);
        int newBlue = costs[i][1] + min(red, green);
        int newGreen = costs[i][2] + min(red, blue);
        
        red = newRed;
        blue = newBlue;
        green = newGreen;
    }
    
    return min({red, blue, green});
}


/*
PROBLEM 9: Paint House II (LeetCode 265)
────────────────────────────────────────
n houses, k colors. Optimize to O(nk) using min and second min.

Time: O(n*k) | Space: O(1)
*/
int minCostPaintHouseII(vector<vector<int>>& costs) {
    if (costs.empty()) return 0;
    
    int n = costs.size(), k = costs[0].size();
    int min1 = 0, min2 = 0, minIdx = -1;
    
    for (int i = 0; i < n; i++) {
        int newMin1 = INT_MAX, newMin2 = INT_MAX, newMinIdx = -1;
        
        for (int j = 0; j < k; j++) {
            int cost = costs[i][j] + (j != minIdx ? min1 : min2);
            
            if (cost < newMin1) {
                newMin2 = newMin1;
                newMin1 = cost;
                newMinIdx = j;
            } else if (cost < newMin2) {
                newMin2 = cost;
            }
        }
        
        min1 = newMin1;
        min2 = newMin2;
        minIdx = newMinIdx;
    }
    
    return min1;
}


/*
PROBLEM 10: Domino and Tromino Tiling (LeetCode 790)
────────────────────────────────────────────────────
Fill 2 x n board with dominoes and trominoes.

States based on how last column is filled.

Time: O(n) | Space: O(1)
*/
int numTilings(int n) {
    const int MOD = 1e9 + 7;
    if (n == 1) return 1;
    if (n == 2) return 2;
    
    // f[i] = ways to fully cover up to column i
    // p[i] = ways to cover with one cell protruding
    long long f1 = 1, f2 = 2;
    long long p1 = 0, p2 = 1;
    
    for (int i = 3; i <= n; i++) {
        long long newF = (f2 + f1 + 2 * p2) % MOD;
        long long newP = (p2 + f1) % MOD;
        
        f1 = f2;
        f2 = newF;
        p1 = p2;
        p2 = newP;
    }
    
    return f2;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== State Machine DP ===\n\n";
    
    vector<int> prices1 = {7, 1, 5, 3, 6, 4};
    cout << "1. One transaction: " << maxProfit1(prices1) << "\n";
    cout << "2. Unlimited: " << maxProfit2(prices1) << "\n";
    
    vector<int> prices2 = {3, 3, 5, 0, 0, 3, 1, 4};
    cout << "3. At most 2: " << maxProfit3(prices2) << "\n";
    cout << "4. At most k=2: " << maxProfit4(2, prices2) << "\n";
    
    vector<int> prices3 = {1, 2, 3, 0, 2};
    cout << "5. With cooldown: " << maxProfitWithCooldown(prices3) << "\n";
    
    vector<int> prices4 = {1, 3, 2, 8, 4, 9};
    cout << "6. With fee=2: " << maxProfitWithFee(prices4, 2) << "\n";
    
    cout << "10. Tiling 2x4: " << numTilings(4) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

STATE MACHINE TEMPLATE:
    Define states (e.g., holding/not holding, last action)
    For each day/item:
        Update each state based on transitions
    Return optimal final state

STOCK PROBLEMS:
+───────────────────────────────+────────────────────────────────────────────────+
| Variant                       | States                                         |
+───────────────────────────────+────────────────────────────────────────────────+
| One transaction               | Track min price                                |
| Unlimited                     | hold, noHold                                   |
| At most 2                     | buy1, sell1, buy2, sell2                       |
| At most k                     | buy[1..k], sell[1..k]                          |
| With cooldown                 | hold, sold, rest                               |
| With fee                      | hold, noHold (subtract fee on sell)            |
+───────────────────────────────+────────────────────────────────────────────────+

KEY: Model problem as states and transitions between states.

================================================================================
*/

