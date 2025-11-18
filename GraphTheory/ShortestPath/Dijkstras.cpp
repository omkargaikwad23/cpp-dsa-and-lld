#include <bits/stdc++.h>
using namespace std;

/*
 * DIJKSTRA'S SHORTEST PATH ALGORITHM
 * ===================================
 * 
 * Dijkstra's algorithm finds the shortest path from a source vertex to all 
 * other vertices in a weighted graph with non-negative edge weights.
 * 
 * KEY PROPERTIES:
 * - Greedy algorithm: Always picks the unvisited vertex with minimum distance
 * - Works only with non-negative edge weights
 * - Single-source shortest path algorithm
 * - Guarantees shortest path once a vertex is processed (visited)
 * 
 * ALGORITHM STEPS:
 * 1. Initialize distance to all vertices as INFINITY, except source (0)
 * 2. Use a priority queue (min-heap) to always process the closest unvisited vertex
 * 3. For each vertex, relax all its neighbors:
 *    - If distance through current vertex is shorter, update it
 * 4. Mark vertex as visited after processing all neighbors
 * 5. Repeat until all vertices are processed
 * 
 * TIME COMPLEXITY:
 * - Naive implementation: O(V^2) - using array to find minimum
 * - With min-heap (priority queue): O((V + E) * log V)
 *   * V = number of vertices
 *   * E = number of edges
 *   * Each vertex is extracted once: O(V log V)
 *   * Each edge is relaxed once: O(E log V)
 * 
 * SPACE COMPLEXITY: O(V + E)
 * - Distance array: O(V)
 * - Priority queue: O(V) in worst case
 * - Adjacency list: O(V + E)
 * 
 * IMPORTANT NOTES:
 * - Does NOT work with negative edge weights (use Bellman-Ford instead)
 * - Multiple entries for same node in PQ are handled by the distance check (line 108)
 * - No visited array needed: the distance check handles already-processed vertices
 * 
 * COMMON USE CASES:
 * - GPS navigation systems
 * - Network routing protocols
 * - Social network analysis (shortest connection path)
 * - Game pathfinding
 * - Resource allocation problems
 */

/*
 * Graph Class
 * Represents a weighted directed graph using adjacency list
 */
class Graph {
    int n;  // Number of vertices
    list<pair<int, int>> *adjList;  // Adjacency list: {destination, weight}

public:
    // Constructor: Initialize graph with given number of vertices
    Graph(int numNodes) {
        this->n = numNodes;  // Fixed: was incorrectly using 'n' instead of 'numNodes'
        adjList = new list<pair<int, int>>[n];
    }

    // Add a directed edge from 'from' to 'to' with given weight
    void addEdge(int from, int to, int weight) {
        adjList[from].push_back({to, weight});
    }

    /*
     * Dijkstra's Algorithm Implementation
     * 
     * @param start: Source vertex (starting point)
     * @param end: Destination vertex (optional, for early termination)
     * @return: Shortest distance from start to end, or -1 if unreachable
     * 
     * Algorithm Flow:
     * 1. Initialize all distances to INFINITY, source to 0
     * 2. Use min-heap to always process closest unvisited vertex
     * 3. Relax edges: update distances if shorter path found
     * 4. Skip stale entries in priority queue (optimization)
     */
    int dijkstra(int start, int end) {
        int ans = -1;
        
        // distance[i] = shortest distance from start to vertex i
        vector<int> distance(n + 1, INT_MAX);
        distance[start] = 0;  // Distance to source is 0

        // Min-heap priority queue: stores {distance, vertex} pairs
        // Always gives us the unvisited vertex with minimum distance
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while(!pq.empty()) {
            // Extract the vertex with minimum distance
            int minValue = pq.top().first;   // Current distance to this vertex
            int index = pq.top().second;     // Vertex index
            pq.pop();
            
            // OPTIMIZATION: Skip stale entries
            // If we've already found a better path to this vertex (through another route),
            // this entry in the PQ is outdated. Skip it.
            // This happens because we push multiple entries for the same vertex when
            // we find better paths, but we don't remove old entries.
            // This check also handles already-processed vertices (distance[index] == minValue means already processed)
            if(distance[index] < minValue) continue;

            // Relax all edges from current vertex
            // Edge relaxation: Check if going through current vertex gives shorter path
            for(auto& edge : adjList[index]) {
                int neighbor = edge.first;      // Destination vertex
                int edgeWeight = edge.second;   // Weight of the edge
                
                // Calculate new distance: distance to current + edge weight
                int newDist = distance[index] + edgeWeight;
                
                // If we found a shorter path, update it
                // Note: If neighbor was already processed, newDist >= distance[neighbor], so this check handles it
                if(newDist < distance[neighbor]) {
                    distance[neighbor] = newDist;  // Update shortest distance
                    pq.push({newDist, neighbor});  // Add to queue for processing
                    // Note: We don't remove old entries, but they'll be skipped by the check above
                }
            }
            
            // Optional: Early termination if we only need distance to 'end'
            if(index == end) {
                ans = distance[index];
            }
        }
        
        // Print all shortest distances from source
        cout << "Distances from start node to all other nodes!\n";
        for(int i = 1; i <= n; i++) {
            if(distance[i] == INT_MAX) {
                cout << i << "-> INF (unreachable)\n";
            } else {
                cout << i << "->" << distance[i] << "\n";
            }
        }
        
        return ans;
    }
};

/*
 * Test/Demo Function
 * 
 * Example Graph:
 *   1 --3--> 2 --4--> 4 --4--> 5 --9--> 8
 *   |        |        |        |        ^
 *   6        |        8        |        |
 *   |        4        2        5        |
 *   v        v        v        v        |
 *   3 --11--> 7      7 --2--> 6 --1----|
 *   |        |        |
 *   8        |        |
 *   |        |        |
 *   v        v        v
 *   4       8        8
 * 
 * Finding shortest path from node 1 to node 8
 */
int main() {
    Graph g(8);
    
    // Build the graph: addEdge(from, to, weight)
    g.addEdge(1, 2, 3);   // 1 -> 2 with weight 3
    g.addEdge(1, 3, 6);   // 1 -> 3 with weight 6
    g.addEdge(2, 3, 4);   // 2 -> 3 with weight 4
    g.addEdge(2, 4, 4);   // 2 -> 4 with weight 4
    g.addEdge(3, 4, 8);   // 3 -> 4 with weight 8
    g.addEdge(3, 7, 11);  // 3 -> 7 with weight 11
    g.addEdge(4, 5, 4);   // 4 -> 5 with weight 4
    g.addEdge(4, 6, 5);   // 4 -> 6 with weight 5
    g.addEdge(4, 7, 2);   // 4 -> 7 with weight 2
    g.addEdge(5, 8, 9);   // 5 -> 8 with weight 9
    g.addEdge(6, 8, 1);   // 6 -> 8 with weight 1
    g.addEdge(7, 8, 2);   // 7 -> 8 with weight 2
    
    // Find shortest path from node 1 to node 8
    int shortestDist = g.dijkstra(1, 8);
    cout << "\nShortest distance from node 1 to node 8: " << shortestDist << endl;
    
    // Path analysis:
    // Shortest path: 1 -> 2 -> 4 -> 7 -> 8
    // Distance: 3 + 4 + 2 + 2 = 11

    return 0;
}

/*
 * EXPECTED OUTPUT:
 * ================
 * Distances from start node to all other nodes!
 * 1->0      (source node)
 * 2->3      (1 -> 2)
 * 3->6      (1 -> 3)
 * 4->7      (1 -> 2 -> 4)
 * 5->11     (1 -> 2 -> 4 -> 5)
 * 6->12     (1 -> 2 -> 4 -> 6)
 * 7->9      (1 -> 2 -> 4 -> 7)
 * 8->11     (1 -> 2 -> 4 -> 7 -> 8)
 * 
 * Shortest distance from node 1 to node 8: 11
 * 
 * PATH: 1 -> 2 (3) -> 4 (4) -> 7 (2) -> 8 (2) = Total: 11
 */

/*
 * ALTERNATIVE IMPLEMENTATION (Competitive Programming Style)
 * ==========================================================
 * 
 * This is a more compact version commonly used in competitive programming.
 * Differences from the class-based implementation:
 * - Uses vector<vector<int>> for adjacency list (edge format: {destination, weight})
 * - Returns vector of distances instead of printing
 * - More concise variable names
 * - No visited array (relies on distance check optimization)
 * 
 * Usage in contests:
 * - Often provided as a helper function
 * - Adjacency list format: adj[u] = {{v1, w1}, {v2, w2}, ...}
 * - Returns shortest distances from source S to all vertices
 * 
 * Example:
 *   vector<vector<int>> adj[V];
 *   adj[0].push_back({1, 5});  // edge from 0 to 1 with weight 5
 *   vector<int> distances = dijkstra(V, adj, 0);
 */
/*
using pii = pair<int,int>;
vector <int> dijkstra(int V, vector<vector<int>> adj[], int S)
{
    vector<int> dist(V, INT_MAX);
    dist[S] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, S});
    
    while(!pq.empty()){
        int minDist = pq.top().first;
        int index = pq.top().second;
        pq.pop();
        if(dist[index] < minDist) continue;  // Skip stale entries
        
        for(auto& edge : adj[index]){
            int newDist = dist[index] + edge[1];  // edge[0] = destination, edge[1] = weight
            if(newDist < dist[edge[0]]){
                dist[edge[0]] = newDist;
                pq.push({newDist, edge[0]});
            }
        }
    }
    return dist;
}
*/