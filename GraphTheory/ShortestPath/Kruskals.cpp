#include <bits/stdc++.h>
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
 */

// Edge structure: represents an undirected edge with weight
struct Edge {
    int from, to, cost;
    Edge(int from, int to, int cost) {
        this->from = from;
        this->to = to;
        this->cost = cost;
    }
};

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
    vector<int> size;    // size[i] = size of component containing i
    int n;

    DSU(int _n) {
        n = _n;
        parent.assign(n + 1, 0);
        rank.assign(n + 1, 0);
        size.assign(n + 1, 0);
        // Initialize: each node is its own parent (separate components)
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
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
            size[u] += size[v];
            // Rank of u doesn't change (height stays same)
        } else if (rank[u] < rank[v]) {
            // Attach smaller tree (u) under larger tree (v)
            parent[u] = v;
            size[v] += size[u];
            // Rank of v doesn't change (height stays same)
        } else {
            // Same rank: can attach either way, but rank increases by 1
            parent[v] = u;
            size[u] += size[v];
            rank[u]++;  // Height increases by 1 (both trees had same height)
        }
    }
};

// Helper function to print MST edges and total cost
void printMstEdges(vector<Edge> &mstEdges, int mstCost) {
    cout << "MST cost is : " << mstCost << "\n";
    cout << "Edges in MST are: \n";
    for (auto& e : mstEdges) {
        cout << e.from << " to " << e.to << " with cost of " << e.cost << endl;
    }
}

// Comparator: sort edges by weight (ascending)
bool comp(Edge &e1, Edge &e2) {
    return e1.cost < e2.cost;
}

/*
 * Kruskal's Algorithm Implementation
 * 
 * Core idea: Greedily add minimum weight edges that don't create cycles
 * Cycle detection: If both endpoints are in same DSU component, adding edge creates cycle
 */
void Kruskal(vector<Edge> &edges, int V, int E) {
    DSU ds(V);  // Initialize DSU: each vertex is separate component
    
    // Sort edges by weight (greedy: always consider smallest edge first)
    sort(edges.begin(), edges.end(), comp);
    int mstCost = 0;
    vector<Edge> mstEdges;

    // Process edges in sorted order
    for (Edge& edge : edges) {
        // If endpoints are in different components, edge doesn't create cycle
        if (ds.findParent(edge.from) != ds.findParent(edge.to)) {
            mstCost += edge.cost;
            mstEdges.push_back(Edge(edge.from, edge.to, edge.cost));
            ds.merge(edge.from, edge.to);  // Merge components
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
    int V = 5, E = 6;  // 5 vertices (0-4), 6 edges
    vector<Edge> edges;

    edges.push_back(Edge(0, 1, 2));   // 0 <-> 1 with weight 2
    edges.push_back(Edge(0, 3, 6));   // 0 <-> 3 with weight 6
    edges.push_back(Edge(1, 3, 8));   // 1 <-> 3 with weight 8
    edges.push_back(Edge(1, 4, 3));   // 1 <-> 4 with weight 3
    edges.push_back(Edge(1, 2, 3));   // 1 <-> 2 with weight 3
    edges.push_back(Edge(2, 4, 7));   // 2 <-> 4 with weight 7

    Kruskal(edges, V, E);
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