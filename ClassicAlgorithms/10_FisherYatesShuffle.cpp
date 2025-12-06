/*
================================================================================
                    FISHER-YATES SHUFFLE (Knuth Shuffle)
================================================================================

PROBLEM: Randomly shuffle an array with uniform distribution.
         Each of n! permutations should have equal probability.

KEY INSIGHT: For each position i (from end to start), swap with a random
             position from [0, i].

ALGORITHM:
1. For i from n-1 down to 1:
   - Pick random j in [0, i]
   - Swap arr[i] and arr[j]

TIME:  O(n)
SPACE: O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// FISHER-YATES SHUFFLE - LC 384
// ═══════════════════════════════════════════════════════════════════════════

class Solution {
    vector<int> original;
    vector<int> current;
    
public:
    Solution(vector<int>& nums) : original(nums), current(nums) {
        srand(time(0));
    }
    
    vector<int> reset() {
        current = original;
        return current;
    }
    
    vector<int> shuffle() {
        int n = current.size();
        
        // Fisher-Yates: iterate from end to start
        for (int i = n - 1; i > 0; i--) {
            // Random index in [0, i]
            int j = rand() % (i + 1);
            swap(current[i], current[j]);
        }
        
        return current;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// STANDALONE FUNCTION
// ═══════════════════════════════════════════════════════════════════════════

void fisherYatesShuffle(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

// Alternative: Forward iteration
void shuffleForward(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        // Random index in [i, n-1]
        int j = i + rand() % (n - i);
        swap(arr[i], arr[j]);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// PARTIAL SHUFFLE - Shuffle first k elements only
// ═══════════════════════════════════════════════════════════════════════════

vector<int> partialShuffle(vector<int>& arr, int k) {
    int n = arr.size();
    vector<int> result = arr;
    
    for (int i = 0; i < k && i < n; i++) {
        int j = i + rand() % (n - i);
        swap(result[i], result[j]);
    }
    
    return vector<int>(result.begin(), result.begin() + k);
}

// ═══════════════════════════════════════════════════════════════════════════
// VERIFY UNIFORMITY (for testing)
// ═══════════════════════════════════════════════════════════════════════════

void verifyUniformity() {
    vector<int> arr = {1, 2, 3};
    map<vector<int>, int> freq;
    int trials = 60000;
    
    for (int t = 0; t < trials; t++) {
        vector<int> copy = arr;
        fisherYatesShuffle(copy);
        freq[copy]++;
    }
    
    cout << "Distribution over " << trials << " trials:\n";
    cout << "(Each permutation should appear ~" << trials / 6 << " times)\n";
    
    for (auto& [perm, count] : freq) {
        cout << "[";
        for (int i = 0; i < perm.size(); i++) {
            cout << perm[i];
            if (i < perm.size() - 1) cout << ",";
        }
        cout << "]: " << count << "\n";
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    srand(time(0));
    
    // Basic shuffle
    vector<int> arr = {1, 2, 3, 4, 5};
    
    cout << "Original: ";
    for (int x : arr) cout << x << " ";
    cout << "\n\n";
    
    cout << "5 shuffles:\n";
    for (int i = 0; i < 5; i++) {
        vector<int> copy = arr;
        fisherYatesShuffle(copy);
        cout << "  ";
        for (int x : copy) cout << x << " ";
        cout << "\n";
    }
    
    // Partial shuffle - get random k elements
    cout << "\nRandom 3 elements from [1,2,3,4,5]:\n";
    for (int i = 0; i < 5; i++) {
        vector<int> copy = arr;
        auto result = partialShuffle(copy, 3);
        cout << "  ";
        for (int x : result) cout << x << " ";
        cout << "\n";
    }
    
    // Verify uniformity
    cout << "\n=== Uniformity Test ===\n";
    verifyUniformity();
    
    return 0;
}

/*
================================================================================
                         WHY IT'S UNIFORM
================================================================================

For array of size n:
- Position n-1 has n choices → probability 1/n for each element
- Position n-2 has n-1 choices → combined with above, 1/n for each
- And so on...

Total permutations: n! and each has probability 1/n!

COMMON MISTAKE (Biased Shuffle):
for (int i = 0; i < n; i++) {
    int j = rand() % n;  // WRONG! Should be rand() % (i+1) or rand() % (n-i)
    swap(arr[i], arr[j]);
}
This gives n^n possibilities, not n!, so NOT uniform.

APPLICATIONS:
- Random sampling
- Randomized algorithms
- Games (deck shuffling)
- A/B testing (random assignment)

RELATED PROBLEMS:
- LC 384: Shuffle an Array
- LC 398: Random Pick Index
- LC 382: Linked List Random Node

================================================================================
*/

