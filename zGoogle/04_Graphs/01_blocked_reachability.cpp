/*
================================================================================
            BLOCKED NODE REACHABILITY (Google Interview)
================================================================================

PROBLEM:
Given a graph, source, destination, and a blocked node:

Part 1: Can you reach destination from source avoiding the blocked node?
Part 2: Find shortest distances from source to all nodes (avoiding blocked)
Part 3: If blocked node ALSO blocks its neighbors, can you still reach?

================================================================================
                         EXAMPLES
================================================================================

Graph: 0--1--2--3--4
Source: 0, Dest: 4, Blocked: 2

Part 1: Can reach? NO (node 2 blocks the only path)
Part 2: Distances: {0:0, 1:1, 2:INF, 3:INF, 4:INF}
Part 3: Blocked=2 also blocks {1,3}, so 0 can only reach itself

================================================================================
                         APPROACH
================================================================================

All parts use BFS from source, but with different blocking conditions:
- Part 1: Skip blocked node during traversal
- Part 2: Same, but compute all distances
- Part 3: First collect all blocked nodes (blocked + its neighbors)

TIME:  O(V + E) - standard BFS
SPACE: O(V) - visited set + queue + distances

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
    unordered_map<int, vector<int>> graph;
    
public:
    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // PART 1: Can reach destination avoiding blocked node?
    // ═══════════════════════════════════════════════════════════════════════
    
    bool canReach(int src, int dest, int blocked) {
        if (src == blocked || dest == blocked) return false;
        
        unordered_set<int> visited;
        queue<int> q;
        
        q.push(src);
        visited.insert(src);
        visited.insert(blocked);  // Treat blocked as already visited
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            if (curr == dest) return true;
            
            for (int neighbor : graph[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        
        return false;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // PART 2: Shortest distance from source to all nodes
    // ═══════════════════════════════════════════════════════════════════════
    
    unordered_map<int, int> shortestDistances(int src, int blocked) {
        unordered_map<int, int> dist;
        
        // Initialize all distances to infinity
        for (auto& [node, _] : graph) {
            dist[node] = INT_MAX;
        }
        
        if (src == blocked) return dist;
        
        queue<int> q;
        q.push(src);
        dist[src] = 0;
        
        unordered_set<int> visited;
        visited.insert(src);
        visited.insert(blocked);
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            for (int neighbor : graph[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    dist[neighbor] = dist[curr] + 1;
                    q.push(neighbor);
                }
            }
        }
        
        return dist;
    }
    
    // ═══════════════════════════════════════════════════════════════════════
    // PART 3: Blocked node also blocks its neighbors
    // ═══════════════════════════════════════════════════════════════════════
    
    bool canReachWithNeighborsBlocked(int src, int dest, int blocked) {
        // Build blocked set: blocked node + all its neighbors
        unordered_set<int> blockedSet;
        blockedSet.insert(blocked);
        for (int neighbor : graph[blocked]) {
            blockedSet.insert(neighbor);
        }
        
        if (blockedSet.count(src) || blockedSet.count(dest)) {
            return false;
        }
        
        // BFS avoiding all blocked nodes
        unordered_set<int> visited = blockedSet;  // Start with blocked
        queue<int> q;
        q.push(src);
        visited.insert(src);
        
        while (!q.empty()) {
            int curr = q.front();
            q.pop();
            
            if (curr == dest) return true;
            
            for (int neighbor : graph[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        
        return false;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    Solution sol;
    
    // Build graph: 0--1--2--3--4
    sol.addEdge(0, 1);
    sol.addEdge(1, 2);
    sol.addEdge(2, 3);
    sol.addEdge(3, 4);
    
    int src = 0, dest = 4, blocked = 2;
    
    cout << "Graph: 0--1--2--3--4\n";
    cout << "Source: " << src << ", Dest: " << dest << ", Blocked: " << blocked << "\n\n";
    
    // Part 1
    cout << "Part 1: Can reach " << dest << "? " 
         << (sol.canReach(src, dest, blocked) ? "YES" : "NO") << "\n";
    
    // Part 2
    cout << "\nPart 2: Shortest distances from " << src << ":\n";
    auto dist = sol.shortestDistances(src, blocked);
    for (auto& [node, d] : dist) {
        cout << "  Node " << node << ": " << (d == INT_MAX ? -1 : d) << "\n";
    }
    
    // Part 3
    cout << "\nPart 3: Can reach with neighbors blocked? "
         << (sol.canReachWithNeighborsBlocked(src, dest, blocked) ? "YES" : "NO") << "\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

All parts:
TIME:  O(V + E) - BFS visits each vertex and edge once
SPACE: O(V) - visited set, queue, distance map

FOLLOW-UP QUESTIONS:
1. What if multiple nodes are blocked? → Use set of blocked nodes
2. What if blocks are dynamic (added/removed)? → Consider Union-Find
3. What if we need the shortest path itself? → Track parent pointers

================================================================================
*/

