/*
Number of ways to partition an array into segments s.t each segment has atleast 2 negative numbers
solve and explain in C++ with a testcase dryrun
*/
#include <iostream>
#include <vector>

int countPartitionsWithTwoNegatives(std::vector<int>& arr) {
    int n = arr.size();
    if (n < 2) return 0;

    std::vector<int> dp(n + 1, 0);
    int negCount = 0;

    for (int i = 0; i < n; ++i) {
        negCount = 0;
        for (int j = i; j >= 0; --j) {
            if (arr[j] < 0) negCount++;
            if (negCount >= 2) {
                if (j == 0) {
                    // Entire segment from the start
                    dp[i + 1]++;
                } else {
                    dp[i + 1] += dp[j];
                }
            }
        }
    }
    return dp[n];
}

int main() {
    // Test case
    std::vector<int> arr = {1, -2, -1, 3, 4, -5, -6};
    int result = countPartitionsWithTwoNegatives(arr);
    std::cout << "Number of partitions: " << result << std::endl;
    return 0;
}