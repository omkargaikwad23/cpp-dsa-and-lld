/*
================================================================================
            CAN SUM - Unbounded Subset Sum (elements can be reused)
================================================================================

Problem: Given target sum and array of numbers, can we reach the target 
         by adding numbers from array? (Each number can be used multiple times)

Example: canSum(7, [2, 3]) → true  (2 + 2 + 3 = 7)
         canSum(7, [2, 4]) → false (no combination works)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 1: Memoization (Top-Down)                                          │
│ Time: O(target * n)  |  Space: O(target)                                    │
└─────────────────────────────────────────────────────────────────────────────┘
*/

bool canSum(int target, vector<int>& nums, unordered_map<int, bool>& memo) {
    if (memo.count(target)) return memo[target];
    if (target == 0) return true;
    if (target < 0) return false;
    
    for (int num : nums) {
        if (canSum(target - num, nums, memo)) {
            return memo[target] = true;
        }
    }
    
    return memo[target] = false;
}

// Wrapper for cleaner API
bool canSumMemo(int target, vector<int>& nums) {
    unordered_map<int, bool> memo;
    return canSum(target, nums, memo);
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 2: Tabulation (Bottom-Up)                                          │
│ Time: O(target * n)  |  Space: O(target)                                    │
└─────────────────────────────────────────────────────────────────────────────┘
*/

bool canSumTabu(int target, vector<int>& nums) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;  // Base case: sum of 0 is always achievable
    
    for (int i = 0; i <= target; i++) {
        if (dp[i]) {
            for (int num : nums) {
                if (i + num <= target) {
                    dp[i + num] = true;
                }
            }
        }
    }
    
    return dp[target];
}


int main() {
    // Test cases
    vector<int> nums1 = {2, 3};
    vector<int> nums2 = {2, 4};
    vector<int> nums3 = {2, 3, 5};
    
    cout << "=== Can Sum (Unbounded) ===\n\n";
    
    cout << "canSum(7, [2,3]) = " << (canSumMemo(7, nums1) ? "YES" : "NO") << "\n";
    cout << "canSum(7, [2,4]) = " << (canSumMemo(7, nums2) ? "YES" : "NO") << "\n";
    cout << "canSum(8, [2,3,5]) = " << (canSumTabu(8, nums3) ? "YES" : "NO") << "\n";
    cout << "canSum(300, [7,14]) = " << (canSumTabu(300, nums1) ? "YES" : "NO") << "\n";
    
    return 0;
}

/*
================================================================================
                            COMPARISON
================================================================================

┌─────────────────┬──────────────────────┬──────────────────────┐
│ Approach        │ Time                 │ Space                │
├─────────────────┼──────────────────────┼──────────────────────┤
│ Brute Force     │ O(n^target)          │ O(target) stack      │
│ Memoization     │ O(target × n)        │ O(target)            │
│ Tabulation      │ O(target × n)        │ O(target)            │
└─────────────────┴──────────────────────┴──────────────────────┘

================================================================================
*/
