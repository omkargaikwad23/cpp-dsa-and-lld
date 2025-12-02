/*
================================================================================
                    GRAPH THEORY - MASTER OVERVIEW
================================================================================

Essential graph algorithms for Google interviews.

================================================================================
                           GRAPH REPRESENTATIONS
================================================================================

1. ADJACENCY LIST (Preferred for sparse graphs)
   vector<vector<int>> adj(n);
   vector<vector<pair<int,int>>> adj(n);  // weighted
   
2. ADJACENCY MATRIX (Dense graphs, O(1) edge lookup)
   vector<vector<int>> matrix(n, vector<int>(n, 0));

3. EDGE LIST (For Kruskal's, Bellman-Ford)
   vector<tuple<int,int,int>> edges;  // {u, v, weight}

================================================================================
                           ALGORITHM SUMMARY
================================================================================

TRAVERSAL:
+─────────────────+─────────────+────────────────────────────────────────────────+
| Algorithm       | Time        | Use Case                                       |
+─────────────────+─────────────+────────────────────────────────────────────────+
| BFS             | O(V + E)    | Shortest path (unweighted), level-order        |
| DFS             | O(V + E)    | Connectivity, cycles, topological sort         |
| Multi-source BFS| O(V + E)    | Distance from multiple sources                 |
| 0-1 BFS         | O(V + E)    | Shortest path (0/1 weights only)               |
+─────────────────+─────────────+────────────────────────────────────────────────+

SHORTEST PATH:
+─────────────────+─────────────+────────────────────────────────────────────────+
| Algorithm       | Time        | Use Case                                       |
+─────────────────+─────────────+────────────────────────────────────────────────+
| Dijkstra        | O(E log V)  | Non-negative weights, single source            |
| Bellman-Ford    | O(V * E)    | Negative weights, detect negative cycles       |
| Floyd-Warshall  | O(V³)       | All pairs shortest path                        |
| DAG Shortest    | O(V + E)    | DAG only, can handle negative weights          |
+─────────────────+─────────────+────────────────────────────────────────────────+

MINIMUM SPANNING TREE:
+─────────────────+─────────────+────────────────────────────────────────────────+
| Algorithm       | Time        | Use Case                                       |
+─────────────────+─────────────+────────────────────────────────────────────────+
| Kruskal's       | O(E log E)  | Sparse graphs, uses Union-Find                 |
| Prim's          | O(E log V)  | Dense graphs, uses priority queue              |
+─────────────────+─────────────+────────────────────────────────────────────────+

CONNECTIVITY:
+─────────────────+─────────────+────────────────────────────────────────────────+
| Algorithm       | Time        | Use Case                                       |
+─────────────────+─────────────+────────────────────────────────────────────────+
| Union-Find      | O(α(n))     | Dynamic connectivity, MST                      |
| Tarjan's SCC    | O(V + E)    | Strongly connected components                  |
| Kosaraju's      | O(V + E)    | SCC (two DFS passes)                           |
| Articulation    | O(V + E)    | Cut vertices                                   |
| Bridges         | O(V + E)    | Cut edges                                      |
+─────────────────+─────────────+────────────────────────────────────────────────+

================================================================================
                           FOLDER STRUCTURE
================================================================================

GraphTheory/
├── 00_GraphOverview.cpp      - This file
├── Graphs/
│   ├── BFS.cpp               - Basic BFS
│   ├── DFS.cpp               - Basic DFS  
│   ├── TopologicalSort.cpp   - Kahn's and DFS-based
│   ├── DisjointSet_unionFind_DSU.cpp
│   ├── TarjanSCC.cpp         - Strongly Connected Components
│   ├── Kosaraju.cpp          - SCC alternate
│   ├── ArticulationPoint.cpp - Cut vertices
│   ├── Bridges.cpp           - Cut edges
│   ├── cyclePathDirected.cpp
│   └── cyclePathUndirected.cpp
├── ShortestPath/
│   ├── Dijkstras.cpp
│   ├── BellmanFord.cpp
│   ├── FloydWarshall.cpp
│   ├── Kruskals.cpp          - MST
│   └── PrimsPQ.cpp           - MST
├── Problems/                  - NEW: LeetCode problems
│   ├── 01_BFS_Problems.cpp
│   ├── 02_DFS_Problems.cpp
│   ├── 03_UnionFind_Problems.cpp
│   ├── 04_TopSort_Problems.cpp
│   └── 05_ShortestPath_Problems.cpp
└── Trie/

================================================================================
                           QUICK TEMPLATES
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
// BFS TEMPLATE
// ─────────────────────────────────────────────────────────────────────────────
vector<int> bfs(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    return dist;
}

// ─────────────────────────────────────────────────────────────────────────────
// DFS TEMPLATE
// ─────────────────────────────────────────────────────────────────────────────
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// DIJKSTRA TEMPLATE
// ─────────────────────────────────────────────────────────────────────────────
vector<long long> dijkstra(int start, vector<vector<pair<int,int>>>& adj) {
    int n = adj.size();
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// ─────────────────────────────────────────────────────────────────────────────
// UNION-FIND TEMPLATE
// ─────────────────────────────────────────────────────────────────────────────
class DSU {
public:
    vector<int> parent, rank_;
    
    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        
        return true;
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// TOPOLOGICAL SORT (KAHN'S)
// ─────────────────────────────────────────────────────────────────────────────
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        
        for (int v : adj[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    return order.size() == n ? order : vector<int>();  // Empty if cycle
}


int main() {
    cout << "=== Graph Theory Overview ===" << endl;
    cout << "See individual files for detailed implementations." << endl;
    return 0;
}

