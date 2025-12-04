#include <bits/stdc++.h>
using namespace std;

/*
[1, 100]
[1, 2, 3, 4, ... 99, 100] -> N = 99


1) solution1 : 
 - iterate the array and [0, 99]
 - 1 make index 0 value -ve
 - 2 is present in array then make value at index 1 neg

 - second iteration if index value is positive then 

 [1, 2, 4] --> [0, 1, 3]
 N = 3
 [-1, -2, 4]
 index 

[1,2,4,5] -> [0, 1, 3, 4]
[-1, -2, 4, -5] -> found index 2 is positive -> val = index + 1 is missing  => 3 is missing

[2, 1, 5, 4] -> [1, 0, 4, 3] 
[-2, -1, 5, -4]
-> index 2 value is positive so value = index + 1 is missing =>> 2 + 1 = 3 is missing 
[2, 1, 5, 4]

*/

/*
sum of N elements [1, N]
sum = (n*(n+1))/2

take arrSum = 


*/

int main()
{
    
    return 0;
}