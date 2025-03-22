/*
Get all the possible combinations of a series of "musical notes" given the following rules:

1. Every sequence must have a sum of 12
2. Possible notes that make up the sequence can only be 1, 2 and 3
3. There are only certain valid transitions, they're given in this dictionary {1: [2, 3], 2: [1, 2], 3: [1]}. Meaning, only 2 and 3 are allowed after 1 and so on
4. First note and last note must have a valid transition. 

Example of valid sequence: [1, 2, 2, 2, 1, 1, 3]. 
Example of not valid: [1, 2, 2, 2, 2, 2, 1] reason is because 1 cannot be followed by another 1 (last and first notes transition is invalid)

Return every possible valid sequence in an array of possible sequences. You may return it in any order.
*/


#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function declaration
void backtrack(vector<int>& sequence, int current_sum, vector<vector<int>>& result, unordered_map<int, vector<int>>& transitions);

// Main function to get all valid sequences
vector<vector<int>> getAllValidSequences() {
    vector<vector<int>> result;
    vector<int> sequence;
    unordered_map<int, vector<int>> transitions = {{1, {2, 3}}, {2, {1, 2}}, {3, {1}}};
    backtrack(sequence, 0, result, transitions);
    return result;
}

// Backtracking helper function
void backtrack(vector<int>& sequence, int current_sum, vector<vector<int>>& result, unordered_map<int, vector<int>>& transitions) {
    if (current_sum == 12) {
        // Ensure the first and last notes can transition
        if (sequence.size() > 1) {
            int lastNote = sequence.back();
            int firstNote = sequence.front();

            // If the find operation returns an iterator that is not equal to end(), it indicates that the firstNote is a valid transition from the lastNote.
            if (find(transitions[lastNote].begin(), transitions[lastNote].end(), firstNote) != transitions[lastNote].end()) {
                // If valid, add the sequence to the results
                result.push_back(sequence);
            }
        }
        return;
    }
    if (current_sum > 12) return;  // Prune the invalid paths

    vector<int> valid_notes = sequence.empty() ? vector<int>{1, 2, 3} : transitions[sequence.back()];  // Get valid transitions

    for (int note : valid_notes) {
        sequence.push_back(note);
        backtrack(sequence, current_sum + note, result, transitions);
        sequence.pop_back();  // Backtrack to try another path
    }
}

// Driver function to run the program
int main() {
    vector<vector<int>> sequences = getAllValidSequences();
    for (const auto& seq : sequences) {
        for (int note : seq) {
            cout << note << " ";
        }
        cout << endl;
    }
    return 0;
}