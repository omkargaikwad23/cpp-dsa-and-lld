/*
================================================================================
                SIMILAR MOVIES (Google Interview)
================================================================================

PROBLEM:
Find N highest-rated movies similar to a given movie.

Movies have ratings and similarity relations (bidirectional & transitive).
Given (movieName, N), return N similar movies with highest ratings.

================================================================================
                         EXAMPLES
================================================================================

Movies: A(6), B(7), C(8), D(9), E(5)
Similar: A-B, B-C, C-D, A-E

All movies connected through similarity (transitive).
Input: (A, 2) → Output: [D, C] (highest rated similar movies)

================================================================================
                         APPROACH
================================================================================

1. Build adjacency list for similarity graph
2. DFS/BFS to find all connected (similar) movies
3. Sort by rating descending
4. Return top N

TIME:  O(V + E + V log V) - traversal + sorting
SPACE: O(V) - visited set + result list

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class MovieFinder {
private:
    unordered_map<string, int> ratings;
    unordered_map<string, vector<string>> graph;
    
    void dfs(const string& movie, unordered_set<string>& visited) {
        visited.insert(movie);
        for (const string& neighbor : graph[movie]) {
            if (!visited.count(neighbor)) {
                dfs(neighbor, visited);
            }
        }
    }
    
public:
    void addMovie(const string& name, int rating) {
        ratings[name] = rating;
        graph[name];  // Ensure node exists in graph
    }
    
    void addSimilarity(const string& a, const string& b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    vector<string> findTopN(const string& movie, int n) {
        // Find all similar movies via DFS
        unordered_set<string> similar;
        dfs(movie, similar);
        similar.erase(movie);  // Exclude the query movie
        
        // Convert to vector and sort by rating (descending)
        vector<string> result(similar.begin(), similar.end());
        sort(result.begin(), result.end(), [&](const string& a, const string& b) {
            return ratings[a] > ratings[b];
        });
        
        // Return top N
        if (result.size() > n) {
            result.resize(n);
        }
        
        return result;
    }
    
    // Using max-heap for better efficiency with large datasets
    vector<string> findTopNOptimized(const string& movie, int n) {
        unordered_set<string> similar;
        dfs(movie, similar);
        similar.erase(movie);
        
        // Use min-heap of size N
        auto cmp = [&](const string& a, const string& b) {
            return ratings[a] > ratings[b];  // Min-heap by rating
        };
        priority_queue<string, vector<string>, decltype(cmp)> minHeap(cmp);
        
        for (const string& m : similar) {
            minHeap.push(m);
            if (minHeap.size() > n) {
                minHeap.pop();
            }
        }
        
        // Extract results (in reverse order for descending)
        vector<string> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top());
            minHeap.pop();
        }
        reverse(result.begin(), result.end());
        
        return result;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    MovieFinder finder;
    
    // Add movies with ratings
    finder.addMovie("A", 6);
    finder.addMovie("B", 7);
    finder.addMovie("C", 8);
    finder.addMovie("D", 9);
    finder.addMovie("E", 5);
    
    // Add similarity relations
    finder.addSimilarity("A", "B");
    finder.addSimilarity("B", "C");
    finder.addSimilarity("C", "D");
    finder.addSimilarity("A", "E");
    
    cout << "Movies: A(6), B(7), C(8), D(9), E(5)\n";
    cout << "Similar: A-B, B-C, C-D, A-E\n\n";
    
    // Find top 2 similar movies to A
    cout << "Top 2 similar to A: ";
    vector<string> top = finder.findTopN("A", 2);
    for (const string& m : top) {
        cout << m << " ";
    }
    cout << "\n";  // Expected: D C
    
    // Find top 3
    cout << "Top 3 similar to A: ";
    top = finder.findTopN("A", 3);
    for (const string& m : top) {
        cout << m << " ";
    }
    cout << "\n";  // Expected: D C B
    
    // Find similar from E
    cout << "Top 2 similar to E: ";
    top = finder.findTopN("E", 2);
    for (const string& m : top) {
        cout << m << " ";
    }
    cout << "\n";  // Expected: D C
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

SORTING APPROACH:
- DFS traversal: O(V + E)
- Sorting: O(V log V)
- Total: O(V + E + V log V)

HEAP APPROACH (for large N):
- DFS traversal: O(V + E)
- Heap operations: O(V log N)
- Total: O(V + E + V log N)

SPACE: O(V) for visited set and result

FOLLOW-UP QUESTIONS:
1. What if similarities have weights (strength)?
   → Use weighted graph, possibly Dijkstra for "most similar"
2. What if we need exactly N results but there aren't enough?
   → Return available movies, or extend to "similar to similar"
3. Real-time streaming of new movies?
   → Use Union-Find for connected components

================================================================================
*/

