#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int>vi;
#define test ll tt; cin>>tt; while(tt--)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define loop(i, b) for (ll i = 0; i < b; i++)
#define iterate(x) for(auto itr=x.begin(); itr != x.end(); ++itr)
#define printarr(a) for(auto i : a) cout<<i<<' ';cout<<endl;
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())

//https://open.kattis.com/problems/magicalcows

int main()
{
    IOS
    // c - max number of cows for each farm
    // n - no of farms initially
    int c, n, m; cin >> c >> n >> m;
    ll cow[n], visitDate[m];
    loop(i, n) cin >> cow[i];
    loop(i, m) cin >> visitDate[i];
    
    // regulator visits only for first 50 days
    // atmost c cows can be stored in each farm
    // stores frequency of farms with Cj no of cows on ith day
    ll dp[51][c+1];
    memset(dp, 0ll, sizeof(dp));


    for(int i=0; i<n; i++){
        dp[0][cow[i]]++;
    }

    for(int i=0; i<50; i++){
        for(int j=1; j<=c; j++){
            if(j <= c/2){
                // farm capacity doesnot exeed
                dp[i+1][j*2] += dp[i][j];
            }
            else{
                // no of farms become twise
                dp[i+1][j] += dp[i][j]*2ll;
            }
            
        }
    }

    for(int i=0; i<m; i++){
        ll sum = 0;
        for(int j=1; j<=c; j++){
            sum += dp[visitDate[i]][j];
        }
        cout << sum << "\n";
    }
    return 0;
}