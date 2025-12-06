/*
================================================================================
                    AMBIGRAM WORDS (Google Interview)
================================================================================

PROBLEM:
Given a list of strings, find all AMBIGRAM words.
An ambigram word reads the same when rotated 180 degrees.

Examples:
- "pod" is an ambigram (p→d, o→o, d→p when rotated)
- "noon" is NOT an ambigram ('n' has no valid 180° rotation)

================================================================================
                         APPROACH
================================================================================

1. Define rotation mapping for characters that look same/different when rotated
2. Use two pointers from both ends
3. Check if rotated(left_char) == right_char

Valid 180° rotations:
- Self-similar: o, x, s, z, i, l
- Pairs: n↔u, p↔d, b↔q, m↔w, a↔e

TIME:  O(n × m) where n = number of words, m = average word length
SPACE: O(1) - just the rotation map

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class AmbigramChecker {
private:
    unordered_map<char, char> rotateMap = {
        // Self-similar characters
        {'o', 'o'}, {'x', 'x'}, {'s', 's'}, {'z', 'z'}, 
        {'i', 'i'}, {'l', 'l'},
        // Character pairs
        {'n', 'u'}, {'u', 'n'},
        {'p', 'd'}, {'d', 'p'},
        {'b', 'q'}, {'q', 'b'},
        {'m', 'w'}, {'w', 'm'},
        {'a', 'e'}, {'e', 'a'}
    };
    
public:
    bool isAmbigram(const string& word) {
        int left = 0, right = word.length() - 1;
        
        while (left <= right) {
            // Check if left char has valid rotation
            if (rotateMap.find(word[left]) == rotateMap.end()) {
                return false;
            }
            
            // Rotated left char must equal right char
            if (rotateMap[word[left]] != word[right]) {
                return false;
            }
            
            left++;
            right--;
        }
        
        return true;
    }
    
    vector<string> findAmbigrams(const vector<string>& words) {
        vector<string> result;
        for (const string& word : words) {
            if (isAmbigram(word)) {
                result.push_back(word);
            }
        }
        return result;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    AmbigramChecker checker;
    
    vector<string> words = {"pod", "axe", "hello", "noon", "swims", 
                            "suns", "dollop", "nun"};
    
    cout << "Testing words: ";
    for (const string& w : words) cout << w << " ";
    cout << "\n\n";
    
    cout << "Individual checks:\n";
    for (const string& word : words) {
        cout << word << ": " << (checker.isAmbigram(word) ? "✓ Ambigram" : "✗ Not Ambigram") << "\n";
    }
    
    cout << "\nAll ambigrams: ";
    vector<string> ambigrams = checker.findAmbigrams(words);
    for (const string& s : ambigrams) {
        cout << s << " ";
    }
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                         NOTES
================================================================================

ROTATION PAIRS (may vary by font):
- Standard: o, x, s, z, i, l look same when rotated
- Common pairs: n↔u, p↔d
- Font-dependent: b↔q, m↔w, a↔e (varies by typeface)

FOLLOW-UP QUESTIONS:
1. What if we need to handle uppercase letters?
   → Add uppercase mappings: O↔O, S↔S, N↔N, Z↔Z, H↔H, X↔X

2. What if we need to handle numbers?
   → Add: 0↔0, 1↔1, 8↔8, 6↔9, 9↔6

3. What about finding the longest ambigram substring?
   → Expand around center or DP approach

================================================================================
*/

