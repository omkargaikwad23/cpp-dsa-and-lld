/*
================================================================================
                    TOPOLOGICAL SORT & ADVANCED GRAPH PROBLEMS
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TOPOLOGICAL SORT PROBLEMS
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM 1: Course Schedule (LeetCode 207)
─────────────────────────────────────────
Check if all courses can be finished (no cycle).
Time: O(V + E) | Space: O(V)
*/
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    
    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        indegree[p[0]]++;
    }
    
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    int completed = 0;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        completed++;
        
        for (int next : adj[course]) {
            if (--indegree[next] == 0) q.push(next);
        }
    }
    
    return completed == numCourses;
}


/*
PROBLEM 2: Alien Dictionary (LeetCode 269) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────
Derive order of characters from sorted alien words.
Time: O(C) where C = total characters | Space: O(1)
*/
string alienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> adj;
    unordered_map<char, int> indegree;
    
    // Initialize all characters
    for (const string& word : words) {
        for (char c : word) {
            indegree[c] = 0;
        }
    }
    
    // Build graph
    for (int i = 0; i < words.size() - 1; i++) {
        string& w1 = words[i];
        string& w2 = words[i + 1];
        
        // Check for invalid case: "abc" before "ab"
        if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2) {
            return "";
        }
        
        for (int j = 0; j < min(w1.size(), w2.size()); j++) {
            if (w1[j] != w2[j]) {
                if (!adj[w1[j]].count(w2[j])) {
                    adj[w1[j]].insert(w2[j]);
                    indegree[w2[j]]++;
                }
                break;
            }
        }
    }
    
    // Topological sort
    queue<char> q;
    for (auto& [c, deg] : indegree) {
        if (deg == 0) q.push(c);
    }
    
    string result;
    while (!q.empty()) {
        char c = q.front();
        q.pop();
        result += c;
        
        for (char next : adj[c]) {
            if (--indegree[next] == 0) q.push(next);
        }
    }
    
    return result.size() == indegree.size() ? result : "";
}


/*
PROBLEM 3: Parallel Courses (LeetCode 1136) ⭐
─────────────────────────────────────────────
Minimum semesters to finish all courses.
Time: O(V + E) | Space: O(V)
*/
int minimumSemesters(int n, vector<vector<int>>& relations) {
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    
    for (auto& r : relations) {
        adj[r[0]].push_back(r[1]);
        indegree[r[1]]++;
    }
    
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    int semesters = 0, completed = 0;
    
    while (!q.empty()) {
        semesters++;
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            int course = q.front();
            q.pop();
            completed++;
            
            for (int next : adj[course]) {
                if (--indegree[next] == 0) q.push(next);
            }
        }
    }
    
    return completed == n ? semesters : -1;
}


/*
PROBLEM 4: Longest Increasing Path in Matrix (LeetCode 329) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────────────────────────────
DFS with memoization (topological order by value).
Time: O(m*n) | Space: O(m*n)
*/
int longestIncreasingPath(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    function<int(int, int)> dfs = [&](int r, int c) -> int {
        if (dp[r][c]) return dp[r][c];
        
        dp[r][c] = 1;
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                matrix[nr][nc] > matrix[r][c]) {
                dp[r][c] = max(dp[r][c], 1 + dfs(nr, nc));
            }
        }
        
        return dp[r][c];
    };
    
    int maxLen = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            maxLen = max(maxLen, dfs(i, j));
        }
    }
    
    return maxLen;
}


// ═══════════════════════════════════════════════════════════════════════════
// STRONGLY CONNECTED COMPONENTS (SCC)
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM 5: Critical Connections (LeetCode 1192) ⭐ BRIDGES
──────────────────────────────────────────────────────────
Find all bridges (edges whose removal disconnects graph).
Tarjan's algorithm.
Time: O(V + E) | Space: O(V)
*/
vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto& e : connections) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
    }
    
    vector<int> disc(n, -1), low(n);
    vector<vector<int>> bridges;
    int timer = 0;
    
    function<void(int, int)> dfs = [&](int u, int parent) {
        disc[u] = low[u] = timer++;
        
        for (int v : adj[u]) {
            if (v == parent) continue;
            
            if (disc[v] == -1) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else {
                low[u] = min(low[u], disc[v]);
            }
        }
    };
    
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) dfs(i, -1);
    }
    
    return bridges;
}


/*
PROBLEM 6: Strongly Connected Components - Kosaraju's
─────────────────────────────────────────────────────
Find all SCCs in directed graph.
Time: O(V + E) | Space: O(V)
*/
int countSCCs(int n, vector<vector<int>>& edges) {
    vector<vector<int>> adj(n), radj(n);
    for (auto& e : edges) {
        adj[e[0]].push_back(e[1]);
        radj[e[1]].push_back(e[0]);
    }
    
    // First DFS: get finishing order
    vector<bool> visited(n, false);
    stack<int> order;
    
    function<void(int)> dfs1 = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) dfs1(v);
        }
        order.push(u);
    };
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) dfs1(i);
    }
    
    // Second DFS: on reversed graph
    fill(visited.begin(), visited.end(), false);
    int sccCount = 0;
    
    function<void(int)> dfs2 = [&](int u) {
        visited[u] = true;
        for (int v : radj[u]) {
            if (!visited[v]) dfs2(v);
        }
    };
    
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (!visited[u]) {
            dfs2(u);
            sccCount++;
        }
    }
    
    return sccCount;
}


// ═══════════════════════════════════════════════════════════════════════════
// BIPARTITE GRAPH
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM 7: Is Graph Bipartite? (LeetCode 785)
─────────────────────────────────────────────
Two-color the graph.
Time: O(V + E) | Space: O(V)
*/
bool isBipartite(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, -1);
    
    for (int i = 0; i < n; i++) {
        if (color[i] != -1) continue;
        
        queue<int> q;
        q.push(i);
        color[i] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : graph[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    
    return true;
}


/*
PROBLEM 8: Possible Bipartition (LeetCode 886)
──────────────────────────────────────────────
Split people into two groups where enemies aren't together.
*/
bool possibleBipartition(int n, vector<vector<int>>& dislikes) {
    vector<vector<int>> adj(n + 1);
    for (auto& d : dislikes) {
        adj[d[0]].push_back(d[1]);
        adj[d[1]].push_back(d[0]);
    }
    
    vector<int> color(n + 1, -1);
    
    for (int i = 1; i <= n; i++) {
        if (color[i] != -1) continue;
        
        queue<int> q;
        q.push(i);
        color[i] = 0;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = 1 - color[u];
                    q.push(v);
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
        }
    }
    
    return true;
}


// ═══════════════════════════════════════════════════════════════════════════
// MINIMUM SPANNING TREE
// ═══════════════════════════════════════════════════════════════════════════

/*
PROBLEM 9: Min Cost to Connect All Points (LeetCode 1584)
─────────────────────────────────────────────────────────
Prim's algorithm for MST.
Time: O(n² log n) | Space: O(n²)
*/
int minCostConnectPoints(vector<vector<int>>& points) {
    int n = points.size();
    vector<bool> inMST(n, false);
    vector<int> minCost(n, INT_MAX);
    minCost[0] = 0;
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, 0});
    
    int totalCost = 0;
    
    while (!pq.empty()) {
        auto [cost, u] = pq.top();
        pq.pop();
        
        if (inMST[u]) continue;
        inMST[u] = true;
        totalCost += cost;
        
        for (int v = 0; v < n; v++) {
            if (!inMST[v]) {
                int dist = abs(points[u][0] - points[v][0]) + 
                           abs(points[u][1] - points[v][1]);
                if (dist < minCost[v]) {
                    minCost[v] = dist;
                    pq.push({dist, v});
                }
            }
        }
    }
    
    return totalCost;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== TopSort & Advanced Graph Problems ===\n\n";
    
    // Course Schedule
    vector<vector<int>> prereqs1 = {{1,0},{2,1}};
    cout << "1. Can finish courses: " << (canFinish(3, prereqs1) ? "Yes" : "No") << "\n";
    
    // Alien Dictionary
    vector<string> words = {"wrt","wrf","er","ett","rftt"};
    cout << "2. Alien order: " << alienOrder(words) << "\n";
    
    // Longest Increasing Path
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
    cout << "4. Longest increasing path: " << longestIncreasingPath(matrix) << "\n";
    
    // Bipartite
    vector<vector<int>> graph = {{1,3},{0,2},{1,3},{0,2}};
    cout << "7. Is bipartite: " << (isBipartite(graph) ? "Yes" : "No") << "\n";
    
    return 0;
}

/*
================================================================================
ADVANCED PATTERNS:
1. Topological Sort: Kahn's (BFS) or DFS with post-order
2. Bridges/Articulation: Tarjan's (disc/low arrays)
3. SCC: Kosaraju's (2 DFS) or Tarjan's
4. Bipartite: Two-coloring with BFS/DFS
5. MST: Kruskal's (Union-Find) or Prim's (Priority Queue)
================================================================================
*/

