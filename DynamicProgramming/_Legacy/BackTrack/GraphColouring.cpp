/*
================================================================================
GRAPH COLORING using M Colors (Backtracking)
================================================================================

Problem: Assign colors to graph nodes such that no two adjacent nodes 
         have the same color. Use at most M colors.

Approach: Backtracking
- Try each color (1 to M) for current node
- If valid (no adjacent node has same color), recurse to next node
- If stuck, backtrack and try different color

Time: O(M^N) - for each of N nodes, try M colors
Space: O(N) - color array + recursion stack

Applications:
- Map coloring (countries sharing border need different colors)
- Scheduling (conflicting tasks need different time slots)
- Register allocation in compilers

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
────────────────────────────────────────────────────────────────────────────────
GRAPH COLORING CLASS
────────────────────────────────────────────────────────────────────────────────
*/
class GraphColoring {
private:
    int n;                      // Number of nodes
    vector<vector<int>> adj;    // Adjacency list
    vector<int> color;          // Color assigned to each node (0 = uncolored)
    
    // Check if assigning 'col' to 'node' is valid
    bool isSafe(int node, int col) {
        for (int neighbor : adj[node]) {
            if (color[neighbor] == col) {
                return false;  // Adjacent node has same color!
            }
        }
        return true;
    }
    
    // Backtracking: try to color node and all subsequent nodes
    bool solve(int node, int m) {
        // Base case: all nodes colored successfully
        if (node == n) return true;
        
        // Try each color from 1 to m
        for (int col = 1; col <= m; col++) {
            if (isSafe(node, col)) {
                color[node] = col;              // Assign color
                
                if (solve(node + 1, m)) {       // Recurse to next node
                    return true;
                }
                
                color[node] = 0;                // Backtrack: remove color
            }
        }
        
        return false;  // No valid coloring found
    }
    
public:
    // Constructor with adjacency list
    GraphColoring(int n, vector<vector<int>>& adjList) 
        : n(n), adj(adjList), color(n, 0) {}
    
    // Try to color graph with at most m colors
    vector<int> colorGraph(int m) {
        color.assign(n, 0);  // Reset colors
        
        if (solve(0, m)) {
            return color;    // Return valid coloring
        }
        return {};           // No solution exists
    }
    
    // Print the coloring result
    void printColoring(const vector<int>& result) {
        if (result.empty()) {
            cout << "Graph cannot be colored with given number of colors!\n";
            return;
        }
        
        cout << "Coloring is possible:\n";
        for (int i = 0; i < n; i++) {
            cout << "  Node " << i << " → Color " << result[i] << "\n";
        }
    }
};


int main() {
    cout << "=== Graph Coloring (Backtracking) ===\n\n";
    
    /*
    Example 1: Simple graph (4 nodes)
    
        0 --- 1
        | \   |
        |   \ |
        3 --- 2
        
    Edges: 0-1, 0-2, 0-3, 1-2, 2-3
    */
    {
        cout << "Example 1: 4-node graph\n";
        cout << "Edges: 0-1, 0-2, 0-3, 1-2, 2-3\n\n";
        
        int n = 4;
        vector<vector<int>> adj(n);
        
        // Add edges (undirected)
        auto addEdge = [&](int u, int v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        };
        
        addEdge(0, 1);
        addEdge(0, 2);
        addEdge(0, 3);
        addEdge(1, 2);
        addEdge(2, 3);
        
        GraphColoring gc(n, adj);
        
        // Try with 2 colors
        cout << "With M = 2 colors:\n";
        gc.printColoring(gc.colorGraph(2));
        
        // Try with 3 colors
        cout << "\nWith M = 3 colors:\n";
        gc.printColoring(gc.colorGraph(3));
    }
    
    cout << "\n" << string(60, '-') << "\n\n";
    
    /*
    Example 2: Complete graph K4 (every node connected to every other)
    Needs exactly 4 colors (chromatic number = 4)
    
        0 --- 1
        |\ /| 
        | X |
        |/ \|
        3 --- 2
    */
    {
        cout << "Example 2: Complete graph K4 (all pairs connected)\n\n";
        
        int n = 4;
        vector<vector<int>> adj(n);
        
        // Complete graph: every node connected to every other
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
        
        GraphColoring gc(n, adj);
        
        cout << "With M = 3 colors:\n";
        gc.printColoring(gc.colorGraph(3));
        
        cout << "\nWith M = 4 colors:\n";
        gc.printColoring(gc.colorGraph(4));
    }
    
    cout << "\n" << string(60, '-') << "\n\n";
    
    /*
    Example 3: Bipartite graph (can be colored with 2 colors)
    
        0 --- 2
        |     |
        1 --- 3
    */
    {
        cout << "Example 3: Bipartite graph (cycle of 4)\n\n";
        
        int n = 4;
        vector<vector<int>> adj(n);
        
        adj[0].push_back(2); adj[2].push_back(0);
        adj[0].push_back(1); adj[1].push_back(0);
        adj[1].push_back(3); adj[3].push_back(1);
        adj[2].push_back(3); adj[3].push_back(2);
        
        GraphColoring gc(n, adj);
        
        cout << "With M = 2 colors:\n";
        gc.printColoring(gc.colorGraph(2));
    }
    
    return 0;
}

/*
================================================================================
OUTPUT
================================================================================

Example 1: 4-node graph
Edges: 0-1, 0-2, 0-3, 1-2, 2-3

With M = 2 colors:
Graph cannot be colored with given number of colors!

With M = 3 colors:
Coloring is possible:
  Node 0 → Color 1
  Node 1 → Color 2
  Node 2 → Color 3
  Node 3 → Color 2

------------------------------------------------------------

Example 2: Complete graph K4 (all pairs connected)

With M = 3 colors:
Graph cannot be colored with given number of colors!

With M = 4 colors:
Coloring is possible:
  Node 0 → Color 1
  Node 1 → Color 2
  Node 2 → Color 3
  Node 3 → Color 4

------------------------------------------------------------

Example 3: Bipartite graph (cycle of 4)

With M = 2 colors:
Coloring is possible:
  Node 0 → Color 1
  Node 1 → Color 2
  Node 2 → Color 2
  Node 3 → Color 1

================================================================================
KEY INSIGHT: Chromatic Number
================================================================================

The minimum colors needed to color a graph is called its CHROMATIC NUMBER.

- Bipartite graph: 2 colors (nodes can be split into 2 groups)
- Odd cycle: 3 colors
- Complete graph Kn: n colors (every node is adjacent to every other)
- Planar graph: at most 4 colors (Four Color Theorem)

================================================================================
*/
