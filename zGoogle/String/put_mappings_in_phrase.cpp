/*
Given some names and their values. Write a function which takes name as input and outputs full value, also replacing the name in the value if present.

AXA = '/leetcode/config'
BYB = '/%AXA%/interview/corner/file'
LCLS = '/tmp/file/usr/shared/%BYB%'

Input: BYB
Output: '/leetcode/config/interview/corner/file'

Input: LCLS
Output: '/tmp/file/usr/shared/leetcode/config/interview/corner/file'
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std;

// Function to resolve the value of a given name
string resolveValue(const string& name, unordered_map<string, string>& map) {
    // Check if the name exists in the map
    if (map.find(name) == map.end()) {
        throw runtime_error("Name not found in map: " + name);
    }

    // Get the initial value for the name
    string value = map[name];

    size_t start_pos = 0;
    // Simple search and replace for placeholders
    while ((start_pos = value.find('%', start_pos)) != string::npos) {
        size_t end_pos = value.find('%', start_pos + 1);
        if (end_pos == string::npos) break;

        // Extract placeholder name between '%'
        string placeholder = value.substr(start_pos + 1, end_pos - start_pos - 1);

        // Recursively resolve the placeholder and substitute it back into the value
        string resolved_value = resolveValue(placeholder, map);
        
        // Replace the placeholder in the original string
        // replace any size length between given range 
        value.replace(start_pos-1, end_pos - start_pos + 1, resolved_value);
        
        // Move past the replaced section
        start_pos += resolved_value.length();
    }

    return value;
}

int main() {
    unordered_map<string, string> map = {
        {"AXA", "/leetcode/config"},
        {"BYB", "/%AXA%/interview/corner/file"},
        {"LCLS", "/tmp/file/usr/shared/%BYB%"}
    };

    try {
        cout << "Result for BYB: " << resolveValue("BYB", map) << endl;
        cout << "Result for LCLS: " << resolveValue("LCLS", map) << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}   