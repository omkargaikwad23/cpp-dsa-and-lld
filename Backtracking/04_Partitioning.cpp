/*
================================================================================
                    BACKTRACKING - PARTITIONING PROBLEMS
================================================================================

Partition input into multiple parts satisfying certain conditions.

Key Pattern:
- At each position, try all possible "cut points"
- Check if current partition is valid
- Recursively solve remaining part

Time: Varies | Space: O(n)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Palindrome Partitioning (LeetCode 131)
─────────────────────────────────────────────────
Partition string so every substring is a palindrome.

Input: s = "aab"
Output: [["a","a","b"],["aa","b"]]

Time: O(n * 2^n) | Space: O(n)
*/
class PalindromePartitioning {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;
    }
    
private:
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left++] != s[right--]) return false;
        }
        return true;
    }
    
    void backtrack(const string& s, int start, vector<string>& current,
                   vector<vector<string>>& result) {
        if (start == s.size()) {
            result.push_back(current);
            return;
        }
        
        for (int end = start; end < s.size(); end++) {
            if (isPalindrome(s, start, end)) {
                current.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, current, result);
                current.pop_back();
            }
        }
    }
};

// Optimized with DP precomputation
class PalindromePartitioningDP {
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        
        // Precompute palindrome status
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i + 1][j - 1]);
            }
        }
        
        vector<vector<string>> result;
        vector<string> current;
        backtrack(s, 0, dp, current, result);
        return result;
    }
    
private:
    void backtrack(const string& s, int start, vector<vector<bool>>& dp,
                   vector<string>& current, vector<vector<string>>& result) {
        if (start == s.size()) {
            result.push_back(current);
            return;
        }
        
        for (int end = start; end < s.size(); end++) {
            if (dp[start][end]) {
                current.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, dp, current, result);
                current.pop_back();
            }
        }
    }
};


/*
PROBLEM 2: Restore IP Addresses (LeetCode 93)
─────────────────────────────────────────────
Return all valid IP addresses from a string of digits.

Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]

Time: O(3^4) = O(81) = O(1) | Space: O(1)
*/
class RestoreIPAddresses {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> result;
        vector<string> current;
        backtrack(s, 0, current, result);
        return result;
    }
    
private:
    bool isValid(const string& segment) {
        if (segment.empty() || segment.size() > 3) return false;
        if (segment.size() > 1 && segment[0] == '0') return false;  // Leading zero
        int num = stoi(segment);
        return num >= 0 && num <= 255;
    }
    
    void backtrack(const string& s, int start, vector<string>& current,
                   vector<string>& result) {
        // Found all 4 segments
        if (current.size() == 4) {
            if (start == s.size()) {
                result.push_back(current[0] + "." + current[1] + "." + 
                                current[2] + "." + current[3]);
            }
            return;
        }
        
        // Pruning: check if remaining string can form remaining segments
        int remaining = s.size() - start;
        int segmentsNeeded = 4 - current.size();
        if (remaining < segmentsNeeded || remaining > segmentsNeeded * 3) return;
        
        // Try segments of length 1, 2, 3
        for (int len = 1; len <= 3 && start + len <= s.size(); len++) {
            string segment = s.substr(start, len);
            if (isValid(segment)) {
                current.push_back(segment);
                backtrack(s, start + len, current, result);
                current.pop_back();
            }
        }
    }
};


/*
PROBLEM 3: Word Break II (LeetCode 140)
───────────────────────────────────────
Return all possible sentences from dictionary words.

Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]

Time: O(2^n) worst case | Space: O(n)
*/
class WordBreakII {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> dict(wordDict.begin(), wordDict.end());
        unordered_map<int, vector<string>> memo;
        return backtrack(s, 0, dict, memo);
    }
    
private:
    vector<string> backtrack(const string& s, int start,
                             unordered_set<string>& dict,
                             unordered_map<int, vector<string>>& memo) {
        if (memo.count(start)) return memo[start];
        
        vector<string> result;
        
        if (start == s.size()) {
            result.push_back("");
            return result;
        }
        
        for (int end = start + 1; end <= s.size(); end++) {
            string word = s.substr(start, end - start);
            if (dict.count(word)) {
                vector<string> suffixes = backtrack(s, end, dict, memo);
                for (const string& suffix : suffixes) {
                    result.push_back(word + (suffix.empty() ? "" : " " + suffix));
                }
            }
        }
        
        memo[start] = result;
        return result;
    }
};


/*
PROBLEM 4: Split Array into Fibonacci Sequence (LeetCode 842)
─────────────────────────────────────────────────────────────
Split string into Fibonacci sequence (each num <= 2^31-1).

Input: num = "1101111"
Output: [11,0,11,11] (11 + 0 = 11, 0 + 11 = 11)

Time: O(n^2) | Space: O(n)
*/
class SplitFibonacci {
public:
    vector<int> splitIntoFibonacci(string num) {
        vector<int> result;
        backtrack(num, 0, result);
        return result;
    }
    
private:
    bool backtrack(const string& num, int start, vector<int>& result) {
        if (start == num.size()) {
            return result.size() >= 3;
        }
        
        long long curr = 0;
        for (int i = start; i < num.size(); i++) {
            // No leading zeros (except "0" itself)
            if (i > start && num[start] == '0') break;
            
            curr = curr * 10 + (num[i] - '0');
            
            // Overflow check
            if (curr > INT_MAX) break;
            
            int n = result.size();
            
            // If we have 2+ numbers, check Fibonacci property
            if (n >= 2) {
                long long sum = (long long)result[n - 1] + result[n - 2];
                if (curr > sum) break;  // Too large
                if (curr < sum) continue;  // Too small, try longer
            }
            
            result.push_back(curr);
            if (backtrack(num, i + 1, result)) return true;
            result.pop_back();
        }
        
        return false;
    }
};


/*
PROBLEM 5: Decode Ways II (LeetCode 639)
────────────────────────────────────────
'*' can be 1-9. Count ways to decode string.

Input: s = "*"
Output: 9 ('1'-'9' -> 'A'-'I')

Note: Better solved with DP due to counting nature.
*/
int numDecodings(string s) {
    const int MOD = 1e9 + 7;
    int n = s.size();
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;
    
    auto ways1 = [](char c) -> long long {
        if (c == '*') return 9;
        if (c == '0') return 0;
        return 1;
    };
    
    auto ways2 = [](char c1, char c2) -> long long {
        if (c1 == '*' && c2 == '*') return 15;  // 11-19, 21-26
        if (c1 == '*') {
            return (c2 <= '6') ? 2 : 1;  // 1X or 2X possible
        }
        if (c2 == '*') {
            if (c1 == '1') return 9;  // 11-19
            if (c1 == '2') return 6;  // 21-26
            return 0;
        }
        int num = (c1 - '0') * 10 + (c2 - '0');
        return (num >= 10 && num <= 26) ? 1 : 0;
    };
    
    dp[1] = ways1(s[0]);
    for (int i = 2; i <= n; i++) {
        dp[i] = (dp[i - 1] * ways1(s[i - 1])) % MOD;
        dp[i] = (dp[i] + dp[i - 2] * ways2(s[i - 2], s[i - 1])) % MOD;
    }
    
    return dp[n];
}


/*
PROBLEM 6: Strobogrammatic Number III (LeetCode 248)
────────────────────────────────────────────────────
Count strobogrammatic numbers in range [low, high].
Strobogrammatic: looks same when rotated 180° (0,1,6,8,9)

Time: O(5^(n/2)) | Space: O(n)
*/
class StrobogrammaticIII {
    vector<pair<char, char>> pairs = {{'0','0'}, {'1','1'}, {'6','9'}, {'8','8'}, {'9','6'}};
    
public:
    int strobogrammaticInRange(string low, string high) {
        int count = 0;
        for (int len = low.size(); len <= high.size(); len++) {
            vector<string> nums;
            generate(len, len, nums);
            for (const string& num : nums) {
                if ((num.size() == low.size() && num < low) ||
                    (num.size() == high.size() && num > high)) {
                    continue;
                }
                count++;
            }
        }
        return count;
    }
    
private:
    void generate(int n, int targetLen, vector<string>& result) {
        if (n == 0) {
            result.push_back("");
            return;
        }
        if (n == 1) {
            result = {"0", "1", "8"};
            return;
        }
        
        vector<string> inner;
        generate(n - 2, targetLen, inner);
        
        for (const string& s : inner) {
            for (auto& [left, right] : pairs) {
                if (n == targetLen && left == '0') continue;  // No leading zeros
                result.push_back(left + s + right);
            }
        }
    }
};


/*
PROBLEM 7: Expression Add Operators (LeetCode 282)
──────────────────────────────────────────────────
Add +, -, * between digits to reach target.

Input: num = "123", target = 6
Output: ["1+2+3", "1*2*3"]

Time: O(4^n * n) | Space: O(n)
*/
class ExpressionAddOperators {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;
        backtrack(num, target, 0, 0, 0, "", result);
        return result;
    }
    
private:
    void backtrack(const string& num, int target, int index,
                   long long value, long long prevOperand, string expr,
                   vector<string>& result) {
        if (index == num.size()) {
            if (value == target) {
                result.push_back(expr);
            }
            return;
        }
        
        for (int len = 1; len <= num.size() - index; len++) {
            string currStr = num.substr(index, len);
            
            // Skip leading zeros
            if (currStr.size() > 1 && currStr[0] == '0') break;
            
            long long curr = stoll(currStr);
            
            if (index == 0) {
                // First number, no operator
                backtrack(num, target, len, curr, curr, currStr, result);
            } else {
                // Try +
                backtrack(num, target, index + len, value + curr, curr,
                         expr + "+" + currStr, result);
                
                // Try -
                backtrack(num, target, index + len, value - curr, -curr,
                         expr + "-" + currStr, result);
                
                // Try * (need to undo previous add/subtract)
                backtrack(num, target, index + len,
                         value - prevOperand + prevOperand * curr,
                         prevOperand * curr,
                         expr + "*" + currStr, result);
            }
        }
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Partitioning Patterns ===\n\n";
    
    // 1. Palindrome Partitioning
    PalindromePartitioning sol1;
    auto res1 = sol1.partition("aab");
    cout << "1. Palindrome partitions of 'aab': " << res1.size() << " ways\n";
    
    // 2. Restore IP Addresses
    RestoreIPAddresses sol2;
    auto res2 = sol2.restoreIpAddresses("25525511135");
    cout << "2. Valid IPs from '25525511135': " << res2.size() << " IPs\n";
    
    // 3. Word Break II
    WordBreakII sol3;
    vector<string> dict = {"cat", "cats", "and", "sand", "dog"};
    auto res3 = sol3.wordBreak("catsanddog", dict);
    cout << "3. Word break sentences: " << res3.size() << " sentences\n";
    
    // 7. Expression Add Operators
    ExpressionAddOperators sol7;
    auto res7 = sol7.addOperators("123", 6);
    cout << "7. Expressions '123' = 6: ";
    for (const string& e : res7) cout << e << " ";
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Palindrome Partitioning       | Try all cut points, check palindrome          |
| Restore IP Addresses          | 4 segments, each 1-3 digits, 0-255            |
| Word Break II                 | Memoize to avoid recomputation                |
| Split Fibonacci               | Validate Fibonacci property as we go          |
| Expression Add Operators      | Track prevOperand for multiplication          |
+───────────────────────────────+────────────────────────────────────────────────+

KEY INSIGHT: Partitioning = deciding where to "cut" the string/array at each step

================================================================================
*/

