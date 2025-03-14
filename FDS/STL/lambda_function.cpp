#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
        vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
            int target = int(graph.size()) - 1;
            vector<int> path{0};
            vector<vector<int>> results;
    
            function<void(int, vector<int>&)> backtrack = [&](int currNode, vector<int>& path) {
                if (currNode == target) {
                    results.push_back(vector(path));
                    return;
                }
                for (int nextNode : graph[currNode]) {
                    path.push_back(nextNode);
                    backtrack(nextNode, path);
                    path.pop_back();
                }
            };
    
            backtrack(0, path);
            return results;
        }
};
