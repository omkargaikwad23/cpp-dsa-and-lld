#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Given an array and a number k, find the maximum consecutive occurrence of k
int maxConsecutiveOccurrence(const vector<int>& arr, int k) {
    int maxCount = 0, currentCount = 0;
    for (int num : arr) {
        if (num == k) {
            currentCount++;
            maxCount = max(maxCount, currentCount);
        } else {
            currentCount = 0;
        }
    }
    return maxCount;
}

// Given an array, find the maximum consecutive occurrence for each unique element
unordered_map<int, int> maxConsecutiveOccurrencesForEach(const vector<int>& arr) {
    unordered_map<int, int> result;
    for (size_t i = 0; i < arr.size(); i++) {
        int currentCount = 1;
        while (i + 1 < arr.size() && arr[i] == arr[i + 1]) {
            i++;
            currentCount++;
        }
        result[arr[i]] = max(result[arr[i]], currentCount);
    }
    return result;
}

// Find the maximum consecutive occurrence when allowed to change c elements to k
int maxConsecutiveWithModifications(const vector<int>& arr, int k, int c) {
    int maxCount = 0, left = 0, changes = 0;

    for (int right = 0; right < arr.size(); right++) {
        if (arr[right] != k) {
            changes++;
        }
        while (changes > c) {
            if (arr[left] != k) {
                changes--;
            }
            left++;
        }
        maxCount = max(maxCount, right - left + 1);
    }

    return maxCount;
}

int main() {
    vector<int> arr = {1, 2, 2, 3, 4, 4, 4, 2, 2};
    int k = 2;
    int c = 1;

    // Example usage
    cout << "Max consecutive occurrence of " << k << ": " << maxConsecutiveOccurrence(arr, k) << endl;
    
    auto occurrences = maxConsecutiveOccurrencesForEach(arr);
    for (auto [key, value] : occurrences) {
        cout << "Max consecutive occurrence of " << key << ": " << value << endl;
    }
    
    cout << "Max consecutive with " << c << " modifications to " << k << ": " << maxConsecutiveWithModifications(arr, k, c) << endl;

    return 0;
}