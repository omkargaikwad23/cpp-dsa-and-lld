#include <bits/stdc++.h>
using namespace std;

// s1 = ABCDGH, s2 = AEDFHR
// lcs = ADH (3)

// time, space: O(n^2)

int lcs(string s1, string s2){
    int l = s1.length(), m = s2.length();
    int dp[l+1][m+1];
    
    for(int i=0; i<=l; i++){
        for(int j=0; j<=m; j++){
            if(i==0 || j==0) {
                dp[i][j] = 0;
            }
            else {
                if(s1[i-1]==s2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
    }
    string ans = "";
    
    int i = l, j = m;
    while(dp[i][j]!=0){
        // cout << i << " " << j << endl;
        if(dp[i][j]>max(dp[i-1][j], dp[i][j-1])){
            ans = s1[i-1] + ans;
            i--, j--;
        }
        else{
            if(dp[i][j-1]>=dp[i-1][j]){
                j--;
            }else{
                i--;
            }
        }
    }
    cout << ans << endl;
    return dp[l][m];
}

int main(){
    string s1, s2;
    cin >> s1 >> s2;
    cout << lcs(s1, s2);
}