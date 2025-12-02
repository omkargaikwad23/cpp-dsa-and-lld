/*
================================================================================
                    PREFIX SUM + HASHMAP
================================================================================

Powerful combination for subarray problems:
- Subarray sum equals K
- Count subarrays with specific sum
- Longest subarray with target sum

Key insight: If prefix[j] - prefix[i] = K, then subarray [i+1, j] has sum K.
Store prefix sums in hashmap for O(1) lookup.

Time: O(n) | Space: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Subarray Sum Equals K (LeetCode 560) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────
Count subarrays with sum equal to k.

Input: nums = [1,1,1], k = 2
Output: 2 ([1,1] appears twice)

Time: O(n) | Space: O(n)
*/
int subarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;  // Empty prefix
    
    int count = 0, prefixSum = 0;
    
    for (int num : nums) {
        prefixSum += num;
        
        // If (prefixSum - k) exists, we found subarrays with sum k
        if (prefixCount.count(prefixSum - k)) {
            count += prefixCount[prefixSum - k];
        }
        
        prefixCount[prefixSum]++;
    }
    
    return count;
}


/*
PROBLEM 2: Continuous Subarray Sum (LeetCode 523)
─────────────────────────────────────────────────
Check if subarray of length >= 2 has sum divisible by k.

Key: (prefix[j] - prefix[i]) % k == 0 ⟹ prefix[j] % k == prefix[i] % k

Time: O(n) | Space: O(min(n, k))
*/
bool checkSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> remainderIndex;
    remainderIndex[0] = -1;  // Index before array starts
    
    int prefixSum = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        prefixSum += nums[i];
        int remainder = prefixSum % k;
        
        if (remainderIndex.count(remainder)) {
            // Subarray length must be >= 2
            if (i - remainderIndex[remainder] >= 2) {
                return true;
            }
        } else {
            remainderIndex[remainder] = i;  // Store first occurrence
        }
    }
    
    return false;
}


/*
PROBLEM 3: Subarray Sums Divisible by K (LeetCode 974)
──────────────────────────────────────────────────────
Count subarrays with sum divisible by k.

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
PROBLEM 4: Longest Subarray with Sum K (Not on LeetCode)
────────────────────────────────────────────────────────
Find longest subarray with sum exactly k.

Note: For positive numbers only, sliding window works.
      For any integers, use hashmap.

Time: O(n) | Space: O(n)
*/
int longestSubarraySumK(vector<int>& nums, int k) {
    unordered_map<int, int> prefixIndex;
    prefixIndex[0] = -1;  // Before first element
    
    int maxLen = 0, prefixSum = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        prefixSum += nums[i];
        
        if (prefixIndex.count(prefixSum - k)) {
            maxLen = max(maxLen, i - prefixIndex[prefixSum - k]);
        }
        
        // Store first occurrence only (for longest)
        if (!prefixIndex.count(prefixSum)) {
            prefixIndex[prefixSum] = i;
        }
    }
    
    return maxLen;
}


/*
PROBLEM 5: Binary Subarrays With Sum (LeetCode 930)
───────────────────────────────────────────────────
Count subarrays with sum equal to goal (binary array).

Input: nums = [1,0,1,0,1], goal = 2
Output: 4

Time: O(n) | Space: O(n)
*/
int numSubarraysWithSum(vector<int>& nums, int goal) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;
    
    int count = 0, prefixSum = 0;
    
    for (int num : nums) {
        prefixSum += num;
        count += prefixCount[prefixSum - goal];
        prefixCount[prefixSum]++;
    }
    
    return count;
}


/*
PROBLEM 6: Count Number of Nice Subarrays (LeetCode 1248)
─────────────────────────────────────────────────────────
Count subarrays with exactly k odd numbers.

Convert: odd → 1, even → 0, then find subarrays with sum = k.

Time: O(n) | Space: O(n)
*/
int numberOfSubarrays(vector<int>& nums, int k) {
    unordered_map<int, int> prefixCount;
    prefixCount[0] = 1;
    
    int count = 0, oddCount = 0;
    
    for (int num : nums) {
        oddCount += (num % 2);  // 1 if odd, 0 if even
        count += prefixCount[oddCount - k];
        prefixCount[oddCount]++;
    }
    
    return count;
}


/*
PROBLEM 7: Longest Well-Performing Interval (LeetCode 1124)
───────────────────────────────────────────────────────────
Find longest interval where tiring days > non-tiring days.
Tiring day: hours > 8.

Convert: >8 → +1, <=8 → -1, find longest subarray with sum > 0.

Time: O(n) | Space: O(n)
*/
int longestWPI(vector<int>& hours) {
    unordered_map<int, int> prefixIndex;
    int maxLen = 0, prefixSum = 0;
    
    for (int i = 0; i < hours.size(); i++) {
        prefixSum += (hours[i] > 8) ? 1 : -1;
        
        if (prefixSum > 0) {
            // Entire array [0, i] is valid
            maxLen = i + 1;
        } else {
            // Find earliest j where prefix[j] = prefixSum - 1
            if (prefixIndex.count(prefixSum - 1)) {
                maxLen = max(maxLen, i - prefixIndex[prefixSum - 1]);
            }
        }
        
        // Store first occurrence
        if (!prefixIndex.count(prefixSum)) {
            prefixIndex[prefixSum] = i;
        }
    }
    
    return maxLen;
}


/*
PROBLEM 8: Contiguous Array (LeetCode 525)
──────────────────────────────────────────
Longest subarray with equal 0s and 1s.

Convert: 0 → -1, find longest subarray with sum = 0.

Time: O(n) | Space: O(n)
*/
int findMaxLength(vector<int>& nums) {
    unordered_map<int, int> prefixIndex;
    prefixIndex[0] = -1;
    
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
PROBLEM 9: Number of Subarrays with Bounded Maximum (LeetCode 795)
──────────────────────────────────────────────────────────────────
Count subarrays where max element is in [left, right].

Approach: count(max <= right) - count(max <= left - 1)

Time: O(n) | Space: O(1)
*/
int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
    auto countAtMost = [&](int bound) {
        int count = 0, current = 0;
        for (int num : nums) {
            current = (num <= bound) ? current + 1 : 0;
            count += current;
        }
        return count;
    };
    
    return countAtMost(right) - countAtMost(left - 1);
}


/*
PROBLEM 10: Subarrays with K Different Integers (LeetCode 992)
──────────────────────────────────────────────────────────────
Count subarrays with exactly k distinct integers.

Approach: atMost(k) - atMost(k-1)

Time: O(n) | Space: O(n)
*/
int subarraysWithKDistinct(vector<int>& nums, int k) {
    auto atMost = [&](int k) {
        if (k < 0) return 0;
        
        unordered_map<int, int> freq;
        int count = 0, left = 0;
        
        for (int right = 0; right < nums.size(); right++) {
            if (freq[nums[right]] == 0) k--;
            freq[nums[right]]++;
            
            while (k < 0) {
                freq[nums[left]]--;
                if (freq[nums[left]] == 0) k++;
                left++;
            }
            
            count += right - left + 1;
        }
        
        return count;
    };
    
    return atMost(k) - atMost(k - 1);
}


/*
PROBLEM 11: Count Subarrays Where Max Element Appears K Times (LeetCode 2962)
─────────────────────────────────────────────────────────────────────────────
Count subarrays where maximum element appears at least k times.

Time: O(n) | Space: O(1)
*/
long long countSubarrays(vector<int>& nums, int k) {
    int maxVal = *max_element(nums.begin(), nums.end());
    long long count = 0;
    int maxCount = 0, left = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == maxVal) maxCount++;
        
        while (maxCount >= k) {
            count += nums.size() - right;  // All extensions are valid
            if (nums[left] == maxVal) maxCount--;
            left++;
        }
    }
    
    return count;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Prefix Sum + HashMap ===\n\n";
    
    // Subarray Sum Equals K
    vector<int> nums1 = {1, 1, 1};
    cout << "1. Subarrays with sum 2: " << subarraySum(nums1, 2) << "\n";
    
    // Continuous Subarray Sum
    vector<int> nums2 = {23, 2, 4, 6, 7};
    cout << "2. Has subarray divisible by 6: " 
         << (checkSubarraySum(nums2, 6) ? "Yes" : "No") << "\n";
    
    // Subarrays Divisible by K
    vector<int> nums3 = {4, 5, 0, -2, -3, 1};
    cout << "3. Subarrays divisible by 5: " << subarraysDivByK(nums3, 5) << "\n";
    
    // Longest with sum K
    vector<int> nums4 = {1, -1, 5, -2, 3};
    cout << "4. Longest subarray sum 3: " << longestSubarraySumK(nums4, 3) << "\n";
    
    // Contiguous Array (equal 0s and 1s)
    vector<int> nums5 = {0, 1, 0};
    cout << "8. Longest equal 0s and 1s: " << findMaxLength(nums5) << "\n";
    
    // K Different Integers
    vector<int> nums6 = {1, 2, 1, 2, 3};
    cout << "10. Subarrays with 2 distinct: " << subarraysWithKDistinct(nums6, 2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

PREFIX + HASHMAP PATTERN:
─────────────────────────
map[0] = 1 (or map[0] = -1 for index)
for each element:
    prefixSum += element
    check if (prefixSum - target) in map
    update map

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Transformation                                 |
+───────────────────────────────+────────────────────────────────────────────────+
| Sum = K                       | Direct prefix sum                              |
| Divisible by K                | Store prefix % k                               |
| Equal 0s and 1s               | 0 → -1, sum = 0                                |
| K odd numbers                 | odd → 1, even → 0                              |
| Exactly K distinct            | atMost(k) - atMost(k-1)                        |
| More tiring than non-tiring   | >8 → +1, <=8 → -1, sum > 0                     |
+───────────────────────────────+────────────────────────────────────────────────+

COUNT vs LONGEST:
- Count: map stores frequency
- Longest: map stores first occurrence index

================================================================================
*/

