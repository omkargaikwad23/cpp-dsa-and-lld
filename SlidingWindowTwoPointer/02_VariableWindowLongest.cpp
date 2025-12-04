/*
================================================================================
                VARIABLE SIZE SLIDING WINDOW - LONGEST/MAXIMUM
================================================================================

Find the LONGEST or MAXIMUM subarray/substring satisfying a condition.

Key Template (Expand then Shrink):
- Expand window by moving right pointer
- Shrink window when constraint is violated
- Update maximum after ensuring window is valid

Pattern:
  int left = 0, maxLen = 0;
  for (int right = 0; right < n; right++) {
      // Expand: add arr[right] to window state
      
      while ( window is INVALID ) {
          // Shrink: remove arr[left] from window state
          left++;
      }
      
      // Window is now valid, update answer
      maxLen = max(maxLen, right - left + 1);
  }

Time: O(n) | Space: O(1) or O(k) depending on problem

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Longest Substring Without Repeating Characters (LeetCode 3)
───────────────────────────────────────────────────────────────────────
Find length of longest substring without repeating characters.

Input: s = "abcabcbb"
Output: 3 ("abc")

Input: s = "bbbbb"
Output: 1 ("b")

Time: O(n) | Space: O(min(n, alphabet_size))
*/
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastIndex;  // char -> last seen index
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.size(); right++) {
        // If char seen before and inside current window, shrink
        if (lastIndex.count(s[right]) && lastIndex[s[right]] >= left) {
            left = lastIndex[s[right]] + 1;
        }
        
        lastIndex[s[right]] = right;
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}

// Alternative using set (more intuitive but slightly slower)
int lengthOfLongestSubstringSet(string s) {
    unordered_set<char> window;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.size(); right++) {
        // Shrink until no duplicate
        while (window.count(s[right])) {
            window.erase(s[left]);
            left++;
        }
        
        window.insert(s[right]);
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 2: Longest Substring with At Most K Distinct Characters (LeetCode 340)
──────────────────────────────────────────────────────────────────────────────
Find longest substring with at most k distinct characters.

Input: s = "eceba", k = 2
Output: 3 ("ece")

Input: s = "aa", k = 1
Output: 2 ("aa")

Time: O(n) | Space: O(k)
*/
int lengthOfLongestSubstringKDistinct(string s, int k) {
    unordered_map<char, int> freq;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < s.size(); right++) {
        freq[s[right]]++;
        
        // Shrink while more than k distinct characters
        while (freq.size() > k) {
            freq[s[left]]--;
            if (freq[s[left]] == 0) {
                freq.erase(s[left]);
            }
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 3: Longest Repeating Character Replacement (LeetCode 424)
─────────────────────────────────────────────────────────────────
You can replace at most k characters. Find longest substring with same letter.

Input: s = "AABABBA", k = 1
Output: 4 ("AABA" → replace B → "AAAA")

Key Insight: Valid window if (window_size - max_freq) <= k

Time: O(n) | Space: O(26) = O(1)
*/
int characterReplacement(string s, int k) {
    vector<int> count(26, 0);
    int left = 0, maxFreq = 0, maxLen = 0;
    
    for (int right = 0; right < s.size(); right++) {
        count[s[right] - 'A']++;
        maxFreq = max(maxFreq, count[s[right] - 'A']);
        
        // If we need to replace more than k chars, shrink
        // (right - left + 1) - maxFreq > k means too many chars to replace
        while ((right - left + 1) - maxFreq > k) {
            count[s[left] - 'A']--;
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 4: Max Consecutive Ones III (LeetCode 1004)
───────────────────────────────────────────────────
Given binary array, return max consecutive 1s if you can flip at most k 0s.

Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
Output: 6 ([1,1,1,0,0,1,1,1,1,1,1] after flipping)

Time: O(n) | Space: O(1)
*/
int longestOnes(vector<int>& nums, int k) {
    int left = 0, zeros = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) zeros++;
        
        // Shrink while too many zeros
        while (zeros > k) {
            if (nums[left] == 0) zeros--;
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 5: Fruit Into Baskets (LeetCode 904)
────────────────────────────────────────────
Collect maximum fruits with only 2 types of baskets.
(Same as: Longest subarray with at most 2 distinct elements)

Input: fruits = [1,2,1,2,3]
Output: 4 ([1,2,1,2])

Time: O(n) | Space: O(1) - at most 3 types in map
*/
int totalFruit(vector<int>& fruits) {
    unordered_map<int, int> basket;  // fruit type -> count
    int left = 0, maxFruits = 0;
    
    for (int right = 0; right < fruits.size(); right++) {
        basket[fruits[right]]++;
        
        // Shrink while more than 2 fruit types
        while (basket.size() > 2) {
            basket[fruits[left]]--;
            if (basket[fruits[left]] == 0) {
                basket.erase(fruits[left]);
            }
            left++;
        }
        
        maxFruits = max(maxFruits, right - left + 1);
    }
    return maxFruits;
}


/*
PROBLEM 6: Longest Subarray of 1's After Deleting One Element (LeetCode 1493)
─────────────────────────────────────────────────────────────────────────────
Delete exactly one element. Find longest subarray of 1's.

Input: nums = [1,1,0,1,1,1]
Output: 5 (delete 0 at index 2)

Similar to Max Consecutive Ones with k=1, but result is (maxLen - 1)

Time: O(n) | Space: O(1)
*/
int longestSubarray(vector<int>& nums) {
    int left = 0, zeros = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] == 0) zeros++;
        
        while (zeros > 1) {
            if (nums[left] == 0) zeros--;
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    // Must delete one element, so subtract 1
    return maxLen - 1;
}


/*
PROBLEM 7: Maximum Erasure Value (LeetCode 1695)
────────────────────────────────────────────────
Find maximum sum of subarray with all unique elements.

Input: nums = [4,2,4,5,6]
Output: 17 ([2,4,5,6])

Time: O(n) | Space: O(n)
*/
int maximumUniqueSubarray(vector<int>& nums) {
    unordered_set<int> seen;
    int left = 0, sum = 0, maxSum = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        while (seen.count(nums[right])) {
            seen.erase(nums[left]);
            sum -= nums[left];
            left++;
        }
        
        seen.insert(nums[right]);
        sum += nums[right];
        maxSum = max(maxSum, sum);
    }
    return maxSum;
}


/*
PROBLEM 8: Get Equal Substrings Within Budget (LeetCode 1208)
─────────────────────────────────────────────────────────────
Maximum length substring where cost to change s to t is <= maxCost.
Cost of changing s[i] to t[i] is |s[i] - t[i]|.

Input: s = "abcd", t = "bcdf", maxCost = 3
Output: 3 ("abc" → "bcd" costs 1+1+1 = 3)

Time: O(n) | Space: O(1)
*/
int equalSubstring(string s, string t, int maxCost) {
    int left = 0, cost = 0, maxLen = 0;
    
    for (int right = 0; right < s.size(); right++) {
        cost += abs(s[right] - t[right]);
        
        while (cost > maxCost) {
            cost -= abs(s[left] - t[left]);
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 9: Longest Subarray with Absolute Diff <= Limit (LeetCode 1438)
───────────────────────────────────────────────────────────────────────
Find longest subarray where abs(max - min) <= limit.

Input: nums = [8,2,4,7], limit = 4
Output: 2 ([2,4] or [4,7])

Approach: Use two deques to track max and min in window

Time: O(n) | Space: O(n)
*/
int longestSubarrayWithLimit(vector<int>& nums, int limit) {
    deque<int> maxQ, minQ;  // Monotonic deques
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        // Maintain monotonic decreasing for max
        while (!maxQ.empty() && nums[right] > nums[maxQ.back()]) {
            maxQ.pop_back();
        }
        maxQ.push_back(right);
        
        // Maintain monotonic increasing for min
        while (!minQ.empty() && nums[right] < nums[minQ.back()]) {
            minQ.pop_back();
        }
        minQ.push_back(right);
        
        // Shrink while difference exceeds limit
        while (nums[maxQ.front()] - nums[minQ.front()] > limit) {
            if (maxQ.front() == left) maxQ.pop_front();
            if (minQ.front() == left) minQ.pop_front();
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 10: Longest Nice Subarray (LeetCode 2401)
─────────────────────────────────────────────────
Find longest subarray where bitwise AND of every pair is 0.

Input: nums = [1,3,8,48,10]
Output: 3 ([3,8,48] - no two elements share a bit)

Approach: Track used bits with OR, shrink when AND with new element > 0

Time: O(n) | Space: O(1)
*/
int longestNiceSubarray(vector<int>& nums) {
    int left = 0, usedBits = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        // Shrink while current element shares bits with window
        while ((usedBits & nums[right]) != 0) {
            usedBits ^= nums[left];  // Remove left element's bits
            left++;
        }
        
        usedBits |= nums[right];  // Add current element's bits
        maxLen = max(maxLen, right - left + 1);
    }
    return maxLen;
}


/*
PROBLEM 11: Maximum Points You Can Obtain from Cards (LeetCode 1423)
────────────────────────────────────────────────────────────────────
Pick k cards from either end. Maximize sum.

Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12 (pick 1, 6, 5)

Approach: Minimize sum of (n-k) length window in middle

Time: O(n) | Space: O(1)
*/
int maxScore(vector<int>& cardPoints, int k) {
    int n = cardPoints.size();
    int windowSize = n - k;
    int total = 0, windowSum = 0, minWindowSum = INT_MAX;
    
    if (windowSize == 0) return total;
    
    // Find minimum window sum of size (n-k)
    for (int i = 0; i < n; i++) {
        total += cardPoints[i]; // total sum of all cards
        windowSum += cardPoints[i];
        
        if (i >= windowSize) {
            windowSum -= cardPoints[i - windowSize];
        }
        
        if (i >= windowSize - 1) {
            minWindowSum = min(minWindowSum, windowSum);
        }
    }
    
    return total - minWindowSum;
}


// ============================================================================
// MAIN - Demo all functions
// ============================================================================

int main() {
    cout << "=== Variable Window - Longest/Maximum ===\n\n";
    
    // 1. Longest Substring Without Repeating
    cout << "1. Longest without repeat 'abcabcbb': " 
         << lengthOfLongestSubstring("abcabcbb") << "\n";
    
    // 2. At Most K Distinct
    cout << "2. At most 2 distinct 'eceba': " 
         << lengthOfLongestSubstringKDistinct("eceba", 2) << "\n";
    
    // 3. Character Replacement
    cout << "3. Char replacement 'AABABBA', k=1: " 
         << characterReplacement("AABABBA", 1) << "\n";
    
    // 4. Max Consecutive Ones III
    vector<int> ones = {1,1,1,0,0,0,1,1,1,1,0};
    cout << "4. Max consecutive ones, k=2: " << longestOnes(ones, 2) << "\n";
    
    // 5. Fruit Into Baskets
    vector<int> fruits = {1,2,1,2,3};
    cout << "5. Fruit into baskets: " << totalFruit(fruits) << "\n";
    
    // 6. Longest Subarray After Deletion
    vector<int> del = {1,1,0,1,1,1};
    cout << "6. Longest after deleting one: " << longestSubarray(del) << "\n";
    
    // 7. Maximum Erasure Value
    vector<int> era = {4,2,4,5,6};
    cout << "7. Max unique subarray sum: " << maximumUniqueSubarray(era) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+────────────────────────────────────+──────────────────────────────────────────+
| Problem                            | Window Constraint                        |
+────────────────────────────────────+──────────────────────────────────────────+
| Longest Without Repeating          | No duplicate characters                  |
| At Most K Distinct                 | At most K unique characters              |
| Character Replacement              | (size - maxFreq) <= K                    |
| Max Consecutive Ones               | At most K zeros in window                |
| Fruit Into Baskets                 | At most 2 unique elements                |
| After Deleting One Element         | At most 1 zero in window                 |
| Maximum Erasure Value              | All unique elements + track sum          |
| Equal Substrings Within Budget     | Cost to transform <= budget              |
| Absolute Diff <= Limit             | max - min <= limit (use two deques)      |
+────────────────────────────────────+──────────────────────────────────────────+

KEY INSIGHT: For "longest" problems, expand first, then shrink when invalid.

================================================================================
*/

