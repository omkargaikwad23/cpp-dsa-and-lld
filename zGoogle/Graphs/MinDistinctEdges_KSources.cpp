/*
================================================================================
        MINIMUM DISTINCT EDGES - Multiple Sources to One Destination
================================================================================

PROBLEM:
Given k sources (A, B, C, ...) and one destination D in an unweighted graph.
Find the minimum number of distinct edges that all sources will traverse to 
reach D.

Key Insight: If multiple sources share an edge, it counts only ONCE.

This is essentially a STEINER TREE problem for unweighted graphs.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// BFS to get shortest distances from a source
vector<int> bfs(int start, const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, INT_MAX);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ SOLUTION 1: Two Sources (A, B) to Destination D                             │
│                                                                             │
│ Time: O(V + E) - 3 BFS calls                                                │
│ Space: O(V)                                                                 │
└─────────────────────────────────────────────────────────────────────────────┘

Example:
        A ─── 1 ─── 2 ─── D
              │
              B

Option 1: A→D independent, B→D independent = 3 + 2 = 5 edges
Option 2: A→1, B→1, then 1→D together = 1 + 1 + 2 = 4 edges ✓

Key Insight: Try every possible "meeting point" x where paths merge.
Distinct edges = dist(A,x) + dist(B,x) + dist(x,D)
*/

int minDistinctEdges_2Sources(vector<vector<int>>& adj, int A, int B, int D) {
    vector<int> distA = bfs(A, adj);
    vector<int> distB = bfs(B, adj);
    vector<int> distD = bfs(D, adj);
    
    int n = adj.size();
    int ans = INT_MAX;
    
    // Try each node as the meeting point
    for (int x = 0; x < n; x++) {
        if (distA[x] == INT_MAX || distB[x] == INT_MAX || distD[x] == INT_MAX) 
            continue;
        
        // A→x + B→x + x→D (shared path from x to D)
        ans = min(ans, distA[x] + distB[x] + distD[x]);
    }
    
    return ans;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ SOLUTION 2: Three Sources (A, B, C) to Destination D                        │
│                                                                             │
│ Time: O(V² + VE) - BFS from all sources + try all meeting point pairs       │
│ Space: O(V)                                                                 │
└─────────────────────────────────────────────────────────────────────────────┘

For 3 sources, the optimal structure can be:

Case 1: All three meet at single point x, then go to D together
        A ──┐
        B ──┼── x ─── D
        C ──┘
        
        Cost = dist(A,x) + dist(B,x) + dist(C,x) + dist(x,D)

Case 2: Two meet at x, third joins at y (on path x→D)
        A ──┐
        B ──┼── x ─── y ─── D
                      │
                      C
        
        Cost = dist(A,x) + dist(B,x) + dist(x,y) + dist(C,y) + dist(y,D)
             = dist(A,x) + dist(B,x) + dist(C,y) + dist(x,D)
             (since dist(x,y) + dist(y,D) = dist(x,D) when y is on shortest path)

Key Insight: We need to try:
1. All possible single meeting points (like 2-source case)
2. All possible pairs of meeting points for Steiner-like structure
*/

int minDistinctEdges_3Sources(vector<vector<int>>& adj, int A, int B, int C, int D) {
    vector<int> distA = bfs(A, adj);
    vector<int> distB = bfs(B, adj);
    vector<int> distC = bfs(C, adj);
    vector<int> distD = bfs(D, adj);
    
    int n = adj.size();
    int ans = INT_MAX;
    
    // Case 1: All three sources meet at a single point x, then go to D
    for (int x = 0; x < n; x++) {
        if (distA[x] == INT_MAX || distB[x] == INT_MAX || 
            distC[x] == INT_MAX || distD[x] == INT_MAX) continue;
        
        ans = min(ans, distA[x] + distB[x] + distC[x] + distD[x]);
    }
    
    // Case 2: Two sources meet at x, third source joins at different point y
    // The Steiner point structure: paths from sources can merge at different points
    // 
    // Try all pairs (x, y) where:
    // - Two sources meet at x
    // - Third source meets at y
    // - x and y are on the path to D
    
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            if (distD[x] == INT_MAX || distD[y] == INT_MAX) continue;
            
            // Check if x is on shortest path from y to D (or vice versa)
            // This ensures we're not double counting edges
            
            // Structure: A,B → x → y → D, C → y
            if (distA[x] != INT_MAX && distB[x] != INT_MAX && distC[y] != INT_MAX) {
                // dist(x,y) via shortest path consideration
                int xy_dist = abs(distD[x] - distD[y]);  // If y is between x and D
                if (distD[y] <= distD[x]) {  // y is closer to D than x
                    int cost = distA[x] + distB[x] + distC[y] + distD[x];
                    // But we may double count x→y and y→D
                    // Actually need: distA[x] + distB[x] + (distD[x] - distD[y]) + distC[y] + distD[y]
                    //              = distA[x] + distB[x] + distC[y] + distD[x]
                    ans = min(ans, cost);
                }
            }
            
            // Try other pairings: (A,C meet at x), (B,C meet at x)
            if (distA[x] != INT_MAX && distC[x] != INT_MAX && distB[y] != INT_MAX) {
                if (distD[y] <= distD[x]) {
                    ans = min(ans, distA[x] + distC[x] + distB[y] + distD[x]);
                }
            }
            
            if (distB[x] != INT_MAX && distC[x] != INT_MAX && distA[y] != INT_MAX) {
                if (distD[y] <= distD[x]) {
                    ans = min(ans, distB[x] + distC[x] + distA[y] + distD[x]);
                }
            }
        }
    }
    
    return ans;
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ SOLUTION 3: K Sources to Destination D (General Case)                       │
│                                                                             │
│ Time: O(3^k * V + k * (V + E)) - Steiner Tree DP with BFS preprocessing     │
│ Space: O(2^k * V)                                                           │
│                                                                             │
│ For small k (≤ 10), this is practical. For larger k, use approximation.     │
└─────────────────────────────────────────────────────────────────────────────┘

This is the Steiner Tree problem on unweighted graph.
We use bitmask DP where state = (node, subset of sources connected).
*/

int minDistinctEdges_KSources(vector<vector<int>>& adj, vector<int>& sources, int D) {
    int n = adj.size();
    int k = sources.size();
    int fullMask = (1 << k) - 1;
    
    // dp[mask][v] = min edges to connect sources in 'mask' and reach node v
    vector<vector<int>> dp(1 << k, vector<int>(n, INT_MAX));
    
    // BFS from each source
    vector<vector<int>> dist(k);
    for (int i = 0; i < k; i++) {
        dist[i] = bfs(sources[i], adj);
    }
    
    // Initialize: each source reaches itself with 0 edges
    for (int i = 0; i < k; i++) {
        for (int v = 0; v < n; v++) {
            if (dist[i][v] != INT_MAX) {
                dp[1 << i][v] = dist[i][v];
            }
        }
    }
    
    // DP: combine subsets
    for (int mask = 1; mask <= fullMask; mask++) {
        // Combine two disjoint subsets at each node
        for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            int other = mask ^ sub;
            for (int v = 0; v < n; v++) {
                if (dp[sub][v] != INT_MAX && dp[other][v] != INT_MAX) {
                    dp[mask][v] = min(dp[mask][v], dp[sub][v] + dp[other][v]);
                }
            }
        }
        
        // Extend: use BFS to propagate dp[mask] values
        // (This step optimizes finding shortest path between meeting points)
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
        for (int v = 0; v < n; v++) {
            if (dp[mask][v] != INT_MAX) {
                pq.push({dp[mask][v], v});
            }
        }
        
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            
            if (d > dp[mask][u]) continue;
            
            for (int v : adj[u]) {
                if (dp[mask][u] + 1 < dp[mask][v]) {
                    dp[mask][v] = dp[mask][u] + 1;
                    pq.push({dp[mask][v], v});
                }
            }
        }
    }
    
    return dp[fullMask][D];
}


/*
┌─────────────────────────────────────────────────────────────────────────────┐
│ MAIN - Test all solutions                                                   │
└─────────────────────────────────────────────────────────────────────────────┘
*/

int main() {
    cout << "=== Minimum Distinct Edges ===\n\n";
    
    /*
    Test Graph:
    
        0 ─── 1 ─── 2 ─── 3
              │     │
              4     5
              
    Edges: 0-1, 1-2, 2-3, 1-4, 2-5
    */
    
    int n = 6;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> edges = {{0,1}, {1,2}, {2,3}, {1,4}, {2,5}};
    for (auto [u, v] : edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    cout << "Graph: 0─1─2─3 with branches 1─4 and 2─5\n\n";
    
    // ─────────────────────────────────────────────────────────────
    // Test 1: Two sources
    cout << "TEST 1: Two Sources (A=0, B=4) to Destination D=3\n";
    cout << "Expected: 0→1→2→3 and 4→1→2→3, meet at 1\n";
    cout << "Distinct edges: 0-1, 1-4, 1-2, 2-3 = 4\n";
    int ans1 = minDistinctEdges_2Sources(adj, 0, 4, 3);
    cout << "Result: " << ans1 << "\n\n";
    
    // ─────────────────────────────────────────────────────────────
    // Test 2: Three sources
    cout << "TEST 2: Three Sources (A=0, B=4, C=5) to Destination D=3\n";
    cout << "Expected: All paths merge towards node 2, then to 3\n";
    cout << "Distinct edges: 0-1, 1-4, 1-2, 2-5, 2-3 = 5\n";
    int ans2 = minDistinctEdges_3Sources(adj, 0, 4, 5, 3);
    cout << "Result: " << ans2 << "\n\n";
    
    // ─────────────────────────────────────────────────────────────
    // Test 3: K sources (general solution)
    cout << "TEST 3: K Sources General Solution\n";
    vector<int> sources2 = {0, 4};
    vector<int> sources3 = {0, 4, 5};
    
    cout << "2 sources (0,4) to D=3: " << minDistinctEdges_KSources(adj, sources2, 3) << "\n";
    cout << "3 sources (0,4,5) to D=3: " << minDistinctEdges_KSources(adj, sources3, 3) << "\n";
    
    return 0;
}


/*
================================================================================
                            COMPLEXITY SUMMARY
================================================================================

┌────────────────────┬─────────────────────────┬─────────────────────┐
│   Problem          │  Time Complexity        │  Space Complexity   │
├────────────────────┼─────────────────────────┼─────────────────────┤
│ 2 Sources          │ O(V + E)                │ O(V)                │
│ 3 Sources          │ O(V² + VE)              │ O(V)                │
│ K Sources (Steiner)│ O(3^k * V + k(V+E))     │ O(2^k * V)          │
└────────────────────┴─────────────────────────┴─────────────────────┘

================================================================================
                            INTERVIEW TIPS
================================================================================

1. CLARIFYING QUESTIONS:
   - Is the graph weighted or unweighted? (affects algorithm choice)
   - How many sources? (2 vs 3 vs k affects complexity)
   - Can sources be the same as destination?

2. KEY INSIGHT TO MENTION:
   - This is the Steiner Tree problem
   - For unweighted graphs, BFS gives shortest paths
   - The "meeting point" approach works because paths merge optimally

3. START SIMPLE:
   - First solve for 2 sources (easy BFS approach)
   - Then extend to 3 sources
   - Mention Steiner Tree DP for general k

4. RELATED PROBLEMS:
   - PathLengthOfTwoFriends (same problem, 2 sources)
   - Minimum Spanning Tree (all nodes connected)
   - Shortest Path algorithms

================================================================================
*/
