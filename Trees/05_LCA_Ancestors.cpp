/*
================================================================================
                    LOWEST COMMON ANCESTOR (LCA)
================================================================================

Find the deepest node that is ancestor of both given nodes.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;  // For some variants
    TreeNode(int x) : val(x), left(nullptr), right(nullptr), parent(nullptr) {}
};


/*
PROBLEM 1: LCA of Binary Tree (LeetCode 236) ⭐ GOOGLE FAVORITE
──────────────────────────────────────────────────────────────
Find LCA when both p and q exist in tree.

Time: O(n) | Space: O(h)
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    if (left && right) return root;  // p and q in different subtrees
    
    return left ? left : right;
}


/*
PROBLEM 2: LCA of BST (LeetCode 235)
────────────────────────────────────
Use BST property - much faster.

Time: O(h) | Space: O(1)
*/
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) {
            root = root->left;
        } else if (p->val > root->val && q->val > root->val) {
            root = root->right;
        } else {
            return root;
        }
    }
    return nullptr;
}


/*
PROBLEM 3: LCA with Parent Pointers (LeetCode 1650)
───────────────────────────────────────────────────
Nodes have parent pointers.

Approach 1: Find depths, align, then go up together.
Approach 2: Use set to track ancestors.
Approach 3: Two pointer technique (like linked list intersection)

Time: O(h) | Space: O(1)
*/
TreeNode* lowestCommonAncestorWithParent(TreeNode* p, TreeNode* q) {
    TreeNode* a = p;
    TreeNode* b = q;
    
    while (a != b) {
        a = a ? a->parent : q;
        b = b ? b->parent : p;
    }
    
    return a;
}


/*
PROBLEM 4: LCA of Binary Tree II (LeetCode 1644)
────────────────────────────────────────────────
p or q might not exist in tree.

Time: O(n) | Space: O(h)
*/
TreeNode* lowestCommonAncestorII(TreeNode* root, TreeNode* p, TreeNode* q) {
    bool foundP = false, foundQ = false;
    
    function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
        if (!node) return nullptr;
        
        TreeNode* left = dfs(node->left);
        TreeNode* right = dfs(node->right);
        
        if (node == p) {
            foundP = true;
            return node;
        }
        if (node == q) {
            foundQ = true;
            return node;
        }
        
        if (left && right) return node;
        return left ? left : right;
    };
    
    TreeNode* lca = dfs(root);
    
    return (foundP && foundQ) ? lca : nullptr;
}


/*
PROBLEM 5: LCA of Binary Tree III (LeetCode 1676)
─────────────────────────────────────────────────
Find LCA of multiple nodes.

Time: O(n * k) | Space: O(h)
*/
TreeNode* lowestCommonAncestorMultiple(TreeNode* root, vector<TreeNode*>& nodes) {
    unordered_set<TreeNode*> nodeSet(nodes.begin(), nodes.end());
    
    function<TreeNode*(TreeNode*)> dfs = [&](TreeNode* node) -> TreeNode* {
        if (!node) return nullptr;
        if (nodeSet.count(node)) return node;
        
        TreeNode* left = dfs(node->left);
        TreeNode* right = dfs(node->right);
        
        if (left && right) return node;
        return left ? left : right;
    };
    
    return dfs(root);
}


/*
PROBLEM 6: LCA of Deepest Leaves (LeetCode 1123)
────────────────────────────────────────────────
Find LCA of all deepest leaves.

Time: O(n) | Space: O(h)
*/
TreeNode* lcaDeepestLeaves(TreeNode* root) {
    function<pair<TreeNode*, int>(TreeNode*)> dfs = 
        [&](TreeNode* node) -> pair<TreeNode*, int> {
        if (!node) return {nullptr, 0};
        
        auto [leftLCA, leftDepth] = dfs(node->left);
        auto [rightLCA, rightDepth] = dfs(node->right);
        
        if (leftDepth > rightDepth) return {leftLCA, leftDepth + 1};
        if (rightDepth > leftDepth) return {rightLCA, rightDepth + 1};
        
        // Same depth - current node is LCA
        return {node, leftDepth + 1};
    };
    
    return dfs(root).first;
}


/*
PROBLEM 7: Ancestors of Node in Binary Tree
───────────────────────────────────────────
Print all ancestors of a given node.

Time: O(n) | Space: O(h)
*/
bool printAncestors(TreeNode* root, int target, vector<int>& ancestors) {
    if (!root) return false;
    
    if (root->val == target) return true;
    
    if (printAncestors(root->left, target, ancestors) || 
        printAncestors(root->right, target, ancestors)) {
        ancestors.push_back(root->val);
        return true;
    }
    
    return false;
}


/*
PROBLEM 8: Distance Between Two Nodes
─────────────────────────────────────
Find distance between two nodes using LCA.

Distance = depth(p) + depth(q) - 2 * depth(LCA)

Time: O(n) | Space: O(h)
*/
int findDistance(TreeNode* root, TreeNode* p, TreeNode* q) {
    auto lca = lowestCommonAncestor(root, p, q);
    
    function<int(TreeNode*, TreeNode*)> depth = [&](TreeNode* root, TreeNode* target) -> int {
        if (!root) return -1;
        if (root == target) return 0;
        
        int left = depth(root->left, target);
        if (left >= 0) return left + 1;
        
        int right = depth(root->right, target);
        if (right >= 0) return right + 1;
        
        return -1;
    };
    
    return depth(lca, p) + depth(lca, q);
}


/*
PROBLEM 9: All Nodes Distance K in Binary Tree (LeetCode 863) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────────────────────────
Find all nodes at distance K from target.

Approach: Convert to graph, BFS from target.

Time: O(n) | Space: O(n)
*/
vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    unordered_map<TreeNode*, TreeNode*> parent;
    
    // Build parent pointers
    function<void(TreeNode*, TreeNode*)> buildParent = [&](TreeNode* node, TreeNode* par) {
        if (!node) return;
        parent[node] = par;
        buildParent(node->left, node);
        buildParent(node->right, node);
    };
    
    buildParent(root, nullptr);
    
    // BFS from target
    vector<int> result;
    unordered_set<TreeNode*> visited;
    queue<TreeNode*> q;
    
    q.push(target);
    visited.insert(target);
    int dist = 0;
    
    while (!q.empty()) {
        if (dist == k) {
            while (!q.empty()) {
                result.push_back(q.front()->val);
                q.pop();
            }
            return result;
        }
        
        int size = q.size();
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // Add neighbors (left, right, parent)
            for (TreeNode* next : {node->left, node->right, parent[node]}) {
                if (next && !visited.count(next)) {
                    visited.insert(next);
                    q.push(next);
                }
            }
        }
        dist++;
    }
    
    return result;
}


/*
PROBLEM 10: Kth Ancestor of a Tree Node (LeetCode 1483)
───────────────────────────────────────────────────────
Binary Lifting for O(log n) queries.

Time: O(n log n) preprocess, O(log n) query | Space: O(n log n)
*/
class TreeAncestor {
    vector<vector<int>> ancestor;
    int LOG;
    
public:
    TreeAncestor(int n, vector<int>& parent) {
        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        
        ancestor.assign(n, vector<int>(LOG, -1));
        
        // Base case: direct parent
        for (int i = 0; i < n; i++) {
            ancestor[i][0] = parent[i];
        }
        
        // Binary lifting
        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                if (ancestor[i][j-1] != -1) {
                    ancestor[i][j] = ancestor[ancestor[i][j-1]][j-1];
                }
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        for (int j = 0; j < LOG && node != -1; j++) {
            if (k & (1 << j)) {
                node = ancestor[node][j];
            }
        }
        return node;
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== LCA and Ancestors ===\n\n";
    
    // Build tree: [3,5,1,6,2,0,8,null,null,7,4]
    TreeNode* root = new TreeNode(3);
    TreeNode* p = root->left = new TreeNode(5);
    root->right = new TreeNode(1);
    root->left->left = new TreeNode(6);
    TreeNode* q = root->left->right = new TreeNode(2);
    root->right->left = new TreeNode(0);
    root->right->right = new TreeNode(8);
    root->left->right->left = new TreeNode(7);
    root->left->right->right = new TreeNode(4);
    
    // LCA
    TreeNode* lca = lowestCommonAncestor(root, p, q);
    cout << "1. LCA of 5 and 2: " << lca->val << "\n";
    
    // Distance K
    auto nodes = distanceK(root, p, 2);
    cout << "9. Nodes at distance 2 from 5: ";
    for (int v : nodes) cout << v << " ";
    cout << "\n";
    
    // Deepest Leaves LCA
    TreeNode* deepestLCA = lcaDeepestLeaves(root);
    cout << "6. LCA of deepest leaves: " << deepestLCA->val << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Variant                       | Key Approach                                   |
+───────────────────────────────+────────────────────────────────────────────────+
| Binary Tree LCA               | Find node where left and right both non-null   |
| BST LCA                       | Use BST property, O(h)                         |
| With Parent Pointers          | Two-pointer like linked list intersection      |
| Multiple Nodes LCA            | Use set, find where left & right merge         |
| Deepest Leaves LCA            | Return node where depths equal                 |
| Distance K Nodes              | Build parent map, BFS from target              |
| Kth Ancestor (queries)        | Binary Lifting for O(log n)                    |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

