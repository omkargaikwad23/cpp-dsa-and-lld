/*
================================================================================
                    BACKTRACKING - COMBINATION SUM VARIATIONS
================================================================================

Find combinations that sum to a target.
Multiple variations based on:
- Can elements be reused?
- Are there duplicates in input?
- Fixed count of elements?

Time: Varies | Space: O(target / min_element)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Combination Sum (LeetCode 39)
────────────────────────────────────────
Elements can be reused unlimited times. Find all unique combinations summing to target.

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]

Time: O(n^(target/min)) | Space: O(target/min)
*/
class CombinationSum {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(candidates, target, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& candidates, int remaining, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(current);
            return;
        }
        
        if (remaining < 0) return;
        
        for (int i = start; i < candidates.size(); i++) {
            current.push_back(candidates[i]);
            // Start from i (not i+1) to allow reuse
            backtrack(candidates, remaining - candidates[i], i, current, result);
            current.pop_back();
        }
    }
};


/*
PROBLEM 2: Combination Sum II (LeetCode 40)
───────────────────────────────────────────
Each element used at most once. Input may have duplicates. Find unique combinations.

Input: candidates = [10,1,2,7,6,1,5], target = 8
Output: [[1,1,6],[1,2,5],[1,7],[2,6]]

Key: Sort + skip duplicates at same level

Time: O(2^n) | Space: O(n)
*/
class CombinationSumII {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());  // Sort for duplicate handling
        vector<vector<int>> result;
        vector<int> current;
        backtrack(candidates, target, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& candidates, int remaining, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(current);
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            // Pruning: remaining candidates too large
            if (candidates[i] > remaining) break;
            
            // Skip duplicates at same recursion level
            if (i > start && candidates[i] == candidates[i - 1]) continue;
            
            current.push_back(candidates[i]);
            backtrack(candidates, remaining - candidates[i], i + 1, current, result);
            current.pop_back();
        }
    }
};


/*
PROBLEM 3: Combination Sum III (LeetCode 216)
─────────────────────────────────────────────
Find k numbers from 1-9 that sum to n. Each number used at most once.

Input: k = 3, n = 7
Output: [[1,2,4]]

Time: O(C(9,k)) | Space: O(k)
*/
class CombinationSumIII {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(k, n, 1, current, result);
        return result;
    }
    
private:
    void backtrack(int k, int remaining, int start,
                   vector<int>& current, vector<vector<int>>& result) {
        if (current.size() == k) {
            if (remaining == 0) {
                result.push_back(current);
            }
            return;
        }
        
        // Pruning
        if (remaining < 0) return;
        if (9 - start + 1 < k - current.size()) return;  // Not enough numbers left
        
        for (int i = start; i <= 9; i++) {
            if (i > remaining) break;  // Early termination
            
            current.push_back(i);
            backtrack(k, remaining - i, i + 1, current, result);
            current.pop_back();
        }
    }
};


/*
PROBLEM 4: Combination Sum IV (LeetCode 377)
────────────────────────────────────────────
Count permutations (order matters) that sum to target. (Better solved with DP)

Input: nums = [1,2,3], target = 4
Output: 7 (1111, 112, 121, 211, 22, 13, 31)

Note: This is actually a DP problem (order matters = not backtracking)
*/
int combinationSum4(vector<int>& nums, int target) {
    vector<unsigned int> dp(target + 1, 0);
    dp[0] = 1;
    
    for (int i = 1; i <= target; i++) {
        for (int num : nums) {
            if (num <= i) {
                dp[i] += dp[i - num];
            }
        }
    }
    
    return dp[target];
}


/*
PROBLEM 5: Target Sum (LeetCode 494)
────────────────────────────────────
Assign +/- to each number to reach target sum.

Input: nums = [1,1,1,1,1], target = 3
Output: 5 (-1+1+1+1+1, +1-1+1+1+1, +1+1-1+1+1, +1+1+1-1+1, +1+1+1+1-1)

Time: O(2^n) backtracking, O(n*sum) DP | Space: O(n)
*/
class TargetSum {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        return backtrack(nums, target, 0, 0);
    }
    
private:
    int backtrack(vector<int>& nums, int target, int index, int currentSum) {
        if (index == nums.size()) {
            return currentSum == target ? 1 : 0;
        }
        
        // Try + and -
        int add = backtrack(nums, target, index + 1, currentSum + nums[index]);
        int subtract = backtrack(nums, target, index + 1, currentSum - nums[index]);
        
        return add + subtract;
    }
};

// Memoized version
class TargetSumMemo {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<string, int> memo;
        return backtrack(nums, target, 0, 0, memo);
    }
    
private:
    int backtrack(vector<int>& nums, int target, int index, int currentSum,
                  unordered_map<string, int>& memo) {
        if (index == nums.size()) {
            return currentSum == target ? 1 : 0;
        }
        
        string key = to_string(index) + "," + to_string(currentSum);
        if (memo.count(key)) return memo[key];
        
        int result = backtrack(nums, target, index + 1, currentSum + nums[index], memo)
                   + backtrack(nums, target, index + 1, currentSum - nums[index], memo);
        
        memo[key] = result;
        return result;
    }
};


/*
PROBLEM 6: Partition Equal Subset Sum (LeetCode 416)
────────────────────────────────────────────────────
Can array be partitioned into two subsets with equal sum?

Input: nums = [1,5,11,5]
Output: true ([1,5,5] and [11])

Time: O(n * sum) DP | Space: O(sum)
*/
bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (int n : nums) sum += n;
    
    if (sum % 2 != 0) return false;
    
    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    
    for (int num : nums) {
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }
    
    return dp[target];
}


/*
PROBLEM 7: Partition to K Equal Sum Subsets (LeetCode 698)
──────────────────────────────────────────────────────────
Can array be partitioned into k subsets with equal sum?

Input: nums = [4,3,2,3,5,2,1], k = 4
Output: true ([5], [1,4], [2,3], [2,3])

Time: O(k * 2^n) | Space: O(n)
*/
class PartitionKSubsets {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int sum = 0;
        for (int n : nums) sum += n;
        
        if (sum % k != 0) return false;
        
        int target = sum / k;
        sort(nums.rbegin(), nums.rend());  // Sort descending for pruning
        
        if (nums[0] > target) return false;
        
        vector<int> buckets(k, 0);
        return backtrack(nums, buckets, 0, target);
    }
    
private:
    bool backtrack(vector<int>& nums, vector<int>& buckets, int index, int target) {
        if (index == nums.size()) {
            return true;  // All numbers placed
        }
        
        unordered_set<int> tried;  // Avoid trying same bucket value twice
        
        for (int i = 0; i < buckets.size(); i++) {
            if (tried.count(buckets[i])) continue;  // Skip duplicate bucket states
            if (buckets[i] + nums[index] > target) continue;  // Pruning
            
            tried.insert(buckets[i]);
            buckets[i] += nums[index];
            
            if (backtrack(nums, buckets, index + 1, target)) {
                return true;
            }
            
            buckets[i] -= nums[index];
        }
        
        return false;
    }
};


/*
PROBLEM 8: Fair Distribution of Cookies (LeetCode 2305)
───────────────────────────────────────────────────────
Distribute cookies to k children, minimize maximum cookies any child gets.

Input: cookies = [8,15,10,20,8], k = 2
Output: 31

Time: O(k^n) | Space: O(k)
*/
class FairDistribution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
        vector<int> distribution(k, 0);
        int result = INT_MAX;
        backtrack(cookies, distribution, 0, k, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& cookies, vector<int>& distribution, 
                   int index, int k, int& result) {
        if (index == cookies.size()) {
            int maxCookies = *max_element(distribution.begin(), distribution.end());
            result = min(result, maxCookies);
            return;
        }
        
        // Pruning: current max already >= result
        int currentMax = *max_element(distribution.begin(), distribution.end());
        if (currentMax >= result) return;
        
        unordered_set<int> tried;
        for (int i = 0; i < k; i++) {
            if (tried.count(distribution[i])) continue;
            tried.insert(distribution[i]);
            
            distribution[i] += cookies[index];
            backtrack(cookies, distribution, index + 1, k, result);
            distribution[i] -= cookies[index];
        }
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Combination Sum Patterns ===\n\n";
    
    // 1. Combination Sum
    CombinationSum sol1;
    vector<int> cand1 = {2, 3, 6, 7};
    auto res1 = sol1.combinationSum(cand1, 7);
    cout << "1. Combinations summing to 7: " << res1.size() << " combinations\n";
    
    // 2. Combination Sum II
    CombinationSumII sol2;
    vector<int> cand2 = {10, 1, 2, 7, 6, 1, 5};
    auto res2 = sol2.combinationSum2(cand2, 8);
    cout << "2. Unique combinations summing to 8: " << res2.size() << " combinations\n";
    
    // 3. Combination Sum III
    CombinationSumIII sol3;
    auto res3 = sol3.combinationSum3(3, 7);
    cout << "3. k=3 numbers (1-9) summing to 7: " << res3.size() << " combinations\n";
    
    // 5. Target Sum
    TargetSum sol5;
    vector<int> nums5 = {1, 1, 1, 1, 1};
    cout << "5. Ways to reach target 3: " << sol5.findTargetSumWays(nums5, 3) << "\n";
    
    // 7. Partition K Subsets
    PartitionKSubsets sol7;
    vector<int> nums7 = {4, 3, 2, 3, 5, 2, 1};
    cout << "7. Can partition into 4 equal subsets: " 
         << (sol7.canPartitionKSubsets(nums7, 4) ? "true" : "false") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+──────────────────────────────+───────────────────────────────────────────────────+
| Problem                      | Key Difference                                    |
+──────────────────────────────+───────────────────────────────────────────────────+
| Combination Sum              | Can reuse elements (start from i, not i+1)        |
| Combination Sum II           | No reuse, has duplicates (sort + skip)            |
| Combination Sum III          | Fixed k elements from 1-9                         |
| Combination Sum IV           | Order matters = DP, not backtracking              |
| Target Sum                   | Binary choice (+/-), can use memoization          |
| Partition Equal Subset       | Find subset with sum = total/2 (DP preferred)    |
| Partition K Subsets          | k buckets, try placing each element               |
+──────────────────────────────+───────────────────────────────────────────────────+

PRUNING TECHNIQUES:
1. Sort + early break when candidate > remaining
2. Skip duplicates at same recursion level
3. Check if enough elements remaining
4. Track max/min bounds and prune if exceeded

================================================================================
*/

