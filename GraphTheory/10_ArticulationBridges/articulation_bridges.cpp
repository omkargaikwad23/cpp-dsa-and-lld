/*
================================================================================
                    ARTICULATION POINTS & BRIDGES
================================================================================

ARTICULATION POINT: Vertex whose removal disconnects graph
BRIDGE: Edge whose removal disconnects graph

Uses Tarjan's low-link values | O(V + E)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Find Bridges (Critical Edges) ⭐
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<int>> findBridges(int n, vector<vector<int>>& adj) {
    vector<int> disc(n, -1), low(n);
    vector<vector<int>> bridges;
    int timer = 0;
    
    function<void(int, int)> dfs = [&](int u, int parent) {
        disc[u] = low[u] = timer++;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                // Bridge condition: no back edge from v's subtree to u or above
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };
    
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) dfs(i, -1);
    }
    
    return bridges;
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Find Articulation Points
// ═══════════════════════════════════════════════════════════════════════════

vector<int> findArticulationPoints(int n, vector<vector<int>>& adj) {
    vector<int> disc(n, -1), low(n);
    vector<bool> isAP(n, false);
    int timer = 0;
    
    function<void(int, int)> dfs = [&](int u, int parent) {
        disc[u] = low[u] = timer++;
        int children = 0;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (disc[v] == -1) {
                children++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                // AP condition 1: Root with 2+ children
                if (parent == -1 && children > 1) {
                    isAP[u] = true;
                }
                // AP condition 2: Non-root where no back edge goes above u
                if (parent != -1 && low[v] >= disc[u]) {
                    isAP[u] = true;
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };
    
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) dfs(i, -1);
    }
    
    vector<int> result;
    for (int i = 0; i < n; i++) {
        if (isAP[i]) result.push_back(i);
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM: Critical Connections in Network (LeetCode 1192) ⭐
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto& c : connections) {
        adj[c[0]].push_back(c[1]);
        adj[c[1]].push_back(c[0]);
    }
    
    vector<int> disc(n, -1), low(n);
    vector<vector<int>> bridges;
    int timer = 0;
    
    function<void(int, int)> dfs = [&](int u, int parent) {
        disc[u] = low[u] = timer++;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };
    
    dfs(0, -1);
    return bridges;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Articulation Points & Bridges Module ===\n\n";
    
    // Build graph
    int n = 5;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edges = {{0,1},{0,2},{1,2},{1,3},{3,4}};
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Find bridges
    auto bridges = findBridges(n, adj);
    cout << "1. Bridges: ";
    for (auto& b : bridges) cout << "[" << b[0] << "," << b[1] << "] ";
    cout << "\n";
    
    // Find articulation points
    auto aps = findArticulationPoints(n, adj);
    cout << "2. Articulation points: ";
    for (int ap : aps) cout << ap << " ";
    cout << "\n";
    
    // Test LeetCode problem
    vector<vector<int>> conns = {{0,1},{1,2},{2,0},{1,3}};
    auto critical = criticalConnections(4, conns);
    cout << "3. Critical connections: ";
    for (auto& c : critical) cout << "[" << c[0] << "," << c[1] << "] ";
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                    SUMMARY
================================================================================

1. BRIDGE CONDITION:
   - Edge (u,v) is bridge if low[v] > disc[u]
   - No back edge from v's subtree reaches u or above

2. ARTICULATION POINT CONDITIONS:
   - Root: Has 2+ children in DFS tree
   - Non-root: low[v] >= disc[u] for some child v

3. KEY INSIGHT:
   - low[u] = min discovery time reachable from u's subtree
   - If low[v] >= disc[u], v can't reach above u without going through u

================================================================================
*/

