/*
================================================================================
                    ADVANCED SLIDING WINDOW & TWO POINTER
================================================================================

Complex problems combining multiple techniques or requiring special handling.
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Sliding Window Median (LeetCode 480)
───────────────────────────────────────────────
Find median of each window of size k.

Approach: Two heaps (max-heap for lower half, min-heap for upper half)
Or use multiset with two iterators

Time: O(n log k) | Space: O(k)
*/
vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    multiset<int> lo, hi;  // lo: max elements, hi: min elements
    vector<double> result;
    
    auto balance = [&]() {
        while (lo.size() > hi.size() + 1) {
            hi.insert(*lo.rbegin());
            lo.erase(prev(lo.end()));
        }
        while (hi.size() > lo.size()) {
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }
    };
    
    for (int i = 0; i < nums.size(); i++) {
        // Add to appropriate set
        if (lo.empty() || nums[i] <= *lo.rbegin()) {
            lo.insert(nums[i]);
        } else {
            hi.insert(nums[i]);
        }
        
        // Remove element leaving window
        if (i >= k) {
            int toRemove = nums[i - k];
            if (lo.count(toRemove)) {
                lo.erase(lo.find(toRemove));
            } else {
                hi.erase(hi.find(toRemove));
            }
        }
        
        balance();
        
        // Get median
        if (i >= k - 1) {
            if (k % 2 == 0) {
                result.push_back(((double)*lo.rbegin() + *hi.begin()) / 2);
            } else {
                result.push_back(*lo.rbegin());
            }
        }
    }
    return result;
}


/*
PROBLEM 2: Minimum Number of Swaps to Group All 1's Together (LeetCode 1151)
────────────────────────────────────────────────────────────────────────────
Find minimum swaps to group all 1's together.

Input: data = [1,0,1,0,1]
Output: 1 (swap data[1] with data[4])

Approach: Fixed window of size = count of 1s. Find window with max 1s.

Time: O(n) | Space: O(1)
*/
int minSwaps(vector<int>& data) {
    int totalOnes = 0;
    for (int x : data) totalOnes += x;
    
    if (totalOnes <= 1) return 0;
    
    int windowOnes = 0, maxOnes = 0;
    int k = totalOnes;
    
    for (int i = 0; i < data.size(); i++) {
        windowOnes += data[i];
        
        if (i >= k) {
            windowOnes -= data[i - k];
        }
        
        maxOnes = max(maxOnes, windowOnes);
    }
    
    return totalOnes - maxOnes;  // Swaps needed = zeros in best window
}


/*
PROBLEM 3: Count Subarrays With Fixed Bounds (LeetCode 2444)
────────────────────────────────────────────────────────────
Count subarrays where min = minK and max = maxK.

Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
Output: 2

Time: O(n) | Space: O(1)
*/
long long countSubarrays(vector<int>& nums, int minK, int maxK) {
    long long count = 0;
    int minPos = -1, maxPos = -1, leftBound = -1;
    
    for (int i = 0; i < nums.size(); i++) {
        // Out of range - reset
        if (nums[i] < minK || nums[i] > maxK) {
            leftBound = i;
        }
        
        // Track last positions of minK and maxK
        if (nums[i] == minK) minPos = i;
        if (nums[i] == maxK) maxPos = i;
        
        // Add valid subarrays ending at i
        count += max(0, min(minPos, maxPos) - leftBound);
    }
    return count;
}


/*
PROBLEM 4: Number of Substrings Containing All Three Characters (LeetCode 1358)
───────────────────────────────────────────────────────────────────────────────
Count substrings containing at least one 'a', 'b', and 'c'.

Input: s = "abcabc"
Output: 10

Time: O(n) | Space: O(1)
*/
int numberOfSubstrings(string s) {
    int n = s.size(), count = 0;
    vector<int> lastSeen(3, -1);  // Last seen index of a, b, c
    
    for (int i = 0; i < n; i++) {
        lastSeen[s[i] - 'a'] = i;
        
        // If all three seen, count substrings ending at i
        if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1) {
            // Any starting point from 0 to min(lastSeen) works
            count += min({lastSeen[0], lastSeen[1], lastSeen[2]}) + 1;
        }
    }
    return count;
}


/*
PROBLEM 5: Max Sum of Two Non-Overlapping Subarrays (LeetCode 1031)
───────────────────────────────────────────────────────────────────
Find max sum of one subarray of size L and one of size M (non-overlapping).

Input: nums = [0,6,5,2,2,5,1,9,4], L = 1, M = 2
Output: 20 (nums[8] + nums[5,6])

Time: O(n) | Space: O(n)
*/
int maxSumTwoNoOverlap(vector<int>& nums, int L, int M) {
    int n = nums.size();
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    
    auto solve = [&](int first, int second) {
        int maxFirst = 0, result = 0;
        
        for (int i = first + second; i <= n; i++) {
            // Max sum of 'first' length subarray ending before current 'second' window
            maxFirst = max(maxFirst, prefix[i - second] - prefix[i - second - first]);
            // Current 'second' window sum
            int secondSum = prefix[i] - prefix[i - second];
            result = max(result, maxFirst + secondSum);
        }
        return result;
    };
    
    return max(solve(L, M), solve(M, L));
}


/*
PROBLEM 6: Binary Subarrays With Sum (LeetCode 930)
───────────────────────────────────────────────────
Count subarrays with sum equal to goal.

Input: nums = [1,0,1,0,1], goal = 2
Output: 4

Time: O(n) | Space: O(1)
*/
int numSubarraysWithSum(vector<int>& nums, int goal) {
    auto atMost = [&](int g) {
        if (g < 0) return 0;
        int left = 0, sum = 0, count = 0;
        for (int right = 0; right < nums.size(); right++) {
            sum += nums[right];
            while (sum > g) {
                sum -= nums[left++];
            }
            count += right - left + 1;
        }
        return count;
    };
    
    return atMost(goal) - atMost(goal - 1);
}


/*
PROBLEM 7: Count Complete Subarrays (LeetCode 2799)
───────────────────────────────────────────────────
Subarray is complete if it contains all distinct elements of the array.

Input: nums = [1,3,1,2,2]
Output: 4

Time: O(n) | Space: O(n)
*/
int countCompleteSubarrays(vector<int>& nums) {
    unordered_set<int> all(nums.begin(), nums.end());
    int target = all.size();
    
    unordered_map<int, int> freq;
    int left = 0, count = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        freq[nums[right]]++;
        
        while (freq.size() == target) {
            count += nums.size() - right;  // All extensions are valid
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }
    }
    return count;
}


/*
PROBLEM 8: Longest Turbulent Subarray (LeetCode 978)
────────────────────────────────────────────────────
Find longest subarray where elements alternate between increasing/decreasing.

Input: arr = [9,4,2,10,7,8,8,1,9]
Output: 5 ([4,2,10,7,8])

Time: O(n) | Space: O(1)
*/
int maxTurbulenceSize(vector<int>& arr) {
    int n = arr.size();
    if (n == 1) return 1;
    
    int maxLen = 1, left = 0;
    
    for (int right = 1; right < n; right++) {
        int cmp = (arr[right] > arr[right - 1]) - (arr[right] < arr[right - 1]);
        
        if (cmp == 0) {
            left = right;
        } else if (right > 1) {
            int prevCmp = (arr[right - 1] > arr[right - 2]) - (arr[right - 1] < arr[right - 2]);
            if (cmp == prevCmp) {
                left = right - 1;
            }
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 9: Take K of Each Character From Left and Right (LeetCode 2516)
───────────────────────────────────────────────────────────────────────
Find minimum minutes to take at least k of each 'a', 'b', 'c'.

Input: s = "aabaaaacaabc", k = 2
Output: 8

Approach: Maximize middle part that can be skipped

Time: O(n) | Space: O(1)
*/
int takeCharacters(string s, int k) {
    int n = s.size();
    vector<int> total(3, 0);
    for (char c : s) total[c - 'a']++;
    
    // Check if possible
    for (int i = 0; i < 3; i++) {
        if (total[i] < k) return -1;
    }
    
    // Find longest middle substring we can skip
    vector<int> skip(3, 0);
    int maxSkip = 0, left = 0;
    
    for (int right = 0; right < n; right++) {
        skip[s[right] - 'a']++;
        
        // Shrink if skipping too much of any character
        while (skip[0] > total[0] - k || skip[1] > total[1] - k || skip[2] > total[2] - k) {
            skip[s[left] - 'a']--;
            left++;
        }
        
        maxSkip = max(maxSkip, right - left + 1);
    }
    
    return n - maxSkip;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Advanced Sliding Window Problems ===\n\n";
    
    // 1. Sliding Window Median
    vector<int> arr1 = {1,3,-1,-3,5,3,6,7};
    vector<double> medians = medianSlidingWindow(arr1, 3);
    cout << "1. Medians: ";
    for (double m : medians) cout << m << " ";
    cout << "\n";
    
    // 2. Min Swaps
    vector<int> arr2 = {1,0,1,0,1};
    cout << "2. Min swaps to group 1s: " << minSwaps(arr2) << "\n";
    
    // 4. Substrings with all three
    cout << "4. Substrings with a,b,c: " << numberOfSubstrings("abcabc") << "\n";
    
    // 6. Binary Subarrays with Sum
    vector<int> arr6 = {1,0,1,0,1};
    cout << "6. Subarrays with sum 2: " << numSubarraysWithSum(arr6, 2) << "\n";
    
    return 0;
}

/*
================================================================================
                              KEY INSIGHTS
================================================================================

1. For "exactly k" → Use atMost(k) - atMost(k-1)

2. For non-overlapping subarrays → Track best seen so far + current window

3. For complete/containing all → Count extensions from valid window

4. Sliding window median → Two heaps or multiset with balance

5. When counting subarrays ending at right → count += (valid starting positions)
================================================================================
*/

