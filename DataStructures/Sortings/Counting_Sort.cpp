// implementing counting sort algorithm

#include <iostream>
using namespace std;

void CountingSort(int arr[],int size)
{
	int count_arr[10] = {0}; //created array of size 10 with all values are zero
	int output_arr[size+1];
	for(int i=0;i<size;i++)
	{
		++count_arr[arr[i]];
	}
	for(int i=1;i<10;i++)
	{
		count_arr[i] = count_arr[i]+count_arr[i-1];
	}
	for(int i=0;i<size;i++)
	{
		output_arr[--count_arr[arr[i]]] = arr[i];
	}
	for(int i=0;i<size;i++)
	{
		arr[i] = output_arr[i];
	}
}

int main() {
	int size;
	cout << "Enter Size of array :" << endl;
	cin >> size;
	int arr[size];

	cout << "Enter " << size << " integers in any order:" << endl;
	for(int i=0;i<size;i++)
	{
		cin >> arr[i];
	}

	cout << "Before Sorting" << endl;
	for(int i=0;i<size;i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	CountingSort(arr, size); //Counting Sort Called Here

	cout << "After Sorting :" << endl;
	for(int i=0;i<size;i++)
	{
		cout << arr[i] <<" ";
	}

	return 0;
}
