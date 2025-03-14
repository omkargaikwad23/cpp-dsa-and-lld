#include <bits/stdc++.h>
using namespace std;

/*
- works only for Directed Acyclic Graph (DAG)
A topological ordering is an ordering of the nodes in a directed graph 
where for each directed edge from node A to node B, node A appears 
before node B in the ordering.

Pick an unvisited node beginning with the selected nodes, do DFS exploring
only unvisited nodes, on recursive callback of dfs add current node to the 
topological ordering in reverse direction
time: O(V+E)
*/

class TopoSortBfs {
    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            vector<vector<int>> graph(numCourses);
            vector<int> inDegree(numCourses, 0);
            vector<int> order;
    
            // Build adjacency list and in-degree array
            for (auto &pre : prerequisites) {
                graph[pre[1]].push_back(pre[0]);
                inDegree[pre[0]]++;  // Track incoming edges
            }
    
            queue<int> q;
            // Add courses with no prerequisites (in-degree = 0) to the queue
            for (int i = 0; i < numCourses; i++) {
                if (inDegree[i] == 0) q.push(i);
            }
    
            // Process courses using BFS (Topological Sorting)
            while (!q.empty()) {
                int course = q.front();
                q.pop();
                order.push_back(course);
    
                for (int next : graph[course]) {
                    if (--inDegree[next] == 0) {
                        q.push(next);
                    }
                }
            }
    
            // If all courses are not processed, there is a cycle
            return order.size() == numCourses ? order : vector<int>();
        }
    };
    

class Graph {
    int n;
    list<int> *adj;
public: 
    Graph(int n) {
        this->n = n;
        adj = new list<int>[n + 1];
    }

    void addEdge(int x, int y) {
        adj[x].push_back(y);
    }

    int dfs(int i, int at, vector<bool>& visited, vector<int>& ordering) {
        visited[at] = true;
        for (auto edge : adj[at]) {
            if (!visited[edge]) 
                i = dfs(i, edge, visited, ordering);
        }
        ordering[i] = at;
        return --i;
    }

    void topoSort() {
        vector<bool> visited(n + 1, false);       
        vector<int> ordering(n + 1, -1);      // stores the topological ordering of nodes
        int i = n - 1;          // iterator to store topological sort in reverse direction

        for (int src = 1; src <= n; src++) {
            if (!visited[src]) {
                i = dfs(i, src, visited, ordering);
            }
        }
        for (int j = 0; j < n; j++) {
            cout << ordering[j] << " ";
        }
    }
};

int main() {
    Graph g(5);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    
    g.topoSort();
    return 0;
}

// OUTPUT: 3 1 4 2 5