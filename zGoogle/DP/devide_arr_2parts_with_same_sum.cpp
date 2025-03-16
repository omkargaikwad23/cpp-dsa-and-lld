/*

https://leetcode.com/discuss/post/6536645/google-phone-screen-l4-by-anonymous_user-hbth/

An array with values is given. After removing an element, find whether the array can be divided into two parts, where the sum has to be equal and elements has to be continuous.

Eg: [3, 1, 1, 1, 7] -> removing 7 -> True. (3) & (1, 1, 1)
[1, 3, 1, 1, 7] -> removing 7 -> False, since the array can't be divided into two parts.

Follow-up: if the array is circular.
Eg: [1, 3, 1, 1, 7] -> removing 7 -> True, (1, 1, 1) & (3)

provide well written C++ solution for both the google interview questions
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to check if an array can be partitioned into two continuous parts with equal sum
bool canPartitionLinear(vector<int>& arr) {
    int totalSum = 0;
    for (int num : arr) totalSum += num;

    // Try removing each element and check for partitioning
    for (size_t i = 0; i < arr.size(); i++) {
        int newSum = totalSum - arr[i]; // Sum after removing element
        if (newSum % 2 != 0) continue;  // Must be even to split equally

        int halfSum = newSum / 2, currentSum = 0;
        for (size_t j = 0; j < arr.size(); j++) {
            if (j == i) continue; // Skip removed element
            currentSum += arr[j];
            if (currentSum == halfSum) return true; // Found valid partition
        }
    }
    return false;
}

bool canPartitionCircular(vector<int>& arr) {
    int n = arr.size();
    int totalSum = 0;

    for (int num : arr) totalSum += num;  // Step 1: Compute total sum

    for (int i = 0; i < n; i++) {
        int newSum = totalSum - arr[i];  // Step 2: Remove arr[i]
        if (newSum % 2 != 0) continue;  // If sum is odd, no valid partition
        int halfSum = newSum / 2;

        // Step 3: Check if there's a continuous subarray sum == halfSum
        unordered_set<int> prefixSums;
        int currentSum = 0;

        // Step 4: Sliding window in circular array (max `2n - 1` iterations)
        for (int j = 0; j < 2 * n - 1; j++) {
            int idx = j % n;  // Circular index
            if (idx == i) continue;  // Skip removed element
            
            currentSum += arr[idx];

            // If we found halfSum directly
            if (currentSum == halfSum) return true;

            // If currentSum - halfSum exists in prefixSums, we found a valid range
            if (prefixSums.count(currentSum - halfSum)) return true;

            // Insert current prefix sum
            prefixSums.insert(currentSum);

            // To maintain a valid window, remove old elements
            if (j >= n - 1) {
                int removeIdx = (j - (n - 1)) % n;
                if (removeIdx != i) currentSum -= arr[removeIdx];
            }
        }
    }
    return false;
}

int main() {
    vector<int> arr1 = {3, 1, 1, 1, 7};
    vector<int> arr2 = {1, 3, 1, 1, 7};

    cout << "Linear case 1: " << (canPartitionLinear(arr1) ? "True" : "False") << endl;
    cout << "Linear case 2: " << (canPartitionLinear(arr2) ? "True" : "False") << endl;

    cout << "Circular case 1: " << (canPartitionCircular(arr1) ? "True" : "False") << endl;
    cout << "Circular case 2: " << (canPartitionCircular(arr2) ? "True" : "False") << endl;

    return 0;
}
