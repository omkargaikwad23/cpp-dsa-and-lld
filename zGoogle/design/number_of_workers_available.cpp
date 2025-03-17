/*
You are given a list of worker shifts, where each shift is
represented as a list [name, start, end]. The name is a string
representing the worker's name, start is an integer representing the
start time of the shift, and end is an integer representing the end
time of the shift. The goal is to generate a schedule that shows the
intervals of time and the workers present during each interval.

Example:
Given the input:
[["Abby", 10, 100], ["Ben", 50, 70], ["Carla", 60, 70], 
["David", 120, 300]]

The output should be:
[[10, 50, ["Abby"]], [50, 60, ["Abby", "Ben"]], 
[60, 70, ["Abby", "Ben", "Carla"]], [70, 100, ["Abby"]], 
[120, 300, ["David"]]]




Example Set of Shifts
Suppose we have the following shifts:

["Abby", 10, 20]
["Ben", 15, 25]
Corresponding Events
From the shifts, we generate the following events:

Event(10, "Abby", true) - Abby starts at 10
Event(15, "Ben", true) - Ben starts at 15
Event(20, "Abby", false) - Abby ends at 20
Event(25, "Ben", false) - Ben ends at 25
Sorted Events
When sorted, these events remain in the same order:

10: Abby starts
15: Ben starts
20: Abby ends
25: Ben ends
Processing Events
The loop through the sorted events generates intervals based on active workers between event times, like so:

Event at time 10: Abby starts
Before Processing: activeWorkers is empty.
Update activeWorkers: Add "Abby" to activeWorkers.
prevTime is -1, so we don't generate an interval yet.
Update prevTime: Set prevTime to 10.
Event at time 15: Ben starts
Before Processing Interval: activeWorkers is {"Abby"}.
Check if Interval: Since prevTime (10) is not -1 and time (15) != prevTime, and we have active workers, create an interval from 10 to 15 with {"Abby"}.
Generate Interval: [10, 15, ["Abby"]].
After Processing Interval: Add "Ben" to activeWorkers.
Update prevTime: Set prevTime to 15.
Event at time 20: Abby ends
Before Processing Interval: activeWorkers is {"Abby", "Ben"}.
Check if Interval: Create an interval from 15 to 20 with {"Abby", "Ben"} because time changed.
Generate Interval: [15, 20, ["Abby", "Ben"]].
After Processing Interval: Remove "Abby" from activeWorkers.
Update prevTime: Set prevTime to 20.
Event at time 25: Ben ends
Before Processing Interval: activeWorkers is {"Ben"}.
Check if Interval: Create an interval from 20 to 25 with {"Ben"}.
Generate Interval: [20, 25, ["Ben"]].
After Processing Interval: Remove "Ben" from activeWorkers.
Update prevTime: Set prevTime to 25.
Summary
The loop processes each event, updating the active workers, and creates intervals wherever a change occurs (i.e., when event.time differs from prevTime and there are active workers). It is critical to change the activeWorkers set at each event—that allows us to maintain who is currently working in the interval before creating the next interval and updating prevTime appropriately.


Event(10, "Abby", true)
Event(10, "Ben", true)
If we didn't check event.time != prevTime, processing these two start events separately without creating an interval in between for each change in active workers would mean no time difference, potentially causing confusion or leading to a flawed segmentation of time.
*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

// Helper struct to store events
struct Event {
    int time;
    string name;
    bool isStart;

    Event(int t, string n, bool s) : time(t), name(n), isStart(s) {}
};

// Custom comparator for sorting events
bool compareEvents(const Event &a, const Event &b) {
    if (a.time == b.time) {
        // If events have the same time, prioritize end events over start events
        return a.isStart < b.isStart;
    }
    return a.time < b.time;
}

vector<vector<string>> generateSchedule(vector<vector<string>> shifts) {
    vector<Event> events;
    
    // Create events for all shifts
    for (const auto &shift : shifts) {
        string name = shift[0];
        int start = stoi(shift[1]);
        int end = stoi(shift[2]);
        
        events.emplace_back(start, name, true);
        events.emplace_back(end, name, false);
    }
    
    // Sort events
    sort(events.begin(), events.end(), compareEvents);
    
    vector<vector<string>> schedule;
    set<string> activeWorkers;
    int prevTime = -1;
    
    // Process each event and generate intervals
    for (const auto &event : events) {
        if (prevTime != -1 && event.time != prevTime && !activeWorkers.empty()) {
            // Create a new schedule entry if active workers exist and time has changed
            vector<string> interval;
            interval.push_back(to_string(prevTime));
            interval.push_back(to_string(event.time));
            interval.insert(interval.end(), activeWorkers.begin(), activeWorkers.end());
            schedule.push_back(interval);
        }
        
        if (event.isStart) {
            activeWorkers.insert(event.name);
        } else {
            activeWorkers.erase(event.name);
        }
        
        prevTime = event.time;
    }
    
    return schedule;
}

int main() {
    vector<vector<string>> shifts = {
        {"Abby", "10", "100"},
        {"Ben", "50", "70"},
        {"Carla", "60", "70"},
        {"David", "120", "300"}
    };
    
    vector<vector<string>> schedule = generateSchedule(shifts);
    
    for (const auto& interval : schedule) {
        cout << "[" << interval[0] << ", " << interval[1] << ", [";
        for (size_t i = 2; i < interval.size(); ++i) {
            cout << interval[i];
            if (i < interval.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]]" << endl;
    }
    
    return 0;
}