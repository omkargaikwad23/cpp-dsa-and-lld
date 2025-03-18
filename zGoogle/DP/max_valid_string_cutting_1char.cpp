/*
You have a dictionary of string, example - [string, sring, sing, wording, ing,ng, g]
You need to tell the maximum longest word in the dictionary that is valid.
Definiton of valid string , if you remove only one character from the string and it should be in the dictionary and by doing so if you able to reach at the end with length as 1, it will be valid.
Example - ( string-> sring->sing->ing->ng->g) [as all the intermediate string are present in the dictionary this will be a valid string and longest lenght is 6]
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

// Function to check the longest valid word using memoization
int findLongestValidWord(const string& word, unordered_set<string>& dict, unordered_map<string, int>& memo) {
    if (memo.find(word) != memo.end()) return memo[word];
    if (word.size() == 1) return 1; // Base case: length 1 is valid
    
    int maxLength = 0;
    for (size_t i = 0; i < word.size(); ++i) {
        string newWord = word.substr(0, i) + word.substr(i + 1);
        if (dict.find(newWord) != dict.end()) {
            maxLength = max(maxLength, findLongestValidWord(newWord, dict, memo));
        }
    }
    
    return memo[word] = maxLength + 1;
}

// Function to find the longest valid word in the dictionary
string longestValidWord(vector<string>& words) {
    unordered_set<string> dict(words.begin(), words.end());
    unordered_map<string, int> memo;
    
    int maxLen = 0;
    string longestWord = "";
    
    for (const string& word : words) {
        int len = findLongestValidWord(word, dict, memo);
        if (len > maxLen) {
            maxLen = len;
            longestWord = word;
        }
    }
    
    return longestWord;
}

int main() {
    vector<string> words = {"string", "sring", "sing", "wording", "ing", "ng", "g"};
    cout << "Longest valid word: " << longestValidWord(words) << endl;
    return 0;
}
