/*
================================================================================
                    BINARY SEARCH TREE (BST) OPERATIONS
================================================================================

BST Property: Left < Root < Right (for all nodes)

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
PROBLEM 1: Search in BST (LeetCode 700)
───────────────────────────────────────
Time: O(h) | Space: O(1) iterative, O(h) recursive
*/
TreeNode* searchBST(TreeNode* root, int val) {
    while (root && root->val != val) {
        root = val < root->val ? root->left : root->right;
    }
    return root;
}


/*
PROBLEM 2: Insert into BST (LeetCode 701)
─────────────────────────────────────────
Time: O(h) | Space: O(h)
*/
TreeNode* insertIntoBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    
    if (val < root->val) {
        root->left = insertIntoBST(root->left, val);
    } else {
        root->right = insertIntoBST(root->right, val);
    }
    
    return root;
}

// Iterative
TreeNode* insertIntoBSTIterative(TreeNode* root, int val) {
    TreeNode* node = new TreeNode(val);
    if (!root) return node;
    
    TreeNode* curr = root;
    while (true) {
        if (val < curr->val) {
            if (!curr->left) { curr->left = node; break; }
            curr = curr->left;
        } else {
            if (!curr->right) { curr->right = node; break; }
            curr = curr->right;
        }
    }
    
    return root;
}


/*
PROBLEM 3: Delete Node in BST (LeetCode 450) ⭐
──────────────────────────────────────────────
Three cases:
1. Leaf: simply remove
2. One child: replace with child
3. Two children: replace with inorder successor/predecessor

Time: O(h) | Space: O(h)
*/
TreeNode* deleteNode(TreeNode* root, int key) {
    if (!root) return nullptr;
    
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        // Found node to delete
        
        // Case 1 & 2: Zero or one child
        if (!root->left) return root->right;
        if (!root->right) return root->left;
        
        // Case 3: Two children - find inorder successor
        TreeNode* successor = root->right;
        while (successor->left) {
            successor = successor->left;
        }
        
        root->val = successor->val;
        root->right = deleteNode(root->right, successor->val);
    }
    
    return root;
}


/*
PROBLEM 4: Validate BST (LeetCode 98) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────
Check if tree is valid BST.

Time: O(n) | Space: O(h)
*/
bool isValidBST(TreeNode* root) {
    function<bool(TreeNode*, long, long)> validate = 
        [&](TreeNode* node, long minVal, long maxVal) -> bool {
        if (!node) return true;
        
        if (node->val <= minVal || node->val >= maxVal) return false;
        
        return validate(node->left, minVal, node->val) && 
               validate(node->right, node->val, maxVal);
    };
    
    return validate(root, LONG_MIN, LONG_MAX);
}

// Inorder approach (should be strictly increasing)
bool isValidBSTInorder(TreeNode* root) {
    TreeNode* prev = nullptr;
    
    function<bool(TreeNode*)> inorder = [&](TreeNode* node) -> bool {
        if (!node) return true;
        
        if (!inorder(node->left)) return false;
        
        if (prev && prev->val >= node->val) return false;
        prev = node;
        
        return inorder(node->right);
    };
    
    return inorder(root);
}


/*
PROBLEM 5: Lowest Common Ancestor in BST (LeetCode 235) ⭐
─────────────────────────────────────────────────────────
Use BST property to find split point.

Time: O(h) | Space: O(1)
*/
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
    while (root) {
        if (p->val < root->val && q->val < root->val) {
            root = root->left;
        } else if (p->val > root->val && q->val > root->val) {
            root = root->right;
        } else {
            return root;  // Split point
        }
    }
    return nullptr;
}


/*
PROBLEM 6: Kth Smallest in BST (LeetCode 230) ⭐ GOOGLE FAVORITE
──────────────────────────────────────────────────────────────
Inorder traversal gives sorted order.

Time: O(h + k) | Space: O(h)
*/
int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> stk;
    TreeNode* curr = root;
    
    while (curr || !stk.empty()) {
        while (curr) {
            stk.push(curr);
            curr = curr->left;
        }
        
        curr = stk.top();
        stk.pop();
        
        if (--k == 0) return curr->val;
        
        curr = curr->right;
    }
    
    return -1;
}


/*
PROBLEM 7: Inorder Successor in BST (LeetCode 285)
──────────────────────────────────────────────────
Find next larger element.

Time: O(h) | Space: O(1)
*/
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
    TreeNode* successor = nullptr;
    
    while (root) {
        if (p->val < root->val) {
            successor = root;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    
    return successor;
}

// Inorder Predecessor
TreeNode* inorderPredecessor(TreeNode* root, TreeNode* p) {
    TreeNode* predecessor = nullptr;
    
    while (root) {
        if (p->val > root->val) {
            predecessor = root;
            root = root->right;
        } else {
            root = root->left;
        }
    }
    
    return predecessor;
}


/*
PROBLEM 8: Two Sum in BST (LeetCode 653)
────────────────────────────────────────
Find two nodes that sum to target.

Time: O(n) | Space: O(n)
*/
bool findTarget(TreeNode* root, int k) {
    unordered_set<int> seen;
    
    function<bool(TreeNode*)> dfs = [&](TreeNode* node) -> bool {
        if (!node) return false;
        
        if (seen.count(k - node->val)) return true;
        seen.insert(node->val);
        
        return dfs(node->left) || dfs(node->right);
    };
    
    return dfs(root);
}


/*
PROBLEM 9: Convert Sorted Array to BST (LeetCode 108)
─────────────────────────────────────────────────────
Build balanced BST from sorted array.

Time: O(n) | Space: O(log n)
*/
TreeNode* sortedArrayToBST(vector<int>& nums) {
    function<TreeNode*(int, int)> build = [&](int left, int right) -> TreeNode* {
        if (left > right) return nullptr;
        
        int mid = left + (right - left) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = build(left, mid - 1);
        root->right = build(mid + 1, right);
        
        return root;
    };
    
    return build(0, nums.size() - 1);
}


/*
PROBLEM 10: Convert BST to Sorted Doubly Linked List (LeetCode 426)
───────────────────────────────────────────────────────────────────
Inorder traversal, link nodes.

Time: O(n) | Space: O(h)
*/
TreeNode* treeToDoublyList(TreeNode* root) {
    if (!root) return nullptr;
    
    TreeNode* head = nullptr;
    TreeNode* prev = nullptr;
    
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        
        inorder(node->left);
        
        if (prev) {
            prev->right = node;
            node->left = prev;
        } else {
            head = node;
        }
        prev = node;
        
        inorder(node->right);
    };
    
    inorder(root);
    
    // Connect head and tail (circular)
    head->left = prev;
    prev->right = head;
    
    return head;
}


/*
PROBLEM 11: Recover BST (LeetCode 99) ⭐
───────────────────────────────────────
Two nodes swapped, restore BST.

Time: O(n) | Space: O(h)
*/
void recoverTree(TreeNode* root) {
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prev = nullptr;
    
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        
        inorder(node->left);
        
        if (prev && prev->val > node->val) {
            if (!first) {
                first = prev;
            }
            second = node;
        }
        prev = node;
        
        inorder(node->right);
    };
    
    inorder(root);
    swap(first->val, second->val);
}


/*
PROBLEM 12: Trim BST (LeetCode 669)
───────────────────────────────────
Remove nodes outside [low, high].

Time: O(n) | Space: O(h)
*/
TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (!root) return nullptr;
    
    if (root->val < low) return trimBST(root->right, low, high);
    if (root->val > high) return trimBST(root->left, low, high);
    
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    
    return root;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== BST Operations ===\n\n";
    
    // Build BST: [4,2,6,1,3,5,7]
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    
    cout << "4. Valid BST: " << (isValidBST(root) ? "Yes" : "No") << "\n";
    
    TreeNode* p = root->left;  // 2
    TreeNode* q = root->left->right;  // 3
    cout << "5. LCA of 2,3: " << lowestCommonAncestorBST(root, p, q)->val << "\n";
    
    cout << "6. 3rd smallest: " << kthSmallest(root, 3) << "\n";
    
    cout << "8. Has pair sum 9: " << (findTarget(root, 9) ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Operation                     | Time Complexity                                |
+───────────────────────────────+────────────────────────────────────────────────+
| Search                        | O(h)                                           |
| Insert                        | O(h)                                           |
| Delete                        | O(h)                                           |
| Kth Smallest                  | O(h + k) with inorder                          |
| Validate                      | O(n)                                           |
| LCA in BST                    | O(h) - use BST property                        |
+───────────────────────────────+────────────────────────────────────────────────+

DELETE CASES:
1. Leaf node: Just remove
2. One child: Replace with child
3. Two children: Replace with inorder successor, then delete successor

================================================================================
*/

