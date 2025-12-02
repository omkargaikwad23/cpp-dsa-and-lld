/*
================================================================================
                    PATTERN 16: DP ON GRAPHS
================================================================================

When to use:
- Shortest paths with constraints
- Counting paths in DAGs
- Graph optimization with states

LeetCode Problems:
- 787. Cheapest Flights Within K Stops
- 1334. Find City With Smallest Number of Neighbors

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Cheapest Flights Within K Stops (LeetCode 787) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────────────────────
Find cheapest flight from src to dst with at most k stops.

Bellman-Ford variant: Relax edges k+1 times.

Time: O(k * E) | Space: O(n)
*/
int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;
    
    for (int i = 0; i <= k; i++) {
        vector<int> newDist = dist;
        
        for (auto& flight : flights) {
            int u = flight[0], v = flight[1], cost = flight[2];
            if (dist[u] != INT_MAX) {
                newDist[v] = min(newDist[v], dist[u] + cost);
            }
        }
        
        dist = newDist;
    }
    
    return dist[dst] == INT_MAX ? -1 : dist[dst];
}


/*
PROBLEM 2: Find City With Smallest Number of Neighbors (LeetCode 1334)
──────────────────────────────────────────────────────────────────────
Find city with smallest number of reachable cities within threshold.

Floyd-Warshall for all-pairs shortest paths.

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
PROBLEM 3: Number of Ways to Arrive at Destination (LeetCode 1976)
──────────────────────────────────────────────────────────────────
Count number of shortest paths.

Dijkstra + count paths.

Time: O((V + E) log V) | Space: O(V + E)
*/
int countPaths(int n, vector<vector<int>>& roads) {
    const int MOD = 1e9 + 7;
    vector<vector<pair<int, int>>> graph(n);
    
    for (auto& road : roads) {
        graph[road[0]].push_back({road[1], road[2]});
        graph[road[1]].push_back({road[0], road[2]});
    }
    
    vector<long long> dist(n, LLONG_MAX);
    vector<long long> ways(n, 0);
    dist[0] = 0;
    ways[0] = 1;
    
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    pq.push({0, 0});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ways[v] = ways[u];
                pq.push({dist[v], v});
            } else if (dist[u] + w == dist[v]) {
                ways[v] = (ways[v] + ways[u]) % MOD;
            }
        }
    }
    
    return ways[n - 1];
}


/*
PROBLEM 4: Longest Path in DAG
──────────────────────────────
Topological sort + DP.

Time: O(V + E) | Space: O(V)
*/
int longestPathDAG(int n, vector<vector<pair<int, int>>>& graph) {
    vector<int> inDegree(n, 0);
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : graph[u]) {
            inDegree[v]++;
        }
    }
    
    queue<int> q;
    vector<int> dist(n, INT_MIN);
    
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
            dist[i] = 0;
        }
    }
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (auto [v, w] : graph[u]) {
            dist[v] = max(dist[v], dist[u] + w);
            if (--inDegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    return *max_element(dist.begin(), dist.end());
}


/*
PROBLEM 5: Path with Maximum Probability (LeetCode 1514)
────────────────────────────────────────────────────────
Find path with maximum probability.

Modified Dijkstra with max instead of min.

Time: O((V + E) log V) | Space: O(V + E)
*/
double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
    vector<vector<pair<int, double>>> graph(n);
    
    for (int i = 0; i < edges.size(); i++) {
        graph[edges[i][0]].push_back({edges[i][1], succProb[i]});
        graph[edges[i][1]].push_back({edges[i][0], succProb[i]});
    }
    
    vector<double> prob(n, 0);
    prob[start] = 1;
    
    priority_queue<pair<double, int>> pq;
    pq.push({1, start});
    
    while (!pq.empty()) {
        auto [p, u] = pq.top();
        pq.pop();
        
        if (p < prob[u]) continue;
        if (u == end) return p;
        
        for (auto [v, w] : graph[u]) {
            if (prob[u] * w > prob[v]) {
                prob[v] = prob[u] * w;
                pq.push({prob[v], v});
            }
        }
    }
    
    return 0;
}


/*
PROBLEM 6: Minimum Cost to Reach Destination in Time (LeetCode 1928)
────────────────────────────────────────────────────────────────────
Find min cost path from 0 to n-1 within maxTime.

State: (node, remaining_time)

Time: O(V * T * log(V * T)) | Space: O(V * T)
*/
int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
    int n = passingFees.size();
    vector<vector<pair<int, int>>> graph(n);
    
    for (auto& e : edges) {
        graph[e[0]].push_back({e[1], e[2]});
        graph[e[1]].push_back({e[0], e[2]});
    }
    
    // dp[node][time] = min cost
    vector<vector<int>> dp(n, vector<int>(maxTime + 1, INT_MAX));
    dp[0][0] = passingFees[0];
    
    // {cost, node, time}
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.push({passingFees[0], 0, 0});
    
    while (!pq.empty()) {
        auto [cost, u, time] = pq.top();
        pq.pop();
        
        if (cost > dp[u][time]) continue;
        if (u == n - 1) return cost;
        
        for (auto [v, t] : graph[u]) {
            int newTime = time + t;
            if (newTime <= maxTime) {
                int newCost = cost + passingFees[v];
                if (newCost < dp[v][newTime]) {
                    dp[v][newTime] = newCost;
                    pq.push({newCost, v, newTime});
                }
            }
        }
    }
    
    return -1;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Graph DP ===\n\n";
    
    // Cheapest Flights
    vector<vector<int>> flights = {{0,1,100},{1,2,100},{0,2,500}};
    cout << "1. Cheapest flight (0→2, k=1): " << findCheapestPrice(3, flights, 0, 2, 1) << "\n";
    
    // Find City
    vector<vector<int>> edges1 = {{0,1,3},{1,2,1},{1,3,4},{2,3,1}};
    cout << "2. City with min neighbors: " << findTheCity(4, edges1, 4) << "\n";
    
    // Count Paths
    vector<vector<int>> roads = {{0,6,7},{0,1,2},{1,2,3},{1,3,3},{6,3,3},{3,5,1},{6,5,1},{2,5,1},{0,4,5},{4,6,2}};
    cout << "3. Number of shortest paths: " << countPaths(7, roads) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Algorithm                                      |
+───────────────────────────────+────────────────────────────────────────────────+
| K stops                       | Bellman-Ford (k+1 iterations)                  |
| All pairs                     | Floyd-Warshall                                 |
| Count shortest paths          | Dijkstra + count ways                          |
| DAG longest path              | Topological sort + DP                          |
| With time constraint          | State (node, time), Dijkstra                   |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

