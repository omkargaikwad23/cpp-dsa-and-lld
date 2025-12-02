/*
================================================================================
                    BFS PROBLEMS - Google Interview Favorites
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Number of Islands (LeetCode 200) ⭐ GOOGLE CLASSIC
─────────────────────────────────────────────────────────────
Count connected components of '1's in grid.
Time: O(m*n) | Space: O(m*n)
*/
int numIslands(vector<vector<char>>& grid) {
    int m = grid.size(), n = grid[0].size();
    int islands = 0;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    auto bfs = [&](int r, int c) {
        queue<pair<int,int>> q;
        q.push({r, c});
        grid[r][c] = '0';
        
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == '1') {
                    grid[nx][ny] = '0';
                    q.push({nx, ny});
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


/*
PROBLEM 2: Rotting Oranges (LeetCode 994) ⭐ MULTI-SOURCE BFS
────────────────────────────────────────────────────────────
Min time to rot all oranges. Start BFS from all rotten oranges.
Time: O(m*n) | Space: O(m*n)
*/
int orangesRotting(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    queue<pair<int,int>> q;
    int fresh = 0;
    
    // Add all rotten oranges to queue
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
            auto [x, y] = q.front();
            q.pop();
            
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1) {
                    grid[nx][ny] = 2;
                    q.push({nx, ny});
                    fresh--;
                    rotted = true;
                }
            }
        }
        
        if (rotted) minutes++;
    }
    
    return fresh == 0 ? minutes : -1;
}


/*
PROBLEM 3: Word Ladder (LeetCode 127) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────
Shortest transformation sequence from beginWord to endWord.
Time: O(n * m * 26) | Space: O(n * m)
*/
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
                char original = word[j];
                for (char c = 'a'; c <= 'z'; c++) {
                    word[j] = c;
                    if (dict.count(word)) {
                        q.push(word);
                        dict.erase(word);
                    }
                }
                word[j] = original;
            }
        }
        level++;
    }
    
    return 0;
}


/*
PROBLEM 4: 01 Matrix (LeetCode 542) ⭐ MULTI-SOURCE BFS
──────────────────────────────────────────────────────
Distance to nearest 0 for each cell.
Time: O(m*n) | Space: O(m*n)
*/
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
        auto [x, y] = q.front();
        q.pop();
        
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                if (dist[x][y] + 1 < dist[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
    
    return dist;
}


/*
PROBLEM 5: Shortest Path in Binary Matrix (LeetCode 1091)
─────────────────────────────────────────────────────────
8-directional BFS from (0,0) to (n-1,n-1).
Time: O(n²) | Space: O(n²)
*/
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    if (grid[0][0] || grid[n-1][n-1]) return -1;
    
    vector<pair<int,int>> dirs = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    queue<pair<int,int>> q;
    q.push({0, 0});
    grid[0][0] = 1;
    int path = 1;
    
    while (!q.empty()) {
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            auto [x, y] = q.front();
            q.pop();
            
            if (x == n-1 && y == n-1) return path;
            
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                    grid[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
        path++;
    }
    
    return -1;
}


/*
PROBLEM 6: Walls and Gates (LeetCode 286) ⭐ MULTI-SOURCE BFS
────────────────────────────────────────────────────────────
Fill each empty room with distance to nearest gate.
Time: O(m*n) | Space: O(m*n)
*/
void wallsAndGates(vector<vector<int>>& rooms) {
    int m = rooms.size(), n = rooms[0].size();
    queue<pair<int,int>> q;
    
    // Add all gates
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (rooms[i][j] == 0) q.push({i, j});
        }
    }
    
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        
        for (auto [dx, dy] : dirs) {
            int nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && rooms[nx][ny] == INT_MAX) {
                rooms[nx][ny] = rooms[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}


/*
PROBLEM 7: Shortest Bridge (LeetCode 934) ⭐
───────────────────────────────────────────
Min flips to connect two islands.
DFS to find one island, BFS to expand to second.
Time: O(n²) | Space: O(n²)
*/
int shortestBridge(vector<vector<int>>& grid) {
    int n = grid.size();
    queue<pair<int,int>> q;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    bool found = false;
    
    // DFS to find and mark first island
    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1) return;
        grid[r][c] = 2;
        q.push({r, c});
        for (auto [dr, dc] : dirs) {
            dfs(r + dr, c + dc);
        }
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
            auto [x, y] = q.front();
            q.pop();
            
            for (auto [dx, dy] : dirs) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    if (grid[nx][ny] == 1) return dist;
                    if (grid[nx][ny] == 0) {
                        grid[nx][ny] = 2;
                        q.push({nx, ny});
                    }
                }
            }
        }
        dist++;
    }
    
    return -1;
}


/*
PROBLEM 8: Open the Lock (LeetCode 752)
───────────────────────────────────────
Min turns to reach target from "0000".
Time: O(10^4 * 8) | Space: O(10^4)
*/
int openLock(vector<string>& deadends, string target) {
    unordered_set<string> dead(deadends.begin(), deadends.end());
    if (dead.count("0000")) return -1;
    if (target == "0000") return 0;
    
    queue<string> q;
    unordered_set<string> visited;
    q.push("0000");
    visited.insert("0000");
    int turns = 0;
    
    while (!q.empty()) {
        turns++;
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            string curr = q.front();
            q.pop();
            
            for (int j = 0; j < 4; j++) {
                for (int d : {-1, 1}) {
                    string next = curr;
                    next[j] = ((curr[j] - '0' + d + 10) % 10) + '0';
                    
                    if (next == target) return turns;
                    if (!dead.count(next) && !visited.count(next)) {
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }
    }
    
    return -1;
}


/*
PROBLEM 9: Snakes and Ladders (LeetCode 909)
────────────────────────────────────────────
Min moves to reach last cell on Boustrophedon board.
*/
int snakesAndLadders(vector<vector<int>>& board) {
    int n = board.size();
    
    auto getPos = [&](int num) -> pair<int,int> {
        int row = (num - 1) / n;
        int col = (num - 1) % n;
        if (row % 2 == 1) col = n - 1 - col;
        return {n - 1 - row, col};
    };
    
    vector<int> dist(n * n + 1, -1);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        
        for (int next = curr + 1; next <= min(curr + 6, n * n); next++) {
            auto [r, c] = getPos(next);
            int dest = board[r][c] == -1 ? next : board[r][c];
            
            if (dist[dest] == -1) {
                dist[dest] = dist[curr] + 1;
                if (dest == n * n) return dist[dest];
                q.push(dest);
            }
        }
    }
    
    return dist[n * n];
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== BFS Problems ===\n\n";
    
    // Number of Islands
    vector<vector<char>> grid1 = {
        {'1','1','0','0','0'},
        {'1','1','0','0','0'},
        {'0','0','1','0','0'},
        {'0','0','0','1','1'}
    };
    cout << "1. Number of Islands: " << numIslands(grid1) << "\n";
    
    // Rotting Oranges
    vector<vector<int>> grid2 = {{2,1,1},{1,1,0},{0,1,1}};
    cout << "2. Rotting Oranges: " << orangesRotting(grid2) << " minutes\n";
    
    // Word Ladder
    vector<string> wordList = {"hot","dot","dog","lot","log","cog"};
    cout << "3. Word Ladder (hit->cog): " << ladderLength("hit", "cog", wordList) << "\n";
    
    return 0;
}

/*
================================================================================
BFS PATTERNS:
1. Grid BFS: 4/8 directional, mark visited
2. Multi-source BFS: Start from all sources simultaneously
3. State BFS: State = (position + extra info), e.g., keys collected
4. Bi-directional BFS: Search from both ends for shortest path
================================================================================
*/

