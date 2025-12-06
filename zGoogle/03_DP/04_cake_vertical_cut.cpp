/*
================================================================================
                CAKE VERTICAL CUT (Google Interview)
================================================================================

PROBLEM:
Given a rectangular cake with non-overlapping toppings.
Determine if it's possible to make a SINGLE VERTICAL CUT such that:
1. The cut does NOT intersect any topping
2. Both resulting pieces contain at least one topping

Each topping is given as [start_x, end_x, start_y, end_y].

================================================================================
                         EXAMPLES
================================================================================

Example 1:
Toppings: a(0,6,0,1), b(7,8,0,4), c(0,1,2,4)

Visual:
  012345678
0 aaaaaaabb
1 aaaaaaabb
2 cc.....bb
3 cc.....bb
4 cc.....bb

Valid cut: Between column 6 and 7
Left piece: toppings a, c
Right piece: topping b
Output: true

Example 2: Single topping spanning entire width
Output: false (can't have topping on both sides)

================================================================================
                         APPROACH
================================================================================

1. Extract all unique x-positions (topping boundaries)
2. For each gap between consecutive x-positions:
   - Check if any topping SPANS across this gap
   - Check if there's at least one topping on each side
3. If valid gap found, return true

TIME:  O(n × m) where n = toppings, m = unique x-positions
SPACE: O(m) for storing x-positions

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

bool canCutCake(const vector<vector<int>>& toppings) {
    if (toppings.size() < 2) return false;  // Need at least 2 toppings
    
    // Collect all unique x-positions
    set<int> xPositions;
    for (const auto& t : toppings) {
        xPositions.insert(t[0]);  // start_x
        xPositions.insert(t[1]);  // end_x
    }
    
    // Check each potential cut position
    auto it = xPositions.begin();
    int prev = *it;
    ++it;
    
    while (it != xPositions.end()) {
        int curr = *it;
        
        // Try cutting between prev and curr
        bool canCut = true;
        bool hasLeftTopping = false;
        bool hasRightTopping = false;
        
        for (const auto& t : toppings) {
            int start_x = t[0];
            int end_x = t[1];
            
            // Check if topping spans across the cut
            if (start_x <= prev && end_x >= curr) {
                canCut = false;
                break;
            }
            
            // Check if topping is entirely on left
            if (end_x <= prev) {
                hasLeftTopping = true;
            }
            
            // Check if topping is entirely on right
            if (start_x >= curr) {
                hasRightTopping = true;
            }
        }
        
        if (canCut && hasLeftTopping && hasRightTopping) {
            return true;
        }
        
        prev = curr;
        ++it;
    }
    
    return false;
}

// Return the cut position if valid cut exists
pair<bool, int> findCutPosition(const vector<vector<int>>& toppings) {
    if (toppings.size() < 2) return {false, -1};
    
    set<int> xPositions;
    for (const auto& t : toppings) {
        xPositions.insert(t[0]);
        xPositions.insert(t[1]);
    }
    
    auto it = xPositions.begin();
    int prev = *it;
    ++it;
    
    while (it != xPositions.end()) {
        int curr = *it;
        
        bool canCut = true;
        bool hasLeft = false, hasRight = false;
        
        for (const auto& t : toppings) {
            if (t[0] <= prev && t[1] >= curr) {
                canCut = false;
                break;
            }
            if (t[1] <= prev) hasLeft = true;
            if (t[0] >= curr) hasRight = true;
        }
        
        if (canCut && hasLeft && hasRight) {
            // Cut position is between prev and curr
            return {true, (prev + curr) / 2};
        }
        
        prev = curr;
        ++it;
    }
    
    return {false, -1};
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test case 1: Valid cut exists
    vector<vector<int>> toppings1 = {
        {0, 6, 0, 1},   // Topping a
        {7, 8, 0, 4},   // Topping b
        {0, 1, 2, 4}    // Topping c
    };
    
    cout << "Test 1:\n";
    cout << "Toppings: a(0-6), b(7-8), c(0-1)\n";
    auto [canCut1, pos1] = findCutPosition(toppings1);
    cout << "Can cut: " << (canCut1 ? "Yes" : "No");
    if (canCut1) cout << " at x=" << pos1;
    cout << "\n\n";
    
    // Test case 2: No valid cut
    vector<vector<int>> toppings2 = {
        {0, 10, 0, 5}   // Single topping spanning entire width
    };
    
    cout << "Test 2:\n";
    cout << "Toppings: single(0-10)\n";
    cout << "Can cut: " << (canCutCake(toppings2) ? "Yes" : "No") << "\n\n";
    
    // Test case 3: Overlapping x-ranges but valid gap
    vector<vector<int>> toppings3 = {
        {0, 3, 0, 2},
        {5, 8, 0, 2},
        {1, 2, 3, 5}
    };
    
    cout << "Test 3:\n";
    cout << "Toppings: (0-3), (5-8), (1-2)\n";
    auto [canCut3, pos3] = findCutPosition(toppings3);
    cout << "Can cut: " << (canCut3 ? "Yes" : "No");
    if (canCut3) cout << " at x=" << pos3;
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

TIME:  O(n × m)
- n = number of toppings
- m = number of unique x-positions (at most 2n)
- For each position gap, check all toppings

SPACE: O(m) = O(n)
- Set of unique x-positions

FOLLOW-UP: What if we need HORIZONTAL cut instead?
→ Same logic, but use y-positions instead of x-positions

================================================================================
*/

