/*
================================================================================
                CONVERT GRAPH TO BINARY TREE (Google Interview)
================================================================================

PROBLEM 1: Find Valid Root for Binary Tree
──────────────────────────────────────────
Given: An undirected, acyclic, connected graph where each node has degree ≤ 3.
Find:  A node that can serve as root to make the graph a valid binary tree.

Key Insight:
- Binary tree node can have at most 2 children
- Root has no parent → can have up to 2 children (degree ≤ 2)
- Non-root has 1 parent → remaining edges are children (degree - 1 ≤ 2, so degree ≤ 3) ✓

Answer: Any node with degree ≤ 2 can be the root.

Example:
        1 ─── 2 ─── 3
              │
              4
              
  Node degrees: 1→1, 2→3, 3→1, 4→1
  Valid roots: 1, 3, 4 (degree ≤ 2)
  Invalid root: 2 (degree = 3, would have 3 children)

================================================================================

PROBLEM 2: Binary Tree with Alternating Colors (Black/White)
────────────────────────────────────────────────────────────
Given: Same graph, but nodes are colored Black (B) or White (W).
Find:  A root such that:
       1. Graph becomes a valid binary tree
       2. Colors alternate by level (W→B→W... or B→W→B...)

Key Insight:
- This requires the graph to be 2-colorable along any path from root
- Since it's a tree (acyclic), it's always bipartite
- We need root with degree ≤ 2 AND whose BFS levels match the given coloring

================================================================================

PROBLEM 3: Binary Tree with RGB Color Sequence
──────────────────────────────────────────────
Given: Same graph, but nodes are colored Red (R), Blue (B), or White (W).
Find:  A root such that:
       1. Graph becomes a valid binary tree
       2. Levels follow sequence: R→B→W→R... or B→W→R... or W→R→B...

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ SOLUTION 1: Find Valid Root for Binary Tree                                 │
│                                                                             │
│ Time Complexity:  O(V) - single pass to check degrees                       │
│ Space Complexity: O(1) - just return any valid node                         │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int findValidRoot(int n, vector<vector<int>>& adj) {
    // Any node with degree <= 2 can be root
    // Because: root has no parent, so all edges become children
    // Binary tree allows at most 2 children per node
    
    for (int i = 0; i < n; i++) {
        if (adj[i].size() <= 2) {
            return i;  // Found valid root
        }
    }
    return -1;  // No valid root (shouldn't happen if input is valid)
}

// Return ALL valid roots
vector<int> findAllValidRoots(int n, vector<vector<int>>& adj) {
    vector<int> validRoots;
    for (int i = 0; i < n; i++) {
        if (adj[i].size() <= 2) {
            validRoots.push_back(i);
        }
    }
    return validRoots;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ SOLUTION 2: Binary Tree with Alternating Colors (Black/White)               │
│                                                                             │
│ Time Complexity:  O(V + E) - BFS from each candidate root                   │
│                   Worst case O(V * (V + E)) if all nodes are candidates     │
│                   Optimized: O(V + E) using bipartite check                 │
│ Space Complexity: O(V) - for BFS queue and visited array                    │
└─────────────────────────────────────────────────────────────────────────────┘
*/

// Check if rooting at 'root' gives valid alternating colors
// startColor: expected color at root level (0 = White, 1 = Black)
bool checkAlternatingBFS(int root, vector<vector<int>>& adj, vector<int>& color, int startColor) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    
    q.push(root);
    visited[root] = true;
    int expectedColor = startColor;
    
    while (!q.empty()) {
        int levelSize = q.size();
        
        // Check all nodes at current level have expected color
        for (int i = 0; i < levelSize; i++) {
            int u = q.front();
            q.pop();
            
            if (color[u] != expectedColor) {
                return false;  // Color mismatch at this level
            }
            
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        
        // Alternate color for next level
        expectedColor = 1 - expectedColor;
    }
    
    return true;
}

int findRootAlternatingColors(int n, vector<vector<int>>& adj, vector<int>& color) {
    // color[i] = 0 (White) or 1 (Black)
    
    for (int root = 0; root < n; root++) {
        // Check 1: Must have degree <= 2 to be valid binary tree root
        if (adj[root].size() > 2) continue;
        
        // Check 2: Try both starting colors (White first or Black first)
        if (checkAlternatingBFS(root, adj, color, 0) ||  // Start with White
            checkAlternatingBFS(root, adj, color, 1)) {  // Start with Black
            return root;
        }
    }
    
    return -1;  // No valid root found
}

/*
 OPTIMIZED APPROACH for Problem 2:
 
 Key insight: In a tree, if we do BFS from ANY node, nodes at even depths
 form one set, odd depths form another. This is the bipartite partition.
 
 So we only need to:
 1. Do ONE BFS from any node to find depth parity of each node
 2. Check if given coloring matches either:
    - All even-depth nodes are White, odd-depth are Black, OR
    - All even-depth nodes are Black, odd-depth are White
 3. If match found, any degree-≤2 node of the starting color is valid root
 
 Time: O(V + E) - single BFS
*/

int findRootAlternatingOptimized(int n, vector<vector<int>>& adj, vector<int>& color) {
    // Step 1: BFS from node 0 to get depth parity
    vector<int> depthParity(n);  // 0 = even depth, 1 = odd depth
    queue<int> q;
    q.push(0);
    depthParity[0] = 0;
    vector<bool> visited(n, false);
    visited[0] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                depthParity[v] = 1 - depthParity[u];
                q.push(v);
            }
        }
    }
    
    // Step 2: Check if coloring matches bipartite structure
    // Pattern A: even-depth = White(0), odd-depth = Black(1)
    // Pattern B: even-depth = Black(1), odd-depth = White(0)
    
    bool patternA = true, patternB = true;
    for (int i = 0; i < n; i++) {
        if (color[i] != depthParity[i]) patternA = false;
        if (color[i] != (1 - depthParity[i])) patternB = false;
    }
    
    if (!patternA && !patternB) return -1;  // Coloring doesn't alternate
    
    // Step 3: Find any node with degree <= 2
    // For pattern A, root should be White; for pattern B, root should be Black
    int expectedRootColor = patternA ? 0 : 1;
    
    for (int i = 0; i < n; i++) {
        if (adj[i].size() <= 2 && color[i] == expectedRootColor) {
            return i;
        }
    }
    
    return -1;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ SOLUTION 3: Binary Tree with RGB Color Sequence                             │
│                                                                             │
│ Time Complexity:  O(V + E) per sequence check, O(3 * (V + E)) = O(V + E)    │
│ Space Complexity: O(V) - for BFS queue and visited array                    │
└─────────────────────────────────────────────────────────────────────────────┘
*/

// Sequences: R(0) -> B(1) -> W(2) -> R(0)...
// sequence[0] = starting color, follows pattern: seq[depth % 3]
bool checkRGBSequenceBFS(int root, vector<vector<int>>& adj, vector<int>& color, 
                          vector<int>& sequence) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<pair<int, int>> q;  // {node, depth}
    
    q.push({root, 0});
    visited[root] = true;
    
    while (!q.empty()) {
        auto [u, depth] = q.front();
        q.pop();
        
        int expectedColor = sequence[depth % 3];
        if (color[u] != expectedColor) {
            return false;
        }
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push({v, depth + 1});
            }
        }
    }
    
    return true;
}

int findRootRGBColors(int n, vector<vector<int>>& adj, vector<int>& color) {
    // color[i] = 0 (Red), 1 (Blue), 2 (White)
    
    // All possible 3-color sequences (cyclic permutations)
    vector<vector<int>> sequences = {
        {0, 1, 2},  // R -> B -> W -> R...
        {1, 2, 0},  // B -> W -> R -> B...
        {2, 0, 1}   // W -> R -> B -> W...
    };
    
    for (int root = 0; root < n; root++) {
        // Check 1: Must have degree <= 2
        if (adj[root].size() > 2) continue;
        
        // Check 2: Try all 3 sequences
        for (auto& seq : sequences) {
            // Root color must match first color in sequence
            if (color[root] == seq[0] && checkRGBSequenceBFS(root, adj, color, seq)) {
                return root;
            }
        }
    }
    
    return -1;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ MAIN - Test all solutions                                                   │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int main() {
    cout << "=== Convert Graph to Binary Tree ===\n\n";
    
    // Test Graph:
    //     0(W) ─── 1(B) ─── 2(W)
    //              │
    //             3(W)
    
    int n = 4;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edges = {{0,1}, {1,2}, {1,3}};
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // ─────────────────────────────────────────────────────────────
    // PROBLEM 1: Find valid root
    cout << "PROBLEM 1: Find Valid Binary Tree Root\n";
    cout << "Graph: 0──1──2 with 1──3\n";
    cout << "Degrees: 0→1, 1→3, 2→1, 3→1\n";
    
    int root1 = findValidRoot(n, adj);
    cout << "Valid root: " << root1 << "\n";
    
    vector<int> allRoots = findAllValidRoots(n, adj);
    cout << "All valid roots: ";
    for (int r : allRoots) cout << r << " ";
    cout << "\n\n";
    
    // ─────────────────────────────────────────────────────────────
    // PROBLEM 2: Alternating colors
    cout << "PROBLEM 2: Alternating Black/White\n";
    
    // Test case that works: 0(W), 1(B), 2(W), 3(W)
    // If root = 0: Level 0: W, Level 1: B, Level 2: W, W ✓
    vector<int> colorBW = {0, 1, 0, 0};  // W, B, W, W
    cout << "Colors: 0(W), 1(B), 2(W), 3(W)\n";
    
    int root2 = findRootAlternatingColors(n, adj, colorBW);
    cout << "Valid root (naive): " << root2 << "\n";
    
    int root2opt = findRootAlternatingOptimized(n, adj, colorBW);
    cout << "Valid root (optimized): " << root2opt << "\n\n";
    
    // ─────────────────────────────────────────────────────────────
    // PROBLEM 3: RGB sequence
    cout << "PROBLEM 3: RGB Color Sequence\n";
    
    // For sequence R->B->W->R...
    // If root = 0: Level 0: R, Level 1: B, Level 2: W, W
    vector<int> colorRGB = {0, 1, 2, 2};  // R, B, W, W
    cout << "Colors: 0(R), 1(B), 2(W), 3(W)\n";
    
    int root3 = findRootRGBColors(n, adj, colorRGB);
    cout << "Valid root: " << root3 << "\n";
    
    return 0;
}

/*
================================================================================
                            COMPLEXITY SUMMARY
================================================================================

┌──────────────┬─────────────────────┬─────────────────────┐
│   Problem    │  Time Complexity    │  Space Complexity   │
├──────────────┼─────────────────────┼─────────────────────┤
│ 1. Basic     │ O(V)                │ O(1)                │
│ 2. BW Naive  │ O(V × (V + E))      │ O(V)                │
│ 2. BW Opt    │ O(V + E)            │ O(V)                │
│ 3. RGB       │ O(V + E)            │ O(V)                │
└──────────────┴─────────────────────┴─────────────────────┘

================================================================================
                            INTERVIEW TIPS
================================================================================

1. CLARIFYING QUESTIONS:
   - Is the graph guaranteed to be connected? (Yes, stated)
   - Is the graph guaranteed to be acyclic? (Yes, stated)
   - Can there be multiple valid roots? (Yes, return any)

2. KEY INSIGHTS TO MENTION:
   - Root has no parent, so degree = number of children
   - For binary tree, root needs degree ≤ 2
   - For color alternation, it's essentially checking bipartite coloring
   - Tree is always bipartite, so just verify given colors match

3. EDGE CASES:
   - Single node (always valid root)
   - Linear chain (any node is valid for Problem 1)
   - All nodes have degree 3 (no valid root)

4. FOLLOW-UP YOU MIGHT GET:
   - What if we want the tree to be balanced?
   - What if we want minimum height?
   - What if colors can be changed? Minimum changes needed?

================================================================================
*/
