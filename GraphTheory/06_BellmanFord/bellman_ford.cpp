/*
================================================================================
                    BELLMAN-FORD ALGORITHM
================================================================================

USE WHEN:
- Shortest path with NEGATIVE weights
- Detecting negative cycles
- Limited number of edges/stops (K stops)

TIME: O(V * E)
SPACE: O(V)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Standard Bellman-Ford
// ═══════════════════════════════════════════════════════════════════════════

pair<vector<long long>, bool> bellmanFord(int n, int start, 
                                          vector<tuple<int,int,int>>& edges) {
    vector<long long> dist(n, LLONG_MAX);
    dist[start] = 0;
    
    // Relax all edges (n-1) times
    for (int i = 0; i < n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // Check for negative cycle (one more iteration)
    bool hasNegativeCycle = false;
    for (auto [u, v, w] : edges) {
        if (dist[u] != LLONG_MAX && dist[u] + w < dist[v]) {
            hasNegativeCycle = true;
            break;
        }
    }
    
    return {dist, hasNegativeCycle};
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Bellman-Ford with K Relaxations (K edges/stops)
// ═══════════════════════════════════════════════════════════════════════════

vector<int> bellmanFordKStops(int n, int start, vector<vector<int>>& edges, int k) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;
    
    // Relax exactly k+1 times (k stops = k+1 edges)
    for (int i = 0; i <= k; i++) {
        vector<int> temp = dist;  // Use previous iteration's values
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dist[u] != INT_MAX) {
                temp[v] = min(temp[v], dist[u] + w);
            }
        }
        dist = temp;
    }
    
    return dist;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Cheapest Flights Within K Stops (LeetCode 787) ⭐ GOOGLE FAVORITE
// ═══════════════════════════════════════════════════════════════════════════

int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    
    // k stops = k+1 edges, so iterate k+1 times
    for (int i = 0; i <= k; i++) {
        vector<int> temp = dist;
        for (auto& f : flights) {
            int u = f[0], v = f[1], w = f[2];
            if (dist[u] != INT_MAX) {
                temp[v] = min(temp[v], dist[u] + w);
            }
        }
        dist = temp;
    }
    
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Detect Negative Cycle
// ═══════════════════════════════════════════════════════════════════════════

bool hasNegativeCycle(int n, vector<tuple<int,int,int>>& edges) {
    vector<long long> dist(n, 0);  // Start from 0 to detect any reachable cycle
    
    for (int i = 0; i < n - 1; i++) {
        for (auto [u, v, w] : edges) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }
    
    // Check for negative cycle
    for (auto [u, v, w] : edges) {
        if (dist[u] + w < dist[v]) {
            return true;
        }
    }
    
    return false;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Shortest Path with Exactly K Edges
// ═══════════════════════════════════════════════════════════════════════════

int shortestPathKEdges(int n, vector<vector<int>>& edges, int src, int dst, int k) {
    // dp[i] = min distance to node i using exactly current number of edges
    vector<int> dp(n, INT_MAX);
    dp[src] = 0;
    
    for (int i = 0; i < k; i++) {
        vector<int> newDp(n, INT_MAX);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            if (dp[u] != INT_MAX) {
                newDp[v] = min(newDp[v], dp[u] + w);
            }
        }
        dp = newDp;
    }
    
    return dp[dst] == INT_MAX ? -1 : dp[dst];
}


// ═══════════════════════════════════════════════════════════════════════════
// SPFA (Shortest Path Faster Algorithm) - Optimized Bellman-Ford
// ═══════════════════════════════════════════════════════════════════════════

vector<long long> spfa(int n, int start, vector<vector<pair<int,int>>>& adj) {
    vector<long long> dist(n, LLONG_MAX);
    vector<bool> inQueue(n, false);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    inQueue[start] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inQueue[u] = false;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!inQueue[v]) {
                    q.push(v);
                    inQueue[v] = true;
                }
            }
        }
    }
    
    return dist;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Bellman-Ford Module ===\n\n";
    
    // Test Cheapest Flights
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{0,2,500}};
    cout << "1. Cheapest (k=1): " << findCheapestPrice(3, flights, 0, 2, 1) << "\n";
    cout << "   Cheapest (k=0): " << findCheapestPrice(3, flights, 0, 2, 0) << "\n";
    
    // Test Negative Cycle
    vector<tuple<int,int,int>> edges = {{0,1,1},{1,2,-1},{2,0,-1}};
    cout << "\n2. Has negative cycle: " << (hasNegativeCycle(3, edges) ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
                    BELLMAN-FORD SUMMARY
================================================================================

1. STANDARD:
   - Relax all edges (n-1) times
   - One more iteration detects negative cycle

2. K STOPS/EDGES:
   - Use temp array to prevent using current iteration's updates
   - Iterate exactly k+1 times for k stops

3. vs DIJKSTRA:
   - Bellman-Ford: Works with negative weights
   - Dijkstra: Faster but no negative weights

4. SPFA:
   - Queue-based optimization
   - Average O(E), worst O(V*E)

================================================================================
*/

