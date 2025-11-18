#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*
 * PRIM'S MINIMUM SPANNING TREE (MST) ALGORITHM
 * =============================================
 * 
 * Prim's algorithm finds the minimum spanning tree of a weighted undirected graph.
 * An MST connects all vertices with minimum total edge weight and no cycles.
 * 
 * KEY PROPERTIES:
 * - Greedy algorithm: Always adds the minimum weight edge connecting MST to new vertex
 * - Works on undirected graphs
 * - Similar to Dijkstra's but minimizes edge weight (not path distance)
 * - MST has exactly (V-1) edges for V vertices
 * 
 * ALGORITHM STEPS:
 * 1. Start with arbitrary vertex (root)
 * 2. Maintain min-heap of edges connecting MST to unvisited vertices
 * 3. Repeatedly add minimum weight edge that connects new vertex to MST
 * 4. Stop when all vertices are included (V-1 edges added)
 * 
 * TIME COMPLEXITY:
 * - With adjacency list + binary heap: O(E log V)
 * - With adjacency matrix + array: O(V^2)
 * - Best for dense graphs (many edges)
 * 
 * SPACE COMPLEXITY: O(V + E)
 * 
 * COMPARISON WITH KRUSKAL'S:
 * - Prim's: Better for dense graphs (O(V^2) vs O(E log E))
 * - Kruskal's: Better for sparse graphs, uses Union-Find
 * 
 * USE CASES:
 * - Network design (minimum cost to connect all nodes)
 * - Cluster analysis
 * - Approximation algorithms for NP-hard problems
 * 
 * INPUT FORMAT:
 * - Adjacency list: adj[u] = vector of {neighbor, weight} pairs
 * - Graph is undirected: if (u, v, w) exists, (v, u, w) also exists
 */

/*
 * Find Minimum Spanning Tree using Prim's algorithm
 * 
 * @param adj: Adjacency list representation of undirected graph
 *             adj[u] = vector of {neighbor, weight} pairs
 * @param V: Number of vertices
 * 
 * Key difference from Dijkstra's:
 * - weight[v] stores minimum edge weight to connect v to MST (not path distance)
 * - We minimize edge weight, not cumulative path cost
 */
void findMST(vector<vector<pair<int, int>>> &adj, int V) {
    // Min-heap: {minimum_edge_weight_to_vertex, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    vector<bool> visited(V, false);
    int edgeCount = 0, minCostSum = 0;
    vector<int> parent(V, -1);      // parent[i] = vertex that connects i to MST
    vector<int> weight(V, INT_MAX); // weight[i] = minimum edge weight to connect i to MST

    // Start with vertex 0 as root
    pq.push({0, 0}); // {weight, nodeIndex}
    weight[0] = 0;

    while (!pq.empty() && edgeCount != V - 1) {
        int minWeight = pq.top().first;
        int nodeIndex = pq.top().second;
        pq.pop();

        // Skip stale entries (already found better edge to this vertex)
        if (visited[nodeIndex] || weight[nodeIndex] < minWeight)
            continue;

        // Add this vertex to MST
        visited[nodeIndex] = true;
        minCostSum += minWeight;
        
        // Count edge only if it's not the root vertex
        if (parent[nodeIndex] != -1) {
            edgeCount++;
        }

        // Relax edges: Update minimum edge weight to connect neighbors to MST
        for (auto& edge : adj[nodeIndex]) {
            int to = edge.first;
            int cost = edge.second;
            
            // If neighbor not in MST and this edge is cheaper, update
            if (!visited[to] && cost < weight[to]) {
                parent[to] = nodeIndex;
                weight[to] = cost;
                pq.push({cost, to});
            }
        }
    }

    // Check if MST spans entire graph (connected graph has V-1 edges)
    bool mstExists = (edgeCount == V - 1);
    if (!mstExists) {
        cout << "Graph is disconnected. MST does not exist.\n";
        return;
    }

    cout << "\nCost of MST: " << minCostSum << endl;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " to " << i << " with cost " << weight[i] << "\n";
    }
}


/*
 * Test/Demo Function
 * 
 * Example Graph (undirected):
 *        2       3
 *    [0]----[1]----[4]
 *      \   8/ \3   /
 *     6 \  /   \  /7
 *        [3]    [2]
 * 
 * Finding Minimum Spanning Tree
 */
int main() {
    int V = 5;  // 5 vertices (0-4)
    
    // Adjacency list: adj[u] = vector of {neighbor, weight} pairs
    // For undirected graph, add edge in both directions
    vector<vector<pair<int, int>>> adj = {
        {{1, 2}, {3, 6}},           // 0: connected to 1 (weight 2), 3 (weight 6)
        {{0, 2}, {3, 8}, {4, 3}, {2, 3}},  // 1: connected to 0, 3, 4, 2
        {{1, 3}, {4, 7}},           // 2: connected to 1 (weight 3), 4 (weight 7)
        {{0, 6}, {1, 8}},           // 3: connected to 0, 1
        {{1, 3}, {2, 7}}            // 4: connected to 1, 2
    };
    
    findMST(adj, V);
}

/*
 * EXPECTED OUTPUT:
 * ================
 * Cost of MST: 14
 * 0 to 1 with cost 2
 * 1 to 2 with cost 3
 * 0 to 3 with cost 6
 * 1 to 4 with cost 3
 * 
 * MST Edges: (0-1:2) + (1-2:3) + (0-3:6) + (1-4:3) = 14
 * 
 * Note: Prim's works well for dense graphs (many edges)
 * Time complexity: O(E log V) with binary heap
 */