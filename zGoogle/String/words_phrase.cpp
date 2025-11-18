#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Given two strings s1 and s2, find out if they only differ by the insertion of phrase(s).

The algorithm checks if one string is a subsequence of the other (all words appear in same order).
This handles BOTH single and multiple phrase insertions.

Example 1: Single phrase insertion
The boy goes to the hospital
The cute little boy goes to the hospital
'cute little' is the added phrase, everything else is the same -> return True

Example 2: Multiple phrase insertions
The boy goes to the hospital
The cute little boy goes to the nice hospital
'cute little' and 'nice' are added phrases -> return True

Example 3: Not just insertion (words changed)
The boy is nice.
The girl is nice.
'boy' changed to 'girl', not just insertion -> return False
*/

bool isSubsequence(const vector<string>& small, const vector<string>& large) {
    size_t i = 0, j = 0;
    while (i < small.size() && j < large.size()) {
        if (small[i] == large[j]) {
            i++;
        }
        j++;
    }
    return i == small.size();
}

bool differsByInsertion(const string& s1, const string& s2) {
    istringstream ss1(s1), ss2(s2);
    vector<string> words1, words2;
    string word;
    
    while (ss1 >> word) words1.push_back(word);
    while (ss2 >> word) words2.push_back(word);
    
    // Ensure we always check the smaller string as a subsequence of the larger one
    if (words1.size() > words2.size()) {
        return isSubsequence(words2, words1);
    } else {
        return isSubsequence(words1, words2);
    }
}

int main() {
    // Example 1: Single phrase insertion
    string s1 = "The cute little boy goes to the hospital";
    string s2 = "The boy goes to the hospital";
    cout << "Example 1 (single phrase): " << (differsByInsertion(s1, s2) ? "True" : "False") << endl;

    // Example 2: Multiple phrase insertions
    string s3 = "The cute little boy goes to the nice hospital";
    string s4 = "The boy goes to the hospital";
    cout << "Example 2 (multiple phrases): " << (differsByInsertion(s3, s4) ? "True" : "False") << endl;
    
    // Example 3: Words changed (not just insertion)
    string s5 = "The boy is nice.";
    string s6 = "The girl is nice.";
    cout << "Example 3 (word changed): " << (differsByInsertion(s5, s6) ? "True" : "False") << endl;
    
    // Example 4: Multiple insertions at different positions
    string s7 = "The quick brown fox jumps over the lazy dog";
    string s8 = "The fox jumps over the dog";
    cout << "Example 4 (multiple phrases): " << (differsByInsertion(s7, s8) ? "True" : "False") << endl;
    
    return 0;
}
