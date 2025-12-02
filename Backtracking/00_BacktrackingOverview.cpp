/*
================================================================================
                      BACKTRACKING - OVERVIEW
================================================================================

Backtracking is a systematic way to explore all possible solutions by building
candidates incrementally and abandoning a candidate ("backtrack") as soon as
it determines that this candidate cannot lead to a valid solution.

Key Idea: Try → Explore → Undo (if needed)

Time Complexity: Usually exponential O(k^n) or O(n!)
Space Complexity: O(n) for recursion stack

================================================================================
                           CORE TEMPLATE
================================================================================

void backtrack(state, choices, result) {
    // BASE CASE: Found valid solution
    if (is_goal(state)) {
        result.add(state);
        return;
    }
    
    // RECURSIVE CASE: Try each choice
    for (choice in choices) {
        if (is_valid(choice)) {
            // 1. MAKE choice
            make_choice(state, choice);
            
            // 2. EXPLORE further
            backtrack(state, remaining_choices, result);
            
            // 3. UNDO choice (backtrack)
            undo_choice(state, choice);
        }
    }
}

================================================================================
                           PATTERN CLASSIFICATION
================================================================================

1. SUBSETS / POWER SET
   ────────────────────
   Generate all possible subsets of a set.
   
   Key: For each element, decide to INCLUDE or EXCLUDE.
   
   Problems:
   - Subsets (no duplicates)
   - Subsets II (with duplicates)
   - Letter Case Permutation
   
   Template:
   void subsets(nums, index, current, result) {
       result.add(current);  // Every state is valid
       for (i = index; i < n; i++) {
           current.add(nums[i]);
           subsets(nums, i + 1, current, result);
           current.remove_last();
       }
   }

2. PERMUTATIONS
   ─────────────
   Generate all possible orderings.
   
   Key: Each element must be used exactly once.
   
   Problems:
   - Permutations (no duplicates)
   - Permutations II (with duplicates)
   - Next Permutation
   
   Template:
   void permute(nums, used, current, result) {
       if (current.size() == n) {
           result.add(current);
           return;
       }
       for (i = 0; i < n; i++) {
           if (used[i]) continue;
           used[i] = true;
           current.add(nums[i]);
           permute(nums, used, current, result);
           current.remove_last();
           used[i] = false;
       }
   }

3. COMBINATIONS
   ─────────────
   Choose k elements from n (order doesn't matter).
   
   Key: Similar to subsets but stop at size k.
   
   Problems:
   - Combinations (n choose k)
   - Combination Sum (can reuse)
   - Combination Sum II (no reuse, with duplicates)
   - Combination Sum III (1-9, k numbers, sum = n)
   
   Template:
   void combine(n, k, start, current, result) {
       if (current.size() == k) {
           result.add(current);
           return;
       }
       for (i = start; i <= n; i++) {
           current.add(i);
           combine(n, k, i + 1, current, result);
           current.remove_last();
       }
   }

4. PARTITIONING
   ─────────────
   Divide input into parts satisfying conditions.
   
   Problems:
   - Palindrome Partitioning
   - Partition to K Equal Sum Subsets
   - Restore IP Addresses
   
5. GRID/BOARD SEARCH
   ──────────────────
   Explore paths on a 2D grid.
   
   Problems:
   - Word Search
   - N-Queens
   - Sudoku Solver
   - Rat in a Maze

6. GENERATE VALID SEQUENCES
   ─────────────────────────
   Build strings/sequences satisfying constraints.
   
   Problems:
   - Generate Parentheses
   - Letter Combinations of Phone Number
   - Expression Add Operators

================================================================================
                           KEY TECHNIQUES
================================================================================

1. PRUNING - Skip invalid branches early
   if (sum > target) return;  // Don't explore further
   
2. HANDLING DUPLICATES - Sort + skip same elements
   if (i > start && nums[i] == nums[i-1]) continue;
   
3. EARLY TERMINATION - Stop when goal found
   if (found) return;
   
4. STATE REPRESENTATION
   - Use vector for path/current state
   - Use boolean array for visited/used
   - Use bitmask for small state space

5. AVOIDING REVISITS
   - Pass start index for combinations
   - Use visited array for permutations
   - Mark/unmark cells for grid problems

================================================================================
                           FILE ORGANIZATION
================================================================================

01_SubsetsPatterns.cpp      - Subsets, power set problems
02_Permutations.cpp         - All ordering problems
03_Combinations.cpp         - Combination sum variations
04_Partitioning.cpp         - String/array partitioning
05_GridBoard.cpp            - N-Queens, Sudoku, Word Search
06_GenerateSequences.cpp    - Parentheses, expressions

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Quick Demo: Basic Backtracking Template
void backtrackDemo(vector<int>& nums, int start, vector<int>& current, 
                   vector<vector<int>>& result) {
    result.push_back(current);
    
    for (int i = start; i < nums.size(); i++) {
        current.push_back(nums[i]);          // Make choice
        backtrackDemo(nums, i + 1, current, result);  // Explore
        current.pop_back();                  // Undo choice
    }
}

int main() {
    cout << "=== Backtracking Patterns ===" << endl;
    
    vector<int> nums = {1, 2, 3};
    vector<int> current;
    vector<vector<int>> result;
    
    backtrackDemo(nums, 0, current, result);
    
    cout << "Subsets of [1,2,3]: " << result.size() << " subsets" << endl;
    
    return 0;
}

