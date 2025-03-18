/*
A binary tree is given, return all the leaf node of the binary tree with the maximum value from root to leaf node in the path.
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void findMaxLeafNodes(TreeNode* root, int maxSoFar, vector<int>& result) {
    if (!root) return;
    
    maxSoFar = max(maxSoFar, root->val);
    
    // If it's a leaf node, add to result
    if (!root->left && !root->right) {
        result.push_back(maxSoFar);
        return;
    }
    
    findMaxLeafNodes(root->left, maxSoFar, result);
    findMaxLeafNodes(root->right, maxSoFar, result);
}

vector<int> getMaxLeafNodes(TreeNode* root) {
    vector<int> result;
    findMaxLeafNodes(root, INT_MIN, result);
    return result;
}

// Helper function to create a simple binary tree for testing
TreeNode* createSampleTree() {
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(8);
    root->right = new TreeNode(15);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(9);
    root->right->left = new TreeNode(12);
    root->right->right = new TreeNode(20);
    return root;
}

int main() {
    TreeNode* root = createSampleTree();
    vector<int> result = getMaxLeafNodes(root);
    
    cout << "Leaf nodes with maximum value in their paths: ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;
    return 0;
}
