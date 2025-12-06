/*
================================================================================
                    ROTATED SORTED ARRAY PROBLEMS
================================================================================

A rotated sorted array is a sorted array that has been "rotated" at some pivot.
Example: [1,2,3,4,5] rotated at pivot 3 → [4,5,1,2,3]

Key Property: One half is ALWAYS sorted!

Pattern 1: Search in Rotated Sorted Array (no duplicates)
Pattern 2: Search in Rotated Sorted Array II (with duplicates)
Pattern 3: Find Minimum in Rotated Sorted Array
Pattern 4: Find Minimum with Duplicates
Pattern 5: Find Rotation Count / Pivot Index

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
================================================================================
PATTERN 1: SEARCH IN ROTATED SORTED ARRAY
================================================================================
LeetCode: 33. Search in Rotated Sorted Array
Problem: Find target in rotated sorted array (no duplicates)
Time: O(log n), Space: O(1)

Key Insight: At least one half is ALWAYS sorted!
Strategy: 
1. Find which half is sorted
2. Check if target is in sorted half
3. Search accordingly
*/
int searchRotated(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        
        // LEFT half is sorted [left...mid]
        if (nums[left] <= nums[mid]) {
            // Is target in the left sorted portion?
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;    // Search left
            } else {
                left = mid + 1;     // Search right
            }
        }
        // RIGHT half is sorted [mid...right]
        else {
            // Is target in the right sorted portion?
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;     // Search right
            } else {
                right = mid - 1;    // Search left
            }
        }
    }
    
    return -1;
}
/*
Example: [4,5,6,7,0,1,2], target=0
- mid=3 (7), left half [4,5,6,7] sorted
- 0 not in [4,7], search right
- mid=5 (1), left half [0,1] sorted... but wait
- Actually: left=4, right=6, mid=5, nums[mid]=1
- nums[4]=0 <= nums[5]=1, left sorted [0,1]
- 0 is in [0,1), go left → found at index 4
*/


/*
================================================================================
PATTERN 2: SEARCH IN ROTATED SORTED ARRAY II (WITH DUPLICATES)
================================================================================
LeetCode: 81. Search in Rotated Sorted Array II
Problem: Same but with duplicates
Time: O(log n) average, O(n) worst case when many duplicates
Space: O(1)

Key Change: Handle nums[left] == nums[mid] == nums[right]
           In this case, we can't determine which half is sorted!
           Solution: Shrink from both ends
*/
bool searchRotatedDuplicates(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return true;
        }
        
        // Cannot determine which half is sorted
        // Example: [1,0,1,1,1] - nums[left]=nums[mid]=nums[right]=1
        if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
            left++;
            right--;
        }
        // Left half is sorted
        else if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Right half is sorted
        else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return false;
}


/*
================================================================================
PATTERN 3: FIND MINIMUM IN ROTATED SORTED ARRAY
================================================================================
LeetCode: 153. Find Minimum in Rotated Sorted Array
Problem: Find the minimum element (no duplicates)
Time: O(log n), Space: O(1)

Key Insight: Minimum is at the "rotation point"
            Compare mid with right to decide direction
*/
int findMin(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // If mid > right, min is in right half (after mid)
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        }
        // If mid <= right, min is at mid or left of mid
        else {
            right = mid;
        }
    }
    
    return nums[left];  // left == right at minimum
}
/*
Example: [4,5,6,7,0,1,2]
- mid=3 (7) > right (2) → min in right half, left=4
- mid=5 (1) < right (2) → min at mid or left, right=5
- mid=4 (0) < right (1) → right=4
- left=4=right, return nums[4]=0 ✓

Example: [3,4,5,1,2]
- mid=2 (5) > right (2) → left=3
- mid=3 (1) < right (2) → right=3
- return nums[3]=1 ✓
*/


/*
================================================================================
PATTERN 4: FIND MINIMUM WITH DUPLICATES
================================================================================
LeetCode: 154. Find Minimum in Rotated Sorted Array II
Problem: Find minimum with duplicates allowed
Time: O(log n) average, O(n) worst case
Space: O(1)
*/
int findMinDuplicates(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        }
        else if (nums[mid] < nums[right]) {
            right = mid;
        }
        // nums[mid] == nums[right], can't decide
        else {
            right--;  // Safe to shrink by 1
        }
    }
    
    return nums[left];
}
// Example: [2,2,2,0,1] → returns 0
// Example: [3,3,1,3] → returns 1


/*
================================================================================
PATTERN 5: FIND ROTATION COUNT / PIVOT INDEX
================================================================================
Problem: How many times was the array rotated?
         (Same as finding index of minimum element)
Time: O(log n), Space: O(1)
*/
int findRotationCount(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    // Array not rotated
    if (nums[left] <= nums[right]) {
        return 0;
    }
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;  // Index of minimum = rotation count
}
// Example: [4,5,6,7,0,1,2] → returns 4 (rotated 4 times)
// Example: [2,3,4,5,1] → returns 4


/*
================================================================================
PATTERN 6: FIND PEAK IN ROTATED ARRAY
================================================================================
Problem: Find the maximum element (element before rotation point)
Time: O(log n), Space: O(1)
*/
int findPeakRotated(vector<int>& nums) {
    int minIdx = findRotationCount(nums);
    
    // Handle edge case: not rotated
    if (minIdx == 0) {
        return nums.back();
    }
    
    return nums[minIdx - 1];
}
// Example: [4,5,6,7,0,1,2] → returns 7


/*
================================================================================
PATTERN 7: SEARCH IN NEARLY SORTED ARRAY
================================================================================
Problem: Array sorted but each element may be swapped with neighbor
         arr[i] can be at i-1, i, or i+1
Time: O(log n), Space: O(1)
*/
int searchNearlySorted(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        // Check neighbors
        if (mid > left && nums[mid - 1] == target) {
            return mid - 1;
        }
        if (mid < right && nums[mid + 1] == target) {
            return mid + 1;
        }
        
        // Decide which half
        if (nums[mid] < target) {
            left = mid + 2;  // Skip checked elements
        } else {
            right = mid - 2;
        }
    }
    
    return -1;
}
// Example: [10,3,40,20,50,80,70], target=40 → returns 2


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Rotated Array Problems ===\n\n";
    
    // Pattern 1: Search in Rotated Array
    vector<int> arr1 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Array: [4,5,6,7,0,1,2]\n";
    cout << "1. Search for 0: index " << searchRotated(arr1, 0) << endl;
    cout << "   Search for 3: index " << searchRotated(arr1, 3) << endl;
    
    // Pattern 2: Search with Duplicates
    vector<int> arr2 = {2, 5, 6, 0, 0, 1, 2};
    cout << "\n2. [2,5,6,0,0,1,2] contains 0? " 
         << (searchRotatedDuplicates(arr2, 0) ? "Yes" : "No") << endl;
    
    // Pattern 3: Find Minimum
    cout << "\n3. Minimum in [4,5,6,7,0,1,2]: " << findMin(arr1) << endl;
    
    // Pattern 4: Find Minimum with Duplicates
    vector<int> arr3 = {2, 2, 2, 0, 1};
    cout << "4. Minimum in [2,2,2,0,1]: " << findMinDuplicates(arr3) << endl;
    
    // Pattern 5: Rotation Count
    cout << "\n5. Rotation count [4,5,6,7,0,1,2]: " << findRotationCount(arr1) << endl;
    
    // Pattern 6: Peak (Maximum)
    cout << "6. Peak in [4,5,6,7,0,1,2]: " << findPeakRotated(arr1) << endl;
    
    // Pattern 7: Nearly Sorted
    vector<int> arr4 = {10, 3, 40, 20, 50, 80, 70};
    cout << "\n7. Search 40 in nearly sorted [10,3,40,20,50,80,70]: " 
         << searchNearlySorted(arr4, 40) << endl;
    
    return 0;
}

/*
================================================================================
                          VISUALIZATION
================================================================================

Original Sorted:     [0, 1, 2, 3, 4, 5, 6, 7]
                      ↑                    ↑
                     min                  max

Rotated at pivot 5:  [5, 6, 7, 0, 1, 2, 3, 4]
                      ↑     ↑  ↑           ↑
                     L      H  min        R
                     
Key Properties:
- nums[L] > nums[R] → array is rotated
- One half is ALWAYS sorted
- If nums[L] <= nums[mid] → left half sorted
- If nums[mid] <= nums[R] → right half sorted

================================================================================
                              CHEAT SHEET
================================================================================

┌──────────────────────────────────────────────────────────────────────────────┐
│ Problem                     │ Compare with     │ Key Condition              │
├──────────────────────────────────────────────────────────────────────────────┤
│ Find minimum                │ nums[right]      │ mid > right → go right     │
│ Find maximum                │ min_idx - 1      │ Find min first             │
│ Search element              │ Check both halves│ Sorted half contains it?   │
│ With duplicates             │ Same + shrink    │ left==mid==right → shrink  │
│ Rotation count              │ Same as find min │ Index of minimum           │
└──────────────────────────────────────────────────────────────────────────────┘

Why compare mid with RIGHT (not left) for finding minimum?
- Comparing with right handles both rotated and non-rotated arrays uniformly
- If not rotated: mid always <= right, converges to left edge
- If rotated: mid > right when min is on right half

================================================================================
*/

