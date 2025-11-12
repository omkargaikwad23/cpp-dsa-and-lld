#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        int dp[n+1][n+1];
        
        for(int i=0; i<=n; i++){
            for(int j=0; j<=n; j++){
                if(i==0 || j==0)
                    dp[i][j] = 0;
                else{
                    if(s[i-1] == s[n-j])
                        dp[i][j] = 1 + dp[i-1][j-1];
                    else
                        dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
                }
            }
        }
        return dp[n][n];
    }
};

int main()
{
    
    
    return 0;
}