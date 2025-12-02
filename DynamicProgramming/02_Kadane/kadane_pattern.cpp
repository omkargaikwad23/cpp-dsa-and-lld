/*
================================================================================
                    PATTERN 2: KADANE'S ALGORITHM
================================================================================

When to use:
- Optimize a contiguous subarray within a 1D array
- Find maximum/minimum sum subarray
- Track running sum with reset condition

LeetCode Problems:
- 53. Maximum Subarray
- 918. Maximum Sum Circular Subarray
- 152. Maximum Product Subarray

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Maximum Subarray (LeetCode 53) ⭐ CLASSIC
───────────────────────────────────────────────────
Find contiguous subarray with largest sum.

dp[i] = max(nums[i], dp[i-1] + nums[i])
(either start new subarray at i, or extend previous)

Time: O(n) | Space: O(1)
*/
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0];
    int currSum = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        currSum = max(nums[i], currSum + nums[i]);
        maxSum = max(maxSum, currSum);
    }
    
    return maxSum;
}

// Alternative formulation
int maxSubArray2(vector<int>& nums) {
    int maxSum = nums[0];
    int currSum = 0;
    
    for (int num : nums) {
        currSum = max(0, currSum) + num;  // Reset if negative
        maxSum = max(maxSum, currSum);
    }
    
    return maxSum;
}


/*
PROBLEM 2: Maximum Sum Circular Subarray (LeetCode 918)
───────────────────────────────────────────────────────
Array is circular. Max subarray can wrap around.

Two cases:
1. Max subarray is in middle (normal Kadane)
2. Max subarray wraps around = totalSum - minSubarray

Time: O(n) | Space: O(1)
*/
int maxSubarraySumCircular(vector<int>& nums) {
    int totalSum = 0;
    int maxSum = nums[0], currMax = 0;
    int minSum = nums[0], currMin = 0;
    
    for (int num : nums) {
        // Normal Kadane for max
        currMax = max(currMax, 0) + num;
        maxSum = max(maxSum, currMax);
        
        // Kadane for min
        currMin = min(currMin, 0) + num;
        minSum = min(minSum, currMin);
        
        totalSum += num;
    }
    
    // If all negative, minSum == totalSum, return maxSum
    if (totalSum == minSum) return maxSum;
    
    return max(maxSum, totalSum - minSum);
}


/*
PROBLEM 3: Maximum Product Subarray (LeetCode 152)
──────────────────────────────────────────────────
Find contiguous subarray with largest product.

Track both max and min (negative * negative = positive)

Time: O(n) | Space: O(1)
*/
int maxProduct(vector<int>& nums) {
    int maxProd = nums[0];
    int currMax = nums[0], currMin = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] < 0) swap(currMax, currMin);  // Swap on negative
        
        currMax = max(nums[i], currMax * nums[i]);
        currMin = min(nums[i], currMin * nums[i]);
        
        maxProd = max(maxProd, currMax);
    }
    
    return maxProd;
}


/*
PROBLEM 4: Maximum Absolute Sum of Any Subarray (LeetCode 1749)
──────────────────────────────────────────────────────────────
Find max(|subarray sum|).

max(maxSubarraySum, |minSubarraySum|)

Time: O(n) | Space: O(1)
*/
int maxAbsoluteSum(vector<int>& nums) {
    int maxSum = 0, minSum = 0;
    int currMax = 0, currMin = 0;
    
    for (int num : nums) {
        currMax = max(0, currMax) + num;
        currMin = min(0, currMin) + num;
        maxSum = max(maxSum, currMax);
        minSum = min(minSum, currMin);
    }
    
    return max(maxSum, -minSum);
}


/*
PROBLEM 5: Best Time to Buy and Sell Stock (LeetCode 121)
─────────────────────────────────────────────────────────
Buy once, sell once. Maximize profit.

Track minimum price seen so far, max profit at each day.

Time: O(n) | Space: O(1)
*/
int maxProfit(vector<int>& prices) {
    int minPrice = prices[0];
    int maxProfit = 0;
    
    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    
    return maxProfit;
}


/*
PROBLEM 6: Maximum Subarray Sum With One Deletion (LeetCode 1186)
────────────────────────────────────────────────────────────────
Can delete at most one element. Find max subarray sum.

Track two states:
- maxEndHere: max sum ending here (no deletion)
- maxEndHereWithDel: max sum ending here (one deletion used)

Time: O(n) | Space: O(1)
*/
int maximumSum(vector<int>& arr) {
    int maxEndHere = arr[0];
    int maxEndHereWithDel = 0;  // Can't delete first element and have non-empty
    int maxSum = arr[0];
    
    for (int i = 1; i < arr.size(); i++) {
        // With deletion: either delete current, or extend previous deletion
        maxEndHereWithDel = max(maxEndHere, maxEndHereWithDel + arr[i]);
        
        // No deletion: start fresh or extend
        maxEndHere = max(arr[i], maxEndHere + arr[i]);
        
        maxSum = max(maxSum, max(maxEndHere, maxEndHereWithDel));
    }
    
    return maxSum;
}


/*
PROBLEM 7: Longest Turbulent Subarray (LeetCode 978)
────────────────────────────────────────────────────
Turbulent: comparison signs alternate.
a[0] < a[1] > a[2] < a[3]... or a[0] > a[1] < a[2] > a[3]...

Time: O(n) | Space: O(1)
*/
int maxTurbulenceSize(vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return n;
    
    int maxLen = 1;
    int inc = 1, dec = 1;  // Length ending with increase/decrease
    
    for (int i = 1; i < n; i++) {
        if (arr[i] > arr[i-1]) {
            inc = dec + 1;
            dec = 1;
        } else if (arr[i] < arr[i-1]) {
            dec = inc + 1;
            inc = 1;
        } else {
            inc = dec = 1;
        }
        maxLen = max(maxLen, max(inc, dec));
    }
    
    return maxLen;
}


/*
PROBLEM 8: Maximum Sum of Two Non-Overlapping Subarrays (LeetCode 1031)
───────────────────────────────────────────────────────────────────────
Find max sum of subarrays of length firstLen and secondLen.

Use prefix sum + track best subarray on left.

Time: O(n) | Space: O(n)
*/
int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
    int n = nums.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    
    auto solve = [&](int L, int M) {
        int maxL = 0, result = 0;
        for (int i = L + M; i <= n; i++) {
            maxL = max(maxL, prefix[i - M] - prefix[i - M - L]);
            result = max(result, maxL + prefix[i] - prefix[i - M]);
        }
        return result;
    };
    
    return max(solve(firstLen, secondLen), solve(secondLen, firstLen));
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Kadane's Algorithm ===\n\n";
    
    // Maximum Subarray
    vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "1. Max subarray sum: " << maxSubArray(nums1) << "\n";
    
    // Circular
    vector<int> nums2 = {5, -3, 5};
    cout << "2. Max circular subarray: " << maxSubarraySumCircular(nums2) << "\n";
    
    // Product
    vector<int> nums3 = {2, 3, -2, 4};
    cout << "3. Max product subarray: " << maxProduct(nums3) << "\n";
    
    // Absolute Sum
    vector<int> nums4 = {1, -3, 2, 3, -4};
    cout << "4. Max absolute sum: " << maxAbsoluteSum(nums4) << "\n";
    
    // Stock
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "5. Max stock profit: " << maxProfit(prices) << "\n";
    
    // With One Deletion
    vector<int> nums5 = {1, -2, 0, 3};
    cout << "6. Max sum with one deletion: " << maximumSum(nums5) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

KADANE'S TEMPLATE:
    currSum = 0 (or nums[0])
    maxSum = INT_MIN (or nums[0])
    for each num:
        currSum = max(num, currSum + num)  // Start fresh or extend
        maxSum = max(maxSum, currSum)
    return maxSum

+───────────────────────────────+────────────────────────────────────────────────+
| Variant                       | Key Modification                               |
+───────────────────────────────+────────────────────────────────────────────────+
| Basic Max Subarray            | currSum = max(num, currSum + num)              |
| Circular                      | max(maxSum, totalSum - minSum)                 |
| Product                       | Track both currMax and currMin                 |
| With Deletion                 | Track two states: with/without deletion        |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

