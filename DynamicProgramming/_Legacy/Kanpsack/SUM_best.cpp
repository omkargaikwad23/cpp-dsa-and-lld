#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

/*
 * BEST SUM - Shortest Combination Problem
 * ========================================
 * 
 * Problem: Find the shortest combination of numbers from array that sums to target.
 * You can use numbers from array any number of times.
 * 
 * Example:
 * Input: target = 100, array = [4, 10, 20, 25]
 * Output: [25, 25, 25, 25] (shortest combination: 4 numbers)
 * 
 * Approach: Memoized recursion
 * - Try each number in array
 * - Find best combination for remaining sum
 * - Keep track of shortest combination
 * 
 * Time Complexity: O(m^2 * n) where m = target sum, n = array size
 * Space Complexity: O(m^2) for memoization
 */

map<int, vector<int>> memo;

pair<vector<int>, bool> bestSum(int targetSum, vector<int>& numbers) {
    // Check memoization
    if (memo.find(targetSum) != memo.end()) {
        return {memo[targetSum], true};
    }
    
    // Base cases
    if (targetSum == 0) {
        return {{}, true};  // Empty combination is valid
    }
    
    if (targetSum < 0) {
        return {{}, false};  // Invalid: negative sum
    }
    
    vector<int> shortestCombination;
    
    // Try each number in the array
    for (int num : numbers) {
        int remainder = targetSum - num;
        pair<vector<int>, bool> result = bestSum(remainder, numbers);
        
        if (result.second == true) {
            // Valid combination found
            vector<int> combination = result.first;
            combination.push_back(num);  // Add current number
            
            // Update shortest combination if this is shorter
            if (shortestCombination.empty() || combination.size() < shortestCombination.size()) {
                shortestCombination = combination;
            }
        }
    }
    
    // Store result in memo
    bool isValid = !shortestCombination.empty();
    if (isValid) {
        memo[targetSum] = shortestCombination;
    }
    
    return {shortestCombination, isValid};
}

int main() {
    // Example: target = 100, numbers = [4, 10, 20, 25]
    int targetSum = 100;
    vector<int> numbers = {4, 10, 20, 25};
    
    memo.clear();  // Clear memo for fresh run
    pair<vector<int>, bool> result = bestSum(targetSum, numbers);
    
    cout << "Target: " << targetSum << endl;
    cout << "Numbers: [4, 10, 20, 25]" << endl;
    
    if (result.second == false || result.first.empty()) {
        cout << "Result: NOT POSSIBLE" << endl;
    } else {
        cout << "Shortest combination: ";
        for (int num : result.first) {
            cout << num << " ";
        }
        cout << endl;
        cout << "Length: " << result.first.size() << " numbers" << endl;
        cout << "Expected: 25 25 25 25 (4 numbers)" << endl;
    }
    
    return 0;
}