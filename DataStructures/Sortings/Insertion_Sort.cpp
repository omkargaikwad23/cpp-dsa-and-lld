#include <bits/stdc++.h>
using namespace std;

void insertionSort(int arr[], int length);

int main()
{
	int n;
	cout << "Enter size of array: ";
	cin >> n;
	int array[n];
	cout << "Enter array elements: " << "\n";
	for(int i=0; i<n; i++){
		cin >> array[i];
	}
	cout << "\n...................\n" << endl;

	insertionSort(array, n);
	cout << "\nSorted Array: ";
	
	for(int i=0; i<n; i++){
		cout << array[i] << " ";
	}
	return 0;
}

void insertionSort(int arr[], int length)
{
	int i, j, key;
	for (i = 1; i < length; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;

		cout << "key: " << key << endl;
		for(int itr=0; itr<length; itr++){
			cout << arr[itr] << " ";
		}
		cout << endl;
	}
}

