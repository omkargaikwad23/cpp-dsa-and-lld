/*
================================================================================
                    QUICK SELECT (Hoare's Selection Algorithm)
================================================================================

PROBLEM: Find the Kth smallest/largest element in unsorted array.

KEY INSIGHT: Partition like QuickSort, but only recurse on ONE side
             (the side that contains our target index).

ALGORITHM:
1. Pick a pivot and partition array
2. If pivot is at index k-1, return it
3. If k-1 < pivot index, recurse on left side
4. If k-1 > pivot index, recurse on right side

TIME:  O(n) average, O(n²) worst case
SPACE: O(1) iterative, O(log n) recursive

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// PARTITION FUNCTION (Lomuto scheme)
// ═══════════════════════════════════════════════════════════════════════════

int partition(vector<int>& nums, int left, int right) {
    int pivot = nums[right];  // Choose rightmost as pivot
    int i = left;             // Pointer for smaller elements
    
    for (int j = left; j < right; j++) {
        if (nums[j] <= pivot) {
            swap(nums[i], nums[j]);
            i++;
        }
    }
    
    swap(nums[i], nums[right]);  // Place pivot in correct position
    return i;  // Return pivot index
}

// ═══════════════════════════════════════════════════════════════════════════
// QUICK SELECT - Kth Smallest (1-indexed)
// ═══════════════════════════════════════════════════════════════════════════

int quickSelect(vector<int>& nums, int left, int right, int k) {
    if (left == right) {
        return nums[left];
    }
    
    int pivotIndex = partition(nums, left, right);
    
    if (k - 1 == pivotIndex) {
        return nums[pivotIndex];  // Found!
    } else if (k - 1 < pivotIndex) {
        return quickSelect(nums, left, pivotIndex - 1, k);  // Search left
    } else {
        return quickSelect(nums, pivotIndex + 1, right, k);  // Search right
    }
}

int findKthSmallest(vector<int> nums, int k) {
    return quickSelect(nums, 0, nums.size() - 1, k);
}

// ═══════════════════════════════════════════════════════════════════════════
// ITERATIVE VERSION (slightly more efficient)
// ═══════════════════════════════════════════════════════════════════════════

int quickSelectIterative(vector<int>& nums, int k) {
    int left = 0, right = nums.size() - 1;
    
    while (left <= right) {
        int pivotIndex = partition(nums, left, right);
        
        if (pivotIndex == k - 1) {
            return nums[pivotIndex];
        } else if (pivotIndex > k - 1) {
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
    
    return -1;  // Should never reach here for valid k
}

// ═══════════════════════════════════════════════════════════════════════════
// KTH LARGEST (LC 215) - Convert to Kth smallest
// ═══════════════════════════════════════════════════════════════════════════

int findKthLargest(vector<int> nums, int k) {
    int n = nums.size();
    // Kth largest = (n - k + 1)th smallest
    return quickSelect(nums, 0, n - 1, n - k + 1);
}

// ═══════════════════════════════════════════════════════════════════════════
// RANDOMIZED VERSION (avoids O(n²) worst case)
// ═══════════════════════════════════════════════════════════════════════════

int partitionRandom(vector<int>& nums, int left, int right) {
    // Random pivot to avoid worst case
    int randomIndex = left + rand() % (right - left + 1);
    swap(nums[randomIndex], nums[right]);
    return partition(nums, left, right);
}

int quickSelectRandom(vector<int>& nums, int left, int right, int k) {
    if (left == right) return nums[left];
    
    int pivotIndex = partitionRandom(nums, left, right);
    
    if (k - 1 == pivotIndex) return nums[pivotIndex];
    else if (k - 1 < pivotIndex) return quickSelectRandom(nums, left, pivotIndex - 1, k);
    else return quickSelectRandom(nums, pivotIndex + 1, right, k);
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    
    cout << "Array: [3, 2, 1, 5, 6, 4]\n\n";
    
    cout << "Kth Smallest:\n";
    for (int k = 1; k <= 6; k++) {
        vector<int> copy = nums;
        cout << "  k=" << k << ": " << findKthSmallest(copy, k) << "\n";
    }
    
    cout << "\nKth Largest:\n";
    for (int k = 1; k <= 3; k++) {
        vector<int> copy = nums;
        cout << "  k=" << k << ": " << findKthLargest(copy, k) << "\n";
    }
    
    return 0;
}

/*
================================================================================
                         COMPARISON WITH SORTING
================================================================================

SORTING APPROACH:
  - Sort array: O(n log n)
  - Access k-th element: O(1)
  - Total: O(n log n)

QUICK SELECT:
  - Average: O(n)
  - Worst: O(n²) but randomized avoids this

HEAP APPROACH:
  - Build min-heap of size k: O(n log k)
  - Good when k << n

WHEN TO USE EACH:
  - Quick Select: Single query, large array
  - Sorting: Multiple queries on same array
  - Heap: k is very small, or streaming data

RELATED PROBLEMS:
- LC 215: Kth Largest Element in an Array
- LC 347: Top K Frequent Elements
- LC 973: K Closest Points to Origin
- LC 703: Kth Largest Element in a Stream

================================================================================
*/

