#include <iostream>
using namespace std;

/*
Quick Sort Algorithm (inplace sorting)
Best			Average				Worst
Ω(nlog(n))     Θ(nlog(n))  		   O(n^2)
APPLICATIONS: used when there is space constrain

Step 1 − Make any element as pivot
Step 2 − Partition the array on the basis of pivot
Step 3 − Apply quick sort on left partition recursively
Step 4 − Apply quick sort on right partition recursively
*/

int Partition(int arr[], int s, int e)
{
	int pivot = arr[e];     // pick pivot as last element
	int pIndex = s;         // partition index
	for(int i=s; i<e; i++){
		if(arr[i] < pivot)
		{
			int temp = arr[i];
			arr[i] = arr[pIndex];
			arr[pIndex] = temp;
			pIndex++;
		}
	}
	int temp = arr[e];
	arr[e] = arr[pIndex];
	arr[pIndex] = temp;

	return pIndex;
}

void QuickSort(int arr[], int s, int e) //start index, end index
{
	if(s<e)
	{
		int p = Partition(arr,s,e);
		QuickSort(arr,s,(p-1)); //recursive QS call for left sort
		QuickSort(arr,(p+1),e); //recursive QS call for right sort
	}
}

int main() {
	int size = 0;
	cout << "Enter Size of array: ";
	cin >> size;
	int myArray[size];

	cout << "Enter " << size << " integers in any order:" << endl;
	for(int i=0;i<size;i++)
	{
		cin >> myArray[i];
	}

	QuickSort(myArray,0,(size-1));

	cout << "After Sorting :" << endl; //QuickSort is called
	for(int i=0;i<size;i++)
	{
		cout << myArray[i] <<" ";
	}
	return 0;
}
