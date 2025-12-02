/*
================================================================================
                    SHORTEST PATH PROBLEMS - Google Interview Favorites
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Network Delay Time (LeetCode 743) ⭐ DIJKSTRA
───────────────────────────────────────────────────────
Find time for signal to reach all nodes.
Time: O(E log V) | Space: O(V + E)
*/
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


/*
PROBLEM 2: Cheapest Flights Within K Stops (LeetCode 787) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────────────────────
Modified Bellman-Ford: limit iterations to k+1.
Time: O(k * E) | Space: O(V)
*/
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    
    for (int i = 0; i <= k; i++) {
        vector<int> temp = dist;
        for (auto& f : flights) {
            int u = f[0], v = f[1], w = f[2];
            if (dist[u] != INT_MAX) {
                temp[v] = min(temp[v], dist[u] + w);
            }
        }
        dist = temp;
    }
    
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}


/*
PROBLEM 3: Path With Minimum Effort (LeetCode 1631) ⭐
─────────────────────────────────────────────────────
Modified Dijkstra: minimize max absolute difference.
Time: O(m*n log(m*n)) | Space: O(m*n)
*/
int minimumEffortPath(vector<vector<int>>& heights) {
    int m = heights.size(), n = heights[0].size();
    vector<vector<int>> effort(m, vector<int>(n, INT_MAX));
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    
    effort[0][0] = 0;
    pq.push({0, 0, 0});
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
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


/*
PROBLEM 4: Swim in Rising Water (LeetCode 778)
──────────────────────────────────────────────
Wait until water level allows path.
Time: O(n² log n²) | Space: O(n²)
*/
int swimInWater(vector<vector<int>>& grid) {
    int n = grid.size();
    vector<vector<int>> time(n, vector<int>(n, INT_MAX));
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    
    time[0][0] = grid[0][0];
    pq.push({grid[0][0], 0, 0});
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
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


/*
PROBLEM 5: 0-1 BFS (Minimum Cost to Make at Least One Valid Path) - LeetCode 1368
──────────────────────────────────────────────────────────────────────────────────
Grid where following arrow = 0 cost, changing = 1 cost.
Use deque: 0-cost edges push_front, 1-cost push_back.
Time: O(m*n) | Space: O(m*n)
*/
int minCost(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> cost(m, vector<int>(n, INT_MAX));
    // Directions: 1=right, 2=left, 3=down, 4=up
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    deque<pair<int,int>> dq;
    dq.push_front({0, 0});
    cost[0][0] = 0;
    
    while (!dq.empty()) {
        auto [r, c] = dq.front();
        dq.pop_front();
        
        for (int d = 0; d < 4; d++) {
            int nr = r + dirs[d].first;
            int nc = c + dirs[d].second;
            
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                int edgeCost = (grid[r][c] == d + 1) ? 0 : 1;
                int newCost = cost[r][c] + edgeCost;
                
                if (newCost < cost[nr][nc]) {
                    cost[nr][nc] = newCost;
                    if (edgeCost == 0) {
                        dq.push_front({nr, nc});
                    } else {
                        dq.push_back({nr, nc});
                    }
                }
            }
        }
    }
    
    return cost[m-1][n-1];
}


/*
PROBLEM 6: Shortest Path to Get All Keys (LeetCode 864) ⭐ STATE BFS
────────────────────────────────────────────────────────────────────
BFS with state = (position, keys_collected).
Time: O(m*n * 2^k) | Space: O(m*n * 2^k)
*/
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
    set<tuple<int,int,int>> visited;
    queue<tuple<int,int,int,int>> q;  // r, c, keys, steps
    
    q.push({startR, startC, 0, 0});
    visited.insert({startR, startC, 0});
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    while (!q.empty()) {
        auto [r, c, keys, steps] = q.front();
        q.pop();
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            
            char cell = grid[nr][nc];
            if (cell == '#') continue;
            
            // Lock without key
            if (cell >= 'A' && cell <= 'F' && !(keys & (1 << (cell - 'A')))) continue;
            
            int newKeys = keys;
            if (cell >= 'a' && cell <= 'f') {
                newKeys |= (1 << (cell - 'a'));
            }
            
            if (newKeys == allKeys) return steps + 1;
            
            if (!visited.count({nr, nc, newKeys})) {
                visited.insert({nr, nc, newKeys});
                q.push({nr, nc, newKeys, steps + 1});
            }
        }
    }
    
    return -1;
}


/*
PROBLEM 7: Find City With Smallest Number of Neighbors (LeetCode 1334) - FLOYD-WARSHALL
──────────────────────────────────────────────────────────────────────────────────────
All-pairs shortest path within threshold.
Time: O(n³) | Space: O(n²)
*/
int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX / 2));
    
    for (int i = 0; i < n; i++) dist[i][i] = 0;
    for (auto& e : edges) {
        dist[e[0]][e[1]] = dist[e[1]][e[0]] = e[2];
    }
    
    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    int result = 0, minReachable = n;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (i != j && dist[i][j] <= distanceThreshold) count++;
        }
        if (count <= minReachable) {
            minReachable = count;
            result = i;
        }
    }
    
    return result;
}


/*
PROBLEM 8: Shortest Path with Alternating Colors (LeetCode 1129)
────────────────────────────────────────────────────────────────
BFS with state = (node, last_color).
*/
vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) {
    vector<vector<pair<int,int>>> adj(n);  // {neighbor, color} 0=red, 1=blue
    
    for (auto& e : redEdges) adj[e[0]].push_back({e[1], 0});
    for (auto& e : blueEdges) adj[e[0]].push_back({e[1], 1});
    
    vector<int> result(n, -1);
    vector<vector<bool>> visited(n, vector<bool>(2, false));
    queue<tuple<int,int,int>> q;  // node, dist, lastColor
    
    q.push({0, 0, -1});  // Start with no color
    result[0] = 0;
    
    while (!q.empty()) {
        auto [node, dist, lastColor] = q.front();
        q.pop();
        
        for (auto [next, color] : adj[node]) {
            if (color != lastColor && !visited[next][color]) {
                visited[next][color] = true;
                if (result[next] == -1) result[next] = dist + 1;
                q.push({next, dist + 1, color});
            }
        }
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Shortest Path Problems ===\n\n";
    
    // Network Delay
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    cout << "1. Network delay: " << networkDelayTime(times, 4, 2) << "\n";
    
    // Cheapest Flights
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{0,2,500}};
    cout << "2. Cheapest flight (k=1): " << findCheapestPrice(3, flights, 0, 2, 1) << "\n";
    
    // Min Effort Path
    vector<vector<int>> heights = {{1,2,2},{3,8,2},{5,3,5}};
    cout << "3. Min effort path: " << minimumEffortPath(heights) << "\n";
    
    // Swim in Water
    vector<vector<int>> grid = {{0,2},{1,3}};
    cout << "4. Swim in rising water: " << swimInWater(grid) << "\n";
    
    return 0;
}

/*
================================================================================
SHORTEST PATH PATTERNS:
1. Dijkstra: Non-negative weights, single source
2. Bellman-Ford: Negative weights, K stops constraint
3. Floyd-Warshall: All pairs, small n
4. 0-1 BFS: Weights only 0 or 1, use deque
5. State BFS: (position + extra state), e.g., keys collected
================================================================================
*/

