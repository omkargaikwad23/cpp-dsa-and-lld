/*
================================================================================
                    BIT MANIPULATION - BASIC OPERATIONS
================================================================================

Fundamental bit operations and their applications.
Time: O(1) for most operations | Space: O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Get, Set, Clear, Toggle Bit at Position i
─────────────────────────────────────────────────────
*/
class BitOperations {
public:
    // Get bit at position i (0-indexed from right)
    static int getBit(int n, int i) {
        return (n >> i) & 1;
    }
    
    // Set bit at position i to 1
    static int setBit(int n, int i) {
        return n | (1 << i);
    }
    
    // Clear bit at position i (set to 0)
    static int clearBit(int n, int i) {
        return n & ~(1 << i);
    }
    
    // Toggle bit at position i
    static int toggleBit(int n, int i) {
        return n ^ (1 << i);
    }
    
    // Update bit at position i to value v (0 or 1)
    static int updateBit(int n, int i, int v) {
        int mask = ~(1 << i);
        return (n & mask) | (v << i);
    }
    
    // Clear all bits from MSB to i (inclusive)
    static int clearBitsMSBtoI(int n, int i) {
        int mask = (1 << i) - 1;
        return n & mask;
    }
    
    // Clear all bits from i to 0 (inclusive)
    static int clearBitsIto0(int n, int i) {
        int mask = ~((1 << (i + 1)) - 1);
        return n & mask;
    }
};


/*
PROBLEM 2: Number of 1 Bits / Hamming Weight (LeetCode 191)
───────────────────────────────────────────────────────────
Count set bits in an integer.

Input: n = 11 (binary: 1011)
Output: 3

Time: O(k) where k = number of set bits | Space: O(1)
*/
int hammingWeight(uint32_t n) {
    int count = 0;
    while (n) {
        n &= (n - 1);  // Clear lowest set bit
        count++;
    }
    return count;
}

// Alternative using built-in
int hammingWeightBuiltin(uint32_t n) {
    return __builtin_popcount(n);
}


/*
PROBLEM 3: Power of Two (LeetCode 231)
──────────────────────────────────────
Check if n is a power of 2.

Power of 2 has exactly one set bit.
n & (n-1) clears the lowest set bit.

Input: n = 16
Output: true (binary: 10000)

Time: O(1) | Space: O(1)
*/
bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}


/*
PROBLEM 4: Power of Four (LeetCode 342)
───────────────────────────────────────
Check if n is a power of 4.

Power of 4: single bit at even position (0, 2, 4, ...)
Mask: 0x55555555 = 01010101... (bits at even positions)

Time: O(1) | Space: O(1)
*/
bool isPowerOfFour(int n) {
    // Must be power of 2 AND bit at even position
    return n > 0 && (n & (n - 1)) == 0 && (n & 0x55555555);
}


/*
PROBLEM 5: Reverse Bits (LeetCode 190)
──────────────────────────────────────
Reverse bits of a 32-bit unsigned integer.

Input:  00000010100101000001111010011100
Output: 00111001011110000010100101000000

Time: O(32) = O(1) | Space: O(1)
*/
uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; i++) {
        result = (result << 1) | (n & 1);
        n >>= 1;
    }
    return result;
}

// Optimized with divide and conquer
uint32_t reverseBitsOptimized(uint32_t n) {
    n = ((n & 0xffff0000) >> 16) | ((n & 0x0000ffff) << 16);
    n = ((n & 0xff00ff00) >> 8)  | ((n & 0x00ff00ff) << 8);
    n = ((n & 0xf0f0f0f0) >> 4)  | ((n & 0x0f0f0f0f) << 4);
    n = ((n & 0xcccccccc) >> 2)  | ((n & 0x33333333) << 2);
    n = ((n & 0xaaaaaaaa) >> 1)  | ((n & 0x55555555) << 1);
    return n;
}


/*
PROBLEM 6: Bitwise AND of Numbers Range (LeetCode 201)
──────────────────────────────────────────────────────
Find AND of all numbers in [left, right].

Key insight: Result is common prefix of left and right.
Any differing bit becomes 0 due to intermediate numbers.

Input: left = 5, right = 7
Output: 4 (101 & 110 & 111 = 100)

Time: O(log n) | Space: O(1)
*/
int rangeBitwiseAnd(int left, int right) {
    int shift = 0;
    
    // Find common prefix
    while (left < right) {
        left >>= 1;
        right >>= 1;
        shift++;
    }
    
    return left << shift;
}


/*
PROBLEM 7: Sum of Two Integers Without +/- (LeetCode 371)
─────────────────────────────────────────────────────────
Add two integers without using + or -.

XOR gives sum without carry.
AND gives carry positions.

Time: O(32) = O(1) | Space: O(1)
*/
int getSum(int a, int b) {
    while (b != 0) {
        int carry = (unsigned int)(a & b) << 1;  // Carry
        a = a ^ b;  // Sum without carry
        b = carry;
    }
    return a;
}


/*
PROBLEM 8: Divide Two Integers (LeetCode 29)
────────────────────────────────────────────
Divide without using *, /, %.

Use bit shifting for efficient division.

Time: O(log²n) | Space: O(1)
*/
int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    
    int sign = (dividend > 0) ^ (divisor > 0) ? -1 : 1;
    long long dvd = abs((long long)dividend);
    long long dvs = abs((long long)divisor);
    
    int result = 0;
    
    while (dvd >= dvs) {
        long long temp = dvs, multiple = 1;
        
        while (dvd >= (temp << 1)) {
            temp <<= 1;
            multiple <<= 1;
        }
        
        dvd -= temp;
        result += multiple;
    }
    
    return sign * result;
}


/*
PROBLEM 9: Binary Number with Alternating Bits (LeetCode 693)
─────────────────────────────────────────────────────────────
Check if binary representation has alternating bits.

Input: n = 5 (101)
Output: true

Input: n = 7 (111)
Output: false

Time: O(1) | Space: O(1)
*/
bool hasAlternatingBits(int n) {
    // n XOR (n >> 1) should be all 1s
    // e.g., 101 XOR 010 = 111
    long long x = n ^ (n >> 1);
    return (x & (x + 1)) == 0;
}


/*
PROBLEM 10: Binary Gap (LeetCode 868)
─────────────────────────────────────
Find longest distance between consecutive 1s.

Input: n = 22 (10110)
Output: 2

Time: O(log n) | Space: O(1)
*/
int binaryGap(int n) {
    int maxGap = 0, lastOne = -1;
    
    for (int i = 0; n > 0; i++, n >>= 1) {
        if (n & 1) {
            if (lastOne >= 0) {
                maxGap = max(maxGap, i - lastOne);
            }
            lastOne = i;
        }
    }
    
    return maxGap;
}


/*
PROBLEM 11: Complement of Base 10 Integer (LeetCode 1009)
─────────────────────────────────────────────────────────
Flip all bits of a number.

Input: n = 5 (101)
Output: 2 (010)

Time: O(log n) | Space: O(1)
*/
int bitwiseComplement(int n) {
    if (n == 0) return 1;
    
    // Find mask with all bits set up to MSB of n
    int mask = 1;
    while (mask < n) {
        mask = (mask << 1) | 1;
    }
    
    return n ^ mask;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Basic Bit Operations ===\n\n";
    
    // Bit operations
    int n = 5;  // 101
    cout << "n = " << n << " (binary: 101)\n";
    cout << "Get bit 2: " << BitOperations::getBit(n, 2) << "\n";
    cout << "Set bit 1: " << BitOperations::setBit(n, 1) << "\n";
    cout << "Clear bit 0: " << BitOperations::clearBit(n, 0) << "\n";
    cout << "Toggle bit 0: " << BitOperations::toggleBit(n, 0) << "\n\n";
    
    // Hamming Weight
    cout << "Hamming weight of 11: " << hammingWeight(11) << "\n";
    
    // Power of 2
    cout << "Is 16 power of 2? " << (isPowerOfTwo(16) ? "Yes" : "No") << "\n";
    
    // Power of 4
    cout << "Is 16 power of 4? " << (isPowerOfFour(16) ? "Yes" : "No") << "\n";
    
    // Range AND
    cout << "Range AND [5,7]: " << rangeBitwiseAnd(5, 7) << "\n";
    
    // Sum without +
    cout << "3 + 5 = " << getSum(3, 5) << "\n";
    
    // Alternating bits
    cout << "Alternating bits 5? " << (hasAlternatingBits(5) ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Operation                     | Expression                                     |
+───────────────────────────────+────────────────────────────────────────────────+
| Get bit i                     | (n >> i) & 1                                   |
| Set bit i                     | n | (1 << i)                                   |
| Clear bit i                   | n & ~(1 << i)                                  |
| Toggle bit i                  | n ^ (1 << i)                                   |
| Clear lowest set bit          | n & (n - 1)                                    |
| Get lowest set bit            | n & (-n)                                       |
| Check power of 2              | n > 0 && (n & (n-1)) == 0                      |
| Count set bits                | while(n) { n &= n-1; count++; }                |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

