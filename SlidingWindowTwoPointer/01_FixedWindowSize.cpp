/*
================================================================================
                    FIXED SIZE SLIDING WINDOW PATTERNS
================================================================================

Window size is constant (given as K in problem).

Key Template:
- Add element at position i
- Remove element at position i - k (when i >= k)
- Process result when window is complete (when i >= k - 1)

Time: O(n) | Space: O(1) or O(k)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Maximum Sum of Subarray of Size K
─────────────────────────────────────────────
Find the maximum sum of any contiguous subarray of size k.

Input: arr = [2, 1, 5, 1, 3, 2], k = 3
Output: 9 (subarray [5, 1, 3])

Time: O(n) | Space: O(1)
*/
int maxSumSubarrayOfSizeK(vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return -1;
    
    int windowSum = 0, maxSum = INT_MIN;
    
    for (int i = 0; i < n; i++) {
        windowSum += arr[i];          // Add incoming element
        
        if (i >= k - 1) {             // Window is complete
            maxSum = max(maxSum, windowSum);
            windowSum -= arr[i - k + 1];  // Remove outgoing element
        }
    }
    return maxSum;
}


/*
PROBLEM 2: First Negative in Every Window of Size K
────────────────────────────────────────────────────
Print the first negative number in every window of size k.
If no negative exists, print 0.

Input: arr = [12, -1, -7, 8, -15, 30, 16, 28], k = 3
Output: [-1, -1, -7, -15, -15, 0]

Approach: Use deque to store indices of negative numbers

Time: O(n) | Space: O(k)
*/
vector<int> firstNegativeInWindow(vector<int>& arr, int k) {
    int n = arr.size();
    deque<int> negatives;  // Store indices of negative numbers
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        // Add current element's index if negative
        if (arr[i] < 0) {
            negatives.push_back(i);
        }
        
        // Remove elements outside window
        while (!negatives.empty() && negatives.front() <= i - k) {
            negatives.pop_front();
        }
        
        // Window is complete
        if (i >= k - 1) {
            if (negatives.empty()) {
                result.push_back(0);
            } else {
                result.push_back(arr[negatives.front()]);
            }
        }
    }
    return result;
}


/*
PROBLEM 3: Count Distinct Elements in Every Window of Size K
─────────────────────────────────────────────────────────────
Count the number of distinct elements in every window of size k.

Input: arr = [1, 2, 1, 3, 4, 2, 3], k = 4
Output: [3, 4, 4, 3]
Explanation: 
  Window [1,2,1,3] → 3 distinct (1, 2, 3)
  Window [2,1,3,4] → 4 distinct (1, 2, 3, 4)
  ...

Time: O(n) | Space: O(k)
*/
vector<int> countDistinctInWindow(vector<int>& arr, int k) {
    int n = arr.size();
    unordered_map<int, int> freq;  // Element -> frequency
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        // Add incoming element
        freq[arr[i]]++;
        
        // Remove outgoing element
        if (i >= k) {
            freq[arr[i - k]]--;
            if (freq[arr[i - k]] == 0) {
                freq.erase(arr[i - k]);
            }
        }
        
        // Window is complete
        if (i >= k - 1) {
            result.push_back(freq.size());
        }
    }
    return result;
}


/*
PROBLEM 4: Maximum of All Subarrays of Size K (Sliding Window Maximum)
──────────────────────────────────────────────────────────────────────
Find maximum element in every window of size k.

Input: arr = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
Output: [3, 3, 5, 5, 6, 7]

Approach: Use monotonic decreasing deque (stores indices)
- Front of deque is always the maximum
- Remove elements smaller than current (they can never be max)

Time: O(n) | Space: O(k)
*/
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n = nums.size();
    deque<int> dq;  // Monotonic decreasing (stores indices)
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        // Remove elements outside the current window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements (they can never be maximum)
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        // Window is complete
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    return result;
}

// Alternative using multiset (O(n log k))
vector<int> maxSlidingWindowMultiset(vector<int>& nums, int k) {
    multiset<int> window;
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        window.insert(nums[i]);
        
        if (i >= k) {
            window.erase(window.find(nums[i - k]));
        }
        
        if (i >= k - 1) {
            result.push_back(*window.rbegin());  // Maximum element
        }
    }
    return result;
}


/*
PROBLEM 5: Find All Anagrams in a String (LeetCode 438)
───────────────────────────────────────────────────────
Given strings s and p, find all start indices of p's anagrams in s.

Input: s = "cbaebabacd", p = "abc"
Output: [0, 6]
Explanation: 
  "cba" at index 0 is anagram of "abc"
  "bac" at index 6 is anagram of "abc"

Time: O(n) | Space: O(1) - only 26 characters
*/
vector<int> findAnagrams(string s, string p) {
    int n = s.size(), k = p.size();
    if (n < k) return {};
    
    vector<int> pCount(26, 0), windowCount(26, 0);
    for (char c : p) pCount[c - 'a']++;
    
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        // Add incoming character
        windowCount[s[i] - 'a']++;
        
        // Remove outgoing character
        if (i >= k) {
            windowCount[s[i - k] - 'a']--;
        }
        
        // Window is complete, check if anagram
        if (i >= k - 1 && windowCount == pCount) {
            result.push_back(i - k + 1);
        }
    }
    return result;
}


/*
PROBLEM 6: Permutation in String (LeetCode 567)
───────────────────────────────────────────────
Check if s2 contains a permutation of s1.

Input: s1 = "ab", s2 = "eidbaooo"
Output: true (s2 contains "ba" which is permutation of "ab")

Time: O(n) | Space: O(1)
*/
bool checkInclusion(string s1, string s2) {
    int k = s1.size(), n = s2.size();
    if (n < k) return false;
    
    vector<int> count1(26, 0), count2(26, 0);
    for (char c : s1) count1[c - 'a']++;
    
    for (int i = 0; i < n; i++) {
        count2[s2[i] - 'a']++;
        
        if (i >= k) {
            count2[s2[i - k] - 'a']--;
        }
        
        if (i >= k - 1 && count1 == count2) {
            return true;
        }
    }
    return false;
}


/*
PROBLEM 7: Subarray Product Less Than K - Count (LeetCode 713)
──────────────────────────────────────────────────────────────
Count subarrays where product of all elements < k.

Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Subarrays: [10], [5], [2], [6], [10,5], [5,2], [2,6], [5,2,6]

Note: This uses VARIABLE window but included here as it counts subarrays

Time: O(n) | Space: O(1)
*/
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    if (k <= 1) return 0;
    
    int product = 1, count = 0, left = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        product *= nums[right];
        
        // Shrink window while product >= k
        while (product >= k) {
            product /= nums[left];
            left++;
        }
        
        // All subarrays ending at right with start >= left are valid
        count += right - left + 1;
    }
    return count;
}


/*
PROBLEM 8: Average of All Subarrays of Size K
─────────────────────────────────────────────
Calculate average of every contiguous subarray of size k.

Input: arr = [1, 3, 2, 6, -1, 4, 1, 8, 2], k = 5
Output: [2.2, 2.8, 2.4, 3.6, 2.8]

Time: O(n) | Space: O(1)
*/
vector<double> findAverages(vector<int>& arr, int k) {
    int n = arr.size();
    vector<double> result;
    double windowSum = 0;
    
    for (int i = 0; i < n; i++) {
        windowSum += arr[i];
        
        if (i >= k - 1) {
            result.push_back(windowSum / k);
            windowSum -= arr[i - k + 1];
        }
    }
    return result;
}


/*
PROBLEM 9: Contains Duplicate II (LeetCode 219)
───────────────────────────────────────────────
Check if array contains duplicates within distance k.

Input: nums = [1,2,3,1], k = 3
Output: true (nums[0] == nums[3], and 3 - 0 <= 3)

Time: O(n) | Space: O(k)
*/
bool containsNearbyDuplicate(vector<int>& nums, int k) {
    unordered_set<int> window;
    
    for (int i = 0; i < nums.size(); i++) {
        if (window.count(nums[i])) {
            return true;
        }
        
        window.insert(nums[i]);
        
        if (window.size() > k) {
            window.erase(nums[i - k]);
        }
    }
    return false;
}


/*
PROBLEM 10: Minimum Difference Between Largest and Smallest in Three Moves
──────────────────────────────────────────────────────────────────────────
You can change at most 3 elements to any value.
Find minimum difference between max and min after changes.

Input: nums = [5,3,2,4]
Output: 0 (change 3 elements to make all same)

Approach: Sort, then find min difference in sliding window of size n-3

Time: O(n log n) | Space: O(1)
*/
int minDifference(vector<int>& nums) {
    int n = nums.size();
    if (n <= 4) return 0;
    
    sort(nums.begin(), nums.end());
    
    int result = INT_MAX;
    // Try removing 0,1,2,3 from left and 3,2,1,0 from right
    for (int i = 0; i <= 3; i++) {
        result = min(result, nums[n - 1 - (3 - i)] - nums[i]);
    }
    return result;
}


// ============================================================================
// MAIN - Demo all functions
// ============================================================================

int main() {
    cout << "=== Fixed Size Sliding Window Patterns ===\n\n";
    
    // 1. Max Sum Subarray of Size K
    vector<int> arr1 = {2, 1, 5, 1, 3, 2};
    cout << "1. Max Sum (k=3): " << maxSumSubarrayOfSizeK(arr1, 3) << "\n";
    
    // 2. First Negative in Window
    vector<int> arr2 = {12, -1, -7, 8, -15, 30, 16, 28};
    vector<int> neg = firstNegativeInWindow(arr2, 3);
    cout << "2. First Negative (k=3): ";
    for (int x : neg) cout << x << " ";
    cout << "\n";
    
    // 3. Count Distinct
    vector<int> arr3 = {1, 2, 1, 3, 4, 2, 3};
    vector<int> distinct = countDistinctInWindow(arr3, 4);
    cout << "3. Count Distinct (k=4): ";
    for (int x : distinct) cout << x << " ";
    cout << "\n";
    
    // 4. Max Sliding Window
    vector<int> arr4 = {1, 3, -1, -3, 5, 3, 6, 7};
    vector<int> maxWin = maxSlidingWindow(arr4, 3);
    cout << "4. Max Sliding Window (k=3): ";
    for (int x : maxWin) cout << x << " ";
    cout << "\n";
    
    // 5. Find Anagrams
    vector<int> anagrams = findAnagrams("cbaebabacd", "abc");
    cout << "5. Anagram Indices: ";
    for (int x : anagrams) cout << x << " ";
    cout << "\n";
    
    // 6. Permutation in String
    cout << "6. Contains Permutation: " << (checkInclusion("ab", "eidbaooo") ? "true" : "false") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+──────────────────────────────────+─────────────────+────────────────────────+
| Problem                          | Data Structure  | Key Insight            |
+──────────────────────────────────+─────────────────+────────────────────────+
| Max/Min Sum of Size K            | Variable        | Add/remove at edges    |
| First Negative in Window         | Deque           | Store negative indices |
| Count Distinct in Window         | HashMap         | Track frequencies      |
| Max of Sliding Window            | Monotonic Deque | Keep potential maxes   |
| Find Anagrams                    | Array[26]       | Compare freq arrays    |
| Permutation in String            | Array[26]       | Same as anagrams       |
| Contains Duplicate II            | HashSet         | Window as set          |
+──────────────────────────────────+─────────────────+────────────────────────+

================================================================================
*/

