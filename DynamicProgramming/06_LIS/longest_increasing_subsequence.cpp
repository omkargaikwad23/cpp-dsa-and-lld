/*
================================================================================
                    PATTERN 6: LONGEST INCREASING SUBSEQUENCE (LIS)
================================================================================

When to use:
- Find longest subsequence in increasing/decreasing order
- Envelope/box stacking problems
- Sequence chain problems

LeetCode Problems:
- 300. Longest Increasing Subsequence
- 673. Number of Longest Increasing Subsequence
- 354. Russian Doll Envelopes

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Longest Increasing Subsequence (LeetCode 300) ⭐ CLASSIC
───────────────────────────────────────────────────────────────────

O(n²) DP Approach:
dp[i] = length of LIS ending at index i
dp[i] = max(dp[j] + 1) for all j < i where nums[j] < nums[i]

O(n log n) Binary Search Approach:
Maintain a "tails" array where tails[i] = smallest tail of all LIS of length i+1.
*/

// O(n²) approach
int lengthOfLIS_N2(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    int maxLen = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        maxLen = max(maxLen, dp[i]);
    }
    
    return maxLen;
}

// O(n log n) approach ⭐ OPTIMAL
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;
    
    for (int num : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if (it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }
    
    return tails.size();
}


/*
PROBLEM 2: Print LIS
────────────────────
Reconstruct the actual LIS.

Time: O(n²) | Space: O(n)
*/
vector<int> printLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1), parent(n, -1);
    int maxLen = 1, maxIdx = 0;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxIdx = i;
        }
    }
    
    // Reconstruct
    vector<int> lis;
    while (maxIdx != -1) {
        lis.push_back(nums[maxIdx]);
        maxIdx = parent[maxIdx];
    }
    reverse(lis.begin(), lis.end());
    
    return lis;
}


/*
PROBLEM 3: Number of Longest Increasing Subsequence (LeetCode 673)
──────────────────────────────────────────────────────────────────
Count all LIS of maximum length.

Track both length and count at each position.

Time: O(n²) | Space: O(n)
*/
int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> len(n, 1), cnt(n, 1);
    int maxLen = 1;
    
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                } else if (len[j] + 1 == len[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }
        maxLen = max(maxLen, len[i]);
    }
    
    int result = 0;
    for (int i = 0; i < n; i++) {
        if (len[i] == maxLen) result += cnt[i];
    }
    
    return result;
}


/*
PROBLEM 4: Russian Doll Envelopes (LeetCode 354)
────────────────────────────────────────────────
Sort by width ascending, height descending.
Then LIS on heights.

Example:
envelopes = [[5,4],[6,4],[6,7],[2,3]]

Sorted (width↑, height↓ for same width):
[[2,3], [5,4], [6,7], [6,4]]

Heights to process: [3, 4, 7, 4]

i = 0, h = 3, tails = [3]          ✓
i = 1, h = 4, tails = [3, 4]       ✓
i = 2, h = 7, tails = [3, 4, 7]    ✓
i = 3, h = 4, tails = [3, 4, 7]    ← h=4 (not 6), 4 replaces 4 (no change)

return 3 ✓

Time: O(n log n) | Space: O(n)
*/
int maxEnvelopes(vector<vector<int>>& envelopes) {
    // Sort by width ascending, then height descending
    // Prevents picking multiple same-width envelopes in LIS (same width, different height)
    sort(envelopes.begin(), envelopes.end(), [](auto& a, auto& b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    });
    
    // LIS on heights
    vector<int> tails;
    for (auto& env : envelopes) {
        int h = env[1];
        auto it = lower_bound(tails.begin(), tails.end(), h);
        if (it == tails.end()) {
            tails.push_back(h);
        } else {
            *it = h;
        }
    }
    
    return tails.size();
}


/*
PROBLEM 5: Longest Increasing Path in Matrix (LeetCode 329)
───────────────────────────────────────────────────────────
Find longest increasing path in 2D grid.

DFS + Memoization. No need for visited since strictly increasing.

Time: O(m*n) | Space: O(m*n)
*/
class Solution {
    vector<vector<int>> memo;
    int m, n;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    int dfs(vector<vector<int>>& matrix, int i, int j) {
        if (memo[i][j] != 0) return memo[i][j];
        
        int maxPath = 1;
        for (auto& [di, dj] : dirs) {
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < m && nj >= 0 && nj < n 
                && matrix[ni][nj] > matrix[i][j]) {
                maxPath = max(maxPath, 1 + dfs(matrix, ni, nj));
            }
        }
        
        return memo[i][j] = maxPath;
    }
    
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        m = matrix.size(); n = matrix[0].size();
        memo.assign(m, vector<int>(n, 0));
        
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result = max(result, dfs(matrix, i, j));
            }
        }
        
        return result;
    }
};


/*
PROBLEM 6: Minimum Number of Removals to Make Mountain Array (LeetCode 1671)
────────────────────────────────────────────────────────────────────────────
Mountain: increases then decreases, length >= 3.
Find min removals to make mountain.

LIS from left + LDS from right, both > 1.
Answer = n - max(LIS[i] + LDS[i] - 1)

Time: O(n²) or O(n log n) | Space: O(n)
*/
int minimumMountainRemovals(vector<int>& nums) {
    int n = nums.size();
    
    // LIS from left
    vector<int> lis(n, 1);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }
    
    // LDS from right (LIS in reverse)
    vector<int> lds(n, 1);
    for (int i = n - 2; i >= 0; i--) {
        for (int j = n - 1; j > i; j--) {
            if (nums[j] < nums[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }
    
    int maxMountain = 0;
    for (int i = 1; i < n - 1; i++) {
        if (lis[i] > 1 && lds[i] > 1) {  // Valid peak
            maxMountain = max(maxMountain, lis[i] + lds[i] - 1);
        }
    }
    
    return n - maxMountain;
}


/*
PROBLEM 7: Longest String Chain (LeetCode 1048)
───────────────────────────────────────────────
word1 is predecessor of word2 if we can add one letter to word1.
Find longest chain.

Sort by length, then LIS-style DP with predecessor check.

Time: O(n * L² * log n) | Space: O(n)
*/
int longestStrChain(vector<string>& words) {
    sort(words.begin(), words.end(), [](auto& a, auto& b) {
        return a.size() < b.size();
    });
    
    unordered_map<string, int> dp;
    int maxLen = 1;
    
    for (const string& word : words) {
        dp[word] = 1;
        for (int i = 0; i < word.size(); i++) {
            string pred = word.substr(0, i) + word.substr(i + 1);
            if (dp.count(pred)) {
                dp[word] = max(dp[word], dp[pred] + 1);
            }
        }
        maxLen = max(maxLen, dp[word]);
    }
    
    return maxLen;
}


/*
PROBLEM 8: Maximum Height by Stacking Cuboids (LeetCode 1691)
─────────────────────────────────────────────────────────────
Sort dimensions of each cuboid, then sort cuboids.
LIS where cuboid j can stack on i if all dims of j >= i.

Time: O(n² * 3) | Space: O(n)
*/
int maxHeight(vector<vector<int>>& cuboids) {
    for (auto& c : cuboids) sort(c.begin(), c.end());
    sort(cuboids.begin(), cuboids.end());
    
    int n = cuboids.size();
    vector<int> dp(n);
    
    for (int i = 0; i < n; i++) {
        dp[i] = cuboids[i][2];  // Height when this is base
        for (int j = 0; j < i; j++) {
            if (cuboids[j][0] <= cuboids[i][0] &&
                cuboids[j][1] <= cuboids[i][1] &&
                cuboids[j][2] <= cuboids[i][2]) {
                dp[i] = max(dp[i], dp[j] + cuboids[i][2]);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== LIS Pattern ===\n\n";
    
    // LIS
    vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "1. LIS length (O(n²)): " << lengthOfLIS_N2(nums1) << "\n";
    cout << "   LIS length (O(n log n)): " << lengthOfLIS(nums1) << "\n";
    
    // Print LIS
    auto lis = printLIS(nums1);
    cout << "2. LIS: ";
    for (int x : lis) cout << x << " ";
    cout << "\n";
    
    // Count LIS
    vector<int> nums2 = {1, 3, 5, 4, 7};
    cout << "3. Number of LIS: " << findNumberOfLIS(nums2) << "\n";
    
    // Russian Dolls
    vector<vector<int>> env = {{5,4},{6,4},{6,7},{2,3}};
    cout << "4. Max envelopes: " << maxEnvelopes(env) << "\n";
    
    // String Chain
    vector<string> words = {"a","b","ba","bca","bda","bdca"};
    cout << "7. Longest string chain: " << longestStrChain(words) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

LIS O(n²):
    for i = 0 to n-1:
        for j = 0 to i-1:
            if nums[j] < nums[i]:
                dp[i] = max(dp[i], dp[j] + 1)

LIS O(n log n):
    tails = []
    for num in nums:
        pos = lower_bound(tails, num)
        if pos == end: append(num)
        else: tails[pos] = num
    return len(tails)

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Approach                                       |
+───────────────────────────────+────────────────────────────────────────────────+
| Basic LIS                     | O(n log n) with binary search                  |
| Count LIS                     | Track both length and count                    |
| Russian Dolls                 | Sort by w asc, h desc → LIS on heights         |
| Longest Path in Matrix        | DFS + memoization                              |
| Mountain Array                | LIS from left + LDS from right                 |
| String Chain                  | Sort by length + hashmap DP                    |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

