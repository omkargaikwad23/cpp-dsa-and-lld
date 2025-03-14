#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

/*
Given two strings s1 and s2, find out if they only differ by the insertion of a phrase.


Example:


The boy goes to the hospital
The cute little boy goes to the hospital
'cute litte' is the added phrase everything else is the same so return True


Example:


The boy is nice.
The girl is nice.
-> Return False
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

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
    string s1 = "The cute little boy goes to the hospital";
    string s2 = "The boy goes to the hospital";
    cout << (differsByInsertion(s1, s2) ? "True" : "False") << endl;

    string s3 = "The boy is nice.";
    string s4 = "The girl is nice.";
    cout << (differsByInsertion(s3, s4) ? "True" : "False") << endl;
    
    return 0;
}
