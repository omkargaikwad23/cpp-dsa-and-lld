/*
================================================================================
                    UNION-FIND (Disjoint Set Union - DSU)
================================================================================

USE WHEN:
- Dynamic connectivity queries
- Grouping/clustering elements
- Cycle detection in undirected graph
- Kruskal's MST algorithm

TIME: O(α(n)) ≈ O(1) amortized per operation
SPACE: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// TEMPLATE: Union-Find with Path Compression + Union by Rank ⭐
// ═══════════════════════════════════════════════════════════════════════════

class DSU {
public:
    vector<int> parent, rank_, size_;
    int components;
    
    DSU(int n) : parent(n), rank_(n, 0), size_(n, 1), components(n) {
        iota(parent.begin(), parent.end(), 0);  // parent[i] = i
    }
    
    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    // Union by rank
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;  // Already connected
        
        // Union by rank
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px; // attach smaller tree to larger tree, rank of px is now the max rank
        size_[px] += size_[py];
        if (rank_[px] == rank_[py]) rank_[px]++; // if ranks are equal, increment rank of px
        
        components--; // decrement number of components
        return true; // return true if union is successful
    }
    
    bool connected(int x, int y) { return find(x) == find(y); }
    int getSize(int x) { return size_[find(x)]; }
    int getComponents() { return components; }
};


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 1: Number of Connected Components (LeetCode 323)
// ═══════════════════════════════════════════════════════════════════════════

int countComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    for (auto& e : edges) {
        dsu.unite(e[0], e[1]);
    }
    return dsu.getComponents();
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 2: Redundant Connection (LeetCode 684) ⭐
// Find edge that creates cycle
// ═══════════════════════════════════════════════════════════════════════════

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


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 3: Graph Valid Tree (LeetCode 261)
// Tree = Connected + No Cycles = n nodes + n-1 edges
// ═══════════════════════════════════════════════════════════════════════════

bool validTree(int n, vector<vector<int>>& edges) {
    if (edges.size() != n - 1) return false;
    
    DSU dsu(n);
    for (auto& e : edges) {
        if (!dsu.unite(e[0], e[1])) return false;
    }
    
    return dsu.getComponents() == 1;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 4: Accounts Merge (LeetCode 721) ⭐ GOOGLE FAVORITE
// ═══════════════════════════════════════════════════════════════════════════

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string, int> emailToId;
    unordered_map<string, string> emailToName;
    int id = 0;
    
    for (auto& acc : accounts) {
        for (int i = 1; i < acc.size(); i++) {
            if (!emailToId.count(acc[i])) {
                emailToId[acc[i]] = id++;
            }
            emailToName[acc[i]] = acc[0];
        }
    }
    
    DSU dsu(id);
    
    for (auto& acc : accounts) {
        int firstId = emailToId[acc[1]];
        for (int i = 2; i < acc.size(); i++) {
            dsu.unite(firstId, emailToId[acc[i]]);
        }
    }
    
    unordered_map<int, vector<string>> groups;
    for (auto& [email, eId] : emailToId) {
        groups[dsu.find(eId)].push_back(email);
    }
    
    vector<vector<string>> result;
    for (auto& [root, emails] : groups) {
        sort(emails.begin(), emails.end());
        vector<string> acc = {emailToName[emails[0]]};
        acc.insert(acc.end(), emails.begin(), emails.end());
        result.push_back(acc);
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 5: Number of Islands II (LeetCode 305) ⭐
// ═══════════════════════════════════════════════════════════════════════════

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
                if (dsu.unite(idx, nr * n + nc)) {
                    islands--;
                }
            }
        }
        
        result.push_back(islands);
    }
    
    return result;
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 6: Most Stones Removed (LeetCode 947)
// ═══════════════════════════════════════════════════════════════════════════

int removeStones(vector<vector<int>>& stones) {
    int n = stones.size();
    DSU dsu(n);
    
    unordered_map<int, int> rowFirst, colFirst;
    
    for (int i = 0; i < n; i++) {
        int r = stones[i][0], c = stones[i][1];
        
        if (rowFirst.count(r)) dsu.unite(i, rowFirst[r]);
        else rowFirst[r] = i;
        
        if (colFirst.count(c)) dsu.unite(i, colFirst[c]);
        else colFirst[c] = i;
    }
    
    return n - dsu.getComponents();
}


// ═══════════════════════════════════════════════════════════════════════════
// PROBLEM 7: Satisfiability of Equality Equations (LeetCode 990)
// ═══════════════════════════════════════════════════════════════════════════

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
        if (eq[1] == '!' && dsu.connected(eq[0] - 'a', eq[3] - 'a')) {
            return false;
        }
    }
    
    return true;
}


// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    cout << "=== Union-Find Module ===\n\n";
    
    // Test Connected Components
    vector<vector<int>> edges1 = {{0,1},{1,2},{3,4}};
    cout << "1. Components: " << countComponents(5, edges1) << "\n";
    
    // Test Redundant Connection
    vector<vector<int>> edges2 = {{1,2},{1,3},{2,3}};
    auto redundant = findRedundantConnection(edges2);
    cout << "2. Redundant: [" << redundant[0] << "," << redundant[1] << "]\n";
    
    // Test Valid Tree
    vector<vector<int>> edges3 = {{0,1},{0,2},{0,3},{1,4}};
    cout << "3. Valid tree: " << (validTree(5, edges3) ? "Yes" : "No") << "\n";
    
    // Test Stones Removed
    vector<vector<int>> stones = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    cout << "6. Stones removed: " << removeStones(stones) << "\n";
    
    return 0;
}

/*
================================================================================
                    UNION-FIND PATTERNS SUMMARY
================================================================================

1. BASIC OPERATIONS:
   - find(x): Get root with path compression
   - unite(x, y): Merge sets with union by rank

2. CONNECTED COMPONENTS:
   - Track count, decrement on successful union

3. CYCLE DETECTION:
   - If unite() returns false, edge creates cycle

4. GRID PROBLEMS:
   - Flatten 2D to 1D: idx = row * cols + col

5. GROUPING:
   - Map elements to IDs
   - Group by root after all unions

================================================================================
*/

