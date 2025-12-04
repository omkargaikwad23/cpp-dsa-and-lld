/*
================================================================================
                    TOPOLOGICAL SORT
================================================================================

USE WHEN:
- Task scheduling with dependencies
- Course prerequisites
- Build order
- Detecting cycles in DAG

TIME: O(V + E) | SPACE: O(V)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 1: Kahn's Algorithm (BFS-based) ⭐ PREFERRED
// ═══════════════════════════════════════════════════════════════════════════

vector<int> topoSortKahns(int n, vector<vector<int>>& adj) {
    vector<int> indegree(n, 0);
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    vector<int> order;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        
        for (int v : adj[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // If order.size() != n, there's a cycle
    return order.size() == n ? order : vector<int>();
}


// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE 2: DFS-based Topological Sort
// ═══════════════════════════════════════════════════════════════════════════

vector<int> topoSortDFS(int n, vector<vector<int>>& adj) {
    vector<int> color(n, 0);  // 0=white, 1=gray, 2=black
    vector<int> order;
    bool hasCycle = false;
    
    function<void(int)> dfs = [&](int u) {
        if (hasCycle) return;
        color[u] = 1;
        
        for (int v : adj[u]) {
            if (color[v] == 1) { hasCycle = true; return; }
            if (color[v] == 0) dfs(v);
        }
        
        color[u] = 2;
        order.push_back(u);
    };
    
    for (int i = 0; i < n; i++) {
        if (color[i] == 0) dfs(i);
    }
    
    if (hasCycle) return {};
    reverse(order.begin(), order.end());
    return order;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Course Schedule (LeetCode 207)
// ═══════════════════════════════════════════════════════════════════════════

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    
    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        indegree[p[0]]++;
    }
    
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    int completed = 0;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        completed++;
        
        for (int next : adj[course]) {
            if (--indegree[next] == 0) q.push(next);
        }
    }
    
    return completed == numCourses;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Course Schedule II (LeetCode 210) ⭐
// ═══════════════════════════════════════════════════════════════════════════

vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> adj(numCourses);
    vector<int> indegree(numCourses, 0);
    
    for (auto& p : prerequisites) {
        adj[p[1]].push_back(p[0]);
        indegree[p[0]]++;
    }
    
    queue<int> q;
    for (int i = 0; i < numCourses; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    vector<int> order;
    while (!q.empty()) {
        int course = q.front();
        q.pop();
        order.push_back(course);
        
        for (int next : adj[course]) {
            if (--indegree[next] == 0) q.push(next);
        }
    }
    
    return order.size() == numCourses ? order : vector<int>();
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Alien Dictionary (LeetCode 269) ⭐ GOOGLE FAVORITE
// ═══════════════════════════════════════════════════════════════════════════

string alienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> adj;
    unordered_map<char, int> indegree;
    
    // Initialize all characters
    for (const string& word : words) {
        for (char c : word) {
            indegree[c] = 0;
        }
    }
    
    // Build graph
    for (int i = 0; i < words.size() - 1; i++) {
        string& w1 = words[i];
        string& w2 = words[i + 1];
        
        // Invalid: "abc" before "ab"
        if (w1.size() > w2.size() && w1.substr(0, w2.size()) == w2) {
            return "";
        }
        
        for (int j = 0; j < min(w1.size(), w2.size()); j++) {
            if (w1[j] != w2[j]) {
                if (!adj[w1[j]].count(w2[j])) {
                    adj[w1[j]].insert(w2[j]);
                    indegree[w2[j]]++;
                }
                break;
            }
        }
    }
    
    // Topological sort
    queue<char> q;
    for (auto& [c, deg] : indegree) {
        if (deg == 0) q.push(c);
    }
    
    string result;
    while (!q.empty()) {
        char c = q.front();
        q.pop();
        result += c;
        
        for (char next : adj[c]) {
            if (--indegree[next] == 0) q.push(next);
        }
    }
    
    return result.size() == indegree.size() ? result : "";
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 4: Parallel Courses (LeetCode 1136)
// Min semesters to complete all courses
// ═══════════════════════════════════════════════════════════════════════════

int minimumSemesters(int n, vector<vector<int>>& relations) {
    vector<vector<int>> adj(n + 1);
    vector<int> indegree(n + 1, 0);
    
    for (auto& r : relations) {
        adj[r[0]].push_back(r[1]);
        indegree[r[1]]++;
    }
    
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) q.push(i);
    }
    
    int semesters = 0, completed = 0;
    
    while (!q.empty()) {
        semesters++;
        int size = q.size();
        
        for (int i = 0; i < size; i++) {
            int course = q.front();
            q.pop();
            completed++;
            
            for (int next : adj[course]) {
                if (--indegree[next] == 0) q.push(next);
            }
        }
    }
    
    return completed == n ? semesters : -1;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 5: Longest Increasing Path in Matrix (LeetCode 329) ⭐
// ═══════════════════════════════════════════════════════════════════════════

int longestIncreasingPath(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> memo(m, vector<int>(n, 0));
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    
    function<int(int, int)> dfs = [&](int r, int c) -> int {
        if (memo[r][c]) return memo[r][c];
        
        memo[r][c] = 1;
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                matrix[nr][nc] > matrix[r][c]) {
                memo[r][c] = max(memo[r][c], 1 + dfs(nr, nc));
            }
        }
        
        return memo[r][c];
    };
    
    int maxLen = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            maxLen = max(maxLen, dfs(i, j));
        }
    }
    
    return maxLen;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Topological Sort Module ===\n\n";
    
    // Test Course Schedule
    vector<vector<int>> prereqs1 = {{1,0},{2,1}};
    cout << "1. Can finish: " << (canFinish(3, prereqs1) ? "Yes" : "No") << "\n";
    
    // Test Course Schedule II
    vector<vector<int>> prereqs2 = {{1,0},{2,0},{3,1},{3,2}};
    auto order = findOrder(4, prereqs2);
    cout << "2. Order: ";
    for (int c : order) cout << c << " ";
    cout << "\n";
    
    // Test Alien Dictionary
    vector<string> words = {"wrt","wrf","er","ett","rftt"};
    cout << "3. Alien order: " << alienOrder(words) << "\n";
    
    // Test Longest Increasing Path
    vector<vector<int>> matrix = {{9,9,4},{6,6,8},{2,1,1}};
    cout << "5. Longest path: " << longestIncreasingPath(matrix) << "\n";
    
    return 0;
}

/*
================================================================================
                    TOPOLOGICAL SORT PATTERNS
================================================================================

1. KAHN'S ALGORITHM (BFS):
   - Calculate indegree
   - Start with indegree = 0 nodes
   - Decrement neighbor indegrees

2. DFS-BASED:
   - Color nodes (white/gray/black)
   - Add to result in post-order
   - Reverse at end

3. CYCLE DETECTION:
   - Kahn's: order.size() != n
   - DFS: gray node visited again

4. PARALLEL PROCESSING:
   - BFS level = one time unit
   - Count levels for min time

================================================================================
*/

