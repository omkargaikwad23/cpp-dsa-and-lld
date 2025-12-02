/*
================================================================================
                    DIJKSTRA'S ALGORITHM
================================================================================

USE WHEN:
- Shortest path with NON-NEGATIVE weights
- Single source shortest path
- Network routing

TIME: O((V + E) log V) with priority queue
SPACE: O(V + E)

⚠️ Does NOT work with negative weights! Use Bellman-Ford instead.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Dijkstra with Priority Queue ⭐
// ═══════════════════════════════════════════════════════════════════════════

vector<long long> dijkstra(int start, vector<vector<pair<int,int>>>& adj) {
    int n = adj.size();
    vector<long long> dist(n, LLONG_MAX);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;  // Skip stale entries
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Dijkstra with Path Reconstruction
// ═══════════════════════════════════════════════════════════════════════════

pair<long long, vector<int>> dijkstraWithPath(int start, int end, 
                                               vector<vector<pair<int,int>>>& adj) {
    int n = adj.size();
    vector<long long> dist(n, LLONG_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    // Reconstruct path
    vector<int> path;
    if (dist[end] != LLONG_MAX) {
        for (int at = end; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
    }
    
    return {dist[end], path};
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Network Delay Time (LeetCode 743) ⭐
// ═══════════════════════════════════════════════════════════════════════════

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int,int>>> adj(n + 1);
    for (auto& t : times) {
        adj[t[0]].push_back({t[1], t[2]});
    }
    
    vector<int> dist(n + 1, INT_MAX);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    
    dist[k] = 0;
    pq.push({0, k});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    int maxDist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;
        maxDist = max(maxDist, dist[i]);
    }
    
    return maxDist;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Path With Minimum Effort (LeetCode 1631) ⭐
// Modified Dijkstra: minimize MAX edge weight
// ═══════════════════════════════════════════════════════════════════════════

int minimumEffortPath(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();
    vector<vector<int>> effort(m, vector<int>(n, INT_MAX));
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    effort[0][0] = 0;
    pq.push({0, 0, 0});
    
    while (!pq.empty()) {
        auto [e, r, c] = pq.top();
        pq.pop();
        
        if (r == m-1 && c == n-1) return e;
        if (e > effort[r][c]) continue;
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                int newEffort = max(e, abs(heights[nr][nc] - heights[r][c]));
                if (newEffort < effort[nr][nc]) {
                    effort[nr][nc] = newEffort;
                    pq.push({newEffort, nr, nc});
                }
            }
        }
    }
    
    return effort[m-1][n-1];
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Swim in Rising Water (LeetCode 778)
// ═══════════════════════════════════════════════════════════════════════════

int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> time(n, vector<int>(n, INT_MAX));
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    time[0][0] = grid[0][0];
    pq.push({grid[0][0], 0, 0});
    
    while (!pq.empty()) {
        auto [t, r, c] = pq.top();
        pq.pop();
        
        if (r == n-1 && c == n-1) return t;
        if (t > time[r][c]) continue;
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                int newTime = max(t, grid[nr][nc]);
                if (newTime < time[nr][nc]) {
                    time[nr][nc] = newTime;
                    pq.push({newTime, nr, nc});
                }
            }
        }
    }
    
    return time[n-1][n-1];
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 4: Shortest Path to Get All Keys (LeetCode 864)
// Dijkstra with state = (position, keys_collected)
// ═══════════════════════════════════════════════════════════════════════════

int shortestPathAllKeys(vector<string>& grid) {
    int m = grid.size(), n = grid[0].size();
    int startR = 0, startC = 0, totalKeys = 0;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '@') { startR = i; startC = j; }
            if (grid[i][j] >= 'a' && grid[i][j] <= 'f') totalKeys++;
        }
    }
    
    int allKeys = (1 << totalKeys) - 1;
    map<tuple<int,int,int>, int> dist;
    priority_queue<tuple<int,int,int,int>, vector<tuple<int,int,int,int>>, greater<>> pq;
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    pq.push({0, startR, startC, 0});
    dist[{startR, startC, 0}] = 0;
    
    while (!pq.empty()) {
        auto [d, r, c, keys] = pq.top();
        pq.pop();
        
        if (keys == allKeys) return d;
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            
            char cell = grid[nr][nc];
            if (cell == '#') continue;
            if (cell >= 'A' && cell <= 'F' && !(keys & (1 << (cell - 'A')))) continue;
            
            int newKeys = keys;
            if (cell >= 'a' && cell <= 'f') {
                newKeys |= (1 << (cell - 'a'));
            }
            
            auto state = make_tuple(nr, nc, newKeys);
            if (!dist.count(state) || d + 1 < dist[state]) {
                dist[state] = d + 1;
                pq.push({d + 1, nr, nc, newKeys});
            }
        }
    }
    
    return -1;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Dijkstra Module ===\n\n";
    
    // Test Network Delay
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    cout << "1. Network delay: " << networkDelayTime(times, 4, 2) << "\n";
    
    // Test Min Effort Path
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};
    cout << "2. Min effort: " << minimumEffortPath(heights) << "\n";
    
    // Test Swim in Water
    vector<vector<int>> grid = {{0,2},{1,3}};
    cout << "3. Swim time: " << swimInWater(grid) << "\n";
    
    return 0;
}

/*
================================================================================
                    DIJKSTRA VARIATIONS
================================================================================

1. STANDARD:
   - Minimize total path weight
   - dist[v] = min(dist[v], dist[u] + weight)

2. MINIMIZE MAX EDGE (Min Effort Path):
   - dist[v] = min(dist[v], max(dist[u], weight))

3. STATE-SPACE DIJKSTRA:
   - State = (position, extra_info)
   - E.g., keys collected, fuel remaining

4. TIPS:
   - Skip stale PQ entries: if (d > dist[u]) continue
   - Use greater<> for min-heap

================================================================================
*/

