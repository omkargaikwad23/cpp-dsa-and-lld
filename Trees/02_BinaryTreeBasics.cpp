/*
================================================================================
                    BINARY TREE BASICS
================================================================================

Fundamental binary tree operations and properties.

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
PROBLEM 1: Maximum Depth / Height (LeetCode 104)
────────────────────────────────────────────────
Time: O(n) | Space: O(h)
*/
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// Iterative BFS
int maxDepthBFS(TreeNode* root) {
    if (!root) return 0;
    
    queue<TreeNode*> q;
    q.push(root);
    int depth = 0;
    
    while (!q.empty()) {
        int size = q.size();
        depth++;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    return depth;
}


/*
PROBLEM 2: Minimum Depth (LeetCode 111)
───────────────────────────────────────
Distance to nearest leaf.

Time: O(n) | Space: O(h)
*/
int minDepth(TreeNode* root) {
    if (!root) return 0;
    
    if (!root->left) return 1 + minDepth(root->right);
    if (!root->right) return 1 + minDepth(root->left);
    
    return 1 + min(minDepth(root->left), minDepth(root->right));
}

// BFS is better for min depth (finds first leaf faster)
int minDepthBFS(TreeNode* root) {
    if (!root) return 0;
    
    queue<TreeNode*> q;
    q.push(root);
    int depth = 0;
    
    while (!q.empty()) {
        depth++;
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // First leaf found
            if (!node->left && !node->right) return depth;
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
    }
    
    return depth;
}


/*
PROBLEM 3: Diameter of Binary Tree (LeetCode 543) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────────────
Longest path between any two nodes.

Time: O(n) | Space: O(h)
*/
int diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    
    function<int(TreeNode*)> height = [&](TreeNode* node) -> int {
        if (!node) return 0;
        
        int left = height(node->left);
        int right = height(node->right);
        
        diameter = max(diameter, left + right);
        
        return 1 + max(left, right);
    };
    
    height(root);
    return diameter;
}


/*
PROBLEM 4: Balanced Binary Tree (LeetCode 110)
──────────────────────────────────────────────
Check if height difference <= 1 for all nodes.

Time: O(n) | Space: O(h)
*/
bool isBalanced(TreeNode* root) {
    function<int(TreeNode*)> checkHeight = [&](TreeNode* node) -> int {
        if (!node) return 0;
        
        int left = checkHeight(node->left);
        if (left == -1) return -1;
        
        int right = checkHeight(node->right);
        if (right == -1) return -1;
        
        if (abs(left - right) > 1) return -1;
        
        return 1 + max(left, right);
    };
    
    return checkHeight(root) != -1;
}


/*
PROBLEM 5: Same Tree (LeetCode 100)
───────────────────────────────────
Check if two trees are identical.

Time: O(n) | Space: O(h)
*/
bool isSameTree(TreeNode* p, TreeNode* q) {
    if (!p && !q) return true;
    if (!p || !q) return false;
    
    return p->val == q->val && 
           isSameTree(p->left, q->left) && 
           isSameTree(p->right, q->right);
}


/*
PROBLEM 6: Symmetric Tree (LeetCode 101) ⭐
──────────────────────────────────────────
Check if tree is mirror of itself.

Time: O(n) | Space: O(h)
*/
bool isSymmetric(TreeNode* root) {
    function<bool(TreeNode*, TreeNode*)> isMirror = [&](TreeNode* t1, TreeNode* t2) -> bool {
        if (!t1 && !t2) return true;
        if (!t1 || !t2) return false;
        
        return t1->val == t2->val && 
               isMirror(t1->left, t2->right) && 
               isMirror(t1->right, t2->left);
    };
    
    return isMirror(root, root);
}


/*
PROBLEM 7: Invert Binary Tree (LeetCode 226) ⭐ CLASSIC
──────────────────────────────────────────────────────
Mirror the tree (swap left and right).

Time: O(n) | Space: O(h)
*/
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    
    return root;
}


/*
PROBLEM 8: Subtree of Another Tree (LeetCode 572)
─────────────────────────────────────────────────
Check if tree t is subtree of tree s.

Time: O(m * n) | Space: O(h)
*/
bool isSubtree(TreeNode* root, TreeNode* subRoot) {
    if (!root) return false;
    
    if (isSameTree(root, subRoot)) return true;
    
    return isSubtree(root->left, subRoot) || isSubtree(root->right, subRoot);
}


/*
PROBLEM 9: Count Complete Tree Nodes (LeetCode 222)
───────────────────────────────────────────────────
Count nodes in complete binary tree efficiently.

Time: O(log²n) | Space: O(log n)
*/
int countNodes(TreeNode* root) {
    if (!root) return 0;
    
    int leftHeight = 0, rightHeight = 0;
    TreeNode* l = root, *r = root;
    
    while (l) { leftHeight++; l = l->left; }
    while (r) { rightHeight++; r = r->right; }
    
    if (leftHeight == rightHeight) {
        return (1 << leftHeight) - 1;  // Perfect tree: 2^h - 1
    }
    
    return 1 + countNodes(root->left) + countNodes(root->right);
}


/*
PROBLEM 10: Maximum Width of Binary Tree (LeetCode 662)
───────────────────────────────────────────────────────
Max width including nulls.

Time: O(n) | Space: O(n)
*/
int widthOfBinaryTree(TreeNode* root) {
    if (!root) return 0;
    
    unsigned long long maxWidth = 0;
    queue<pair<TreeNode*, unsigned long long>> q;
    q.push({root, 0});
    
    while (!q.empty()) {
        int size = q.size();
        unsigned long long left = q.front().second;
        unsigned long long right = left;
        
        for (int i = 0; i < size; i++) {
            auto [node, idx] = q.front();
            q.pop();
            right = idx;
            
            if (node->left) q.push({node->left, 2 * (idx - left)});
            if (node->right) q.push({node->right, 2 * (idx - left) + 1});
        }
        
        maxWidth = max(maxWidth, right - left + 1);
    }
    
    return maxWidth;
}


/*
PROBLEM 11: Find Leaves of Binary Tree (LeetCode 366)
─────────────────────────────────────────────────────
Collect leaves level by level from bottom.

Time: O(n) | Space: O(n)
*/
vector<vector<int>> findLeaves(TreeNode* root) {
    vector<vector<int>> result;
    
    function<int(TreeNode*)> getHeight = [&](TreeNode* node) -> int {
        if (!node) return -1;
        
        int height = 1 + max(getHeight(node->left), getHeight(node->right));
        
        if (height >= result.size()) {
            result.push_back({});
        }
        result[height].push_back(node->val);
        
        return height;
    };
    
    getHeight(root);
    return result;
}


/*
PROBLEM 12: Merge Two Binary Trees (LeetCode 617)
─────────────────────────────────────────────────
Overlay two trees, sum overlapping nodes.

Time: O(n) | Space: O(h)
*/
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    if (!root1) return root2;
    if (!root2) return root1;
    
    root1->val += root2->val;
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);
    
    return root1;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Binary Tree Basics ===\n\n";
    
    // Build tree: [1,2,3,4,5]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    
    cout << "1. Max Depth: " << maxDepth(root) << "\n";
    cout << "2. Min Depth: " << minDepth(root) << "\n";
    cout << "3. Diameter: " << diameterOfBinaryTree(root) << "\n";
    cout << "4. Balanced: " << (isBalanced(root) ? "Yes" : "No") << "\n";
    cout << "6. Symmetric: " << (isSymmetric(root) ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Insight                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Max Depth                     | 1 + max(left, right)                           |
| Min Depth                     | BFS finds first leaf faster                    |
| Diameter                      | max(left + right) at each node                 |
| Balanced                      | Return -1 if unbalanced (early termination)    |
| Symmetric                     | Check mirror(left, right)                      |
| Invert                        | Swap children recursively                      |
| Complete Tree Count           | O(log²n) using height comparison               |
| Width                         | BFS with position indexing                     |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

