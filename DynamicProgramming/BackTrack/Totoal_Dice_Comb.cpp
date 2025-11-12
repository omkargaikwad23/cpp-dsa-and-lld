#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define loop(i, a, b) for (int i = a; i < b; i++)
#define mod 1000000007

/*
Your task is to count the number of ways to construct sum n by throwing a dice 
one or more times. Each throw produces an outcome between 1 and 6.
For example, if n=3, there are 4 ways:
1+1+1
1+2
2+1
3
*/
unordered_map<int, ll>memo;
// not working
ll dice_comb(int n){
  memo.insert({0, 1});
  if(n==0) return 1;
  if(n<0) return 0;

  if(memo.find(n)!=memo.end()){ 
    memo[n] = memo[n]%mod;
    return memo[n];
  }

  for(int i=1; i<=n; i++){
    memo[n] += dice_comb(n-i);
  }
  return memo[n];
}

// working
ll tabu(int n){
  vector<ll>dp(n+1, 0);
  dp[0] = 1;  //to make sum 0 there will be 1 way
  for(int i=1; i<=n; i++){
    for(int j=1; j<=6; j++){   //dice outcome possibilities
      if(j> i) break;
      dp[i] = (dp[i] + dp[i-j]) % mod;
    }
  }
  return dp[n];
}

int main()
{
  int T = 1, n;
  // cin >> T;
  while (T--)
  {
    cin >> n;
    ll ways = dice_comb(n);
    cout << ways;
  }
  return 0;
}

/*testcases:
1 -> 1
2 -> 2
3 -> 4
5 -> 16
10 -> 492
*/