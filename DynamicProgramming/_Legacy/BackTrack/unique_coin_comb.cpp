#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long int lli;
#define loop(i, a, b) for (int i = a; i < b; i++)
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<endl;
#define mod 1000000007



int solve(vector<int>&coins, int x){
    int n = coins.size()-1;
    int dp[n+1][x+1];
    // cout << endl;
    // printarr(coins);
    for(int i=1; i<=n; i++){
        for(int sum=0; sum<=x; sum++){
            if(sum==0){
                dp[i][sum] = 1; //to make sum 0 by any number of coins there will be 1 way
            }
            else{
                int op1 = (coins[i]>sum) ? 0 : dp[i][sum-coins[i]];  //take ith coin
                int op2 = (i==1) ? 0 : dp[i-1][sum];  //dont take ith coin, i==1 can't exclude it
                dp[i][sum] = (op1 + op2)%mod;
            }
        }
    }
    return dp[n][x];
}

int main()
{
    int T = 1, x, n;
    // cin >> T;
    while (T--)
    {
        cin >> n >> x;
        vector<int>coins(n+1);
        for(int i=1; i<=n; i++){
            cin >> coins[i];
        }
        
        cout << solve(coins, x) << endl;
        
    }
    return 0;
}