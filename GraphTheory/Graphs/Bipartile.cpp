#include <bits/stdc++.h>
using namespace std;


/*
https://codeforces.com/problemset/problem/1144/F
6 5
1 5
2 1
1 4
3 1
6 1
output:
YES
10100
*/

// return false if graph is bipartile
bool dfs(int u, vector<bool>& visited, vector<bool>& col, vector<int> adj[]){
    visited[u] = true;
    for(auto v : adj[u]){
        if(visited[v] && col[u]==col[v]) 
            return false;
        else if(!visited[v]){
            col[v] = !col[u];
            if(!dfs(v, visited, col, adj)){
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> adj[n+1];
    int u, v;

    loop(i, m){
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<bool>visited(n+1, false);
    vector<bool>color(n+1);
    color[1] = 1;

    if(dfs(1, visited, color, adj))
        cout << "YES\n";
    else
        cout << "NO\n";
    
    return 0;
}