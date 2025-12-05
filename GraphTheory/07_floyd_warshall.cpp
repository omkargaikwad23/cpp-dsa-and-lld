/*
================================================================================
                    FLOYD-WARSHALL ALGORITHM
================================================================================

USE WHEN:
- All-pairs shortest path
- Small graphs (V ≤ 400)
- Need distance between ANY two nodes

TIME: O(V³)
SPACE: O(V²)

Explanation:
 - dist[i][j] = shortest distance from node i to node j
 - n = number of nodes
 - edges = list of edges
 - k = intermediate node
 - i = source node
 - j = destination node

 Time Complexity: O(V³)
 Space Complexity: O(V²)

 Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]]
 Output: [[0,3,4,5],[3,0,1,2],[4,1,0,1],[5,2,1,0]]

 Example:
 
 0 --- 1 --- 3
  \   /
   \ /
    2

 Explanation:
 The shortest path from node 0 to node 3 is 5 (0 -> 1 -> 3).
 The shortest path from node 1 to node 2 is 1 (1 -> 2).
 The shortest path from node 1 to node 3 is 2 (1 -> 3).
 The shortest path from node 2 to node 3 is 1 (2 -> 3).

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Floyd-Warshall
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<int>> floydWarshall(int n, vector<vector<int>>& edges) {
    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    // Distance to self = 0
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    
    // Add edges
    for (auto& e : edges) {
        dist[e[0]][e[1]] = e[2];
        // For undirected: dist[e[1]][e[0]] = e[2];
    }
    
    // Floyd-Warshall: try each node as intermediate
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    return dist;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Find the City With Smallest Number of Neighbors (LeetCode 1334)
// ═══════════════════════════════════════════════════════════════════════════

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& e : edges) {
        dist[e[0]][e[1]] = dist[e[1]][e[0]] = e[2];
    }
    
    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    int result = 0, minReachable = n;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] <= distanceThreshold) count++;
        }
        if (count <= minReachable) {
            minReachable = count;
            result = i;
        }
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Shortest Path Visiting All Nodes (LeetCode 847)
// Bitmask DP variation
// ═══════════════════════════════════════════════════════════════════════════

int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();
    int fullMask = (1 << n) - 1;
    
    // BFS with state (mask, node)
    queue<tuple<int, int, int>> q;  // mask, node, dist
    set<pair<int,int>> visited;
    
    for (int i = 0; i < n; i++) {
        int mask = 1 << i;
        q.push({mask, i, 0});
        visited.insert({mask, i});
    }
    
    while (!q.empty()) {
        auto [mask, node, dist] = q.front();
        q.pop();
        
        if (mask == fullMask) return dist;
        
        for (int next : graph[node]) {
            int newMask = mask | (1 << next);
            if (!visited.count({newMask, next})) {
                visited.insert({newMask, next});
                q.push({newMask, next, dist + 1});
            }
        }
    }
    
    return -1;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Course Schedule IV (LeetCode 1462)
// Check if course i is prerequisite of course j
// ═══════════════════════════════════════════════════════════════════════════

vector<bool> checkIfPrerequisite(int n, vector<vector<int>>& prerequisites, 
                                  vector<vector<int>>& queries) {
    // Transitive closure using Floyd-Warshall
    vector<vector<bool>> reachable(n, vector<bool>(n, false));
    
    for (auto& p : prerequisites) {
        reachable[p[0]][p[1]] = true;
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                reachable[i][j] = reachable[i][j] || 
                                  (reachable[i][k] && reachable[k][j]);
            }
        }
    }
    
    vector<bool> result;
    for (auto& q : queries) {
        result.push_back(reachable[q[0]][q[1]]);
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// Detect Negative Cycle using Floyd-Warshall
// ═══════════════════════════════════════════════════════════════════════════

bool hasNegativeCycle(int n, vector<vector<int>>& edges) {
    vector<vector<int>> dist(n, vector<int>(n, INF));
    
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& e : edges) {
        dist[e[0]][e[1]] = e[2];
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Negative cycle exists if dist[i][i] < 0
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) return true;
    }
    
    return false;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Floyd-Warshall Module ===\n\n";
    
    // Test Find City
    vector<vector<int>> edges1 = {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    cout << "1. City with least neighbors: " << findTheCity(4, edges1, 4) << "\n";
    
    // Test Shortest Path Visiting All
    vector<vector<int>> graph = {{1,2,3},{0},{0},{0}};
    cout << "2. Shortest path all nodes: " << shortestPathLength(graph) << "\n";
    
    return 0;
}

/*
================================================================================
                    FLOYD-WARSHALL SUMMARY
================================================================================

1. ALL-PAIRS SHORTEST PATH:
   for (k = 0 to n-1)  // intermediate node
     for (i = 0 to n-1)
       for (j = 0 to n-1)
         dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

2. TRANSITIVE CLOSURE:
   - Same pattern but with boolean OR
   - reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j])

3. NEGATIVE CYCLE:
   - After algorithm, check if dist[i][i] < 0

4. WHEN TO USE:
   - Small graphs (n ≤ 400)
   - Need all-pairs distances
   - Multiple queries for shortest paths

================================================================================
*/

