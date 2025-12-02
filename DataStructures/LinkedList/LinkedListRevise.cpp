#include <bits/stdc++.h>
using namespace std;

class Node{
    friend class LinkedList;
public:
    int data;
    Node* next;
    Node(){}
    
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

class LinkedList{
    Node* head;
public:
    LinkedList(){
        head = nullptr;
    }

    void appendNode(int data){
        Node* newNode = new Node(data);
        if (head == nullptr){
            head = newNode;
        } else {
            Node* itr = head;
            while(itr->next){
                itr = itr->next;
            }
            itr->next = newNode;
        }
    }

    void prependNode(int data){
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    int getLength(){
        Node* itr = head;
        int length = 0;
        while(itr){
            length++;
            itr = itr->next;
        }
        return length;
    }

    void insertNode(int data, int loc){
        Node* newNode = new Node(data);
        if(loc == 0){
            prependNode(data);
        } else if(loc == getLength()){
            appendNode(data);
        } else {
            Node* itr = head;
            int reach = 0;
            while(++reach != loc){
                itr = itr->next;
            }
            cout << itr->data << endl;
            newNode->next = itr->next;
            itr->next = newNode;
        }
        this->printList();
    }

    void printList(){
        Node* itr = head;
        while(itr){
            cout << itr->data << " ";
            itr = itr->next;
        }
        cout << "\n";
    }
};

int main(){
    LinkedList ls;

    do {
        cout << "\n1) Append Node\n"
                "2) Prepend Node\n"
                "3) Print list\n"
                "4) Insert Node\n"
                << endl;
        cout << "\nEnter choice: ";
        int choice, data;
        cin >> choice;
        
        switch (choice)
        {
            case 1:{
                cout << "\nEnter no of nodes to insert: ";
                int N; cin >> N;
                cout << "\nEnter node values: ";
                for(int i=0; i<N; i++){
                    cin >> data;
                    ls.appendNode(data);
                }
                break;
            }
            case 2:{
                cin >> data;
                ls.prependNode(data);
                break;
            }
            case 3:{
                ls.printList();
                break;
            }
            case 4:{
                int loc; 
                cout << "Enter location to insert: ";
                cin >> loc;
                cout << "Enter data to insert: ";
                cin >> data;
                ls.insertNode(data, loc);
                break;
            }
            default:
                break;
        }
    } while (true);
}