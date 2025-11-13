#include <bits/stdc++.h>
using namespace std;

/*
 * TRIE (Prefix Tree) Data Structure
 * ==================================
 * 
 * A Trie is a tree-like data structure used to store a dynamic set of strings.
 * It's particularly efficient for operations involving prefixes.
 * 
 * KEY PROPERTIES:
 * - Each node represents a character
 * - Path from root to any node represents a prefix/word
 * - Nodes can share common prefixes (space efficient)
 * - Supports fast prefix matching and word lookup
 * 
 * TIME COMPLEXITY:
 * - Insert: O(m) where m = length of word
 * - Search: O(m) where m = length of word
 * - StartsWith: O(m) where m = length of prefix
 * 
 * SPACE COMPLEXITY:
 * - Worst case: O(ALPHABET_SIZE * N * M) where:
 *   * ALPHABET_SIZE = 26 (for lowercase English letters)
 *   * N = number of nodes
 *   * M = average key length
 * - In practice, space is much better due to shared prefixes
 * - Example: ["apple", "app", "abc"] shares 'a' prefix
 * 
 * COMMON USE CASES:
 * - Autocomplete/autosuggest features
 * - Spell checkers
 * - IP routing (longest prefix matching)
 * - Phone directory
 * - Search engines (prefix matching)
 * - Word games (finding valid words)
 */

/*
 * Node Structure
 * Each node in the Trie represents a character and contains:
 * - children[26]: Array of pointers to child nodes (one for each lowercase letter)
 * - isEndOfWord: Flag indicating if this node marks the end of a complete word
 */
struct Node {
    Node *children[26];  // 26 pointers for 'a' to 'z'
    bool isEndOfWord = false;

    // Check if a character exists as a child
    bool containsKey(char key) {
        return (children[key - 'a'] != NULL);
    }
    
    // Create a new child node for the given character
    void put(char ch) {
        children[ch - 'a'] = new Node();
    }
    
    // Get the child node for the given character
    Node* get(char ch) {
        return children[ch - 'a'];
    }
    
    // Mark this node as the end of a word
    void setEnd() {
        isEndOfWord = true;
    }
    
    // Check if this node marks the end of a word
    bool isEnd() {
        return isEndOfWord;
    }
};

/*
 * Trie Class
 * Main data structure that manages the Trie tree
 */
class Trie {
private:
    Node* root;  // Root node (represents empty string)

public:
    // Constructor: Initialize with an empty root node
    Trie() {
        root = new Node();
    }

    /*
     * Insert a word into the Trie
     * Algorithm:
     * 1. Start from root
     * 2. For each character in the word:
     *    - If character doesn't exist, create new node
     *    - Move to the next node
     * 3. Mark the last node as end of word
     */
    void insertWord(string word) {
        Node* curr = root;
        for(int i = 0; i < word.length(); i++) {
            // If current character path doesn't exist, create it
            if(!curr->containsKey(word[i])) {
                curr->put(word[i]);
            }
            // Move to the next node
            curr = curr->get(word[i]);
        }
        // Mark the end of the word
        curr->setEnd();
    }

    bool searchWord(string word) {
        Node *curr = root;
        // Traverse the Trie following the word's characters
        for(int i = 0; i < word.size(); i++) {
            // If any character is missing, word doesn't exist
            if(!curr->containsKey(word[i])) {
                return false;
            }
            curr = curr->get(word[i]);
        }
        // Check if we ended at a node marked as end of word
        return curr->isEnd();
    }


    bool startsWith(string prefix) {
        Node *curr = root;
        // Traverse the Trie following the prefix's characters
        for(int i = 0; i < prefix.size(); i++) {
            // If any character is missing, prefix doesn't exist
            if(!curr->containsKey(prefix[i])) {
                return false;
            }
            curr = curr->get(prefix[i]);
        }
        // If we successfully traversed all characters, prefix exists
        return true;
    }
};


int main() {
    Trie* trie = new Trie();

    // Insert words into the Trie
    trie->insertWord("apple");
    trie->insertWord("app");      // Note: "app" is a prefix of "apple"
    trie->insertWord("abc");

    // Test word search (complete words only)
    cout << "Word Search Results:\n";
    cout << "searchWord(\"app\"): " << trie->searchWord("app") << endl;      // true (complete word)
    cout << "searchWord(\"apple\"): " << trie->searchWord("apple") << endl;  // true (complete word)
    cout << "searchWord(\"apps\"): " << trie->searchWord("apps") << endl;    // false (doesn't exist)
    cout << "searchWord(\"ap\"): " << trie->searchWord("ap") << endl;        // false (prefix only, not a word)

    // Test prefix search (any prefix)
    cout << "\nPrefix Search Results:\n";
    cout << "startsWith(\"ap\"): " << trie->startsWith("ap") << endl;        // true
    cout << "startsWith(\"a\"): " << trie->startsWith("a") << endl;          // true
    cout << "startsWith(\"auto\"): " << trie->startsWith("auto") << endl;    // false

    return 0;
}