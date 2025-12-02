/*
Find N highest-rated movies similar to a given movie.

Movies have ratings and similarity relations (bidirectional & transitive).
Given (movieName, N), return N similar movies with highest ratings.

Example:
  Movies: A(6), B(7), C(8), D(9), E(5)
  Similar: A-B, B-C, C-D, A-E
  
  Input: (A, 2) → Output: [D, C]
  
Approach:
  1. Build adjacency list for similarity graph
  2. DFS/BFS to find all connected movies
  3. Sort by rating and return top N
*/

#include <bits/stdc++.h>
using namespace std;

class MovieFinder {
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
        graph[name]; // ensure node exists
    }
    
    void addSimilarity(const string& a, const string& b) {
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    vector<string> findTopN(const string& movie, int n) {
        // Find all similar movies via DFS
        unordered_set<string> similar;
        dfs(movie, similar);
        similar.erase(movie); // exclude the query movie
        
        // Convert to vector and sort by rating (descending)
        vector<string> result(similar.begin(), similar.end());
        sort(result.begin(), result.end(), [&](const string& a, const string& b) {
            return ratings[a] > ratings[b];
        });
        
        // Return top N
        if (result.size() > n) result.resize(n);
        return result;
    }
};

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
    
    // Find top 2 similar movies to A
    vector<string> top = finder.findTopN("A", 2);
    
    for (const string& m : top) {
        cout << m << " ";
    }
    // Output: D C
    
    return 0;
}
