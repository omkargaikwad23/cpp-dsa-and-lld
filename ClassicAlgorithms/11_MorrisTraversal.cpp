/*
================================================================================
                    MORRIS TRAVERSAL (Threaded Binary Tree)
================================================================================

PROBLEM: Traverse binary tree without stack or recursion.

KEY INSIGHT: Use the right pointers of leaf nodes (which are null) to
             create temporary links back to ancestors.

ALGORITHM (Inorder):
1. If no left child: visit node, go right
2. If has left child:
   - Find inorder predecessor (rightmost in left subtree)
   - If predecessor's right is null: create thread, go left
   - If predecessor's right points to current: remove thread, visit, go right

TIME:  O(n)
SPACE: O(1) - no recursion/stack!

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
// MORRIS INORDER TRAVERSAL
// ═══════════════════════════════════════════════════════════════════════════

vector<int> morrisInorder(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            // No left child: visit and go right
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            // Find inorder predecessor
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                // Create thread: predecessor points to current
                pred->right = curr;
                curr = curr->left;
            } else {
                // Thread exists: we've returned, remove it
                pred->right = nullptr;
                result.push_back(curr->val);  // Visit current
                curr = curr->right;
            }
        }
    }
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// MORRIS PREORDER TRAVERSAL
// ═══════════════════════════════════════════════════════════════════════════

vector<int> morrisPreorder(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            result.push_back(curr->val);  // Visit
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                result.push_back(curr->val);  // Visit BEFORE going left
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
// RECOVER BST (LC 99) - Using Morris to find swapped nodes
// ═══════════════════════════════════════════════════════════════════════════

void recoverTree(TreeNode* root) {
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    TreeNode* prev = nullptr;
    TreeNode* curr = root;
    
    while (curr) {
        if (!curr->left) {
            // Check for violation
            if (prev && prev->val > curr->val) {
                if (!first) {
                    first = prev;
                    second = curr;
                } else {
                    second = curr;
                }
            }
            prev = curr;
            curr = curr->right;
        } else {
            TreeNode* pred = curr->left;
            while (pred->right && pred->right != curr) {
                pred = pred->right;
            }
            
            if (!pred->right) {
                pred->right = curr;
                curr = curr->left;
            } else {
                pred->right = nullptr;
                
                // Check for violation
                if (prev && prev->val > curr->val) {
                    if (!first) {
                        first = prev;
                        second = curr;
                    } else {
                        second = curr;
                    }
                }
                prev = curr;
                curr = curr->right;
            }
        }
    }
    
    // Swap the two nodes
    if (first && second) {
        swap(first->val, second->val);
    }
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Build tree:
    //       4
    //      / \
    //     2   6
    //    / \ / \
    //   1  3 5  7
    
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);
    
    cout << "Tree:\n";
    cout << "       4\n";
    cout << "      / \\\n";
    cout << "     2   6\n";
    cout << "    / \\ / \\\n";
    cout << "   1  3 5  7\n\n";
    
    cout << "Morris Inorder:  ";
    for (int x : morrisInorder(root)) cout << x << " ";
    cout << "\n";
    
    cout << "Morris Preorder: ";
    for (int x : morrisPreorder(root)) cout << x << " ";
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                         HOW MORRIS WORKS (Visual)
================================================================================

Tree:       Step 1: Create thread    Step 2: Return via thread
    4           4                        4
   / \         / \                      / \
  2   6       2   6                    2   6
 / \         / \                      / \
1   3       1---3 (thread to 2)      1   3 (thread removed)
            ↑                             visited: 1, 2

The temporary threads allow us to return to ancestors without using stack.

WHY O(n) TIME?
- Each edge is traversed at most twice (create + remove thread)
- Total edges = n-1, so O(n) overall

WHEN TO USE:
- When O(1) space is required
- Interview question specifically asks for constant space
- Memory-constrained systems

RELATED PROBLEMS:
- LC 94: Binary Tree Inorder Traversal
- LC 144: Binary Tree Preorder Traversal
- LC 99: Recover Binary Search Tree

================================================================================
*/

