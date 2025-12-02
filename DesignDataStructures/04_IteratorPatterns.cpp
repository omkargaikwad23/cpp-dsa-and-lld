/*
================================================================================
                    DESIGN - ITERATOR PATTERNS
================================================================================

Iterator patterns for traversing complex data structures.
Key insight: Use stack for DFS-like iteration, queue for BFS-like.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Flatten Nested List Iterator (LeetCode 341) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────
Iterator for nested list that can contain integers or nested lists.

Input: [[1,1],2,[1,1]]
Output: 1,1,2,1,1

Design: Stack of iterators, flatten lazily.

Time: O(1) amortized next(), O(L/N) hasNext() | Space: O(D) depth
*/
class NestedInteger {
public:
    bool isInteger() const;
    int getInteger() const;
    const vector<NestedInteger>& getList() const;
};

class NestedIterator {
    stack<vector<NestedInteger>::const_iterator> begins, ends;
    
    void flatten() {
        while (!begins.empty()) {
            if (begins.top() == ends.top()) {
                begins.pop();
                ends.pop();
            } else {
                auto it = begins.top();
                if (it->isInteger()) return;
                
                begins.top()++;
                begins.push(it->getList().begin());
                ends.push(it->getList().end());
            }
        }
    }
    
public:
    NestedIterator(vector<NestedInteger>& nestedList) {
        begins.push(nestedList.begin());
        ends.push(nestedList.end());
        flatten();
    }
    
    int next() {
        int val = begins.top()->getInteger();
        begins.top()++;
        flatten();
        return val;
    }
    
    bool hasNext() {
        return !begins.empty();
    }
};


/*
PROBLEM 2: Peeking Iterator (LeetCode 284)
──────────────────────────────────────────
Iterator that supports peek() without advancing.

Time: O(1) | Space: O(1)
*/
class Iterator {
public:
    bool hasNext() const;
    int next();
};

class PeekingIterator : public Iterator {
    int peekedValue;
    bool hasPeeked;
    
public:
    PeekingIterator(const vector<int>& nums) : Iterator() {
        hasPeeked = false;
    }
    
    int peek() {
        if (!hasPeeked) {
            peekedValue = Iterator::next();
            hasPeeked = true;
        }
        return peekedValue;
    }
    
    int next() {
        if (hasPeeked) {
            hasPeeked = false;
            return peekedValue;
        }
        return Iterator::next();
    }
    
    bool hasNext() const {
        return hasPeeked || Iterator::hasNext();
    }
};


/*
PROBLEM 3: Binary Search Tree Iterator (LeetCode 173)
─────────────────────────────────────────────────────
In-order iterator for BST.

Design: Controlled recursion using stack.

Time: O(1) amortized | Space: O(h)
*/
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
    stack<TreeNode*> stk;
    
    void pushLeft(TreeNode* node) {
        while (node) {
            stk.push(node);
            node = node->left;
        }
    }
    
public:
    BSTIterator(TreeNode* root) {
        pushLeft(root);
    }
    
    int next() {
        TreeNode* node = stk.top();
        stk.pop();
        pushLeft(node->right);
        return node->val;
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};


/*
PROBLEM 4: Zigzag Iterator (LeetCode 281)
─────────────────────────────────────────
Iterate through two lists in zigzag order.

Input: v1 = [1,2], v2 = [3,4,5,6]
Output: 1,3,2,4,5,6

Time: O(1) | Space: O(k) for k lists
*/
class ZigzagIterator {
    queue<pair<vector<int>::iterator, vector<int>::iterator>> q;
    
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        if (!v1.empty()) q.push({v1.begin(), v1.end()});
        if (!v2.empty()) q.push({v2.begin(), v2.end()});
    }
    
    int next() {
        auto [it, end] = q.front();
        q.pop();
        
        int val = *it;
        it++;
        
        if (it != end) {
            q.push({it, end});
        }
        
        return val;
    }
    
    bool hasNext() {
        return !q.empty();
    }
};


/*
PROBLEM 5: Flatten 2D Vector (LeetCode 251)
───────────────────────────────────────────
Iterator for 2D vector.

Time: O(1) amortized | Space: O(1)
*/
class Vector2D {
    vector<vector<int>>::iterator outer, outerEnd;
    vector<int>::iterator inner;
    
    void advance() {
        while (outer != outerEnd && inner == outer->end()) {
            outer++;
            if (outer != outerEnd) inner = outer->begin();
        }
    }
    
public:
    Vector2D(vector<vector<int>>& vec) {
        outer = vec.begin();
        outerEnd = vec.end();
        if (outer != outerEnd) {
            inner = outer->begin();
        }
        advance();
    }
    
    int next() {
        int val = *inner;
        inner++;
        advance();
        return val;
    }
    
    bool hasNext() {
        return outer != outerEnd;
    }
};


/*
PROBLEM 6: Design Compressed String Iterator (LeetCode 604)
───────────────────────────────────────────────────────────
"a2b3" → a,a,b,b,b

Time: O(1) amortized | Space: O(1)
*/
class StringIterator {
    string str;
    int idx;
    char ch;
    int count;
    
    void parseNext() {
        if (idx >= str.size()) {
            count = 0;
            return;
        }
        
        ch = str[idx++];
        count = 0;
        while (idx < str.size() && isdigit(str[idx])) {
            count = count * 10 + (str[idx++] - '0');
        }
    }
    
public:
    StringIterator(string compressedString) : str(compressedString), idx(0), count(0) {
        parseNext();
    }
    
    char next() {
        if (!hasNext()) return ' ';
        count--;
        char result = ch;
        if (count == 0) parseNext();
        return result;
    }
    
    bool hasNext() {
        return count > 0;
    }
};


/*
PROBLEM 7: Design File System Iterator (Preorder)
─────────────────────────────────────────────────
Iterate through file system in preorder (directory before contents).
*/
struct FileNode {
    string name;
    bool isFile;
    vector<FileNode*> children;
};

class FileSystemIterator {
    stack<pair<FileNode*, int>> stk;  // {node, child_index}
    
public:
    FileSystemIterator(FileNode* root) {
        if (root) stk.push({root, -1});
    }
    
    string next() {
        while (!stk.empty()) {
            auto& [node, idx] = stk.top();
            
            if (idx == -1) {
                // First visit to this node
                idx = 0;
                return node->name;
            }
            
            if (idx < node->children.size()) {
                FileNode* child = node->children[idx++];
                stk.push({child, -1});
            } else {
                stk.pop();
            }
        }
        return "";
    }
    
    bool hasNext() {
        return !stk.empty();
    }
};


/*
PROBLEM 8: RLE Iterator (LeetCode 900)
──────────────────────────────────────
Run-length encoded array. Exhaust n elements, return last.

Input: [3,8,0,9,2,5], next(2) → 8, next(1) → 8, next(1) → 5

Time: O(n) amortized | Space: O(1)
*/
class RLEIterator {
    vector<int> encoding;
    int idx;
    
public:
    RLEIterator(vector<int>& encoding) : encoding(encoding), idx(0) {}
    
    int next(int n) {
        while (idx < encoding.size() && n > encoding[idx]) {
            n -= encoding[idx];
            idx += 2;
        }
        
        if (idx >= encoding.size()) return -1;
        
        encoding[idx] -= n;
        return encoding[idx + 1];
    }
};


/*
PROBLEM 9: Stream of Characters (LeetCode 1032)
───────────────────────────────────────────────
Query if suffix of stream matches any word.

Design: Trie of reversed words + check stream in reverse.
*/
class StreamChecker {
    struct TrieNode {
        TrieNode* children[26] = {};
        bool isEnd = false;
    };
    
    TrieNode* root;
    string stream;
    
public:
    StreamChecker(vector<string>& words) {
        root = new TrieNode();
        for (const string& word : words) {
            TrieNode* node = root;
            for (int i = word.size() - 1; i >= 0; i--) {
                int c = word[i] - 'a';
                if (!node->children[c]) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->isEnd = true;
        }
    }
    
    bool query(char letter) {
        stream += letter;
        TrieNode* node = root;
        
        for (int i = stream.size() - 1; i >= 0 && node; i--) {
            int c = stream[i] - 'a';
            node = node->children[c];
            if (node && node->isEnd) return true;
        }
        
        return false;
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Iterator Patterns ===\n\n";
    
    // 3. BST Iterator
    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);
    
    BSTIterator bstIt(root);
    cout << "3. BST Iterator: ";
    while (bstIt.hasNext()) {
        cout << bstIt.next() << " ";
    }
    cout << "\n";
    
    // 4. Zigzag Iterator
    vector<int> v1 = {1, 2}, v2 = {3, 4, 5, 6};
    ZigzagIterator zz(v1, v2);
    cout << "4. Zigzag: ";
    while (zz.hasNext()) {
        cout << zz.next() << " ";
    }
    cout << "\n";
    
    // 8. RLE Iterator
    vector<int> enc = {3, 8, 0, 9, 2, 5};
    RLEIterator rle(enc);
    cout << "8. RLE next(2): " << rle.next(2) << "\n";
    cout << "   RLE next(1): " << rle.next(1) << "\n";
    cout << "   RLE next(1): " << rle.next(1) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Iterator                      | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Flatten Nested List           | Stack of iterators, flatten lazily            |
| Peeking Iterator              | Cache next value                              |
| BST Iterator                  | Stack + push all left nodes                   |
| Zigzag Iterator               | Queue of (iterator, end) pairs                |
| Flatten 2D Vector             | Two iterators: outer and inner                |
| Compressed String             | Parse char + count on demand                  |
| RLE Iterator                  | Track index, exhaust counts                   |
| Stream Checker                | Trie of reversed words                        |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

