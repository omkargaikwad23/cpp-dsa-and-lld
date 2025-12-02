/*
================================================================================
                    PATTERN 1: FIBONACCI SEQUENCE
================================================================================

When to use:
- Solution depends on solutions of smaller instances
- Clear recursive relationship: F(n) = F(n-1) + F(n-2)
- Linear dependencies between states

LeetCode Problems:
- 70. Climbing Stairs
- 509. Fibonacci Number
- 746. Min Cost Climbing Stairs
- 1137. N-th Tribonacci Number

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Fibonacci Number (LeetCode 509)
──────────────────────────────────────────
F(0) = 0, F(1) = 1
F(n) = F(n-1) + F(n-2) for n > 1

Time: O(n) | Space: O(1)
*/
int fib(int n) {
    if (n <= 1) return n;
    int prev2 = 0, prev1 = 1;
    for (int i = 2; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


/*
PROBLEM 2: Climbing Stairs (LeetCode 70)
────────────────────────────────────────
Can climb 1 or 2 steps. Count ways to reach top.

dp[i] = dp[i-1] + dp[i-2]
(ways to reach step i = ways from step i-1 + ways from step i-2)

Time: O(n) | Space: O(1)
*/
int climbStairs(int n) {
    if (n <= 2) return n;
    int prev2 = 1, prev1 = 2;
    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


/*
PROBLEM 3: Min Cost Climbing Stairs (LeetCode 746)
──────────────────────────────────────────────────
Pay cost[i] to climb from step i. Can climb 1 or 2 steps.
Start from step 0 or 1.

dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2])

Time: O(n) | Space: O(1)
*/
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    int prev2 = 0, prev1 = 0;  // Cost to reach step 0 and 1 is 0 (we start there)
    
    for (int i = 2; i <= n; i++) {
        int curr = min(prev1 + cost[i-1], prev2 + cost[i-2]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


/*
PROBLEM 4: N-th Tribonacci Number (LeetCode 1137)
─────────────────────────────────────────────────
T(0) = 0, T(1) = 1, T(2) = 1
T(n) = T(n-1) + T(n-2) + T(n-3)

Time: O(n) | Space: O(1)
*/
int tribonacci(int n) {
    if (n == 0) return 0;
    if (n <= 2) return 1;
    
    int prev3 = 0, prev2 = 1, prev1 = 1;
    for (int i = 3; i <= n; i++) {
        int curr = prev1 + prev2 + prev3;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


/*
PROBLEM 5: House Robber (LeetCode 198)
──────────────────────────────────────
Can't rob adjacent houses. Maximize money.

dp[i] = max(dp[i-1], dp[i-2] + nums[i])
(either skip current house, or rob current + best from 2 houses ago)

Time: O(n) | Space: O(1)
*/
int rob(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    
    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);
    
    for (int i = 2; i < n; i++) {
        int curr = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


/*
PROBLEM 6: House Robber II (LeetCode 213)
─────────────────────────────────────────
Houses arranged in circle. First and last are adjacent.

Solution: max(rob(0 to n-2), rob(1 to n-1))

Time: O(n) | Space: O(1)
*/
int robHelper(vector<int>& nums, int start, int end) {
    int prev2 = 0, prev1 = 0;
    for (int i = start; i <= end; i++) {
        int curr = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

int robII(vector<int>& nums) {
    int n = nums.size();
    if (n == 1) return nums[0];
    return max(robHelper(nums, 0, n-2), robHelper(nums, 1, n-1));
}


/*
PROBLEM 7: Delete and Earn (LeetCode 740)
─────────────────────────────────────────
Delete num[i], earn num[i] points, but delete all num[i]-1 and num[i]+1.

Convert to House Robber: group by value, can't take adjacent values.

Time: O(n + max) | Space: O(max)
*/
int deleteAndEarn(vector<int>& nums) {
    int maxVal = *max_element(nums.begin(), nums.end());
    vector<int> earn(maxVal + 1, 0);
    
    for (int num : nums) {
        earn[num] += num;
    }
    
    // House robber on earn array
    int prev2 = 0, prev1 = earn[1];
    for (int i = 2; i <= maxVal; i++) {
        int curr = max(prev1, prev2 + earn[i]);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}


/*
PROBLEM 8: Count Ways to Build Good Strings (LeetCode 2466)
───────────────────────────────────────────────────────────
Build strings using 'zero' 0s or 'one' 1s at each step.
Count strings of length [low, high].

dp[i] = dp[i - zero] + dp[i - one]

Time: O(high) | Space: O(high)
*/
int countGoodStrings(int low, int high, int zero, int one) {
    const int MOD = 1e9 + 7;
    vector<long long> dp(high + 1, 0);
    dp[0] = 1;
    
    long long count = 0;
    for (int i = 1; i <= high; i++) {
        if (i >= zero) dp[i] = (dp[i] + dp[i - zero]) % MOD;
        if (i >= one) dp[i] = (dp[i] + dp[i - one]) % MOD;
        if (i >= low) count = (count + dp[i]) % MOD;
    }
    
    return count;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Fibonacci Pattern ===\n\n";
    
    // Fibonacci
    cout << "1. Fibonacci(10): " << fib(10) << "\n";
    
    // Climbing Stairs
    cout << "2. Climbing 5 stairs: " << climbStairs(5) << " ways\n";
    
    // Min Cost Climbing
    vector<int> cost = {10, 15, 20};
    cout << "3. Min cost climbing: " << minCostClimbingStairs(cost) << "\n";
    
    // Tribonacci
    cout << "4. Tribonacci(10): " << tribonacci(10) << "\n";
    
    // House Robber
    vector<int> houses = {2, 7, 9, 3, 1};
    cout << "5. House Robber: " << rob(houses) << "\n";
    
    // House Robber II
    vector<int> houses2 = {2, 3, 2};
    cout << "6. House Robber II: " << robII(houses2) << "\n";
    
    // Delete and Earn
    vector<int> nums = {3, 4, 2};
    cout << "7. Delete and Earn: " << deleteAndEarn(nums) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

KEY INSIGHT: Current state depends only on previous 1-2 states.

TEMPLATE:
    prev2 = base_case_0
    prev1 = base_case_1
    for i from 2 to n:
        curr = f(prev1, prev2)
        prev2 = prev1
        prev1 = curr
    return prev1

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Recurrence                                     |
+───────────────────────────────+────────────────────────────────────────────────+
| Fibonacci                     | dp[i] = dp[i-1] + dp[i-2]                      |
| Climbing Stairs               | dp[i] = dp[i-1] + dp[i-2]                      |
| Min Cost Climbing             | dp[i] = min(dp[i-1]+cost[i-1], dp[i-2]+cost[i-2]) |
| House Robber                  | dp[i] = max(dp[i-1], dp[i-2] + nums[i])        |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

