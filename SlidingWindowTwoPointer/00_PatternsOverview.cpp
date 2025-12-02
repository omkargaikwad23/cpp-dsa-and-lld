/*
================================================================================
              SLIDING WINDOW & TWO POINTER PATTERNS - OVERVIEW
================================================================================

This folder contains comprehensive patterns for Sliding Window and Two Pointer
techniques - essential for solving array/string problems efficiently.

Time Complexity: Usually O(n) or O(n log n)
Space Complexity: Usually O(1) or O(k) where k = window size or unique elements

================================================================================
                           PATTERN CLASSIFICATION
================================================================================

1. FIXED SIZE SLIDING WINDOW
   ─────────────────────────
   Window size is constant (given as input).
   
   Problems:
   - Maximum sum of subarray of size K
   - First negative in every window of size K
   - Count distinct elements in every window of size K
   - Maximum of all subarrays of size K
   - Permutation in String (fixed window = pattern length)
   - Find All Anagrams in String
   
   Template:
   for (int i = 0; i < n; i++) {
       // Add element to window
       if (i >= k) {
           // Remove element leaving window
       }
       if (i >= k - 1) {
           // Window is complete, process result
       }
   }

2. VARIABLE SIZE SLIDING WINDOW (Shrinking/Expanding)
   ───────────────────────────────────────────────────
   Window size changes based on a condition.
   
   Problems:
   - Longest Substring Without Repeating Characters
   - Longest Substring with At Most K Distinct Characters
   - Minimum Window Substring
   - Minimum Size Subarray Sum (sum >= target)
   - Maximum Consecutive Ones III (flip at most K zeros)
   - Longest Repeating Character Replacement
   - Fruit Into Baskets
   - Subarrays with K Different Integers
   
   Template (Find Maximum/Longest):
   int left = 0;
   for (int right = 0; right < n; right++) {
       // Expand: add arr[right] to window
       while ( window invalid ) {
           // Shrink: remove arr[left] from window
           left++;
       }
       // Update max result
       maxLen = max(maxLen, right - left + 1);
   }
   
   Template (Find Minimum/Shortest):
   int left = 0;
   for (int right = 0; right < n; right++) {
       // Expand: add arr[right] to window
       while ( window valid/satisfies condition ) {
           // Update min result
           minLen = min(minLen, right - left + 1);
           // Shrink: remove arr[left] from window
           left++;
       }
   }

3. TWO POINTERS - OPPOSITE DIRECTION (Converging)
   ───────────────────────────────────────────────
   Start from both ends, move towards center.
   
   Problems:
   - Two Sum (sorted array)
   - Three Sum / Four Sum
   - Container With Most Water
   - Trapping Rain Water
   - Valid Palindrome
   - Reverse String / Array
   - Sort Colors (Dutch National Flag)
   - Remove Duplicates from Sorted Array
   
   Template:
   int left = 0, right = n - 1;
   while (left < right) {
       if ( some condition ) left++;
       else if ( some condition ) right--;
       else {
           // Found answer or process
       }
   }

4. TWO POINTERS - SAME DIRECTION (Fast & Slow)
   ───────────────────────────────────────────
   Both pointers start from same end, move at different speeds.
   
   Problems:
   - Remove Element / Move Zeros
   - Remove Duplicates from Sorted Array
   - Linked List Cycle Detection (Floyd's)
   - Find Middle of Linked List
   - Find Duplicate Number
   - Happy Number
   - Merge Sorted Arrays in-place
   
   Template:
   int slow = 0;
   for (int fast = 0; fast < n; fast++) {
       if ( condition ) {
           // Process arr[slow] and arr[fast]
           slow++;
       }
   }

5. SLIDING WINDOW WITH HASHMAP/COUNTER
   ────────────────────────────────────
   Track frequency of elements in current window.
   
   Problems:
   - Minimum Window Substring
   - Find All Anagrams
   - Longest Substring with At Most K Distinct Chars
   - Subarrays with K Different Integers
   
   Template:
   unordered_map<char, int> freq;
   int left = 0;
   for (int right = 0; right < n; right++) {
       freq[s[right]]++;
       while ( window condition violated ) {
           freq[s[left]]--;
           if (freq[s[left]] == 0) freq.erase(s[left]);
           left++;
       }
       // Process valid window
   }

================================================================================
                         FILE ORGANIZATION
================================================================================

01_FixedWindowSize.cpp         - Fixed size window patterns
02_VariableWindowLongest.cpp   - Find longest/maximum subarray/substring
03_VariableWindowShortest.cpp  - Find shortest/minimum subarray/substring
04_TwoPointersOpposite.cpp     - Converging pointers from both ends
05_TwoPointersSameDirection.cpp - Fast/slow pointers, partition problems
06_SlidingWindowWithMap.cpp    - Window with frequency counting
07_AdvancedProblems.cpp        - Complex combinations of patterns

================================================================================
                           KEY INSIGHTS
================================================================================

1. WHEN TO USE SLIDING WINDOW:
   - Contiguous subarray/substring problems
   - "Maximum/Minimum length" with some constraint
   - "Number of subarrays" with property

2. WHEN TO USE TWO POINTERS:
   - Sorted array problems
   - Pairs with target sum
   - Partition problems
   - Palindrome problems

3. FIXED vs VARIABLE WINDOW:
   - Fixed: Window size given in problem
   - Variable: Window size depends on constraint (sum, distinct chars, etc.)

4. MAXIMUM vs MINIMUM:
   - Maximum: Expand first, shrink when invalid
   - Minimum: Expand until valid, shrink while still valid

5. OPTIMIZATION PATTERN:
   - Brute force O(n²) or O(n³) → Sliding window O(n)
   - If you see "subarray" or "substring" → Think sliding window

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Quick reference - see individual files for detailed implementations

int main() {
    cout << "=== Sliding Window & Two Pointer Patterns ===" << endl;
    cout << "See individual files for detailed implementations." << endl;
    return 0;
}

