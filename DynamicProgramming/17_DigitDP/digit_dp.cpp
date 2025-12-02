/*
================================================================================
                    PATTERN 17: DIGIT DP
================================================================================

When to use:
- Counting numbers in range with digit constraints
- Large ranges (up to 10^18)
- Properties based on individual digits

LeetCode Problems:
- 357. Count Numbers with Unique Digits
- 233. Number of Digit One
- 902. Numbers At Most N Given Digit Set

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
DIGIT DP TEMPLATE
─────────────────
State: (position, tight bound, started, extra state)
- position: current digit position
- tight: whether we're still at upper bound
- started: whether we've placed non-zero digit
- extra: problem-specific state (e.g., mask for unique digits)
*/

/*
PROBLEM 1: Count Numbers with Unique Digits (LeetCode 357)
──────────────────────────────────────────────────────────
Count numbers in [0, 10^n) with all unique digits.

Time: O(10^n) but math solution is O(n) | Space: O(n)
*/
int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1;
    
    int result = 10;  // 0-9
    int available = 9;
    int current = 9;  // First digit can't be 0
    
    for (int i = 2; i <= n && available > 0; i++) {
        current *= available;
        result += current;
        available--;
    }
    
    return result;
}


/*
PROBLEM 2: Number of Digit One (LeetCode 233)
─────────────────────────────────────────────
Count occurrences of digit 1 in [1, n].

Digit DP or mathematical approach.

Time: O(log n) | Space: O(1)
*/
int countDigitOne(int n) {
    if (n <= 0) return 0;
    
    long long count = 0;
    long long factor = 1;
    
    while (factor <= n) {
        long long higher = n / (factor * 10);
        long long current = (n / factor) % 10;
        long long lower = n % factor;
        
        if (current == 0) {
            count += higher * factor;
        } else if (current == 1) {
            count += higher * factor + lower + 1;
        } else {
            count += (higher + 1) * factor;
        }
        
        factor *= 10;
    }
    
    return count;
}


/*
PROBLEM 3: Numbers At Most N Given Digit Set (LeetCode 902)
───────────────────────────────────────────────────────────
Count numbers <= n using only digits from given set.

Time: O(log n * |digits|) | Space: O(log n)
*/
int atMostNGivenDigitSet(vector<string>& digits, int n) {
    string s = to_string(n);
    int len = s.size();
    int d = digits.size();
    
    int count = 0;
    
    // Numbers with fewer digits
    for (int i = 1; i < len; i++) {
        count += pow(d, i);
    }
    
    // Numbers with same length
    for (int i = 0; i < len; i++) {
        bool found = false;
        
        for (const string& digit : digits) {
            if (digit[0] < s[i]) {
                count += pow(d, len - i - 1);
            } else if (digit[0] == s[i]) {
                found = true;
            }
        }
        
        if (!found) return count;
    }
    
    return count + 1;  // Include n itself
}


/*
PROBLEM 4: Count Special Integers (LeetCode 2376)
─────────────────────────────────────────────────
Count positive integers <= n with all distinct digits.

Digit DP with bitmask for used digits.

Time: O(10 * 2^10 * log n) | Space: O(10 * 2^10)
*/
class Solution2376 {
    string num;
    int memo[11][1024][2][2];
    
    int dp(int pos, int mask, bool tight, bool started) {
        if (pos == num.size()) return started ? 1 : 0;
        
        int& res = memo[pos][mask][tight][started];
        if (res != -1) return res;
        res = 0;
        
        int limit = tight ? (num[pos] - '0') : 9;
        
        for (int d = 0; d <= limit; d++) {
            if (!started && d == 0) {
                res += dp(pos + 1, mask, false, false);
            } else if (!(mask & (1 << d))) {
                res += dp(pos + 1, mask | (1 << d), tight && (d == limit), true);
            }
        }
        
        return res;
    }
    
public:
    int countSpecialNumbers(int n) {
        num = to_string(n);
        memset(memo, -1, sizeof(memo));
        return dp(0, 0, true, false);
    }
};


/*
PROBLEM 5: Non-negative Integers without Consecutive Ones (LeetCode 600)
────────────────────────────────────────────────────────────────────────
Count numbers <= n without consecutive 1s in binary.

Time: O(log n) | Space: O(log n)
*/
int findIntegers(int n) {
    // Fibonacci-based: f[i] = count for i bits
    vector<int> fib(32);
    fib[0] = 1; fib[1] = 2;
    for (int i = 2; i < 32; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    int count = 0;
    int prevBit = 0;
    
    for (int i = 30; i >= 0; i--) {
        if (n & (1 << i)) {
            count += fib[i];  // All numbers with this bit = 0
            if (prevBit) return count;  // Two consecutive 1s
            prevBit = 1;
        } else {
            prevBit = 0;
        }
    }
    
    return count + 1;  // Include n itself
}


/*
PROBLEM 6: Numbers With Repeated Digits (LeetCode 1012)
───────────────────────────────────────────────────────
Count numbers <= n with at least one repeated digit.

Answer = n - count(unique digits)

Time: O(10 * 2^10 * log n) | Space: O(10 * 2^10)
*/
class Solution1012 {
    int countUnique(int n) {
        if (n < 0) return 0;
        string s = to_string(n);
        int len = s.size();
        
        int count = 0;
        
        // Numbers with fewer digits
        for (int i = 1; i < len; i++) {
            count += 9 * permutation(9, i - 1);
        }
        
        // Numbers with same length
        unordered_set<int> used;
        for (int i = 0; i < len; i++) {
            int limit = s[i] - '0';
            
            for (int d = (i == 0 ? 1 : 0); d < limit; d++) {
                if (!used.count(d)) {
                    count += permutation(9 - i, len - i - 1);
                }
            }
            
            if (used.count(limit)) break;
            used.insert(limit);
            
            if (i == len - 1) count++;  // Include n itself
        }
        
        return count;
    }
    
    int permutation(int n, int r) {
        int result = 1;
        for (int i = 0; i < r; i++) {
            result *= (n - i);
        }
        return result;
    }
    
public:
    int numDupDigitsAtMostN(int n) {
        return n - countUnique(n);
    }
};


// ============================================================================
// DIGIT DP TEMPLATE (Generic)
// ============================================================================

class DigitDPTemplate {
    string num;
    // memo[pos][state][tight][started]
    map<tuple<int, int, bool, bool>, int> memo;
    
    int dp(int pos, int state, bool tight, bool started) {
        if (pos == num.size()) {
            // Return 1 if valid, 0 otherwise
            return started ? 1 : 0;
        }
        
        auto key = make_tuple(pos, state, tight, started);
        if (memo.count(key)) return memo[key];
        
        int limit = tight ? (num[pos] - '0') : 9;
        int result = 0;
        
        for (int d = 0; d <= limit; d++) {
            if (!started && d == 0) {
                // Leading zero
                result += dp(pos + 1, state, false, false);
            } else {
                // Check if digit d is valid given current state
                int newState = state;  // Update state based on problem
                result += dp(pos + 1, newState, tight && (d == limit), true);
            }
        }
        
        return memo[key] = result;
    }
    
public:
    int count(int n) {
        num = to_string(n);
        memo.clear();
        return dp(0, 0, true, false);
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Digit DP ===\n\n";
    
    // Unique Digits
    cout << "1. Unique digits (n=2): " << countNumbersWithUniqueDigits(2) << "\n";
    
    // Count Ones
    cout << "2. Digit ones in [1,13]: " << countDigitOne(13) << "\n";
    
    // Given Digit Set
    vector<string> digits = {"1", "3", "5", "7"};
    cout << "3. At most 100: " << atMostNGivenDigitSet(digits, 100) << "\n";
    
    // Special Integers
    Solution2376 sol;
    cout << "4. Special integers <= 20: " << sol.countSpecialNumbers(20) << "\n";
    
    // No Consecutive Ones
    cout << "5. No consecutive 1s <= 5: " << findIntegers(5) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

DIGIT DP TEMPLATE:
    dp(pos, state, tight, started):
        if pos == n: return valid
        
        limit = num[pos] if tight else 9
        for d = 0 to limit:
            if not started and d == 0:
                result += dp(pos+1, state, false, false)
            else:
                newState = transition(state, d)
                result += dp(pos+1, newState, tight && d==limit, true)
        return result

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Extra State                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Unique digits                 | Bitmask of used digits                         |
| Count digit d                 | Running count                                  |
| No consecutive                | Last digit or last bit                         |
| Given digit set               | Position only                                  |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

