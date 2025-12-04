#include <bits/stdc++.h>
using namespace std;

/*
Given an array containing score of students in a particular subject.
 Get the max and min score in the subject with minimum number of comparision.


[2, 5, 3, 7, 1] -> 2*n comparisons

2, 5
5, 3 -> 3, 5
5, 7
7, 1 -> 1, 7

[2, 5, 3, 7, 1]
0, 2, 7, 10, 17, 18


diff = sum - prevSum;



minVal = arr[0];
maxVal = arr[0];

1, 2, 3, 4



for(int i=1; i<n; i++){
    if(arr[i] <= minVal){
        minVal = arr[i];
    }
    else if(arr[i] > maxVal) {
        maxVal = arr[i];
    }
}

*/

int main()
{
    
    
    return 0;
}