/*
================================================================================
                    PATTERN 7: PALINDROMIC SUBSEQUENCE/SUBSTRING
================================================================================

When to use:
- Find subsequence/substring that reads same forwards and backwards
- Palindrome partitioning
- Min insertions/deletions to make palindrome

LeetCode Problems:
- 516. Longest Palindromic Subsequence
- 647. Palindromic Substrings
- 1312. Min Insertion Steps to Make String Palindrome

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Longest Palindromic Subsequence (LeetCode 516) ⭐
───────────────────────────────────────────────────────────
LPS = LCS(s, reverse(s))

Or direct DP:
dp[i][j] = LPS in s[i..j]
If s[i] == s[j]: dp[i][j] = dp[i+1][j-1] + 2
Else: dp[i][j] = max(dp[i+1][j], dp[i][j-1])

Time: O(n²) | Space: O(n²) or O(n)
*/
int longestPalindromeSubseq(string s) {
    int n = s.size();
    vector<int> dp(n, 1);  // dp[j] = LPS ending at j
    
    for (int i = n - 2; i >= 0; i--) {
        int prev = 0;
        for (int j = i + 1; j < n; j++) {
            int temp = dp[j];
            if (s[i] == s[j]) {
                dp[j] = prev + 2;
            } else {
                dp[j] = max(dp[j], dp[j-1]);
            }
            prev = temp;
        }
    }
    
    return dp[n-1];
}


/*
PROBLEM 2: Longest Palindromic Substring (LeetCode 5)
─────────────────────────────────────────────────────
Find longest palindromic substring (contiguous).

Expand from center approach is O(n²) time, O(1) space.

Time: O(n²) | Space: O(1)
*/
string longestPalindrome(string s) {
    int n = s.size();
    int start = 0, maxLen = 1;
    
    auto expandFromCenter = [&](int left, int right) {
        while (left >= 0 && right < n && s[left] == s[right]) {
            if (right - left + 1 > maxLen) {
                maxLen = right - left + 1;
                start = left;
            }
            left--;
            right++;
        }
    };
    
    for (int i = 0; i < n; i++) {
        expandFromCenter(i, i);      // Odd length
        expandFromCenter(i, i + 1);  // Even length
    }
    
    return s.substr(start, maxLen);
}


/*
PROBLEM 3: Palindromic Substrings (LeetCode 647)
────────────────────────────────────────────────
Count all palindromic substrings.

Time: O(n²) | Space: O(1)
*/
int countSubstrings(string s) {
    int n = s.size();
    int count = 0;
    
    auto expandCount = [&](int left, int right) {
        while (left >= 0 && right < n && s[left] == s[right]) {
            count++;
            left--;
            right++;
        }
    };
    
    for (int i = 0; i < n; i++) {
        expandCount(i, i);      // Odd
        expandCount(i, i + 1);  // Even
    }
    
    return count;
}


/*
PROBLEM 4: Min Insertion to Make Palindrome (LeetCode 1312)
───────────────────────────────────────────────────────────
Min insertions = n - LPS(s)

Time: O(n²) | Space: O(n)
*/
int minInsertions(string s) {
    return s.size() - longestPalindromeSubseq(s);
}


/*
PROBLEM 5: Palindrome Partitioning II (LeetCode 132) ⭐
──────────────────────────────────────────────────────
Min cuts to partition string into palindromes.

dp[i] = min cuts for s[0..i-1]
If s[j..i-1] is palindrome: dp[i] = min(dp[i], dp[j] + 1)

Time: O(n²) | Space: O(n²)
*/
int minCut(string s) {
    int n = s.size();
    
    // Precompute palindrome check
    vector<vector<bool>> isPalin(n, vector<bool>(n, false));
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (s[i] == s[j] && (j - i <= 2 || isPalin[i+1][j-1])) {
                isPalin[i][j] = true;
            }
        }
    }
    
    vector<int> dp(n + 1, 0);
    for (int i = 0; i <= n; i++) dp[i] = i - 1;  // Max cuts
    
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
PROBLEM 6: Palindrome Partitioning (LeetCode 131)
─────────────────────────────────────────────────
Return all palindrome partitions.

Backtracking + precomputed palindrome check.

Time: O(n * 2^n) | Space: O(n²)
*/
class Solution131 {
    vector<vector<string>> result;
    vector<vector<bool>> isPalin;
    
    void backtrack(string& s, int start, vector<string>& path) {
        if (start == s.size()) {
            result.push_back(path);
            return;
        }
        
        for (int end = start; end < s.size(); end++) {
            if (isPalin[start][end]) {
                path.push_back(s.substr(start, end - start + 1));
                backtrack(s, end + 1, path);
                path.pop_back();
            }
        }
    }
    
public:
    vector<vector<string>> partition(string s) {
        int n = s.size();
        isPalin.assign(n, vector<bool>(n, false));
        
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j < n; j++) {
                if (s[i] == s[j] && (j - i <= 2 || isPalin[i+1][j-1])) {
                    isPalin[i][j] = true;
                }
            }
        }
        
        vector<string> path;
        backtrack(s, 0, path);
        return result;
    }
};


/*
PROBLEM 7: Valid Palindrome III (LeetCode 1216)
───────────────────────────────────────────────
Check if string can become palindrome by removing at most k characters.

n - LPS <= k

Time: O(n²) | Space: O(n)
*/
bool isValidPalindrome(string s, int k) {
    return (int)s.size() - longestPalindromeSubseq(s) <= k;
}


/*
PROBLEM 8: Count Different Palindromic Subsequences (LeetCode 730)
──────────────────────────────────────────────────────────────────
Count distinct palindromic subsequences.

Time: O(n²) | Space: O(n²)
*/
int countPalindromicSubsequences(string s) {
    const int MOD = 1e9 + 7;
    int n = s.size();
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (s[i] != s[j]) {
                dp[i][j] = dp[i+1][j] + dp[i][j-1] - dp[i+1][j-1];
            } else {
                int left = i + 1, right = j - 1;
                while (left <= right && s[left] != s[i]) left++;
                while (left <= right && s[right] != s[j]) right--;
                
                if (left > right) {
                    dp[i][j] = dp[i+1][j-1] * 2 + 2;
                } else if (left == right) {
                    dp[i][j] = dp[i+1][j-1] * 2 + 1;
                } else {
                    dp[i][j] = dp[i+1][j-1] * 2 - dp[left+1][right-1];
                }
            }
            
            dp[i][j] = ((dp[i][j] % MOD) + MOD) % MOD;
        }
    }
    
    return dp[0][n-1];
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Palindrome DP ===\n\n";
    
    // Longest Palindromic Subsequence
    cout << "1. LPS of 'bbbab': " << longestPalindromeSubseq("bbbab") << "\n";
    
    // Longest Palindromic Substring
    cout << "2. Longest palindrome in 'babad': " << longestPalindrome("babad") << "\n";
    
    // Count Palindromic Substrings
    cout << "3. Count palindromes in 'aaa': " << countSubstrings("aaa") << "\n";
    
    // Min Insertions
    cout << "4. Min insertions for 'leetcode': " << minInsertions("leetcode") << "\n";
    
    // Min Cuts
    cout << "5. Min cuts for 'aab': " << minCut("aab") << "\n";
    
    // Valid Palindrome III
    cout << "7. 'abcdeca' valid with k=2: " << (isValidPalindrome("abcdeca", 2) ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Formula                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Longest Palindromic Subseq    | LCS(s, reverse(s)) or interval DP             |
| Longest Palindromic Substring | Expand from center                             |
| Count Palindromic Substrings  | Expand from each center                        |
| Min Insertions                | n - LPS                                        |
| Min Cuts                      | dp[i] = min(dp[j] + 1) if s[j..i-1] palindrome |
+───────────────────────────────+────────────────────────────────────────────────+

INTERVAL DP for Palindromes:
    if s[i] == s[j]:
        dp[i][j] = dp[i+1][j-1] + 2
    else:
        dp[i][j] = max(dp[i+1][j], dp[i][j-1])

================================================================================
*/

