/*
================================================================================
                    PATTERN 9: SUBSET SUM
================================================================================

When to use:
- Determine if subset with target sum exists
- Count subsets with target sum
- Partition array into subsets

Closely related to 0/1 Knapsack.

LeetCode Problems:
- 416. Partition Equal Subset Sum
- 494. Target Sum
- 698. Partition to K Equal Sum Subsets

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Subset Sum Exists (Classic) ⭐
────────────────────────────────────────
Check if subset with target sum exists.

dp[i] = true if sum i is achievable

Example:
Input: nums = [1, 2, 3, 4], target = 5
Output: true
Explanation: The subset [1, 4] sums to 5.
Draw the dp table:
0 1 2 3 4 5
1 1 0 0 0 0
2 1 0 1 0 0
3 1 0 1 1 0
4 1 0 1 1 1

Time: O(n * target) | Space: O(target)
*/
bool subsetSumExists(vector<int>& nums, int target) {
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    
    for (int num : nums) {
        for (int j = target; j >= num; j--) { // BACKWARDS! (because we can reuse the same element)
            dp[j] = dp[j] || dp[j - num];
        }
    }
    
    return dp[target];
}


/*
PROBLEM 2: Count Subsets with Sum (Classic)
───────────────────────────────────────────
Count subsets that sum to target.

Time: O(n * target) | Space: O(target)
*/
int countSubsetSum(vector<int>& nums, int target) {
    vector<int> dp(target + 1, 0);
    dp[0] = 1;
    
    for (int num : nums) {
        for (int j = target; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }
    
    return dp[target];
}


/*
PROBLEM 3: Partition Equal Subset Sum (LeetCode 416) ⭐
──────────────────────────────────────────────────────
Can array be partitioned into two equal sum subsets?

Time: O(n * sum) | Space: O(sum)
*/
bool canPartition(vector<int>& nums) {
    int sum = 0;
    for (int num : nums) sum += num;
    
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
PROBLEM 4: Target Sum (LeetCode 494)
────────────────────────────────────
Assign + or - to reach target. Count ways.

P - N = target, P + N = sum
=> P = (sum + target) / 2

Count subsets with sum P.

Time: O(n * sum) | Space: O(sum)
*/
int findTargetSumWays(vector<int>& nums, int target) {
    int sum = 0;
    for (int num : nums) sum += num;
    
    if ((sum + target) % 2 != 0 || sum + target < 0) return 0;
    
    int P = (sum + target) / 2;
    vector<int> dp(P + 1, 0);
    dp[0] = 1;
    
    for (int num : nums) {
        for (int j = P; j >= num; j--) {
            dp[j] += dp[j - num];
        }
    }
    
    return dp[P];
}


/*
PROBLEM 5: Partition to K Equal Sum Subsets (LeetCode 698)
──────────────────────────────────────────────────────────
Can array be partitioned into k equal sum subsets?

Bitmask DP or backtracking.

Time: O(n * 2^n) | Space: O(2^n)
*/
bool canPartitionKSubsets(vector<int>& nums, int k) {
    int sum = 0;
    for (int num : nums) sum += num;
    
    if (sum % k != 0) return false;
    int target = sum / k;
    
    int n = nums.size();
    sort(nums.rbegin(), nums.rend());
    
    if (nums[0] > target) return false;
    
    vector<int> buckets(k, 0);
    
    function<bool(int)> backtrack = [&](int idx) -> bool {
        if (idx == n) return true;
        
        for (int i = 0; i < k; i++) {
            if (buckets[i] + nums[idx] <= target) {
                buckets[i] += nums[idx];
                if (backtrack(idx + 1)) return true;
                buckets[i] -= nums[idx];
            }
            
            if (buckets[i] == 0) break;  // Pruning
        }
        
        return false;
    };
    
    return backtrack(0);
}


/*
PROBLEM 6: Minimum Difference Partition
───────────────────────────────────────
Partition into two subsets with minimum difference.

Find max sum <= total/2.
Answer = total - 2 * maxSum.

Time: O(n * sum) | Space: O(sum)
*/
int minimumDifference(vector<int>& nums) {
    int sum = 0;
    for (int num : nums) sum += num;
    
    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    
    for (int num : nums) {
        for (int j = target; j >= num; j--) {
            dp[j] = dp[j] || dp[j - num];
        }
    }
    
    for (int j = target; j >= 0; j--) {
        if (dp[j]) return sum - 2 * j;
    }
    
    return sum;
}


/*
PROBLEM 7: Number of Subsets with Given Difference
──────────────────────────────────────────────────
Count subsets where S1 - S2 = diff.

S1 - S2 = diff, S1 + S2 = sum
=> S1 = (sum + diff) / 2

Time: O(n * sum) | Space: O(sum)
*/
int countSubsetsWithDiff(vector<int>& nums, int diff) {
    int sum = 0;
    for (int num : nums) sum += num;
    
    if ((sum + diff) % 2 != 0 || sum + diff < 0) return 0;
    
    int target = (sum + diff) / 2;
    return countSubsetSum(nums, target);
}


/*
PROBLEM 8: Fair Division of Cookies (LeetCode 2305)
───────────────────────────────────────────────────
Distribute cookies to k people, minimize max sum.

Time: O(k * 3^n) | Space: O(k * 2^n)
*/
int distributeCookies(vector<int>& cookies, int k) {
    int n = cookies.size();
    
    // Precompute subset sums
    vector<int> subsetSum(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subsetSum[mask] += cookies[i];
            }
        }
    }
    
    // dp[p][mask] = min max when distributing mask to first p people
    vector<vector<int>> dp(k + 1, vector<int>(1 << n, INT_MAX));
    dp[0][0] = 0;
    
    for (int p = 0; p < k; p++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[p][mask] == INT_MAX) continue;
            
            int remaining = ((1 << n) - 1) ^ mask;
            for (int sub = remaining; sub > 0; sub = (sub - 1) & remaining) {
                int newMask = mask | sub;
                dp[p + 1][newMask] = min(dp[p + 1][newMask], 
                                        max(dp[p][mask], subsetSum[sub]));
            }
        }
    }
    
    return dp[k][(1 << n) - 1];
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Subset Sum Pattern ===\n\n";
    
    // Subset Sum Exists
    vector<int> nums1 = {3, 34, 4, 12, 5, 2};
    cout << "1. Subset sum 9 exists: " << (subsetSumExists(nums1, 9) ? "Yes" : "No") << "\n";
    
    // Count Subsets
    vector<int> nums2 = {1, 2, 3, 3};
    cout << "2. Count subsets sum 6: " << countSubsetSum(nums2, 6) << "\n";
    
    // Partition Equal Subset
    vector<int> nums3 = {1, 5, 11, 5};
    cout << "3. Can partition [1,5,11,5]: " << (canPartition(nums3) ? "Yes" : "No") << "\n";
    
    // Target Sum
    vector<int> nums4 = {1, 1, 1, 1, 1};
    cout << "4. Target sum ways (target=3): " << findTargetSumWays(nums4, 3) << "\n";
    
    // Partition K Subsets
    vector<int> nums5 = {4, 3, 2, 3, 5, 2, 1};
    cout << "5. Can partition into 4: " << (canPartitionKSubsets(nums5, 4) ? "Yes" : "No") << "\n";
    
    // Minimum Difference
    vector<int> nums6 = {1, 6, 11, 5};
    cout << "6. Min partition diff: " << minimumDifference(nums6) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

SUBSET SUM TEMPLATE:
    dp[0] = true (or 1 for counting)
    for num in nums:
        for j = target down to num:  // BACKWARDS!
            dp[j] = dp[j] || dp[j - num]

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Transform                                      |
+───────────────────────────────+────────────────────────────────────────────────+
| Subset sum exists             | Direct subset sum                              |
| Equal partition               | Target = sum / 2                               |
| Target sum +/-                | Target = (sum + target) / 2                    |
| Min partition diff            | Find max sum <= sum / 2                        |
| K equal subsets               | Backtracking or bitmask DP                     |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

