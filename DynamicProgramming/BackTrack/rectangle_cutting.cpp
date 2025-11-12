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
Given an a×b rectangle, your task is to cut it into squares. On each move you can select 
a rectangle and cut it into two rectangles in such a way that all side lengths remain 
integers. What is the minimum possible number of moves?
eg. 3 5
    3
*/


//time: O(h*w(h+w)) space: O(h*w)
int solve(int n, int m){
    int dp[n+1][m+1];
    
    for(int height=1; height<=n; height++){
        for(int width=1; width<=m; width++){
            if(height==width){
                dp[height][width] = 0;
            }
            else{
                //check every vertical cut
                int op1 = 1e8, op2 = 1e8;
                for(int i=1; i<width; i++){
                    op1 = min(op1, 1+dp[height][width-i]+dp[height][i]);
                }
                //check every horizontal cut
                for(int i=1; i<height; i++){
                    op2 = min(op2, 1+dp[height-i][width]+dp[i][width]);
                }
                dp[height][width] = min(op1, op2)%mod;
            }
        }
    }
    
    return dp[n][m];
}

int main()
{
    int T = 1, m, n;
    // cin >> T;
    while (T--)
    {
        cin >> n >> m;
        cout << solve(n, m);
    
    
    }
    return 0;
}