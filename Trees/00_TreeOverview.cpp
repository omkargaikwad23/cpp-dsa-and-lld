/*
================================================================================
                    TREE DATA STRUCTURES - OVERVIEW
================================================================================

Essential tree concepts for Google interviews.

================================================================================
                           TREE BASICS
================================================================================

TERMINOLOGY:
- Root: Topmost node
- Leaf: Node with no children
- Height: Longest path from node to leaf
- Depth: Distance from root to node
- Level: All nodes at same depth

TYPES OF TREES:
1. Binary Tree: Each node has at most 2 children
2. Binary Search Tree (BST): Left < Root < Right
3. Complete Binary Tree: All levels filled except possibly last (filled left to right)
4. Perfect Binary Tree: All internal nodes have 2 children, all leaves at same level
5. Balanced Tree: Height difference of subtrees <= 1
6. N-ary Tree: Each node can have N children

================================================================================
                           FILE ORGANIZATION
================================================================================

01_Traversals.cpp        - Inorder, Preorder, Postorder, Level Order, Morris
02_BinaryTreeBasics.cpp  - Height, Diameter, Balance check, Symmetric
03_BST_Operations.cpp    - Insert, Delete, Search, Validate, LCA in BST
04_TreeConstruction.cpp  - Build from traversals, Serialize/Deserialize
05_LCA_Ancestors.cpp     - Lowest Common Ancestor variants
06_PathProblems.cpp      - Root to leaf paths, Path sum problems
07_TreeViews.cpp         - Left, Right, Top, Bottom, Boundary views
08_TreeTransformations.cpp - Flatten, Invert, Convert to linked list
09_AdvancedTreeProblems.cpp - Hard tree problems

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// TREE NODE DEFINITIONS
// ─────────────────────────────────────────────────────────────────────────────

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;  // For Next pointer problems
    Node* parent; // For parent pointer problems
    Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr), parent(nullptr) {}
};

// N-ary tree node
struct NaryNode {
    int val;
    vector<NaryNode*> children;
    NaryNode(int x) : val(x) {}
};


// ─────────────────────────────────────────────────────────────────────────────
// TREE UTILITY FUNCTIONS
// ─────────────────────────────────────────────────────────────────────────────

// Build tree from level order (LeetCode style input)
TreeNode* buildTree(vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) return nullptr;
    
    TreeNode* root = new TreeNode(nodes[0]);
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;
    
    while (!q.empty() && i < nodes.size()) {
        TreeNode* curr = q.front();
        q.pop();
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->left = new TreeNode(nodes[i]);
            q.push(curr->left);
        }
        i++;
        
        if (i < nodes.size() && nodes[i] != -1) {
            curr->right = new TreeNode(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    
    return root;
}

// Print tree level order
void printTree(TreeNode* root) {
    if (!root) {
        cout << "[]" << endl;
        return;
    }
    
    queue<TreeNode*> q;
    q.push(root);
    vector<string> result;
    
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        if (node) {
            result.push_back(to_string(node->val));
            q.push(node->left);
            q.push(node->right);
        } else {
            result.push_back("null");
        }
    }
    
    // Remove trailing nulls
    while (!result.empty() && result.back() == "null") {
        result.pop_back();
    }
    
    cout << "[";
    for (int i = 0; i < result.size(); i++) {
        cout << result[i];
        if (i < result.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}


// ─────────────────────────────────────────────────────────────────────────────
// QUICK REFERENCE
// ─────────────────────────────────────────────────────────────────────────────

/*
TRAVERSAL ORDER:
- Inorder (Left, Root, Right): Sorted order for BST
- Preorder (Root, Left, Right): Used for serialization
- Postorder (Left, Right, Root): Used for deletion
- Level Order (BFS): Level by level

COMMON PATTERNS:
1. DFS (Recursion/Stack) - Most tree problems
2. BFS (Queue) - Level order, shortest path
3. Morris Traversal - O(1) space traversal
4. Parent Pointer - When need to go upward

TIME COMPLEXITY:
- Traversal: O(n)
- Search in BST: O(h) where h = height
- Balanced BST: h = log(n)
- Skewed BST: h = n

SPACE COMPLEXITY:
- Recursive DFS: O(h) stack space
- BFS: O(w) where w = max width
- Morris: O(1)
*/

int main() {
    cout << "=== Tree Data Structures ===" << endl;
    
    // Build sample tree: [1,2,3,4,5,null,6]
    vector<int> nodes = {1, 2, 3, 4, 5, -1, 6};
    TreeNode* root = buildTree(nodes);
    
    cout << "Sample tree: ";
    printTree(root);
    
    return 0;
}

