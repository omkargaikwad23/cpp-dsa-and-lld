#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <random>
#include <fstream>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> p32;
typedef pair<ll, ll> p64;
typedef pair<double, double> pdd;
typedef vector<ll> v64;
typedef vector<int> v32;
typedef vector<vector<int>> vv32;
typedef vector<vector<ll>> vv64;
typedef vector<vector<p64>> vvp64;
typedef vector<p64> vp64;
typedef vector<p32> vp32;
ll MOD = 998244353;
double eps = 1e-12;
#define forn(i, e) for (ll i = 0; i < e; i++)
#define forsn(i, s, e) for (ll i = s; i < e; i++)
#define rforn(i, s) for (ll i = s; i >= 0; i--)
#define rforsn(i, s, e) for (ll i = s; i >= e; i--)
#define ln "\n"
#define dbg(x) cout << #x << " = " << x << ln
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define INF 2e18
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define all(x) (x).begin(), (x).end()
#define sz(x) ((ll)(x).size())
#define iterate(x) for (auto itr = x.begin(); itr != x.end(); ++itr)

int arr1[200002];
ll arr2[200002];
ll arr2D[1001][1001];
vector<ll> vec;

map<ll, vector<int>> mymp;

pair<vector<int>, bool> S(int sum, int A[], int n)
{
    if (mymp.find(sum) != mymp.end())
        return {mymp[sum], true};

    if (sum == 0)
    {
        vector<int> v;
        return {v, true};
    }

    if (sum < 0)
    {
        vector<int> v;
        return {v, false};
    }

    for (int i = 0; i < n; i++)
    {
        int remain = sum - A[i];
        pair<vector<int>, bool> temp = S(remain, A, n);

        if (temp.second == true)
        {
            mymp[remain] = temp.first;

            temp.first.push_back(A[i]);

            mymp[sum] = temp.first;

            return {temp.first, true};
        }
    }

    vector<int> v;
    return {v, false};
}

vector<int> tabu(int sum, int arr[], int n)
{
    vector<pair<vector<int>, bool>> table;

    table[0].first.push_back(0);
    table[0].second = true;

    for (int i = 0; i <= sum; i++)
    {
        if (table[i].second == true)
        {           
            for (int j = 0; j < n; j++)
            { 
                table[i].first.push_back(arr[j]);
                table[i + arr[i]].first = table[i].first;
                table[i + arr[i]].second = true;
            }
        }
    }
    cout << "hi" << endl;
    return table[sum].first;
}

void solve()
{
    ll n, m, a, b, c, d;
    string s;
    
    cin >> n;
    
    forn(i, n) cin >> arr1[i];

    cin >> m;
    cout << n << " ";
    // pair<vector<int>,bool> temp = S(m,arr1,n);
    // if(temp.second != false)
    // {
    //     for(auto i:temp.first) cout << i << " ";
    //     cout << endl;
    // }
    
    vector<int> temp = tabu(m, arr1, n);
    
    for (auto itr : temp)
    {
        cout << 1 << " ";
        cout << itr << " ";
    }
}

int main()
{
    fast_cin();
    ll t = 1;
    //cin >> t;
    for (int it = 1; it <= t; it++)
    {
        //cout << "Case #" << it+1 << ": ";
        solve();
    }
    return 0;
}