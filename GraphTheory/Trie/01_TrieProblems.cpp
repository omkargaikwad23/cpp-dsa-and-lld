/*
================================================================================
                    TRIE PROBLEMS - LeetCode Favorites
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Implement Trie (LeetCode 208) ⭐ MUST KNOW
// ═══════════════════════════════════════════════════════════════════════════

class Trie {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEnd = false;
    };
    TrieNode* root;
    
public:
    Trie() { root = new TrieNode(); }
    
    void insert(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) return false;
            node = node->children[i];
        }
        return node->isEnd;
    }
    
    bool startsWith(string prefix) {
        TrieNode* node = root;
        for (char c : prefix) {
            int i = c - 'a';
            if (!node->children[i]) return false;
            node = node->children[i];
        }
        return true;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Word Search II (LeetCode 212) ⭐ GOOGLE FAVORITE
// Find all words from dictionary in board using backtracking + Trie
// ═══════════════════════════════════════════════════════════════════════════

class Solution212 {
    struct TrieNode {
        TrieNode* children[26] = {};
        string word = "";  // Store complete word at end
    };
    
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        // Build Trie from words
        TrieNode* root = new TrieNode();
        for (string& w : words) {
            TrieNode* node = root;
            for (char c : w) {
                int i = c - 'a';
                if (!node->children[i]) node->children[i] = new TrieNode();
                node = node->children[i];
            }
            node->word = w;
        }
        
        vector<string> result;
        int m = board.size(), n = board[0].size();
        
        function<void(int, int, TrieNode*)> dfs = [&](int r, int c, TrieNode* node) {
            if (r < 0 || r >= m || c < 0 || c >= n) return;
            
            char ch = board[r][c];
            if (ch == '#' || !node->children[ch - 'a']) return;
            
            node = node->children[ch - 'a'];
            
            if (!node->word.empty()) {
                result.push_back(node->word);
                node->word = "";  // Avoid duplicates
            }
            
            board[r][c] = '#';  // Mark visited
            dfs(r + 1, c, node);
            dfs(r - 1, c, node);
            dfs(r, c + 1, node);
            dfs(r, c - 1, node);
            board[r][c] = ch;   // Restore
        };
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dfs(i, j, root);
            }
        }
        
        return result;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Maximum XOR of Two Numbers (LeetCode 421) ⭐ IMPORTANT
// ═══════════════════════════════════════════════════════════════════════════

class Solution421 {
    struct BitNode {
        BitNode* children[2] = {};
    };
    
public:
    int findMaximumXOR(vector<int>& nums) {
        BitNode* root = new BitNode();
        
        // Insert all numbers
        for (int num : nums) {
            BitNode* node = root;
            for (int i = 30; i >= 0; i--) {
                int bit = (num >> i) & 1;
                if (!node->children[bit]) {
                    node->children[bit] = new BitNode();
                }
                node = node->children[bit];
            }
        }
        
        // Find max XOR for each number
        int maxXor = 0;
        for (int num : nums) {
            BitNode* node = root;
            int currXor = 0;
            
            for (int i = 30; i >= 0; i--) {
                int bit = (num >> i) & 1;
                int want = 1 - bit;
                
                if (node->children[want]) {
                    currXor |= (1 << i);
                    node = node->children[want];
                } else {
                    node = node->children[bit];
                }
            }
            maxXor = max(maxXor, currXor);
        }
        
        return maxXor;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 4: Design Add and Search Words (LeetCode 211)
// Support '.' wildcard that matches any letter
// ═══════════════════════════════════════════════════════════════════════════

class WordDictionary {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEnd = false;
    };
    TrieNode* root;
    
public:
    WordDictionary() { root = new TrieNode(); }
    
    void addWord(string word) {
        TrieNode* node = root;
        for (char c : word) {
            int i = c - 'a';
            if (!node->children[i]) node->children[i] = new TrieNode();
            node = node->children[i];
        }
        node->isEnd = true;
    }
    
    bool search(string word) {
        return searchFrom(word, 0, root);
    }
    
private:
    bool searchFrom(const string& word, int idx, TrieNode* node) {
        if (!node) return false;
        if (idx == word.size()) return node->isEnd;
        
        char c = word[idx];
        if (c == '.') {
            // Try all children
            for (int i = 0; i < 26; i++) {
                if (searchFrom(word, idx + 1, node->children[i])) {
                    return true;
                }
            }
            return false;
        } else {
            return searchFrom(word, idx + 1, node->children[c - 'a']);
        }
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 5: Replace Words (LeetCode 648)
// Replace words in sentence with their shortest root from dictionary
// ═══════════════════════════════════════════════════════════════════════════

class Solution648 {
    struct TrieNode {
        TrieNode* children[26] = {};
        string word = "";
    };
    
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        // Build Trie from dictionary
        TrieNode* root = new TrieNode();
        for (string& word : dictionary) {
            TrieNode* node = root;
            for (char c : word) {
                int i = c - 'a';
                if (!node->children[i]) node->children[i] = new TrieNode();
                node = node->children[i];
            }
            node->word = word;
        }
        
        // Find shortest root for each word
        auto findRoot = [&](const string& word) -> string {
            TrieNode* node = root;
            for (char c : word) {
                if (!node->children[c - 'a']) break;
                node = node->children[c - 'a'];
                if (!node->word.empty()) return node->word;
            }
            return word;
        };
        
        // Process sentence
        stringstream ss(sentence);
        string word, result;
        while (ss >> word) {
            if (!result.empty()) result += " ";
            result += findRoot(word);
        }
        
        return result;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 6: Longest Word in Dictionary (LeetCode 720)
// Find longest word that can be built one character at a time
// ═══════════════════════════════════════════════════════════════════════════

class Solution720 {
public:
    string longestWord(vector<string>& words) {
        struct TrieNode {
            TrieNode* children[26] = {};
            bool isEnd = false;
        };
        
        TrieNode* root = new TrieNode();
        root->isEnd = true;  // Empty string is valid
        
        // Insert all words
        for (string& w : words) {
            TrieNode* node = root;
            for (char c : w) {
                int i = c - 'a';
                if (!node->children[i]) node->children[i] = new TrieNode();
                node = node->children[i];
            }
            node->isEnd = true;
        }
        
        string result;
        
        // DFS to find longest buildable word
        function<void(TrieNode*, string&)> dfs = [&](TrieNode* node, string& path) {
            if (path.size() > result.size() || 
                (path.size() == result.size() && path < result)) {
                result = path;
            }
            
            for (int i = 0; i < 26; i++) {
                if (node->children[i] && node->children[i]->isEnd) {
                    path += ('a' + i);
                    dfs(node->children[i], path);
                    path.pop_back();
                }
            }
        };
        
        string path;
        dfs(root, path);
        return result;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 7: Count Distinct Substrings
// ═══════════════════════════════════════════════════════════════════════════

int countDistinctSubstrings(string& s) {
    struct TrieNode {
        TrieNode* children[26] = {};
    };
    
    TrieNode* root = new TrieNode();
    int count = 0;
    int n = s.size();
    
    // Insert all suffixes
    for (int i = 0; i < n; i++) {
        TrieNode* node = root;
        for (int j = i; j < n; j++) {
            int idx = s[j] - 'a';
            if (!node->children[idx]) {
                node->children[idx] = new TrieNode();
                count++;  // New distinct substring
            }
            node = node->children[idx];
        }
    }
    
    return count + 1;  // +1 for empty string
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 8: Implement Magic Dictionary (LeetCode 676)
// Search with exactly one character different
// ═══════════════════════════════════════════════════════════════════════════

class MagicDictionary {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEnd = false;
    };
    TrieNode* root;
    
public:
    MagicDictionary() { root = new TrieNode(); }
    
    void buildDict(vector<string> dictionary) {
        for (string& w : dictionary) {
            TrieNode* node = root;
            for (char c : w) {
                int i = c - 'a';
                if (!node->children[i]) node->children[i] = new TrieNode();
                node = node->children[i];
            }
            node->isEnd = true;
        }
    }
    
    bool search(string searchWord) {
        return dfs(searchWord, 0, root, false);
    }
    
private:
    bool dfs(const string& word, int idx, TrieNode* node, bool changed) {
        if (!node) return false;
        if (idx == word.size()) return node->isEnd && changed;
        
        int i = word[idx] - 'a';
        
        if (changed) {
            // Must match exactly now
            return dfs(word, idx + 1, node->children[i], true);
        }
        
        // Try changing current character
        for (int j = 0; j < 26; j++) {
            if (!node->children[j]) continue;
            
            if (j == i) {
                // No change
                if (dfs(word, idx + 1, node->children[j], false)) return true;
            } else {
                // Change here
                if (dfs(word, idx + 1, node->children[j], true)) return true;
            }
        }
        
        return false;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Trie Problems ===\n\n";
    
    // Problem 1: Basic Trie
    Trie trie;
    trie.insert("apple");
    cout << "1. search('apple'): " << trie.search("apple") << "\n";
    cout << "   startsWith('app'): " << trie.startsWith("app") << "\n";
    
    // Problem 3: Max XOR
    Solution421 sol421;
    vector<int> nums = {3, 10, 5, 25, 2, 8};
    cout << "\n3. Max XOR: " << sol421.findMaximumXOR(nums) << "\n";
    
    // Problem 4: Word Dictionary with wildcard
    WordDictionary dict;
    dict.addWord("bad");
    dict.addWord("dad");
    dict.addWord("mad");
    cout << "\n4. search('.ad'): " << dict.search(".ad") << "\n";
    cout << "   search('b..'): " << dict.search("b..") << "\n";
    
    // Problem 7: Count Distinct Substrings
    string s = "abab";
    cout << "\n7. Distinct substrings of 'abab': " << countDistinctSubstrings(s) << "\n";
    
    return 0;
}

/*
================================================================================
                    PROBLEM CATEGORIES
================================================================================

1. BASIC TRIE:
   - LeetCode 208: Implement Trie
   - LeetCode 720: Longest Word in Dictionary

2. TRIE + BACKTRACKING:
   - LeetCode 212: Word Search II ⭐

3. TRIE + WILDCARD:
   - LeetCode 211: Add and Search Words
   - LeetCode 676: Magic Dictionary

4. BINARY TRIE (XOR):
   - LeetCode 421: Maximum XOR of Two Numbers
   - LeetCode 1707: Maximum XOR With an Element From Array

5. STRING MANIPULATION:
   - LeetCode 648: Replace Words
   - Count Distinct Substrings

================================================================================
*/

