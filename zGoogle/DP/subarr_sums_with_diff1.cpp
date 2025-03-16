/*
There is an array of size n. Find the sum of all possible valid subsequences in the array.
Valid Subsequence: Continuous subarray with absolute difference of 1 between adjacent elements.
Input: [4,5,4,9,10,11,3,8]
Ans: 99
Input: [11,35]
Ans: 46

4 5
4 5 4
5 4
9 10
10 11
9 10 11


First Line: 4 5
Sum: 4+5=9
Second Line: 4 5 4
Sum: 4+5+4=13
Third Line: 5 4
Sum: 5+4=9
Fourth Line: 9 10
Sum: 9+10=19
Fifth Line: 10 11
Sum: 10+11=21
Sixth Line: 9 10 11
Sum: 9+10+11=30
Now, add the sums from each line together:

9+13+9+19+21+30=101
*/