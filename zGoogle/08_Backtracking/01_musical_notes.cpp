/*
================================================================================
                VALID MUSICAL NOTES (Google Interview)
================================================================================

PROBLEM:
Generate all possible sequences of "musical notes" following rules:

1. Every sequence must have a sum of 12
2. Possible notes: 1, 2, 3 only
3. Valid transitions: {1: [2,3], 2: [1,2], 3: [1]}
   - After 1, you can only use 2 or 3
   - After 2, you can only use 1 or 2
   - After 3, you can only use 1
4. First and last notes must have valid transition (circular)

================================================================================
                         EXAMPLES
================================================================================

Valid:   [1, 2, 2, 2, 1, 1, 3] → sum=12, all transitions valid, 3→1 valid
Invalid: [1, 2, 2, 2, 2, 2, 1] → 1→1 not valid (last to first)

================================================================================
                         APPROACH
================================================================================

BACKTRACKING:
1. Start with empty sequence
2. At each step, try valid notes based on previous note
3. When sum = 12, check if last→first transition is valid
4. Prune when sum > 12

TIME:  O(3^n × n) where n ≈ sum/avg_note ≈ 12/2 = 6
SPACE: O(n) for recursion stack

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class MusicalNotes {
private:
    unordered_map<int, vector<int>> transitions = {
        {1, {2, 3}},
        {2, {1, 2}},
        {3, {1}}
    };
    
    void backtrack(vector<int>& sequence, int currentSum, 
                   vector<vector<int>>& result) {
        // Base case: sum reached 12
        if (currentSum == 12) {
            // Check circular transition: last → first
            if (sequence.size() > 1) {
                int lastNote = sequence.back();
                int firstNote = sequence.front();
                
                // Check if firstNote is valid after lastNote
                auto& validNext = transitions[lastNote];
                if (find(validNext.begin(), validNext.end(), firstNote) != validNext.end()) {
                    result.push_back(sequence);
                }
            }
            return;
        }
        
        // Pruning: sum exceeded
        if (currentSum > 12) return;
        
        // Get valid next notes
        vector<int> validNotes;
        if (sequence.empty()) {
            validNotes = {1, 2, 3};  // Any note can start
        } else {
            validNotes = transitions[sequence.back()];
        }
        
        // Try each valid note
        for (int note : validNotes) {
            sequence.push_back(note);
            backtrack(sequence, currentSum + note, result);
            sequence.pop_back();
        }
    }
    
public:
    vector<vector<int>> getAllValidSequences() {
        vector<vector<int>> result;
        vector<int> sequence;
        backtrack(sequence, 0, result);
        return result;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    MusicalNotes solver;
    
    cout << "=== Valid Musical Note Sequences (sum = 12) ===\n\n";
    cout << "Transition rules:\n";
    cout << "  After 1: can use 2 or 3\n";
    cout << "  After 2: can use 1 or 2\n";
    cout << "  After 3: can use 1 only\n";
    cout << "  Last → First must also be valid\n\n";
    
    auto sequences = solver.getAllValidSequences();
    
    cout << "Found " << sequences.size() << " valid sequences:\n\n";
    
    int count = 0;
    for (const auto& seq : sequences) {
        cout << "[";
        for (int i = 0; i < seq.size(); i++) {
            cout << seq[i];
            if (i < seq.size() - 1) cout << ", ";
        }
        cout << "]\n";
        
        if (++count >= 20) {
            cout << "... (" << sequences.size() - 20 << " more)\n";
            break;
        }
    }
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

TIME: O(3^n × n) worst case
- At each position, up to 3 choices
- n ≈ 12 / average_note ≈ 6
- Final validation is O(n)

SPACE: O(n)
- Recursion depth: O(n)
- Each sequence stored: O(n)

PRUNING HELPS:
- Sum > 12: prune immediately
- Transition constraints reduce branching factor significantly

================================================================================
*/

