/*
 * COUNT OF SMALLER NUMBERS AFTER SELF (LeetCode 315)
 * Using Divide and Conquer (Merge Sort)
 * 
 * PROBLEM:
 * Given an array nums, return an array counts where counts[i] is the number
 * of smaller elements to the RIGHT of nums[i].
 * 
 * Example:
 *   Input:  [5, 2, 6, 1]
 *   Output: [2, 1, 1, 0]
 *   
 *   Explanation:
 *   - For 5: elements to right smaller than 5 → [2, 1] → count = 2
 *   - For 2: elements to right smaller than 2 → [1]    → count = 1
 *   - For 6: elements to right smaller than 6 → [1]    → count = 1
 *   - For 1: no elements to the right          → []    → count = 0
 * 
 * BRUTE FORCE: O(n²) - For each element, scan all elements to its right
 * OPTIMAL:     O(n log n) - Using Merge Sort (Divide & Conquer)
 * 
 * ═══════════════════════════════════════════════════════════════════════════
 * KEY INSIGHT: During merge sort, when merging two sorted halves,
 * if an element from RIGHT half is placed before element from LEFT half,
 * it means that RIGHT element is SMALLER and originally was to the RIGHT.
 * ═══════════════════════════════════════════════════════════════════════════
 */

#include <iostream>
#include <vector>
using namespace std;

/*
 * WHY MERGE SORT WORKS HERE?
 * 
 * During the MERGE step:
 * - Left half contains elements that were originally to the LEFT
 * - Right half contains elements that were originally to the RIGHT
 * 
 * When we pick an element from RIGHT half before LEFT half element,
 * we know: "this right element is smaller AND was originally to the right"
 * 
 * We track ORIGINAL INDICES to update the correct position in result.
 */

class Solution {
private:
    vector<int> counts;  // Result array
    
    // We need to track original indices because sorting changes positions
    // pair<value, original_index>
    void mergeSort(vector<pair<int, int>>& nums, int left, int right) {
        if (left >= right) return;
        
        int mid = left + (right - left) / 2;
        
        // Divide
        mergeSort(nums, left, mid);
        mergeSort(nums, mid + 1, right);
        
        // Conquer (merge)
        merge(nums, left, mid, right);
    }
    
    void merge(vector<pair<int, int>>& nums, int left, int mid, int right) {
        vector<pair<int, int>> temp(right - left + 1);
        
        int i = left;      // Pointer for left half
        int j = mid + 1;   // Pointer for right half
        int k = 0;         // Pointer for temp array
        
        // Count of elements from right half that have been placed
        // (these are smaller elements that were to the right)
        int rightCount = 0;
        
        while (i <= mid && j <= right) {
            if (nums[j].first < nums[i].first) {
                // Element from right half is smaller
                // It will be placed before remaining left half elements
                rightCount++;
                temp[k++] = nums[j++];
            } else {
                // Element from left half is smaller or equal
                // All elements already taken from right half are smaller
                // AND were originally to the right of nums[i]
                counts[nums[i].second] += rightCount;
                temp[k++] = nums[i++];
            }
        }
        
        // Remaining elements in left half
        while (i <= mid) {
            counts[nums[i].second] += rightCount;
            temp[k++] = nums[i++];
        }
        
        // Remaining elements in right half
        while (j <= right) {
            temp[k++] = nums[j++];
        }
        
        // Copy back to original array
        for (int i = 0; i < temp.size(); i++) {
            nums[left + i] = temp[i];
        }
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        counts.resize(n, 0);
        
        // Create pairs of (value, original_index)
        vector<pair<int, int>> indexed(n);
        for (int i = 0; i < n; i++) {
            indexed[i] = {nums[i], i};
        }
        
        mergeSort(indexed, 0, n - 1);
        
        return counts;
    }
};

/*
 * STEP-BY-STEP VISUALIZATION
 * 
 * Input: [5, 2, 6, 1]
 * With indices: [(5,0), (2,1), (6,2), (1,3)]
 * counts = [0, 0, 0, 0]
 * 
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ DIVIDE PHASE                                                        │
 * ├─────────────────────────────────────────────────────────────────────┤
 * │                     [(5,0), (2,1), (6,2), (1,3)]                    │
 * │                              /          \                           │
 * │                   [(5,0), (2,1)]    [(6,2), (1,3)]                  │
 * │                      /    \            /    \                       │
 * │                  [(5,0)] [(2,1)]    [(6,2)] [(1,3)]                 │
 * └─────────────────────────────────────────────────────────────────────┘
 * 
 * ┌─────────────────────────────────────────────────────────────────────┐
 * │ MERGE PHASE (where counting happens)                                │
 * ├─────────────────────────────────────────────────────────────────────┤
 * │                                                                     │
 * │ MERGE [(5,0)] and [(2,1)]:                                         │
 * │   Compare: 2 < 5 → pick (2,1), rightCount = 1                      │
 * │   Now left half done, (5,0) gets rightCount=1                      │
 * │   counts[0] += 1 → counts = [1, 0, 0, 0]                           │
 * │   Result: [(2,1), (5,0)]                                           │
 * │                                                                     │
 * │ MERGE [(6,2)] and [(1,3)]:                                         │
 * │   Compare: 1 < 6 → pick (1,3), rightCount = 1                      │
 * │   Now right half done, (6,2) gets rightCount=1                     │
 * │   counts[2] += 1 → counts = [1, 0, 1, 0]                           │
 * │   Result: [(1,3), (6,2)]                                           │
 * │                                                                     │
 * │ MERGE [(2,1), (5,0)] and [(1,3), (6,2)]:                           │
 * │   Compare: 1 < 2 → pick (1,3), rightCount = 1                      │
 * │   Compare: 2 < 6 → pick (2,1), counts[1] += 1                      │
 * │   counts = [1, 1, 1, 0]                                            │
 * │   Compare: 5 < 6 → pick (5,0), counts[0] += 1                      │
 * │   counts = [2, 1, 1, 0]                                            │
 * │   Pick remaining (6,2), rightCount still 1 (already counted)       │
 * │   Result: [(1,3), (2,1), (5,0), (6,2)]                             │
 * │                                                                     │
 * │ FINAL: counts = [2, 1, 1, 0] ✓                                     │
 * └─────────────────────────────────────────────────────────────────────┘
 */

/*
 * WHY DO WE TRACK ORIGINAL INDICES?
 * 
 * After sorting, element positions change!
 * We need to know: "For this value, where should I update the count?"
 * 
 * Original: [5, 2, 6, 1]
 *            ↓  ↓  ↓  ↓
 * Index:     0  1  2  3
 * 
 * If we sort without tracking indices, we lose the mapping.
 * With pairs: [(5,0), (2,1), (6,2), (1,3)]
 * After sort: [(1,3), (2,1), (5,0), (6,2)]
 * 
 * Now when we count for value 5, we know to update counts[0]
 */

/*
 * COMPLEXITY ANALYSIS
 * 
 * Time:  O(n log n) - Standard merge sort
 * Space: O(n) - For temp array and indexed pairs
 * 
 * Comparison with other approaches:
 * ┌────────────────────┬────────────┬─────────┐
 * │ Approach           │ Time       │ Space   │
 * ├────────────────────┼────────────┼─────────┤
 * │ Brute Force        │ O(n²)      │ O(1)    │
 * │ Merge Sort         │ O(n log n) │ O(n)    │
 * │ Binary Index Tree  │ O(n log n) │ O(n)    │
 * │ Segment Tree       │ O(n log n) │ O(n)    │
 * └────────────────────┴────────────┴─────────┘
 */

// Demo
int main() {
    Solution sol;
    
    vector<int> nums = {5, 2, 6, 1};
    vector<int> result = sol.countSmaller(nums);
    
    cout << "Input:  [5, 2, 6, 1]\n";
    cout << "Output: [";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]\n";
    
    // Expected: [2, 1, 1, 0]
    
    return 0;
}

/*
 * RELATED PROBLEMS (Same Pattern):
 * 
 * 1. Count Inversions in Array
 *    - Count pairs (i,j) where i < j but arr[i] > arr[j]
 * 
 * 2. Reverse Pairs (LeetCode 493)
 *    - Count pairs where i < j and nums[i] > 2*nums[j]
 * 
 * 3. Count of Range Sum (LeetCode 327)
 *    - Count subarrays with sum in given range
 * 
 * KEY TAKEAWAY:
 * Merge sort is useful for counting problems involving
 * "elements to the left/right satisfying some condition"
 * because during merge, relative positions are preserved.
 */

