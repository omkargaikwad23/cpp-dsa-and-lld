/*
================================================================================
                WORKER SCHEDULE (Google Interview)
================================================================================

PROBLEM:
Given a list of worker shifts [name, start, end], generate a schedule showing
which workers are present during each time interval.

================================================================================
                         EXAMPLES
================================================================================

Input: [["Abby", 10, 100], ["Ben", 50, 70], ["Carla", 60, 70], ["David", 120, 300]]

Output:
[[10, 50, ["Abby"]], 
 [50, 60, ["Abby", "Ben"]], 
 [60, 70, ["Abby", "Ben", "Carla"]], 
 [70, 100, ["Abby"]], 
 [120, 300, ["David"]]]

================================================================================
                         APPROACH
================================================================================

LINE SWEEP / EVENT-BASED:
1. Create events: (time, name, isStart)
2. Sort events by time (end events before start if same time)
3. Process events, maintaining active worker set
4. Generate intervals when time changes

TIME:  O(n log n) - sorting events
SPACE: O(n) - storing events and active workers

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct Event {
    int time;
    string name;
    bool isStart;
    
    Event(int t, string n, bool s) : time(t), name(n), isStart(s) {}
};

vector<tuple<int, int, vector<string>>> generateSchedule(
    vector<tuple<string, int, int>>& shifts) {
    
    // Create events
    vector<Event> events;
    for (auto& [name, start, end] : shifts) {
        events.emplace_back(start, name, true);
        events.emplace_back(end, name, false);
    }
    
    // Sort: by time, end events before start events (if same time)
    sort(events.begin(), events.end(), [](const Event& a, const Event& b) {
        if (a.time == b.time) {
            return a.isStart < b.isStart;  // false (end) < true (start)
        }
        return a.time < b.time;
    });
    
    // Process events
    vector<tuple<int, int, vector<string>>> schedule;
    set<string> activeWorkers;
    int prevTime = -1;
    
    for (const Event& event : events) {
        // Create interval if time changed and we have active workers
        if (prevTime != -1 && event.time != prevTime && !activeWorkers.empty()) {
            vector<string> workers(activeWorkers.begin(), activeWorkers.end());
            schedule.push_back({prevTime, event.time, workers});
        }
        
        // Update active workers
        if (event.isStart) {
            activeWorkers.insert(event.name);
        } else {
            activeWorkers.erase(event.name);
        }
        
        prevTime = event.time;
    }
    
    return schedule;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    vector<tuple<string, int, int>> shifts = {
        {"Abby", 10, 100},
        {"Ben", 50, 70},
        {"Carla", 60, 70},
        {"David", 120, 300}
    };
    
    cout << "=== Input Shifts ===\n";
    for (auto& [name, start, end] : shifts) {
        cout << name << ": [" << start << ", " << end << "]\n";
    }
    cout << "\n";
    
    auto schedule = generateSchedule(shifts);
    
    cout << "=== Generated Schedule ===\n";
    for (auto& [start, end, workers] : schedule) {
        cout << "[" << start << ", " << end << "] → [";
        for (int i = 0; i < workers.size(); i++) {
            cout << workers[i];
            if (i < workers.size() - 1) cout << ", ";
        }
        cout << "]\n";
    }
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

TIME:  O(n log n)
- Creating events: O(n)
- Sorting events: O(n log n)
- Processing events: O(n)
- Set operations: O(log n) each, O(n log n) total

SPACE: O(n)
- Events array: O(n)
- Active workers set: O(n) worst case
- Result: O(n) intervals

FOLLOW-UP QUESTIONS:
1. What if we need count of workers instead of names?
   → Use counter instead of set
   
2. What if shifts can overlap for same worker?
   → Use multiset or counter per worker
   
3. Query: how many workers at time T?
   → Binary search on intervals or use segment tree

================================================================================
*/

