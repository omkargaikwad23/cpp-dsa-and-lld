#include <iostream>
#include <vector>
using namespace std;

/*
 * BIPARTITE GRAPH CHECK
 * =====================
 * 
 * Problem: Check if a graph is bipartite.
 * A graph is bipartite if we can color all vertices using 2 colors
 * such that no two adjacent vertices have the same color.
 * 
 * Approach: DFS with 2-coloring
 * - Color each vertex with 0 or 1
 * - Adjacent vertices must have different colors
 * - If we find adjacent vertices with same color, graph is not bipartite
 * 
 * Algorithm:
 * 1. Start DFS from each unvisited vertex
 * 2. Color current vertex (start with 0)
 * 3. Color neighbors with opposite color (!col[node])
 * 4. If neighbor is already colored with same color, return false
 * 
 * Time Complexity: O(V + E) where V = vertices, E = edges
 * Space Complexity: O(V) for color array only
 * 
 * Note: We don't need a separate visited array!
 * The color array serves dual purpose:
 * - col[i] == -1 means unvisited
 * - col[i] == 0 or 1 means visited (with that color)
 * 
 * Example:
 * Graph: 0-1-2
 *         \|/
 *          3
 * This graph is NOT bipartite (odd cycle: 0-1-2-3-0)
 */

class Solution {
    // DFS helper function to check bipartite property
    bool dfs(vector<vector<int>>& graph, int u, vector<int>& col) {
        // Check all neighbors
        for (int v : graph[u]) {
            // If neighbor has same color as current vertex, conflict!
            if (col[v] == col[u]) {
                return false;  // Not bipartite
            }
            
            // If neighbor is unvisited (col[v] == -1)
            if (col[v] == -1) {
                // Color neighbor with opposite color
                col[v] = !col[u];
                // Recursively check neighbor
                if (!dfs(graph, v, col))
                    return false;
            }
        }
        return true;
    }

public:
    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> col(n, -1);  // Color array: -1 = unvisited, 0/1 = colors
        
        // Check each connected component
        for (int i = 0; i < n; i++) {
            if (col[i] == -1) {  // Start DFS for unvisited components
                col[i] = 0;      // Start coloring with 0
                if (!dfs(graph, i, col)) {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    Solution sol;
    
    // Example 1: Bipartite graph (no odd cycles)
    // Graph: 0-1
    //        2-3
    vector<vector<int>> graph1 = {
        {1},      // Node 0 connected to 1
        {0},      // Node 1 connected to 0
        {3},      // Node 2 connected to 3
        {2}       // Node 3 connected to 2
    };
    
    cout << "Example 1: Graph with 2 disconnected edges" << endl;
    cout << "Graph: 0-1, 2-3" << endl;
    cout << "Is Bipartite: " << (sol.isBipartite(graph1) ? "YES" : "NO") << endl;
    cout << "Expected: YES\n" << endl;
    
    // Example 2: NOT bipartite (odd cycle - triangle)
    // Graph: 0-1-2-0 (triangle)
    vector<vector<int>> graph2 = {
        {1, 2},   // Node 0 connected to 1, 2
        {0, 2},   // Node 1 connected to 0, 2
        {0, 1}    // Node 2 connected to 0, 1
    };
    
    cout << "Example 2: Graph with odd cycle (triangle: 0-1-2-0)" << endl;
    cout << "Graph: Triangle (odd cycle of length 3)" << endl;
    cout << "Is Bipartite: " << (sol.isBipartite(graph2) ? "YES" : "NO") << endl;
    cout << "Expected: NO\n" << endl;
    
    // Example 3: Simple bipartite graph
    // Graph: 0-1-2
    vector<vector<int>> graph3 = {
        {1},      // Node 0 connected to 1
        {0, 2},   // Node 1 connected to 0, 2
        {1}       // Node 2 connected to 1
    };
    
    cout << "Example 3: Simple path graph (0-1-2)" << endl;
    cout << "Is Bipartite: " << (sol.isBipartite(graph3) ? "YES" : "NO") << endl;
    cout << "Expected: YES" << endl;
    
    return 0;
}