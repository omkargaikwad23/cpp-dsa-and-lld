#include <bits/stdc++.h>
using namespace std;

/*
Find Longest Cycle in a Directed Graph

Algorithm: Use DFS with state tracking to detect cycles
- State 0: Unvisited node
- State 1: Currently visiting (in recursion stack) - used to detect cycles
- State 2: Completely processed - OPTIMIZATION to avoid revisiting nodes

Why State 2 is needed:
- When we backtrack from a node, we mark it as state 2 (completely processed)
- This prevents revisiting nodes that have already been explored in a different DFS path
- Without state 2: If we start DFS from a new node and encounter a previously processed node,
  we might unnecessarily explore it again (though it won't break correctness)
- With state 2: We skip already-processed nodes, ensuring O(V + E) time complexity

Note: State 2 is an optimization. We could use only states 0 and 1, but then we'd need
to check if a node was already visited to avoid redundant work.

When we encounter a node with state=1 during DFS, we found a back edge (cycle).
Cycle length = current_depth - depth[back_edge_node] + 1

Time Complexity: O(V + E) - single DFS traversal
Space Complexity: O(V) - for state and depth arrays
*/

class Solution {
    int longest = -1;

    void dfs(vector<vector<int>>& adj, vector<int>& state, vector<int>& depth, int node, int d) {
        state[node] = 1;        // Mark as currently visiting
        depth[node] = d;        // Store depth of this node

        // Explore all neighbors
        for(auto next : adj[node]) {
            if(state[next] == 0) {
                // Unvisited node - continue DFS
                dfs(adj, state, depth, next, d + 1);
            }
            else if(state[next] == 1) {
                // Found back edge - cycle detected!
                // Cycle length = current depth - depth of back edge node + 1
                longest = max(longest, d - depth[next] + 1);
            }
            // If state[next] == 2: node already processed from another DFS path, skip
            // This prevents redundant exploration and maintains O(V+E) complexity
        }

        state[node] = 2;  // Mark as completely processed - prevents revisiting from other paths
    }

public:
    int longestCycle(vector<vector<int>>& adj) {

        // State: 0=unvisited, 1=visiting, 2=done
        vector<int> state(adj.size(), 0);
        vector<int> depth(adj.size(), 0);

        // DFS from each unvisited node
        for(int i = 0; i < adj.size(); i++) {
            if(state[i] == 0) {
                dfs(adj, state, depth, i, 0);
            }
        }

        return longest;
    }
};

int main() {
    Solution sol;
    
    // Example 1: Graph with cycles
    // Graph structure:
    // 0 -> 1 -> 2 -> 3 -> 4 -> 5
    //           ↑              ↓
    //           └──────────────┘
    // Cycle: 2 -> 3 -> 4 -> 5 -> 2 (length = 4)
    
    vector<vector<int>> adj = {{1, 2}, {2, 3}, {3, 4}, {4, 5}, {5, 2}};
    
    int result = sol.longestCycle(adj);
    cout << "Longest cycle length: " << result << "\n";
    
    // Example 2: Multiple cycles
    // Graph structure:
    // 0 -> 1 -> 2 -> 0  (cycle length = 3)
    // 2 -> 3 -> 4 -> 3  (cycle length = 2)
    
    Solution sol2;
    vector<vector<int>> adj2 = {
        {0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 3}};
    
    int result2 = sol2.longestCycle(adj2);
    cout << "Longest cycle length: " << result2 << "\n";
    
    return 0;
}

