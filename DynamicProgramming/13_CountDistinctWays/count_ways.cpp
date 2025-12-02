/*
================================================================================
                    PATTERN 13: COUNT DISTINCT WAYS
================================================================================

When to use:
- Count number of ways to achieve a goal
- Series of choices to reach target
- "How many ways" problems

LeetCode Problems:
- 91. Decode Ways
- 2266. Count Number of Texts

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Decode Ways (LeetCode 91) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────
'1'-'26' maps to 'A'-'Z'. Count decodings of digit string.

dp[i] = ways to decode s[0..i-1]

Time: O(n) | Space: O(1)
*/
int numDecodings(string s) {
    if (s.empty() || s[0] == '0') return 0;
    
    int prev2 = 1;  // dp[i-2]
    int prev1 = 1;  // dp[i-1]
    
    for (int i = 1; i < s.size(); i++) {
        int curr = 0;
        
        // Single digit
        if (s[i] != '0') curr = prev1;
        
        // Two digits
        int twoDigit = stoi(s.substr(i-1, 2));
        if (twoDigit >= 10 && twoDigit <= 26) {
            curr += prev2;
        }
        
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}


/*
PROBLEM 2: Decode Ways II (LeetCode 639)
────────────────────────────────────────
Same as above but '*' can be 1-9.

Time: O(n) | Space: O(1)
*/
int numDecodingsII(string s) {
    const int MOD = 1e9 + 7;
    if (s.empty()) return 0;
    
    long prev2 = 1;
    long prev1 = (s[0] == '*') ? 9 : (s[0] != '0' ? 1 : 0);
    
    for (int i = 1; i < s.size(); i++) {
        long curr = 0;
        
        // Single digit
        if (s[i] == '*') curr = 9 * prev1;
        else if (s[i] != '0') curr = prev1;
        
        // Two digits
        if (s[i-1] == '*') {
            if (s[i] == '*') {
                curr += 15 * prev2;  // 11-19, 21-26 (15 combos)
            } else if (s[i] <= '6') {
                curr += 2 * prev2;   // 1x or 2x
            } else {
                curr += prev2;       // Only 1x
            }
        } else if (s[i-1] == '1') {
            curr += (s[i] == '*' ? 9 : 1) * prev2;
        } else if (s[i-1] == '2') {
            if (s[i] == '*') curr += 6 * prev2;
            else if (s[i] <= '6') curr += prev2;
        }
        
        curr %= MOD;
        prev2 = prev1;
        prev1 = curr;
    }
    
    return prev1;
}


/*
PROBLEM 3: Count Number of Texts (LeetCode 2266)
────────────────────────────────────────────────
Phone keypad: 2-abc, 3-def, 4-ghi, 5-jkl, 6-mno, 7-pqrs, 8-tuv, 9-wxyz.
Count ways to type message.

Time: O(n) | Space: O(1)
*/
int countTexts(string pressedKeys) {
    const int MOD = 1e9 + 7;
    int n = pressedKeys.size();
    
    vector<long> dp(5, 0);
    dp[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        char c = pressedKeys[i-1];
        int maxPress = (c == '7' || c == '9') ? 4 : 3;
        
        dp[i % 5] = 0;
        for (int j = 1; j <= maxPress && i - j >= 0; j++) {
            if (pressedKeys[i-j] == c) {
                dp[i % 5] = (dp[i % 5] + dp[(i-j) % 5]) % MOD;
            } else {
                break;
            }
        }
    }
    
    return dp[n % 5];
}


/*
PROBLEM 4: Knight Dialer (LeetCode 935)
───────────────────────────────────────
Phone keypad, knight moves. Count n-digit numbers.

Time: O(n) | Space: O(1)
*/
int knightDialer(int n) {
    const int MOD = 1e9 + 7;
    
    // Valid moves from each digit
    vector<vector<int>> moves = {
        {4, 6}, {6, 8}, {7, 9}, {4, 8}, {0, 3, 9},
        {}, {0, 1, 7}, {2, 6}, {1, 3}, {2, 4}
    };
    
    vector<long> dp(10, 1);
    
    for (int step = 1; step < n; step++) {
        vector<long> newDp(10, 0);
        for (int digit = 0; digit <= 9; digit++) {
            for (int prev : moves[digit]) {
                newDp[digit] = (newDp[digit] + dp[prev]) % MOD;
            }
        }
        dp = newDp;
    }
    
    long total = 0;
    for (long count : dp) total = (total + count) % MOD;
    return total;
}


/*
PROBLEM 5: Count Stepping Numbers in Range (LeetCode 2801)
──────────────────────────────────────────────────────────
Count numbers where adjacent digits differ by 1.

Digit DP problem.

Time: O(digits * 10 * 2) | Space: O(digits * 10)
*/
class Solution2801 {
    const int MOD = 1e9 + 7;
    string num;
    vector<vector<vector<int>>> memo;
    
    int dp(int pos, int lastDigit, bool tight, bool started) {
        if (pos == num.size()) return started ? 1 : 0;
        
        int& res = memo[pos][lastDigit + 1][tight * 2 + started];
        if (res != -1) return res;
        
        int limit = tight ? (num[pos] - '0') : 9;
        res = 0;
        
        for (int d = 0; d <= limit; d++) {
            if (!started && d == 0) {
                res = (res + dp(pos + 1, -1, false, false)) % MOD;
            } else if (!started || abs(d - lastDigit) == 1) {
                res = (res + dp(pos + 1, d, tight && (d == limit), true)) % MOD;
            }
        }
        
        return res;
    }
    
    int count(string& s) {
        num = s;
        memo.assign(s.size(), vector<vector<int>>(11, vector<int>(4, -1)));
        return dp(0, -1, true, false);
    }
    
public:
    int countSteppingNumbers(string low, string high) {
        int highCount = count(high);
        
        // Subtract count for low-1
        int i = low.size() - 1;
        while (i >= 0 && low[i] == '0') {
            low[i] = '9';
            i--;
        }
        if (i >= 0) low[i]--;
        if (low[0] == '0' && low.size() > 1) low = low.substr(1);
        
        int lowCount = (low.empty() || low == "0") ? 0 : count(low);
        
        return ((highCount - lowCount) % MOD + MOD) % MOD;
    }
};


/*
PROBLEM 6: Count Vowels Permutation (LeetCode 1220)
───────────────────────────────────────────────────
Count strings of length n following vowel rules.

a -> e
e -> a, i
i -> a, e, o, u
o -> i, u
u -> a

Time: O(n) | Space: O(1)
*/
int countVowelPermutation(int n) {
    const int MOD = 1e9 + 7;
    
    long a = 1, e = 1, i = 1, o = 1, u = 1;
    
    for (int step = 1; step < n; step++) {
        long newA = (e + i + u) % MOD;
        long newE = (a + i) % MOD;
        long newI = (e + o) % MOD;
        long newO = i;
        long newU = (i + o) % MOD;
        
        a = newA; e = newE; i = newI; o = newO; u = newU;
    }
    
    return (a + e + i + o + u) % MOD;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Count Distinct Ways ===\n\n";
    
    // Decode Ways
    cout << "1. Decode '226': " << numDecodings("226") << "\n";
    cout << "   Decode '12': " << numDecodings("12") << "\n";
    
    // Count Texts
    cout << "3. Count texts '22233': " << countTexts("22233") << "\n";
    
    // Knight Dialer
    cout << "4. Knight dialer (n=3): " << knightDialer(3) << "\n";
    
    // Vowel Permutation
    cout << "6. Vowel permutation (n=2): " << countVowelPermutation(2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

COUNT WAYS TEMPLATE:
    dp[0] = 1  // Base: one way to achieve nothing
    for i = 1 to n:
        for each valid previous state j:
            dp[i] += dp[j]
    return dp[n]

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Transition                                     |
+───────────────────────────────+────────────────────────────────────────────────+
| Decode Ways                   | Take 1 digit or 2 digits (10-26)               |
| Count Texts                   | Take 1-3 (or 1-4) same digits                  |
| Knight Dialer                 | Valid knight moves between digits              |
| Vowel Permutation             | Follow vowel transition rules                  |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

