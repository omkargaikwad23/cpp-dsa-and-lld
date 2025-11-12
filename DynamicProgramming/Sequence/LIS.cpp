#include <bits/stdc++.h>
using namespace std;

/*
Input: nums = [10,9,2,5,3,7,101,18]
Output: 4
Explanation: The LIS is [2,3,7,101], therefore the length is 4.
*/

// time : O(n*2) space : O(n)
int lengthOfLIS(vector<int>& nums) {
    int n = nums.size(), maxi = 1;
    vector<int> lis(n, 1), hash(n);
    int lastIndex = 0;
    
    for(int i=0; i<n; i++){
        hash[i] = i;
        for(int j=0; j<i; j++){
            if(nums[i] > nums[j] && lis[j]+1 > lis[i]){
                lis[i] = lis[j]+1;
                hash[i] = j;
            }
            if(lis[i] > maxi){
                maxi = lis[i];
                lastIndex = i;
            }
        }
    }
    
    // print LIS
    vector<int> temp;
    temp.push_back(nums[lastIndex]);
    while(hash[lastIndex] != lastIndex){
        lastIndex = hash[lastIndex];
        temp.push_back(nums[lastIndex]);
    }

    return *max_element(lis.begin(), lis.end());
}

//N.log(N)
int lengthOfLIS1(vector<int>& nums) {
    vector<int> res;
    for(int i=0; i<nums.size(); i++) {
        auto it = lower_bound(res.begin(), res.end(), nums[i]);
        if(it==res.end()) res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}
/*
So what above algo is doing? For each number we have 2 options:
- if it's the highest found value, we push it back, since a high value obviously makes our increasing sequence longer
- if it's not the highest found value, then it could be a nice start (or continuation) of a shorter sequence. And we keep that sequence in place. Merging all found and possible sequences into one dp
See how res is changing when we go through the numbers:

[1,2,7,8,3,4,5,9,0]
1 -> [1]
2 -> [1,2]
7 -> [1,2,7]
8 -> [1,2,7,8]
3 -> [1,2,3,8]  // we replaced 7 with 3, since for the longest sequence we need only the last number and 1,2,3 is our new shorter sequence
4 -> [1,2,3,4] // we replaced 8 with 4, since the max len is the same but 4 has more chances for longer sequence
5 -> [1,2,3,4,5]
9 -> [1,2,3,4,5,9]
0 -> [0,2,3,4,5,9] // we replaced 1 with 0, so that it can become a new sequence
*/

int main(){
    vector<int>nums;
    int n, temp;
    for(int i=0; i<n; i++){
        cin >> temp;
        nums.push_back(temp);
    }

    cout << lengthOfLIS(nums) << endl;
}