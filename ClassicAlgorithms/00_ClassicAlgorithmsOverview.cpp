/*
================================================================================
                    CLASSIC ALGORITHMS - INTERVIEW MUST-KNOW
================================================================================

This folder contains standard algorithms frequently asked in FAANG interviews.
Each algorithm is a "named technique" that you should recognize instantly.

================================================================================
                         INDEX OF ALGORITHMS
================================================================================

01_BoyerMooreMajority.cpp
   - Find majority element (appears > n/2 times)
   - TIME: O(n) | SPACE: O(1)
   - Problems: LC 169, LC 229

02_DutchNationalFlag.cpp
   - Sort array with 3 distinct values (0, 1, 2)
   - TIME: O(n) | SPACE: O(1)
   - Problems: LC 75 Sort Colors

03_FloydCycleDetection.cpp
   - Detect cycle in linked list / find duplicate
   - TIME: O(n) | SPACE: O(1)
   - Problems: LC 141, LC 142, LC 287

04_QuickSelect.cpp
   - Find Kth smallest/largest element
   - TIME: O(n) average | SPACE: O(1)
   - Problems: LC 215, LC 347

05_ReservoirSampling.cpp
   - Random sampling from stream of unknown size
   - TIME: O(n) | SPACE: O(k)
   - Problems: LC 382, LC 398

06_FisherYatesShuffle.cpp
   - Randomly shuffle array with uniform distribution
   - TIME: O(n) | SPACE: O(1)
   - Problems: LC 384

07_KMPPatternMatch.cpp
   - Find pattern in string efficiently
   - TIME: O(n + m) | SPACE: O(m)
   - Problems: LC 28, LC 214

08_RabinKarp.cpp
   - Rolling hash for pattern matching
   - TIME: O(n + m) average | SPACE: O(1)
   - Problems: LC 187, LC 28

09_Manacher.cpp
   - Find longest palindromic substring
   - TIME: O(n) | SPACE: O(n)
   - Problems: LC 5, LC 647

10_ZAlgorithm.cpp
   - String preprocessing for pattern matching
   - TIME: O(n) | SPACE: O(n)
   - Problems: LC 28, LC 459

11_SieveOfEratosthenes.cpp
   - Find all primes up to n
   - TIME: O(n log log n) | SPACE: O(n)
   - Problems: LC 204, LC 762

12_FastExponentiation.cpp
   - Compute a^n in O(log n)
   - TIME: O(log n) | SPACE: O(1)
   - Problems: LC 50, LC 372

13_EuclideanGCD.cpp
   - GCD, LCM, Extended Euclidean
   - TIME: O(log min(a,b)) | SPACE: O(1)
   - Problems: LC 1979, LC 365

14_MorrisTraversal.cpp
   - Tree traversal without stack/recursion
   - TIME: O(n) | SPACE: O(1)
   - Problems: LC 94, LC 144, LC 99

15_MonotonicStack.cpp
   - Next Greater/Smaller Element pattern
   - TIME: O(n) | SPACE: O(n)
   - Problems: LC 739, LC 84, LC 42

16_SlidingWindowMax.cpp
   - Maximum in sliding window using Monotonic Deque
   - TIME: O(n) | SPACE: O(k)
   - Problems: LC 239

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "=== Classic Algorithms for Interviews ===\n\n";
    cout << "See individual files for implementations.\n";
    cout << "Each file contains:\n";
    cout << "  - Problem description\n";
    cout << "  - Core algorithm with comments\n";
    cout << "  - Time/Space complexity\n";
    cout << "  - Related LeetCode problems\n";
    return 0;
}

