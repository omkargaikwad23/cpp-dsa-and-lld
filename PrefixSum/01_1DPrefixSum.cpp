/*
================================================================================
                    PREFIX SUM - 1D PROBLEMS
================================================================================

Basic 1D prefix sum pattern for range sum queries.
Time: O(n) build, O(1) query | Space: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Range Sum Query - Immutable (LeetCode 303)
─────────────────────────────────────────────────────
Answer multiple range sum queries efficiently.

Time: O(n) build, O(1) query | Space: O(n)
*/
class NumArray {
private:
    vector<int> prefix;
    
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};



/*
PROBLEM 3: Find Pivot Index (LeetCode 724)
──────────────────────────────────────────
Find index where left sum equals right sum.

Input: nums = [1,7,3,6,5,6]
Output: 3 (left sum = 1+7+3 = 11, right sum = 5+6 = 11)

Time: O(n) | Space: O(1)
*/
int pivotIndex(vector<int>& nums) {
    int totalSum = 0, leftSum = 0;
    for (int num : nums) totalSum += num;
    
    for (int i = 0; i < nums.size(); i++) {
        // Right sum = totalSum - leftSum - nums[i]
        if (leftSum == totalSum - leftSum - nums[i]) {
            return i;
        }
        leftSum += nums[i];
    }
    
    return -1;
}


/*
PROBLEM 4: Product of Array Except Self (LeetCode 238) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────
Return array where output[i] = product of all elements except nums[i].
NO DIVISION allowed!

Input: nums = [1,2,3,4]
Output: [24,12,8,6]

Approach: Left prefix product * Right suffix product

Time: O(n) | Space: O(1) excluding output
*/
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);
    
    // Left products
    int leftProduct = 1;
    for (int i = 0; i < n; i++) {
        result[i] = leftProduct;
        leftProduct *= nums[i];
    }
    
    // Right products (multiply in-place)
    int rightProduct = 1;
    for (int i = n - 1; i >= 0; i--) {
        result[i] *= rightProduct;
        rightProduct *= nums[i];
    }
    
    return result;
}


/*
PROBLEM 5: Find the Middle Index in Array (LeetCode 1991)
─────────────────────────────────────────────────────────
Find leftmost index where sum of elements to the left equals right.

Same as Pivot Index but returns leftmost.

Time: O(n) | Space: O(1)
*/
int findMiddleIndex(vector<int>& nums) {
    return pivotIndex(nums);  // Same logic
}


/*
PROBLEM 6: Minimum Value to Get Positive Step by Step Sum (LeetCode 1413)
─────────────────────────────────────────────────────────────────────────
Find min start value so running sum is always >= 1.

Input: nums = [-3,2,-3,4,2]
Output: 5

Time: O(n) | Space: O(1)
*/
int minStartValue(vector<int>& nums) {
    int minPrefix = 0, prefixSum = 0;
    
    for (int num : nums) {
        prefixSum += num;
        minPrefix = min(minPrefix, prefixSum);
    }
    
    // Start value must make minimum prefix sum >= 1
    return 1 - minPrefix;
}


/*
PROBLEM 7: Number of Ways to Split Array (LeetCode 2270)
────────────────────────────────────────────────────────
Count valid splits where left sum >= right sum.

Time: O(n) | Space: O(1)
*/
int waysToSplitArray(vector<int>& nums) {
    long long totalSum = 0, leftSum = 0;
    for (int num : nums) totalSum += num;
    
    int count = 0;
    for (int i = 0; i < nums.size() - 1; i++) {
        leftSum += nums[i];
        if (leftSum >= totalSum - leftSum) {
            count++;
        }
    }
    
    return count;
}


/*
PROBLEM 8: Sum of All Odd Length Subarrays (LeetCode 1588)
──────────────────────────────────────────────────────────
Sum of all subarrays with odd length.

Input: arr = [1,4,2,5,3]
Output: 58

Approach: Count contribution of each element.

Time: O(n) | Space: O(1)
*/
int sumOddLengthSubarrays(vector<int>& arr) {
    int n = arr.size(), sum = 0;
    
    for (int i = 0; i < n; i++) {
        // Element at index i appears in subarrays starting from [0..i] and ending at [i..n-1]
        int leftCount = i + 1;
        int rightCount = n - i;
        int totalSubarrays = leftCount * rightCount;
        
        // Odd length subarrays = (total + 1) / 2
        int oddSubarrays = (totalSubarrays + 1) / 2;
        sum += arr[i] * oddSubarrays;
    }
    
    return sum;
}


/*
PROBLEM 9: Contiguous Array (LeetCode 525)
──────────────────────────────────────────
Find max length subarray with equal 0s and 1s.

Approach: Treat 0 as -1, find longest subarray with sum 0.

Time: O(n) | Space: O(n)
*/
int findMaxLength(vector<int>& nums) {
    unordered_map<int, int> prefixIndex;
    prefixIndex[0] = -1;  // Base case
    
    int maxLen = 0, prefixSum = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        prefixSum += (nums[i] == 0) ? -1 : 1;
        
        if (prefixIndex.count(prefixSum)) {
            maxLen = max(maxLen, i - prefixIndex[prefixSum]);
        } else {
            prefixIndex[prefixSum] = i;
        }
    }
    
    return maxLen;
}


/*
PROBLEM 10: Subarray Sum Divisible by K (LeetCode 974)
──────────────────────────────────────────────────────
Count subarrays with sum divisible by k.

Key: (prefix[j] - prefix[i]) % k == 0
     ⟹ prefix[j] % k == prefix[i] % k

Time: O(n) | Space: O(k)
*/
int subarraysDivByK(vector<int>& nums, int k) {
    unordered_map<int, int> remainderCount;
    remainderCount[0] = 1;
    
    int count = 0, prefixSum = 0;
    
    for (int num : nums) {
        prefixSum += num;
        int remainder = ((prefixSum % k) + k) % k;  // Handle negative
        
        count += remainderCount[remainder];
        remainderCount[remainder]++;
    }
    
    return count;
}


/*
PROBLEM 11: Make Sum Divisible by P (LeetCode 1590)
───────────────────────────────────────────────────
Remove shortest subarray to make total sum divisible by p.

Time: O(n) | Space: O(n)
*/
int minSubarray(vector<int>& nums, int p) {
    long long totalSum = 0;
    for (int num : nums) totalSum += num;
    
    int target = totalSum % p;
    if (target == 0) return 0;
    
    unordered_map<int, int> prefixIndex;
    prefixIndex[0] = -1;
    
    int minLen = nums.size();
    long long prefixSum = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        prefixSum += nums[i];
        int remainder = prefixSum % p;
        
        // We need (prefixSum - needed) % p == target
        int needed = ((remainder - target) % p + p) % p;
        
        if (prefixIndex.count(needed)) {
            minLen = min(minLen, i - prefixIndex[needed]);
        }
        
        prefixIndex[remainder] = i;
    }
    
    return minLen < nums.size() ? minLen : -1;
}


/*
PROBLEM 12: Range Sum Query - Mutable (LeetCode 307)
────────────────────────────────────────────────────
Support point update and range sum query.

Note: For frequent updates, use Segment Tree or BIT instead.
Here's a simple approach for sparse updates.
*/
class NumArrayMutable {
private:
    vector<int> nums;
    vector<int> prefix;
    
    void buildPrefix() {
        int n = nums.size();
        prefix.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
    }
    
public:
    NumArrayMutable(vector<int>& nums) : nums(nums) {
        buildPrefix();
    }
    
    void update(int index, int val) {
        int diff = val - nums[index];
        nums[index] = val;
        for (int i = index + 1; i < prefix.size(); i++) {
            prefix[i] += diff;
        }
    }
    
    int sumRange(int left, int right) {
        return prefix[right + 1] - prefix[left];
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== 1D Prefix Sum ===\n\n";
    
    // Range Sum Query
    vector<int> nums1 = {-2, 0, 3, -5, 2, -1};
    NumArray na(nums1);
    cout << "1. Sum [0,2] = " << na.sumRange(0, 2) << "\n";
    cout << "   Sum [2,5] = " << na.sumRange(2, 5) << "\n";
    
    // Pivot Index
    vector<int> nums2 = {1, 7, 3, 6, 5, 6};
    cout << "3. Pivot index: " << pivotIndex(nums2) << "\n";
    
    // Product Except Self
    vector<int> nums3 = {1, 2, 3, 4};
    auto products = productExceptSelf(nums3);
    cout << "4. Product except self: ";
    for (int p : products) cout << p << " ";
    cout << "\n";
    
    // Contiguous Array
    vector<int> nums4 = {0, 1, 0};
    cout << "9. Max length (equal 0s and 1s): " << findMaxLength(nums4) << "\n";
    
    // Subarray Divisible by K
    vector<int> nums5 = {4, 5, 0, -2, -3, 1};
    cout << "10. Subarrays divisible by 5: " << subarraysDivByK(nums5, 5) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Pattern                       | Key Insight                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Range sum query               | prefix[r+1] - prefix[l]                        |
| Pivot/Middle index            | leftSum == totalSum - leftSum - nums[i]        |
| Product except self           | leftProduct * rightProduct (no division)       |
| Equal 0s and 1s               | Treat 0 as -1, find sum = 0 subarray           |
| Divisible by K                | Same remainder → sum divisible by K            |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

