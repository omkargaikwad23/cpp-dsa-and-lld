/*
================================================================================
                MAX CARS IN GARAGE (Google Interview)
================================================================================

PROBLEM:
Given piles of car parking tickets with arrival and departure times,
find the maximum number of cars in the garage at any given time.

================================================================================
                         EXAMPLES
================================================================================

Tickets: [(1,4), (2,5), (7,9), (3,6)]
- At time 3: cars with tickets (1,4), (2,5), (3,6) are present → 3 cars
- Maximum: 3 cars

================================================================================
                         APPROACH
================================================================================

LINE SWEEP / EVENT-BASED:
1. Create events: arrival (+1), departure (-1)
2. Sort by time (departures before arrivals if same time)
3. Sweep through, tracking running count

TIME:  O(n log n) - sorting
SPACE: O(n) - events array

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

int maxCarsInGarage(const vector<pair<int, int>>& tickets) {
    // Create events: (time, type) where 'A'=arrival, 'D'=departure
    vector<pair<int, char>> events;
    
    for (const auto& ticket : tickets) {
        events.push_back({ticket.first, 'A'});   // Arrival
        events.push_back({ticket.second, 'D'});  // Departure
    }
    
    // Sort: by time, departures before arrivals (if same time)
    // This ensures a car leaving at time T is counted before one arriving at T
    sort(events.begin(), events.end(), [](const auto& a, const auto& b) {
        if (a.first == b.first) {
            return a.second < b.second;  // 'A' > 'D', so 'D' comes first
        }
        return a.first < b.first;
    });
    
    int currentCars = 0;
    int maxCars = 0;
    
    for (const auto& event : events) {
        if (event.second == 'A') {
            currentCars++;
            maxCars = max(maxCars, currentCars);
        } else {
            currentCars--;
        }
    }
    
    return maxCars;
}

// Alternative: Using map (auto-sorted)
int maxCarsInGarageMap(const vector<pair<int, int>>& tickets) {
    map<int, int> timeline;
    
    for (const auto& ticket : tickets) {
        timeline[ticket.first]++;   // Arrival: +1
        timeline[ticket.second]--;  // Departure: -1
    }
    
    int current = 0, maxCars = 0;
    for (const auto& [time, delta] : timeline) {
        current += delta;
        maxCars = max(maxCars, current);
    }
    
    return maxCars;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    vector<pair<int, int>> tickets = {
        {1, 4},
        {2, 5},
        {7, 9},
        {3, 6}
    };
    
    cout << "=== Parking Tickets ===\n";
    for (const auto& t : tickets) {
        cout << "[" << t.first << ", " << t.second << "]\n";
    }
    cout << "\n";
    
    cout << "Max cars (event method): " << maxCarsInGarage(tickets) << "\n";
    cout << "Max cars (map method): " << maxCarsInGarageMap(tickets) << "\n";
    
    // Test edge case: overlapping at same time
    vector<pair<int, int>> tickets2 = {
        {1, 5},
        {5, 10}  // Arrives exactly when first leaves
    };
    
    cout << "\n=== Edge Case: Back-to-back ===\n";
    cout << "[1,5] and [5,10]\n";
    cout << "Max cars: " << maxCarsInGarageMap(tickets2) << " (should be 1)\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

EVENT SORTING METHOD:
- Time: O(n log n) for sorting
- Space: O(n) for events array

MAP METHOD:
- Time: O(n log n) for map insertions
- Space: O(n) for map entries

BOTH handle the case where departure and arrival happen at same time:
- Map method: automatically combines +1 and -1 at same time point
- Event method: sort departures before arrivals

================================================================================
*/

