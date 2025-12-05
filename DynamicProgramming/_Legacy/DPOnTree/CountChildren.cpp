/*
================================================================================
                COUNT DESCENDANTS (Subtree Size - 1)
================================================================================

Problem: For each node in a tree, count the number of nodes in its subtree
         (excluding itself). This is "number of descendants" or "children count".

Example:
        1
       / \
      2   3
     /     \
    4       5

Output: [4, 1, 1, 0, 0]
  - Node 1: 4 descendants (2, 3, 4, 5)
  - Node 2: 1 descendant (4)
  - Node 3: 1 descendant (5)
  - Node 4: 0 descendants (leaf)
  - Node 5: 0 descendants (leaf)

Approach: DFS from root, for each node:
  descendants[node] = sum of (1 + descendants[child]) for all children

Time: O(n)  |  Space: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int parent, vector<int>& descendants, vector<vector<int>>& adj) {
    int count = 0;
    
    for (int child : adj[node]) {
        if (child != parent) {
            dfs(child, node, descendants, adj);
            count += 1 + descendants[child];  // child + its descendants
        }
    }
    
    descendants[node] = count;
}

vector<int> countDescendants(int n, vector<pair<int,int>>& edges, int root = 1) {
    // Build adjacency list
    vector<vector<int>> adj(n + 1);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> descendants(n + 1, 0);
    dfs(root, -1, descendants, adj);
    
    return descendants;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ BONUS: Count Subtree Size (including the node itself)                       │
│ Just add 1 to each result, or modify DFS slightly                           │
└─────────────────────────────────────────────────────────────────────────────┘
*/

void dfsSubtreeSize(int node, int parent, vector<int>& subtreeSize, vector<vector<int>>& adj) {
    subtreeSize[node] = 1;  // Count self
    
    for (int child : adj[node]) {
        if (child != parent) {
            dfsSubtreeSize(child, node, subtreeSize, adj);
            subtreeSize[node] += subtreeSize[child];
        }
    }
}


int main() {
    cout << "=== Count Descendants (DP on Tree) ===\n\n";
    
    /*
    Tree structure:
            1
           / \
          2   3
         /     \
        4       5
    */
    
    int n = 5;
    vector<pair<int,int>> edges = {{1,2}, {1,3}, {2,4}, {3,5}};
    
    cout << "Tree:";
    cout << "        1";
    cout << "       / \";
    cout << "      2   3";
    cout << "     /     \";
    cout << "    4       5";
    
    // Count descendants
    vector<int> desc = countDescendants(n, edges);
    cout << "Descendants (subtree size - 1):\n";
    for (int i = 1; i <= n; i++) {
        cout << "  Node " << i << ": " << desc[i] << " descendants\n";
    }
    cout << "Expected: [4, 1, 1, 0, 0]\n\n";
    
    // Count subtree size
    vector<vector<int>> adj(n + 1);
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> subtree(n + 1, 0);
    dfsSubtreeSize(1, -1, subtree, adj);
    
    cout << "Subtree size (including self):\n";
    for (int i = 1; i <= n; i++) {
        cout << "  Node " << i << ": " << subtree[i] << " nodes\n";
    }
    cout << "Expected: [5, 2, 2, 1, 1]\n";
    
    return 0;
}

/*
================================================================================
                        RELATED PROBLEMS
================================================================================

1. Subtree Size       → subtree[node] = 1 + sum(subtree[children])
2. Descendants Count  → desc[node] = sum(1 + desc[children])
3. Tree Diameter      → Need both subtree depth from each node
4. Tree Center        → Remove leaves iteratively / use subtree sizes
5. Rerooting DP       → Compute answer for all roots efficiently

================================================================================
*/
