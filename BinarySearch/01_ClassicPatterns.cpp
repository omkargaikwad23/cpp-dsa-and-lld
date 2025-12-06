/*
================================================================================
                    CLASSIC BINARY SEARCH PATTERNS
================================================================================

This file covers fundamental binary search patterns on sorted arrays.

Pattern 1: Exact Element Search
Pattern 2: Lower Bound (first >= target)
Pattern 3: Upper Bound (first > target)
Pattern 4: First Occurrence
Pattern 5: Last Occurrence
Pattern 6: Search Insert Position
Pattern 7: Count in Range
Pattern 8: Floor and Ceil

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
================================================================================
PATTERN 1: EXACT ELEMENT SEARCH
================================================================================
Problem: Find index of target in sorted array
LeetCode: 704. Binary Search
Time: O(log n), Space: O(1)
*/
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;             // Found!
        } else if (nums[mid] < target) {
            left = mid + 1;         // Search right half
        } else {
            right = mid - 1;        // Search left half
        }
    }
    
    return -1;  // Not found
}
// Example: [1,3,5,7,9], target=5 → returns 2


/*
================================================================================
PATTERN 2: LOWER BOUND
================================================================================
Problem: Find first position where element >= target
         (insertion point that keeps array sorted)
Same as: std::lower_bound
Time: O(log n), Space: O(1)

Use Case: "Find first element not less than target"
*/
int lowerBound(vector<int>& nums, int target) {
    int left = 0, right = nums.size();  // Note: right = size (can insert at end)
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < target) {
            left = mid + 1;     // Need larger
        } else {
            right = mid;        // Found candidate, but look for earlier
        }
    }
    
    return left; // return the index of the first element >= target
}
// Example: [1,3,5,7,9], target=4 → returns 2 (index of 5)
// Example: [1,3,5,7,9], target=5 → returns 2 (index of 5)
// Example: [1,3,5,7,9], target=10 → returns 5 (past end)


/*
================================================================================
PATTERN 3: UPPER BOUND
================================================================================
Problem: Find first position where element > target
Same as: std::upper_bound
Time: O(log n), Space: O(1)

Use Case: "Find first element greater than target"
*/
int upperBound(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] <= target) {
            left = mid + 1;     // Need strictly larger
        } else {
            right = mid;        // Found candidate
        }
    }
    
    return left;
}
// Example: [1,3,5,7,9], target=5 → returns 3 (index of 7)
// Example: [1,2,2,2,3], target=2 → returns 4 (index of 3)


/*
================================================================================
PATTERN 4: FIRST OCCURRENCE (With Duplicates)
================================================================================
LeetCode: 34. Find First and Last Position of Element in Sorted Array
Time: O(log n), Space: O(1)

Key: When found, save result and keep searching LEFT
*/
int firstOccurrence(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            result = mid;       // Save this position
            right = mid - 1;    // Keep looking left for earlier occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}
// Example: [1,2,2,2,3], target=2 → returns 1


/*
================================================================================
PATTERN 5: LAST OCCURRENCE (With Duplicates)
================================================================================
Time: O(log n), Space: O(1)

Key: When found, save result and keep searching RIGHT
*/
int lastOccurrence(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            result = mid;       // Save this position
            left = mid + 1;     // Keep looking right for later occurrence
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}
// Example: [1,2,2,2,3], target=2 → returns 3


/*
================================================================================
PATTERN 6: SEARCH INSERT POSITION
================================================================================
LeetCode: 35. Search Insert Position
Problem: Return index where target should be inserted
Time: O(log n), Space: O(1)

This is exactly the same as lower_bound!
*/
int searchInsert(vector<int>& nums, int target) {
    int left = 0, right = nums.size();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}
// Example: [1,3,5,6], target=5 → returns 2 (found at index 2)
// Example: [1,3,5,6], target=2 → returns 1 (insert at index 1)
// Example: [1,3,5,6], target=7 → returns 4 (insert at end)


/*
================================================================================
PATTERN 7: COUNT ELEMENTS IN RANGE [low, high]
================================================================================
Time: O(log n), Space: O(1)

Uses: upper_bound(high) - lower_bound(low)
*/
int countInRange(vector<int>& nums, int low, int high) {
    // Count of elements where low <= x <= high
    auto left = lower_bound(nums.begin(), nums.end(), low);
    auto right = upper_bound(nums.begin(), nums.end(), high);
    return right - left;
}
// Example: [1,2,3,4,5,6,7], low=3, high=5 → returns 3 (elements: 3,4,5)


/*
================================================================================
PATTERN 8: FLOOR AND CEIL
================================================================================
Floor: Largest element <= target
Ceil: Smallest element >= target
*/
int findFloor(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int floor = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] <= target) {
            floor = nums[mid];  // Candidate for floor
            left = mid + 1;     // Try to find larger
        } else {
            right = mid - 1;
        }
    }
    
    return floor;
}
// Example: [1,3,5,7,9], target=6 → returns 5

int findCeil(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    int ceil = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] >= target) {
            ceil = nums[mid];   // Candidate for ceil
            right = mid - 1;    // Try to find smaller
        } else {
            left = mid + 1;
        }
    }
    
    return ceil;
}
// Example: [1,3,5,7,9], target=6 → returns 7


/*
================================================================================
PATTERN 9: FIND RANGE (First and Last Position)
================================================================================
LeetCode: 34. Find First and Last Position of Element in Sorted Array
Time: O(log n), Space: O(1)

Combines first and last occurrence
*/
vector<int> searchRange(vector<int>& nums, int target) {
    return {firstOccurrence(nums, target), lastOccurrence(nums, target)};
}
// Example: [5,7,7,8,8,10], target=8 → [3,4]
// Example: [5,7,7,8,8,10], target=6 → [-1,-1]


/*
================================================================================
PATTERN 10: SINGLE ELEMENT IN SORTED ARRAY
================================================================================
LeetCode: 540. Single Element in a Sorted Array
Problem: Every element appears twice except one. Find it.
Key: Use index parity! Before single element, pairs at (even,odd).
     After single element, pairs at (odd,even).
Time: O(log n), Space: O(1)
*/
int singleNonDuplicate(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Ensure mid is even (start of pair)
        if (mid % 2 == 1) mid--;
        
        if (nums[mid] == nums[mid + 1]) {
            // Pair is intact, single element is to the right
            left = mid + 2;
        } else {
            // Pair broken or single element is here or left
            right = mid;
        }
    }
    
    return nums[left];
}
// Example: [1,1,2,3,3,4,4,8,8] → returns 2


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Classic Binary Search Patterns ===\n\n";
    
    vector<int> arr = {1, 2, 2, 2, 3, 5, 7, 9};
    
    cout << "Array: [1, 2, 2, 2, 3, 5, 7, 9]\n\n";
    
    // Pattern 1: Exact Search
    cout << "1. Binary Search for 5: " << binarySearch(arr, 5) << endl;
    cout << "   Binary Search for 4: " << binarySearch(arr, 4) << endl;
    
    // Pattern 2: Lower Bound
    cout << "2. Lower Bound of 2: " << lowerBound(arr, 2) << endl;
    cout << "   Lower Bound of 4: " << lowerBound(arr, 4) << endl;
    
    // Pattern 3: Upper Bound
    cout << "3. Upper Bound of 2: " << upperBound(arr, 2) << endl;
    
    // Pattern 4 & 5: First and Last Occurrence
    cout << "4. First Occurrence of 2: " << firstOccurrence(arr, 2) << endl;
    cout << "5. Last Occurrence of 2: " << lastOccurrence(arr, 2) << endl;
    
    // Pattern 6: Search Insert
    vector<int> arr2 = {1, 3, 5, 6};
    cout << "6. Search Insert 4 in [1,3,5,6]: " << searchInsert(arr2, 4) << endl;
    
    // Pattern 7: Count in Range
    cout << "7. Count in range [2,5]: " << countInRange(arr, 2, 5) << endl;
    
    // Pattern 8: Floor and Ceil
    vector<int> arr3 = {1, 3, 5, 7, 9};
    cout << "8. Floor of 6 in [1,3,5,7,9]: " << findFloor(arr3, 6) << endl;
    cout << "   Ceil of 6 in [1,3,5,7,9]: " << findCeil(arr3, 6) << endl;
    
    // Pattern 9: Search Range
    vector<int> arr4 = {5, 7, 7, 8, 8, 10};
    auto range = searchRange(arr4, 8);
    cout << "9. Range of 8 in [5,7,7,8,8,10]: [" << range[0] << "," << range[1] << "]" << endl;
    
    // Pattern 10: Single Element
    vector<int> arr5 = {1, 1, 2, 3, 3, 4, 4, 8, 8};
    cout << "10. Single element in [1,1,2,3,3,4,4,8,8]: " << singleNonDuplicate(arr5) << endl;
    
    return 0;
}

/*
================================================================================
                              CHEAT SHEET
================================================================================

┌──────────────────────────────────────────────────────────────────────────────┐
│ Problem                    │ Technique              │ Return Value           │
├──────────────────────────────────────────────────────────────────────────────┤
│ Find exact element         │ left <= right          │ mid or -1              │
│ First >= target            │ left < right           │ left                   │
│ First > target             │ left < right           │ left                   │
│ First occurrence           │ left <= right + result │ result                 │
│ Last occurrence            │ left <= right + result │ result                 │
│ Insert position            │ Same as lower_bound    │ left                   │
│ Count in range             │ upper - lower          │ difference             │
└──────────────────────────────────────────────────────────────────────────────┘

KEY DIFFERENCES:
- Lower bound: nums[mid] < target  → left = mid + 1, else right = mid
- Upper bound: nums[mid] <= target → left = mid + 1, else right = mid

================================================================================
*/

