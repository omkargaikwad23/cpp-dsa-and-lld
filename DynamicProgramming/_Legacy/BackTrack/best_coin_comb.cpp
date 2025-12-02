#include <bits/stdc++.h>
using namespace std;
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<endl;
#define mod 1000000007
#define INF 1000000000

int best_sum(int coins[], int n, int sum){
  vector<int>dp(sum+1, INF);

  dp[0] = 0;  //0 coins will be required to make sum=0
  //if x-Ci sum can be made in y coins
  //then x sum can be made in y+1 coins
  for(int i=1; i<=sum; i++){
    for(int j=0; j<n; j++){
      if(i-coins[j]>=0) 
        dp[i] = min(dp[i], dp[i-coins[j]]+1);
    }
  }
  if(dp[sum]==INF) return -1;
  return dp[sum];
}

int main()
{
  int T = 1, m, n;
  // cin >> T;
  while (T--)
  {
    cin >> n >> m;
    int arr[n];
    for(int i=0; i<n; i++){
      cin >> arr[i];
    }
    int res = best_sum(arr, n, m);
    cout << res << endl;
    
  }
  return 0;
}