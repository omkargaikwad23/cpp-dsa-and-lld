/*
================================================================================
                    UNION-FIND PROBLEMS - Google Interview Favorites
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// UNION-FIND TEMPLATE
// ═══════════════════════════════════════════════════════════════════════════

class DSU {
public:
    vector<int> parent, rank_, size_;
    int components;
    
    DSU(int n) : parent(n), rank_(n, 0), size_(n, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        size_[px] += size_[py];
        if (rank_[px] == rank_[py]) rank_[px]++;
        components--;
        return true;
    }
    
    bool connected(int x, int y) { return find(x) == find(y); }
    int getSize(int x) { return size_[find(x)]; }
    int getComponents() { return components; }
};


/*
PROBLEM 1: Number of Connected Components (LeetCode 323) ⭐
──────────────────────────────────────────────────────────
Count connected components in undirected graph.
Time: O(E * α(n)) | Space: O(n)
*/
int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    for (auto& e : edges) {
        dsu.unite(e[0], e[1]);
    }
    return dsu.getComponents();
}


/*
PROBLEM 2: Redundant Connection (LeetCode 684) ⭐
────────────────────────────────────────────────
Find edge that creates cycle in undirected graph.
Time: O(E * α(n)) | Space: O(n)
*/
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n = edges.size();
    DSU dsu(n + 1);
    
    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) {
            return e;  // This edge creates cycle
        }
    }
    
    return {};
}


/*
PROBLEM 3: Graph Valid Tree (LeetCode 261)
──────────────────────────────────────────
Check if graph is a valid tree (connected + no cycles).
Tree: n nodes, n-1 edges, connected
*/
bool validTree(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) return false;  // Must have n-1 edges
    
    DSU dsu(n);
    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) return false;  // Cycle detected
    }
    
    return dsu.getComponents() == 1;  // Must be connected
}


/*
PROBLEM 4: Accounts Merge (LeetCode 721) ⭐ GOOGLE FAVORITE
──────────────────────────────────────────────────────────
Merge accounts with common emails.
Time: O(n * m * α(n*m)) | Space: O(n*m)
*/
vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, int> emailToId;
    unordered_map<string, string> emailToName;
    int id = 0;
    
    // Assign unique id to each email
    for (auto& acc : accounts) {
        for (int i = 1; i < acc.size(); i++) {
            if (!emailToId.count(acc[i])) {
                emailToId[acc[i]] = id++;
            }
            emailToName[acc[i]] = acc[0];
        }
    }
    
    DSU dsu(id);
    
    // Union emails in same account
    for (auto& acc : accounts) {
        int firstId = emailToId[acc[1]];
        for (int i = 2; i < acc.size(); i++) {
            dsu.unite(firstId, emailToId[acc[i]]);
        }
    }
    
    // Group emails by root
    unordered_map<int, vector<string>> groups;
    for (auto& [email, eId] : emailToId) {
        groups[dsu.find(eId)].push_back(email);
    }
    
    // Build result
    vector<vector<string>> result;
    for (auto& [root, emails] : groups) {
        sort(emails.begin(), emails.end());
        vector<string> acc = {emailToName[emails[0]]};
        acc.insert(acc.end(), emails.begin(), emails.end());
        result.push_back(acc);
    }
    
    return result;
}


/*
PROBLEM 5: Longest Consecutive Sequence (LeetCode 128)
──────────────────────────────────────────────────────
Find length of longest consecutive sequence.
Time: O(n) | Space: O(n)
*/
int longestConsecutive(vector<int>& nums) {
    unordered_map<int, int> numToIdx;
    int n = nums.size();
    if (n == 0) return 0;
    
    for (int i = 0; i < n; i++) {
        numToIdx[nums[i]] = i;
    }
    
    DSU dsu(n);
    
    for (int num : nums) {
        if (numToIdx.count(num + 1)) {
            dsu.unite(numToIdx[num], numToIdx[num + 1]);
        }
    }
    
    int maxLen = 1;
    for (int i = 0; i < n; i++) {
        maxLen = max(maxLen, dsu.getSize(i));
    }
    
    return maxLen;
}


/*
PROBLEM 6: Number of Islands II (LeetCode 305) ⭐
────────────────────────────────────────────────
Count islands after each land addition.
Time: O(k * α(m*n)) | Space: O(m*n)
*/
vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
    DSU dsu(m * n);
    vector<vector<bool>> grid(m, vector<bool>(n, false));
    vector<pair<int,int>> dirs = {{0,1},{0,-1},{1,0},{-1,0}};
    vector<int> result;
    int islands = 0;
    
    for (auto& pos : positions) {
        int r = pos[0], c = pos[1];
        
        if (grid[r][c]) {
            result.push_back(islands);
            continue;
        }
        
        grid[r][c] = true;
        islands++;
        int idx = r * n + c;
        
        for (auto [dr, dc] : dirs) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc]) {
                int nidx = nr * n + nc;
                if (dsu.unite(idx, nidx)) {
                    islands--;
                }
            }
        }
        
        result.push_back(islands);
    }
    
    return result;
}


/*
PROBLEM 7: Most Stones Removed (LeetCode 947) ⭐
───────────────────────────────────────────────
Remove max stones where each removal shares row/col.
Answer = total - number of connected components
Time: O(n * α(n)) | Space: O(n)
*/
int removeStones(vector<vector<int>>& stones) {
    int n = stones.size();
    DSU dsu(n);
    
    unordered_map<int, int> rowFirst, colFirst;
    
    for (int i = 0; i < n; i++) {
        int r = stones[i][0], c = stones[i][1];
        
        if (rowFirst.count(r)) {
            dsu.unite(i, rowFirst[r]);
        } else {
            rowFirst[r] = i;
        }
        
        if (colFirst.count(c)) {
            dsu.unite(i, colFirst[c]);
        } else {
            colFirst[c] = i;
        }
    }
    
    return n - dsu.getComponents();
}


/*
PROBLEM 8: Satisfiability of Equality Equations (LeetCode 990)
──────────────────────────────────────────────────────────────
Check if equations like "a==b", "b!=c" are satisfiable.
*/
bool equationsPossible(vector<string>& equations) {
    DSU dsu(26);
    
    // Process '==' first
    for (auto& eq : equations) {
        if (eq[1] == '=') {
            dsu.unite(eq[0] - 'a', eq[3] - 'a');
        }
    }
    
    // Check '!='
    for (auto& eq : equations) {
        if (eq[1] == '!') {
            if (dsu.connected(eq[0] - 'a', eq[3] - 'a')) {
                return false;
            }
        }
    }
    
    return true;
}


/*
PROBLEM 9: Smallest String With Swaps (LeetCode 1202)
─────────────────────────────────────────────────────
Swap chars at given index pairs, find lexicographically smallest string.
*/
string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    int n = s.size();
    DSU dsu(n);
    
    for (auto& p : pairs) {
        dsu.unite(p[0], p[1]);
    }
    
    // Group indices by component
    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < n; i++) {
        groups[dsu.find(i)].push_back(i);
    }
    
    // Sort characters within each group
    for (auto& [root, indices] : groups) {
        string chars;
        for (int idx : indices) {
            chars += s[idx];
        }
        sort(chars.begin(), chars.end());
        
        for (int i = 0; i < indices.size(); i++) {
            s[indices[i]] = chars[i];
        }
    }
    
    return s;
}


/*
PROBLEM 10: Minimize Malware Spread (LeetCode 924)
──────────────────────────────────────────────────
Remove one initially infected node to minimize total infection.
*/
int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    int n = graph.size();
    DSU dsu(n);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j]) dsu.unite(i, j);
        }
    }
    
    // Count infected nodes per component
    unordered_map<int, int> infectedCount;
    for (int node : initial) {
        infectedCount[dsu.find(node)]++;
    }
    
    // Find node to remove
    int result = initial[0];
    int maxSaved = 0;
    
    sort(initial.begin(), initial.end());
    
    for (int node : initial) {
        int root = dsu.find(node);
        if (infectedCount[root] == 1) {  // Only this node infected in component
            int saved = dsu.getSize(node);
            if (saved > maxSaved) {
                maxSaved = saved;
                result = node;
            }
        }
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Union-Find Problems ===\n\n";
    
    // Connected Components
    vector<vector<int>> edges1 = {{0,1},{1,2},{3,4}};
    cout << "1. Components in 5 nodes: " << countComponents(5, edges1) << "\n";
    
    // Redundant Connection
    vector<vector<int>> edges2 = {{1,2},{1,3},{2,3}};
    auto redundant = findRedundantConnection(edges2);
    cout << "2. Redundant edge: [" << redundant[0] << "," << redundant[1] << "]\n";
    
    // Valid Tree
    vector<vector<int>> edges3 = {{0,1},{0,2},{0,3},{1,4}};
    cout << "3. Valid tree: " << (validTree(5, edges3) ? "Yes" : "No") << "\n";
    
    // Longest Consecutive
    vector<int> nums = {100,4,200,1,3,2};
    cout << "5. Longest consecutive: " << longestConsecutive(nums) << "\n";
    
    // Most Stones Removed
    vector<vector<int>> stones = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    cout << "7. Stones removed: " << removeStones(stones) << "\n";
    
    return 0;
}

/*
================================================================================
UNION-FIND PATTERNS:
1. Connected components: Count roots
2. Cycle detection: If already connected, edge creates cycle
3. Dynamic connectivity: Process edges and answer queries
4. Group by component: Map root -> elements
5. Grid problems: Flatten 2D to 1D index
================================================================================
*/

