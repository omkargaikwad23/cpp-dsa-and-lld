// https://leetcode.com/discuss/interview-question/2328651/Google-Phone-Interview-Question
// https://leetcode.com/discuss/interview-question/1678945/Google-or-Phone-or-String-Substitutor
/*
Given map {X=>123, Y=456}
Input: %X%_%Y%
Output: 123_456

Given map {USER=>admin, HOME=>/%USER%/home}
Input: I am %USER% My home is %HOME%
Output: I am admin My home is /admin/home

solved using recursion
*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <unordered_set>

using namespace std;

// Function to find the closing '%' for a given start position
int findClosingPercent(const string& input, int start) {
    for (int i = start; i < input.length(); i++) {
        if (input[i] == '%') return i;
    }
    return -1; // No closing '%' found
}

// Recursive function to resolve variables
string resolveVariable(const string& var, unordered_map<string, string>& dict, unordered_set<string>& visited) {
    if (dict.find(var) == dict.end()) return ""; // Variable not found
    
    // Detect circular reference
    if (visited.find(var) != visited.end()) {
        throw runtime_error("Error: Circular reference detected!");
    }

    visited.insert(var);  // Mark variable as visited
    string value = dict[var];

    // Process potential nested variables
    string resolvedValue;
    for (size_t i = 0; i < value.length(); i++) {
        if (value[i] == '%') {
            int closing = findClosingPercent(value, i + 1);
            if (closing == -1) throw runtime_error("Error: Unmatched % found!");

            string nestedVar = value.substr(i + 1, closing - i - 1);
            string nestedValue = resolveVariable(nestedVar, dict, visited);
            if (nestedValue.empty()) throw runtime_error("Error: Undefined variable " + nestedVar);

            resolvedValue += nestedValue;
            i = closing;
        } else {
            resolvedValue += value[i];
        }
    }

    visited.erase(var);  // Variables to be used multiple times without getting blocked.
    return resolvedValue;
}

// Function to replace placeholders in the input string
string replaceVariables(string input, unordered_map<string, string>& dict) {
    string result;
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '%') {
            int closing = findClosingPercent(input, i + 1);
            if (closing == -1) throw runtime_error("Error: Unmatched % found!");

            string var = input.substr(i + 1, closing - i - 1);
            unordered_set<string> visited;  // Track visited variables to detect circular references
            string replacement = resolveVariable(var, dict, visited);

            if (replacement.empty()) throw runtime_error("Error: Undefined variable " + var);

            result += replacement;
            i = closing;
        } else {
            result += input[i];
        }
    }
    return result;
}

// Driver function
int main() {
    unordered_map<string, string> dict = {
        {"USER", "%PRONOUN% John"},
        {"PRONOUN", "Mr."}
    };
    
    string input = "Hi %USER%";
    
    try {
        string output = replaceVariables(input, dict);
        cout << output << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    return 0;
}
