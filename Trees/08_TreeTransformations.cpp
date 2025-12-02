/*
================================================================================
                    TREE TRANSFORMATIONS
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
PROBLEM 1: Flatten Binary Tree to Linked List (LeetCode 114) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────────────────────────────
Flatten to right-skewed tree in preorder.
Time: O(n) | Space: O(1) with Morris
*/
void flatten(TreeNode* root) {
    TreeNode* curr = root;
    
    while (curr) {
        if (curr->left) {
            // Find rightmost node of left subtree
            TreeNode* pred = curr->left;
            while (pred->right) {
                pred = pred->right;
            }
            
            // Connect to right subtree
            pred->right = curr->right;
            curr->right = curr->left;
            curr->left = nullptr;
        }
        curr = curr->right;
    }
}


/*
PROBLEM 2: Invert Binary Tree (LeetCode 226) ⭐ CLASSIC
──────────────────────────────────────────────────────
Mirror the tree.
*/
TreeNode* invertTree(TreeNode* root) {
    if (!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}


/*
PROBLEM 3: Convert BST to Greater Tree (LeetCode 538)
─────────────────────────────────────────────────────
Each node's value = sum of all greater values + original.
Reverse inorder traversal.
*/
TreeNode* convertBST(TreeNode* root) {
    int sum = 0;
    
    function<void(TreeNode*)> reverseInorder = [&](TreeNode* node) {
        if (!node) return;
        reverseInorder(node->right);
        sum += node->val;
        node->val = sum;
        reverseInorder(node->left);
    };
    
    reverseInorder(root);
    return root;
}


/*
PROBLEM 4: Binary Tree to Linked List (Inorder)
───────────────────────────────────────────────
*/
TreeNode* treeToList(TreeNode* root) {
    TreeNode dummy(0);
    TreeNode* prev = &dummy;
    
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        prev->right = node;
        node->left = prev;
        prev = node;
        inorder(node->right);
    };
    
    inorder(root);
    
    if (dummy.right) dummy.right->left = nullptr;
    return dummy.right;
}


/*
PROBLEM 5: Populating Next Right Pointers (LeetCode 116) ⭐
──────────────────────────────────────────────────────────
Connect nodes at same level (perfect binary tree).
Time: O(n) | Space: O(1)
*/
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

Node* connect(Node* root) {
    if (!root) return nullptr;
    
    Node* leftmost = root;
    
    while (leftmost->left) {
        Node* curr = leftmost;
        
        while (curr) {
            curr->left->next = curr->right;
            if (curr->next) {
                curr->right->next = curr->next->left;
            }
            curr = curr->next;
        }
        
        leftmost = leftmost->left;
    }
    
    return root;
}

// For any binary tree (LeetCode 117)
Node* connectAny(Node* root) {
    Node* curr = root;
    
    while (curr) {
        Node dummy(0);
        Node* prev = &dummy;
        
        while (curr) {
            if (curr->left) {
                prev->next = curr->left;
                prev = prev->next;
            }
            if (curr->right) {
                prev->next = curr->right;
                prev = prev->next;
            }
            curr = curr->next;
        }
        
        curr = dummy.next;
    }
    
    return root;
}


/*
PROBLEM 6: Balance BST (LeetCode 1382)
─────────────────────────────────────
Convert to sorted array, rebuild balanced.
*/
TreeNode* balanceBST(TreeNode* root) {
    vector<int> sorted;
    
    function<void(TreeNode*)> inorder = [&](TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        sorted.push_back(node->val);
        inorder(node->right);
    };
    
    inorder(root);
    
    function<TreeNode*(int, int)> build = [&](int l, int r) -> TreeNode* {
        if (l > r) return nullptr;
        int mid = l + (r - l) / 2;
        TreeNode* node = new TreeNode(sorted[mid]);
        node->left = build(l, mid - 1);
        node->right = build(mid + 1, r);
        return node;
    };
    
    return build(0, sorted.size() - 1);
}


/*
PROBLEM 7: Delete Leaves With Given Value (LeetCode 1325)
─────────────────────────────────────────────────────────
Recursively delete leaves with target value.
*/
TreeNode* removeLeafNodes(TreeNode* root, int target) {
    if (!root) return nullptr;
    
    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);
    
    if (!root->left && !root->right && root->val == target) {
        return nullptr;
    }
    
    return root;
}


/*
PROBLEM 8: Linked List in Binary Tree (LeetCode 1367)
─────────────────────────────────────────────────────
Check if linked list is a downward path in tree.
*/
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool isSubPath(ListNode* head, TreeNode* root) {
    function<bool(ListNode*, TreeNode*)> match = [&](ListNode* l, TreeNode* t) -> bool {
        if (!l) return true;
        if (!t) return false;
        if (l->val != t->val) return false;
        return match(l->next, t->left) || match(l->next, t->right);
    };
    
    if (!root) return false;
    return match(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
}


int main() {
    cout << "=== Tree Transformations ===\n\n";
    
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->right = new TreeNode(6);
    
    flatten(root);
    cout << "Flattened (preorder): ";
    while (root) {
        cout << root->val << " ";
        root = root->right;
    }
    cout << "\n";
    
    return 0;
}

/*
SUMMARY:
+───────────────────────────+────────────────────────────────────────+
| Transformation            | Technique                              |
+───────────────────────────+────────────────────────────────────────+
| Flatten to List           | Morris-like: connect left to right     |
| Invert                    | Swap children recursively              |
| BST to Greater Tree       | Reverse inorder with running sum       |
| Next Right Pointers       | Level-by-level using next pointers     |
| Balance BST               | Inorder to array, rebuild balanced     |
+───────────────────────────+────────────────────────────────────────+
*/

