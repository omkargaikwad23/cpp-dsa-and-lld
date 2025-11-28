/*
    Algorithm Summary:
    ------------------
    This solution uses *Tarjan's Algorithm* to find all the critical connections (bridges) in an undirected graph.

    - A bridge is an edge that, if removed, increases the number of connected components in the graph.
    - We assign each node a discovery time (`tin`) and a low-link value (`low`) during DFS traversal.
    - If for any adjacent node `v`, `low[v] > tin[u]`, then edge (u, v) is a bridge.

    Key Concepts:
    - `tin[node]` stores the time at which the node was first visited (discovery time).
    - `low[node]` represents the lowest discovery time reachable from that node (including back edges).
    
    Bridge Condition: `low[child] > tin[parent]`
    -------------------------------------------
    This means the child cannot reach the parent or any ancestor via back-edges.
    
    Explanation:
    - `low[child]` = the EARLIEST discovery time that child can reach (via its subtree + back-edges)
    - `tin[parent]` = the discovery time when parent was first visited
    - If `low[child] > tin[parent]`, the child's earliest reachable node has discovery time > parent's discovery time
    - This means child CANNOT reach parent (or any ancestor discovered before/at parent's time)
    - Therefore, the edge (parent, child) is the ONLY path connecting them
    - Removing this edge would disconnect the child from the rest of the graph
    
    Intuition:
    - If low[child] <= tin[parent]: child can reach parent/ancestor → alternative path exists → NOT a bridge
    - If low[child] > tin[parent]: child cannot reach parent/ancestor → only one path → IS a bridge

    Time Complexity: O(N + E)
    - Each node and edge is visited exactly once in DFS traversal.
    
    Space Complexity: O(N + E)
    - adjacency list: O(E)
    - tin, low, visited arrays: O(N)
    - recursion stack: O(N) in worst case
*/

class Solution {
    int dfsTime = 0;  // Global time counter for discovery times
    
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adjacencyList(n);
        vector<bool> visited(n, false);
        vector<int> discoveryTime(n, 0); // tin
        vector<int> lowLink(n, 0);       // low
        vector<vector<int>> bridges;

        // Build the undirected graph
        for (auto &edge : connections) {
            int u = edge[0], v = edge[1];
            adjacencyList[u].push_back(v);
            adjacencyList[v].push_back(u);
        }

        // Perform DFS for each disconnected component
        for (int node = 0; node < n; ++node) {
            if (!visited[node]) {
                dfs(node, -1, visited, discoveryTime, lowLink, adjacencyList, bridges);
            }
        }

        return bridges;
    }

    void dfs(int currentNode, int parentNode,
             vector<bool> &visited,
             vector<int> &discoveryTime,
             vector<int> &lowLink,
             vector<vector<int>> &adjacencyList,
             vector<vector<int>> &bridges) {

        visited[currentNode] = true;
        discoveryTime[currentNode] = lowLink[currentNode] = ++dfsTime;

        for (int neighbor : adjacencyList[currentNode]) {
            if (neighbor == parentNode) continue;  // Skip the parent node

            if (!visited[neighbor]) {
                // DFS on the unvisited neighbor
                dfs(neighbor, currentNode, visited, discoveryTime, lowLink, adjacencyList, bridges);

                // After returning from recursion, update the low-link value
                lowLink[currentNode] = min(lowLink[currentNode], lowLink[neighbor]);

                // Check if the edge is a bridge
                // 
                // WHY lowLink[neighbor] > discoveryTime[currentNode] means it's a bridge:
                // ------------------------------------------------------------------------
                // 
                // 1. discoveryTime[currentNode] = time when we FIRST visited currentNode
                // 2. lowLink[neighbor] = LOWEST discovery time that neighbor can reach
                //    (via its subtree and any back-edges)
                //
                // If lowLink[neighbor] > discoveryTime[currentNode]:
                //   → neighbor CANNOT reach currentNode or any ancestor of currentNode
                //   → The ONLY path from currentNode to neighbor is the direct edge (currentNode, neighbor)
                //   → If we remove this edge, neighbor becomes disconnected
                //   → Therefore, this edge is a BRIDGE
                //
                // Example:
                //   Consider: A --- B --- C
                //                    |
                //                    D
                //   If DFS visits A(1) → B(2) → C(3) → D(4)
                //   - Edge (B, C): lowLink[C] = 3, discoveryTime[B] = 2
                //     Since 3 > 2, edge (B, C) is a bridge ✓
                //   - Edge (B, D): lowLink[D] = 4, discoveryTime[B] = 2
                //     Since 4 > 2, edge (B, D) is a bridge ✓
                //
                // Counter-example (NOT a bridge):
                //   Consider: A --- B --- C
                //            |           |
                //            └-----------┘
                //   If DFS visits A(1) → B(2) → C(3), then back-edge C→A found
                //   - Edge (B, C): lowLink[C] = 1 (can reach A via back-edge)
                //     discoveryTime[B] = 2
                //     Since 1 < 2, edge (B, C) is NOT a bridge (there's an alternative path)
                //
                if (lowLink[neighbor] > discoveryTime[currentNode]) {
                    bridges.push_back({currentNode, neighbor});
                }
            } else {
                // Back edge found; update low-link
                lowLink[currentNode] = min(lowLink[currentNode], discoveryTime[neighbor]);
            }
        }
    }
};