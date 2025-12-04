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

vector<pii> dir = {{0,1},{1,0},{-1,0},{0,-1}};

int t = 0;
void solve(){
    t++;
    int r, c; cin >> r >> c;
    vector<vector<char>> grid(r, vector<char>(c));

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cin >> grid[i][j];
        }
    }

    queue<pii> q;

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(grid[i][j] == '.') continue;
            q.push({i, j});
        }
    }

    bool notPossible = false;

    while(!q.empty()){
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        
        int frnds = 0, empty = 0;
        for(auto& d : dir){
            int newi = i + d.first;
            int newj = j + d.second;
            if(newi<0 || newj<0 || newi==r || newj==c) continue;
            if(grid[newi][newj] == '^')
                frnds++;
            else
                empty++;
        }
        if(frnds >= 2) continue;
        if(frnds + empty < 2) {
            notPossible = true;
            break;
        }


        empty = (frnds == 1) ? 1 : 2;

        for(auto& d : dir){
            int newi = i + d.first;
            int newj = j + d.second;
            if(newi<0 || newj<0 || newi==r || newj==c) continue;
            if(grid[newi][newj] == '^')
                continue;
            else{
                grid[newi][newj] = '^';
                q.push({newi, newj});
                empty--;
                if(empty == 0) break;
            }
        }
    }

    cout << "Case #" << t << ": ";

    if(notPossible){
        cout << "Impossible\n";
    }
    else{
        cout << "Possible\n";
        for(int i=0; i<r; i++){
            for(int j=0; j<c; j++){
                cout << grid[i][j];
            }
            cout << endl;
        }
    }
}

int main()
{
    IOS
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    TEST
    solve();
    return 0;
}