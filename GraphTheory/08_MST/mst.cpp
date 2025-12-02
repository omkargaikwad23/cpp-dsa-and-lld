/*
================================================================================
                    MINIMUM SPANNING TREE (MST)
================================================================================

MST: Connects all vertices with minimum total edge weight, no cycles.

KRUSKAL'S: Sort edges + Union-Find | O(E log E)
PRIM'S: Priority Queue from any node | O(E log V)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// Union-Find for Kruskal's
// ═══════════════════════════════════════════════════════════════════════════

class DSU {
public:
    vector<int> parent, rank_;
    DSU(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
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


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 1: Kruskal's Algorithm ⭐
// ═══════════════════════════════════════════════════════════════════════════

int kruskalMST(int n, vector<vector<int>>& edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
        return a[2] < b[2];
    });
    
    DSU dsu(n);
    int mstWeight = 0;
    int edgesUsed = 0;
    
    for (auto& e : edges) {
        if (dsu.unite(e[0], e[1])) {
            mstWeight += e[2];
            edgesUsed++;
            if (edgesUsed == n - 1) break;  // MST complete
        }
    }
    
    return edgesUsed == n - 1 ? mstWeight : -1;  // -1 if not connected
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 2: Prim's Algorithm ⭐
// ═══════════════════════════════════════════════════════════════════════════

int primMST(int n, vector<vector<pair<int,int>>>& adj) {
    vector<bool> inMST(n, false);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    
    pq.push({0, 0});  // {weight, node}
    int mstWeight = 0;
    int edgesUsed = 0;
    
    while (!pq.empty() && edgesUsed < n) {
        auto [w, u] = pq.top();
        pq.pop();
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        mstWeight += w;
        edgesUsed++;
        
        for (auto [v, weight] : adj[u]) {
            if (!inMST[v]) {
                pq.push({weight, v});
            }
        }
    }
    
    return edgesUsed == n ? mstWeight : -1;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Min Cost to Connect All Points (LeetCode 1584) ⭐
// ═══════════════════════════════════════════════════════════════════════════

int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    
    // Prim's with optimized approach
    vector<int> minDist(n, INT_MAX);
    vector<bool> inMST(n, false);
    minDist[0] = 0;
    
    int totalCost = 0;
    
    for (int i = 0; i < n; i++) {
        // Find min distance node not in MST
        int u = -1;
        for (int j = 0; j < n; j++) {
            if (!inMST[j] && (u == -1 || minDist[j] < minDist[u])) {
                u = j;
            }
        }
        
        inMST[u] = true;
        totalCost += minDist[u];
        
        // Update distances
        for (int v = 0; v < n; v++) {
            if (!inMST[v]) {
                int dist = abs(points[u][0] - points[v][0]) + 
                           abs(points[u][1] - points[v][1]);
                minDist[v] = min(minDist[v], dist);
            }
        }
    }
    
    return totalCost;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Connecting Cities With Minimum Cost (LeetCode 1135)
// ═══════════════════════════════════════════════════════════════════════════

int minimumCost(int n, vector<vector<int>>& connections) {
    sort(connections.begin(), connections.end(), [](auto& a, auto& b) {
        return a[2] < b[2];
    });
    
    DSU dsu(n + 1);
    int cost = 0, edges = 0;
    
    for (auto& c : connections) {
        if (dsu.unite(c[0], c[1])) {
            cost += c[2];
            edges++;
            if (edges == n - 1) return cost;
        }
    }
    
    return -1;  // Not all cities connected
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Find Critical and Pseudo-Critical Edges (LeetCode 1489)
// ═══════════════════════════════════════════════════════════════════════════

class Solution1489 {
    int findMST(int n, vector<vector<int>>& edges, int exclude, int include) {
        DSU dsu(n);
        int weight = 0, count = 0;
        
        if (include != -1) {
            weight += edges[include][2];
            dsu.unite(edges[include][0], edges[include][1]);
            count++;
        }
        
        for (int i = 0; i < edges.size(); i++) {
            if (i == exclude) continue;
            if (dsu.unite(edges[i][0], edges[i][1])) {
                weight += edges[i][2];
                count++;
            }
        }
        
        return count == n - 1 ? weight : INT_MAX;
    }
    
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // Add index to edges
        for (int i = 0; i < edges.size(); i++) {
            edges[i].push_back(i);
        }
        
        sort(edges.begin(), edges.end(), [](auto& a, auto& b) {
            return a[2] < b[2];
        });
        
        int mstWeight = findMST(n, edges, -1, -1);
        
        vector<int> critical, pseudoCritical;
        
        for (int i = 0; i < edges.size(); i++) {
            // Check if critical (MST weight increases without it)
            if (findMST(n, edges, i, -1) > mstWeight) {
                critical.push_back(edges[i][3]);
            }
            // Check if pseudo-critical (can be in some MST)
            else if (findMST(n, edges, -1, i) == mstWeight) {
                pseudoCritical.push_back(edges[i][3]);
            }
        }
        
        return {critical, pseudoCritical};
    }
};


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== MST Module ===\n\n";
    
    // Test Kruskal
    vector<vector<int>> edges1 = {{0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}};
    cout << "1. Kruskal MST: " << kruskalMST(4, edges1) << "\n";
    
    // Test Min Cost Connect Points
    vector<vector<int>> points = {{0,0},{2,2},{3,10},{5,2},{7,0}};
    cout << "2. Min cost points: " << minCostConnectPoints(points) << "\n";
    
    // Test Connecting Cities
    vector<vector<int>> conns = {{1,2,5},{1,3,6},{2,3,1}};
    cout << "3. Min cost cities: " << minimumCost(3, conns) << "\n";
    
    return 0;
}

/*
================================================================================
                    MST SUMMARY
================================================================================

1. KRUSKAL'S:
   - Sort edges by weight
   - Add edge if it doesn't create cycle (Union-Find)
   - Stop when n-1 edges added

2. PRIM'S:
   - Start from any node
   - Always add min weight edge to MST
   - Use priority queue for efficiency

3. WHEN TO USE:
   - Kruskal: Sparse graphs, edge list given
   - Prim: Dense graphs, adjacency list given

================================================================================
*/

