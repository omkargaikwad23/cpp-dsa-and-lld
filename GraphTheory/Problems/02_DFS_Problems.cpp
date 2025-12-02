/*
================================================================================
                    DFS PROBLEMS - Google Interview Favorites
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Clone Graph (LeetCode 133) ⭐ GOOGLE CLASSIC
───────────────────────────────────────────────────────
Deep copy a graph.
Time: O(V + E) | Space: O(V)
*/
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node(int _val = 0) : val(_val) {}
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


/*
PROBLEM 2: Pacific Atlantic Water Flow (LeetCode 417) ⭐
───────────────────────────────────────────────────────
Find cells that can flow to both oceans.
Time: O(m*n) | Space: O(m*n)
*/
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
    
    // DFS from Pacific (top and left)
    for (int i = 0; i < m; i++) dfs(i, 0, pacific);
    for (int j = 0; j < n; j++) dfs(0, j, pacific);
    
    // DFS from Atlantic (bottom and right)
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


/*
PROBLEM 3: Surrounded Regions (LeetCode 130)
────────────────────────────────────────────
Capture regions not connected to border.
Time: O(m*n) | Space: O(m*n)
*/
void solve(vector<vector<char>>& board) {
    int m = board.size(), n = board[0].size();
    
    function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= m || c < 0 || c >= n || board[r][c] != 'O') return;
        board[r][c] = 'T';  // Temporary mark
        dfs(r+1, c); dfs(r-1, c); dfs(r, c+1); dfs(r, c-1);
    };
    
    // Mark border-connected O's
    for (int i = 0; i < m; i++) {
        dfs(i, 0);
        dfs(i, n-1);
    }
    for (int j = 0; j < n; j++) {
        dfs(0, j);
        dfs(m-1, j);
    }
    
    // Flip O to X, T back to O
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 'O') board[i][j] = 'X';
            else if (board[i][j] == 'T') board[i][j] = 'O';
        }
    }
}


/*
PROBLEM 4: Number of Closed Islands (LeetCode 1254)
───────────────────────────────────────────────────
Count islands not touching border.
*/
int closedIsland(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    
    function<bool(int, int)> dfs = [&](int r, int c) -> bool {
        if (r < 0 || r >= m || c < 0 || c >= n) return false;
        if (grid[r][c] == 1) return true;
        
        grid[r][c] = 1;
        bool top = dfs(r-1, c);
        bool bottom = dfs(r+1, c);
        bool left = dfs(r, c-1);
        bool right = dfs(r, c+1);
        
        return top && bottom && left && right;
    };
    
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0 && dfs(i, j)) {
                count++;
            }
        }
    }
    
    return count;
}


/*
PROBLEM 5: Max Area of Island (LeetCode 695)
────────────────────────────────────────────
Find largest island.
Time: O(m*n) | Space: O(m*n)
*/
int maxAreaOfIsland(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    int maxArea = 0;
    
    function<int(int, int)> dfs = [&](int r, int c) -> int {
        if (r < 0 || r >= m || c < 0 || c >= n || grid[r][c] == 0) return 0;
        grid[r][c] = 0;
        return 1 + dfs(r+1, c) + dfs(r-1, c) + dfs(r, c+1) + dfs(r, c-1);
    };
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                maxArea = max(maxArea, dfs(i, j));
            }
        }
    }
    
    return maxArea;
}


/*
PROBLEM 6: All Paths From Source to Target (LeetCode 797)
─────────────────────────────────────────────────────────
Find all paths from 0 to n-1 in DAG.
Time: O(2^n * n) | Space: O(n)
*/
vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> result;
    vector<int> path;
    
    function<void(int)> dfs = [&](int node) {
        path.push_back(node);
        
        if (node == n - 1) {
            result.push_back(path);
        } else {
            for (int next : graph[node]) {
                dfs(next);
            }
        }
        
        path.pop_back();
    };
    
    dfs(0);
    return result;
}


/*
PROBLEM 7: Course Schedule II (LeetCode 210) ⭐ TOPOLOGICAL SORT
───────────────────────────────────────────────────────────────
Return order to take courses (topological sort).
Time: O(V + E) | Space: O(V)
*/
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
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
    
    vector<int> order;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        order.push_back(course);
        
        for (int next : adj[course]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    return order.size() == numCourses ? order : vector<int>();
}


/*
PROBLEM 8: Detect Cycle in Directed Graph
─────────────────────────────────────────
Using DFS coloring (WHITE=0, GRAY=1, BLACK=2).
*/
bool hasCycleDirected(int n, vector<vector<int>>& adj) {
    vector<int> color(n, 0);  // 0=white, 1=gray, 2=black
    
    function<bool(int)> dfs = [&](int u) -> bool {
        color[u] = 1;  // Gray - being processed
        
        for (int v : adj[u]) {
            if (color[v] == 1) return true;  // Back edge
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


/*
PROBLEM 9: Find Eventual Safe States (LeetCode 802)
───────────────────────────────────────────────────
Find nodes not in any cycle.
*/
vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> color(n, 0);
    
    function<bool(int)> isSafe = [&](int node) -> bool {
        if (color[node] > 0) return color[node] == 2;
        
        color[node] = 1;  // Being visited
        for (int next : graph[node]) {
            if (!isSafe(next)) return false;
        }
        color[node] = 2;  // Safe
        return true;
    };
    
    vector<int> result;
    for (int i = 0; i < n; i++) {
        if (isSafe(i)) result.push_back(i);
    }
    
    return result;
}


/*
PROBLEM 10: Number of Provinces (LeetCode 547)
──────────────────────────────────────────────
Count connected components.
*/
int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<bool> visited(n, false);
    int provinces = 0;
    
    function<void(int)> dfs = [&](int i) {
        visited[i] = true;
        for (int j = 0; j < n; j++) {
            if (isConnected[i][j] && !visited[j]) {
                dfs(j);
            }
        }
    };
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            provinces++;
        }
    }
    
    return provinces;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== DFS Problems ===\n\n";
    
    // Max Area of Island
    vector<vector<int>> grid = {{0,0,1,0,0},{0,1,1,1,0},{0,0,1,0,0}};
    cout << "5. Max area of island: " << maxAreaOfIsland(grid) << "\n";
    
    // Course Schedule II
    vector<vector<int>> prereqs = {{1,0},{2,0},{3,1},{3,2}};
    auto order = findOrder(4, prereqs);
    cout << "7. Course order: ";
    for (int c : order) cout << c << " ";
    cout << "\n";
    
    // Provinces
    vector<vector<int>> conn = {{1,1,0},{1,1,0},{0,0,1}};
    cout << "10. Number of provinces: " << findCircleNum(conn) << "\n";
    
    return 0;
}

/*
================================================================================
DFS PATTERNS:
1. Grid DFS: Mark visited, explore 4/8 directions
2. Graph traversal: Visited array to avoid revisiting
3. Cycle detection: Color (WHITE/GRAY/BLACK) or recursion stack
4. Topological sort: DFS + post-order reversal
5. Path finding: Backtracking with path vector
================================================================================
*/

