/*
================================================================================
                    DUTCH NATIONAL FLAG ALGORITHM
================================================================================

PROBLEM: Sort an array containing only 0s, 1s, and 2s in a single pass.
         (Named after the Dutch flag which has 3 color stripes)

Also known as: 3-way partitioning, Sort Colors (LC 75)

KEY INSIGHT: Use 3 pointers to partition array into 3 regions:
  [0, low)    → all 0s
  [low, mid)  → all 1s  
  [mid, high] → unprocessed
  (high, n)   → all 2s

ALGORITHM:
1. Initialize: low = 0, mid = 0, high = n-1
2. While mid <= high:
   - If arr[mid] == 0: swap(arr[low], arr[mid]), low++, mid++
   - If arr[mid] == 1: mid++
   - If arr[mid] == 2: swap(arr[mid], arr[high]), high--

TIME:  O(n) - single pass
SPACE: O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// CLASSIC: Sort Colors (LC 75)
// ═══════════════════════════════════════════════════════════════════════════

void sortColors(vector<int>& nums) {
    int low = 0;              // Next position for 0
    int mid = 0;              // Current element being processed
    int high = nums.size() - 1;  // Next position for 2
    
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } 
        else if (nums[mid] == 1) {
            mid++;
        } 
        else {  // nums[mid] == 2
            swap(nums[mid], nums[high]);
            high--;
            // Don't increment mid! Need to check swapped element
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// VARIATION: 3-Way Partition around pivot (used in QuickSort)
// ═══════════════════════════════════════════════════════════════════════════

pair<int, int> threeWayPartition(vector<int>& nums, int pivot) {
    int low = 0;
    int mid = 0;
    int high = nums.size() - 1;
    
    while (mid <= high) {
        if (nums[mid] < pivot) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } 
        else if (nums[mid] == pivot) {
            mid++;
        } 
        else {
            swap(nums[mid], nums[high]);
            high--;
        }
    }
    
    // Returns range [low, high] where all elements equal pivot
    return {low, high};
}

// ═══════════════════════════════════════════════════════════════════════════
// VARIATION: Move all zeros to end (LC 283)
// ═══════════════════════════════════════════════════════════════════════════

void moveZeroes(vector<int>& nums) {
    int nonZero = 0;  // Next position for non-zero
    
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            swap(nums[nonZero], nums[i]);
            nonZero++;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// VARIATION: Segregate negative and positive (negatives first)
// ═══════════════════════════════════════════════════════════════════════════

void segregateNegativePositive(vector<int>& nums) {
    int neg = 0;  // Next position for negative
    
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] < 0) {
            swap(nums[neg], nums[i]);
            neg++;
        }
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test Sort Colors
    vector<int> colors = {2, 0, 2, 1, 1, 0};
    cout << "Before: ";
    for (int c : colors) cout << c << " ";
    
    sortColors(colors);
    
    cout << "\nAfter:  ";
    for (int c : colors) cout << c << " ";
    cout << "\n\n";
    
    // Test Move Zeroes
    vector<int> nums = {0, 1, 0, 3, 12};
    cout << "Move zeroes - Before: ";
    for (int n : nums) cout << n << " ";
    
    moveZeroes(nums);
    
    cout << "\nMove zeroes - After:  ";
    for (int n : nums) cout << n << " ";
    cout << "\n\n";
    
    // Test 3-way partition
    vector<int> arr = {4, 9, 4, 4, 1, 9, 4, 4, 9, 4, 4, 1, 4};
    cout << "3-way partition around 4:\n";
    cout << "Before: ";
    for (int x : arr) cout << x << " ";
    
    auto [lo, hi] = threeWayPartition(arr, 4);
    
    cout << "\nAfter:  ";
    for (int x : arr) cout << x << " ";
    cout << "\nPivot range: [" << lo << ", " << hi << "]\n";
    
    return 0;
}

/*
================================================================================
                         VISUAL WALKTHROUGH
================================================================================

Array: [2, 0, 2, 1, 1, 0]
       L     H
       M

Step 1: nums[mid]=2 → swap with high, high--
        [0, 0, 2, 1, 1, 2]
         L        H
         M

Step 2: nums[mid]=0 → swap with low, low++, mid++
        [0, 0, 2, 1, 1, 2]
            L     H
            M

Step 3: nums[mid]=0 → swap with low, low++, mid++
        [0, 0, 2, 1, 1, 2]
               L  H
               M

Step 4: nums[mid]=2 → swap with high, high--
        [0, 0, 1, 1, 2, 2]
               L H
               M

Step 5: nums[mid]=1 → mid++
        [0, 0, 1, 1, 2, 2]
               L H
                 M

Step 6: nums[mid]=1 → mid++
        [0, 0, 1, 1, 2, 2]
               L H
                   M   (mid > high, DONE!)

RELATED PROBLEMS:
- LC 75: Sort Colors
- LC 283: Move Zeroes
- LC 905: Sort Array By Parity
- LC 922: Sort Array By Parity II

================================================================================
*/

