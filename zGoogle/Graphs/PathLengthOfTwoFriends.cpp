/*
There is an undirected graph where each node represents the home of a person. Two persons represented as node a and node b. 
a and b should reach node c while traveling independently, or both of them can club at some point and reach c. Find the minimum cost required for both of them to reach the destination (edges traversed). 

Note: If a and b both traverse an edge together, it is counted as cost 1.

Follow up:
What if there are n (a, b, c, d, ...) friends that are reaching the destination c ?
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> bfs(int start, const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int minCostTwoFriends(vector<vector<int>>& adj, int a, int b, int c) {
    vector<int> distA = bfs(a, adj);
    vector<int> distB = bfs(b, adj);
    vector<int> distC = bfs(c, adj);

    int n = adj.size();
    int ans = INT_MAX;

    // Option 1: Independent paths
    ans = min(ans, distA[c] + distB[c]);

    // Option 2: Meet at node x
    for (int x = 0; x < n; x++) {
        if (distA[x] == INT_MAX || distB[x] == INT_MAX || distC[x] == INT_MAX) continue;
        ans = min(ans, distA[x] + distB[x] + distC[x]);
    }

    return ans;
}
