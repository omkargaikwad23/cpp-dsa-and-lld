#include <iostream>
#include <iostream>
#include <map>
#include <stack>
#include <unordered_set>
using namespace std;


void solve(vector<int> &arr1, vector<int> &arr2, int k) {

    unordered_set<int> us(arr1.begin(), arr1.begin() + k);
    
    int i = 0;
    for(; i<arr2.size(); i++) {
        if(us.find(arr2[i]) != us.end()) continue; //if arr2[i] is common skip it
        k--;
        cout << arr2[i] << ", ";
        if(k == 0) break;
    }
    i++;

    while(i < arr2.size()) {
        cout << arr2[i++] << " ";
    }
}


int main() {
    vector<int> arr1 = {1, 2, 3, 4, 5};
    vector<int> arr2 = {3, 3, 3, 4, 5, 6, 1, 2};
    int k = 3;

    solve(arr1, arr2, k);  // Output: 4 5 6 1 2

    vector<int> arr1_2 = {1, 2, 3, 4, 5};
    vector<int> arr2_2 = {1, 4, 3, 2, 4};
    k = 3;

    solve(arr1_2, arr2_2, k);  // Output: 4 4
}

/*
Given two arrays arr1 and arr2 and a window size K, remove elements from prefix arr2 such that no common element exists in first K-window of arr1 and arr2.

Example - 1 :-
arr1 = [1, 2, 3, 4, 5]
arr2 = [3, 3, 3, 4, 5, 6, 1, 2]
K = 3
Output:- [4, 5, 6, 1, 2]

First K-window of arr1 = [1, 2, 3]
First K-window of arr2 = [3, 3, 3]
Here all the three elements of K-window of arr2 are present in arr1.
So remove all the three.

Now, arr2 = [4, 5, 6, 1, 2]

New K-window of arr2 = [4, 5, 6]

No common elements in both K-windows. So we stop removing elements.

Output:- [4, 5, 6, 1, 2]

----------------
Example - 2 :-

arr1 = [1, 2, 3, 4, 5]
arr2 = [1, 4, 3, 2, 4]
K = 3
Output:- [4, 4]

First K-window of arr1 = [1, 2, 3]
First K-window of arr2 = [1, 4,3]

1 and 3 are common elements here. Remove them.

Now arr2 = [4, 2, 4]

First K-window of arr1 = [1, 2, 3]
First K-window of arr2 = [4, 2, 4]

2 is the common element here, remove it.

Now arr2 = [4, 4]

Final output:- [4, 4]
*/
