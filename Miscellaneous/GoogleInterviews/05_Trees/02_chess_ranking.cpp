/*
================================================================================
                CHESS PLAYER RANKING (Google Interview)
================================================================================

PROBLEM:
In a tournament, players compete head-to-head. Results form a directed graph
where edge (A → B) means A defeated B.

A player has a "precise rank" if we can determine their exact position.
This happens when: (players they beat) + (players who beat them) + 1 = N

================================================================================
                         EXAMPLES
================================================================================

Players: 0, 1, 2, 3
Results: 0→1, 0→2, 1→2, 3→0, 3→2

Graph:
  3 → 0 → 1
  ↓   ↓   ↓
  2 ← 2 ← 2

For player 0:
- Reachable from 0 (players 0 beats directly/indirectly): {0, 1, 2} = 3
- Reachable TO 0 (players who beat 0 directly/indirectly): {3, 0} = 2
- Total unique: 3 + 2 - 1 = 4 = N → Precise rank!

================================================================================
                         APPROACH
================================================================================

1. Build adjacency list for wins (A → B means A beats B)
2. Build reverse graph for losses
3. For each player:
   - BFS/DFS forward: count all players they transitively beat
   - BFS/DFS reverse: count all players who transitively beat them
   - If reachableForward + reachableBackward - 1 == N → precise rank

TIME:  O(N × (V + E)) - BFS from each player
SPACE: O(V + E) for graphs + O(V) for visited sets

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class TournamentRanking {
private:
    int n;  // Number of players
    vector<vector<int>> wins;     // wins[i] = players that i defeated
    vector<vector<int>> losses;   // losses[i] = players that defeated i
    
    int bfs(int start, const vector<vector<int>>& adj) {
        unordered_set<int> visited;
        queue<int> q;
        
        q.push(start);
        visited.insert(start);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (int neighbor : adj[node]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        
        return visited.size();
    }
    
public:
    TournamentRanking(int numPlayers) : n(numPlayers) {
        wins.resize(n);
        losses.resize(n);
    }
    
    void addResult(int winner, int loser) {
        wins[winner].push_back(loser);
        losses[loser].push_back(winner);
    }
    
    vector<int> findPlayersWithPreciseRank() {
        vector<int> result;
        
        for (int player = 0; player < n; player++) {
            // Count players this player transitively beats
            int beatsCount = bfs(player, wins);
            
            // Count players who transitively beat this player
            int beatenByCount = bfs(player, losses);
            
            // Check if rank is precise
            // beatsCount includes self, beatenByCount includes self
            // So we subtract 1 to avoid double-counting self
            if (beatsCount + beatenByCount - 1 == n) {
                result.push_back(player);
            }
            
            cout << "Player " << player << ": beats=" << beatsCount 
                 << ", beaten by=" << beatenByCount;
            if (beatsCount + beatenByCount - 1 == n) {
                cout << " → PRECISE RANK";
            }
            cout << "\n";
        }
        
        return result;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    TournamentRanking tournament(4);
    
    // Add match results: winner, loser
    tournament.addResult(0, 1);  // 0 beats 1
    tournament.addResult(0, 2);  // 0 beats 2
    tournament.addResult(1, 2);  // 1 beats 2
    tournament.addResult(3, 0);  // 3 beats 0
    tournament.addResult(3, 2);  // 3 beats 2
    
    cout << "=== Tournament Results ===\n";
    cout << "0 beats 1, 2\n";
    cout << "1 beats 2\n";
    cout << "3 beats 0, 2\n\n";
    
    cout << "=== Analyzing Rankings ===\n";
    vector<int> preciseRanks = tournament.findPlayersWithPreciseRank();
    
    cout << "\n=== Players with Precise Rank ===\n";
    for (int player : preciseRanks) {
        cout << "Player " << player << "\n";
    }
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

TIME:  O(N × (V + E))
- For each of N players, run BFS twice
- Each BFS is O(V + E)

SPACE: O(V + E)
- Store both forward and reverse graphs
- BFS visited set: O(V)

OPTIMIZATIONS:
1. If graph is a DAG (no cycles), use topological sort for O(V + E) total
2. Use Floyd-Warshall for transitive closure if dense graph
3. Use SCCs if cycles exist

================================================================================
*/

