#include <iostream>
using namespace std;

class Node
{
public:
	int key;
	int data;
	Node* next;
	Node()
	{
		key = 0;
		data = 0;
		next = NULL;
	}
	Node(int k, int d)
	{
		key = k;
		data = d;
		next = NULL;
	}
};

class CircularLinkedList{
public:
	Node* head;
	CircularLinkedList()
	{
		head = NULL;
	}

	//1. this method check if node exist or not using key value
	Node* nodeExist(int k)  //return pointer so "Node*"
	{
		Node* temp = NULL;
		Node* ptr = head; //local pointer created
		if(ptr==NULL)
		{
			return temp;
		}
		else
		{
			do
			{
				if(ptr->key==k)
				{
					temp = ptr;  //head address will be stored in temp
				}
				ptr = ptr->next;

			}while(ptr!=head); //execute this loop until ptr and node are not equal
		}
		return temp; //will return the address of node whose key value matches with passed key
	}

	//2. Append a node to the list
	void appendNode(Node *new_node)
	{
		if(nodeExist(new_node->key)!=NULL)
		{
			cout << "Node already exist with key value :" << new_node->key << ". Append another node with different key value" << endl;
		}
		else
		{
			if(head==NULL)
			{
				head = new_node;
				new_node->next = head;
				cout << "Node Appended at first head position" << endl;
			}
			else
			{
				Node* ptr = head;
				while(ptr->next!=head)
				{
					ptr = ptr->next;
				}                       //just accessing the last head address throughout the linked list until head comes
				ptr->next = new_node;
				new_node->next = head;
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
				n->next = head; //single node pointing to itself
				cout << "Node prepended at first position" << endl;
			}else
			{
				Node* ptr = head;
				while(ptr->next!=head)
				{
					ptr = ptr->next; //ptr will store the address of last node in list
				}
				ptr->next = n;  //last node will point to the prepended node (before list)
				n->next = head; //prepended node will point to the first node of the list
				head=n;         //now head will point to the newly prepended node
				cout << "Node Prepended" << endl;
			}
		}
	}

	//4. Insert a node after a particular node in the list
	void insertNodeAfter(int k,Node *n)
	{
		Node* ptr = nodeExist(k); //ptr will point the node whose key is k after which we have to insert new node
		if(ptr==NULL)
		{
			cout << "No node exist with key value :" << k << endl;
		} //if passed key doesn't exist with
		else
		{
			if(nodeExist(n->key)!=NULL) //check passed node already exist or not
			{
				cout << "Node already exist with key value :" << n->key << ". Append another node with different key value" << endl;

			}
			else
			{
				if(ptr->next==head) //if key is of last node of the list
				{
					ptr->next = n;
					n->next = head;  //point newly inserted node at end towards first node
					cout << "Node inserted at the end" << endl;
				}
				else
				{
					n->next = ptr->next; //inserted node will point to the next of ptr
					ptr->next = n; //inserted node after passed key(ptr address)
					cout << "Node inserted in between" << endl;
				}
			}
		}
	}

	//5. Delete node by unique key
	void deleteNodeByKey(int k)
	{
		Node* ptr = nodeExist(k);
		if(ptr==NULL)
		{
			cout << "No node exist with key value of" << k << endl;
		}
		else
		{   //25:00
			if(ptr==head)
			{
				if(head->next==NULL)
				{
					head = NULL;
					cout << "Head node Unlinked...List Empty" << endl;
				}
				else
				{
					Node* ptr1 = head;
					while(ptr->next!=head)
					{
						ptr1 = ptr1->next;
					}
					ptr1->next = head->next;
					head = head->next;
					cout << "Node UNLINKED with key value " << k << endl;
				}
			}
			else
			{
				Node* temp = NULL;
				Node* prevptr = head;
				Node* currentptr = head->next;
				while(currentptr!=NULL)
				{
					if(currentptr->key==k)
					{
						temp = currentptr;
						currentptr = NULL;
					}
					else
					{
						prevptr = prevptr->next;
						currentptr = currentptr->next;
					}
				}
				prevptr->next = temp->next;
				cout << "Node UNLINKED with key value :" << k << endl;
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
			cout << "Node Data updated successfully" << endl;
		}
		else
		{
			cout << "Node doesn't exist with key value :" << k << endl;
		}
	}

	//7. Printing the entire linked list
	void printList()
	{
		if(head==NULL)
		{
			cout << "There are no nodes in circular Linked list";
		}
		else
		{
			cout << "Head address :" << head << endl;
			cout << "Circular Linked List values :" << endl;
			Node* temp = head;
			do
			{
				cout << "(" << temp->key << ", " << temp->data << ", " << temp->next << ") -->";
				temp = temp->next;
			}while(temp!=head);
		}
	}
};

int main()
{
	CircularLinkedList s;
	int option;
	int key1, k1, data1;
	do
	{
		cout << "\nwhat operation do you want to perform :" << endl;
		cout << "0. EXIT" << endl;
		cout << "1. appendNode()" << endl;
		cout << "2.prependNode()" << endl;
		cout << "3.insertNodeAfter()" << endl;
		cout << "4. deleteNodeByKey()" << endl;
		cout << "5. updateNodeByKey()" << endl;
		cout << "6. print()" << endl;
		cout << "7. Clear Screen" << endl;

		cin >> option;
		Node* n1 = new Node();

		switch(option)
		{
		case 0:
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

