#include <bits/stdc++.h>
using namespace std;

//Maximum Sum Circular Subarray
class Solution {
  public:
      int maxSubarraySumCircular(vector<int>& nums) {
          int curMax = 0;
          int curMin = 0;
          int maxSum = nums[0];
          int minSum = nums[0];
          int totalSum = 0;
          
          for (int num: nums) {
              // Normal Kadane's
              curMax = max(curMax, 0) + num;
              maxSum = max(maxSum, curMax);
              
              // Kadane's but with min to find minimum subarray
              curMin = min(curMin, 0) + num;
              minSum = min(minSum, curMin);
              
              totalSum += num;  
          }
  
          if (totalSum == minSum) {
              return maxSum;
          }
          
          return max(maxSum, totalSum - minSum);
      }
};

// find max sum of subarray
int maxSumSubArray(int arr[], int n){
  int maxSum = INT_MIN;
  int curSum = 0;
  for(int i=0; i<n; i++){
    curSum += arr[i];
    maxSum = max(maxSum, curSum);
    if(curSum<0)  curSum = 0;
  }
  return maxSum;
}

int minSumSubArray(int arr[], int n){
  int minSum = INT_MAX;
  int curSum = 0;
  for(int i=0; i<n; i++){
    curSum += arr[i];
    minSum = min(minSum, curSum);
    if(curSum>0)  curSum = 0;
  }
  return minSum;
}

int kadane(vector<int>& nums) {
  int currMax = nums[0];
  int maxSum = nums[0];

  for (int i = 1; i < nums.size(); i++) {
      int num = nums[i];
      currMax = max(num, currMax + num);
      maxSum = max(maxSum, currMax);
  }

  return maxSum;
}

int main(){
  int n; cin>>n;
  int arr[n];
  for(int i=0;i<n;i++) cin>> arr[i];

  int res = maxSumSubArray(arr, n);
  // int res2 = minSumSubArray(arr, n);
  cout << res << endl;
  // cout << max(res, abs(res2)) << endl;
}