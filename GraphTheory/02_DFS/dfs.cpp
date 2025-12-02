/*
================================================================================
                    DFS (Depth-First Search)
================================================================================

USE WHEN:
- Cycle detection
- Connected components
- Path finding (all paths)
- Topological sort
- Backtracking problems

TIME: O(V + E) | SPACE: O(V)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 1: Basic DFS (Graph)
// ═══════════════════════════════════════════════════════════════════════════

void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;
    // Process node u
    
    for (int v : adj[u]) {
        if (!visited[v]) {
            dfs(v, adj, visited);
        }
    }
}

// Iterative DFS
void dfsIterative(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    stack<int> stk;
    
    stk.push(start);
    
    while (!stk.empty()) {
        int u = stk.top();
        stk.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        // Process node u
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                stk.push(v);
            }
        }
    }
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 2: DFS on Grid
// ═══════════════════════════════════════════════════════════════════════════

void dfsGrid(vector<vector<int>>& grid, int r, int c, 
             vector<vector<bool>>& visited) {
    int m = grid.size(), n = grid[0].size();
    if (r < 0 || r >= m || c < 0 || c >= n) return;
    if (visited[r][c] || grid[r][c] == 0) return;
    
    visited[r][c] = true;
    // Process cell (r, c)
    
    dfsGrid(grid, r + 1, c, visited);
    dfsGrid(grid, r - 1, c, visited);
    dfsGrid(grid, r, c + 1, visited);
    dfsGrid(grid, r, c - 1, visited);
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 3: Cycle Detection (Directed Graph) ⭐
// ═══════════════════════════════════════════════════════════════════════════

// Using colors: 0=white (unvisited), 1=gray (in progress), 2=black (done)
bool hasCycleDirected(int n, vector<vector<int>>& adj) {
    vector<int> color(n, 0);
    
    function<bool(int)> dfs = [&](int u) -> bool {
        color[u] = 1;  // Gray - in current path
        
        for (int v : adj[u]) {
            if (color[v] == 1) return true;   // Back edge = cycle
            if (color[v] == 0 && dfs(v)) return true;
        }
        
        color[u] = 2;  // Black - done
        return false;
    };
    
    for (int i = 0; i < n; i++) {
        if (color[i] == 0 && dfs(i)) return true;
    }
    
    return false;
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 4: Cycle Detection (Undirected Graph)
// ═══════════════════════════════════════════════════════════════════════════

bool hasCycleUndirected(int n, vector<vector<int>>& adj) {
    vector<bool> visited(n, false);
    
    function<bool(int, int)> dfs = [&](int u, int parent) -> bool {
        visited[u] = true;
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                if (dfs(v, u)) return true;
            } else if (v != parent) {
                return true;  // Back edge to non-parent = cycle
            }
        }
        
        return false;
    };
    
    for (int i = 0; i < n; i++) {
        if (!visited[i] && dfs(i, -1)) return true;
    }
    
    return false;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Clone Graph (LeetCode 133) ⭐
// ═══════════════════════════════════════════════════════════════════════════

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int v = 0) : val(v) {}
};

Node* cloneGraph(Node* node) {
    if (!node) return nullptr;
    
    unordered_map<Node*, Node*> visited;
    
    function<Node*(Node*)> dfs = [&](Node* n) -> Node* {
        if (visited.count(n)) return visited[n];
        
        Node* clone = new Node(n->val);
        visited[n] = clone;
        
        for (Node* neighbor : n->neighbors) {
            clone->neighbors.push_back(dfs(neighbor));
        }
        
        return clone;
    };
    
    return dfs(node);
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Pacific Atlantic Water Flow (LeetCode 417) ⭐
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();
    vector<vector<bool>> pacific(m, vector<bool>(n, false));
    vector<vector<bool>> atlantic(m, vector<bool>(n, false));
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    function<void(int, int, vector<vector<bool>>&)> dfs = 
        [&](int r, int c, vector<vector<bool>>& ocean) {
        ocean[r][c] = true;
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                !ocean[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                dfs(nr, nc, ocean);
            }
        }
    };
    
    // DFS from Pacific (top + left)
    for (int i = 0; i < m; i++) dfs(i, 0, pacific);
    for (int j = 0; j < n; j++) dfs(0, j, pacific);
    
    // DFS from Atlantic (bottom + right)
    for (int i = 0; i < m; i++) dfs(i, n-1, atlantic);
    for (int j = 0; j < n; j++) dfs(m-1, j, atlantic);
    
    vector<vector<int>> result;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (pacific[i][j] && atlantic[i][j]) {
                result.push_back({i, j});
            }
        }
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Surrounded Regions (LeetCode 130)
// ═══════════════════════════════════════════════════════════════════════════

void solve(vector<vector<char>>& board) {
    int m = board.size(), n = board[0].size();
    
    function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != 'O') return;
        board[r][c] = 'T';  // Temporary mark
        dfs(r+1, c); dfs(r-1, c); dfs(r, c+1); dfs(r, c-1);
    };
    
    // Mark border-connected O's
    for (int i = 0; i < m; i++) { dfs(i, 0); dfs(i, n-1); }
    for (int j = 0; j < n; j++) { dfs(0, j); dfs(m-1, j); }
    
    // Flip
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            else if (board[i][j] == 'T') board[i][j] = 'O';
        }
    }
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 4: Max Area of Island (LeetCode 695)
// ═══════════════════════════════════════════════════════════════════════════

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    
    function<int(int, int)> dfs = [&](int r, int c) -> int {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) return 0;
        grid[r][c] = 0;
        return 1 + dfs(r+1, c) + dfs(r-1, c) + dfs(r, c+1) + dfs(r, c-1);
    };
    
    int maxArea = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                maxArea = max(maxArea, dfs(i, j));
            }
        }
    }
    
    return maxArea;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 5: All Paths From Source to Target (LeetCode 797)
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> result;
    vector<int> path;
    
    function<void(int)> dfs = [&](int u) {
        path.push_back(u);
        
        if (u == n - 1) {
            result.push_back(path);
        } else {
            for (int v : graph[u]) {
                dfs(v);
            }
        }
        
        path.pop_back();
    };
    
    dfs(0);
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== DFS Module ===\n\n";
    
    // Test Cycle Detection (Directed)
    vector<vector<int>> adj = {{1}, {2}, {0}};  // 0->1->2->0
    cout << "1. Has cycle (directed): " << (hasCycleDirected(3, adj) ? "Yes" : "No") << "\n";
    
    // Test Max Area
    vector<vector<int>> grid = {{0,0,1,0,0},{0,1,1,1,0},{0,0,1,0,0}};
    cout << "4. Max island area: " << maxAreaOfIsland(grid) << "\n";
    
    // Test All Paths
    vector<vector<int>> graph = {{1,2},{3},{3},{}};
    auto paths = allPathsSourceTarget(graph);
    cout << "5. Paths from 0 to 3: " << paths.size() << "\n";
    
    return 0;
}

/*
================================================================================
                    DFS PATTERNS SUMMARY
================================================================================

1. BASIC DFS:
   - Recursion or stack-based
   - Mark visited before/after processing

2. CYCLE DETECTION:
   - Directed: 3 colors (white/gray/black)
   - Undirected: Track parent node

3. CONNECTED COMPONENTS:
   - Run DFS from each unvisited node
   - Count DFS calls

4. PATH FINDING:
   - Backtracking with path vector
   - Add node -> recurse -> remove node

5. GRID DFS:
   - Boundary check + obstacle check + visited check
   - Mark visited early to avoid stack overflow

================================================================================
*/

