#include <bits/stdc++.h>
using namespace std;

/*
https://leetcode.com/problems/partition-equal-subset-sum/

Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
*/

//time: space: 
class Solution {
    vector<vector<int>>mem;
    bool helper(vector<int>& nums, int n, int target){
        if(target<0 || n<0) return false;
        if(target==0) return true;   //sum found
        
        if(mem[n][target]!=-1) 
            return mem[n][target];
        
        return mem[n][target] = helper(nums, n-1, target-nums[n]) || 
            helper(nums, n-1, target);
    }
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0, n = nums.size();
        
        for(int i=0; i<n; i++)
            sum+=nums[i];
        if(sum%2==1) return false;   //odd sum
        
        mem.resize(n+1, vector<int>(sum/2+1, -1));
        return helper(nums, nums.size()-1, sum/2);
    }
};

// tabulation
class Tabulation{
public:
    bool canPartition(vector<int>& nums) {
        int sum = 0, n = nums.size();
        for(int i=0; i<n; i++)
            sum+=nums[i];
        if(sum & 1) return false;
        
        bool dp[n+1][sum/2+1];
        for(int i=0; i<=n; i++){
            for(int j=0; j<=sum/2; j++){
                if(i==0 || j==0)            //base case
                    dp[i][j] = false;
                else if(nums[i-1] > j)      //skip case
                    dp[i][j] = dp[i-1][j];
                else if(nums[i-1]==j)
                    dp[i][j] = true;
                else
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
            }
        }
        return dp[n][sum/2];
    }
};

/* ----- partial into K equal subset sum -----*/
// https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
class Solution_698 {
    bool solve(int start,int k, int curSum, int target, vector<int>&nums, vector<int>&vis){
        if(k == 1) return true;
        if(curSum == target) 
            return solve(0, k-1, 0, target, nums, vis);
        
        for(int i=start; i<nums.size(); i++){
            if(curSum + nums[i] > target) break;
            if(!vis[i]){
                vis[i] = true;
                if(solve(i+1, k, curSum + nums[i], target, nums, vis))
                    return true;
                vis[i] = false;
            }
        }
        return false;
    }
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        
        sort(nums.begin(), nums.end());
        vector<int> dp(k, 0), vis(nums.size(), false);
        
        if(total%k != 0 || nums.size()<k || nums[nums.size()-1] > total/k) 
            return false;

        return solve(0, k, 0, total/k, nums, vis); //start_index, k, cur_sum, target 
    }
};