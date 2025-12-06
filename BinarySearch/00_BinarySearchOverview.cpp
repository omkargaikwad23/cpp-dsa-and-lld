/*
================================================================================
                      BINARY SEARCH - OVERVIEW
================================================================================

Binary Search is a search algorithm that finds the position of a target value
within a SORTED/MONOTONIC search space by repeatedly dividing the search interval
in half.

Time Complexity: O(log n)
Space Complexity: O(1) iterative, O(log n) recursive

================================================================================
                     WHEN TO USE BINARY SEARCH
================================================================================

1. SORTED ARRAY - Classical binary search
2. MONOTONIC FUNCTION - If condition changes from F→T or T→F
3. SEARCH SPACE - When you can define a min/max range and check feasibility
4. OPTIMIZATION - "Minimum maximum" or "Maximum minimum" problems

KEY INSIGHT: Binary search works whenever there's a monotonic property!
             (not just sorted arrays)

================================================================================
                          TWO MAIN TEMPLATES
================================================================================

TEMPLATE 1: Exact Match (left <= right)
─────────────────────────────────────────
Use when: Looking for exact target in array
Returns: Index of target or -1

    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;

TEMPLATE 2: Boundary Search (left < right)
─────────────────────────────────────────
Use when: Finding first/last position satisfying a condition
Returns: Boundary index

    int left = 0, right = n;  // or n-1 depending on problem
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (condition(mid)) right = mid;     // Find first true
        else left = mid + 1;
    }
    return left;

================================================================================
                     PATTERN CLASSIFICATION
================================================================================

1. CLASSIC BINARY SEARCH (01_ClassicPatterns.cpp)
   ─────────────────────────────────────────────────
   - Exact element search
   - Lower bound / Upper bound
   - First / Last occurrence
   - Search insert position
   - Count occurrences
   
   Keywords: "find", "search", "sorted array", "exact match"

2. ROTATED ARRAY (02_RotatedArray.cpp)
   ─────────────────────────────────────────────────
   - Search in rotated sorted array
   - Find minimum in rotated array
   - Find rotation point
   - With/without duplicates
   
   Keywords: "rotated", "pivot", "circular array"

3. BINARY SEARCH ON ANSWER (03_SearchOnAnswer.cpp)
   ─────────────────────────────────────────────────
   - Koko Eating Bananas
   - Capacity to Ship Packages
   - Split Array Largest Sum
   - Minimize Maximum / Maximize Minimum
   
   Keywords: "minimum speed", "maximum capacity", "at most k",
             "minimize the maximum", "within h hours"

4. MATRIX SEARCH (04_MatrixSearch.cpp)
   ─────────────────────────────────────────────────
   - Search in 2D sorted matrix
   - Search in row-wise & column-wise sorted matrix
   - Kth smallest in sorted matrix
   
   Keywords: "2D matrix", "sorted rows", "sorted columns"

5. ADVANCED PROBLEMS (05_AdvancedProblems.cpp)
   ─────────────────────────────────────────────────
   - Peak element
   - Find in Mountain Array
   - Median of Two Sorted Arrays
   - Aggressive Cows / Magnetic Force
   - Allocate Books
   
   Keywords: "bitonic", "mountain", "two arrays", "allocate"

================================================================================
                     BINARY SEARCH ON ANSWER TEMPLATE
================================================================================

This is the most important pattern for interviews!

The idea: Instead of searching IN an array, we search FOR an answer
          in a range [min_possible, max_possible]

TEMPLATE:
    int left = min_possible_answer;
    int right = max_possible_answer;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (isFeasible(mid)) {
            result = mid;           // This answer works
            right = mid - 1;        // Try for smaller (minimize)
            // OR left = mid + 1;   // Try for larger (maximize)
        } else {
            left = mid + 1;         // Need larger answer
            // OR right = mid - 1;  // Need smaller answer
        }
    }
    return result;

================================================================================
                        STL FUNCTIONS (C++)
================================================================================

#include <algorithm>
vector<int> v = {1, 2, 4, 4, 4, 5, 7};

// binary_search - returns true/false
bool found = binary_search(v.begin(), v.end(), 4);  // true

// lower_bound - iterator to first element >= value
auto lb = lower_bound(v.begin(), v.end(), 4);  // index 2

// upper_bound - iterator to first element > value  
auto ub = upper_bound(v.begin(), v.end(), 4);  // index 5

// Count occurrences
int count = upper_bound(...) - lower_bound(...);

// equal_range - returns pair of (lower_bound, upper_bound)
auto [lo, hi] = equal_range(v.begin(), v.end(), 4);

================================================================================
                          COMMON MISTAKES
================================================================================

1. Integer Overflow in mid calculation
   BAD:  mid = (left + right) / 2
   GOOD: mid = left + (right - left) / 2

2. Infinite loop with left < right
   - Make sure left or right always changes
   - mid = left + (right - left) / 2  → rounds down
   - mid = left + (right - left + 1) / 2  → rounds up (use when left = mid)

3. Off-by-one errors
   - Carefully decide: right = n or right = n-1?
   - Return left, right, or result?

4. Not identifying the monotonic property
   - Ask: "If answer X works, do all answers > X (or < X) also work?"

================================================================================
                          COMPLEXITY ANALYSIS
================================================================================

Search Space Size    | Iterations (log₂)
─────────────────────|──────────────────
10                   | 4
100                  | 7
1,000                | 10
1,000,000            | 20
1,000,000,000        | 30
10^18                | 60

Even for 10^18 search space, only ~60 iterations needed!

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Quick demo of the two main templates
int main() {
    cout << "=== Binary Search Overview ===" << endl;
    
    vector<int> arr = {1, 2, 4, 4, 4, 5, 7, 9};
    
    // Template 1: Exact match
    int target = 5;
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            cout << "Found " << target << " at index " << mid << endl;
            break;
        }
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    // Template 2: Lower bound (first element >= target)
    target = 4;
    left = 0; right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) right = mid;
        else left = mid + 1;
    }
    cout << "Lower bound of " << target << " is at index " << left << endl;
    
    // STL comparison
    auto it = lower_bound(arr.begin(), arr.end(), 4);
    cout << "STL lower_bound: index " << (it - arr.begin()) << endl;
    
    return 0;
}

/*
================================================================================
                          PROBLEM INDEX
================================================================================

01_ClassicPatterns.cpp
  - Binary Search
  - Lower Bound / Upper Bound
  - First / Last Occurrence
  - Search Insert Position
  - Count Elements in Range

02_RotatedArray.cpp
  - Search in Rotated Sorted Array
  - Search in Rotated Array II (duplicates)
  - Find Minimum in Rotated Sorted Array
  - Find Rotation Count

03_SearchOnAnswer.cpp (★ MOST IMPORTANT FOR INTERVIEWS ★)
  - Koko Eating Bananas (LC 875)
  - Capacity to Ship Packages (LC 1011)
  - Split Array Largest Sum (LC 410)
  - Minimum Days to Make m Bouquets (LC 1482)
  - Magnetic Force Between Two Balls (LC 1552)
  - Allocate Minimum Pages

04_MatrixSearch.cpp
  - Search a 2D Matrix (LC 74)
  - Search a 2D Matrix II (LC 240)
  - Kth Smallest Element in Sorted Matrix (LC 378)
  - Count Negative Numbers in Sorted Matrix

05_AdvancedProblems.cpp
  - Find Peak Element (LC 162)
  - Find in Mountain Array (LC 1095)
  - Median of Two Sorted Arrays (LC 4)
  - Sqrt(x) (LC 69)
  - Find K Closest Elements (LC 658)

================================================================================
*/

