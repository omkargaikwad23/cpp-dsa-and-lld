/*
================================================================================
                    TREE PATH PROBLEMS
================================================================================

Problems involving paths in trees - root to leaf, any to any, path sums.

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
PROBLEM 1: Path Sum (LeetCode 112)
──────────────────────────────────
Check if root-to-leaf path with given sum exists.

Time: O(n) | Space: O(h)
*/
bool hasPathSum(TreeNode* root, int targetSum) {
    if (!root) return false;
    
    if (!root->left && !root->right) {
        return root->val == targetSum;
    }
    
    return hasPathSum(root->left, targetSum - root->val) || 
           hasPathSum(root->right, targetSum - root->val);
}


/*
PROBLEM 2: Path Sum II (LeetCode 113)
─────────────────────────────────────
Find all root-to-leaf paths with given sum.

Time: O(n²) | Space: O(n)
*/
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    vector<int> path;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int remaining) {
        if (!node) return;
        
        path.push_back(node->val);
        
        if (!node->left && !node->right && remaining == node->val) {
            result.push_back(path);
        }
        
        dfs(node->left, remaining - node->val);
        dfs(node->right, remaining - node->val);
        
        path.pop_back();
    };
    
    dfs(root, targetSum);
    return result;
}


/*
PROBLEM 3: Path Sum III (LeetCode 437) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────
Count paths that sum to target (can start/end anywhere).

Use prefix sum with hashmap.

Time: O(n) | Space: O(n)
*/
int pathSumIII(TreeNode* root, int targetSum) {
    unordered_map<long long, int> prefixCount;
    prefixCount[0] = 1;
    int count = 0;
    
    function<void(TreeNode*, long long)> dfs = [&](TreeNode* node, long long currSum) {
        if (!node) return;
        
        currSum += node->val;
        
        if (prefixCount.count(currSum - targetSum)) {
            count += prefixCount[currSum - targetSum];
        }
        
        prefixCount[currSum]++;
        dfs(node->left, currSum);
        dfs(node->right, currSum);
        prefixCount[currSum]--;
    };
    
    dfs(root, 0);
    return count;
}


/*
PROBLEM 4: Binary Tree Maximum Path Sum (LeetCode 124) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────
Find maximum sum path (any node to any node).

Time: O(n) | Space: O(h)
*/
int maxPathSum(TreeNode* root) {
    int maxSum = INT_MIN;
    
    function<int(TreeNode*)> maxGain = [&](TreeNode* node) -> int {
        if (!node) return 0;
        
        int leftGain = max(0, maxGain(node->left));
        int rightGain = max(0, maxGain(node->right));
        
        // Path through this node
        maxSum = max(maxSum, node->val + leftGain + rightGain);
        
        // Return max single path from this node
        return node->val + max(leftGain, rightGain);
    };
    
    maxGain(root);
    return maxSum;
}


/*
PROBLEM 5: Sum Root to Leaf Numbers (LeetCode 129)
──────────────────────────────────────────────────
Each path represents a number. Find total sum.

Time: O(n) | Space: O(h)
*/
int sumNumbers(TreeNode* root) {
    int total = 0;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int num) {
        if (!node) return;
        
        num = num * 10 + node->val;
        
        if (!node->left && !node->right) {
            total += num;
            return;
        }
        
        dfs(node->left, num);
        dfs(node->right, num);
    };
    
    dfs(root, 0);
    return total;
}


/*
PROBLEM 6: Binary Tree Paths (LeetCode 257)
───────────────────────────────────────────
Return all root-to-leaf paths as strings.

Time: O(n²) | Space: O(n)
*/
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> result;
    
    function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path) {
        if (!node) return;
        
        path += to_string(node->val);
        
        if (!node->left && !node->right) {
            result.push_back(path);
            return;
        }
        
        path += "->";
        dfs(node->left, path);
        dfs(node->right, path);
    };
    
    dfs(root, "");
    return result;
}


/*
PROBLEM 7: Longest Univalue Path (LeetCode 687)
───────────────────────────────────────────────
Longest path where all nodes have same value.

Time: O(n) | Space: O(h)
*/
int longestUnivaluePath(TreeNode* root) {
    int maxPath = 0;
    
    function<int(TreeNode*)> dfs = [&](TreeNode* node) -> int {
        if (!node) return 0;
        
        int left = dfs(node->left);
        int right = dfs(node->right);
        
        int leftPath = (node->left && node->left->val == node->val) ? left + 1 : 0;
        int rightPath = (node->right && node->right->val == node->val) ? right + 1 : 0;
        
        maxPath = max(maxPath, leftPath + rightPath);
        
        return max(leftPath, rightPath);
    };
    
    dfs(root);
    return maxPath;
}


/*
PROBLEM 8: Pseudo-Palindromic Paths (LeetCode 1457)
───────────────────────────────────────────────────
Count paths where digit frequencies allow palindrome.

Time: O(n) | Space: O(h)
*/
int pseudoPalindromicPaths(TreeNode* root) {
    int count = 0;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int mask) {
        if (!node) return;
        
        mask ^= (1 << node->val);  // Toggle bit for this digit
        
        if (!node->left && !node->right) {
            // Palindrome possible if at most one bit set
            if ((mask & (mask - 1)) == 0) count++;
            return;
        }
        
        dfs(node->left, mask);
        dfs(node->right, mask);
    };
    
    dfs(root, 0);
    return count;
}


/*
PROBLEM 9: Smallest String Starting From Leaf (LeetCode 988)
────────────────────────────────────────────────────────────
Find lexicographically smallest leaf-to-root path.

Time: O(n²) | Space: O(n)
*/
string smallestFromLeaf(TreeNode* root) {
    string result = "";
    
    function<void(TreeNode*, string)> dfs = [&](TreeNode* node, string path) {
        if (!node) return;
        
        path = char('a' + node->val) + path;  // Prepend
        
        if (!node->left && !node->right) {
            if (result.empty() || path < result) {
                result = path;
            }
            return;
        }
        
        dfs(node->left, path);
        dfs(node->right, path);
    };
    
    dfs(root, "");
    return result;
}


/*
PROBLEM 10: Count Good Nodes in Binary Tree (LeetCode 1448)
───────────────────────────────────────────────────────────
Node is good if no node on path from root has greater value.

Time: O(n) | Space: O(h)
*/
int goodNodes(TreeNode* root) {
    int count = 0;
    
    function<void(TreeNode*, int)> dfs = [&](TreeNode* node, int maxSoFar) {
        if (!node) return;
        
        if (node->val >= maxSoFar) {
            count++;
            maxSoFar = node->val;
        }
        
        dfs(node->left, maxSoFar);
        dfs(node->right, maxSoFar);
    };
    
    dfs(root, INT_MIN);
    return count;
}


/*
PROBLEM 11: Longest ZigZag Path (LeetCode 1372)
───────────────────────────────────────────────
Alternate left-right moves.

Time: O(n) | Space: O(h)
*/
int longestZigZag(TreeNode* root) {
    int maxLen = 0;
    
    // direction: 0 = came from left, 1 = came from right
    function<void(TreeNode*, int, int)> dfs = [&](TreeNode* node, int direction, int len) {
        if (!node) return;
        
        maxLen = max(maxLen, len);
        
        if (direction == 0) {  // Go right to continue zigzag
            dfs(node->right, 1, len + 1);
            dfs(node->left, 0, 1);  // Reset
        } else {
            dfs(node->left, 0, len + 1);
            dfs(node->right, 1, 1);  // Reset
        }
    };
    
    dfs(root->left, 0, 1);
    dfs(root->right, 1, 1);
    
    return maxLen;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Tree Path Problems ===\n\n";
    
    // Build tree: [5,4,8,11,null,13,4,7,2,null,null,5,1]
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(4);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(11);
    root->left->left->left = new TreeNode(7);
    root->left->left->right = new TreeNode(2);
    root->right->left = new TreeNode(13);
    root->right->right = new TreeNode(4);
    root->right->right->left = new TreeNode(5);
    root->right->right->right = new TreeNode(1);
    
    // Path Sum
    cout << "1. Has path sum 22: " << (hasPathSum(root, 22) ? "Yes" : "No") << "\n";
    
    // Path Sum III
    cout << "3. Paths with sum 8: " << pathSumIII(root, 8) << "\n";
    
    // Max Path Sum
    cout << "4. Max path sum: " << maxPathSum(root) << "\n";
    
    // Sum Numbers
    TreeNode* root2 = new TreeNode(1);
    root2->left = new TreeNode(2);
    root2->right = new TreeNode(3);
    cout << "5. Sum of numbers: " << sumNumbers(root2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Root-to-leaf sum              | DFS with remaining target                      |
| All paths with sum            | Backtracking with path vector                  |
| Path sum anywhere             | Prefix sum with hashmap                        |
| Max path (any-to-any)         | Track max gain at each node                    |
| Path as number                | num = num * 10 + node->val                     |
| Pseudo-palindromic            | Bitmask for digit frequency                    |
+───────────────────────────────+────────────────────────────────────────────────+

PATTERN: Most path problems use DFS with state tracking.

================================================================================
*/

