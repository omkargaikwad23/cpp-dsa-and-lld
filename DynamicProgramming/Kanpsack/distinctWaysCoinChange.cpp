#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define mod 1000000007

/*
money system consisting of n coins. Each coin has a positive integer value.
Your task is to calculate the number of distinct ways you can produce a money
sum x using the available coins.*/

int solve(int coins[], int n, int sum)
{
    vector<int> dp(sum + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= sum; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i - coins[j] >= 0)
                dp[i] = (dp[i] + dp[i - coins[j]]) % mod;
        }
    }
    // printarr(dp);
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
        for (int i = 0; i < n; i++)
            cin >> coins[i];

        cout << solve(coins, n, m) << endl;
    }
    return 0;
}