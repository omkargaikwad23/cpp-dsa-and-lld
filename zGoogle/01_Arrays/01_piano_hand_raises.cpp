/*
================================================================================
                    PIANO HAND RAISES (Google Interview)
================================================================================

PROBLEM:
You have a piano keyboard and one hand with 5 fingers.
Your hand covers 5 consecutive keys: [key, key+1, key+2, key+3, key+4]

You can press any of these 5 keys without moving your hand.
If the next key to play is outside these 5 keys, you must RAISE your hand
and reposition it (counts as one hand raise).

Given a sequence of keys to play, find the MINIMUM number of hand raises.

================================================================================
                         EXAMPLES
================================================================================

Example 1: keys = [10, 11, 12, 13, 14]
Output: 0
Explanation: All keys within hand span of 5, no need to move.

Example 2: keys = [10, 11, 12, 20]  
Output: 1
Explanation: After 12, key 20 is out of range → raise hand once.

Example 3: keys = [5, 7, 10, 11, 20, 22]
Output: 2

================================================================================
                         APPROACH
================================================================================

1. Track the RANGE [lo, hi] of keys covered by current hand position
2. For each new key:
   - If key is reachable (within span of 5 from both lo and hi): extend range
   - If NOT reachable: raise hand, reset range to just this key
3. A key is reachable if: key >= hi - 4 AND key <= lo + 4

TIME:  O(n) - single pass through keys
SPACE: O(1) - only tracking lo, hi, raises

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

int minHandRaises(vector<int>& keys) {
    if (keys.empty()) return 0;
    
    int raises = 0;
    int lo = keys[0], hi = keys[0];  // Current hand range [lo, hi]
    
    for (int key : keys) {
        // Check if key is reachable from current hand position
        // Hand can span 5 keys, so range must stay within span of 4
        if (key > lo + 4 || key < hi - 4) {
            // Can't reach this key - must raise hand
            raises++;
            lo = hi = key;  // Reset hand position to new key
        } else {
            // Extend range if key is within reach
            lo = min(lo, key);
            hi = max(hi, key);
        }
    }
    
    return raises;
}

// Follow-up: Return the list of thumb positions used
vector<int> getThumbPositions(vector<int>& keys) {
    if (keys.empty()) return {};
    
    vector<int> thumbPositions;
    int lo = keys[0], hi = keys[0];
    thumbPositions.push_back(keys[0]);  // Initial thumb position
    
    for (int key : keys) {
        if (key > lo + 4 || key < hi - 4) {
            thumbPositions.push_back(key);  // New thumb position
            lo = hi = key;
        } else {
            lo = min(lo, key);
            hi = max(hi, key);
        }
    }
    
    return thumbPositions;
}

// ═══════════════════════════════════════════════════════════════════════════
// TEST CASES
// ═══════════════════════════════════════════════════════════════════════════

void runTest(vector<int> input, int expected) {
    int result = minHandRaises(input);
    cout << "Input: ";
    for (int x : input) cout << x << " ";
    cout << "\nExpected = " << expected << ", Got = " << result;
    cout << (result == expected ? "   ✔ PASS" : "   ✘ FAIL") << "\n\n";
}

int main() {
    runTest({10, 11, 12, 13, 14}, 0);      // All within 5-key span
    runTest({5, 4, 3, 2, 1}, 0);           // Descending, still within span
    runTest({10, 11, 12, 20}, 1);          // Jump to 20
    runTest({5, 7, 10, 11, 20, 22}, 2);    // Two jumps
    runTest({1, 100, 101, 102, 50, 51, 55}, 3);  // Multiple repositions
    runTest({7, 7, 7, 7}, 0);              // Same key repeated
    runTest({10, 20, 11, 21, 12, 22}, 5);  // Alternating far apart
    runTest({1, 2, 3, 4, 5, 6}, 1);        // Need to extend once
    
    return 0;
}

