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

vector<vector<pii>> g(201);

void dijkstra(int n, int start){
    vector<int> dist(n+1, INT_MAX);
    vector<int> vis(n+1, false);
    priority_queue<vi, vector<vi>, greater<vi>> pq;
    pq.push({0, start, 0});
    dist[start] = 0;
    vis[start] = 0;

    vector<int> count(n+1, 0);

    while(!pq.empty()){
        int minVal = pq.top()[0];
        int index = pq.top()[1];
        int steps = pq.top()[2];
        pq.pop();

        count[index] = max(steps, 0);

        for(auto& edge : g[index]){
            if(vis[edge.first]) continue;
            int newDist = dist[index] + edge.second;

            if(newDist < dist[edge.first]){
                dist[edge.first] = newDist;
                vis[edge.first] = true;
                pq.push({newDist, edge.first, steps+1});
            }
        }
    }
    vector<int> ans(n+1, 0);

    for(int i=0; i<=n; i++){
        // cout << count[i] << " ";
        for(auto& edge : g[i]){
            int d = dist[edge.first] + edge.second;
            if(d == dist[i]){
                ans[i] += count[edge.first];
            }
        }
    }
    cout << endl;
    for(int i=1; i<=n; i++){
        cout << ans[i] << " "; 
    }
}

void solve(){
    int n, m; 
    cin >> n >> m;
    int u, v, w; 
    for(int i=0; i<m; i++){
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    int start; cin >> start;

    dijkstra(n, start);
}

int main()
{
    IOS
    solve();
    return 0;
}