#include <iostream>
using namespace std;


void ShellSort(int arr[],int size)
{
	for(int gap=size/2; gap>0; gap/=2){
		for(int j=gap; j<size; j+=1)
		{
			int temp = arr[j];
			int i = 0;
			for(i=j; i>=gap && arr[i-gap]>temp; i-=gap)
			{
				arr[i] = arr[i-gap];
			}
			arr[i] = temp;
		}

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

	ShellSort(arr, size); //Radix Sort Called Here

	cout << "After Sorting :" << endl;
	for(int i=0;i<size;i++)
	{
		cout << arr[i] <<" ";
	}

	return 0;
}
