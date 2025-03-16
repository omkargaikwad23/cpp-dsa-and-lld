#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <utility>
#include <unordered_set>

using namespace std;

/*
Ask:
a) if its possible to fly from starting airport to ending airport with timing in mind
b) path taken

Input: Starting Airport, Ending Airport, List of Flight Schedule with corresponding flying & landing time (eg (AirportA, 1) -> (AirportB, 4))

eg: can you fly from A to C with following flight schedule:
Flight 1: A,1 -> B,4
Flight 2: B,3 -> C,5
ans: no because you cannot "go back in time". When you land at B, flight 2 has already taken off.
*/

struct Flight {
    string destination;
    int departure;
    int arrival;
};

bool canFly(const string& start, const string& end, const vector<tuple<string, int, string, int>>& flights, vector<string>& path) {
    unordered_map<string, vector<Flight>> flightGraph;
    
    // Build the graph
    for (const auto& flightInfo : flights) {
        string from = get<0>(flightInfo);
        int departure = get<1>(flightInfo);
        string to = get<2>(flightInfo);
        int arrival = get<3>(flightInfo);
        
        flightGraph[from].push_back({to, departure, arrival});
    }
    
    // Priority Queue for BFS: (current_location, current_time, path_taken)
    queue<tuple<string, int, vector<string>>> q;
    q.push({start, 0, {start}});
    
    // Visited set to prevent cycles
    unordered_set<string> visited;
    
    while (!q.empty()) {
        auto [current, currentTime, currentPath] = q.front();
        q.pop();

        if (current == end) {
            path = currentPath;
            return true;
        }

        visited.insert(current);

        for (const auto& flight : flightGraph[current]) {
            if (flight.departure >= currentTime && visited.find(flight.destination) == visited.end()) {
                vector<string> newPath = currentPath;
                newPath.push_back(flight.destination);
                q.push({flight.destination, flight.arrival, newPath});
            }
        }
    }
    
    return false;
}

int main() {
    vector<tuple<string, int, string, int>> flightSchedule = {
        {"A", 1, "B", 4},
        {"B", 3, "C", 5}
    };
    
    vector<string> path;
    if (canFly("A", "C", flightSchedule, path)) {
        cout << "Yes, you can fly from A to C." << endl;
        cout << "Path taken: ";
        for (const auto& airport : path) {
            cout << airport << " ";
        }
        cout << endl;
    } else {
        cout << "No, you cannot fly from A to C with the given schedule." << endl;
    }
    
    return 0;
}