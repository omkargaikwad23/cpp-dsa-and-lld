#include <bits/stdc++.h>
using namespace std;

/*
Kosaraju's Algorithm: Find Strongly Connected Components (SCCs) in a directed graph

Time Complexity: O(V + E)
- DFS1: O(V + E) - visit each node and edge once
- Transpose: O(V + E) - iterate through all edges to reverse them
- DFS2: O(V + E) - visit each node and edge once in transposed graph
Total: O(V + E)

Space Complexity: O(V + E)
- Adjacency list: O(V + E)
- Transposed graph: O(V + E)
- Stack: O(V)
- Visited array: O(V)
Total: O(V + E)

Steps:
1. DFS1: Traverse graph, push nodes to stack after visiting all neighbors
2. Transpose: Reverse all edges
3. DFS2: Pop from stack, DFS on transposed graph (each DFS = one SCC)

Dry Run Example:
Graph: 0->1->2->0 (SCC1), 2->3->4->5->3 (SCC2)

Step 1 - DFS1 (fill stack):
  Start from 0: 0->1->2->0 (back edge, backtrack)
  Stack: [2, 1, 0]

  Continue from 2: 2->3->4->5->3 (back edge, backtrack)
  Stack: [5, 4, 3, 2, 1, 0]

Step 2 - Transpose:
  Original: 0->1, 1->2, 2->0,3, 3->4, 4->5, 5->3
  Transposed: 0<-2, 1<-0, 2<-1, 3<-2,5, 4<-3, 5<-4

Step 3 - DFS2 (find SCCs):
  Pop 0: DFS from 0 in transposed graph
    Visit 0->2->1->0 (back edge)
    SCC1 found: {0, 2, 1}
  Pop 1,2: Already visited, skip
  Pop 3: DFS from 3 in transposed graph
    Visit 3->5->4->3 (back edge)
    SCC2 found: {3, 5, 4}
  Pop 4,5: Already visited, skip

Result: 2 SCCs - {0,1,2} and {3,4,5}
*/

// First DFS: Fill stack with nodes in order of finishing times
void dfs1(int u, vector<vector<int>>& adj, vector<bool>& vis, stack<int>& st) {
    vis[u] = true;
    for(int v : adj[u]) {
        if(!vis[v]) {
            dfs1(v, adj, vis, st);
        }
    }
    st.push(u);  // Push after visiting all neighbors
}

// Second DFS: Explore transposed graph to find SCCs
void dfs2(int u, vector<vector<int>>& rev, vector<bool>& vis, vector<int>& component) {
    vis[u] = true;
    component.push_back(u);
    for(int v : rev[u]) {
        if(!vis[v]) {
            dfs2(v, rev, vis, component);
        }
    }
}

// Build transposed graph (reverse all edges)
vector<vector<int>> transpose(int n, vector<vector<int>>& adj) {
    vector<vector<int>> rev(n);
    for(int u = 0; u < n; u++) {
        for(int v : adj[u]) {
            rev[v].push_back(u);
        }
    }
    return rev;
}

void findSCC(int n, vector<vector<int>>& adj) {
    // Step 1: First DFS to fill stack
    vector<bool> vis(n, false);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        if(!vis[i]) {
            dfs1(i, adj, vis, st);
        }
    }

    // Step 2: Transpose graph
    vector<vector<int>> rev = transpose(n, adj);

    // Step 3: Second DFS on transposed graph
    fill(vis.begin(), vis.end(), false);
    vector<vector<int>> sccs;
    
    while(!st.empty()) {
        int u = st.top();
        st.pop();
        if(!vis[u]) {
            vector<int> component;
            dfs2(u, rev, vis, component);
            sccs.push_back(component);
        }
    }

    // Output results
    cout << "Number of SCCs: " << sccs.size() << "\n";
    for(auto& comp : sccs) {
        for(int node : comp) {
            cout << node << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n = 6;
    // Adjacency list: adj[u] contains all nodes that u points to
    // Graph structure:
    //   0 -> 1 -> 2 -> 0  (SCC1: {0,1,2})
    //        ↓
    //   3 -> 4 -> 5 -> 3  (SCC2: {3,4,5})
    vector<vector<int>> adj = {
        {1},      // 0 -> 1
        {2},      // 1 -> 2
        {0, 3},   // 2 -> 0, 2 -> 3
        {4},      // 3 -> 4
        {5},      // 4 -> 5
        {3}       // 5 -> 3
    };
    
    findSCC(n, adj);
}
