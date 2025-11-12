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
You are in a book shop which sells n different books. You know the price and number of pages of each book.
You have decided that the total price of your purchases will be at most x. What is the maximum number of 
pages you can buy? You can buy each book at most once.
*/

vector<vector<int>> dp;
int solve(int prices[], int pages[], int n, int cost){
    if(cost<0 || n==0) return 0;
    if(dp[n][cost]!=-1) return dp[n][cost];

    if(prices[n-1] > cost){
        return solve(prices, pages, n-1, cost);
    }
    else{
        ll maxi = max(pages[n-1]+solve(prices, pages, n-1, cost-prices[n-1]), solve(prices, pages, n-1, cost));
        maxi %= mod;
        return dp[n][cost] = maxi;
    }
}

//Time, space: O(n*cash) 
vector<vector<int>> table;
int tabular_method(int weight[], int profit[], int n, int bagW){
    table.resize(n+1, vector<int>(bagW+1, 0));
    for(int i=1; i<=n; i++){
        for(int j=0; j<=bagW; j++){
            if(weight[i-1]>j)           //if price is greater than current bagW
                table[i][j] = table[i-1][j];
            else{
                table[i][j] = max(profit[i-1]+table[i-1][j-weight[i-1]], table[i-1][j]);
            }
        }
    }
    return table[n][bagW];
}

int main()
{
    int T = 1, m, n, val;
    // cin >> T;
    while (T--)
    {
        cin >> n >> m;
        int price[n], pages[n];
        for(int i=0; i<n; i++)
            cin >> price[i];
        for(int j=0; j<n; j++)
            cin >> pages[j];
        
        // dp.resize(n+1, vector<int>(m+1, -1));
        // int res = solve(price, pages, n, m);

        int res = tabular_method(price, pages, n, m);
        cout << res << endl;
    }
    return 0;
}

/*
#Test 1
INPUT:
10 10
1 2 10 6 5 1 7 4 10 4
6 3 8 1 7 3 8 6 5 6

OUTPUT:
21

#Test 2
Input:
4 10
4 8 5 3
5 12 8 1

Output:
13

Explanation: You can buy books 1 and 3. Their price is 4+5=9 and the number of pages is 5+8=13.
*/