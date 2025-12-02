#include <iostream>
using namespace std;

class Node
{
public:
	int key;
	int data;
	Node* next;
	Node* previous;
	Node()
	{
		key = 0;
		data = 0;
		next = NULL;
		previous = NULL;
	}
	Node(int k, int d)
	{
		key = k;
		data = d;
		next = NULL;
		previous = NULL;
	}
};

class DoublyLinkedList
{
public:
	Node* head;
	DoublyLinkedList()
	{
		head = NULL;

	}
	DoublyLinkedList(Node *n)
	{
		head = n;
	}

	//1. Check if node exists using key value
	Node* nodeExist(int k)
	{
		Node* temp = NULL;
		Node* ptr = head; //local pointer created
		while(ptr!=NULL)
		{
			if(ptr->key==k)
			{
				temp = ptr;
			}
			ptr = ptr->next;  //traversing through the whole linked list
		}
		return temp;
	}

	//2. Append a node to the list
	void appendNode(Node *n)
	{
		if(nodeExist(n->key)!=NULL)
		{
			cout << "Node already exist with key value :" << n->key << ". Append another node with different key value" << endl;
		}
		else
		{
			if(head==NULL)
			{
				head = n;
				cout << "Node Appended as head Node" << endl;
			}
			else
			{
				Node* ptr = head;
				while(ptr->next!=NULL)
				{
					ptr = ptr->next;
				}                       //just accessing the last head address throughout the linked list
				ptr->next = n;
				n->previous = ptr;
				cout << "Node Appended" << endl; //node appended to that address
			}
		}
	}

	//3. Prepend Node - Attach node at the start
	void prependNode(Node *n)
	{
		if(nodeExist(n->key)!=NULL)
		{
			cout << "Node already exist with key value :" << n->key << ". Append another node with different key value" << endl;
		}
		else
		{
			if(head==NULL)
			{
				head = n;
				cout << "Node prepended as head Node" << endl;
			}
			else
			{
				head->previous = n;
				n->next = head; //assigning n storing head address to that newly added node

				head = n;
				cout << "Node prepended" << endl;
			}
			head->previous = n;
			n->next = head; //assigning n storing head address to that newly added node
			head = n;
		}
	}

	//4. Insert a node after a particular node in the list
	void insertNodeAfter(int k,Node *n)
	{
		Node* ptr = nodeExist(k);
		if(ptr==NULL)
		{
			cout << "No node exist with key value :" << k << endl;
		}
		else
		{
			if(nodeExist(n->key)!=NULL)
			{
				cout << "Node already exist with key value :" << n->key << ". Append another node with different key value" << endl;
			}
			else
			{
				Node *nextNode = ptr->next;
				//inserting at the end
				if(nextNode==NULL)
				{
					ptr->next = n;
					n->previous = ptr;
					cout << "Node Inserted at the END" << endl;
				}
				//inserting in between
				else
				{
					n->next = nextNode;
					nextNode->previous = n;
					n->previous= ptr;
					ptr->next = n;

					cout << "Node Inserted in between" << endl;
				}
			}
		}
	}

	/*
	// delete a node from given position in a doubly linked list.
	Node* deleteNode(Node *head_ref, int x)
    {
      if(head_ref==nullptr) return head_ref;
      
      if(x==1){
          head_ref = head_ref->next;
          head_ref->prev = nullptr;
          return head_ref;
      }
      else{
            Node *t =head_ref;
            for(int i = 0;i < x-1;i++)
                t=t->next;
            t->prev->next=t->next;
            if(t->next) 
                t->next->prev=t->prev;
            delete t;
      }
      return head_ref;
		}
	*/

	//5. Delete node by unique key
	void deleteNodeByKey(int k)
	{
		Node* ptr = nodeExist(k);
		if(ptr==NULL)
		{
			cout << "No node exist with key value" << k << endl;
		}
		else
		{
			if(head==NULL)
			{
				cout << "Doubly Linked list is already empty. Can't delete any Node" << endl;
			}
			else if(head!=NULL)
			{
				if(head->key==k)
				{
				head = head->next; //now head will point to next node instead of key node
				cout << "NODE UNLINKED with key value:" << k << endl;
				}
				else
				{
					Node *nextNode = ptr->next;
					Node *prevNode = ptr->previous;
					//deleting at thr node
					if(nextNode==NULL)
					{
						prevNode->next = NULL;
						cout << "Node deleted at the end" << endl;
					}
					//deleting in between
					else
					{
						prevNode->next=NULL;
						nextNode->previous = prevNode;
						cout << "Node Deleted in Between" << endl;
					}
				}
			}
		}
	}
	//6. update node
	void updateNodeByKey(int k,int d)
	{
		Node* ptr = nodeExist(k);
		if(ptr!=NULL)
		{
			ptr->data = d;
			cout << "Node Data Updated Successfully" << endl;
		}
		else
		{
			cout << "No node exist with key value" << k << endl;
		}
	}

	//7. printing
	void printList()
	{
		if(head==NULL)
		{
			cout << "No Nodes in Doubly Linked List" << endl;
		}
		else
		{
			cout << endl << "Doubly Linked List Values :";
			Node* temp = head;
			while(temp!=NULL)
			{
				cout << "(" << temp->key << ", " << temp->data << ") <--> ";
				temp = temp->next;
			}
		}
	}
};

int main() {
	DoublyLinkedList s;
	int option;
	int key1, k1, data1;
	do
	{
		cout << "\nwhat operation do you want to perform :" << endl;
		cout << "0. EXIT" << endl;
		cout << "1. appendNode()" << endl;
		cout << "2. prependNode()" << endl;
		cout << "3. insertNodeAfter()" << endl;
		cout << "4. deleteNodeByKey()" << endl;
		cout << "5. updateNodeByKey()" << endl;
		cout << "6. print()" << endl;
		cout << "7. Clear Screen" << endl << endl;

		cin >> option;
		Node* n1 = new Node();

		switch(option)
		{
		case 0:
			cout << "You decided to exit, Byee!" << endl;
			break;
		case 1:
			cout << "Append Node Operation \nEnter key & data to be appended " << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			s.appendNode(n1);
			break;
		case 2:
			cout << "Prepend Node Operation \nEnter key & data to be prepended " << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			s.prependNode(n1);
			break;
		case 3:
			cout << "Insert Node After Operation \nEnter key of existing Node after which you want to Insert this New node :" << endl;
			cin >> k1;
			cout << "Enter key and data of the New Node first:" << endl;
			cin >> key1;
			cin >> data1;
			n1->key = key1;
			n1->data = data1;
			s.insertNodeAfter(k1,n1);
			break;
		case 4:
			cout << "Delete Node by Key Operation - \nEnter key of the Node to be deleted:" << endl;
			cin >> k1;
			s.deleteNodeByKey(k1);
			break;
		case 5:
			cout << "Update Node by Key Operation - \nEnter key and new data to be updated" << endl;
			cin >> key1;
			cin >> data1;
			s.updateNodeByKey(key1, data1);
			break;
		case 6:
			s.printList();
			break;
		case 7:
			system("cls");
			break;
		default:
			cout << "Enter proper option number!" << endl;
		}

	}while(option!=0);
	return 0;
}
