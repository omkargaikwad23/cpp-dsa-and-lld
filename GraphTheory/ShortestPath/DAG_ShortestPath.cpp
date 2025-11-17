#include <bits/stdc++.h>
using namespace std;

/*
 * SHORTEST PATH IN DIRECTED ACYCLIC GRAPH (DAG)
 * ==============================================
 * 
 * Finds shortest paths from a source vertex to all other vertices in a DAG.
 * Uses topological sorting to process vertices in correct order.
 * 
 * KEY PROPERTIES:
 * - Works ONLY for Directed Acyclic Graphs (no cycles)
 * - Can handle NEGATIVE edge weights (unlike Dijkstra's)
 * - Single-source shortest path algorithm
 * - More efficient than Bellman-Ford for DAGs
 * 
 * ALGORITHM STEPS:
 * 1. Compute topological ordering of vertices
 * 2. Process vertices in topological order
 * 3. For each vertex, relax all outgoing edges
 * 
 * WHY TOPOLOGICAL ORDER?
 * ======================
 * In topological order, when we process a vertex, all vertices that can reach it
 * have already been processed. This ensures we've found the shortest path to
 * current vertex before relaxing its outgoing edges.
 * 
 * TIME COMPLEXITY: O(V + E)
 * - Topological sort: O(V + E)
 * - Relaxing edges: O(V + E)
 * - Much faster than Dijkstra's O((V+E)logV) for DAGs
 * 
 * SPACE COMPLEXITY: O(V + E)
 * 
 * COMPARISON:
 * - Dijkstra's: O((V+E)logV), doesn't work with negative weights
 * - Bellman-Ford: O(VE), works with negative weights, detects negative cycles
 * - DAG Shortest Path: O(V+E), works with negative weights, only for DAGs
 * 
 * USE CASES:
 * - Project scheduling (critical path method)
 * - Dependency resolution
 * - Longest path problems (negate weights)
 */

class Graph {
    int n;  // Number of vertices
    list<pair<int, int>> *adj;  // Adjacency list: {destination, weight}

public: 
    Graph(int n) {
        this->n = n;
        adj = new list<pair<int, int>>[n + 1];
    }

    // Add directed edge from x to y with weight w
    void addEdge(int x, int y, int w) {
        adj[x].push_back({y, w});
    }

    /*
     * DFS helper for topological sort
     * Uses reverse indexing: fills ordering array from right to left
     * This ensures topological order (left to right) after DFS completes
     * 
     * @param i: Current index in ordering array (decrements as we go)
     * @param at: Current vertex being processed
     * @return: Updated index after processing
     */
    int dfs(int i, int at, vector<bool>& visited, vector<int>& ordering) {
        visited[at] = true;
        
        // Process all neighbors first (post-order DFS)
        for (auto edge : adj[at]) {
            if (visited[edge.first]) continue;
            i = dfs(i, edge.first, visited, ordering);
        }
        
        // Add current vertex to ordering (rightmost position)
        // This ensures vertices with no outgoing edges come first in final order
        ordering[i] = at;
        return --i;  // Decrement index for next vertex
    }

    /*
     * Topological Sort using DFS
     * 
     * Returns array where ordering[i] = vertex at position i in topological order
     * Note: ordering[0] = -1 (unused), valid vertices start from ordering[1]
     * 
     * Algorithm: Post-order DFS - add vertex to ordering after processing all descendants
     */
    vector<int> topoSort() {
        vector<bool> visited(n + 1, false);
        vector<int> ordering(n + 1, -1);  // -1 indicates unused position
        int i = n;  // Start from rightmost position, fill backwards

        // Process all components (in case graph is disconnected)
        for (int src = 1; src <= n; src++) {
            if (!visited[src]) {
                i = dfs(i, src, visited, ordering);
            }
        }
        
        return ordering;
    }

    /*
     * DAG Shortest Path Algorithm
     * 
     * Key insight: Process vertices in topological order ensures that when we
     * relax edges from a vertex, we've already found shortest path to that vertex.
     * 
     * @param ordering: Topological ordering of vertices
     * @param start: Source vertex
     * @param numNodes: Number of vertices in topological order
     */
    void dagShortestPath(vector<int> &ordering, int start, int numNodes) {
        vector<int> dist(n + 1, INT_MAX);
        dist[start] = 0;

        // Process vertices in topological order
        for (int i = 1; i <= numNodes; i++) {
            int nodeIndex = ordering[i];
            
            // Skip if source vertex hasn't been reached yet
            if (dist[nodeIndex] == INT_MAX) continue;
            
            // Relax all outgoing edges from current vertex
            for (auto edge : adj[nodeIndex]) {
                int newDist = dist[nodeIndex] + edge.second;
                
                // Update distance if we found shorter path
                if (dist[edge.first] == INT_MAX) {
                    dist[edge.first] = newDist;
                } else {
                    dist[edge.first] = min(dist[edge.first], newDist);
                }
            }
        }
        
        cout << "Shortest paths from node " << start << " to all other nodes:\n";
        for (int i = 1; i <= n; i++) {
            if (dist[i] == INT_MAX) {
                cout << i << " -> INF (unreachable)\n";
            } else {
                cout << i << " -> " << dist[i] << "\n";
            }
        }
    }
};

/*
 * Test/Demo Function
 * 
 * Example DAG (Directed Acyclic Graph):
 *   1 --3--> 2 --4--> 4 --(-4)--> 5 --9--> 8
 *   |        |        |                      ^
 *   6        |        8                      |
 *   |        4        2                      |
 *   v        v        v                      |
 *   3 --11--> 7      7 --2------------------|
 *   |        |        |
 *   8        |        |
 *   |        |        |
 *   v        v        v
 *   4       8        8
 * 
 * Note: Edge 4->5 has negative weight (-4), which Dijkstra's cannot handle
 * but DAG shortest path algorithm can!
 */
int main() {
    Graph g(8);
    
    // Build the DAG: addEdge(from, to, weight)
    g.addEdge(1, 2, 3);   // 1 -> 2 with weight 3
    g.addEdge(1, 3, 6);   // 1 -> 3 with weight 6
    g.addEdge(2, 3, 4);   // 2 -> 3 with weight 4
    g.addEdge(2, 4, 4);   // 2 -> 4 with weight 4
    g.addEdge(3, 4, 8);   // 3 -> 4 with weight 8
    g.addEdge(3, 7, 11);  // 3 -> 7 with weight 11
    g.addEdge(4, 5, -4);  // 4 -> 5 with weight -4 (NEGATIVE - Dijkstra's can't handle this!)
    g.addEdge(4, 6, 5);   // 4 -> 6 with weight 5
    g.addEdge(4, 7, 2);   // 4 -> 7 with weight 2
    g.addEdge(5, 8, 9);   // 5 -> 8 with weight 9
    g.addEdge(6, 8, 1);   // 6 -> 8 with weight 1
    g.addEdge(7, 8, 2);   // 7 -> 8 with weight 2

    cout << "Topological ordering of nodes in graph:\n";
    vector<int> topSortOrdering = g.topoSort();
    for (auto o : topSortOrdering) {
        cout << o << " ";
    }
    cout << "\n\n";

    cout << "Finding shortest paths from node 1:\n";
    g.dagShortestPath(topSortOrdering, 1, 8);

    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ================
 * Topological ordering of nodes in graph:
 * -1 1 2 3 4 7 6 5 8
 * 
 * Finding shortest paths from node 1:
 * Shortest paths from node 1 to all other nodes:
 * 1 -> 0      (source node)
 * 2 -> 3      (1 -> 2)
 * 3 -> 6      (1 -> 3, note: 1->2->3 would be 7, so 1->3 is shorter)
 * 4 -> 7      (1 -> 2 -> 4)
 * 5 -> 3      (1 -> 2 -> 4 -> 5: 3+4+(-4) = 3) [NEGATIVE EDGE USED!]
 * 6 -> 12     (1 -> 2 -> 4 -> 6: 3+4+5 = 12)
 * 7 -> 9      (1 -> 2 -> 4 -> 7: 3+4+2 = 9)
 * 8 -> 11     (1 -> 2 -> 4 -> 5 -> 8: 3+4+(-4)+9 = 12, OR 1->2->4->7->8: 3+4+2+2 = 11)
 * 
 * Key observation: Path 1->2->4->5->8 uses negative edge (4->5: -4)
 * This gives total cost 12, but path 1->2->4->7->8 gives 11 (better)
 * Dijkstra's algorithm would fail on this graph due to negative edge!
 */