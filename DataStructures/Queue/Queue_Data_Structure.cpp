//fifo
/*
        _ _ _ _ _
 <--out _|_|_|_|_ in<--

 */
#include <iostream>
#include <string>
using namespace std;

class Queue{
private:
	int arr[5];
	int rear;
	int front;

public:
	Queue()  //creating empty queue
	{
		front = -1;
		rear = -1;
		for(int i=0;i<5;i++)
		{
			arr[i] = 0;
		}
	}

	bool isEmpty()
	{
		if(front==-1 && rear==-1)
			return true;
		else
			return false;
	}
	bool isFull()
	{
		if(rear == 4)
			return true;
		else
			return false;
	}

	void enqueue(int val)//adding element to queue
	{
		if(isFull())
		{
			cout << "Queue is Full!" << endl;
			return;
		}
		else if(isEmpty())
		{
			rear = 0;
			front = 0;
			arr[rear] = val;
		}
		else
		{
			rear++;
			arr[rear] = val;
		}
	}

	int dequeue()
	{
		int x;
		if(isEmpty())
		{
			cout << "Queue is Empty!!" << endl;
			return 0;
		}
		else if(front == rear)
		{
			x = arr[front];
			arr[front] = 0;
			rear = -1;
			front = -1;
			return x;
		}
		else
		{
			x = arr[front];
			arr[front] = 0;
			front++; //front will goes on increasing from left to right
			return x;
		}
	}

	int count()
	{
		return (rear-front+1);
	}
	
	void display()
	{
	    cout << "All values in the Queue are" << endl;
		for(int i=0;i<5;i++)
		{
			cout << arr[i] << " ";
		}
	}
};

int main() {
	Queue q1;
	int option, value;
	do
	{
		cout << "\nSelect option number to perform perticular operation." << endl;
		cout << "------------------------------------------" << endl;
		cout << "0. press 0 to EXIT" << endl;
		cout << "1. Enqueue()" << endl;
		cout << "2. Dequeue()" << endl;
		cout << "3. isEmpty()" << endl;
		cout << "4. isFull()" << endl;
		cout << "5. count()" << endl;
		cout << "6. display()" << endl;
		cout << "7. Clear Screen" << endl;
		cout << "------------------------------------------\n" << endl;

		cin >> option;
		switch(option){
			case 0:
				cout << "You have decided to exit. Bye!!" << endl;
				break;
			case 1:
				cout << "Enter element which you want to add in Queue" << endl;
				cin >> value;
				q1.enqueue(value);
				break;
			case 2:
				cout << "You have selected to remove item from Queue." << endl;
				cout << "Dequeued Value :" << q1.dequeue() << endl;
				break;
			case 3:
				if(q1.isEmpty())
					cout << "Queue is Empty!!" << endl;
				else
					cout << "Queue is not Full" << endl;
				break;
			case 4:
				if(q1.isFull())
					cout << "Queue is Full!!" << endl;
				else
					cout << "Queue is not Full!!" << endl;
				break;
			case 5:
				cout << "Count Operation. \nTotal number of items in Queue :" << q1.count() << endl;
				break;
			case 6:
				cout << "Display Function Called." << endl;
				q1.display();
				break;
			case 7:
				system("cls");
				break;
			default:
				cout << "You have entered wrong option" << endl;
		}
	}while(option!=0);
	return 0;
}
