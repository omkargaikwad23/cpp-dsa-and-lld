/*
================================================================================
                    STRONGLY CONNECTED COMPONENTS (SCC)
================================================================================

SCC: Maximal set of vertices where every vertex is reachable from every other.

KOSARAJU'S: Two DFS passes | O(V + E)
TARJAN'S: Single DFS with low-link values | O(V + E)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 1: Kosaraju's Algorithm ⭐
// ═══════════════════════════════════════════════════════════════════════════

int kosarajuSCC(int n, vector<vector<int>>& adj) {
    // Build reverse graph
    vector<vector<int>> radj(n);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            radj[v].push_back(u);
        }
    }
    
    // First DFS: Get finishing order
    vector<bool> visited(n, false);
    stack<int> order;
    
    function<void(int)> dfs1 = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) dfs1(v);
        }
        order.push(u);
    };
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i);
    }
    
    // Second DFS: On reversed graph in finishing order
    fill(visited.begin(), visited.end(), false);
    int sccCount = 0;
    
    function<void(int)> dfs2 = [&](int u) {
        visited[u] = true;
        for (int v : radj[u]) {
            if (!visited[v]) dfs2(v);
        }
    };
    
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (!visited[u]) {
            dfs2(u);
            sccCount++;
        }
    }
    
    return sccCount;
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 2: Tarjan's Algorithm
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<int>> tarjanSCC(int n, vector<vector<int>>& adj) {
    vector<int> disc(n, -1), low(n), sccId(n, -1);
    vector<bool> onStack(n, false);
    stack<int> stk;
    int timer = 0, numSCC = 0;
    vector<vector<int>> sccs;
    
    function<void(int)> dfs = [&](int u) {
        disc[u] = low[u] = timer++;
        stk.push(u);
        onStack[u] = true;
        
        for (int v : adj[u]) {
            if (disc[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (onStack[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
        
        // Root of SCC
        if (low[u] == disc[u]) {
            vector<int> scc;
            while (true) {
                int v = stk.top();
                stk.pop();
                onStack[v] = false;
                sccId[v] = numSCC;
                scc.push_back(v);
                if (v == u) break;
            }
            sccs.push_back(scc);
            numSCC++;
        }
    };
    
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) dfs(i);
    }
    
    return sccs;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM: Make Graph Strongly Connected
// Min edges to add to make graph strongly connected = max(sources, sinks)
// ═══════════════════════════════════════════════════════════════════════════

int minEdgesToMakeSCC(int n, vector<vector<int>>& adj) {
    auto sccs = tarjanSCC(n, adj);
    int numSCC = sccs.size();
    
    if (numSCC == 1) return 0;
    
    // Build condensation graph and count in/out degrees
    vector<int> sccId(n);
    for (int i = 0; i < numSCC; i++) {
        for (int v : sccs[i]) {
            sccId[v] = i;
        }
    }
    
    vector<int> inDeg(numSCC, 0), outDeg(numSCC, 0);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (sccId[u] != sccId[v]) {
                outDeg[sccId[u]]++;
                inDeg[sccId[v]]++;
            }
        }
    }
    
    int sources = 0, sinks = 0;
    for (int i = 0; i < numSCC; i++) {
        if (inDeg[i] == 0) sources++;
        if (outDeg[i] == 0) sinks++;
    }
    
    return max(sources, sinks);
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== SCC Module ===\n\n";
    
    // Test Kosaraju
    vector<vector<int>> adj = {{1}, {2}, {0,3}, {4}, {5,7}, {6}, {4,7}, {}};
    cout << "1. Kosaraju SCC count: " << kosarajuSCC(8, adj) << "\n";
    
    // Test Tarjan
    auto sccs = tarjanSCC(8, adj);
    cout << "2. Tarjan SCCs: " << sccs.size() << "\n";
    for (int i = 0; i < sccs.size(); i++) {
        cout << "   SCC " << i << ": ";
        for (int v : sccs[i]) cout << v << " ";
        cout << "\n";
    }
    
    return 0;
}

/*
================================================================================
                    SCC SUMMARY
================================================================================

1. KOSARAJU'S (Easier to understand):
   - DFS on original graph → get finish order
   - DFS on reversed graph in reverse finish order
   - Each DFS in step 2 = one SCC

2. TARJAN'S (Single pass):
   - Use disc[] and low[] arrays
   - low[u] = min discovery time reachable from u
   - u is SCC root if low[u] == disc[u]

3. APPLICATIONS:
   - 2-SAT problem
   - Finding strongly connected regions
   - Graph condensation

================================================================================
*/

