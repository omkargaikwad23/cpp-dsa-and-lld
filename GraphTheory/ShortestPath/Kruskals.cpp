#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

/*
 * KRUSKAL'S MINIMUM SPANNING TREE (MST) ALGORITHM
 * ================================================
 * 
 * Kruskal's algorithm finds the minimum spanning tree by:
 * 1. Sorting all edges by weight (ascending)
 * 2. Greedily adding edges that don't form cycles
 * 3. Using Union-Find (DSU) to detect cycles efficiently
 * 
 * KEY PROPERTIES:
 * - Greedy algorithm: Always picks minimum weight edge that doesn't create cycle
 * - Works on undirected graphs
 * - Uses Disjoint Set Union (DSU) for cycle detection
 * - Better for sparse graphs (few edges)
 * 
 * ALGORITHM STEPS:
 * 1. Sort all edges by weight
 * 2. Initialize DSU (each vertex is its own component)
 * 3. For each edge in sorted order:
 *    - If endpoints are in different components, add edge to MST
 *    - Union the two components
 * 4. Stop when (V-1) edges are added
 * 
 * TIME COMPLEXITY: O(E log E) = O(E log V)
 * - Sorting edges: O(E log E)
 * - DSU operations: O(E * α(V)) where α is inverse Ackermann (nearly constant)
 * 
 * SPACE COMPLEXITY: O(V + E)
 * 
 * COMPARISON WITH PRIM'S:
 * - Kruskal's: Better for sparse graphs, processes edges independently
 * - Prim's: Better for dense graphs, grows MST from a vertex
 * 
 * USE CASES:
 * - Network design (connect all nodes with minimum cost)
 * - Cluster analysis
 * - Image segmentation
 * 
 * INPUT FORMAT:
 * - Adjacency list: adj[u] = vector of {neighbor, weight} pairs
 * - Graph is undirected: if (u, v, w) exists, (v, u, w) also exists
 */

/*
 * Disjoint Set Union (DSU) / Union-Find Data Structure
 * 
 * Used to efficiently:
 * - Check if two vertices are in the same connected component
 * - Merge two components (union operation)
 * 
 * Optimizations:
 * - Path compression: Flattens tree during find operation
 * - Union by rank: Always attaches smaller tree under larger tree
 * 
 * Time complexity: O(α(n)) per operation (nearly constant)
 */
struct DSU {
    vector<int> parent;  // parent[i] = parent of node i
    vector<int> rank;    // rank[i] = approximate depth of tree rooted at i
    int n;

    DSU(int _n) {
        n = _n;
        parent.assign(n + 1, 0);
        rank.assign(n + 1, 0);
        // Initialize: each node is its own parent (separate components)
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    // Find root of component containing 'node' with path compression
    int findParent(int node) {
        if (parent[node] == node) return node;
        // Path compression: make parent point directly to root
        return parent[node] = findParent(parent[node]);
    }

    // Union two components containing u and v (union by rank)
    void merge(int u, int v) {
        u = findParent(u);
        v = findParent(v);
        if (u == v) return;  // Already in same component

        /*
         * UNION BY RANK: Attach smaller rank tree under larger rank tree
         * 
         * WHY DO THIS?
         * ============
         * Goal: Keep tree height (rank) as small as possible for efficient find operations
         * 
         * If we attach smaller tree under larger:
         * - Tree height doesn't increase (or increases by at most 1)
         * - Example: Tree A (height 3) + Tree B (height 2) = height 3 (no increase)
         * 
         * If we attach larger tree under smaller (WRONG):
         * - Tree height increases significantly
         * - Example: Tree A (height 2) + Tree B (height 3) = height 4 (increased by 1)
         * - This makes find() operations slower (more nodes to traverse)
         * 
         * Result: Tree height stays O(log n), making find() O(log n)
         * Combined with path compression: Nearly O(1) amortized time
         */
        if (rank[u] > rank[v]) {
            // Attach smaller tree (v) under larger tree (u)
            parent[v] = u;
        } else if (rank[u] < rank[v]) {
            // Attach smaller tree (u) under larger tree (v)
            parent[u] = v;
        } else {
            // Same rank: can attach either way, but rank increases by 1
            parent[v] = u;
            rank[u]++;  // Height increases by 1 (both trees had same height)
        }
    }
};

// Helper function to print MST edges and total cost
void printMstEdges(vector<tuple<int, int, int>> &mstEdges, int mstCost) {
    cout << "MST cost is : " << mstCost << "\n";
    cout << "Edges in MST are: \n";
    for (auto& edge : mstEdges) {
        int from = get<0>(edge);
        int to = get<1>(edge);
        int cost = get<2>(edge);
        cout << from << " to " << to << " with cost of " << cost << endl;
    }
}

/*
 * Kruskal's Algorithm Implementation
 * 
 * @param adj: Adjacency list representation of undirected graph
 *             adj[u] = vector of {neighbor, weight} pairs
 * @param V: Number of vertices
 * 
 * Core idea: Greedily add minimum weight edges that don't create cycles
 * Cycle detection: If both endpoints are in same DSU component, adding edge creates cycle
 */
void kruskal(vector<vector<pair<int, int>>> &adj, int V) {
    DSU ds(V);  // Initialize DSU: each vertex is separate component
    
    // Extract all edges from adjacency list
    // Format: {weight, from, to} - weight first for easy sorting
    vector<tuple<int, int, int>> edges;
    
    // Convert adjacency list to edge list
    // For undirected graph, we only add each edge once (u < v to avoid duplicates)
    for (int u = 0; u < V; u++) {
        for (auto& neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            // Only add edge once (when u < v) to avoid duplicates in undirected graph
            if (u < v) {
                edges.push_back({weight, u, v});
            }
        }
    }
    
    // Sort edges by weight (ascending)
    sort(edges.begin(), edges.end());
    
    int mstCost = 0;
    vector<tuple<int, int, int>> mstEdges;

    // Process edges in sorted order
    for (auto& edge : edges) {
        int weight = get<0>(edge);
        int from = get<1>(edge);
        int to = get<2>(edge);
        
        // If endpoints are in different components, edge doesn't create cycle
        if (ds.findParent(from) != ds.findParent(to)) {
            mstCost += weight;
            mstEdges.push_back({from, to, weight});
            ds.merge(from, to);  // Merge components
        }
        // If endpoints in same component, skip (would create cycle)
    }

    printMstEdges(mstEdges, mstCost);
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
 * Finding Minimum Spanning Tree using Kruskal's algorithm
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

    kruskal(adj, V);
}

/*
 * EXPECTED OUTPUT:
 * ================
 * MST cost is : 14
 * Edges in MST are:
 * 0 to 1 with cost of 2
 * 1 to 4 with cost of 3
 * 1 to 2 with cost of 3
 * 0 to 3 with cost of 6
 * 
 * MST Edges: (0-1:2) + (1-4:3) + (1-2:3) + (0-3:6) = 14
 * 
 * Algorithm trace:
 * 1. Sort edges: (0-1:2), (1-4:3), (1-2:3), (0-3:6), (2-4:7), (1-3:8)
 * 2. Add (0-1:2) - connects 0 and 1
 * 3. Add (1-4:3) - connects 4 to {0,1}
 * 4. Add (1-2:3) - connects 2 to {0,1,4}
 * 5. Add (0-3:6) - connects 3 to {0,1,2,4}
 * 6. Skip (2-4:7) - would create cycle (2 and 4 already connected)
 * 7. Skip (1-3:8) - would create cycle (1 and 3 already connected)
 */