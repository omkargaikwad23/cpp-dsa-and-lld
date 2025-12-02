/*
================================================================================
                    PATTERN 15: DP ON TREES
================================================================================

When to use:
- Tree-structured data
- Compute values based on children/parent
- Selection problems on trees

LeetCode Problems:
- 337. House Robber III
- 124. Binary Tree Maximum Path Sum
- 968. Binary Tree Cameras

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

/*
PROBLEM 1: House Robber III (LeetCode 337) ⭐
────────────────────────────────────────────
Can't rob adjacent nodes (parent-child).

Return {max if rob this, max if don't rob this}

Time: O(n) | Space: O(h)
*/
pair<int, int> robHelper(TreeNode* root) {
    if (!root) return {0, 0};
    
    auto [leftRob, leftNotRob] = robHelper(root->left);
    auto [rightRob, rightNotRob] = robHelper(root->right);
    
    int robThis = root->val + leftNotRob + rightNotRob;
    int notRobThis = max(leftRob, leftNotRob) + max(rightRob, rightNotRob);
    
    return {robThis, notRobThis};
}

int rob(TreeNode* root) {
    auto [robRoot, notRobRoot] = robHelper(root);
    return max(robRoot, notRobRoot);
}


/*
PROBLEM 2: Binary Tree Maximum Path Sum (LeetCode 124) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────
Find path with maximum sum (any path in tree).

For each node, compute max single-side path and update global max.

Time: O(n) | Space: O(h)
*/
class Solution124 {
    int maxSum = INT_MIN;
    
    int maxGain(TreeNode* node) {
        if (!node) return 0;
        
        int leftGain = max(0, maxGain(node->left));
        int rightGain = max(0, maxGain(node->right));
        
        // Path through this node
        maxSum = max(maxSum, node->val + leftGain + rightGain);
        
        // Return max single path
        return node->val + max(leftGain, rightGain);
    }
    
public:
    int maxPathSum(TreeNode* root) {
        maxGain(root);
        return maxSum;
    }
};


/*
PROBLEM 3: Binary Tree Cameras (LeetCode 968) ⭐
───────────────────────────────────────────────
Place minimum cameras to monitor all nodes.
Camera monitors parent, itself, and children.

States: 0 = needs camera, 1 = has camera, 2 = covered

Time: O(n) | Space: O(h)
*/
class Solution968 {
    int cameras = 0;
    
    int dfs(TreeNode* node) {
        if (!node) return 2;  // Null is covered
        
        int left = dfs(node->left);
        int right = dfs(node->right);
        
        if (left == 0 || right == 0) {
            // Child needs camera, place one here
            cameras++;
            return 1;
        }
        
        if (left == 1 || right == 1) {
            // Child has camera, this is covered
            return 2;
        }
        
        // Both children covered, this needs camera
        return 0;
    }
    
public:
    int minCameraCover(TreeNode* root) {
        if (dfs(root) == 0) cameras++;  // Root needs camera
        return cameras;
    }
};


/*
PROBLEM 4: Diameter of Binary Tree (LeetCode 543)
─────────────────────────────────────────────────
Longest path between any two nodes.

Time: O(n) | Space: O(h)
*/
class Solution543 {
    int diameter = 0;
    
    int depth(TreeNode* node) {
        if (!node) return 0;
        int left = depth(node->left);
        int right = depth(node->right);
        diameter = max(diameter, left + right);
        return 1 + max(left, right);
    }
    
public:
    int diameterOfBinaryTree(TreeNode* root) {
        depth(root);
        return diameter;
    }
};


/*
PROBLEM 5: Longest Univalue Path (LeetCode 687)
───────────────────────────────────────────────
Longest path where all nodes have same value.

Time: O(n) | Space: O(h)
*/
class Solution687 {
    int maxPath = 0;
    
    int dfs(TreeNode* node) {
        if (!node) return 0;
        
        int left = dfs(node->left);
        int right = dfs(node->right);
        
        int leftPath = (node->left && node->left->val == node->val) ? left + 1 : 0;
        int rightPath = (node->right && node->right->val == node->val) ? right + 1 : 0;
        
        maxPath = max(maxPath, leftPath + rightPath);
        return max(leftPath, rightPath);
    }
    
public:
    int longestUnivaluePath(TreeNode* root) {
        dfs(root);
        return maxPath;
    }
};


/*
PROBLEM 6: Sum of Distances in Tree (LeetCode 834) ⭐ HARD
──────────────────────────────────────────────────────────
For each node, sum of distances to all other nodes.

Re-rooting technique: First DFS for one root, then adjust for others.

Time: O(n) | Space: O(n)
*/
class Solution834 {
    vector<vector<int>> graph;
    vector<int> count;   // Number of nodes in subtree
    vector<int> result;  // Sum of distances
    int n;
    
    void dfs1(int node, int parent) {
        for (int child : graph[node]) {
            if (child != parent) {
                dfs1(child, node);
                count[node] += count[child];
                result[node] += result[child] + count[child];
            }
        }
    }
    
    void dfs2(int node, int parent) {
        for (int child : graph[node]) {
            if (child != parent) {
                // Moving root from node to child:
                // - Nodes in child's subtree get 1 closer
                // - Nodes outside get 1 farther
                result[child] = result[node] - count[child] + (n - count[child]);
                dfs2(child, node);
            }
        }
    }
    
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        this->n = n;
        graph.resize(n);
        count.resize(n, 1);
        result.resize(n, 0);
        
        for (auto& e : edges) {
            graph[e[0]].push_back(e[1]);
            graph[e[1]].push_back(e[0]);
        }
        
        dfs1(0, -1);
        dfs2(0, -1);
        
        return result;
    }
};


/*
PROBLEM 7: Tree DP on General Tree (Classic)
────────────────────────────────────────────
Max independent set on tree (no adjacent nodes).

Time: O(n) | Space: O(n)
*/
vector<vector<int>> adj;
vector<int> weight;

pair<int, int> treeDP(int node, int parent) {
    int include = weight[node];
    int exclude = 0;
    
    for (int child : adj[node]) {
        if (child != parent) {
            auto [childIncl, childExcl] = treeDP(child, node);
            include += childExcl;  // If include node, exclude children
            exclude += max(childIncl, childExcl);  // If exclude, take max of children
        }
    }
    
    return {include, exclude};
}


/*
PROBLEM 8: Number of Good Leaf Nodes Pairs (LeetCode 1530)
──────────────────────────────────────────────────────────
Count pairs of leaves with distance <= distance.

Time: O(n * distance²) | Space: O(n * distance)
*/
class Solution1530 {
    int result = 0;
    int dist;
    
    vector<int> dfs(TreeNode* node) {
        if (!node) return {};
        if (!node->left && !node->right) return {1};  // Leaf at distance 1
        
        auto left = dfs(node->left);
        auto right = dfs(node->right);
        
        // Count pairs
        for (int l : left) {
            for (int r : right) {
                if (l + r <= dist) result++;
            }
        }
        
        // Merge distances
        vector<int> distances;
        for (int l : left) if (l + 1 < dist) distances.push_back(l + 1);
        for (int r : right) if (r + 1 < dist) distances.push_back(r + 1);
        
        return distances;
    }
    
public:
    int countPairs(TreeNode* root, int distance) {
        dist = distance;
        dfs(root);
        return result;
    }
};


// ============================================================================
// MAIN (Demo with sample tree)
// ============================================================================

int main() {
    cout << "=== Tree DP ===\n\n";
    
    // Create sample tree: [3,2,3,null,3,null,1]
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(3);
    root->right->right = new TreeNode(1);
    
    // House Robber III
    cout << "1. House Robber III: " << rob(root) << "\n";
    
    // Max Path Sum
    Solution124 sol124;
    cout << "2. Max Path Sum: " << sol124.maxPathSum(root) << "\n";
    
    // Cameras
    TreeNode* root2 = new TreeNode(0);
    root2->left = new TreeNode(0);
    root2->left->left = new TreeNode(0);
    root2->left->right = new TreeNode(0);
    
    Solution968 sol968;
    cout << "3. Min Cameras: " << sol968.minCameraCover(root2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

TREE DP TEMPLATE:
    pair<int,int> dfs(node) {
        if (!node) return base_case;
        
        auto [leftA, leftB] = dfs(node->left);
        auto [rightA, rightB] = dfs(node->right);
        
        int includeThis = f(leftB, rightB, node->val);
        int excludeThis = g(leftA, leftB, rightA, rightB);
        
        return {includeThis, excludeThis};
    }

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | States Returned                                |
+───────────────────────────────+────────────────────────────────────────────────+
| House Robber III              | {rob this, don't rob this}                     |
| Binary Tree Cameras           | {needs camera, has camera, covered}            |
| Max Path Sum                  | Global max + max single path                   |
| Sum of Distances              | Re-rooting: adjust from parent                 |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

