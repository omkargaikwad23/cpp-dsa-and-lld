//binary Search
#include <iostream>
using namespace std;

int binarySearch(int arr[], int left, int right, int x){
	while(left<=right){
		int mid = (left + right)/2;
		if(arr[mid] == x)
			return mid;
		else if(arr[mid] < x)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return -1;
}

// closest value less than or equal to the seach value
int binarySearchLower(int arr[], int left, int right, int x){
	while(left <= right){
		int mid = (left + right) / 2;
		if(arr[mid] <= x)
			left = mid + 1;
		else
			right = mid - 1;
	}
	return arr[left - 1];
}

// closest value greater than or equal to the search value
int binarySearchUpper(int arr[], int left, int right, int x){
	while(left <= right){
		int mid = (left + right) / 2;
		if(arr[right] >= arr[mid])
			right = mid - 1;
		else 
			left = mid + 1;
	}
	return arr[right + 1];
}

// Missing number in the array
// 0 1 2 3 5 6 7 -> 4
// l = 0, r = 7 -> m = 3 (arr[m] > m : 5 > 3) r = m
// l = 0, r = 3 -> m = 1 (arr[m] <= m : 1 <= 1) l = 1 + 1
// l = 2, r = 3 -> m = 2 (arr[m] <= m : 2 <= 2) l = 2 + 1
int missingNumber(int arr[], int left, int right){
	right += 1;
	while(left < right){
		int mid = (left + right) / 2;
		if(arr[mid] > mid) right = mid;
		else left = mid + 1;
	}
	return left;
}

//find the position of an element in a sorted range that has a value not less than the given value
int lowerBound(){
	vector<int> v = {10, 20, 30, 40, 50};
    // Finding lower bound for value 35 in vector v which is 40
    return *lower_bound(v.begin(), v.end(), 35);

}


int main() {
	int num;
	int myarr[10];
	int output;
	cout << "Enter 10 integers in Ascending order" << endl;
	for(int i=0;i<10;i++){
		cin >> myarr[i];
	}
	cout << "Enter number that you want to search :"<< endl;
	cin >> num;

	output = binarySearch(myarr,0,9,num);
	if(output == -1)
	{
		cout << "No match found" << endl;
	}
	else
	{
		cout << "Match found at Index Position :" << output << endl;
	}
	return 0;
}
