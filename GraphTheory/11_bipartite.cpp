/*
================================================================================
                    BIPARTITE GRAPH
================================================================================

BIPARTITE: Graph that can be 2-colored (no edge between same color)
EQUIVALENT: Graph has no odd-length cycle

Check using BFS/DFS coloring | O(V + E)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Check Bipartite using BFS ⭐
// ═══════════════════════════════════════════════════════════════════════════

bool isBipartiteBFS(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1);
    
    for (int start = 0; start < n; start++) {
        if (color[start] != -1) continue;
        
        queue<int> q;
        q.push(start);
        color[start] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (color[v] == -1) { // unvisited
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;  // Same color = not bipartite
                }
            }
        }
    }
    
    return true;
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Check Bipartite using DFS
// ═══════════════════════════════════════════════════════════════════════════

bool isBipartiteDFS(int n, vector<vector<int>>& adj) {
    vector<int> color(n, -1);
    
    function<bool(int, int)> dfs = [&](int u, int c) -> bool {
        color[u] = c;
        for (int v : adj[u]) {
            if (color[v] == -1) {
                if (!dfs(v, 1 - c)) return false;
            } else if (color[v] == c) {
                return false;
            }
        }
        return true;
    };
    
    for (int i = 0; i < n; i++) {
        if (color[i] == -1 && !dfs(i, 0)) return false;
    }
    
    return true;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Maximum Bipartite Matching (Kuhn's Algorithm)
// ═══════════════════════════════════════════════════════════════════════════

int maxBipartiteMatching(int n, int m, vector<vector<int>>& adj) {
    // n = left side vertices, m = right side vertices
    // adj[u] = right side neighbors of left vertex u
    
    vector<int> match(m, -1);  // match[v] = which left vertex v is matched to
    
    function<bool(int, vector<bool>&)> dfs = [&](int u, vector<bool>& visited) -> bool {
        for (int v : adj[u]) {
            if (visited[v]) continue;
            visited[v] = true;
            
            // If v is unmatched or we can find alternate path
            if (match[v] == -1 || dfs(match[v], visited)) {
                match[v] = u;
                return true;
            }
        }
        return false;
    };
    
    int matching = 0;
    for (int u = 0; u < n; u++) {
        vector<bool> visited(m, false);
        if (dfs(u, visited)) {
            matching++;
        }
    }
    
    return matching;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Bipartite Module ===\n\n";
    
    // Test Is Bipartite
    vector<vector<int>> graph1 = {{1,3},{0,2},{1,3},{0,2}};
    cout << "1. Is bipartite (square): " << (isBipartiteBFS(graph1) ? "Yes" : "No") << "\n";
    
    vector<vector<int>> graph2 = {{1,2,3},{0,2},{0,1,3},{0,2}};
    cout << "   Is bipartite (triangle): " << (isBipartiteBFS(graph2) ? "Yes" : "No") << "\n";
    
    // Test Possible Bipartition
    vector<vector<int>> dislikes = {{1,2},{1,3},{2,4}};
    cout << "2. Possible bipartition: " << (possibleBipartition(4, dislikes) ? "Yes" : "No") << "\n";
    
    // Test Maximum Matching
    vector<vector<int>> adj = {{0,1},{0},{1,2}};  // 3 left vertices, 3 right vertices
    cout << "3. Max matching: " << maxBipartiteMatching(3, 3, adj) << "\n";
    
    return 0;
}

/*
================================================================================
                    BIPARTITE SUMMARY
================================================================================

1. CHECK BIPARTITE:
   - 2-color using BFS/DFS
   - Conflict (same color neighbors) = not bipartite

2. PROPERTIES:
   - No odd-length cycles
   - Can partition into two independent sets

3. MAXIMUM MATCHING:
   - Kuhn's algorithm (Hungarian)
   - For each left vertex, try to find augmenting path

================================================================================
*/

