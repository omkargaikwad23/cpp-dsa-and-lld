//filo
#include <iostream>
#include <string>
using namespace std;

class Stack{
private:
	int top;
	int arr[5];
public:
	Stack()
	{
		top = -1;
		for(int i=0;i<5;i++)
		{
			arr[i] = 0;  //make all entries as 0 (stack values)
		}
	}

	bool isEmpty()
	{
		if(top==-1)
			return true;
		else
			return false;
	}
	bool isFull()
	{
		if(top==4)
			return true;
		else
			return false;
	}
	void push(int val)
	{
		if(isFull())
		{
			cout << "stack overflow" << endl;
		}
		else
		{
			top++;
			arr[top] = val;
		}
	}
	int pop()
	{
		if(isEmpty())
		{
			cout << "stack underflow !!" << endl;
			return true;
		}
		else
		{
			int popvalue = arr[top];
			arr[top] = 0;
			top--;
			return popvalue;
		}
	}

	int count()
	{
		return(top+1);
	}

	int peek(int pos)
	{
		if(isEmpty())
		{
			cout << "Stack underflow !!" << endl;
			return 0;
		}
		else
		{
			return arr[pos];
		}
	}

	void change(int pos, int val)
	{
		arr[pos] = val;
		cout << "value is changed at location " << pos << endl;
	}

	void display()
	{
		cout << "All values in the stack are :" << endl;
		for(int i=4;i>=0;i--)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}
};

int main() {
	Stack s1;
	int option,position,value;
	do{
		cout << "\nSelect following option number to perform a particular operation."<<endl;
		cout << "------------------------------------------" << endl;
		cout << "0. EXIT" << endl;
		cout << "1. Push()" << endl;
		cout << "2. Pop()" << endl;
		cout << "3. isEmpty()" << endl;
		cout << "4. isFull()" << endl;
		cout << "5. peek()" << endl;
		cout << "6. count()" << endl;
		cout << "7. change() " << endl;
		cout << "8. display()" << endl;
		cout << "9. Clear Screen" << endl;
		cout << "------------------------------------------" << endl;

		cin >> option;
		switch(option)
		{
		case 0:
			cout << "You have decided to exit. Bye!!" << endl;
			break;
		case 1:
			cout << "Enter an item to push in the stack" << endl;
			cin >> value;
			s1.push(value);
			cout << "Item is successfully pushed in the Stack :)" << endl;
			break;
		case 2:
			cout << "Pop Function Called = Poped value:" << s1.pop() << endl;
			break;
		case 3:
			if(s1.isEmpty())
				cout << "Stack is Empty." << endl;
			else
				cout << "Stack is not Empty." << endl;
			break;
		case 4:
			if(s1.isFull())
				cout << "Stack is full" << endl;
			else
				cout << "Stack is not full" << endl;
			break;
		case 5:
			cout << "Enter position of items you want to peak:" << endl;
			cin >> position;
			cout << "Peek Function Called = Value at position  "<< position << " is " << endl << s1.peek(position) << endl;
			break;
		case 6:
			cout << "Count Function Called = Number of Items in the Stack are :" << s1.count() << endl;
			break;
		case 7:
			cout << "Change Function Called = " ;
			cout << "Enter position of item you want to change:";
			cin >> position;
			cout << "Enter value of item you want to change :" << endl;
			cin >> value;
			s1.change(position,value);
			break;
		case 8:
			cout << "Display function is called." << endl;
			s1.display();
			break;
		case 9:
			system("cls");
			break;

		default:
			cout << "Enter Proper Option number" << endl;
	}

	}while(option!=0);

	return 0;
}
