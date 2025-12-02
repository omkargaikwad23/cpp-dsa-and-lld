/*
================================================================================
                    BIT MANIPULATION - ADVANCED TRICKS
================================================================================

Advanced bit manipulation techniques and optimizations.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: UTF-8 Validation (LeetCode 393)
──────────────────────────────────────────
Validate if array represents valid UTF-8 encoding.

Rules:
- 1 byte:  0xxxxxxx
- 2 bytes: 110xxxxx 10xxxxxx
- 3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
- 4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

Time: O(n) | Space: O(1)
*/
bool validUtf8(vector<int>& data) {
    int remaining = 0;
    
    for (int byte : data) {
        byte &= 0xFF;  // Only consider last 8 bits
        
        if (remaining == 0) {
            if ((byte >> 7) == 0) remaining = 0;           // 0xxxxxxx
            else if ((byte >> 5) == 0b110) remaining = 1;  // 110xxxxx
            else if ((byte >> 4) == 0b1110) remaining = 2; // 1110xxxx
            else if ((byte >> 3) == 0b11110) remaining = 3;// 11110xxx
            else return false;
        } else {
            if ((byte >> 6) != 0b10) return false;         // Must be 10xxxxxx
            remaining--;
        }
    }
    
    return remaining == 0;
}


/*
PROBLEM 2: Gray Code (LeetCode 89)
──────────────────────────────────
Generate n-bit Gray code sequence.
Adjacent numbers differ by exactly one bit.

Input: n = 2
Output: [0,1,3,2] (00, 01, 11, 10)

Gray code formula: i ^ (i >> 1)

Time: O(2^n) | Space: O(2^n)
*/
vector<int> grayCode(int n) {
    vector<int> result;
    for (int i = 0; i < (1 << n); i++) {
        result.push_back(i ^ (i >> 1));
    }
    return result;
}


/*
PROBLEM 3: Circular Permutation in Binary (LeetCode 1238)
─────────────────────────────────────────────────────────
Gray code starting from a specific number.

Time: O(2^n) | Space: O(2^n)
*/
vector<int> circularPermutation(int n, int start) {
    vector<int> result;
    for (int i = 0; i < (1 << n); i++) {
        result.push_back(start ^ i ^ (i >> 1));
    }
    return result;
}


/*
PROBLEM 4: Maximum Product of Word Lengths (LeetCode 318)
─────────────────────────────────────────────────────────
Find max product of lengths of two words with no common letters.

Approach: Represent each word as bitmask of letters.

Time: O(n² + total_chars) | Space: O(n)
*/
int maxProduct(vector<string>& words) {
    int n = words.size();
    vector<int> masks(n, 0);
    
    // Build bitmask for each word
    for (int i = 0; i < n; i++) {
        for (char c : words[i]) {
            masks[i] |= 1 << (c - 'a');
        }
    }
    
    int maxProd = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((masks[i] & masks[j]) == 0) {  // No common letters
                maxProd = max(maxProd, (int)(words[i].size() * words[j].size()));
            }
        }
    }
    
    return maxProd;
}


/*
PROBLEM 5: Integer Replacement (LeetCode 397)
─────────────────────────────────────────────
Minimum operations to reduce n to 1:
- If even: n → n/2
- If odd: n → n+1 or n-1

Key insight: Look at last 2 bits for odd numbers.
- ...01 → prefer -1
- ...11 → prefer +1 (except n=3)

Time: O(log n) | Space: O(1)
*/
int integerReplacement(int n) {
    int count = 0;
    long long num = n;  // Avoid overflow for n = INT_MAX
    
    while (num > 1) {
        if (num % 2 == 0) {
            num /= 2;
        } else if (num == 3 || (num & 2) == 0) {
            num--;  // ...01 pattern
        } else {
            num++;  // ...11 pattern
        }
        count++;
    }
    
    return count;
}


/*
PROBLEM 6: Concatenation of Consecutive Binary Numbers (LeetCode 1680)
──────────────────────────────────────────────────────────────────────
Concatenate binary of 1 to n. Return mod 10^9+7.

Input: n = 3
Output: 27 (binary: 1 + 10 + 11 = 11011 = 27)

Time: O(n) | Space: O(1)
*/
int concatenatedBinary(int n) {
    const int MOD = 1e9 + 7;
    long long result = 0;
    int length = 0;  // Current number of bits needed
    
    for (int i = 1; i <= n; i++) {
        // Update length when i is power of 2
        if ((i & (i - 1)) == 0) {
            length++;
        }
        result = ((result << length) | i) % MOD;
    }
    
    return result;
}


/*
PROBLEM 7: Minimum One Bit Operations to Make Integer Zero (LeetCode 1611)
──────────────────────────────────────────────────────────────────────────
Operations: flip rightmost bit or flip bit left of rightmost 1.

This is related to Gray code!

Time: O(log n) | Space: O(1)
*/
int minimumOneBitOperations(int n) {
    // Number of steps to reach n in Gray code from 0
    int result = 0;
    while (n) {
        result ^= n;
        n >>= 1;
    }
    return result;
}


/*
PROBLEM 8: Find Kth Largest XOR Coordinate Value (LeetCode 1738)
───────────────────────────────────────────────────────────────
2D prefix XOR, find kth largest.

Time: O(mn log k) | Space: O(mn)
*/
int kthLargestValue(vector<vector<int>>& matrix, int k) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> prefix(m + 1, vector<int>(n + 1, 0));
    priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            prefix[i][j] = prefix[i-1][j] ^ prefix[i][j-1] ^ 
                          prefix[i-1][j-1] ^ matrix[i-1][j-1];
            
            pq.push(prefix[i][j]);
            if (pq.size() > k) pq.pop();
        }
    }
    
    return pq.top();
}


/*
PROBLEM 9: Check If a String Contains All Binary Codes of Size K (LeetCode 1461)
────────────────────────────────────────────────────────────────────────────────
Check if string contains all binary strings of length k.

Time: O(n) | Space: O(2^k)
*/
bool hasAllCodes(string s, int k) {
    if (s.size() < k) return false;
    
    unordered_set<int> seen;
    int mask = (1 << k) - 1;
    int curr = 0;
    
    for (int i = 0; i < s.size(); i++) {
        curr = ((curr << 1) | (s[i] - '0')) & mask;
        if (i >= k - 1) {
            seen.insert(curr);
        }
    }
    
    return seen.size() == (1 << k);
}


/*
PROBLEM 10: Bitwise ORs of Subarrays (LeetCode 898)
───────────────────────────────────────────────────
Count distinct values of OR of all subarrays.

Key insight: OR can only increase or stay same.
At each position, limited distinct values (at most 32).

Time: O(n * 32) | Space: O(n * 32)
*/
int subarrayBitwiseORs(vector<int>& arr) {
    unordered_set<int> result, current, next;
    
    for (int num : arr) {
        next.clear();
        next.insert(num);
        for (int prev : current) {
            next.insert(prev | num);
        }
        current = next;
        result.insert(current.begin(), current.end());
    }
    
    return result.size();
}


// ============================================================================
// USEFUL BIT TRICKS REFERENCE
// ============================================================================

void bitTricksReference() {
    cout << "=== Useful Bit Tricks ===\n\n";
    
    // Get lowest set bit
    int n = 12;  // 1100
    cout << "Lowest set bit of " << n << ": " << (n & -n) << "\n";
    
    // Check if number is power of 2
    cout << "Is 16 power of 2? " << (16 > 0 && (16 & 15) == 0) << "\n";
    
    // Turn off rightmost 1
    cout << "Turn off rightmost 1 in 12: " << (12 & 11) << "\n";
    
    // Isolate rightmost 0
    cout << "Isolate rightmost 0 in 10: " << (~10 & (10 + 1)) << "\n";
    
    // Turn on rightmost 0
    cout << "Turn on rightmost 0 in 10: " << (10 | (10 + 1)) << "\n";
    
    // Count trailing zeros
    cout << "Trailing zeros in 8: " << __builtin_ctz(8) << "\n";
    
    // Count leading zeros
    cout << "Leading zeros in 8: " << __builtin_clz(8) << "\n";
    
    // Log base 2 (floor)
    cout << "Log2(15): " << (31 - __builtin_clz(15)) << "\n";
    
    // Next power of 2
    int x = 13;
    x--;
    x |= x >> 1; x |= x >> 2; x |= x >> 4; x |= x >> 8; x |= x >> 16;
    x++;
    cout << "Next power of 2 after 13: " << x << "\n";
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Advanced Bit Tricks ===\n\n";
    
    // Gray Code
    auto gray = grayCode(3);
    cout << "2. Gray code (n=3): ";
    for (int g : gray) cout << g << " ";
    cout << "\n";
    
    // Max Product
    vector<string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
    cout << "4. Max product of word lengths: " << maxProduct(words) << "\n";
    
    // Integer Replacement
    cout << "5. Min operations for 8: " << integerReplacement(8) << "\n";
    
    // Concatenated Binary
    cout << "6. Concatenated binary (n=3): " << concatenatedBinary(3) << "\n";
    
    // Has All Codes
    cout << "9. 'aab00011011' has all 2-bit codes? " 
         << (hasAllCodes("00110110", 2) ? "Yes" : "No") << "\n";
    
    cout << "\n";
    bitTricksReference();
    
    return 0;
}

/*
================================================================================
                              CHEAT SHEET
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Operation                     | Expression                                     |
+───────────────────────────────+────────────────────────────────────────────────+
| Get lowest set bit            | n & (-n)                                       |
| Clear lowest set bit          | n & (n - 1)                                    |
| Set lowest 0 bit              | n | (n + 1)                                    |
| Clear lowest 0 bit            | n & (n + 1)                                    |
| Gray code                     | i ^ (i >> 1)                                   |
| Inverse Gray code             | while(n) { result ^= n; n >>= 1; }             |
| Count trailing zeros          | __builtin_ctz(n)                               |
| Count leading zeros           | __builtin_clz(n)                               |
| Floor(log2(n))                | 31 - __builtin_clz(n)                          |
| Ceil(log2(n))                 | 32 - __builtin_clz(n - 1)                      |
| Is power of 2                 | n && !(n & (n - 1))                            |
| Next power of 2               | 1 << (32 - __builtin_clz(n - 1))               |
| Swap a and b                  | a ^= b; b ^= a; a ^= b;                        |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

