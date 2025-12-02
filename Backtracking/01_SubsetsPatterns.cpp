/*
================================================================================
                    BACKTRACKING - SUBSETS / POWER SET
================================================================================

Generate all possible subsets of a given set.
For n elements, there are 2^n subsets.

Key Decision: For each element, INCLUDE or EXCLUDE it.

Time: O(n * 2^n) | Space: O(n) recursion depth
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Subsets (LeetCode 78)
────────────────────────────────
Generate all subsets of distinct integers.

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Time: O(n * 2^n) | Space: O(n)
*/
class Subsets {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<int>& current,
                   vector<vector<int>>& result) {
        result.push_back(current);  // Every subset is valid
        
        for (int i = start; i < nums.size(); i++) {
            current.push_back(nums[i]);      // Include element
            backtrack(nums, i + 1, current, result);
            current.pop_back();              // Exclude element (backtrack)
        }
    }
};

// Alternative: Iterative approach
vector<vector<int>> subsetsIterative(vector<int>& nums) {
    vector<vector<int>> result = {{}};
    
    for (int num : nums) {
        int n = result.size();
        for (int i = 0; i < n; i++) {
            vector<int> subset = result[i];
            subset.push_back(num);
            result.push_back(subset);
        }
    }
    
    return result;
}

// Alternative: Bitmask approach
vector<vector<int>> subsetsBitmask(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        result.push_back(subset);
    }
    
    return result;
}


/*
PROBLEM 2: Subsets II - With Duplicates (LeetCode 90)
─────────────────────────────────────────────────────
Generate all unique subsets (input may have duplicates).

Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Key: Sort first, then skip duplicates at same level.

Time: O(n * 2^n) | Space: O(n)
*/
class SubsetsII {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // Sort to handle duplicates
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, vector<int>& current,
                   vector<vector<int>>& result) {
        result.push_back(current);
        
        for (int i = start; i < nums.size(); i++) {
            // Skip duplicates at the same recursion level
            if (i > start && nums[i] == nums[i - 1]) continue;
            
            current.push_back(nums[i]);
            backtrack(nums, i + 1, current, result);
            current.pop_back();
        }
    }
};


/*
PROBLEM 3: Letter Case Permutation (LeetCode 784)
─────────────────────────────────────────────────
Generate all strings by toggling case of letters.

Input: s = "a1b2"
Output: ["a1b2","a1B2","A1b2","A1B2"]

Time: O(n * 2^n) | Space: O(n)
*/
class LetterCasePermutation {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> result;
        backtrack(s, 0, result);
        return result;
    }
    
private:
    void backtrack(string& s, int index, vector<string>& result) {
        if (index == s.size()) {
            result.push_back(s);
            return;
        }
        
        // Always try the character as-is
        backtrack(s, index + 1, result);
        
        // If letter, also try toggled case
        if (isalpha(s[index])) {
            s[index] ^= 32;  // Toggle case using XOR
            backtrack(s, index + 1, result);
            s[index] ^= 32;  // Backtrack
        }
    }
};


/*
PROBLEM 4: Subsets of Size K (Combinations) (LeetCode 77)
─────────────────────────────────────────────────────────
Generate all combinations of k numbers from 1 to n.

Input: n = 4, k = 2
Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]

Time: O(k * C(n,k)) | Space: O(k)
*/
class Combinations {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(n, k, 1, current, result);
        return result;
    }
    
private:
    void backtrack(int n, int k, int start, vector<int>& current,
                   vector<vector<int>>& result) {
        if (current.size() == k) {
            result.push_back(current);
            return;
        }
        
        // Pruning: need (k - current.size()) more elements
        // Can only pick from [start, n], so need n - start + 1 >= k - current.size()
        for (int i = start; i <= n - (k - current.size()) + 1; i++) {
            current.push_back(i);
            backtrack(n, k, i + 1, current, result);
            current.pop_back();
        }
    }
};


/*
PROBLEM 5: Find All Subsets That Sum to K
─────────────────────────────────────────
Find all subsets with sum equal to target.

Input: nums = [1,2,3,4,5], target = 5
Output: [[1,4],[2,3],[5]]

Time: O(2^n) | Space: O(n)
*/
class SubsetsWithSum {
public:
    vector<vector<int>> findSubsets(vector<int>& nums, int target) {
        vector<vector<int>> result;
        vector<int> current;
        backtrack(nums, 0, target, current, result);
        return result;
    }
    
private:
    void backtrack(vector<int>& nums, int start, int remaining,
                   vector<int>& current, vector<vector<int>>& result) {
        if (remaining == 0) {
            result.push_back(current);
            return;
        }
        
        if (remaining < 0) return;  // Pruning
        
        for (int i = start; i < nums.size(); i++) {
            current.push_back(nums[i]);
            backtrack(nums, i + 1, remaining - nums[i], current, result);
            current.pop_back();
        }
    }
};


/*
PROBLEM 6: Beautiful Subsets (LeetCode 2597)
────────────────────────────────────────────
Count subsets where no two elements have difference k.

Input: nums = [2,4,6], k = 2
Output: 4 ([[2],[4],[6],[2,6]])

Time: O(2^n) | Space: O(n)
*/
class BeautifulSubsets {
public:
    int beautifulSubsets(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        unordered_map<int, int> count;
        return backtrack(nums, k, 0, count) - 1;  // Exclude empty set
    }
    
private:
    int backtrack(vector<int>& nums, int k, int start, 
                  unordered_map<int, int>& count) {
        int total = 1;  // Count current subset
        
        for (int i = start; i < nums.size(); i++) {
            // Check if nums[i] - k exists in current subset
            if (count[nums[i] - k] == 0) {
                count[nums[i]]++;
                total += backtrack(nums, k, i + 1, count);
                count[nums[i]]--;
            }
        }
        
        return total;
    }
};


/*
PROBLEM 7: Maximum Length of Concatenated String (LeetCode 1239)
────────────────────────────────────────────────────────────────
Find max length of concatenation with unique characters.

Input: arr = ["un","iq","ue"]
Output: 4 ("uniq" or "ique")

Time: O(2^n * 26) | Space: O(n)
*/
class MaxConcatLength {
public:
    int maxLength(vector<string>& arr) {
        vector<int> masks;  // Bitmask representation of each string
        
        // Convert strings to bitmasks, skip invalid strings
        for (const string& s : arr) {
            int mask = 0;
            bool valid = true;
            for (char c : s) {
                int bit = 1 << (c - 'a');
                if (mask & bit) { valid = false; break; }  // Duplicate char
                mask |= bit;
            }
            if (valid) masks.push_back(mask);
        }
        
        int maxLen = 0;
        backtrack(masks, arr, 0, 0, maxLen);
        return maxLen;
    }
    
private:
    void backtrack(vector<int>& masks, vector<string>& arr, int index, 
                   int currentMask, int& maxLen) {
        maxLen = max(maxLen, __builtin_popcount(currentMask));
        
        for (int i = index; i < masks.size(); i++) {
            // No overlap in characters
            if ((currentMask & masks[i]) == 0) {
                backtrack(masks, arr, i + 1, currentMask | masks[i], maxLen);
            }
        }
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Subsets Patterns ===\n\n";
    
    // 1. Subsets
    Subsets sol1;
    vector<int> nums1 = {1, 2, 3};
    auto res1 = sol1.subsets(nums1);
    cout << "1. Subsets of [1,2,3]: " << res1.size() << " subsets\n";
    
    // 2. Subsets II
    SubsetsII sol2;
    vector<int> nums2 = {1, 2, 2};
    auto res2 = sol2.subsetsWithDup(nums2);
    cout << "2. Unique subsets of [1,2,2]: " << res2.size() << " subsets\n";
    
    // 3. Letter Case Permutation
    LetterCasePermutation sol3;
    auto res3 = sol3.letterCasePermutation("a1b2");
    cout << "3. Letter case permutations of 'a1b2': " << res3.size() << " strings\n";
    
    // 4. Combinations
    Combinations sol4;
    auto res4 = sol4.combine(4, 2);
    cout << "4. C(4,2) combinations: " << res4.size() << " combinations\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Subsets                       | Include/exclude each element, start index     |
| Subsets II (duplicates)       | Sort + skip same elements at same level       |
| Letter Case Permutation       | Branch on letter toggle (XOR 32)              |
| Combinations (n choose k)     | Stop when size == k, prune early              |
| Subsets with Target Sum       | Track remaining sum, prune when negative      |
| Beautiful Subsets             | Use hashmap to track conflicts                |
| Max Concat Length             | Use bitmask for character tracking            |
+───────────────────────────────+────────────────────────────────────────────────+

KEY INSIGHT: Subsets use "start index" to avoid duplicates by only considering
elements after current position.

================================================================================
*/

