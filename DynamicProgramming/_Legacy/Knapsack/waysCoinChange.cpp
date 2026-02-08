#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int>vi;
typedef vector<ll>vl;
typedef vector<bool>vb;
#define TEST ll tt; cin>>tt; while(tt--)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define loop(i, b) for (ll i = 0; i < b; i++)
#define printarr(a) for(auto i:a) cout<<i<<' ';cout<<endl;
#define all(x) (x).begin(), (x).end()
#define mod 1000000007

/*
https://practice.geeksforgeeks.org/problems/coin-change2448/1
*/
long long int count(int coins[], int m, int n) {
    long long dp[n+1]={0};
    dp[0]=1;
    for(int i=0;i<m;i++){
        for(int j=coins[i]; j<n+1; j++){
            dp[j] += dp[j-coins[i]];
        }
    }
    return dp[n];
}

/*
https://leetcode.com/problems/coin-change-2/description/
unique ways to make amount from unlimited coins
time, space: O(n*amount)

Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
*/

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();
        int dp[n][amount+1];
    
        for(int i=0; i<n; i++){
            for(int sum=0; sum<=amount; sum++){
                if(sum==0){
                    dp[i][sum] = 1;   //to make sum=0 by any number of coins: 1 way 
                }
                else{
                    int op1 = (coins[i]>sum) ? 0 : dp[i][sum-coins[i]]; //take ith coin
                    int op2 = (i==0) ? 0 : dp[i-1][sum]; //dont take ith coin
                    dp[i][sum] = op1 + op2;
                }
            }
        }
       
        return dp[n-1][amount];
    }
};

int main()
{
    IOS
    
    return 0;
}