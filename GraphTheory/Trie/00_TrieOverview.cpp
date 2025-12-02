/*
================================================================================
                    TRIE (PREFIX TREE) - QUICK REFERENCE
================================================================================

WHEN TO USE TRIE:
- Prefix-based search (autocomplete, spell check)
- Word dictionary operations
- XOR problems (use binary trie)
- Count distinct substrings

TIME COMPLEXITY: O(L) for all operations where L = word length
SPACE COMPLEXITY: O(ALPHABET_SIZE * L * N) worst case

================================================================================
                    INTERVIEW-READY TEMPLATES
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 1: SIMPLE TRIE (Most Common - Use This!)
// ═══════════════════════════════════════════════════════════════════════════

struct TrieNode {
    TrieNode* children[26] = {};  // Auto-initialized to nullptr
    bool isEnd = false;
    int count = 0;  // Optional: count words ending here
    int prefixCount = 0;  // Optional: count words with this prefix
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }
    
    // INSERT word - O(L)
    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
            }
            node = node->children[idx];
            node->prefixCount++;
        }
        node->isEnd = true;
        node->count++;
    }
    
    // SEARCH exact word - O(L)
    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }
    
    // STARTS WITH prefix - O(L)
    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return true;
    }
    
    // COUNT words with prefix - O(L)
    int countPrefix(const string& prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->prefixCount;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 2: BINARY TRIE (For XOR Problems)
// ═══════════════════════════════════════════════════════════════════════════

struct BitNode {
    BitNode* children[2] = {};  // 0 and 1
};

class BinaryTrie {
    BitNode* root;
    int BITS = 30;  // Adjust based on max value (30 for 10^9)
public:
    BinaryTrie() { root = new BitNode(); }
    
    // Insert number bit by bit (MSB to LSB)
    void insert(int num) {
        BitNode* node = root;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node->children[bit]) {
                node->children[bit] = new BitNode();
            }
            node = node->children[bit];
        }
    }
    
    // Find number that gives max XOR with num
    int getMaxXor(int num) {
        BitNode* node = root;
        int maxXor = 0;
        for (int i = BITS; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int want = 1 - bit;  // Want opposite bit for max XOR
            
            if (node->children[want]) {
                maxXor |= (1 << i);
                node = node->children[want];
            } else {
                node = node->children[bit];
            }
        }
        return maxXor;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 3: TRIE WITH DELETE
// ═══════════════════════════════════════════════════════════════════════════

class TrieWithDelete {
    struct Node {
        Node* children[26] = {};
        int endCount = 0;
        int prefixCount = 0;
    };
    Node* root;
    
public:
    TrieWithDelete() { root = new Node(); }
    
    void insert(const string& word) {
        Node* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new Node();
            }
            node = node->children[idx];
            node->prefixCount++;
        }
        node->endCount++;
    }
    
    void erase(const string& word) {
        Node* node = root;
        for (char c : word) {
            int idx = c - 'a';
            node = node->children[idx];
            node->prefixCount--;
        }
        node->endCount--;
    }
    
    int countWord(const string& word) {
        Node* node = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->endCount;
    }
    
    int countPrefix(const string& prefix) {
        Node* node = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!node->children[idx]) return 0;
            node = node->children[idx];
        }
        return node->prefixCount;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// MAIN - Quick Test
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Trie Quick Test ===\n\n";
    
    // Test Simple Trie
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    
    cout << "search('apple'): " << trie.search("apple") << "\n";      // 1
    cout << "search('app'): " << trie.search("app") << "\n";          // 1
    cout << "search('ap'): " << trie.search("ap") << "\n";            // 0
    cout << "startsWith('app'): " << trie.startsWith("app") << "\n";  // 1
    cout << "countPrefix('app'): " << trie.countPrefix("app") << "\n"; // 3
    
    // Test Binary Trie
    cout << "\n=== Binary Trie (Max XOR) ===\n";
    BinaryTrie btrie;
    vector<int> nums = {3, 10, 5, 25, 2, 8};
    for (int n : nums) btrie.insert(n);
    
    int maxXor = 0;
    for (int n : nums) {
        maxXor = max(maxXor, btrie.getMaxXor(n));
    }
    cout << "Max XOR: " << maxXor << "\n";  // 28 (5 XOR 25)
    
    return 0;
}

/*
================================================================================
                    COMMON PATTERNS CHEAT SHEET
================================================================================

1. BASIC TRIE:
   - Insert/Search/StartsWith: LeetCode 208
   - Use: children[26], isEnd flag

2. TRIE WITH COUNT:
   - Add: count (words ending), prefixCount (words with prefix)
   - Use: For counting problems

3. BINARY TRIE:
   - For XOR problems (Maximum XOR, XOR queries)
   - children[2] for bits 0 and 1
   - Process MSB to LSB

4. TRIE FOR DISTINCT SUBSTRINGS:
   - Insert all suffixes
   - Count new nodes created

KEY TIPS:
- Always initialize children to nullptr
- Use (c - 'a') for lowercase, (c - 'A') for uppercase
- For mixed case, use 52 children or unordered_map
- For XOR: BITS = 30 for values up to 10^9

================================================================================
*/

