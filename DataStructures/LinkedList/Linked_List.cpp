#include <iostream>
using namespace std;

class Node
{
public:
  int data;
  Node *next;
  Node(){}
  Node(int data){
    this->data = data;
    this->next = nullptr;
  }
};

class LinkedList
{
  Node *head;
public:
  LinkedList()
  {
    head = nullptr;
  }
  void printList();
  void appendNode(int);
  void prependNode(int);
  int nodeAtIndex(int);
  void insertAtIndex(int , int );
  void removeAtIndex(int);
  void reverseList();

};

void LinkedList::printList()
{
  Node *itr = head;
  while (itr)
  {
    cout << " ->" << itr->data;
    itr = itr->next;
  }
  cout << endl;
  return;
}

void LinkedList::appendNode(int data)
{
  Node *newNode = new Node(data);
  newNode->data = data;
  if (head == nullptr)
  {
    newNode->next = nullptr;
    head = newNode;
  }
  else
  {
    Node *itr = head;
    while (itr->next != nullptr)
    {
      itr = itr->next;
    }
    itr->next = newNode;
    newNode->next = nullptr;
  }
  cout << "Node appended!" << endl;
}

void LinkedList::prependNode(int data)
{
  Node *newNode = new Node();
  newNode->data = data;
  newNode->next = head;
  head = newNode;
  cout << "Node prepended!" << endl;
}

int LinkedList::nodeAtIndex(int index){
  Node* itr = head;
  int counter = 0;
  while(counter!=index){
    counter++;
    itr = itr->next;
  }
  return itr->data;
}

void LinkedList::insertAtIndex(int data, int index){
  if(index==0) {this->prependNode(data); return;}
  
  Node* newNode = new Node();
  newNode->data = data;
  Node* itr = head;
  int counter = 1;
  while(counter!=index){
    counter++;
    itr = itr->next;
  }
  Node* nextNode = itr->next;
  itr->next = newNode;
  newNode->next = nextNode;
  cout << "Node inserted!" << endl;
  return;
}

void LinkedList::removeAtIndex(int index){
  Node* itr = head;
  Node* prev;
  
  if(index==0){
    head = itr->next;
  }
  else{
    int counter = 1;
    while(counter!=index){
      prev = itr;
      itr = itr->next;
      counter++;
    }
    prev = itr->next;
  }
  cout << "Node deleted!" << endl;
}

void LinkedList::reverseList(){
  Node* itr = head;
  Node* nextNode = nullptr;
  Node* prevNode = nullptr;
  while(itr!=nullptr){
    nextNode = itr->next;
    itr->next = prevNode;
    prevNode = itr;
    itr = nextNode;
  }
  head = prevNode;
  this->printList();
}

int main()
{
  LinkedList ll;
  int data, index, option;

  do
  {
    cout << "\nSelect :\n"
            "0. EXIT\n"
            "1. printList()\n"
            "2. appendNode()\n"
            "3. prependNode()\n"
            "4. nodeAtIndex()\n"
            "5. insertAtIndex()\n"
            "6. removeAtIndex()\n"
            "7. reverseList()\n";

    cin >> option;

    switch (option)
    {
    case 0:
      break;
    case 1:
    {
      cout << "List is: " << endl;
      ll.printList();
      break;
    }
    case 2:
    {
      cout << "Enter data: ";
      cin >> data;
      ll.appendNode(data);
      break;
    }
    case 3:
    {
      cout << "Enter data: ";
      cin >> data;
      ll.prependNode(data);
      break;
    }
    case 4:
    {
      cout << "Enter index: ";
      cin >> index;
      int nodeVal = ll.nodeAtIndex(index);
      cout << "Node at given index: " << nodeVal << endl;
      break; 
    }
    case 5:
    {
      cout << "Enter data: ";
      cin >> data;
      cout << "Enter index: ";
      cin >> index;
      ll.insertAtIndex(data, index);
      break;
    }
    case 6:
    {
      cout << "Enter index: ";
      cin >> index;
      ll.removeAtIndex(index);
      break;
    }
    case 7:
    {
      cout << "Revered list: " << endl;
      ll.reverseList();
      break;
    }
    }
  } while (option != 0);

  return 0;
}