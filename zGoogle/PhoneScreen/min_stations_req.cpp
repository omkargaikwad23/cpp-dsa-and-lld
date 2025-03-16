#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
There are piles of car parking tickets, each having the arrival time and departure time of the car. Return the number of cars in the garage at any given time.

Time: O(nlogn).
*/

int maxCarsInGarage(const vector<pair<int, int>>& tickets) {
    vector<pair<int, char>> events; // 'A' for arrival, 'D' for departure
    
    // Create events
    for (const auto& ticket : tickets) {
        events.push_back({ticket.first, 'A'});  // Arrival event
        events.push_back({ticket.second, 'D'}); // Departure event
    }
    
    // Sort events: first by time, then by type ('D' before 'A' if equal)
    sort(events.begin(), events.end(), [](const pair<int, char>& a, const pair<int, char>& b) {
        if (a.first == b.first)
            return a.second < b.second;
        return a.first < b.first;
    });
    
    int maxCars = 0, currentCars = 0;
    
    // Process events
    for (const auto& event : events) {
        if (event.second == 'A') {
            currentCars++;
            maxCars = max(maxCars, currentCars);
        } else { // event.second == 'D'
            currentCars--;
        }
    }
    
    return maxCars;
}

int main() {
    vector<pair<int, int>> tickets = {
        {1, 4},  // Car arrives at time 1 and departs at time 4
        {2, 5},
        {7, 9},
        {3, 6}
    };
    
    cout << "The maximum number of cars in the garage at any time is: " << maxCarsInGarage(tickets) << endl;
    
    return 0;
}