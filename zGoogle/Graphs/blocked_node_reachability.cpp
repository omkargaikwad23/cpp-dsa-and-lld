/*
Can you reach destination from source if certain nodes are blocked?

Problem:
  Given a graph, source, destination, and a blocked node:
  1. Can you reach destination avoiding the blocked node?
  2. Find shortest distances from source to all nodes (avoiding blocked)
  3. Blocked node also blocks its neighbors - can you still reach?

Example:
  Graph: 0--1--2--3--4
  Source: 0, Dest: 4, Blocked: 2
  
  Part 1: Can reach? NO (2 blocks the only path)
  Part 2: Distances: {0:0, 1:1, 2:INF, 3:INF, 4:INF}
  Part 3: Blocked=2 also blocks {1,3}, so 0 can only reach itself

Approach: BFS from source, skip blocked nodes

Time:  O(V + E) - standard BFS
Space: O(V) - visited set + queue + distances
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
    
    // Part 1: Can reach destination avoiding blocked node?
    bool canReach(int src, int dest, int blocked) {
        if (src == blocked || dest == blocked) return false;
        
        unordered_set<int> visited;
        queue<int> q;
        q.push(src);
        visited.insert(src);
        visited.insert(blocked);  // treat blocked as visited
        
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
    
    // Part 2: Shortest distance from source to all nodes
    unordered_map<int, int> shortestDistances(int src, int blocked) {
        unordered_map<int, int> dist;
        for (auto& [node, _] : graph) dist[node] = INT_MAX;
        
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
    
    // Part 3: Blocked node also blocks its neighbors
    bool canReachWithNeighborsBlocked(int src, int dest, int blocked) {
        unordered_set<int> blockedSet;
        blockedSet.insert(blocked);
        for (int neighbor : graph[blocked]) {
            blockedSet.insert(neighbor);
        }
        
        if (blockedSet.count(src) || blockedSet.count(dest)) return false;
        
        unordered_set<int> visited = blockedSet;  // start with blocked nodes
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

int main() {
    Solution sol;
    
    // Build graph: 0--1--2--3--4
    sol.addEdge(0, 1);
    sol.addEdge(1, 2);
    sol.addEdge(2, 3);
    sol.addEdge(3, 4);
    
    int src = 0, dest = 4, blocked = 2;
    
    // Part 1
    cout << "Can reach " << dest << " from " << src 
         << " (blocked=" << blocked << ")? " 
         << (sol.canReach(src, dest, blocked) ? "YES" : "NO") << "\n";
    
    // Part 2
    cout << "\nShortest distances from " << src << ":\n";
    auto dist = sol.shortestDistances(src, blocked);
    for (auto& [node, d] : dist) {
        cout << "  " << node << ": " << (d == INT_MAX ? -1 : d) << "\n";
    }
    
    // Part 3
    cout << "\nCan reach with neighbors blocked? "
         << (sol.canReachWithNeighborsBlocked(src, dest, blocked) ? "YES" : "NO") << "\n";
    
    return 0;
}

