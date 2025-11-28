#include <bits/stdc++.h>
using namespace std;

/*
Given weights and profit of n items, put these items in 
a knapsack of capacity W to get maximum total profit in knapsack.

3 50  --> n, w
60 100 120 --> profit
10 20 30 --> weights

weight : 30+20 and profit : 120 + 100
*/
int knapsack_rec(int wt[], int profit[], vector<vector<int>> &dp, int w, int n){
    if(w == 0 || n == 0) return 0; // if the capacity of the knapsack is 0 or the number of items is 0, then the profit is 0
    if(dp[w][n] != -1) return dp[w][n]; // if the result is already calculated, then return it
    
    int res;
    if(wt[n-1] > w) // if the weight of the item is greater than the capacity of the knapsack, then we cannot take the item
        res = knapsack_rec(wt, profit, dp, w, n-1); // not taking the item
    else
        res = max(knapsack_rec(wt, profit, dp, w, n-1), knapsack_rec(wt, profit, dp, w-wt[n], n-1) + profit[n]); // taking the item: profit[n] + profit of the remaining items
    return dp[w][n] = res; // store the result in the dp table
}

int knapsack_itr(int wt[], int profit[], int weight, int n){
  vector<vector<int>>dp(n+1, vector<int>(weight+1, 0)); // initialize the dp table
    
  for(int i = 1; i <= n; i++){ // iterate over the items
      for(int j = 0; j <= weight; j++){ // iterate over the capacities
          if(wt[i-1] > j){ // if the weight of the item is greater than the capacity of the knapsack, then we cannot take the item
              dp[i][j] = dp[i-1][j]; // not taking the item
          }
          else{
              dp[i][j] = max((profit[i-1]+dp[i-1][j-wt[i-1]]), dp[i-1][j]); // taking the item: profit[i-1] + profit of the remaining items
          }
      }
  }
  return dp[n][weight]; // return the maximum profit
}

int main()
{
    // Example: 3 items, capacity 50
    int n = 3, w = 50;
    
    int profit[] = {60, 100, 120};
    int wt[] = {10, 20, 30};

    vector<vector<int>> dp(w+1, vector<int>(n+1, -1));
    cout << "Recursive: " << knapsack_rec(wt, profit, dp, w, n) << "\n";
    cout << "Iterative: " << knapsack_itr(wt, profit, w, n) << '\n';
    return 0;
}