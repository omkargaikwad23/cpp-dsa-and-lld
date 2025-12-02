/*
================================================================================
                    TREE CONSTRUCTION & SERIALIZATION
================================================================================

Build trees from traversals, serialize/deserialize trees.

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
PROBLEM 1: Build Tree from Preorder and Inorder (LeetCode 105) ⭐ CLASSIC
─────────────────────────────────────────────────────────────────────────
Preorder: Root, Left, Right
Inorder: Left, Root, Right

Time: O(n) | Space: O(n)
*/
TreeNode* buildTreePreIn(vector<int>& preorder, vector<int>& inorder) {
    unordered_map<int, int> inorderIdx;
    for (int i = 0; i < inorder.size(); i++) {
        inorderIdx[inorder[i]] = i;
    }
    
    int preIdx = 0;
    
    function<TreeNode*(int, int)> build = [&](int left, int right) -> TreeNode* {
        if (left > right) return nullptr;
        
        int rootVal = preorder[preIdx++];
        TreeNode* root = new TreeNode(rootVal);
        
        int mid = inorderIdx[rootVal];
        root->left = build(left, mid - 1);
        root->right = build(mid + 1, right);
        
        return root;
    };
    
    return build(0, inorder.size() - 1);
}


/*
PROBLEM 2: Build Tree from Inorder and Postorder (LeetCode 106)
───────────────────────────────────────────────────────────────
Postorder: Left, Right, Root (root is last)

Time: O(n) | Space: O(n)
*/
TreeNode* buildTreeInPost(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int, int> inorderIdx;
    for (int i = 0; i < inorder.size(); i++) {
        inorderIdx[inorder[i]] = i;
    }
    
    int postIdx = postorder.size() - 1;
    
    function<TreeNode*(int, int)> build = [&](int left, int right) -> TreeNode* {
        if (left > right) return nullptr;
        
        int rootVal = postorder[postIdx--];
        TreeNode* root = new TreeNode(rootVal);
        
        int mid = inorderIdx[rootVal];
        root->right = build(mid + 1, right);  // Right first!
        root->left = build(left, mid - 1);
        
        return root;
    };
    
    return build(0, inorder.size() - 1);
}


/*
PROBLEM 3: Build Tree from Preorder and Postorder (LeetCode 889)
────────────────────────────────────────────────────────────────
Without inorder, multiple valid trees possible.

Time: O(n) | Space: O(n)
*/
TreeNode* buildTreePrePost(vector<int>& preorder, vector<int>& postorder) {
    unordered_map<int, int> postIdx;
    for (int i = 0; i < postorder.size(); i++) {
        postIdx[postorder[i]] = i;
    }
    
    int preIdx = 0;
    
    function<TreeNode*(int, int)> build = [&](int left, int right) -> TreeNode* {
        if (left > right) return nullptr;
        
        TreeNode* root = new TreeNode(preorder[preIdx++]);
        
        if (left == right) return root;
        
        int leftChildIdx = postIdx[preorder[preIdx]];
        root->left = build(left, leftChildIdx);
        root->right = build(leftChildIdx + 1, right - 1);
        
        return root;
    };
    
    return build(0, preorder.size() - 1);
}


/*
PROBLEM 4: Serialize and Deserialize Binary Tree (LeetCode 297) ⭐ GOOGLE FAVORITE
──────────────────────────────────────────────────────────────────────────────────
Convert tree to string and back.
*/
class Codec {
public:
    // Preorder serialization
    string serialize(TreeNode* root) {
        if (!root) return "null";
        return to_string(root->val) + "," + 
               serialize(root->left) + "," + 
               serialize(root->right);
    }
    
    TreeNode* deserialize(string data) {
        queue<string> nodes;
        stringstream ss(data);
        string token;
        
        while (getline(ss, token, ',')) {
            nodes.push(token);
        }
        
        return buildTree(nodes);
    }
    
private:
    TreeNode* buildTree(queue<string>& nodes) {
        string val = nodes.front();
        nodes.pop();
        
        if (val == "null") return nullptr;
        
        TreeNode* root = new TreeNode(stoi(val));
        root->left = buildTree(nodes);
        root->right = buildTree(nodes);
        
        return root;
    }
};

// Level Order Serialization (more space efficient for complete trees)
class CodecBFS {
public:
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        string result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            if (node) {
                result += to_string(node->val) + ",";
                q.push(node->left);
                q.push(node->right);
            } else {
                result += "null,";
            }
        }
        
        return result;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        vector<string> nodes;
        stringstream ss(data);
        string token;
        while (getline(ss, token, ',')) {
            if (!token.empty()) nodes.push_back(token);
        }
        
        TreeNode* root = new TreeNode(stoi(nodes[0]));
        queue<TreeNode*> q;
        q.push(root);
        int i = 1;
        
        while (!q.empty() && i < nodes.size()) {
            TreeNode* curr = q.front();
            q.pop();
            
            if (nodes[i] != "null") {
                curr->left = new TreeNode(stoi(nodes[i]));
                q.push(curr->left);
            }
            i++;
            
            if (i < nodes.size() && nodes[i] != "null") {
                curr->right = new TreeNode(stoi(nodes[i]));
                q.push(curr->right);
            }
            i++;
        }
        
        return root;
    }
};


/*
PROBLEM 5: Serialize BST (LeetCode 449)
───────────────────────────────────────
BST can be serialized more compactly (no nulls needed).

Time: O(n) | Space: O(n)
*/
class CodecBST {
public:
    string serialize(TreeNode* root) {
        string result;
        
        function<void(TreeNode*)> preorder = [&](TreeNode* node) {
            if (!node) return;
            result += to_string(node->val) + ",";
            preorder(node->left);
            preorder(node->right);
        };
        
        preorder(root);
        return result;
    }
    
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        queue<int> nodes;
        stringstream ss(data);
        string token;
        while (getline(ss, token, ',')) {
            if (!token.empty()) nodes.push(stoi(token));
        }
        
        return build(nodes, INT_MIN, INT_MAX);
    }
    
private:
    TreeNode* build(queue<int>& nodes, int minVal, int maxVal) {
        if (nodes.empty()) return nullptr;
        
        int val = nodes.front();
        if (val < minVal || val > maxVal) return nullptr;
        
        nodes.pop();
        TreeNode* root = new TreeNode(val);
        root->left = build(nodes, minVal, val);
        root->right = build(nodes, val, maxVal);
        
        return root;
    }
};


/*
PROBLEM 6: Maximum Binary Tree (LeetCode 654)
─────────────────────────────────────────────
Build tree where root is max element, left/right from left/right of max.

Time: O(n²) worst, O(n log n) average | Space: O(n)
*/
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
    function<TreeNode*(int, int)> build = [&](int left, int right) -> TreeNode* {
        if (left > right) return nullptr;
        
        int maxIdx = left;
        for (int i = left + 1; i <= right; i++) {
            if (nums[i] > nums[maxIdx]) maxIdx = i;
        }
        
        TreeNode* root = new TreeNode(nums[maxIdx]);
        root->left = build(left, maxIdx - 1);
        root->right = build(maxIdx + 1, right);
        
        return root;
    };
    
    return build(0, nums.size() - 1);
}


/*
PROBLEM 7: Construct BST from Preorder (LeetCode 1008)
──────────────────────────────────────────────────────
Time: O(n) | Space: O(n)
*/
TreeNode* bstFromPreorder(vector<int>& preorder) {
    int idx = 0;
    
    function<TreeNode*(int, int)> build = [&](int minVal, int maxVal) -> TreeNode* {
        if (idx >= preorder.size()) return nullptr;
        
        int val = preorder[idx];
        if (val < minVal || val > maxVal) return nullptr;
        
        idx++;
        TreeNode* root = new TreeNode(val);
        root->left = build(minVal, val);
        root->right = build(val, maxVal);
        
        return root;
    };
    
    return build(INT_MIN, INT_MAX);
}


/*
PROBLEM 8: Clone Tree with Random Pointer
─────────────────────────────────────────
Clone tree where nodes have random pointers.

Time: O(n) | Space: O(n)
*/
struct NodeRandom {
    int val;
    NodeRandom* left;
    NodeRandom* right;
    NodeRandom* random;
    NodeRandom(int x) : val(x), left(nullptr), right(nullptr), random(nullptr) {}
};

NodeRandom* cloneTree(NodeRandom* root) {
    if (!root) return nullptr;
    
    unordered_map<NodeRandom*, NodeRandom*> oldToNew;
    
    // First pass: create all nodes
    function<void(NodeRandom*)> createNodes = [&](NodeRandom* node) {
        if (!node) return;
        oldToNew[node] = new NodeRandom(node->val);
        createNodes(node->left);
        createNodes(node->right);
    };
    
    createNodes(root);
    
    // Second pass: connect pointers
    function<void(NodeRandom*)> connectPointers = [&](NodeRandom* node) {
        if (!node) return;
        NodeRandom* clone = oldToNew[node];
        clone->left = oldToNew[node->left];
        clone->right = oldToNew[node->right];
        clone->random = oldToNew[node->random];
        connectPointers(node->left);
        connectPointers(node->right);
    };
    
    connectPointers(root);
    
    return oldToNew[root];
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Tree Construction ===\n\n";
    
    // Test Preorder + Inorder
    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};
    
    TreeNode* root = buildTreePreIn(preorder, inorder);
    
    Codec codec;
    string serialized = codec.serialize(root);
    cout << "1. Serialized: " << serialized << "\n";
    
    TreeNode* deserialized = codec.deserialize(serialized);
    cout << "   Deserialized root: " << deserialized->val << "\n";
    
    // Test BST from Preorder
    vector<int> bstPre = {8, 5, 1, 7, 10, 12};
    TreeNode* bst = bstFromPreorder(bstPre);
    cout << "7. BST root: " << bst->val << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

CONSTRUCTION FROM TRAVERSALS:
+───────────────────────────────+────────────────────────────────────────────────+
| Given                         | Key Insight                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Preorder + Inorder            | Preorder[0] is root, split inorder             |
| Inorder + Postorder           | Postorder[-1] is root, split inorder           |
| Preorder + Postorder          | Multiple trees possible, left child in postorder|
| BST + Preorder only           | Use value bounds to determine subtrees         |
+───────────────────────────────+────────────────────────────────────────────────+

SERIALIZATION:
- DFS (Preorder): Simple, good for any tree
- BFS (Level order): Good for complete trees, easier visualization
- BST: No nulls needed, reconstruct using bounds

================================================================================
*/

