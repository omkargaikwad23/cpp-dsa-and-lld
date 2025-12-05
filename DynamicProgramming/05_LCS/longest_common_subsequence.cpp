/*
================================================================================
                    PATTERN 5: LONGEST COMMON SUBSEQUENCE (LCS)
================================================================================

When to use:
- Find subsequence appearing in same order in both sequences
- String comparison problems
- Sequence alignment

LeetCode Problems:
- 1143. Longest Common Subsequence
- 583. Delete Operation for Two Strings
- 1092. Shortest Common Supersequence

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Longest Common Subsequence (LeetCode 1143) ⭐ CLASSIC
───────────────────────────────────────────────────────────────
Find length of LCS of two strings.

dp[i][j] = LCS of s1[0..i-1] and s2[0..j-1]
If s1[i-1] == s2[j-1]: dp[i][j] = dp[i-1][j-1] + 1
Else: dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Time: O(m*n) | Space: O(m*n)
*/
int longestCommonSubsequence(string text1, string text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i-1] == text2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[m][n];
}

// Space optimized O(n)
int lcsOptimized(string& s1, string& s2) {
    int m = s1.size(), n = s2.size();
    vector<int> dp(n + 1, 0);
    
    for (int i = 1; i <= m; i++) {
        int prev = 0;
        for (int j = 1; j <= n; j++) {
            int curr = dp[j];
            if (s1[i-1] == s2[j-1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = max(dp[j], dp[j-1]);
            }
            prev = curr;
        }
    }
    
    return dp[n];
}


/*
PROBLEM 2: Print LCS
────────────────────
Reconstruct the actual LCS string.

Time: O(m*n) | Space: O(m*n)
*/
string printLCS(string& s1, string& s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i-1] == s2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Backtrack to find LCS
    string lcs = "";
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i-1] == s2[j-1]) {
            lcs = s1[i-1] + lcs;
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return lcs;
}


/*
PROBLEM 3: Delete Operation for Two Strings (LeetCode 583)
──────────────────────────────────────────────────────────
Min deletions to make two strings equal.

Answer = m + n - 2 * LCS

Time: O(m*n) | Space: O(n)
*/
int minDistance(string word1, string word2) {
    int lcs = longestCommonSubsequence(word1, word2);
    return word1.size() + word2.size() - 2 * lcs;
}


/*
PROBLEM 4: Shortest Common Supersequence (LeetCode 1092)
────────────────────────────────────────────────────────
Find shortest string containing both s1 and s2 as subsequences.

Length = m + n - LCS
Build by backtracking through LCS table.

Time: O(m*n) | Space: O(m*n)
*/
string shortestCommonSupersequence(string str1, string str2) {
    int m = str1.size(), n = str2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    // Build LCS table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    // Build SCS by backtracking
    string scs = "";
    int i = m, j = n;
    
    while (i > 0 && j > 0) {
        if (str1[i-1] == str2[j-1]) {
            scs = str1[i-1] + scs;
            i--; j--;
        } else if (dp[i-1][j] > dp[i][j-1]) {
            scs = str1[i-1] + scs;
            i--;
        } else {
            scs = str2[j-1] + scs;
            j--;
        }
    }
    
    // Add remaining characters
    while (i > 0) scs = str1[--i] + scs;
    while (j > 0) scs = str2[--j] + scs;
    
    return scs;
}


/*
PROBLEM 5: Longest Repeating Subsequence
────────────────────────────────────────
Find longest subsequence that appears at least twice.
Same as LCS(s, s) but characters at different indices.

Time: O(n²) | Space: O(n)
*/
int longestRepeatingSubsequence(string s) {
    int n = s.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s[i-1] == s[j-1] && i != j) {  // Different indices!
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    
    return dp[n][n];
}


/*
PROBLEM 6: Uncrossed Lines (LeetCode 1035)
──────────────────────────────────────────
Connect matching elements with non-crossing lines.
This is exactly LCS!

Time: O(m*n) | Space: O(n)
*/
int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    vector<int> dp(n + 1, 0);
    
    for (int i = 1; i <= m; i++) {
        int prev = 0;
        for (int j = 1; j <= n; j++) {
            int curr = dp[j];
            if (nums1[i-1] == nums2[j-1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = max(dp[j], dp[j-1]);
            }
            prev = curr;
        }
    }
    
    return dp[n];
}


/*
PROBLEM 7: Max Dot Product of Two Subsequences (LeetCode 1458)
──────────────────────────────────────────────────────────────
Find max dot product of subsequences (same length).

dp[i][j] = max dot product using nums1[0..i-1] and nums2[0..j-1]

Time: O(m*n) | Space: O(n)
*/
int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
    int m = nums1.size(), n = nums2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MIN));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int prod = nums1[i-1] * nums2[j-1];
            dp[i][j] = max({
                prod,                               // Take only this pair
                dp[i-1][j-1] + prod,               // Extend previous
                dp[i-1][j],                        // Skip nums1[i-1]
                dp[i][j-1]                         // Skip nums2[j-1]
            });
        }
    }
    
    return dp[m][n];
}


/*
PROBLEM 8: Distinct Subsequences (LeetCode 115)
───────────────────────────────────────────────
Count distinct subsequences of s that equal t.

dp[i][j] = ways to form t[0..j-1] from s[0..i-1]

Time: O(m*n) | Space: O(n)
*/
int numDistinct(string s, string t) {
    int m = s.size(), n = t.size();
    vector<unsigned long long> dp(n + 1, 0);
    dp[0] = 1;  // Empty t can be formed from any s
    
    for (int i = 1; i <= m; i++) {
        for (int j = n; j >= 1; j--) {  // Backwards to avoid overwriting
            if (s[i-1] == t[j-1]) {
                dp[j] += dp[j-1];
            }
        }
    }
    
    return dp[n];
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== LCS Pattern ===\n\n";
    
    // LCS
    string s1 = "abcde", s2 = "ace";
    cout << "1. LCS length: " << longestCommonSubsequence(s1, s2) << "\n";
    cout << "   LCS string: " << printLCS(s1, s2) << "\n";
    
    // Delete Operations
    cout << "3. Min deletions (sea, eat): " << minDistance("sea", "eat") << "\n";
    
    // Shortest Common Supersequence
    cout << "4. SCS (abac, cab): " << shortestCommonSupersequence("abac", "cab") << "\n";
    
    // Longest Repeating Subsequence
    cout << "5. Longest repeating (axxxy): " << longestRepeatingSubsequence("axxxy") << "\n";
    
    // Uncrossed Lines
    vector<int> n1 = {1, 4, 2}, n2 = {1, 2, 4};
    cout << "6. Max uncrossed lines: " << maxUncrossedLines(n1, n2) << "\n";
    
    // Distinct Subsequences
    cout << "8. Distinct subsequences (rabbbit, rabbit): " << numDistinct("rabbbit", "rabbit") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

LCS TEMPLATE:
    for i = 1 to m:
        for j = 1 to n:
            if s1[i-1] == s2[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
            else:
                dp[i][j] = max(dp[i-1][j], dp[i][j-1])

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Formula                                        |
+───────────────────────────────+────────────────────────────────────────────────+
| LCS Length                    | Standard LCS                                   |
| Min Deletions                 | m + n - 2*LCS                                  |
| Shortest Common Superseq      | m + n - LCS, backtrack to build                |
| Longest Repeating Subseq      | LCS(s, s) with i != j                          |
| Uncrossed Lines               | Exactly LCS                                    |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

