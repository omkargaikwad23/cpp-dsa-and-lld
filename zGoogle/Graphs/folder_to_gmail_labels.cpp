/*
Convert folder objects to Gmail label paths.

Input: folders = [{id, parentId, name}, ...]  (parentId=0 means root)
Output: Full path labels for each folder

Example:
  {27, 15, "projects"}, {81, 27, "novel"}, {15, 0, "personal"}, {35, 27, "blog"}
  
  Output: ["personal/projects", "personal/projects/novel", "personal", "personal/projects/blog"]

Approach: Build tree, DFS from root accumulating paths

Time:  O(N * D) where N = number of folders, D = max depth
       - O(N) to build maps
       - O(N) DFS visits, each path string copy is O(D)
       
Space: O(N * D)
       - O(N) for adjacency list and name map
       - O(D) recursion stack depth
       - O(N * D) for output (N paths, avg length D)
*/

#include <bits/stdc++.h>
using namespace std;

struct Folder {
    int id, parentId;
    string name;
};

class Solution {
    unordered_map<int, string> names;
    unordered_map<int, vector<int>> children;
    vector<string> labels;
    
    void dfs(int id, string path) {
        // Skip virtual root (id = 0)
        if (id != 0) {
            path = path.empty() ? names[id] : path + "/" + names[id];
            labels.push_back(path);
        }
        
        // Visit all children
        for (int child : children[id]) {
            dfs(child, path);
        }
    }
    
public:
    vector<string> getLabels(const vector<Folder>& folders) {
        // Build maps: id -> name, parentId -> children
        for (const auto& f : folders) {
            names[f.id] = f.name;
            children[f.parentId].push_back(f.id);
        }
        
        // Start DFS from root (parentId = 0)
        dfs(0, "");
        
        return labels;
    }
};

int main() {
    // id, parentId, name
    vector<Folder> folders = {
        {27, 15, "projects"},
        {81, 27, "novel"},
        {15, 0, "personal"},
        {35, 27, "blog"}
    };
    
    Solution sol;
    vector<string> labels = sol.getLabels(folders);
    
    for (const string& label : labels) {
        cout << label << "\n";
    }
    
    // Output:
    // personal
    // personal/projects
    // personal/projects/novel
    // personal/projects/blog
    
    return 0;
}
