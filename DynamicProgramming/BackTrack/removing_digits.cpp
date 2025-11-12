#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long int lli;
typedef long double ld;
#define pii pair<int, int>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define loop(i, a, b) for (int i = a; i < b; i++)
#define iterate(x) for(auto itr=x.begin(); itr != x.end(); ++itr)
bool isPrime(ll n){if(n <= 1)return false;if(n <= 3)return true;if(n%2 == 0 || n%3 == 0)return false;for(ll i=5; i*i<=n; i=i+6)if(n%i == 0 || n%(i+2) == 0)return false;return true;}
ll nextPrime(ll N){if(N<=1)return 2;ll prime = N;bool found = false;while(!found){prime++;if(isPrime(prime))found=true;}return prime;}
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<endl;
#define mod 1000000007

/*
Input:
27
Output:
5
Explanation: An optimal solution is 27→20→18→10→9→0.
*/

int solve(int n){
    vector<ll>dp(n+1, INT_MAX);
    dp[0] = 0;
    for(int i=1; i<=n; i++){
        int num = i;
        while(num>0){
            int dig = num%10;
            dp[i] = min(dp[i], dp[i-dig]+1);
            num/=10;
        }
    }
    // printarr(dp);
    return dp[n];
}

int main()
{
    int T = 1, m, n;
    // cin >> T;
    while (T--)
    {
        cin >> n;
        cout << solve(n);

    }
    return 0;
}