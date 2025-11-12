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
    if(w == 0 || n == 0) return 0;
    if(dp[w][n] != -1) return dp[w][n];
    
    int res;
    if(wt[n] > w)
        res = knapsack_rec(wt, profit, dp, w, n-1);
    else
        res = max(knapsack_rec(wt, profit, dp, w, n-1), knapsack_rec(wt, profit, dp, w-wt[n], n-1) + profit[n]);
    return dp[w][n] = res;
}

int knapsack_itr(int wt[], int profit[], int weight, int n){
  vector<vector<int>>dp(n+1, vector<int>(weight+1, 0));
    
  for(int i=1; i<=n; i++){
      for(int j=0; j<=weight; j++){
          if(wt[i-1]>j){
              dp[i][j] = dp[i-1][j];
          }
          else{
              dp[i][j] = max((profit[i-1]+dp[i-1][j-wt[i-1]]), dp[i-1][j]);
          }
      }
  }
  return dp[n][weight];
}

int main()
{
    int n, w; 
    cin >> n >> w;

    int profit[n], wt[n];
    for(int i=0; i<n; i++)
        cin >> profit[i];
    for(int i=0; i<n; i++)
        cin >> wt[i];

    vector<vector<int>> dp(w+1, vector<int>(n+1, -1));
    cout << knapsack_rec(wt, profit, dp, w, n) << "\n";
    cout << knapsack_itr(wt, profit, w, n) << '\n';
    return 0;
}