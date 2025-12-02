/*
================================================================================
                    PATTERN 8: EDIT DISTANCE
================================================================================

When to use:
- Transform one sequence into another
- Operations: insert, delete, substitute (replace)
- String similarity/distance problems

LeetCode Problems:
- 72. Edit Distance
- 583. Delete Operation for Two Strings
- 712. Minimum ASCII Delete Sum for Two Strings

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Edit Distance (LeetCode 72) ⭐ CLASSIC
─────────────────────────────────────────────────
Min operations to transform word1 to word2.
Operations: insert, delete, replace.

dp[i][j] = edit distance for word1[0..i-1] and word2[0..j-1]

If word1[i-1] == word2[j-1]:
    dp[i][j] = dp[i-1][j-1]
Else:
    dp[i][j] = 1 + min(dp[i-1][j-1],  // replace
                       dp[i-1][j],     // delete from word1
                       dp[i][j-1])     // insert to word1

Time: O(m*n) | Space: O(n)
*/
int minDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    vector<int> dp(n + 1);
    
    // Base case: word1 is empty
    for (int j = 0; j <= n; j++) dp[j] = j;
    
    for (int i = 1; i <= m; i++) {
        int prev = dp[0];
        dp[0] = i;  // word2 is empty, delete all from word1
        
        for (int j = 1; j <= n; j++) {
            int curr = dp[j];
            if (word1[i-1] == word2[j-1]) {
                dp[j] = prev;
            } else {
                dp[j] = 1 + min({prev, dp[j], dp[j-1]});
            }
            prev = curr;
        }
    }
    
    return dp[n];
}


/*
PROBLEM 2: Delete Operation for Two Strings (LeetCode 583)
──────────────────────────────────────────────────────────
Min deletions to make two strings equal.

dp[i][j] = min deletions for word1[0..i-1] and word2[0..j-1]

Or use LCS: answer = m + n - 2*LCS

Time: O(m*n) | Space: O(n)
*/
int minDeleteDistance(string word1, string word2) {
    int m = word1.size(), n = word2.size();
    vector<int> dp(n + 1, 0);
    
    // Find LCS length
    for (int i = 1; i <= m; i++) {
        int prev = 0;
        for (int j = 1; j <= n; j++) {
            int curr = dp[j];
            if (word1[i-1] == word2[j-1]) {
                dp[j] = prev + 1;
            } else {
                dp[j] = max(dp[j], dp[j-1]);
            }
            prev = curr;
        }
    }
    
    return m + n - 2 * dp[n];
}


/*
PROBLEM 3: Minimum ASCII Delete Sum (LeetCode 712)
──────────────────────────────────────────────────
Min ASCII sum of deleted characters to make strings equal.

dp[i][j] = min cost for s1[0..i-1] and s2[0..j-1]

Time: O(m*n) | Space: O(n)
*/
int minimumDeleteSum(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<int> dp(n + 1, 0);
    
    // Base: delete all of s2
    for (int j = 1; j <= n; j++) {
        dp[j] = dp[j-1] + s2[j-1];
    }
    
    for (int i = 1; i <= m; i++) {
        int prev = dp[0];
        dp[0] += s1[i-1];  // Delete s1[i-1]
        
        for (int j = 1; j <= n; j++) {
            int curr = dp[j];
            if (s1[i-1] == s2[j-1]) {
                dp[j] = prev;  // No deletion needed
            } else {
                dp[j] = min(dp[j] + s1[i-1],      // Delete from s1
                           dp[j-1] + s2[j-1]);    // Delete from s2
            }
            prev = curr;
        }
    }
    
    return dp[n];
}


/*
PROBLEM 4: One Edit Distance (LeetCode 161)
───────────────────────────────────────────
Check if two strings are exactly one edit apart.

Time: O(n) | Space: O(1)
*/
bool isOneEditDistance(string s, string t) {
    int m = s.size(), n = t.size();
    if (abs(m - n) > 1) return false;
    
    if (m > n) swap(s, t), swap(m, n);  // Ensure s is shorter
    
    for (int i = 0; i < m; i++) {
        if (s[i] != t[i]) {
            if (m == n) return s.substr(i + 1) == t.substr(i + 1);  // Replace
            return s.substr(i) == t.substr(i + 1);  // Delete from t
        }
    }
    
    return n - m == 1;  // All chars match, t has one extra
}


/*
PROBLEM 5: Edit Distance with Different Costs
─────────────────────────────────────────────
Custom costs for insert, delete, replace.

Time: O(m*n) | Space: O(n)
*/
int editDistanceWithCosts(string s1, string s2, int insertCost, int deleteCost, int replaceCost) {
    int m = s1.size(), n = s2.size();
    vector<int> dp(n + 1);
    
    for (int j = 0; j <= n; j++) dp[j] = j * insertCost;
    
    for (int i = 1; i <= m; i++) {
        int prev = dp[0];
        dp[0] = i * deleteCost;
        
        for (int j = 1; j <= n; j++) {
            int curr = dp[j];
            if (s1[i-1] == s2[j-1]) {
                dp[j] = prev;
            } else {
                dp[j] = min({prev + replaceCost,
                            dp[j] + deleteCost,
                            dp[j-1] + insertCost});
            }
            prev = curr;
        }
    }
    
    return dp[n];
}


/*
PROBLEM 6: Regular Expression Matching (LeetCode 10)
────────────────────────────────────────────────────
'.' matches any single character.
'*' matches zero or more of the preceding element.

Time: O(m*n) | Space: O(n)
*/
bool isMatch(string s, string p) {
    int m = s.size(), n = p.size();
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
    dp[0][0] = true;
    
    // Handle patterns like a*, a*b*, etc. matching empty string
    for (int j = 2; j <= n; j++) {
        if (p[j-1] == '*') {
            dp[0][j] = dp[0][j-2];
        }
    }
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j-1] == '*') {
                // Zero occurrences of preceding char
                dp[i][j] = dp[i][j-2];
                // One or more occurrences
                if (p[j-2] == '.' || p[j-2] == s[i-1]) {
                    dp[i][j] = dp[i][j] || dp[i-1][j];
                }
            } else if (p[j-1] == '.' || p[j-1] == s[i-1]) {
                dp[i][j] = dp[i-1][j-1];
            }
        }
    }
    
    return dp[m][n];
}


/*
PROBLEM 7: Wildcard Matching (LeetCode 44)
──────────────────────────────────────────
'?' matches any single character.
'*' matches any sequence (including empty).

Time: O(m*n) | Space: O(n)
*/
bool isMatchWildcard(string s, string p) {
    int m = s.size(), n = p.size();
    vector<bool> dp(n + 1, false);
    dp[0] = true;
    
    // Handle leading *s
    for (int j = 1; j <= n && p[j-1] == '*'; j++) {
        dp[j] = true;
    }
    
    for (int i = 1; i <= m; i++) {
        bool prev = dp[0];
        dp[0] = false;
        
        for (int j = 1; j <= n; j++) {
            bool curr = dp[j];
            if (p[j-1] == '*') {
                dp[j] = dp[j-1] || dp[j];  // Match empty or consume char
            } else if (p[j-1] == '?' || p[j-1] == s[i-1]) {
                dp[j] = prev;
            } else {
                dp[j] = false;
            }
            prev = curr;
        }
    }
    
    return dp[n];
}


/*
PROBLEM 8: Interleaving String (LeetCode 97)
────────────────────────────────────────────
Check if s3 is interleaving of s1 and s2.

dp[i][j] = true if s1[0..i-1] and s2[0..j-1] interleave to form s3[0..i+j-1]

Time: O(m*n) | Space: O(n)
*/
bool isInterleave(string s1, string s2, string s3) {
    int m = s1.size(), n = s2.size();
    if (m + n != s3.size()) return false;
    
    vector<bool> dp(n + 1, false);
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 && j == 0) {
                dp[j] = true;
            } else if (i == 0) {
                dp[j] = dp[j-1] && s2[j-1] == s3[j-1];
            } else if (j == 0) {
                dp[j] = dp[j] && s1[i-1] == s3[i-1];
            } else {
                dp[j] = (dp[j] && s1[i-1] == s3[i+j-1]) ||
                        (dp[j-1] && s2[j-1] == s3[i+j-1]);
            }
        }
    }
    
    return dp[n];
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Edit Distance Pattern ===\n\n";
    
    // Edit Distance
    cout << "1. Edit distance (horse, ros): " << minDistance("horse", "ros") << "\n";
    
    // Delete Operations
    cout << "2. Min deletions (sea, eat): " << minDeleteDistance("sea", "eat") << "\n";
    
    // ASCII Delete Sum
    cout << "3. Min ASCII delete (sea, eat): " << minimumDeleteSum("sea", "eat") << "\n";
    
    // One Edit Distance
    cout << "4. One edit apart (ab, acb): " << (isOneEditDistance("ab", "acb") ? "Yes" : "No") << "\n";
    
    // Regex
    cout << "6. Regex match (aa, a*): " << (isMatch("aa", "a*") ? "Yes" : "No") << "\n";
    
    // Wildcard
    cout << "7. Wildcard match (adceb, *a*b): " << (isMatchWildcard("adceb", "*a*b") ? "Yes" : "No") << "\n";
    
    // Interleaving
    cout << "8. Interleave (aab,axy,aaxaby): " << (isInterleave("aab", "axy", "aaxaby") ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

EDIT DISTANCE TEMPLATE:
    if s1[i-1] == s2[j-1]:
        dp[i][j] = dp[i-1][j-1]
    else:
        dp[i][j] = 1 + min(dp[i-1][j-1],  // replace
                          dp[i-1][j],      // delete
                          dp[i][j-1])      // insert

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Operations                                     |
+───────────────────────────────+────────────────────────────────────────────────+
| Edit Distance                 | Insert, Delete, Replace (all cost 1)           |
| Delete Only                   | Only delete, or m + n - 2*LCS                  |
| ASCII Delete                  | Delete with ASCII costs                        |
| Regex Matching                | '.' any char, '*' zero or more of preceding    |
| Wildcard                      | '?' any char, '*' any sequence                 |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

