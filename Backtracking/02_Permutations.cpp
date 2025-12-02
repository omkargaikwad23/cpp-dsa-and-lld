/*
================================================================================
                    BACKTRACKING - PERMUTATIONS
================================================================================

Generate all possible orderings of elements.
For n distinct elements, there are n! permutations.

Key: Each element must be used exactly once.
Use "visited/used" array to track which elements are in current permutation.

Time: O(n * n!) | Space: O(n)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Permutations (LeetCode 46)
─────────────────────────────────────
Generate all permutations of distinct integers.

Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Time: O(n * n!) | Space: O(n)
*/
class Permutations {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(nums, used, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, vector<bool>& used, 
                   vector<int>& current, vector<vector<int>>& result) {
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            
            used[i] = true;
            current.push_back(nums[i]);
            backtrack(nums, used, current, result);
            current.pop_back();
            used[i] = false;
        }
    }
};

// Alternative: Swap-based approach (no extra space for current)
class PermutationsSwap {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        backtrack(nums, 0, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<vector<int>>& result) {
        if (start == nums.size()) {
            result.push_back(nums);
            return;
        }
        
        for (int i = start; i < nums.size(); i++) {
            swap(nums[start], nums[i]);
            backtrack(nums, start + 1, result);
            swap(nums[start], nums[i]);  // Backtrack
        }
    }
};


/*
PROBLEM 2: Permutations II - With Duplicates (LeetCode 47)
──────────────────────────────────────────────────────────
Generate unique permutations (input may have duplicates).

Input: nums = [1,1,2]
Output: [[1,1,2],[1,2,1],[2,1,1]]

Key: Sort + skip duplicates (same value at same level if previous not used)

Time: O(n * n!) | Space: O(n)
*/
class PermutationsII {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // Sort to handle duplicates
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(nums, used, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, vector<bool>& used,
                   vector<int>& current, vector<vector<int>>& result) {
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            
            // Skip duplicates: if same as previous AND previous is not used
            // (means we're at same recursion level, duplicate would create same permutation)
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;
            
            used[i] = true;
            current.push_back(nums[i]);
            backtrack(nums, used, current, result);
            current.pop_back();
            used[i] = false;
        }
    }
};


/*
PROBLEM 3: Next Permutation (LeetCode 31)
─────────────────────────────────────────
Find next lexicographically greater permutation.

Input: nums = [1,2,3]
Output: [1,3,2]

Input: nums = [3,2,1]
Output: [1,2,3] (wrap around)

Algorithm:
1. Find largest i where nums[i] < nums[i+1] (rightmost ascending pair)
2. Find largest j where nums[j] > nums[i]
3. Swap nums[i] and nums[j]
4. Reverse suffix after i

Time: O(n) | Space: O(1)
*/
void nextPermutation(vector<int>& nums) {
    int n = nums.size();
    int i = n - 2;
    
    // Step 1: Find first decreasing element from right
    while (i >= 0 && nums[i] >= nums[i + 1]) {
        i--;
    }
    
    if (i >= 0) {
        // Step 2: Find smallest element greater than nums[i] from right
        int j = n - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        // Step 3: Swap
        swap(nums[i], nums[j]);
    }
    
    // Step 4: Reverse suffix
    reverse(nums.begin() + i + 1, nums.end());
}


/*
PROBLEM 4: Permutation Sequence - Kth Permutation (LeetCode 60)
───────────────────────────────────────────────────────────────
Find the kth permutation sequence of [1,2,...,n].

Input: n = 3, k = 3
Output: "213"
Permutations: ["123","132","213","231","312","321"]

Approach: Use factorial to determine each digit position

Time: O(n²) | Space: O(n)
*/
string getPermutation(int n, int k) {
    vector<int> factorial(n, 1);
    vector<int> nums;
    
    // Calculate factorials
    for (int i = 1; i < n; i++) {
        factorial[i] = factorial[i - 1] * i;
    }
    
    // Initialize available numbers
    for (int i = 1; i <= n; i++) {
        nums.push_back(i);
    }
    
    k--;  // Convert to 0-indexed
    string result;
    
    for (int i = n - 1; i >= 0; i--) {
        int index = k / factorial[i];
        result += to_string(nums[index]);
        nums.erase(nums.begin() + index);
        k %= factorial[i];
    }
    
    return result;
}


/*
PROBLEM 5: Permutations of String
─────────────────────────────────
Generate all permutations of characters in a string.

Input: s = "abc"
Output: ["abc","acb","bac","bca","cab","cba"]
*/
class StringPermutations {
public:
    vector<string> permute(string s) {
        vector<string> result;
        sort(s.begin(), s.end());
        backtrack(s, 0, result);
        return result;
    }
    
private:
    void backtrack(string& s, int start, vector<string>& result) {
        if (start == s.size()) {
            result.push_back(s);
            return;
        }
        
        unordered_set<char> used;  // Track used chars at this level
        for (int i = start; i < s.size(); i++) {
            if (used.count(s[i])) continue;  // Skip duplicates
            used.insert(s[i]);
            
            swap(s[start], s[i]);
            backtrack(s, start + 1, result);
            swap(s[start], s[i]);
        }
    }
};


/*
PROBLEM 6: Beautiful Arrangement (LeetCode 526)
───────────────────────────────────────────────
Count permutations where perm[i] divisible by i or i divisible by perm[i].

Input: n = 2
Output: 2 ([1,2] and [2,1])

Time: O(k) where k = valid permutations | Space: O(n)
*/
class BeautifulArrangement {
public:
    int countArrangement(int n) {
        vector<bool> used(n + 1, false);
        return backtrack(n, 1, used);
    }
    
private:
    int backtrack(int n, int pos, vector<bool>& used) {
        if (pos > n) return 1;
        
        int count = 0;
        for (int i = 1; i <= n; i++) {
            if (!used[i] && (i % pos == 0 || pos % i == 0)) {
                used[i] = true;
                count += backtrack(n, pos + 1, used);
                used[i] = false;
            }
        }
        return count;
    }
};


/*
PROBLEM 7: Count Vowel Permutation (LeetCode 1220)
──────────────────────────────────────────────────
Count strings of length n with vowels following rules:
a -> e, e -> a,i, i -> a,e,o,u (not i), o -> i,u, u -> a

Input: n = 2
Output: 10

Note: This is better solved with DP, but can be done with backtracking.

Time: O(5^n) backtracking, O(n) DP | Space: O(n)
*/
int countVowelPermutation(int n) {
    const int MOD = 1e9 + 7;
    // DP approach (more efficient)
    // dp[i][v] = count of strings of length i ending with vowel v
    
    vector<long long> dp(5, 1);  // a, e, i, o, u
    
    for (int len = 2; len <= n; len++) {
        vector<long long> next(5, 0);
        next[0] = (dp[1] + dp[2] + dp[4]) % MOD;  // a follows e, i, u
        next[1] = (dp[0] + dp[2]) % MOD;          // e follows a, i
        next[2] = (dp[1] + dp[3]) % MOD;          // i follows e, o
        next[3] = dp[2];                          // o follows i
        next[4] = (dp[2] + dp[3]) % MOD;          // u follows i, o
        dp = next;
    }
    
    long long total = 0;
    for (int i = 0; i < 5; i++) {
        total = (total + dp[i]) % MOD;
    }
    return total;
}


/*
PROBLEM 8: All Permutations with Specific Constraints
─────────────────────────────────────────────────────
Generate permutations where element i can't be adjacent to element j.

Example: Seating arrangement where enemies can't sit together.
*/
class ConstrainedPermutations {
public:
    vector<vector<int>> permute(vector<int>& nums, set<pair<int,int>>& forbidden) {
        vector<vector<int>> result;
        vector<int> current;
        vector<bool> used(nums.size(), false);
        backtrack(nums, forbidden, used, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, set<pair<int,int>>& forbidden,
                   vector<bool>& used, vector<int>& current,
                   vector<vector<int>>& result) {
        if (current.size() == nums.size()) {
            result.push_back(current);
            return;
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;
            
            // Check constraint with last element
            if (!current.empty()) {
                int last = current.back();
                if (forbidden.count({last, nums[i]}) || 
                    forbidden.count({nums[i], last})) {
                    continue;
                }
            }
            
            used[i] = true;
            current.push_back(nums[i]);
            backtrack(nums, forbidden, used, current, result);
            current.pop_back();
            used[i] = false;
        }
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Permutation Patterns ===\n\n";
    
    // 1. Permutations
    Permutations sol1;
    vector<int> nums1 = {1, 2, 3};
    auto res1 = sol1.permute(nums1);
    cout << "1. Permutations of [1,2,3]: " << res1.size() << " permutations\n";
    
    // 2. Permutations II
    PermutationsII sol2;
    vector<int> nums2 = {1, 1, 2};
    auto res2 = sol2.permuteUnique(nums2);
    cout << "2. Unique permutations of [1,1,2]: " << res2.size() << " permutations\n";
    
    // 3. Next Permutation
    vector<int> nums3 = {1, 2, 3};
    nextPermutation(nums3);
    cout << "3. Next permutation of [1,2,3]: [";
    for (int i = 0; i < nums3.size(); i++) {
        cout << nums3[i] << (i < nums3.size()-1 ? "," : "");
    }
    cout << "]\n";
    
    // 4. Kth Permutation
    cout << "4. 3rd permutation of [1,2,3]: " << getPermutation(3, 3) << "\n";
    
    // 6. Beautiful Arrangement
    BeautifulArrangement sol6;
    cout << "6. Beautiful arrangements (n=2): " << sol6.countArrangement(2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Permutations                  | Use visited array, try each unused element    |
| Permutations II (dups)        | Sort + skip if same as prev AND prev unused   |
| Next Permutation              | Find pivot, swap, reverse suffix              |
| Kth Permutation               | Use factorial to compute digit by digit       |
| String Permutations           | Swap-based or use set for duplicates          |
| Beautiful Arrangement         | Constraint check before recursing             |
+───────────────────────────────+────────────────────────────────────────────────+

KEY INSIGHT: 
- Subsets use "start index" (order doesn't matter)
- Permutations use "visited array" (order matters, each used once)

================================================================================
*/

