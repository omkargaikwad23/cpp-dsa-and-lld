#include <iostream>
using namespace std;
void bubbleSort(int a[])
{
	for(int i=0;i<5;i++)
	{
		for(int j=0; j<(5-i-1); j++)
		{
			if(a[j] > a[j+1])
			{
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}

int main() {
	int myarr[5];
	cout << "Enter the 5 random numbers to sort:" << endl;
	for(int i=0;i<5;i++)
	{
		cin >> myarr[i];
	}

	cout << "BEFORE SORTING :" << endl;
	for(int i=0;i<5;i++)
	{
		cout << myarr[i] << " ";
	}

	bubbleSort(myarr);

	cout << endl;

	cout << "After SORTING : " << endl;
	for(int i=0;i<5;i++)
	{
		cout << myarr[i] << " ";
	}
	return 0;
}
