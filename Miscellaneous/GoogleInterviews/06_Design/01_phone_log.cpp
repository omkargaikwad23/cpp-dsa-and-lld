/*
================================================================================
                PHONE LOG SYSTEM (Google Interview)
================================================================================

PROBLEM:
Design a system for a telephone company that tracks phone call logs.

Implement:
1. registerLog(personId, startTime, endTime) - Record a phone call
2. getMostTalkativePerson(timestamp) - Return person with most talk time
   (only count COMPLETED calls before timestamp)

================================================================================
                         EXAMPLES
================================================================================

registerLog("Alice", 0, 10)   // Alice talks 10 units
registerLog("Bob", 5, 15)     // Bob talks 10 units  
registerLog("Alice", 20, 35)  // Alice talks 15 more units
registerLog("Bob", 30, 40)    // Bob talks 10 more units

getMostTalkativePerson(12)  → "Alice" (Alice: 10, Bob: 0 - not complete)
getMostTalkativePerson(20)  → Either (Alice: 10, Bob: 10)
getMostTalkativePerson(40)  → "Alice" (Alice: 25, Bob: 20)

================================================================================
                         APPROACH
================================================================================

BASIC: HashMap storing person → list of (start, end)
QUERY: Iterate all logs, sum completed calls for each person

OPTIMIZED:
- Sort logs by endTime for binary search
- Or use prefix sums for frequent queries
- Or use segment tree for range queries

TIME:  registerLog: O(1), getMostTalkative: O(N×M)
SPACE: O(N×M) where N = people, M = avg calls per person

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

class PhoneLogSystem {
private:
    // personId → list of {startTime, endTime}
    unordered_map<string, vector<pair<int, int>>> logs;
    
public:
    // O(1) - just append
    void registerLog(string personId, int startTime, int endTime) {
        logs[personId].push_back({startTime, endTime});
    }
    
    // O(N × M) - iterate all people and their calls
    string getMostTalkativePerson(int timestamp) {
        string mostTalkative = "";
        int maxTalkTime = 0;
        
        for (auto& [personId, callLogs] : logs) {
            int totalTime = 0;
            
            for (auto& [start, end] : callLogs) {
                // Only count COMPLETED calls (end <= timestamp)
                if (end <= timestamp) {
                    totalTime += (end - start);
                }
            }
            
            if (totalTime > maxTalkTime) {
                maxTalkTime = totalTime;
                mostTalkative = personId;
            }
        }
        
        return mostTalkative;
    }
    
    // Extension: Consider ongoing calls too
    string getMostTalkativeWithOngoing(int timestamp) {
        string mostTalkative = "";
        int maxTalkTime = 0;
        
        for (auto& [personId, callLogs] : logs) {
            int totalTime = 0;
            
            for (auto& [start, end] : callLogs) {
                if (end <= timestamp) {
                    // Completed call
                    totalTime += (end - start);
                } else if (start <= timestamp) {
                    // Ongoing call - count partial
                    totalTime += (timestamp - start);
                }
            }
            
            if (totalTime > maxTalkTime) {
                maxTalkTime = totalTime;
                mostTalkative = personId;
            }
        }
        
        return mostTalkative;
    }
    
    // Get talk time for specific person
    int getTalkTime(string personId, int timestamp) {
        if (logs.find(personId) == logs.end()) return 0;
        
        int totalTime = 0;
        for (auto& [start, end] : logs[personId]) {
            if (end <= timestamp) {
                totalTime += (end - start);
            }
        }
        return totalTime;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    PhoneLogSystem system;
    
    // Register calls
    system.registerLog("Alice", 0, 10);
    system.registerLog("Bob", 5, 15);
    system.registerLog("Alice", 20, 35);
    system.registerLog("Bob", 30, 40);
    
    cout << "=== Call Logs ===\n";
    cout << "Alice: [0,10], [20,35]\n";
    cout << "Bob: [5,15], [30,40]\n\n";
    
    // Queries
    cout << "=== Queries ===\n";
    
    cout << "At timestamp 12:\n";
    cout << "  Most talkative: " << system.getMostTalkativePerson(12) << "\n";
    cout << "  Alice time: " << system.getTalkTime("Alice", 12) << "\n";
    cout << "  Bob time: " << system.getTalkTime("Bob", 12) << " (call not complete)\n\n";
    
    cout << "At timestamp 20:\n";
    cout << "  Most talkative: " << system.getMostTalkativePerson(20) << "\n";
    cout << "  Alice time: " << system.getTalkTime("Alice", 20) << "\n";
    cout << "  Bob time: " << system.getTalkTime("Bob", 20) << "\n\n";
    
    cout << "At timestamp 40:\n";
    cout << "  Most talkative: " << system.getMostTalkativePerson(40) << "\n";
    cout << "  Alice time: " << system.getTalkTime("Alice", 40) << "\n";
    cout << "  Bob time: " << system.getTalkTime("Bob", 40) << "\n";
    
    return 0;
}

/*
================================================================================
                         OPTIMIZATIONS
================================================================================

1. SORT BY END TIME + BINARY SEARCH:
   - Query becomes O(N × log M) instead of O(N × M)
   
2. PREFIX SUM:
   - Precompute cumulative talk time at each end point
   - Query becomes O(N × log M)
   
3. SEGMENT TREE / FENWICK TREE:
   - If timestamps are bounded, use segment tree
   - Query becomes O(N × log T) where T = time range
   
4. CACHING:
   - Cache results for frequently queried timestamps

================================================================================
                         FOLLOW-UP QUESTIONS
================================================================================

1. Should we count ongoing calls or only completed?
2. Can calls overlap for same person?
3. What's the expected query frequency vs log registration?
4. Do we need top-K talkative people?
5. Can we preprocess data or must handle online queries?

================================================================================
*/

