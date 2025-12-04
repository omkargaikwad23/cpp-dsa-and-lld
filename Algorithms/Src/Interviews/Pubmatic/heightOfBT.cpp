#include <bits/stdc++.h>
using namespace std;

/*
Time: O(N) : N is number of nodes
Space: O(h) : height of binary tree
*/

class Node{
public:
    int val;
    Node* left, *right;
    Node(int _val){
        val = _val;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree {
public:
    void insertNode(int data, Node* treeRoot){

    }
    int findHeightOfTree(Node* root){
        if(!root) 
            return 0;

        int lh = findHeightOfTree(root->left);
        int rh = findHeightOfTree(root->right);

        return 1 + max(lh, rh);
    }
};

int main(){
    
}