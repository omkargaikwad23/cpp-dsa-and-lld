#include <iostream>
#include <string>
using namespace std;

/*
 * PROBLEM: Count Distinct Substrings
 * ===================================
 * 
 * Given a string, count the number of distinct substrings (including empty string).
 * 
 * Example 1:
 * Input: "aa"
 * Output: 3
 * Distinct substrings: {"", "a", "aa"}
 * 
 * Example 2:
 * Input: "abab"
 * Output: 8
 * Distinct substrings: {"", "a", "b", "ab", "ba", "aba", "bab", "abab"}
 * 
 * APPROACH: Using Trie Data Structure
 * ====================================
 * 
 * Key Insight:
 * - Every substring is a prefix of some suffix
 * - We can generate all substrings by considering all suffixes
 * - Use Trie to efficiently count distinct substrings
 * 
 * Algorithm:
 * 1. For each starting position i (0 to n-1):
 *    - Consider all substrings starting at i: s[i...j] for j from i to n-1
 *    - Insert each substring into Trie
 *    - Count new nodes created (each new node = one distinct substring)
 * 
 * 2. Add 1 for empty string (not counted in Trie)
 * 
 * Time Complexity: O(N^2) where N is string length
 * - For each starting position i: O(N) substrings
 * - Each substring insertion: O(N) in worst case
 * - Total: O(N^2 * N) = O(N^3) worst case, but Trie makes it O(N^2) average
 * 
 * Space Complexity: O(N^2) - Trie can have at most N^2 nodes
 */

/*
 * Trie Node Structure
 * 
 * Each node represents a character in the Trie
 * - links[26]: Pointers to child nodes for each lowercase letter (a-z)
 */
struct Node {
    Node* links[26];  // One pointer for each lowercase letter (a-z)
    
    // Check if current node has a child for character 'ch'
    bool containsKey(char ch) {
        return (links[ch - 'a'] != NULL);
    }
    
    // Get the child node for character 'ch'
    Node* get(char ch) {
        return links[ch - 'a'];
    }
    
    // Set child node for character 'ch'
    void put(char ch) {
        links[ch - 'a'] = new Node();
    }
    
};

/*
 * Count Distinct Substrings using Trie
 * 
 * Algorithm:
 * 1. Start from each position i in the string
 * 2. For each position i, consider all substrings starting at i
 * 3. Insert each substring into Trie character by character
 * 4. Count new nodes created (each new node = one distinct substring)
 * 5. Return count + 1 (for empty string)
 * 
 * Why Trie works:
 * - If a substring already exists, we don't create new nodes
 * - Only new nodes are counted, giving us distinct substrings
 * - Empty string is not represented in Trie, so we add 1
 */
int countDistinctSubstrings(string &s) {
    Node* root = new Node();
    int n = s.size();
    int distinctCount = 0;  // Count of distinct substrings (excluding empty string)
    
    // For each starting position i
    for (int i = 0; i < n; i++) {
        Node* node = root;  // Start from root for each new starting position
        
        // Consider all substrings starting at position i
        // Substrings: s[i], s[i..i+1], s[i..i+2], ..., s[i..n-1]
        for (int j = i; j < n; j++) {
            char ch = s[j];
            
            // If this character path doesn't exist, create new node
            // New node = new distinct substring found
            if (!node->containsKey(ch)) {
                node->put(ch);
                distinctCount++;  // Each new node represents a distinct substring
            }
            
            // Move to next node in Trie
            node = node->get(ch);
        }
    }
    
    // Return distinctCount + 1 (adding 1 for empty string "")
    return distinctCount + 1;
}

int main() {
    // Test case 1
    string str1 = "aa";
    cout << "Input: \"" << str1 << "\"" << endl;
    cout << "Output: " << countDistinctSubstrings(str1) << endl;
    cout << "Expected: 3 (substrings: {\"\", \"a\", \"aa\"})\n" << endl;
    
    // Test case 2
    string str2 = "abab";
    cout << "Input: \"" << str2 << "\"" << endl;
    cout << "Output: " << countDistinctSubstrings(str2) << endl;
    cout << "Expected: 8 (substrings: {\"\", \"a\", \"b\", \"ab\", \"ba\", \"aba\", \"bab\", \"abab\"})" << endl;
    
    return 0;
}