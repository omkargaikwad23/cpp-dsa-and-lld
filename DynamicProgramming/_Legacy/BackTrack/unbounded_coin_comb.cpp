#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<endl;
#define mod 1000000007

/*
money system consisting of n coins. Each coin has a positive integer value. 
Your task is to calculate the number of distinct ways you can produce a money 
sum x using the available coins.
For example, if the coins are {2,3,5} and the desired sum is 9, there are 8 ways:
2+2+5
2+5+2
5+2+2
3+3+3
2+2+2+3
2+2+3+2
2+3+2+2
3+2+2+2
*/

int solve(int coins[], int n, int sum){
  vector<int>dp(sum+1, 0);
  dp[0] = 1;
  for(int i=1; i<=sum; i++){
    for(int j=0; j<n; j++){
      if(i-coins[j] >= 0)
        dp[i] = (dp[i]+dp[i-coins[j]])%mod;
    }
  }
  printarr(dp);
  return dp[sum];
}

int main()
{
  int T = 1, m, n;
  // cin >> T;
  while (T--)
  {
    cin >> n >> m;
    int coins[n];
    for(int i=0; i<n; i++)
      cin >> coins[i];

    int res = solve(coins, n, m);
    cout << res << endl;
    
    
  }
  return 0;
}