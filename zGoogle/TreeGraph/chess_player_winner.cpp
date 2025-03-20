/*


Optimal Solution Algorithm:
Use a graph-based approach to track dominance relationships:

Represent players as nodes, with directed edges from winner to loser.
Perform depth-first search (DFS) or breadth-first search (BFS) from each player in both the original and reverse graph to determine reachability.
For each player, calculate the number of players they can reach and are reachable from.
A player has a precise rank if the sum of these reachables (including themselves) equals N.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

// Function to perform BFS and return count of nodes reachable.
int bfs(int start, const vector<vector<int>>& adjList) {
    unordered_set<int> visited;
    queue<int> q;
    q.push(start);
    visited.insert(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : adjList[node]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
    
    return visited.size();
}

int main() {
    // Sample adjacency list for a directed graph.
    vector<vector<int>> adjList = {
        {1, 2},    // Player 0 defeats players 1 and 2.
        {2},       // Player 1 defeats player 2.
        {},        // Player 2 defeats no one.
        {0, 2}     // Player 3 defeats players 0 and 2.
    };
    
    int N = adjList.size();
    
    // Compute the reverse graph.
    vector<vector<int>> reverseAdjList(N);
    for (int i = 0; i < N; ++i) {
        for (int v : adjList[i]) {
            reverseAdjList[v].push_back(i);
        }
    }
    
    for (int i = 0; i < N; ++i) {
        int reachableFrom = bfs(i, adjList);
        int reachTo = bfs(i, reverseAdjList);
        
        cout << " " << reachableFrom << " -> " << reachTo << endl;

        if (reachableFrom + reachTo - 1 == N) {
            cout << "Player " << i << " has a precise rank." << endl;
        } else {
            cout << "Player " << i << " does not have a precise rank." << endl;
        }
    }
    
    return 0;
}

/*
 3 -> 2
Player 0 has a precise rank.
 2 -> 3
Player 1 has a precise rank.
 1 -> 4
Player 2 has a precise rank.
 4 -> 1
Player 3 has a precise rank.
*/