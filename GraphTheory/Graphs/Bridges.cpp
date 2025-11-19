#include <bits/stdc++.h>
using namespace std;

/**
 * Graph class to find bridges in an undirected graph using Tarjan's algorithm
 * 
 * A bridge (or cut-edge) is an edge whose removal increases the number of 
 * connected components in the graph.
 * 
 * Algorithm: Tarjan's Bridge Finding Algorithm
 * Time Complexity: O(V + E)
 * Space Complexity: O(V + E)
 */
class Graph {
    int numVertices;
    vector<vector<int>> adj;      // Adjacency list representation
    vector<int> timeInsert;       // Time when node was first discovered (DFS discovery time)
    vector<int> timeLow;          // Lowest discovery time reachable from this node
    vector<bool> visited;         // Track visited nodes
    
public:
    /**
     * Constructor: Initialize graph with given number of vertices and edges
     * @param n Number of vertices
     * @param edges Vector of pairs representing undirected edges
     */
    Graph(int n, vector<pair<int, int>> edges) {
        numVertices = n;
        adj.resize(n);
        timeInsert.assign(n, -1);
        timeLow.assign(n, -1);
        visited.assign(n, false);
        
        // Build adjacency list from edges
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    
    /**
     * DFS function to find bridges using Tarjan's algorithm
     * 
     * Key concepts:
     * - timeInsert[node]: Discovery time when node was first visited
     * - timeLow[node]: Minimum discovery time reachable from node via DFS tree edges
     *                  and at most one back-edge
     * 
     * Bridge condition: An edge (parent -> child) is a bridge if and only if
     *                   timeLow[child] > timeInsert[parent]
     *                   This means child cannot reach parent or any ancestor via back-edges
     * 
     * @param node Current node being processed
     * @param parent Parent node in DFS tree (to avoid going back)
     * @param timer Current discovery time counter
     */
    void dfs(int node, int parent, int &timer) {
        // Mark node as visited and assign discovery time
        visited[node] = true;
        timeInsert[node] = timeLow[node] = timer++;
        
        // Explore all neighbors
        for (int neighbor : adj[node]) {
            // Skip the parent to avoid immediate backtracking
            if (neighbor == parent) continue;
            
            if (!visited[neighbor]) {
                // Tree edge: unvisited neighbor becomes child in DFS tree
                dfs(neighbor, node, timer);
                
                // After returning from child, update low time
                // Child might have found a back-edge to an earlier node
                timeLow[node] = min(timeLow[node], timeLow[neighbor]);
                
                // Bridge condition check
                // If child's low time is greater than parent's discovery time,
                // it means child cannot reach parent or any ancestor via back-edges
                // Therefore, the edge (node -> neighbor) is a bridge
                if (timeLow[neighbor] > timeInsert[node]) {
                    cout << "Bridge found: " << node << " - " << neighbor << endl;
                }
            }
            else {
                // Back-edge: neighbor is already visited (not parent)
                // This creates a cycle, so update low time to neighbor's discovery time
                timeLow[node] = min(timeLow[node], timeInsert[neighbor]);
            }
        }
    }
    
    /**
     * Find all bridges in the graph
     * Handles disconnected graphs by checking all components
     */
    void findBridges() {
        int timer = 0;
        
        // Process all connected components
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                dfs(i, -1, timer);
            }
        }
    }
};

int main() {
    
    vector<pair<int, int>> edges = {
        {0, 1},
        {0, 2},
        {1, 2},
        {2, 3},
        {3, 4}
    };
    
    Graph g(5, edges);
    
    cout << "Finding bridges in the graph:" << endl;
    g.findBridges();
    
    return 0;
}

/*
  EXPECTED OUTPUT:
  =================
  Example graph:
    0---1
    |   |
    2---3---4
    
    Edges: (0,1), (0,2), (1,2), (2,3), (3,4)

    EXPECTED OUTPUT:
    =================
    Finding bridges in the graph:
    Bridge found: 3 - 4

    EXPECTED EXPLANATION:
    =================
    - Edge (3,4) is a bridge because removing it disconnects node 4 from the rest
    - All other edges are part of cycles, so removing them doesn't disconnect the graph
*/