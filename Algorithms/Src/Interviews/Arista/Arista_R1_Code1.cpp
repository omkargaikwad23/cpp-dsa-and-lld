#include <bits/stdc++.h>
using namespace std;

/*

        1 (i==0, i<1)
    2    3 (i =0, i<2)

    4    


1,2,3
*/

struct Node{
    int data;
    Node* left = nullptr, *right = nullptr;
    Node(int _data){
        data = _data;
    }
};

class Tree{
    // Tree* root;
public:
    void printLeftView(Node* root){
        if(root == nullptr) return;

        queue<Node*> q;
        q.push(root);

        vector<int> leftView; 

        while(!q.empty()){
            int n = q.size();
            for(int i=0; i<n; i++){
                Node* curr = q.front();
                q.pop();
                
                if(i==0){
                    leftView.push_back(curr->data);
                }
                if(curr->left){
                    q.push(curr->left);
                }
                if(curr->right){
                    q.push(curr->right);
                }
            }
        }

        for(auto& itr : leftView){
            cout << itr << " ";
        }
    }   

    void printTree(Node* root){
        if(root == nullptr) return;
        cout << root->data << ". ";
        printTree(root->left);
        printTree(root->right);
    }
};

/*
        1
        2   3
            /
        4 6
            \
        5   7
            \8

    1, 2, 4, 5, 8
*/

int main()
{
    Node* root  = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->left->left = new Node(5);
    root->right->left = new Node(6);
    root->right->left->right = new Node(7);
    root->right->left->right->right = new Node(8);

    // cout << root->data << endl;

    // cout << root->left->data << endl;


    Tree t;
    // t.printTree(root);

    t.printLeftView(root);
    return 0;
}