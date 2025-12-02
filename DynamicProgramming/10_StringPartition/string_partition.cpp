/*
================================================================================
                    PATTERN 10: STRING PARTITION
================================================================================

When to use:
- Partition string into substrings satisfying conditions
- Word break problems
- Minimize/count partitions

LeetCode Problems:
- 139. Word Break
- 140. Word Break II
- 132. Palindrome Partitioning II

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Word Break (LeetCode 139) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────
Can string be segmented into dictionary words?

dp[i] = true if s[0..i-1] can be segmented

Time: O(n² * m) or O(n²) with Trie | Space: O(n)
*/
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict(wordDict.begin(), wordDict.end());
    int n = s.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j] && dict.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    
    return dp[n];
}


/*
PROBLEM 2: Word Break II (LeetCode 140)
───────────────────────────────────────
Return all possible sentences.

Backtracking with memoization.

Time: O(2^n) worst case | Space: O(2^n)
*/
class WordBreakII {
    unordered_set<string> dict;
    unordered_map<int, vector<string>> memo;
    
    vector<string> solve(string& s, int start) {
        if (start == s.size()) return {""};
        if (memo.count(start)) return memo[start];
        
        vector<string> result;
        for (int end = start + 1; end <= s.size(); end++) {
            string word = s.substr(start, end - start);
            if (dict.count(word)) {
                for (string& sub : solve(s, end)) {
                    result.push_back(word + (sub.empty() ? "" : " " + sub));
                }
            }
        }
        
        return memo[start] = result;
    }
    
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        dict = unordered_set<string>(wordDict.begin(), wordDict.end());
        memo.clear();
        return solve(s, 0);
    }
};


/*
PROBLEM 3: Palindrome Partitioning II (LeetCode 132)
────────────────────────────────────────────────────
Min cuts to partition into palindromes.

Time: O(n²) | Space: O(n²)
*/
int minCut(string s) {
    int n = s.size();
    
    // Precompute palindrome check
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            isPalin[i][j] = (s[i] == s[j]) && (j - i <= 2 || isPalin[i+1][j-1]);
        }
    }
    
    vector<int> dp(n + 1);
    for (int i = 0; i <= n; i++) dp[i] = i - 1;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            if (isPalin[j][i-1]) {
                dp[i] = min(dp[i], dp[j] + 1);
            }
        }
    }
    
    return dp[n];
}


/*
PROBLEM 4: Concatenated Words (LeetCode 472)
────────────────────────────────────────────
Find all words that are concatenation of other words.

For each word, check if it can be formed by shorter words.

Time: O(n * L³) | Space: O(n * L)
*/
vector<string> findAllConcatenatedWords(vector<string>& words) {
    unordered_set<string> dict(words.begin(), words.end());
    vector<string> result;
    
    for (const string& word : words) {
        int n = word.size();
        if (n == 0) continue;
        
        vector<bool> dp(n + 1, false);
        dp[0] = true;
        
        for (int i = 1; i <= n; i++) {
            for (int j = (i == n ? 1 : 0); j < i; j++) {
                if (dp[j] && dict.count(word.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        if (dp[n]) result.push_back(word);
    }
    
    return result;
}


/*
PROBLEM 5: Extra Characters in String (LeetCode 2707)
─────────────────────────────────────────────────────
Min extra characters after breaking into dictionary words.

dp[i] = min extra characters for s[0..i-1]

Time: O(n² * m) | Space: O(n)
*/
int minExtraChar(string s, vector<string>& dictionary) {
    unordered_set<string> dict(dictionary.begin(), dictionary.end());
    int n = s.size();
    vector<int> dp(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i-1] + 1;  // Treat s[i-1] as extra
        for (int j = 0; j < i; j++) {
            if (dict.count(s.substr(j, i - j))) {
                dp[i] = min(dp[i], dp[j]);
            }
        }
    }
    
    return dp[n];
}


/*
PROBLEM 6: Restore IP Addresses (LeetCode 93)
─────────────────────────────────────────────
Return all valid IP addresses from string.

Backtracking with 4 segments.

Time: O(3^4 * n) | Space: O(n)
*/
class Solution93 {
    vector<string> result;
    
    bool isValid(const string& s) {
        if (s.empty() || s.size() > 3) return false;
        if (s.size() > 1 && s[0] == '0') return false;
        int num = stoi(s);
        return num >= 0 && num <= 255;
    }
    
    void backtrack(string& s, int start, vector<string>& parts) {
        if (parts.size() == 4) {
            if (start == s.size()) {
                result.push_back(parts[0] + "." + parts[1] + "." + parts[2] + "." + parts[3]);
            }
            return;
        }
        
        for (int len = 1; len <= 3 && start + len <= s.size(); len++) {
            string part = s.substr(start, len);
            if (isValid(part)) {
                parts.push_back(part);
                backtrack(s, start + len, parts);
                parts.pop_back();
            }
        }
    }
    
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> parts;
        backtrack(s, 0, parts);
        return result;
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== String Partition ===\n\n";
    
    // Word Break
    vector<string> dict1 = {"leet", "code"};
    cout << "1. Word break 'leetcode': " << (wordBreak("leetcode", dict1) ? "Yes" : "No") << "\n";
    
    // Palindrome Partition II
    cout << "3. Min cuts 'aab': " << minCut("aab") << "\n";
    
    // Extra Characters
    vector<string> dict2 = {"leet", "code", "leetcode"};
    cout << "5. Extra chars 'leetscode': " << minExtraChar("leetscode", dict2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

STRING PARTITION TEMPLATE:
    dp[0] = base_case
    for i = 1 to n:
        for j = 0 to i-1:
            if s[j..i-1] is valid:
                dp[i] = f(dp[i], dp[j] + ...)

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Valid Condition                                |
+───────────────────────────────+────────────────────────────────────────────────+
| Word Break                    | Substring in dictionary                        |
| Palindrome Partition          | Substring is palindrome                        |
| Concatenated Words            | Word = concat of shorter dict words            |
| Restore IP                    | Valid IP segment (0-255, no leading 0)         |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

