/*
 * BINARY SEARCH PATTERNS - Learning Reference
 * 
 * KEY INSIGHT: Binary search works on any monotonic function (sorted property)
 * Time: O(log n) | Space: O(1) iterative, O(log n) recursive
 * 
 * PATTERN RECOGNITION:
 * - Use left <= right when searching for exact match
 * - Use left < right when searching for boundary/condition
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 1. CLASSIC BINARY SEARCH - Find exact element
// Returns index if found, -1 otherwise
int binarySearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;  // Prevents overflow
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}
// Example: arr = [1,3,5,7,9], target = 5 → returns 2

// 2. LOWER BOUND - First element >= target
// Same as std::lower_bound - insertion point for target
int lowerBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;
}
// Example: arr = [1,3,5,7,9], target = 4 → returns 2 (index of 5)
// Example: arr = [1,3,5,7,9], target = 5 → returns 2 (index of 5)

// 3. UPPER BOUND - First element > target
// Same as std::upper_bound
int upperBound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] <= target) left = mid + 1;
        else right = mid;
    }
    return left;
}
// Example: arr = [1,3,5,7,9], target = 5 → returns 3 (index of 7)

// 4. FIRST OCCURRENCE - First index of target (with duplicates)
int firstOccurrence(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            right = mid - 1;  // Keep searching left
        }
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}
// Example: arr = [1,2,2,2,3], target = 2 → returns 1

// 5. LAST OCCURRENCE - Last index of target (with duplicates)
int lastOccurrence(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1, result = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            result = mid;
            left = mid + 1;  // Keep searching right
        }
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}
// Example: arr = [1,2,2,2,3], target = 2 → returns 3

// 6. MISSING NUMBER IN SORTED ARRAY [0 to n]
// Array has n elements from 0 to n with one missing
int missingNumber(vector<int>& arr) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > mid) right = mid;  // Missing is on left
        else left = mid + 1;              // Missing is on right
    }
    return left;
}
// Example: arr = [0,1,2,3,5,6,7] → returns 4

// 7. SEARCH IN ROTATED SORTED ARRAY (No duplicates)
int searchRotated(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        
        // Left half is sorted
        if (arr[left] <= arr[mid]) {
            if (arr[left] <= target && target < arr[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }
        // Right half is sorted
        else {
            if (arr[mid] < target && target <= arr[right])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return -1;
}
// Example: arr = [4,5,6,7,0,1,2], target = 0 → returns 4

// 8. FIND MINIMUM IN ROTATED SORTED ARRAY
int findMinRotated(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[right]) left = mid + 1;
        else right = mid;
    }
    return arr[left];
}
// Example: arr = [4,5,6,7,0,1,2] → returns 0

// 9. PEAK ELEMENT - Element greater than neighbors
int findPeakElement(vector<int>& arr) {
    int left = 0, right = arr.size() - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] > arr[mid + 1]) right = mid;
        else left = mid + 1;
    }
    return left;
}
// Example: arr = [1,2,3,1] → returns 2 (index of peak 3)

// 10. SEARCH INSERT POSITION
// Find index where target should be inserted to keep array sorted
int searchInsert(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) left = mid + 1;
        else right = mid;
    }
    return left;  // Same as lower_bound
}
// Example: arr = [1,3,5,6], target = 4 → returns 2

// 11. SQRT - Integer square root
int mySqrt(int x) {
    if (x == 0) return 0;
    int left = 1, right = x, ans = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (mid <= x / mid) {  // Avoids overflow
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return ans;
}
// Example: x = 8 → returns 2 (sqrt(8) = 2.828...)

// STL BINARY SEARCH FUNCTIONS (C++)
void stlBinarySearch() {
    vector<int> v = {1, 2, 4, 4, 4, 5, 7};
    
    // binary_search - returns true/false
    bool found = binary_search(v.begin(), v.end(), 4);  // true
    
    // lower_bound - iterator to first element >= value
    auto lb = lower_bound(v.begin(), v.end(), 4);  // points to index 2
    
    // upper_bound - iterator to first element > value
    auto ub = upper_bound(v.begin(), v.end(), 4);  // points to index 5
    
    // Count occurrences = upper_bound - lower_bound
    int count = ub - lb;  // 3 (three 4's)
    
    // equal_range - returns pair of (lower_bound, upper_bound)
    auto range = equal_range(v.begin(), v.end(), 4);
}

// MAIN - Demo all functions
int main() {
    cout << "=== Binary Search Patterns Demo ===\n\n";
    
    // 1. Classic Binary Search
    vector<int> arr1 = {1, 3, 5, 7, 9};
    cout << "1. Binary Search [1,3,5,7,9], target=5: " << binarySearch(arr1, 5) << "\n";
    
    // 2. Lower Bound
    cout << "2. Lower Bound [1,3,5,7,9], target=4: " << lowerBound(arr1, 4) << "\n";
    
    // 3. Upper Bound
    cout << "3. Upper Bound [1,3,5,7,9], target=5: " << upperBound(arr1, 5) << "\n";
    
    // 4 & 5. First/Last Occurrence
    vector<int> arr2 = {1, 2, 2, 2, 3};
    cout << "4. First Occurrence [1,2,2,2,3], target=2: " << firstOccurrence(arr2, 2) << "\n";
    cout << "5. Last Occurrence [1,2,2,2,3], target=2: " << lastOccurrence(arr2, 2) << "\n";
    
    // 6. Missing Number
    vector<int> arr3 = {0, 1, 2, 3, 5, 6, 7};
    cout << "6. Missing Number [0,1,2,3,5,6,7]: " << missingNumber(arr3) << "\n";
    
    // 7. Rotated Array Search
    vector<int> arr4 = {4, 5, 6, 7, 0, 1, 2};
    cout << "7. Search Rotated [4,5,6,7,0,1,2], target=0: " << searchRotated(arr4, 0) << "\n";
    
    // 8. Find Min in Rotated
    cout << "8. Find Min Rotated [4,5,6,7,0,1,2]: " << findMinRotated(arr4) << "\n";
    
    // 9. Peak Element
    vector<int> arr5 = {1, 2, 3, 1};
    cout << "9. Peak Element [1,2,3,1]: " << findPeakElement(arr5) << "\n";
    
    // 10. Search Insert Position
    vector<int> arr6 = {1, 3, 5, 6};
    cout << "10. Search Insert [1,3,5,6], target=4: " << searchInsert(arr6, 4) << "\n";
    
    // 11. Integer Sqrt
    cout << "11. Sqrt(8): " << mySqrt(8) << "\n";
    
    return 0;
}

/*
 * CHEAT SHEET:
 * ┌─────────────────────────────────────────────────────────────┐
 * │ Pattern                  │ Condition         │ Loop Type    │
 * ├─────────────────────────────────────────────────────────────┤
 * │ Exact match              │ left <= right     │ 3-way split  │
 * │ Lower/Upper bound        │ left < right      │ 2-way split  │
 * │ First/Last occurrence    │ left <= right     │ save result  │
 * │ Rotated array            │ left <= right     │ check halves │
 * └─────────────────────────────────────────────────────────────┘
 * 
 * TIP: mid = left + (right - left) / 2  prevents integer overflow
 */

