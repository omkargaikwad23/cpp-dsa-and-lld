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


/*
Return the fewest number of coins that you need to make up that amount. 

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

You have infinite number of each kind of coins
*/


class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // tabulation
        vector<int> dp(amount+1, INT_MAX-1);
        dp[0] = 0;
        for(int i=1; i<=amount; i++){
            for(int j=0; j<coins.size(); j++){
                if(i-coins[j] >= 0)
                    dp[i] = min(dp[i], dp[i-coins[j]]+1);
            }
        }
        return (dp[amount] == INT_MAX-1) ? -1 : dp[amount];
        
        // top down
        // map<int, int>memo;
        // return min_coins(coins, amount, memo);
    }
    
    int min_coins(const vector<int>& coins, int amount, map<int, int>& memo)
    {
        if(amount < 0) return -1;
        if(amount == 0) return 0;
        if(memo.count(amount)!=0) return memo[amount];
        int min_value = INT_MAX;
        for(const auto& c: coins) {
            auto count = min_coins(coins, amount-c, memo);
            if(count != -1)
                min_value = min(min_value, count+1);
        }
        return memo[amount] = (min_value == INT_MAX) ? -1 : min_value;
    }
};

int main()
{
    return 0;
}