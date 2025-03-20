/*

https://leetcode.com/discuss/post/6536645/google-phone-screen-l4-by-anonymous_user-hbth/

An array with values is given. After removing an element, find whether the array can be divided into two parts, where the sum has to be equal and elements has to be continuous.

Eg: [3, 1, 1, 1, 7] -> removing 7 -> True. (3) & (1, 1, 1)
[1, 3, 1, 1, 7] -> removing 7 -> False, since the array can't be divided into two parts.

Follow-up: if the array is circular.
Eg: [1, 3, 1, 1, 7] -> removing 7 -> True, (1, 1, 1) & (3)

*/

#include <iostream>
#include <vector>
#include <numeric> // for std::accumulate

// Use individual using statements for specific functions or objects
using std::vector;
using std::accumulate;
using std::cout;
using std::endl;
using std::boolalpha;

bool canSplitNonCircular(const vector<int>& arr, int index) {
    int totalSum = accumulate(arr.begin(), arr.end(), 0) - arr[index];
    if (totalSum % 2 != 0) return false;
    int target = totalSum / 2;
    
    int currentSum = 0;
    for (int i = 0; i < arr.size(); ++i) {
        if (i == index) continue;
        currentSum += arr[i];
        if (currentSum == target) return true;
        if (currentSum > target) return false;
    }
    return false;
}

bool canSplitCircular(vector<int>& arr, int index) {
    int totalSum = accumulate(arr.begin(), arr.end(), 0) - arr[index];
    int n = arr.size();
    if (totalSum % 2 != 0) return false;
    int target = totalSum / 2;
    
    int currentSum = 0;
    for (int start = 0, end = 0, count = 0; count < 2 * (n - 1); ++end, ++count) {
        if (arr[end % n] == index) continue;
        currentSum += arr[end % n];
        while (currentSum > target) {
            if (start % n == index) {
                ++start;
                continue;
            }
            currentSum -= arr[start++ % n];
        }
        if (currentSum == target) return true;
    }
    
    return false;
}

bool canSplitArray(vector<int>& arr, bool isCircular) {
    for (int i = 0; i < arr.size(); ++i) {
        if (isCircular) {
            if (canSplitCircular(arr, i)) return true;
        } else {
            if (canSplitNonCircular(arr, i)) return true;
        }
    }
    return false;
}

int main() {
    vector<int> arr1 = {3, 1, 1, 1, 7};
    vector<int> arr2 = {1, 3, 1, 1, 7};
    
    cout << boolalpha; // Print 'true' or 'false' instead of 1 or 0.
    cout << "Non-circular result for [3, 1, 1, 1, 7]: " << canSplitArray(arr1, false) << endl;
    cout << "Circular result for [1, 3, 1, 1, 7]: " << canSplitArray(arr2, true) << endl;
    
    return 0;
}