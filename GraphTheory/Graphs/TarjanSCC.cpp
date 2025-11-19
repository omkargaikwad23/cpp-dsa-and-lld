/*
    Algorithm Summary:
    ------------------
    This solution uses **Tarjan's Algorithm** to find all the critical connections (bridges) in an undirected graph.

    - A bridge is an edge that, if removed, increases the number of connected components in the graph.
    - We assign each node a discovery time (`discoveryTime`) and a low-link value (`lowLink`) during DFS traversal.
    - If for any adjacent node `v`, `lowLink[v] > discoveryTime[u]`, then edge (u, v) is a bridge.

    Key Concepts:
    - `discoveryTime[node]` stores the time at which the node was first visited.
    - `lowLink[node]` represents the lowest discovery time (node's discovery time) reachable from that node (including back edges).
    - During DFS traversal, if we encounter a child with `lowLink[child] > discoveryTime[node]`, then that edge is a bridge. 
        - If YES → nothing lower was reachable → the only way to reach child was through node → that edge (node, child) is a bridge.
        - If NO → there was a lower path → the edge (node, child) is not a bridge.

    Time Complexity: O(N + E)
    - Each node and edge is visited exactly once in DFS traversal.
    
    Space Complexity: O(N + E)
    - `adjacency list`: O(E)
    - `discoveryTime`, `lowLink`, `visited` arrays: O(N)
    - `recursion stack`: O(N) in worst case
*/

class Solution {
    int dfsTime = 0;  // Global time counter for discovery times
    
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adjacencyList(n);
        vector<bool> visited(n, false);
        vector<int> discoveryTime(n, 0); 
        vector<int> lowLink(n, 0);
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
                // Could neighbor have reached anything before I arrived at currentNode?
                if (lowLink[neighbor] > discoveryTime[currentNode]) { // If YES → nothing lower was reachable → the only way to reach neighbor was through currentNode → that edge (currentNode, neighbor) is a bridge.
                    bridges.push_back({currentNode, neighbor});
                }
            } else {
                // Back edge found; update low-link
                lowLink[currentNode] = min(lowLink[currentNode], discoveryTime[neighbor]);
            }
        }
    }
};

/*

Example Graph:
0 --- 1 --- 2
      |
      3 --- 4

Bridges: (0,1), (1,2), (1,3), (3,4)

Explanation:

*/