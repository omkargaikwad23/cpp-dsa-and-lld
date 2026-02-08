/*
================================================================================
        BEST SUM - Find Shortest Combination (Unbounded, elements reusable)
================================================================================

Problem: Find the shortest combination of numbers that sum to target.
         Each number can be used multiple times.

Example: bestSum(8, [2, 3, 5]) → [3, 5] (length 2, not [2,2,2,2] length 4)
         bestSum(7, [2, 4])    → {} (impossible)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 1: Memoization (Top-Down)                                          │
│ Time: O(target × n × target)  |  Space: O(target²)                          │
└─────────────────────────────────────────────────────────────────────────────┘
*/

vector<int> bestSum(int target, vector<int>& nums, 
                    unordered_map<int, vector<int>>& memo) {
    if (memo.count(target)) return memo[target];
    if (target == 0) return {0};   // Marker: valid empty combination
    if (target < 0) return {};      // Invalid
    
    vector<int> shortest;
    
    for (int num : nums) {
        vector<int> result = bestSum(target - num, nums, memo);
        
        // Check if valid (contains marker 0 or has elements)
        if (!result.empty()) {
            // Build combination
            vector<int> combination;
            for (int x : result) {
                if (x != 0) combination.push_back(x);  // Skip marker
            }
            combination.push_back(num);
            
            // Update if shorter
            if (shortest.empty() || combination.size() < shortest.size()) {
                shortest = combination;
            }
        }
    }
    
    return memo[target] = shortest;
}

vector<int> bestSumMemo(int target, vector<int>& nums) {
    unordered_map<int, vector<int>> memo;
    return bestSum(target, nums, memo);
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 2: Tabulation (Bottom-Up) - Cleaner!                               │
│ Time: O(target × n × target)  |  Space: O(target²)                          │
└─────────────────────────────────────────────────────────────────────────────┘
*/

vector<int> bestSumTabu(int target, vector<int>& nums) {
    // dp[i] = shortest combination to make sum i (empty if impossible)
    vector<vector<int>> dp(target + 1);
    dp[0] = {0};  // Marker: sum 0 is achievable with empty combination
    
    for (int i = 0; i <= target; i++) {
        if (dp[i].empty()) continue;  // Can't reach sum i
        
        for (int num : nums) {
            if (i + num > target) continue;
            
            // Build new combination
            vector<int> combo;
            for (int x : dp[i]) {
                if (x != 0) combo.push_back(x);
            }
            combo.push_back(num);
            
            // Update if shorter or first valid
            if (dp[i + num].empty() || combo.size() < dp[i + num].size()) {
                dp[i + num] = combo;
            }
        }
    }
    
    // Remove marker if present
    vector<int>& result = dp[target];
    if (!result.empty() && result[0] == 0) {
        result.erase(result.begin());
    }
    
    return result;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ Solution 3: BFS - Most Intuitive for "Shortest"!                            │
│ Time: O(target × n)  |  Space: O(target)                                    │
└─────────────────────────────────────────────────────────────────────────────┘

Since we want SHORTEST, BFS naturally finds it first!
*/

vector<int> bestSumBFS(int target, vector<int>& nums) {
    if (target == 0) return {};
    
    queue<pair<int, vector<int>>> q;  // {current_sum, combination}
    unordered_set<int> visited;
    
    q.push({0, {}});
    visited.insert(0);
    
    while (!q.empty()) {
        auto [sum, combo] = q.front();
        q.pop();
        
        for (int num : nums) {
            int newSum = sum + num;
            
            if (newSum == target) {
                combo.push_back(num);
                return combo;  // BFS guarantees shortest!
            }
            
            if (newSum < target && !visited.count(newSum)) {
                visited.insert(newSum);
                vector<int> newCombo = combo;
                newCombo.push_back(num);
                q.push({newSum, newCombo});
            }
        }
    }
    
    return {};  // Not possible
}



void printResult(const string& label, vector<int>& result) {
    cout << label;
    if (result.empty()) {
        cout << "NOT POSSIBLE\n";
    } else {
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] << (i < result.size()-1 ? ", " : "");
        }
        cout << "] (length: " << result.size() << ")\n";
    }
}

int main() {
    cout << "=== Best Sum (Shortest Combination) ===\n\n";
    
    vector<int> nums1 = {2, 3, 5};
    vector<int> nums2 = {2, 4};
    vector<int> nums3 = {4, 10, 20, 25};
    
    // Test 1
    auto r1 = bestSumTabu(8, nums1);
    printResult("bestSum(8, [2,3,5]) = ", r1);
    cout << "Expected: [3,5] or [5,3]\n\n";
    
    // Test 2
    auto r2 = bestSumBFS(7, nums2);
    printResult("bestSum(7, [2,4]) = ", r2);
    cout << "Expected: NOT POSSIBLE\n\n";
    
    // Test 3
    auto r3 = bestSumTabu(100, nums3);
    printResult("bestSum(100, [4,10,20,25]) = ", r3);
    cout << "Expected: [25,25,25,25] (length 4)\n\n";
    
    return 0;
}

/*
================================================================================
                            COMPARISON
================================================================================

┌─────────────────┬────────────────────────┬─────────────────────┐
│ Approach        │ Time                   │ When to Use         │
├─────────────────┼────────────────────────┼─────────────────────┤
│ Memoization     │ O(target × n × target) │ When need the combo │
│ Tabulation      │ O(target × n × target) │ When need the combo │
│ BFS             │ O(target × n)          │ Shortest = BFS!     │
└─────────────────┴────────────────────────┴─────────────────────┘

KEY INSIGHT: When finding "shortest/minimum steps", BFS is often optimal!

================================================================================
*/
