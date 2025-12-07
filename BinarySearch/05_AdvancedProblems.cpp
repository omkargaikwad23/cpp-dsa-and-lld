/*
================================================================================
                    ADVANCED BINARY SEARCH PROBLEMS
================================================================================

Pattern 1: Find Peak Element
Pattern 2: Find in Mountain Array
Pattern 3: Median of Two Sorted Arrays
Pattern 4: Sqrt(x) and Nth Root
Pattern 5: Find K Closest Elements
Pattern 6: Random Pick with Weight
Pattern 7: H-Index II

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

/*
================================================================================
PATTERN 1: FIND PEAK ELEMENT
================================================================================
LeetCode: 162. Find Peak Element

Peak: Element strictly greater than its neighbors
Note: nums[-1] = nums[n] = -∞

Key Insight: If nums[mid] < nums[mid+1], peak exists on right
            (because we're going uphill and eventually hit boundary)

Time: O(log n), Space: O(1)
*/
int findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[mid + 1]) {
            // Going downhill, peak is at mid or left
            right = mid;
        } else {
            // Going uphill, peak is on right
            left = mid + 1;
        }
    }
    
    return left;
}
/*
Example: [1,2,1,3,5,6,4] → returns 5 (index of 6) 

Explanation:
- We start with left = 0 and right = 6
- We calculate mid = (0 + 6) / 2 = 3
- We check if nums[3] > nums[4] (3 > 5)
- Since 3 < 5, we move left to mid + 1 = 4
- We calculate mid = (4 + 6) / 2 = 5
- We check if nums[5] > nums[6] (6 > 4)
- Since 6 > 4, we move right to mid = 5
*/


/*
================================================================================
PATTERN 2: FIND IN MOUNTAIN ARRAY
================================================================================
LeetCode: 1095. Find in Mountain Array

Mountain Array: Strictly increasing then strictly decreasing
Given: target, find minimum index where arr[i] == target

Approach:
1. Find peak (max element)
2. Binary search in ascending part
3. If not found, binary search in descending part

Time: O(log n), Space: O(1)
*/
class MountainArray {
public:
    // Simulated mountain array interface
    vector<int> arr;
    MountainArray(vector<int>& a) : arr(a) {}
    int get(int idx) { return arr[idx]; }
    int length() { return arr.size(); }
};

int findInMountainArray(int target, MountainArray& mountainArr) {
    int n = mountainArr.length();
    
    // Step 1: Find peak index
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (mountainArr.get(mid) < mountainArr.get(mid + 1)) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    int peak = left;
    
    // Step 2: Search in ascending part [0, peak]
    left = 0; right = peak;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = mountainArr.get(mid);
        if (val == target) return mid;
        else if (val < target) left = mid + 1;
        else right = mid - 1;
    }
    
    // Step 3: Search in descending part [peak+1, n-1]
    left = peak + 1; right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int val = mountainArr.get(mid);
        if (val == target) return mid;
        else if (val > target) left = mid + 1;  // Descending!
        else right = mid - 1;
    }
    
    return -1;
}


/*
================================================================================
PATTERN 3: MEDIAN OF TWO SORTED ARRAYS ⭐⭐⭐ (Hard!)
================================================================================
LeetCode: 4. Median of Two Sorted Arrays

Problem: Find median of two sorted arrays in O(log(m+n))

Key Insight: Binary search on partition position
            Partition both arrays such that left half <= right half

Time: O(log(min(m,n))), Space: O(1)
*/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    // Ensure nums1 is smaller (binary search on smaller array)
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }
    
    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;
    
    while (left <= right) {
        int partitionX = left + (right - left) / 2; // partitionX is the partition index in nums1
        int partitionY = (m + n + 1) / 2 - partitionX; // partitionY is the partition index in nums2
        
        //if partitionX is 0 it means nothing is there on left side. Use -INF for maxLeftX
        //if partitionX is length of input then there is nothing on right side. Use +INF for minRightX
        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
        
        // similarly for nums2
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];
        
        // Check if valid partition
        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            // Found correct partition
            // if the combined length is even, then the median is the average of the max of the left and the min of the right
            // if the combined length is odd, then the median is the max of the left
            if ((m + n) % 2 == 0) {
                return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            } else {
                return max(maxLeftX, maxLeftY);
            }
        }
        else if (maxLeftX > minRightY) { //we are too far on right side for partitionX. Go on left side.
            right = partitionX - 1;  // Move left in nums1
        }
        else { //we are too far on left side for partitionX. Go on right side.
            left = partitionX + 1;   // Move right in nums1
        }
    }
    
    return 0.0;  // Should never reach here
}
/*
nums1: [1, 3]     nums2: [2]
Partition: nums1 takes 1 element, nums2 takes 1 element
Left half: [1, 2], Right half: [3]
Median = 2

nums1: [1, 2]     nums2: [3, 4]
Partition: nums1 takes 1, nums2 takes 1
Left: [1, 3] max=3, Right: [2, 4] min=2 → Invalid!
Adjust partition...
Final: Left [1, 2], Right [3, 4] → median = (2+3)/2 = 2.5
*/


/*
================================================================================
PATTERN 4: SQRT(X) AND NTH ROOT
================================================================================
LeetCode: 69. Sqrt(x)

Time: O(log x), Space: O(1)
*/
int mySqrt(int x) {
    if (x == 0) return 0;
    
    int left = 1, right = x;
    int result = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Use division to avoid overflow: mid * mid <= x → mid <= x / mid
        if (mid <= x / mid) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return result;
}

// Nth Root with precision
double nthRoot(int n, double x, double precision = 1e-7) {
    double left = 0, right = max(1.0, x);
    
    while (right - left > precision) {
        double mid = (left + right) / 2;
        
        if (pow(mid, n) < x) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    return left;
}


/*
================================================================================
PATTERN 5: FIND K CLOSEST ELEMENTS
================================================================================
LeetCode: 658. Find K Closest Elements

Problem: Find k closest elements to target in sorted array

Approach: Binary search for starting position of k-length window
Time: O(log(n-k) + k), Space: O(1) excluding output
*/
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int left = 0, right = arr.size() - k;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Compare distance from x to endpoints of window
        // If arr[mid+k] is closer to x than arr[mid], move right
        if (x - arr[mid] > arr[mid + k] - x) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return vector<int>(arr.begin() + left, arr.begin() + left + k);
}
// Example: arr = [1,2,3,4,5], k = 4, x = 3 → [1,2,3,4]


/*
================================================================================
PATTERN 6: RANDOM PICK WITH WEIGHT
================================================================================
LeetCode: 528. Random Pick with Weight

Problem: Pick index i with probability proportional to w[i]

Approach: Build prefix sum, binary search for random number
*/
class RandomPickWeight {
    vector<int> prefixSum;
    
public:
    RandomPickWeight(vector<int>& w) {
        prefixSum.resize(w.size());
        prefixSum[0] = w[0];
        for (int i = 1; i < w.size(); i++) {
            prefixSum[i] = prefixSum[i-1] + w[i];
        }
    }
    
    int pickIndex() {
        int target = rand() % prefixSum.back() + 1;  // [1, total]
        
        // Find first prefix sum >= target
        return lower_bound(prefixSum.begin(), prefixSum.end(), target) 
               - prefixSum.begin();
    }
};
/*
w = [1, 3, 2] → prefixSum = [1, 4, 6]
Random(1-6):
- 1 → index 0 (1/6 probability)
- 2,3,4 → index 1 (3/6 probability)
- 5,6 → index 2 (2/6 probability)
*/


/*
================================================================================
PATTERN 7: H-INDEX II
================================================================================
LeetCode: 275. H-Index II

H-Index: Maximum h such that h papers have at least h citations each
Given sorted citations array.

Time: O(log n), Space: O(1)
*/
int hIndex(vector<int>& citations) {
    int n = citations.size();
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // n - mid papers have >= citations[mid] citations
        if (citations[mid] >= n - mid) {
            right = mid - 1;  // Try for larger h
        } else {
            left = mid + 1;
        }
    }
    
    return n - left;
}
// Example: [0,1,3,5,6] → h = 3 (papers with 3,5,6 citations)


/*
================================================================================
PATTERN 8: GUESS NUMBER HIGHER OR LOWER
================================================================================
LeetCode: 374. Guess Number Higher or Lower

Classic binary search with API call instead of array access
*/
// Simulated API
int pick = 6;
int guess(int num) {
    if (num == pick) return 0;
    if (num > pick) return -1;
    return 1;
}

int guessNumber(int n) {
    int left = 1, right = n;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int result = guess(mid);
        
        if (result == 0) return mid;
        else if (result == -1) right = mid - 1;
        else left = mid + 1;
    }
    
    return -1;
}


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Advanced Binary Search Problems ===\n\n";
    
    // Pattern 1: Peak Element
    vector<int> arr1 = {1, 2, 1, 3, 5, 6, 4};
    cout << "1. Peak element index in [1,2,1,3,5,6,4]: " 
         << findPeakElement(arr1) << endl;
    
    // Pattern 2: Mountain Array
    vector<int> mountain = {1, 2, 3, 4, 5, 3, 1};
    MountainArray ma(mountain);
    cout << "2. Find 3 in mountain [1,2,3,4,5,3,1]: " 
         << findInMountainArray(3, ma) << endl;
    
    // Pattern 3: Median of Two Sorted Arrays
    vector<int> nums1 = {1, 3}, nums2 = {2};
    cout << "3. Median of [1,3] and [2]: " 
         << findMedianSortedArrays(nums1, nums2) << endl;
    
    // Pattern 4: Sqrt
    cout << "4. Sqrt(8): " << mySqrt(8) << endl;
    cout << "   Cube root of 27: " << nthRoot(3, 27) << endl;
    
    // Pattern 5: K Closest Elements
    vector<int> arr2 = {1, 2, 3, 4, 5};
    auto closest = findClosestElements(arr2, 4, 3);
    cout << "5. 4 closest to 3 in [1,2,3,4,5]: ";
    for (int x : closest) cout << x << " ";
    cout << endl;
    
    // Pattern 7: H-Index
    vector<int> citations = {0, 1, 3, 5, 6};
    cout << "7. H-Index of [0,1,3,5,6]: " << hIndex(citations) << endl;
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

PROBLEM TYPE              | KEY INSIGHT
--------------------------|---------------------------------------------
Peak Element              | Go towards higher neighbor
Mountain Array            | Find peak, then search both halves
Median of Two Arrays      | Binary search on partition position
Sqrt / Nth Root           | Binary search on answer with precision
K Closest Elements        | Binary search on window start position
Random Pick with Weight   | Prefix sum + binary search
H-Index                   | n - mid papers have >= citations[mid]

================================================================================
*/

