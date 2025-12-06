/*
================================================================================
                TRIPLETS WITH DISTANCE CONSTRAINT (Google Interview)
================================================================================

PROBLEM:
Given 3 SORTED arrays A, B, C (each of size n) and an integer D.
Find the number of tuples (i, j, k) such that:
  |A[i] - B[j]| <= D
  |B[j] - C[k]| <= D  
  |A[i] - C[k]| <= D

================================================================================
                         EXAMPLES
================================================================================

Example: A = [1,3,5], B = [2,4,6], C = [3,5,7], D = 2
Valid tuples: (1,2,3), (3,2,3), (3,4,3), (3,4,5), (5,4,5), (5,6,5), (5,6,7)
Output: 7

================================================================================
                         APPROACH
================================================================================

OBSERVATION: For sorted arrays, if |A[i] - C[k]| <= D, and all three values
are "close", they form a valid triplet.

KEY INSIGHT: 
- Fix B[j] as the middle element
- Use two pointers to find valid ranges in A and C
- For each B[j], find all A[i] within distance D and all C[k] within distance D

Three Pointer Approach:
1. For each element in B (middle element)
2. Find range of valid elements in A using two pointers
3. Find range of valid elements in C using two pointers
4. Count valid triplets where max - min <= D

TIME:  O(n) with sliding window approach
SPACE: O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Three Pointers - O(n) for sorted arrays
int countValidTuples(vector<int>& A, vector<int>& B, vector<int>& C, int D) {
    int count = 0;
    int n = A.size();
    
    int i = 0, j = 0, k = 0;
    
    while (i < n && j < n && k < n) {
        // Get current values
        int a = A[i], b = B[j], c = C[k];
        
        // Check if current triplet is valid
        if (abs(a - b) <= D && abs(b - c) <= D && abs(a - c) <= D) {
            count++;
            cout << "Valid: (" << a << ", " << b << ", " << c << ")\n";
        }
        
        // Move the pointer with smallest value to try to find more triplets
        if (a <= b && a <= c) {
            i++;
        } else if (b <= a && b <= c) {
            j++;
        } else {
            k++;
        }
    }
    
    return count;
}

// Approach 2: More comprehensive - O(n²) but catches all triplets
int countAllValidTuples(vector<int>& A, vector<int>& B, vector<int>& C, int D) {
    int count = 0;
    int n = A.size();
    
    // For each element in B (treat as middle element)
    for (int j = 0; j < n; j++) {
        int b = B[j];
        
        // Find valid range in A: elements where |A[i] - b| <= D
        // That means: b - D <= A[i] <= b + D
        auto aStart = lower_bound(A.begin(), A.end(), b - D);
        auto aEnd = upper_bound(A.begin(), A.end(), b + D);
        
        // Find valid range in C: elements where |C[k] - b| <= D
        auto cStart = lower_bound(C.begin(), C.end(), b - D);
        auto cEnd = upper_bound(C.begin(), C.end(), b + D);
        
        // Check all combinations
        for (auto itA = aStart; itA != aEnd; ++itA) {
            for (auto itC = cStart; itC != cEnd; ++itC) {
                int a = *itA, c = *itC;
                // Already know |a-b| <= D and |b-c| <= D
                // Just need to verify |a-c| <= D
                if (abs(a - c) <= D) {
                    count++;
                }
            }
        }
    }
    
    return count;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    vector<int> A = {1, 3, 5};
    vector<int> B = {2, 4, 6};
    vector<int> C = {3, 5, 7};
    int D = 2;
    
    cout << "=== Three Pointer Approach ===\n";
    int result1 = countValidTuples(A, B, C, D);
    cout << "Count: " << result1 << "\n\n";
    
    cout << "=== Binary Search Approach (All Triplets) ===\n";
    int result2 = countAllValidTuples(A, B, C, D);
    cout << "Count: " << result2 << "\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY NOTES
================================================================================

Three Pointer: O(n) - but may miss some triplets due to pointer movement

Binary Search: O(n² log n) worst case
- For each element in B: O(n)
- Binary search in A and C: O(log n)
- Iterate valid ranges: O(n) each worst case

For truly O(n log n), need more sophisticated approach with:
- Merge sorted arrays
- Count inversions style technique
================================================================================
*/

