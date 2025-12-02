/*
================================================================================
                    BIT MANIPULATION - OVERVIEW
================================================================================

Bit manipulation provides O(1) operations and constant space solutions.
Essential for Google interviews!

================================================================================
                           BASIC OPERATIONS
================================================================================

OPERATION           | EXPRESSION          | EXAMPLE (n=5, binary: 101)
--------------------|---------------------|-----------------------------
Set bit i           | n | (1 << i)        | Set bit 1: 101 | 010 = 111 (7)
Clear bit i         | n & ~(1 << i)       | Clear bit 2: 101 & 011 = 001 (1)
Toggle bit i        | n ^ (1 << i)        | Toggle bit 0: 101 ^ 001 = 100 (4)
Check bit i         | (n >> i) & 1        | Check bit 2: (101 >> 2) & 1 = 1
Get lowest set bit  | n & (-n)            | 101 & 011 = 001 (1)
Clear lowest set bit| n & (n - 1)         | 101 & 100 = 100 (4)
Check power of 2    | n && !(n & (n-1))   | 100 & 011 = 0 → power of 2
Count set bits      | __builtin_popcount  | popcount(101) = 2
Swap without temp   | a ^= b; b ^= a; a^=b| Swaps a and b

================================================================================
                           XOR PROPERTIES
================================================================================

1. a ^ a = 0         (same numbers cancel)
2. a ^ 0 = a         (identity)
3. a ^ b = b ^ a     (commutative)
4. (a ^ b) ^ c = a ^ (b ^ c)  (associative)

Applications:
- Find single number in array where others appear twice
- Find two unique numbers
- Swap without temp variable
- Missing number in range

================================================================================
                           COMMON PATTERNS
================================================================================

1. SINGLE NUMBER VARIANTS
   - XOR all elements to find unique
   - Divide by bit position for multiple uniques

2. COUNTING BITS
   - Brian Kernighan: n &= (n-1) clears lowest bit
   - DP: dp[i] = dp[i >> 1] + (i & 1)

3. SUBSET ENUMERATION
   - Iterate 0 to (1 << n) - 1
   - Each bit represents include/exclude

4. BITMASK DP
   - State compression using bits
   - Traveling Salesman, Assignment problems

5. POWER OF TWO/FOUR
   - n & (n-1) == 0 for power of 2
   - Additional mask check for power of 4

================================================================================
                           FILE ORGANIZATION
================================================================================

01_BasicOperations.cpp   - Fundamental bit operations
02_XORTricks.cpp         - Single number, swapping, XOR properties
03_CountingBits.cpp      - Popcount, Hamming distance
04_SubsetsBitmask.cpp    - Subset enumeration, bitmask DP
05_BitTricks.cpp         - Power of 2, reverse bits, advanced tricks

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Quick reference cheat sheet
void bitCheatSheet() {
    int n = 5;  // binary: 101
    
    // Basic operations
    cout << "n = " << n << " (binary: 101)\n";
    cout << "Set bit 1: " << (n | (1 << 1)) << "\n";      // 7
    cout << "Clear bit 2: " << (n & ~(1 << 2)) << "\n";   // 1
    cout << "Toggle bit 0: " << (n ^ (1 << 0)) << "\n";   // 4
    cout << "Check bit 2: " << ((n >> 2) & 1) << "\n";    // 1
    cout << "Lowest set bit: " << (n & (-n)) << "\n";     // 1
    cout << "Clear lowest set: " << (n & (n-1)) << "\n";  // 4
    cout << "Count set bits: " << __builtin_popcount(n) << "\n";  // 2
}

int main() {
    cout << "=== Bit Manipulation Patterns ===" << endl;
    bitCheatSheet();
    return 0;
}

