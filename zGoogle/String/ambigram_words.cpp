/*
Given a list of strings we need to output the list of ambigram words
eg. axe, pod are ambigram words because if we rotate these words 180 degrees, they will remain the same.

*/


#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<char, char> rotateMap = {
    {'o', 'o'}, {'x', 'x'}, {'s', 's'}, {'z', 'z'}, {'i', 'i'}, {'l', 'l'},
    {'n', 'u'}, {'u', 'n'},
    {'p', 'd'}, {'d', 'p'},
    {'b', 'q'}, {'q', 'b'},
    {'m', 'w'}, {'w', 'm'},
    {'a', 'e'}, {'e', 'a'}
};

bool isAmbigram(const string& word) {
    int left = 0, right = word.length() - 1;
    
    while (left <= right) {
        // Check if left char has a valid rotation mapping
        if (rotateMap.find(word[left]) == rotateMap.end()) {
            return false;
        }
        // The rotated left char must equal the right char
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

int main() {
    vector<string> words = {"axe", "pod", "hello", "noon", "swims"};
    vector<string> ambigrams = findAmbigrams(words);
    
    cout << "Ambigram words: ";
    for (const string& s : ambigrams) {
        cout << s << " ";
    }
    return 0;
}