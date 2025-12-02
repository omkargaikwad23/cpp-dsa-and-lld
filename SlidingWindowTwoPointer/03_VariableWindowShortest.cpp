/*
================================================================================
               VARIABLE SIZE SLIDING WINDOW - SHORTEST/MINIMUM
================================================================================

Find the SHORTEST or MINIMUM subarray/substring satisfying a condition.

Key Template (Shrink while Valid):
- Expand window by moving right pointer
- When constraint is satisfied, try to shrink
- Update minimum while window is still valid

Pattern:
  int left = 0, minLen = INT_MAX;
  for (int right = 0; right < n; right++) {
      // Expand: add arr[right] to window state
      
      while ( window is VALID/satisfies condition ) {
          // Update minimum answer
          minLen = min(minLen, right - left + 1);
          
          // Shrink: remove arr[left] from window state
          left++;
      }
  }

Difference from "Longest" problems:
- Longest: Shrink when INVALID
- Shortest: Shrink while VALID (to find minimum)

Time: O(n) | Space: O(1) or O(k)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Minimum Size Subarray Sum (LeetCode 209)
───────────────────────────────────────────────────
Find minimum length subarray with sum >= target.

Input: target = 7, nums = [2,3,1,2,4,3]
Output: 2 ([4,3])

Input: target = 4, nums = [1,4,4]
Output: 1 ([4])

Time: O(n) | Space: O(1)
*/
int minSubArrayLen(int target, vector<int>& nums) {
    int left = 0, sum = 0, minLen = INT_MAX;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        // Shrink while valid (sum >= target)
        while (sum >= target) {
            minLen = min(minLen, right - left + 1);
            sum -= nums[left];
            left++;
        }
    }
    
    return minLen == INT_MAX ? 0 : minLen;
}


/*
PROBLEM 2: Minimum Window Substring (LeetCode 76)
─────────────────────────────────────────────────
Find minimum window in s that contains all characters of t.

Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"

Key: Use two maps - required chars and window chars
Track how many required chars are satisfied

Time: O(n + m) | Space: O(m) where m = t.length()
*/
string minWindow(string s, string t) {
    if (t.empty() || s.length() < t.length()) return "";
    
    unordered_map<char, int> required, window;
    for (char c : t) required[c]++;
    
    int left = 0, minLen = INT_MAX, minStart = 0;
    int have = 0, need = required.size();  // Count unique chars satisfied
    
    for (int right = 0; right < s.size(); right++) {
        char c = s[right];
        window[c]++;
        
        // Check if this char is now satisfied
        if (required.count(c) && window[c] == required[c]) {
            have++;
        }
        
        // Shrink while we have all required chars
        while (have == need) {
            // Update minimum
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }
            
            // Remove left char from window
            char leftChar = s[left];
            window[leftChar]--;
            if (required.count(leftChar) && window[leftChar] < required[leftChar]) {
                have--;
            }
            left++;
        }
    }
    
    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}


/*
PROBLEM 3: Minimum Window Subsequence (LeetCode 727 - Premium)
──────────────────────────────────────────────────────────────
Find minimum window in s1 that contains s2 as subsequence.

Input: s1 = "abcdebdde", s2 = "bde"
Output: "bcde"

Approach: Two pointers, find subsequence then minimize

Time: O(n * m) | Space: O(1)
*/
string minWindowSubsequence(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    int minLen = INT_MAX, minStart = 0;
    
    int i = 0;  // s1 pointer
    while (i < n) {
        int j = 0;  // s2 pointer
        
        // Find subsequence going forward
        while (i < n) {
            if (s1[i] == s2[j]) j++;
            if (j == m) break;
            i++;
        }
        
        if (j < m) break;  // No more matches possible
        
        // i now points to last char of subsequence
        int end = i;
        j = m - 1;
        
        // Go backward to minimize window
        while (j >= 0) {
            if (s1[i] == s2[j]) j--;
            i--;
        }
        i++;  // Start of window
        
        if (end - i + 1 < minLen) {
            minLen = end - i + 1;
            minStart = i;
        }
        
        i++;  // Move to find next window
    }
    
    return minLen == INT_MAX ? "" : s1.substr(minStart, minLen);
}


/*
PROBLEM 4: Shortest Subarray with Sum at Least K (LeetCode 862)
───────────────────────────────────────────────────────────────
Find shortest subarray with sum >= k. Array can have NEGATIVE numbers.

Input: nums = [2,-1,2], k = 3
Output: 3 ([2,-1,2])

Approach: Use monotonic deque with prefix sums
(Standard sliding window doesn't work with negatives)

Time: O(n) | Space: O(n)
*/
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    
    deque<int> dq;  // Monotonic increasing of prefix sums
    int minLen = INT_MAX;
    
    for (int i = 0; i <= n; i++) {
        // Check if we found valid subarray (prefix[i] - prefix[dq.front()] >= k)
        while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k) {
            minLen = min(minLen, i - dq.front());
            dq.pop_front();
        }
        
        // Maintain monotonic increasing
        while (!dq.empty() && prefix[i] <= prefix[dq.back()]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return minLen == INT_MAX ? -1 : minLen;
}


/*
PROBLEM 5: Minimum Operations to Reduce X to Zero (LeetCode 1658)
─────────────────────────────────────────────────────────────────
Remove elements from either end to make sum = x. Find minimum operations.

Input: nums = [1,1,4,2,3], x = 5
Output: 2 (remove 3, 2)

Key Insight: Equivalent to finding LONGEST subarray with sum = totalSum - x

Time: O(n) | Space: O(1)
*/
int minOperations(vector<int>& nums, int x) {
    int n = nums.size();
    int totalSum = 0;
    for (int num : nums) totalSum += num;
    
    int target = totalSum - x;
    if (target < 0) return -1;
    if (target == 0) return n;
    
    // Find longest subarray with sum = target
    int left = 0, sum = 0, maxLen = -1;
    
    for (int right = 0; right < n; right++) {
        sum += nums[right];
        
        while (sum > target && left <= right) {
            sum -= nums[left];
            left++;
        }
        
        if (sum == target) {
            maxLen = max(maxLen, right - left + 1);
        }
    }
    
    return maxLen == -1 ? -1 : n - maxLen;
}


/*
PROBLEM 6: Minimum Number of Flips to Make Binary String Alternating (LeetCode 1888)
───────────────────────────────────────────────────────────────────────────────────
Type 1: Remove first char, append to end
Type 2: Flip any character

Input: s = "111000"
Output: 2

Approach: Double string, find window of size n with minimum mismatches

Time: O(n) | Space: O(n)
*/
int minFlips(string s) {
    int n = s.size();
    string doubled = s + s;
    string alt1 = "", alt2 = "";
    
    // Generate two alternating patterns
    for (int i = 0; i < 2 * n; i++) {
        alt1 += (i % 2 == 0) ? '0' : '1';
        alt2 += (i % 2 == 0) ? '1' : '0';
    }
    
    int diff1 = 0, diff2 = 0, minFlips = INT_MAX;
    
    for (int i = 0; i < 2 * n; i++) {
        // Add right element
        if (doubled[i] != alt1[i]) diff1++;
        if (doubled[i] != alt2[i]) diff2++;
        
        // Remove left element if window > n
        if (i >= n) {
            if (doubled[i - n] != alt1[i - n]) diff1--;
            if (doubled[i - n] != alt2[i - n]) diff2--;
        }
        
        // Window is complete
        if (i >= n - 1) {
            minFlips = min(minFlips, min(diff1, diff2));
        }
    }
    
    return minFlips;
}


/*
PROBLEM 7: Minimum Consecutive Cards to Pick Up (LeetCode 2260)
───────────────────────────────────────────────────────────────
Find minimum length subarray containing at least one pair of matching cards.

Input: cards = [3,4,2,3,4,7]
Output: 4 ([3,4,2,3] or [4,2,3,4])

Time: O(n) | Space: O(n)
*/
int minimumCardPickup(vector<int>& cards) {
    unordered_map<int, int> lastSeen;
    int minLen = INT_MAX;
    
    for (int i = 0; i < cards.size(); i++) {
        if (lastSeen.count(cards[i])) {
            minLen = min(minLen, i - lastSeen[cards[i]] + 1);
        }
        lastSeen[cards[i]] = i;
    }
    
    return minLen == INT_MAX ? -1 : minLen;
}


/*
PROBLEM 8: Replace the Substring for Balanced String (LeetCode 1234)
────────────────────────────────────────────────────────────────────
String contains only Q, W, E, R. Find minimum substring to replace
so each char appears exactly n/4 times.

Input: s = "QWER"
Output: 0 (already balanced)

Input: s = "QQWE"
Output: 1 (replace one Q)

Time: O(n) | Space: O(1)
*/
int balancedString(string s) {
    int n = s.size();
    int required = n / 4;
    unordered_map<char, int> count;
    
    for (char c : s) count[c]++;
    
    // Check if already balanced
    auto isBalanced = [&]() {
        return count['Q'] <= required && count['W'] <= required && 
               count['E'] <= required && count['R'] <= required;
    };
    
    if (isBalanced()) return 0;
    
    int left = 0, minLen = n;
    
    for (int right = 0; right < n; right++) {
        // Remove from outside (add to window)
        count[s[right]]--;
        
        // Shrink while balanced
        while (isBalanced()) {
            minLen = min(minLen, right - left + 1);
            count[s[left]]++;  // Add back to outside
            left++;
        }
    }
    
    return minLen;
}


/*
PROBLEM 9: Minimum Number of K Consecutive Bit Flips (LeetCode 995)
───────────────────────────────────────────────────────────────────
Flip K consecutive bits in each operation. Return minimum flips to make all 1s.

Input: nums = [0,0,0,1,0,1,1,0], k = 3
Output: 3

Approach: Greedy + sliding window to track flips

Time: O(n) | Space: O(n) or O(1) with modification
*/
int minKBitFlips(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> isFlipped(n, 0);  // Track where flips start
    int flips = 0, flipCount = 0;
    
    for (int i = 0; i < n; i++) {
        // Remove effect of flip that ended
        if (i >= k) {
            flipCount -= isFlipped[i - k];
        }
        
        // Current effective value
        if ((nums[i] + flipCount) % 2 == 0) {  // Currently 0
            if (i + k > n) return -1;  // Can't flip
            
            isFlipped[i] = 1;
            flipCount++;
            flips++;
        }
    }
    
    return flips;
}


/*
PROBLEM 10: Grumpy Bookstore Owner (LeetCode 1052)
──────────────────────────────────────────────────
Owner is grumpy some minutes. Can use technique for X minutes to not be grumpy.
Find maximum satisfied customers.

Input: customers = [1,0,1,2,1,1,7,5], grumpy = [0,1,0,1,0,1,0,1], minutes = 3
Output: 16

Time: O(n) | Space: O(1)
*/
int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
    int n = customers.size();
    int baseSatisfied = 0;
    
    // Count customers when owner is not grumpy
    for (int i = 0; i < n; i++) {
        if (grumpy[i] == 0) {
            baseSatisfied += customers[i];
        }
    }
    
    // Find window of 'minutes' that recovers most grumpy customers
    int windowRecovery = 0, maxRecovery = 0;
    
    for (int i = 0; i < n; i++) {
        if (grumpy[i] == 1) {
            windowRecovery += customers[i];
        }
        
        if (i >= minutes && grumpy[i - minutes] == 1) {
            windowRecovery -= customers[i - minutes];
        }
        
        if (i >= minutes - 1) {
            maxRecovery = max(maxRecovery, windowRecovery);
        }
    }
    
    return baseSatisfied + maxRecovery;
}


// ============================================================================
// MAIN - Demo all functions
// ============================================================================

int main() {
    cout << "=== Variable Window - Shortest/Minimum ===\n\n";
    
    // 1. Minimum Size Subarray Sum
    vector<int> arr1 = {2,3,1,2,4,3};
    cout << "1. Min subarray sum >= 7: " << minSubArrayLen(7, arr1) << "\n";
    
    // 2. Minimum Window Substring
    cout << "2. Min window substring: " << minWindow("ADOBECODEBANC", "ABC") << "\n";
    
    // 4. Shortest Subarray with Sum >= K
    vector<int> arr4 = {2,-1,2};
    cout << "4. Shortest subarray sum >= 3: " << shortestSubarray(arr4, 3) << "\n";
    
    // 5. Min Operations to Reduce X
    vector<int> arr5 = {1,1,4,2,3};
    cout << "5. Min operations to reduce 5: " << minOperations(arr5, 5) << "\n";
    
    // 7. Minimum Card Pickup
    vector<int> cards = {3,4,2,3,4,7};
    cout << "7. Min card pickup: " << minimumCardPickup(cards) << "\n";
    
    // 8. Balanced String
    cout << "8. Min replace for balanced QQWE: " << balancedString("QQWE") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+─────────────────────────────────────+──────────────────────────────────────────+
| Problem                             | Valid Window Condition                   |
+─────────────────────────────────────+──────────────────────────────────────────+
| Min Subarray Sum                    | sum >= target                            |
| Min Window Substring                | Contains all chars of t                  |
| Min Window Subsequence              | Contains t as subsequence                |
| Shortest Subarray Sum >= K          | prefix[i] - prefix[j] >= k (use deque)   |
| Min Ops to Reduce X                 | Find longest with sum = total - x        |
| Balanced String                     | Each char count <= n/4 outside window    |
+─────────────────────────────────────+──────────────────────────────────────────+

KEY INSIGHT: For "shortest" problems:
1. Expand until window becomes valid
2. Shrink while window remains valid, updating minimum
3. Stop shrinking when window becomes invalid

================================================================================
*/

