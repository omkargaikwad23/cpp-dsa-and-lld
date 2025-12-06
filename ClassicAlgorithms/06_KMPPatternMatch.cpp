/*
================================================================================
                    KMP (Knuth-Morris-Pratt) PATTERN MATCHING
================================================================================

PROBLEM: Find all occurrences of pattern in text.

KEY INSIGHT: When a mismatch occurs, use information about the pattern
             to skip comparisons that are guaranteed to fail.

CORE CONCEPT: LPS (Longest Proper Prefix which is also Suffix) array
  - lps[i] = length of longest proper prefix of pattern[0..i] 
             that is also a suffix

ALGORITHM:
1. Build LPS array for pattern: O(m)
2. Match pattern against text using LPS to skip: O(n)

TIME:  O(n + m)
SPACE: O(m) for LPS array

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// BUILD LPS (Longest Proper Prefix Suffix) ARRAY
// ═══════════════════════════════════════════════════════════════════════════

vector<int> buildLPS(const string& pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    
    int len = 0;  // Length of previous longest prefix suffix
    int i = 1;
    
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                // Try shorter prefix
                len = lps[len - 1];
                // Don't increment i
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

// ═══════════════════════════════════════════════════════════════════════════
// KMP SEARCH - Find all occurrences
// ═══════════════════════════════════════════════════════════════════════════

vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.size();
    int m = pattern.size();
    
    if (m == 0) return result;
    
    vector<int> lps = buildLPS(pattern);
    
    int i = 0;  // Index for text
    int j = 0;  // Index for pattern
    
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
            
            if (j == m) {
                // Pattern found at index (i - j)
                result.push_back(i - j);
                j = lps[j - 1];  // Look for next match
            }
        } else {
            if (j != 0) {
                j = lps[j - 1];  // Use LPS to skip
            } else {
                i++;
            }
        }
    }
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// FIND FIRST OCCURRENCE - LC 28: strStr()
// ═══════════════════════════════════════════════════════════════════════════

int strStr(string haystack, string needle) {
    if (needle.empty()) return 0;
    
    vector<int> lps = buildLPS(needle);
    int i = 0, j = 0;
    
    while (i < haystack.size()) {
        if (haystack[i] == needle[j]) {
            i++;
            j++;
            if (j == needle.size()) {
                return i - j;  // First occurrence
            }
        } else {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return -1;  // Not found
}

// ═══════════════════════════════════════════════════════════════════════════
// SHORTEST PALINDROME (LC 214) - KMP application
// ═══════════════════════════════════════════════════════════════════════════

string shortestPalindrome(string s) {
    // Find longest palindrome prefix, then prepend reverse of suffix
    // Use KMP: find longest prefix of s that matches suffix of reverse(s)
    
    string rev = s;
    reverse(rev.begin(), rev.end());
    string combined = s + "#" + rev;
    
    vector<int> lps = buildLPS(combined);
    
    int longestPalindromePrefixLen = lps.back();
    string toAdd = s.substr(longestPalindromePrefixLen);
    reverse(toAdd.begin(), toAdd.end());
    
    return toAdd + s;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test LPS array
    string pattern = "AABAACAABAA";
    vector<int> lps = buildLPS(pattern);
    
    cout << "Pattern: " << pattern << "\n";
    cout << "LPS:     ";
    for (int x : lps) cout << x;
    cout << "\n\n";
    
    // Test KMP search
    string text = "AABAACAADAABAABA";
    pattern = "AABA";
    
    cout << "Text:    " << text << "\n";
    cout << "Pattern: " << pattern << "\n";
    cout << "Found at indices: ";
    for (int idx : kmpSearch(text, pattern)) {
        cout << idx << " ";
    }
    cout << "\n\n";
    
    // Test strStr
    cout << "strStr(\"hello\", \"ll\"): " << strStr("hello", "ll") << "\n";
    cout << "strStr(\"aaaaa\", \"bba\"): " << strStr("aaaaa", "bba") << "\n\n";
    
    // Test shortest palindrome
    cout << "Shortest palindrome of \"aacecaaa\": " << shortestPalindrome("aacecaaa") << "\n";
    cout << "Shortest palindrome of \"abcd\": " << shortestPalindrome("abcd") << "\n";
    
    return 0;
}

/*
================================================================================
                         LPS ARRAY WALKTHROUGH
================================================================================

Pattern: "AABAACAABAA"
Index:    0 1 2 3 4 5 6 7 8 9 10
Char:     A A B A A C A A B A A
LPS:      0 1 0 1 2 0 1 2 3 4 5

lps[5] = 0 because "AABAA" + C has no proper prefix = suffix
lps[10] = 5 because "AABAACAABAA" has prefix "AABAA" = suffix "AABAA"

WHY KMP IS O(n + m):
- LPS build: O(m) - each char compared at most twice
- Search: O(n) - text pointer never goes backward
- Total: O(n + m)

RELATED PROBLEMS:
- LC 28: Find the Index of the First Occurrence in a String
- LC 214: Shortest Palindrome
- LC 459: Repeated Substring Pattern
- LC 1392: Longest Happy Prefix

================================================================================
*/

