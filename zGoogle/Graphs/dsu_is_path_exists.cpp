#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
You are given a graph with N nodes, labeled from 0 to N-1.
You are also given a sorted array arr of size N and an integer diff.
If the absolute difference between arr[i] and arr[j] is less than or equal to diff (i.e., |arr[i] - arr[j]| <= diff),
then there exists an edge between nodes i and j in the graph.

Implement a function that takes the array arr, the integer diff, and a list queries as input.
Each query is a list of two integers, representing two nodes. The function should return a list of booleans.
The i-th element of the output list should be True if there exists a path between the two nodes specified in the i-th query(queries[i][0], queries[i][1]), and False otherwise.

Example:

Input:
Given N = 4, arr = [1, 2, 3, 6], diff = 2 and queries=[[0,2], [1,3]]

Output:
[True, False]
*/

struct DSU {
    vector<int> parent;
    vector<int> rank;
    int n;
    
    DSU(int _n) {
        n = _n;
        parent.resize(n);
        rank.assign(n, 0);
        for(int i=0; i<n; i++) {
            parent[i] = i;
        }
    }
    
    int findParent(int u) {
        if(parent[u] == u) return u;
        return parent[u] = findParent(parent[u]);
    }
    
    void merge(int u, int v) {
        u = findParent(u);
        v = findParent(v);
        if(u == v) return;
        
        if(rank[u] < rank[v]) 
            swap(u, v);
        
        parent[v] = u; // rank[v] > rank[u]
        if(rank[u] == rank[v])
            rank[u]++;
    }
};

class Solution {
public:
    vector<bool> isPathPresent(vector<int> &arr, vector<vector<int>> &queries, int diff) {
        int n = arr.size();
        DSU dsu(n);
        //create adj list
        for(int i = 0; i < n - 1; i++) {
            for(int j = i+1; j < n; j++) {
                int curDiff = abs(arr[i] - arr[j]);
                if(curDiff <= diff) {
                    dsu.merge(i, j);
                }
                else {
                    break;
                }
            }
        }
        
        // iterate over queries
        vector<bool> res;
        for(const auto &q : queries) {
            int parentA = dsu.findParent(q[0]);
            int parentB = dsu.findParent(q[1]);
            if(parentA == parentB) {
                res.push_back(true);
            }
            else {
                res.push_back(false);
            }
        }
        return res;
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 6};
    int diff = 2;
    vector<vector<int>> queries = {{0,2}, {1,3}};
                                   
    Solution sol;
    vector<bool> res = sol.isPathPresent(arr, queries, diff);
    
    for(auto r : res) {
        cout << r << " ";
    }
}
