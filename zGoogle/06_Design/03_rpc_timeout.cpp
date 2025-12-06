/*
================================================================================
                RPC TIMEOUT DETECTION (Google Interview)
================================================================================

PROBLEM:
You have a stream of RPC request logs. Each log has: {id, timestamp, type}.
Type is either "Start" or "End".

Given a timeout T, detect AT THE EARLIEST POSSIBLE TIME if a request has
timed out (i.e., when we process a log and realize a request is overdue).

================================================================================
                         EXAMPLES
================================================================================

Logs:
id=0, time=0, Start
id=1, time=1, Start
id=0, time=2, End
id=2, time=6, Start
id=1, time=7, End

Timeout = 3

Answer: {1, 6}
- At time 6, when we process id=2 Start, we check pending requests
- id=1 started at time=1, now time=6, duration > 3 → TIMED OUT
- We detect id=1's timeout at time 6

================================================================================
                         APPROACH
================================================================================

1. Use HashMap to track start times: id → startTime
2. Use Queue to maintain order of pending requests
3. For each new log:
   - Before processing, check if any pending request has timed out
   - Process the current log (start → add to map/queue, end → remove)

TIME:  O(n) amortized - each request added/removed once
SPACE: O(n) - storing pending requests

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct Log {
    int id;
    int time;
    string type;  // "Start" or "End"
    
    Log(int i, int t, string ty) : id(i), time(t), type(ty) {}
};

class RPCTimeoutDetector {
private:
    unordered_map<int, int> startTimes;  // id → start time
    queue<int> pendingOrder;              // Order of pending starts
    int timeout;
    
public:
    RPCTimeoutDetector(int t) : timeout(t) {}
    
    vector<pair<int, int>> processLogs(vector<Log>& logs) {
        vector<pair<int, int>> timedOut;  // {id, detection_time}
        
        for (auto& log : logs) {
            // Check for timeouts before processing new log
            while (!pendingOrder.empty()) {
                int frontId = pendingOrder.front();
                
                // Skip if already completed
                if (startTimes.find(frontId) == startTimes.end()) {
                    pendingOrder.pop();
                    continue;
                }
                
                // Check if timed out
                if (log.time - startTimes[frontId] > timeout) {
                    timedOut.push_back({frontId, log.time});
                    startTimes.erase(frontId);
                    pendingOrder.pop();
                } else {
                    break;  // If front hasn't timed out, neither have later ones
                }
            }
            
            // Process current log
            if (log.type == "Start") {
                startTimes[log.id] = log.time;
                pendingOrder.push(log.id);
            } else {  // "End"
                if (startTimes.count(log.id)) {
                    startTimes.erase(log.id);
                    // Note: we don't remove from queue immediately (lazy removal)
                }
            }
        }
        
        return timedOut;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    vector<Log> logs = {
        {0, 0, "Start"},
        {1, 1, "Start"},
        {0, 2, "End"},
        {2, 6, "Start"},
        {1, 7, "End"}
    };
    
    int timeout = 3;
    
    cout << "=== RPC Logs ===\n";
    for (auto& log : logs) {
        cout << "id=" << log.id << ", time=" << log.time 
             << ", " << log.type << "\n";
    }
    cout << "\nTimeout = " << timeout << "\n\n";
    
    RPCTimeoutDetector detector(timeout);
    auto timedOut = detector.processLogs(logs);
    
    cout << "=== Timeout Detections ===\n";
    for (auto& [id, detectionTime] : timedOut) {
        cout << "Request " << id << " timed out (detected at time " 
             << detectionTime << ")\n";
    }
    
    if (timedOut.empty()) {
        cout << "No timeouts detected.\n";
    }
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

TIME:  O(n) amortized
- Each request is added to queue once, removed once
- Each log processed once

SPACE: O(n)
- HashMap for start times: O(n)
- Queue for pending order: O(n)

KEY INSIGHT:
- We can only detect timeout when processing a NEW log
- Between logs, no detection happens (no background timer)
- Queue maintains FIFO order of starts for efficient timeout checking

FOLLOW-UP:
1. What if we need real-time detection with background timer?
   → Use priority queue ordered by (startTime + timeout)
   
2. What if logs can arrive out of order?
   → Sort by timestamp first, or use more complex state management

================================================================================
*/

