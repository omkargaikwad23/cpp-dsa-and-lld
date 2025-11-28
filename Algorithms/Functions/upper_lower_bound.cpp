/*
lower_bound → first element >= x  
upper_bound → first element > x

Input: 10 20 30 40 50
Output: lower_bound for element 30 at index 2

Input: 10 20 30 40 50
Output: lower_bound for element 35 at index 3

Input: 10 20 30 40 50
Output: lower_bound for element 55 at index 5 (Basically, 55 is not present, so it returns end() iterator)

Input: 10 20 30 30 30 40 50
Output: lower_bound for element 30 at index 2
*/

/*
Input : 10 20 30 30 40 50
Output : upper_bound for element 30 is at index 4

Input : 10 20 30 40 50
Output : upper_bound for element 45 is at index 4

Input : 10 20 30 40 50
Output : upper_bound for element 60 is at index 5
*/

// CPP program to illustrate
// std :: lower_bound
#include <bits/stdc++.h>
using namespace std;

// Driver code
int main()
{
	// Input vector
	vector<int> v{ 10, 20, 30, 30, 30, 40, 50 };

	// Print vector
	cout << "Vector contains :";
	for (unsigned int i = 0; i < v.size(); i++)
		cout << " " << v[i];
	cout << "\n";

	vector<int>::iterator low1, low2, low3;
	
	// std :: lower_bound
	low1 = lower_bound(v.begin(), v.end(), 30);
	low2 = lower_bound(v.begin(), v.end(), 35);
	low3 = lower_bound(v.begin(), v.end(), 55);

	// Printing the lower bounds
	cout
		<< "\nlower_bound for element 30 at position : "
		<< (low1 - v.begin());
	cout
		<< "\nlower_bound for element 35 at position : "
		<< (low2 - v.begin());
	cout
		<< "\nlower_bound for element 55 at position : "
		<< (low3 - v.begin());

	return 0;
}
