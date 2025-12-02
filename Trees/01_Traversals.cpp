/*
================================================================================
                    TREE TRAVERSALS
================================================================================

All traversal methods: Recursive, Iterative, Morris (O(1) space)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};


// ═══════════════════════════════════════════════════════════════════════════
// INORDER TRAVERSAL (Left, Root, Right)
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM: Inorder Traversal (LeetCode 94)
For BST: gives sorted order
*/

// Recursive
void inorderRecursive(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorderRecursive(root->left, result);
    result.push_back(root->val);
    inorderRecursive(root->right, result);
}

// Iterative with Stack
vector<int> inorderIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> stk;
    TreeNode* curr = root;
    
    while (curr || !stk.empty()) {
        // Go to leftmost
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        
        curr = stk.top();
        stk.pop();
        result.push_back(curr->val);
        
        curr = curr->right;
    }
    
    return result;
}

// Morris Traversal - O(1) space ⭐
vector<int> inorderMorris(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            // Find inorder predecessor
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                // Create thread
                pred->right = curr;
                curr = curr->left;
            } else {
                // Thread exists, remove it
                pred->right = nullptr;
                result.push_back(curr->val);
                curr = curr->right;
            }
        }
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// PREORDER TRAVERSAL (Root, Left, Right)
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM: Preorder Traversal (LeetCode 144)
Used for: Serialization, Copy tree
*/

// Recursive
void preorderRecursive(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);
    preorderRecursive(root->left, result);
    preorderRecursive(root->right, result);
}

// Iterative with Stack
vector<int> preorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        TreeNode* node = stk.top();
        stk.pop();
        result.push_back(node->val);
        
        // Push right first so left is processed first
        if (node->right) stk.push(node->right);
        if (node->left) stk.push(node->left);
    }
    
    return result;
}

// Morris Preorder - O(1) space
vector<int> preorderMorris(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                result.push_back(curr->val);  // Visit before going left
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = nullptr;
                curr = curr->right;
            }
        }
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// POSTORDER TRAVERSAL (Left, Right, Root)
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM: Postorder Traversal (LeetCode 145)
Used for: Deletion, Expression evaluation
*/

// Recursive
void postorderRecursive(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorderRecursive(root->left, result);
    postorderRecursive(root->right, result);
    result.push_back(root->val);
}

// Iterative with Two Stacks
vector<int> postorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> s1, s2;
    s1.push(root);
    
    while (!s1.empty()) {
        TreeNode* node = s1.top();
        s1.pop();
        s2.push(node);
        
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    
    while (!s2.empty()) {
        result.push_back(s2.top()->val);
        s2.pop();
    }
    
    return result;
}

// Iterative with One Stack (using prev pointer)
vector<int> postorderOneStack(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<TreeNode*> stk;
    TreeNode* curr = root;
    TreeNode* prev = nullptr;
    
    while (curr || !stk.empty()) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        
        curr = stk.top();
        
        if (!curr->right || curr->right == prev) {
            result.push_back(curr->val);
            stk.pop();
            prev = curr;
            curr = nullptr;
        } else {
            curr = curr->right;
        }
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// LEVEL ORDER TRAVERSAL (BFS)
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM: Level Order Traversal (LeetCode 102) ⭐ GOOGLE FAVORITE
*/

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level;
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(level);
    }
    
    return result;
}

// Level Order Bottom to Top (LeetCode 107)
vector<vector<int>> levelOrderBottom(TreeNode* root) {
    vector<vector<int>> result = levelOrder(root);
    reverse(result.begin(), result.end());
    return result;
}

// Zigzag Level Order (LeetCode 103) ⭐
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<TreeNode*> q;
    q.push(root);
    bool leftToRight = true;
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> level(levelSize);
        
        for (int i = 0; i < levelSize; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            int idx = leftToRight ? i : levelSize - 1 - i;
            level[idx] = node->val;
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        result.push_back(level);
        leftToRight = !leftToRight;
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// VERTICAL ORDER TRAVERSAL
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM: Vertical Order Traversal (LeetCode 987)
*/
vector<vector<int>> verticalTraversal(TreeNode* root) {
    // {col, row, val}
    vector<tuple<int, int, int>> nodes;
    
    function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int row, int col) {
        if (!node) return;
        nodes.push_back({col, row, node->val});
        dfs(node->left, row + 1, col - 1);
        dfs(node->right, row + 1, col + 1);
    };
    
    dfs(root, 0, 0);
    sort(nodes.begin(), nodes.end());
    
    vector<vector<int>> result;
    int prevCol = INT_MIN;
    
    for (auto& [col, row, val] : nodes) {
        if (col != prevCol) {
            result.push_back({});
            prevCol = col;
        }
        result.back().push_back(val);
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// N-ARY TREE TRAVERSALS
// ═══════════════════════════════════════════════════════════════════════════

struct NaryNode {
    int val;
    vector<NaryNode*> children;
    NaryNode(int x) : val(x) {}
};

// N-ary Preorder (LeetCode 589)
vector<int> naryPreorder(NaryNode* root) {
    vector<int> result;
    if (!root) return result;
    
    stack<NaryNode*> stk;
    stk.push(root);
    
    while (!stk.empty()) {
        NaryNode* node = stk.top();
        stk.pop();
        result.push_back(node->val);
        
        // Push children in reverse order
        for (int i = node->children.size() - 1; i >= 0; i--) {
            stk.push(node->children[i]);
        }
    }
    
    return result;
}

// N-ary Level Order (LeetCode 429)
vector<vector<int>> naryLevelOrder(NaryNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    
    queue<NaryNode*> q;
    q.push(root);
    
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        
        for (int i = 0; i < size; i++) {
            NaryNode* node = q.front();
            q.pop();
            level.push_back(node->val);
            
            for (NaryNode* child : node->children) {
                q.push(child);
            }
        }
        
        result.push_back(level);
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Tree Traversals ===\n\n";
    
    // Build tree: [1,2,3,4,5,null,6]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    
    // Inorder
    auto inorder = inorderIterative(root);
    cout << "Inorder: ";
    for (int v : inorder) cout << v << " ";
    cout << "\n";
    
    // Preorder
    auto preorder = preorderIterative(root);
    cout << "Preorder: ";
    for (int v : preorder) cout << v << " ";
    cout << "\n";
    
    // Postorder
    auto postorder = postorderIterative(root);
    cout << "Postorder: ";
    for (int v : postorder) cout << v << " ";
    cout << "\n";
    
    // Level Order
    auto levels = levelOrder(root);
    cout << "Level Order: ";
    for (auto& level : levels) {
        cout << "[";
        for (int v : level) cout << v << " ";
        cout << "] ";
    }
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Traversal                     | Order                                          |
+───────────────────────────────+────────────────────────────────────────────────+
| Inorder                       | Left → Root → Right (BST sorted)               |
| Preorder                      | Root → Left → Right (serialization)            |
| Postorder                     | Left → Right → Root (deletion)                 |
| Level Order                   | Level by level (BFS)                           |
+───────────────────────────────+────────────────────────────────────────────────+

ITERATIVE PATTERNS:
- Inorder: Go left, process, go right
- Preorder: Process, push right then left
- Postorder: Two stacks OR one stack with prev pointer

MORRIS TRAVERSAL:
- O(1) space by using thread pointers
- Modifies tree temporarily, restores it

================================================================================
*/

