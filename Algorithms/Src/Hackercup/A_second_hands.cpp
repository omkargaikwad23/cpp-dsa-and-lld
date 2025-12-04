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

int t = 0;
void solve(){
    t++;
    int n, k; cin >> n >> k;
    int arr[n];

    bool flag = true;

    map<int,int> mp;
    for(int i=0; i<n; i++){
        cin >> arr[i];
        mp[arr[i]]++;
        if(mp[arr[i]] > 2) flag = false;
    }

    cout << "Case #" << t << ": ";

    if((n > 2*k) || !flag) {
        cout << "NO\n";
    }
    else{
        cout << "YES\n";
    }
}

int main()
{
    IOS
    freopen("input1.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
    TEST
    solve();
    return 0;
}