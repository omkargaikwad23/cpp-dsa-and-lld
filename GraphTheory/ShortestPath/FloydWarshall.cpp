
/*
The Floyd-Warshall algorithm finds the shortest paths in a weighted graph with positive or negative edge weights, as long as there are no negative cycles. Unlike algorithms that compute shortest paths from a single source, Floyd-Warshall computes the shortest paths between all pairs of vertices in the graph.

This algorithm takes a fundamentally different approach by computing all-pairs shortest paths in one go, rather than separately for each source. We start by initializing a distance matrix where direct connections between cities are filled with their edge weights, and all other distances are set to infinity. The distance from a city to itself is set to zero. This matrix serves both as our working space and our final result.

The core of the our algorithm involves three nested loops. The outermost loop iterates through all vertices, considering each as a potential intermediate point on the shortest path between every other pair of vertices. For each pair of vertices (i, j), we check if passing through the current intermediate vertex k offers a shorter path than we currently know. If it does, we update the distance.

This iterative process gradually refines our shortest paths. By the time all vertices have been considered as intermediates, we have determined all shortest paths. After running Floyd-Warshall, our distance matrix contains all the information needed. We can directly count reachable cities for each source and select our answer, similar to previous approaches.

Floyd-Warshall has several advantages: it solves the all-pairs shortest path problem directly with a simple and elegant one-pass implementation. For dense graphs, its time complexity of O(V^3) can be more efficient than running algorithms like Dijkstra’s or SPFA multiple times. However, for sparse graphs or when only a few sources are involved, other algorithms might be more efficient.

Floyd-Warshall Algorithm
Time complexity: O(n^3)
Space complexity: O(n^2)
*/

class Solution {
    public:
        // Large value to represent infinity
        const int INF = 1e9 + 7;
        int findTheCity(int n, vector<vector<int>>& edges) {
            // Matrix to store shortest path distances from each city
            vector<vector<int>> shortestPathMatrix(n, vector<int>(n, INF));
    
            // Compute shortest paths from each city using Bellman-Ford algorithm
            for (int i = 0; i < n; i++) {
                bellmanFord(n, edges, shortestPathMatrix[i], i);
            }
    
            // Find the city with the fewest number of reachable cities within the
            // distance threshold
            return getCityWithFewestReachable(n, shortestPathMatrix,
                                              distanceThreshold);
        }
    
    private:
        // Bellman-Ford algorithm to find shortest paths from a source city
        void bellmanFord(int n, const vector<vector<int>>& edges,
                         vector<int>& shortestPathDistances, int source) {
            // Initialize distances from the source
            fill(shortestPathDistances.begin(), shortestPathDistances.end(), INF);
            shortestPathDistances[source] = 0;  // Distance to source itself is zero
    
            // Relax edges up to n-1 times
            for (int i = 1; i < n; i++) {
                for (const auto& edge : edges) {
                    int start = edge[0];
                    int end = edge[1];
                    int weight = edge[2];
                    // Update shortest path distances if a shorter path is found
                    if (shortestPathDistances[start] != INF &&
                        shortestPathDistances[start] + weight <
                            shortestPathDistances[end]) {
                        shortestPathDistances[end] =
                            shortestPathDistances[start] + weight;
                    }
                    if (shortestPathDistances[end] != INF &&
                        shortestPathDistances[end] + weight <
                            shortestPathDistances[start]) {
                        shortestPathDistances[start] =
                            shortestPathDistances[end] + weight;
                    }
                }
            }
        }
    
    };