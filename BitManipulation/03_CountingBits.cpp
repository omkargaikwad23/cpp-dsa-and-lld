/*
================================================================================
                    BIT MANIPULATION - COUNTING BITS
================================================================================

Counting set bits (1s) in binary representations.
Key techniques:
- Brian Kernighan: n &= (n-1) clears lowest set bit
- DP: dp[i] = dp[i >> 1] + (i & 1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Counting Bits (LeetCode 338)
───────────────────────────────────────
Return array where ans[i] = number of 1s in binary of i.

Input: n = 5
Output: [0,1,1,2,1,2]

Approach: DP using dp[i] = dp[i >> 1] + (i & 1)

Time: O(n) | Space: O(n)
*/
vector<int> countBits(int n) {
    vector<int> dp(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i >> 1] + (i & 1);
        // Alternative: dp[i] = dp[i & (i-1)] + 1
    }
    
    return dp;
}


/*
PROBLEM 2: Hamming Distance (LeetCode 461)
──────────────────────────────────────────
Count positions where bits differ.

Input: x = 1, y = 4
Output: 2 (001 vs 100)

Time: O(1) | Space: O(1)
*/
int hammingDistance(int x, int y) {
    int diff = x ^ y;
    int count = 0;
    
    while (diff) {
        diff &= (diff - 1);  // Clear lowest set bit
        count++;
    }
    
    return count;
}


/*
PROBLEM 3: Total Hamming Distance (LeetCode 477)
────────────────────────────────────────────────
Sum of Hamming distances between all pairs.

Input: nums = [4,14,2]
Output: 6

Approach: Count 0s and 1s at each bit position.
Contribution = count0 * count1 for each position.

Time: O(32n) | Space: O(1)
*/
int totalHammingDistance(vector<int>& nums) {
    int n = nums.size(), total = 0;
    
    for (int i = 0; i < 32; i++) {
        int ones = 0;
        for (int num : nums) {
            ones += (num >> i) & 1;
        }
        int zeros = n - ones;
        total += ones * zeros;
    }
    
    return total;
}


/*
PROBLEM 4: Prime Number of Set Bits (LeetCode 762)
──────────────────────────────────────────────────
Count numbers in [left, right] with prime number of set bits.

Input: left = 10, right = 15
Output: 5

Time: O((right - left) * 32) | Space: O(1)
*/
int countPrimeSetBits(int left, int right) {
    // Prime set bits possible: 2,3,5,7,11,13,17,19 (up to 32 bits)
    unordered_set<int> primes = {2, 3, 5, 7, 11, 13, 17, 19};
    
    int count = 0;
    for (int i = left; i <= right; i++) {
        if (primes.count(__builtin_popcount(i))) {
            count++;
        }
    }
    
    return count;
}


/*
PROBLEM 5: Number Complement (LeetCode 476)
───────────────────────────────────────────
Flip all bits of a positive integer.

Input: num = 5 (101)
Output: 2 (010)

Time: O(log n) | Space: O(1)
*/
int findComplement(int num) {
    // Find mask with same number of bits all set to 1
    int mask = 1;
    while (mask < num) {
        mask = (mask << 1) | 1;
    }
    return num ^ mask;
}


/*
PROBLEM 6: Sort Integers by Number of 1 Bits (LeetCode 1356)
────────────────────────────────────────────────────────────
Sort by number of 1 bits (ascending), then by value.

Input: arr = [0,1,2,3,4,5,6,7,8]
Output: [0,1,2,4,8,3,5,6,7]

Time: O(n log n) | Space: O(1)
*/
vector<int> sortByBits(vector<int>& arr) {
    sort(arr.begin(), arr.end(), [](int a, int b) {
        int countA = __builtin_popcount(a);
        int countB = __builtin_popcount(b);
        if (countA != countB) return countA < countB;
        return a < b;
    });
    
    return arr;
}


/*
PROBLEM 7: Minimum Flips to Make a OR b Equal to c (LeetCode 1318)
─────────────────────────────────────────────────────────────────
Count flips to make a | b = c.

Input: a = 2, b = 6, c = 5
Output: 3

Time: O(32) | Space: O(1)
*/
int minFlips(int a, int b, int c) {
    int flips = 0;
    
    for (int i = 0; i < 32; i++) {
        int bitA = (a >> i) & 1;
        int bitB = (b >> i) & 1;
        int bitC = (c >> i) & 1;
        
        if (bitC == 0) {
            flips += bitA + bitB;  // Both must be 0
        } else {
            if (bitA == 0 && bitB == 0) flips++;  // At least one must be 1
        }
    }
    
    return flips;
}


/*
PROBLEM 8: Minimum Bit Flips to Convert Number (LeetCode 2220)
──────────────────────────────────────────────────────────────
Count bits that differ (same as Hamming distance).

Time: O(1) | Space: O(1)
*/
int minBitFlips(int start, int goal) {
    return __builtin_popcount(start ^ goal);
}


/*
PROBLEM 9: Number of Valid Words for Each Puzzle (LeetCode 1178)
────────────────────────────────────────────────────────────────
Word is valid for puzzle if:
- Contains first letter of puzzle
- Every letter is in puzzle

Input: words = ["aaaa","asas","able"], puzzles = ["aboveyz"]
Output: [1]

Approach: Bitmask words, enumerate subsets of puzzles.

Time: O(words * 26 + puzzles * 2^7) | Space: O(2^26)
*/
vector<int> findNumOfValidWords(vector<string>& words, vector<string>& puzzles) {
    unordered_map<int, int> wordMasks;
    
    // Count word masks
    for (const string& word : words) {
        int mask = 0;
        for (char c : word) {
            mask |= 1 << (c - 'a');
        }
        if (__builtin_popcount(mask) <= 7) {
            wordMasks[mask]++;
        }
    }
    
    vector<int> result;
    for (const string& puzzle : puzzles) {
        int mask = 0;
        for (char c : puzzle) {
            mask |= 1 << (c - 'a');
        }
        
        int firstBit = 1 << (puzzle[0] - 'a');
        int count = 0;
        
        // Enumerate subsets containing first letter
        int sub = mask;
        while (sub) {
            if (sub & firstBit) {
                if (wordMasks.count(sub)) {
                    count += wordMasks[sub];
                }
            }
            sub = (sub - 1) & mask;
        }
        
        result.push_back(count);
    }
    
    return result;
}


/*
PROBLEM 10: Count Number of Maximum Bitwise-OR Subsets (LeetCode 2044)
──────────────────────────────────────────────────────────────────────
Count subsets with maximum OR value.

Input: nums = [3,1]
Output: 2 ([3] and [3,1] both have OR = 3)

Time: O(2^n) | Space: O(1)
*/
int countMaxOrSubsets(vector<int>& nums) {
    int maxOr = 0;
    for (int num : nums) maxOr |= num;
    
    int count = 0;
    int n = nums.size();
    
    for (int mask = 1; mask < (1 << n); mask++) {
        int orVal = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                orVal |= nums[i];
            }
        }
        if (orVal == maxOr) count++;
    }
    
    return count;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Counting Bits ===\n\n";
    
    // Counting Bits
    auto bits = countBits(5);
    cout << "1. Count bits [0..5]: ";
    for (int b : bits) cout << b << " ";
    cout << "\n";
    
    // Hamming Distance
    cout << "2. Hamming distance (1, 4): " << hammingDistance(1, 4) << "\n";
    
    // Total Hamming Distance
    vector<int> nums = {4, 14, 2};
    cout << "3. Total Hamming distance: " << totalHammingDistance(nums) << "\n";
    
    // Prime Set Bits
    cout << "4. Prime set bits [10, 15]: " << countPrimeSetBits(10, 15) << "\n";
    
    // Complement
    cout << "5. Complement of 5: " << findComplement(5) << "\n";
    
    // Min Flips for OR
    cout << "7. Min flips (2|6=5): " << minFlips(2, 6, 5) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Operation                     | Method                                         |
+───────────────────────────────+────────────────────────────────────────────────+
| Count set bits                | __builtin_popcount(n) or Brian Kernighan       |
| Count bits DP                 | dp[i] = dp[i >> 1] + (i & 1)                   |
| Hamming distance              | popcount(a ^ b)                                |
| Total Hamming distance        | Sum(ones * zeros) for each bit position        |
| Find complement               | n ^ mask (where mask has all bits set)         |
+───────────────────────────────+────────────────────────────────────────────────+

BRIAN KERNIGHAN'S ALGORITHM:
while (n) { n &= (n-1); count++; }
- Clears lowest set bit each iteration
- Time: O(number of set bits)

================================================================================
*/

