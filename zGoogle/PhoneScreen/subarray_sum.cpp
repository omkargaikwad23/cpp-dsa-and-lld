#include <iostream>
#include <vector>

using namespace std;

/**
 * Correct implementation: Returns the sum of all special subarray elements
 * Special subarray: Any subarray forming AP with difference ±1.
 */

int sumOfSpecialSubarrays(const vector<int>& arr) {
    int totalSum = 0;
    
    for (size_t i = 0; i < arr.size(); ++i) {
        int currentSum = arr[i]; // Initialize with the single element
        totalSum += currentSum;

        // This will track consecutive elements forming an AP
        for (size_t j = i + 1; j < arr.size(); ++j) {
            int diff = arr[j] - arr[j - 1];

            // Check if the difference continues with ±1
            if (diff == 1 || diff == -1) {
                currentSum += arr[j];
                totalSum += currentSum; // Add current sum of valid AP sequence
            } else {
                break; // Break if the difference is not maintained
            }
        }
    }
    
    return totalSum;
}


/**
 * Linear runtime complexity implementation:
 * Sum of all AP subarrays with difference ±1.
 */

 int sumOfSpecialSubarraysLinear(const vector<int>& arr) {
    if (arr.empty()) return 0;

    int totalSum = arr[0]; // Start with the first element
    int currentSum = arr[0];
    int currentLength = 1; // To track the special AP length

    for (size_t i = 1; i < arr.size(); ++i) {
        int diff = arr[i] - arr[i - 1];

        // Continue the AP with difference ±1
        if (diff == 1 || diff == -1) {
            currentLength++;
            currentSum += arr[i] * currentLength; // Add the element with the extended length
        } else {
            // Reset current AP segment details
            currentLength = 1;
            currentSum = arr[i];
        }

        // Add current sum contribution to total sum
        totalSum += currentSum;
    }

    return totalSum;
}

int main() {
    vector<int> arr = {2, 3, 4, 3};
    int result = sumOfSpecialSubarrays(arr);
    cout << "The sum of all special subarrays is: " << result << endl;
    return 0;
}