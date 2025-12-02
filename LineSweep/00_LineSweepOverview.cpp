/*
================================================================================
                      LINE SWEEP ALGORITHM - OVERVIEW
================================================================================

Line Sweep (or Sweep Line) is a technique where we process events in sorted
order by "sweeping" across one dimension (usually x-axis or time).

Key Idea:
- Convert problem into events (start/end points)
- Sort events by position/time
- Process events left-to-right, maintaining state

Time: Usually O(n log n) for sorting
Space: O(n) for storing events

================================================================================
                           PATTERN CLASSIFICATION
================================================================================

1. INTERVAL PROBLEMS (1D)
   ──────────────────────
   Problems involving intervals on a line.
   
   Events: {position, type (start/end)}
   
   Problems:
   - Meeting Rooms (can attend all?)
   - Meeting Rooms II (min rooms needed)
   - Merge Intervals
   - Insert Interval
   - Maximum Overlapping Intervals
   - Minimum Platforms (trains)
   
   Template:
   vector<pair<int, int>> events;  // {position, +1 for start, -1 for end}
   for (auto& interval : intervals) {
       events.push_back({interval[0], 1});   // Start
       events.push_back({interval[1], -1});  // End
   }
   sort(events.begin(), events.end());
   
   int active = 0, maxActive = 0;
   for (auto& [pos, type] : events) {
       active += type;
       maxActive = max(maxActive, active);
   }

2. DIFFERENCE ARRAY (Range Updates)
   ─────────────────────────────────
   Efficient range addition operations.
   
   For adding val to range [l, r]:
   diff[l] += val;
   diff[r + 1] -= val;
   
   Problems:
   - Corporate Flight Bookings
   - Car Pooling
   - Range Addition
   - Brightest Position on Street
   
   Template:
   vector<int> diff(n + 1, 0);
   for (auto& [start, end, val] : updates) {
       diff[start] += val;
       diff[end + 1] -= val;
   }
   // Prefix sum to get actual values
   for (int i = 1; i < n; i++) {
       diff[i] += diff[i - 1];
   }

3. COORDINATE COMPRESSION + SWEEP
   ───────────────────────────────
   When coordinates are sparse, compress them first.
   
   Problems:
   - Rectangle Area (union of rectangles)
   - Number of Rectangles Containing Each Point
   - Count Integers in Intervals
   
   Template:
   // Collect all unique x-coordinates
   set<int> xCoords;
   for (auto& rect : rectangles) {
       xCoords.insert(rect.x1);
       xCoords.insert(rect.x2);
   }
   // Map to compressed indices
   map<int, int> compress;
   int idx = 0;
   for (int x : xCoords) compress[x] = idx++;

4. SKYLINE PROBLEMS (2D with Heights)
   ───────────────────────────────────
   Track maximum height as we sweep.
   
   Events: {x, type, height}
   Use max-heap or multiset to track active heights.
   
   Problems:
   - The Skyline Problem
   - Falling Squares
   - Perfect Rectangle
   
   Template:
   vector<tuple<int, int, int>> events;  // {x, type, height}
   multiset<int> activeHeights;
   activeHeights.insert(0);  // Ground level
   
   for (auto& [x, type, h] : events) {
       if (type == START) activeHeights.insert(h);
       else activeHeights.erase(activeHeights.find(h));
       
       int maxHeight = *activeHeights.rbegin();
       // Process change in max height
   }

5. CALENDAR / BOOKING PROBLEMS
   ────────────────────────────
   Track overlapping bookings/events.
   
   Problems:
   - My Calendar I, II, III
   - Employee Free Time
   - Meeting Scheduler
   
   Using ordered map:
   map<int, int> timeline;  // position -> delta
   timeline[start]++;
   timeline[end]--;

================================================================================
                           KEY INSIGHTS
================================================================================

1. WHEN TO USE LINE SWEEP:
   - Intervals that can overlap
   - "Maximum at any point" questions
   - Range update queries
   - 2D geometric problems (sweep one dimension)

2. EVENT ORDERING:
   - Usually sort by position
   - Tie-breaking matters! (start before end, or end before start?)
   - For counting overlaps: process starts before ends at same point

3. DATA STRUCTURES:
   - Simple counter: For counting overlaps
   - Multiset/Heap: For tracking active elements with values
   - Segment Tree: For range queries during sweep
   - Difference Array: For range additions

4. COMPLEXITY:
   - Sorting events: O(n log n)
   - Processing events: O(n) to O(n log n) depending on DS

================================================================================
                           FILE ORGANIZATION
================================================================================

01_IntervalProblems.cpp    - Meeting rooms, merge intervals, overlaps
02_DifferenceArray.cpp     - Range updates, flight bookings, car pooling
03_SkylineProblems.cpp     - Skyline, falling squares, max height tracking
04_CalendarProblems.cpp    - My Calendar series, booking systems
05_GeometricSweep.cpp      - Rectangle area, 2D problems

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Quick reference - see individual files for detailed implementations

int main() {
    cout << "=== Line Sweep Algorithm Patterns ===" << endl;
    cout << "See individual files for detailed implementations." << endl;
    return 0;
}

