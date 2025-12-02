/*
================================================================================
                    TREE VIEWS (Left, Right, Top, Bottom, Boundary)
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


/*
PROBLEM 1: Right Side View (LeetCode 199) ⭐ GOOGLE FAVORITE
──────────────────────────────────────────────────────────
See tree from right side.
Time: O(n) | Space: O(h)
*/
vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
        if (!node) return;
        
        if (depth == result.size()) {
            result.push_back(node->val);
        }
        
        dfs(node->right, depth + 1);  // Right first
        dfs(node->left, depth + 1);
    };
    
    dfs(root, 0);
    return result;
}


/*
PROBLEM 2: Left Side View
─────────────────────────
*/
vector<int> leftSideView(TreeNode* root) {
    vector<int> result;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int depth) {
        if (!node) return;
        if (depth == result.size()) result.push_back(node->val);
        dfs(node->left, depth + 1);   // Left first
        dfs(node->right, depth + 1);
    };
    
    dfs(root, 0);
    return result;
}


/*
PROBLEM 3: Top View
───────────────────
Nodes visible from top (first node at each horizontal distance).
Time: O(n) | Space: O(n)
*/
vector<int> topView(TreeNode* root) {
    if (!root) return {};
    
    map<int, int> topNodes;  // col -> value
    queue<pair<TreeNode*, int>> q;  // node, col
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, col] = q.front();
        q.pop();
        
        if (!topNodes.count(col)) {
            topNodes[col] = node->val;
        }
        
        if (node->left) q.push({node->left, col - 1});
        if (node->right) q.push({node->right, col + 1});
    }
    
    vector<int> result;
    for (auto& [col, val] : topNodes) {
        result.push_back(val);
    }
    return result;
}


/*
PROBLEM 4: Bottom View
──────────────────────
Last node at each horizontal distance.
*/
vector<int> bottomView(TreeNode* root) {
    if (!root) return {};
    
    map<int, int> bottomNodes;
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        auto [node, col] = q.front();
        q.pop();
        
        bottomNodes[col] = node->val;  // Overwrite (last one wins)
        
        if (node->left) q.push({node->left, col - 1});
        if (node->right) q.push({node->right, col + 1});
    }
    
    vector<int> result;
    for (auto& [col, val] : bottomNodes) {
        result.push_back(val);
    }
    return result;
}


/*
PROBLEM 5: Boundary of Binary Tree (LeetCode 545) ⭐
───────────────────────────────────────────────────
Anti-clockwise boundary: left boundary + leaves + right boundary (reversed).
Time: O(n) | Space: O(n)
*/
vector<int> boundaryOfBinaryTree(TreeNode* root) {
    if (!root) return {};
    
    vector<int> result = {root->val};
    if (!root->left && !root->right) return result;
    
    // Left boundary (exclude leaf)
    function<void(TreeNode*)> leftBoundary = [&](TreeNode* node) {
        if (!node || (!node->left && !node->right)) return;
        result.push_back(node->val);
        if (node->left) leftBoundary(node->left);
        else leftBoundary(node->right);
    };
    
    // Leaves
    function<void(TreeNode*)> leaves = [&](TreeNode* node) {
        if (!node) return;
        if (!node->left && !node->right) {
            result.push_back(node->val);
            return;
        }
        leaves(node->left);
        leaves(node->right);
    };
    
    // Right boundary (exclude leaf, add in reverse)
    vector<int> rightBound;
    function<void(TreeNode*)> rightBoundary = [&](TreeNode* node) {
        if (!node || (!node->left && !node->right)) return;
        rightBound.push_back(node->val);
        if (node->right) rightBoundary(node->right);
        else rightBoundary(node->left);
    };
    
    leftBoundary(root->left);
    leaves(root);
    rightBoundary(root->right);
    
    for (int i = rightBound.size() - 1; i >= 0; i--) {
        result.push_back(rightBound[i]);
    }
    
    return result;
}


/*
PROBLEM 6: Vertical Order Traversal (LeetCode 987)
──────────────────────────────────────────────────
*/
vector<vector<int>> verticalTraversal(TreeNode* root) {
    vector<tuple<int, int, int>> nodes;  // col, row, val
    
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


int main() {
    cout << "=== Tree Views ===\n\n";
    
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(4);
    
    auto right = rightSideView(root);
    cout << "Right view: ";
    for (int v : right) cout << v << " ";
    cout << "\n";
    
    return 0;
}

/*
SUMMARY:
+───────────────────+────────────────────────────────────────────+
| View              | Approach                                   |
+───────────────────+────────────────────────────────────────────+
| Right Side        | DFS right-first, track depth               |
| Left Side         | DFS left-first, track depth                |
| Top View          | BFS with column, first at each col         |
| Bottom View       | BFS with column, last at each col          |
| Boundary          | Left boundary + leaves + right (reversed)  |
+───────────────────+────────────────────────────────────────────+
*/

