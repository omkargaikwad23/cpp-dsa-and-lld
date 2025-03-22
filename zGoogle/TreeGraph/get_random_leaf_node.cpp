/*
Problem Restatement: You are tasked with implementing a tree data structure where you can add a node to a specified parent and retrieve a random node or a random leaf node from the tree, all in constant time O(1).
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class TreeNode {
    public:
    int val;
    vector<TreeNode*> children;
    bool isLeaf;

    TreeNode(int val) : val(val), isLeaf(true) {}
};

class Tree {
    TreeNode* root;
    unordered_map<int, TreeNode*> nodes;
    vector<TreeNode*> leaves;

    public:
    Tree(int rootVal) {
        root = new TreeNode(rootVal);
        nodes[rootVal] = root;
        leaves.push_back(root);
        srand(time(0)); // Seed for randomness
    }

    void addNode(TreeNode* parent, int val) {
        TreeNode* newNode = new TreeNode(val);
        nodes[val] = newNode;
        parent->children.push_back(newNode);

        if (parent->isLeaf) {
            parent->isLeaf = false;
            removeLeaf(parent);
        }
        leaves.push_back(newNode); // Add new node as leaf
    }

    TreeNode* getRandomNode() {
        int index = rand() % nodes.size();
        auto it = nodes.begin();
        advance(it, index);
        return it->second;
    }

    TreeNode* getRandomLeafNode() {
        int index = rand() % leaves.size();
        return leaves[index];
    }

    private:
    void removeLeaf(TreeNode* node) {
        auto it = find(leaves.begin(), leaves.end(), node);
        if (it != leaves.end()) {
            leaves.erase(it);
        }
    }
};

int main() {
    // Example usage
    Tree tree(1); // Create a tree with root value 1
    TreeNode* root = tree.getRandomNode(); // Get root as random node

    tree.addNode(root, 2);
    tree.addNode(root, 3);

    TreeNode* leaf = tree.getRandomLeafNode();
    cout << "Random Leaf Node Value: " << leaf->val << endl;

    TreeNode* randomNode = tree.getRandomNode();
    cout << "Random Node Value: " << randomNode->val << endl;

    return 0;
}