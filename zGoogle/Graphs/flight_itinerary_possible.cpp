/*
Can you fly from airport A to B given flight schedules with timing constraints?

Input: start, end, flights as [(from, depart_time, to, arrive_time), ...]

Example:
  Flight 1: A@1 -> B@4
  Flight 2: B@3 -> C@5
  
  Can fly A to C? NO - land at B@4, but flight to C departs @3
  
Approach: BFS tracking (airport, earliest_arrival_time)
*/

#include <bits/stdc++.h>
using namespace std;

struct Flight {
    string to;
    int depart, arrive;
};

vector<string> canFly(
    const string& start, const string& end,
    const vector<tuple<string, int, string, int>>& flights
) {
    // Build graph
    unordered_map<string, vector<Flight>> graph;
    for (auto& [from, dep, to, arr] : flights) {
        graph[from].push_back({to, dep, arr});
    }
    
    // BFS: {airport, time, path}
    queue<tuple<string, int, vector<string>>> q;
    q.push({start, 0, {start}});
    
    // Track best arrival time at each airport
    unordered_map<string, int> bestTime;
    bestTime[start] = 0;
    
    while (!q.empty()) {
        auto [curr, time, path] = q.front();
        q.pop();
        
        if (curr == end) return path;
        
        for (auto& [to, dep, arr] : graph[curr]) {
            // Can catch flight & haven't reached 'to' earlier
            if (dep >= time && (!bestTime.count(to) || arr < bestTime[to])) {
                bestTime[to] = arr;
                auto newPath = path;
                newPath.push_back(to);
                q.push({to, arr, newPath});
            }
        }
    }
    
    return {};
}

int main() {
    vector<tuple<string, int, string, int>> flights = {
        {"A", 1, "B", 4},
        {"B", 3, "C", 5}
    };
    
    auto path = canFly("A", "C", flights);
    
    cout << "Yes! Path: ";
    for (const string& s : path) cout << s << " ";
    
    return 0;
}
