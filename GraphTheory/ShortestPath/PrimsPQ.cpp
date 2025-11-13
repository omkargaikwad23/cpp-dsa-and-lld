#include <bits/stdc++.h>
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
 */

class Prims {
    int N;  // Number of vertices
    vector<pair<int, int>> *adj;  // Adjacency list: {neighbor, weight}

public:
    Prims(int N) {
        this->N = N;
        adj = new vector<pair<int, int>>[N];
    }

    // Add undirected edge between u and v with weight w
    void addEdge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    /*
     * Find Minimum Spanning Tree using Prim's algorithm
     * 
     * Key difference from Dijkstra's:
     * - weight[v] stores minimum edge weight to connect v to MST (not path distance)
     * - We minimize edge weight, not cumulative path cost
     */
    void findMST() {
        // Min-heap: {minimum_edge_weight_to_vertex, vertex}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        vector<bool> visited(N, false);
        int edgeCount = 0, minCostSum = 0;
        vector<int> parent(N, -1);      // parent[i] = vertex that connects i to MST
        vector<int> weight(N, INT_MAX); // weight[i] = minimum edge weight to connect i to MST

        // Start with vertex 0 as root
        pq.push({0, 0});
        weight[0] = 0;

        while (!pq.empty() && edgeCount != N - 1) {
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
        bool mstExists = (edgeCount == N - 1);
        if (!mstExists) {
            cout << "Graph is disconnected. MST does not exist.\n";
            return;
        }

        cout << "\nCost of MST: " << minCostSum << endl;
        for (int i = 1; i < N; i++) {
            cout << parent[i] << " to " << i << " with cost " << weight[i] << "\n";
        }
    }
};


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
    Prims g(5);
    g.addEdge(0, 1, 2);   // 0 <-> 1 with weight 2
    g.addEdge(0, 3, 6);   // 0 <-> 3 with weight 6
    g.addEdge(1, 3, 8);   // 1 <-> 3 with weight 8
    g.addEdge(1, 4, 3);   // 1 <-> 4 with weight 3
    g.addEdge(1, 2, 3);   // 1 <-> 2 with weight 3
    g.addEdge(2, 4, 7);   // 2 <-> 4 with weight 7
    
    g.findMST();
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