/*
================================================================================
                    LINE SWEEP - INTERVAL PROBLEMS
================================================================================

Core technique: Convert intervals to events, sweep left to right.

Event types:
- START (+1): Interval begins
- END (-1): Interval ends

Time: O(n log n) | Space: O(n)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Meeting Rooms (LeetCode 252 - Premium)
─────────────────────────────────────────────────
Can a person attend all meetings?

Input: intervals = [[0,30],[5,10],[15,20]]
Output: false

Approach: Check if any intervals overlap (sort by start, check adjacent)

Time: O(n log n) | Space: O(1)
*/
bool canAttendMeetings(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] < intervals[i - 1][1]) {
            return false;  // Overlap found
        }
    }
    return true;
}


/*
PROBLEM 2: Meeting Rooms II (LeetCode 253 - Premium)
────────────────────────────────────────────────────
Find minimum number of conference rooms required.

Input: intervals = [[0,30],[5,10],[15,20]]
Output: 2

Approach: Line sweep - count overlapping intervals at any point

Time: O(n log n) | Space: O(n)
*/
int minMeetingRooms(vector<vector<int>>& intervals) {
    map<int, int> timeline;
    for (auto& interval : intervals) {
        timeline[interval[0]]++;
        timeline[interval[1]]--;
    }
    
    int rooms = 0, maxRooms = 0;
    for (auto& [time, count] : timeline) {
        rooms += count;
        maxRooms = max(maxRooms, rooms);
    }
    return maxRooms;
}

// Alternative using min-heap (track end times)
int minMeetingRoomsHeap(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    sort(intervals.begin(), intervals.end());
    priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap of end times
    
    for (auto& interval : intervals) {
        // If earliest ending meeting ends before current starts, reuse room
        if (!pq.empty() && pq.top() <= interval[0]) {
            pq.pop();
        }
        pq.push(interval[1]);
    }
    
    return pq.size();
}


/*
PROBLEM 3: Merge Intervals (LeetCode 56)
────────────────────────────────────────
Merge all overlapping intervals.

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]

Time: O(n log n) | Space: O(n)
*/
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= merged.back()[1]) {
            // Overlapping - extend the end
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}


/*
PROBLEM 4: Insert Interval (LeetCode 57)
────────────────────────────────────────
Insert new interval and merge if necessary.

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Time: O(n) | Space: O(n)
*/
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> result;
    int i = 0, n = intervals.size();
    
    // Add all intervals that end before newInterval starts
    while (i < n && intervals[i][1] < newInterval[0]) {
        result.push_back(intervals[i++]);
    }
    
    // Merge overlapping intervals
    while (i < n && intervals[i][0] <= newInterval[1]) {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push_back(newInterval);
    
    // Add remaining intervals
    while (i < n) {
        result.push_back(intervals[i++]);
    }
    
    return result;
}


/*
PROBLEM 5: Interval List Intersections (LeetCode 986)
─────────────────────────────────────────────────────
Find intersection of two sorted interval lists.

Input: firstList = [[0,2],[5,10]], secondList = [[1,5],[8,12]]
Output: [[1,2],[5,5],[8,10]]

Time: O(m + n) | Space: O(1) excluding output
*/
vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> result;
    int i = 0, j = 0;
    
    while (i < A.size() && j < B.size()) {
        int lo = max(A[i][0], B[j][0]);
        int hi = min(A[i][1], B[j][1]);
        
        if (lo <= hi) {
            result.push_back({lo, hi});
        }
        
        // Move pointer for interval that ends first
        if (A[i][1] < B[j][1]) i++;
        else j++;
    }
    
    return result;
}


/*
PROBLEM 6: Non-overlapping Intervals (LeetCode 435)
───────────────────────────────────────────────────
Find minimum intervals to remove to make rest non-overlapping.

Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1 (remove [1,3])

Approach: Greedy - keep interval that ends earliest

Time: O(n log n) | Space: O(1)
*/
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    // Sort by end time
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    
    int count = 0, prevEnd = intervals[0][1];
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] < prevEnd) {
            count++;  // Overlapping, must remove
        } else {
            prevEnd = intervals[i][1];
        }
    }
    
    return count;
}


/*
PROBLEM 7: Minimum Number of Arrows to Burst Balloons (LeetCode 452)
────────────────────────────────────────────────────────────────────
Find minimum arrows to burst all balloons (intervals on x-axis).

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2

Approach: Sort by end, shoot arrow at end of first unpopped balloon

Time: O(n log n) | Space: O(1)
*/
int findMinArrowPoints(vector<vector<int>>& points) {
    if (points.empty()) return 0;
    
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    
    int arrows = 1;
    int arrowPos = points[0][1];
    
    for (int i = 1; i < points.size(); i++) {
        if (points[i][0] > arrowPos) {
            arrows++;
            arrowPos = points[i][1];
        }
    }
    
    return arrows;
}


/*
PROBLEM 8: Maximum Number of Events (LeetCode 1353)
───────────────────────────────────────────────────
Attend maximum events (each event takes 1 day, can attend on any day in range).

Input: events = [[1,2],[2,3],[3,4]]
Output: 3 (attend each on different days)

Approach: Sort by start, use min-heap of end times

Time: O(n log n) | Space: O(n)
*/
int maxEvents(vector<vector<int>>& events) {
    sort(events.begin(), events.end());
    priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap of end days
    
    int i = 0, n = events.size(), day = 0, attended = 0;
    
    while (i < n || !pq.empty()) {
        if (pq.empty()) {
            day = events[i][0];  // Jump to next event start
        }
        
        // Add all events starting on current day
        while (i < n && events[i][0] <= day) {
            pq.push(events[i][1]);
            i++;
        }
        
        // Remove expired events
        while (!pq.empty() && pq.top() < day) {
            pq.pop();
        }
        
        // Attend event with earliest deadline
        if (!pq.empty()) {
            pq.pop();
            attended++;
        }
        
        day++;
    }
    
    return attended;
}


/*
PROBLEM 9: Remove Covered Intervals (LeetCode 1288)
───────────────────────────────────────────────────
Remove intervals that are covered by another.

Input: intervals = [[1,4],[3,6],[2,8]]
Output: 2 ([1,4] is not covered, [3,6] is covered by [2,8])

Time: O(n log n) | Space: O(1)
*/
int removeCoveredIntervals(vector<vector<int>>& intervals) {
    // Sort by start ascending, then by end descending
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];  // Longer interval first
    });
    
    int count = 0, prevEnd = 0;
    
    for (auto& interval : intervals) {
        if (interval[1] > prevEnd) {
            count++;
            prevEnd = interval[1];
        }
        // Else: covered by previous (starts same/later, ends earlier)
    }
    
    return count;
}


/*
PROBLEM 10: Minimum Platforms (Train Station)
─────────────────────────────────────────────
Find minimum platforms needed at a station.

Input: arrival = [900,940,950,1100,1500,1800]
       departure = [910,1200,1120,1130,1900,2000]
Output: 3

Time: O(n log n) | Space: O(n)
*/
int minPlatforms(vector<int>& arrival, vector<int>& departure) {
    vector<pair<int, int>> events;
    
    for (int i = 0; i < arrival.size(); i++) {
        events.push_back({arrival[i], 1});     // Arrival
        events.push_back({departure[i], -1});  // Departure
    }
    
    // Sort by time; departures before arrivals at same time
    sort(events.begin(), events.end(), [](auto& a, auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second;
    });
    
    int platforms = 0, maxPlatforms = 0;
    for (auto& [time, type] : events) {
        platforms += type;
        maxPlatforms = max(maxPlatforms, platforms);
    }
    
    return maxPlatforms;
}


/*
PROBLEM 11: Employee Free Time (LeetCode 759 - Premium)
───────────────────────────────────────────────────────
Find common free time intervals for all employees.

Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]] (common free time)

Time: O(n log n) | Space: O(n)
*/
vector<vector<int>> employeeFreeTime(vector<vector<vector<int>>>& schedule) {
    vector<vector<int>> allIntervals;
    for (auto& employee : schedule) {
        for (auto& interval : employee) {
            allIntervals.push_back(interval);
        }
    }
    
    sort(allIntervals.begin(), allIntervals.end());
    
    vector<vector<int>> freeTime;
    int prevEnd = allIntervals[0][1];
    
    for (int i = 1; i < allIntervals.size(); i++) {
        if (allIntervals[i][0] > prevEnd) {
            freeTime.push_back({prevEnd, allIntervals[i][0]});
        }
        prevEnd = max(prevEnd, allIntervals[i][1]);
    }
    
    return freeTime;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Line Sweep - Interval Problems ===\n\n";
    
    // 2. Meeting Rooms II
    vector<vector<int>> meetings = {{0,30},{5,10},{15,20}};
    cout << "2. Min meeting rooms: " << minMeetingRooms(meetings) << "\n";
    
    // 3. Merge Intervals
    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> merged = merge(intervals);
    cout << "3. Merged intervals: ";
    for (auto& i : merged) cout << "[" << i[0] << "," << i[1] << "] ";
    cout << "\n";
    
    // 6. Non-overlapping Intervals
    vector<vector<int>> overlapping = {{1,2},{2,3},{3,4},{1,3}};
    cout << "6. Intervals to remove: " << eraseOverlapIntervals(overlapping) << "\n";
    
    // 7. Min Arrows
    vector<vector<int>> balloons = {{10,16},{2,8},{1,6},{7,12}};
    cout << "7. Min arrows: " << findMinArrowPoints(balloons) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Insight                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Meeting Rooms I               | Check adjacent after sorting by start         |
| Meeting Rooms II              | Line sweep or min-heap of end times           |
| Merge Intervals               | Sort by start, extend end if overlap          |
| Insert Interval               | Three phases: before, merge, after            |
| Interval Intersection         | Two pointers, advance smaller end             |
| Non-overlapping               | Greedy: keep earliest ending interval         |
| Min Arrows                    | Same as non-overlapping, sort by end          |
| Max Events                    | Sort by start, heap of ends, attend earliest  |
| Remove Covered                | Sort by start ASC, end DESC                   |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

