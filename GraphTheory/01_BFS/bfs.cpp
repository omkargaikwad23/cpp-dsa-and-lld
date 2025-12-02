/*
================================================================================
                    BFS (Breadth-First Search)
================================================================================

USE WHEN:
- Shortest path in UNWEIGHTED graph
- Level-order traversal
- Finding nearest/minimum steps
- Multi-source shortest distance

TIME: O(V + E) | SPACE: O(V)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 1: Basic BFS (Graph)
// ═══════════════════════════════════════════════════════════════════════════

vector<int> bfs(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    return dist;
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 2: BFS on Grid (4-directional)
// ═══════════════════════════════════════════════════════════════════════════

int bfsGrid(vector<vector<int>>& grid, int sr, int sc, int tr, int tc) {
    int m = grid.size(), n = grid[0].size();
    if (grid[sr][sc] == 1 || grid[tr][tc] == 1) return -1;
    
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    vector<vector<int>> dist(m, vector<int>(n, -1));
    queue<pair<int,int>> q;
    
    dist[sr][sc] = 0;
    q.push({sr, sc});
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        if (r == tr && c == tc) return dist[r][c];
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                grid[nr][nc] == 0 && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    
    return -1;
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 3: Multi-Source BFS ⭐
// ═══════════════════════════════════════════════════════════════════════════

// Start BFS from multiple sources simultaneously
vector<vector<int>> multiSourceBFS(vector<vector<int>>& grid, 
                                    vector<pair<int,int>>& sources) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    queue<pair<int,int>> q;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    // Add all sources to queue
    for (auto [r, c] : sources) {
        dist[r][c] = 0;
        q.push({r, c});
    }
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                dist[r][c] + 1 < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    
    return dist;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Number of Islands (LeetCode 200) ⭐
// ═══════════════════════════════════════════════════════════════════════════

int numIslands(vector<vector<char>>& grid) {
    int m = grid.size(), n = grid[0].size();
    int islands = 0;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    auto bfs = [&](int sr, int sc) {
        queue<pair<int,int>> q;
        q.push({sr, sc});
        grid[sr][sc] = '0';
        
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == '1') {
                    grid[nr][nc] = '0';
                    q.push({nr, nc});
                }
            }
        }
    };
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {
                bfs(i, j);
                islands++;
            }
        }
    }
    
    return islands;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Rotting Oranges (LeetCode 994) ⭐ Multi-Source BFS
// ═══════════════════════════════════════════════════════════════════════════

int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int,int>> q;
    int fresh = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 2) q.push({i, j});
            else if (grid[i][j] == 1) fresh++;
        }
    }
    
    if (fresh == 0) return 0;
    
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    int minutes = 0;
    
    while (!q.empty()) {
        int size = q.size();
        bool rotted = false;
        
        for (int i = 0; i < size; i++) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    q.push({nr, nc});
                    fresh--;
                    rotted = true;
                }
            }
        }
        if (rotted) minutes++;
    }
    
    return fresh == 0 ? minutes : -1;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Word Ladder (LeetCode 127) ⭐
// ═══════════════════════════════════════════════════════════════════════════

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(endWord)) return 0;
    
    queue<string> q;
    q.push(beginWord);
    int level = 1;
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            string word = q.front();
            q.pop();
            
            if (word == endWord) return level;
            
            for (int j = 0; j < word.size(); j++) {
                char orig = word[j];
                for (char c = 'a'; c <= 'z'; c++) {
                    word[j] = c;
                    if (dict.count(word)) {
                        q.push(word);
                        dict.erase(word);
                    }
                }
                word[j] = orig;
            }
        }
        level++;
    }
    
    return 0;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 4: 01 Matrix (LeetCode 542) ⭐ Multi-Source BFS
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    queue<pair<int,int>> q;
    
    // Start from all 0s
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 0) {
                dist[i][j] = 0;
                q.push({i, j});
            }
        }
    }
    
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                dist[r][c] + 1 < dist[nr][nc]) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    
    return dist;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 5: Shortest Bridge (LeetCode 934)
// ═══════════════════════════════════════════════════════════════════════════

int shortestBridge(vector<vector<int>>& grid) {
    int n = grid.size();
    queue<pair<int,int>> q;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    bool found = false;
    
    // DFS to find first island and mark as 2
    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1) return;
        grid[r][c] = 2;
        q.push({r, c});
        for (auto [dr, dc] : dirs) dfs(r + dr, c + dc);
    };
    
    for (int i = 0; i < n && !found; i++) {
        for (int j = 0; j < n && !found; j++) {
            if (grid[i][j] == 1) {
                dfs(i, j);
                found = true;
            }
        }
    }
    
    // BFS to expand to second island
    int dist = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            auto [r, c] = q.front();
            q.pop();
            
            for (auto [dr, dc] : dirs) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    if (grid[nr][nc] == 1) return dist;
                    if (grid[nr][nc] == 0) {
                        grid[nr][nc] = 2;
                        q.push({nr, nc});
                    }
                }
            }
        }
        dist++;
    }
    
    return -1;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== BFS Module ===\n\n";
    
    // Test Number of Islands
    vector<vector<char>> grid1 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "1. Number of Islands: " << numIslands(grid1) << "\n";
    
    // Test Rotting Oranges
    vector<vector<int>> grid2 = {{2,1,1},{1,1,0},{0,1,1}};
    cout << "2. Rotting Oranges: " << orangesRotting(grid2) << " min\n";
    
    // Test Word Ladder
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    cout << "3. Word Ladder (hit->cog): " << ladderLength("hit", "cog", wordList) << "\n";
    
    return 0;
}

/*
================================================================================
                    BFS PATTERNS SUMMARY
================================================================================

1. BASIC BFS:
   - Use: Shortest path in unweighted graph
   - Template: queue + visited/dist array

2. GRID BFS:
   - 4-directional: {{0,1},{0,-1},{1,0},{-1,0}}
   - 8-directional: Add diagonals
   - Mark visited to avoid revisiting

3. MULTI-SOURCE BFS: ⭐
   - Start BFS from ALL sources simultaneously
   - Problems: Rotting Oranges, 01 Matrix, Walls and Gates

4. LEVEL-BY-LEVEL BFS:
   - Process entire level before moving to next
   - Use: min steps, level order

================================================================================
*/

