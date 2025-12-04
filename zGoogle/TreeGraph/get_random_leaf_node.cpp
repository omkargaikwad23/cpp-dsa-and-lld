/*
================================================================================
            GET RANDOM NODE / RANDOM LEAF NODE - O(1) Operations
================================================================================

PROBLEM:
Implement a tree with these O(1) operations:
1. addNode(parent, val) - Add a child node to given parent
2. getRandomNode()      - Return any node with equal probability
3. getRandomLeafNode()  - Return any leaf node with equal probability

KEY TRICKS:
- Use vector + map for O(1) random access by index
- Use "swap and pop" technique for O(1) removal from vector
- Track each leaf's index in vector for O(1) lookup during removal

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val;
    vector<TreeNode*> children;
    int leafIndex = -1;  // Index in leaves vector (-1 if not a leaf)
    
    TreeNode(int v) : val(v) {}
};

class Tree {
private:
    TreeNode* root;
    vector<TreeNode*> allNodes;              // For O(1) random node
    vector<TreeNode*> leaves;                // For O(1) random leaf
    unordered_map<int, TreeNode*> nodeMap;   // For O(1) parent lookup
    
public:
    Tree(int rootVal) {
        root = new TreeNode(rootVal);
        
        // Root is initially a leaf
        root->leafIndex = 0;
        leaves.push_back(root);
        
        allNodes.push_back(root);
        nodeMap[rootVal] = root;
        
        srand(time(0));
    }
    
    // O(1) - Add child node to parent
    void addNode(int parentVal, int childVal) {
        TreeNode* parent = nodeMap[parentVal];
        TreeNode* child = new TreeNode(childVal);
        
        // Add to parent's children
        parent->children.push_back(child);
        
        // Track in our data structures
        allNodes.push_back(child);
        nodeMap[childVal] = child;
        
        // New node is always a leaf
        child->leafIndex = leaves.size();
        leaves.push_back(child);
        
        // If parent was a leaf, remove it from leaves (O(1) swap-and-pop)
        if (parent->leafIndex != -1) {
            removeFromLeaves(parent);
        }
    }
    
    // O(1) - Get random node with equal probability
    TreeNode* getRandomNode() {
        if (allNodes.empty()) return nullptr;
        return allNodes[rand() % allNodes.size()];
    }
    
    // O(1) - Get random leaf with equal probability
    TreeNode* getRandomLeaf() {
        if (leaves.empty()) return nullptr;
        return leaves[rand() % leaves.size()];
    }
    
    // Utility: Print tree info
    void printInfo() {
        cout << "Total nodes: " << allNodes.size() << "\n";
        cout << "Leaves: ";
        for (auto* leaf : leaves) cout << leaf->val << " ";
        cout << "\n";
    }

private:
    // O(1) removal using swap-and-pop technique
    void removeFromLeaves(TreeNode* node) {
        int idx = node->leafIndex;
        
        // Swap with last element
        TreeNode* lastLeaf = leaves.back();
        leaves[idx] = lastLeaf;
        lastLeaf->leafIndex = idx;
        
        // Pop the last element
        leaves.pop_back();
        node->leafIndex = -1;
    }
};


/*
================================================================================
                                    MAIN
================================================================================
*/

int main() {
    cout << "=== Random Node / Random Leaf O(1) ===\n\n";
    
    /*
    Build tree:
            1
           /|\
          2 3 4
            |
            5
            
    Leaves: 2, 4, 5
    */
    
    Tree tree(1);
    tree.addNode(1, 2);
    tree.addNode(1, 3);
    tree.addNode(1, 4);
    tree.addNode(3, 5);
    
    tree.printInfo();
    
    cout << "\nRandom samples:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Random node: " << tree.getRandomNode()->val;
        cout << ", Random leaf: " << tree.getRandomLeaf()->val << "\n";
    }
    
    return 0;
}


/*
================================================================================
                            COMPLEXITY ANALYSIS
================================================================================

┌─────────────────────┬──────────┬─────────────────────────────────────────────┐
│ Operation           │ Time     │ How                                         │
├─────────────────────┼──────────┼─────────────────────────────────────────────┤
│ addNode()           │ O(1)     │ Vector push_back, map insert                │
│ getRandomNode()     │ O(1)     │ Random index into vector                    │
│ getRandomLeaf()     │ O(1)     │ Random index into leaves vector             │
│ removeFromLeaves()  │ O(1)     │ Swap-and-pop (no shifting needed)           │
└─────────────────────┴──────────┴─────────────────────────────────────────────┘

Space: O(n) for storing all nodes

================================================================================
                            KEY TECHNIQUE: SWAP AND POP
================================================================================

To remove element at index i from vector in O(1):

    Before: [A, B, C, D, E]  (remove C at index 2)
                  ^
    Step 1: Swap C with last element E
            [A, B, E, D, C]
                  ^     ^
    Step 2: Pop last element
            [A, B, E, D]

This avoids O(n) shifting that normal erase() causes!

Requirement: Track each element's index (leafIndex in our TreeNode)

================================================================================
*/
