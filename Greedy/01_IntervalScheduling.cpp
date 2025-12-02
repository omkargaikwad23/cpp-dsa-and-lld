/*
================================================================================
                    GREEDY - INTERVAL SCHEDULING
================================================================================

Key Insight: Sort by END time for maximizing selections,
             Sort by START time for merging/processing.

Time: O(n log n) for sorting | Space: O(1) or O(n)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Activity Selection / Maximum Meetings (Classic Greedy)
─────────────────────────────────────────────────────────────────
Select maximum number of non-overlapping activities.

Input: start = [1,3,0,5,8,5], end = [2,4,6,7,9,9]
Output: 4 (meetings: [1,2], [3,4], [5,7], [8,9])

Strategy: Sort by END time, greedily pick if start >= last end.

Time: O(n log n) | Space: O(n)
*/
int maxMeetings(vector<int>& start, vector<int>& end) {
    int n = start.size();
    vector<pair<int, int>> meetings;
    
    for (int i = 0; i < n; i++) {
        meetings.push_back({end[i], start[i]});  // {end, start}
    }
    
    sort(meetings.begin(), meetings.end());  // Sort by end time
    
    int count = 0, lastEnd = -1;
    for (auto& [e, s] : meetings) {
        if (s > lastEnd) {  // Can attend
            count++;
            lastEnd = e;
        }
    }
    
    return count;
}


/*
PROBLEM 2: Non-overlapping Intervals (LeetCode 435)
───────────────────────────────────────────────────
Minimum intervals to remove to make rest non-overlapping.

Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1 (remove [1,3])

Strategy: Count max non-overlapping (sort by end), answer = n - count

Time: O(n log n) | Space: O(1)
*/
int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return 0;
    
    // Sort by end time
    sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    
    int count = 1;  // Keep first interval
    int end = intervals[0][1];
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] >= end) {  // Non-overlapping
            count++;
            end = intervals[i][1];
        }
    }
    
    return intervals.size() - count;
}


/*
PROBLEM 3: Minimum Number of Arrows to Burst Balloons (LeetCode 452)
────────────────────────────────────────────────────────────────────
Find minimum arrows to burst all balloons (each arrow at x pops balloons covering x).

Input: points = [[10,16],[2,8],[1,6],[7,12]]
Output: 2

Strategy: Same as activity selection - sort by end, count groups

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
        if (points[i][0] > arrowPos) {  // Need new arrow
            arrows++;
            arrowPos = points[i][1];
        }
    }
    
    return arrows;
}


/*
PROBLEM 4: Merge Intervals (LeetCode 56)
────────────────────────────────────────
Merge all overlapping intervals.

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]

Strategy: Sort by START time, extend end if overlapping

Time: O(n log n) | Space: O(n)
*/
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    
    sort(intervals.begin(), intervals.end());
    
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);
    
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i][0] <= merged.back()[1]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    
    return merged;
}


/*
PROBLEM 5: Insert Interval (LeetCode 57)
────────────────────────────────────────
Insert new interval into sorted non-overlapping intervals.

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Time: O(n) | Space: O(n)
*/
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> result;
    int i = 0, n = intervals.size();
    
    // Add all intervals ending before newInterval starts
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
PROBLEM 6: Video Stitching (LeetCode 1024)
──────────────────────────────────────────
Minimum clips to cover [0, time].

Input: clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], time = 10
Output: 3 ([0,2], [1,9] or [1,5], [5,9] or [8,10])

Strategy: Sort by start, greedily extend furthest reachable

Time: O(n log n) | Space: O(1)
*/
int videoStitching(vector<vector<int>>& clips, int time) {
    sort(clips.begin(), clips.end());
    
    int count = 0, end = 0, furthest = 0, i = 0;
    
    while (end < time) {
        // Find clip starting at or before 'end' that extends furthest
        while (i < clips.size() && clips[i][0] <= end) {
            furthest = max(furthest, clips[i][1]);
            i++;
        }
        
        if (furthest == end) return -1;  // Can't extend
        
        count++;
        end = furthest;
    }
    
    return count;
}


/*
PROBLEM 7: Interval List Intersections (LeetCode 986)
─────────────────────────────────────────────────────
Find intersection of two sorted interval lists.

Input: firstList = [[0,2],[5,10]], secondList = [[1,5],[8,12]]
Output: [[1,2],[5,5],[8,10]]

Time: O(m + n) | Space: O(1)
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
        
        // Advance the one that ends first
        if (A[i][1] < B[j][1]) i++;
        else j++;
    }
    
    return result;
}


/*
PROBLEM 8: Maximum Length of Pair Chain (LeetCode 646)
──────────────────────────────────────────────────────
Find longest chain where (c,d) can follow (a,b) if b < c.

Input: pairs = [[1,2],[2,3],[3,4]]
Output: 2 ([1,2] -> [3,4])

Same as activity selection!

Time: O(n log n) | Space: O(1)
*/
int findLongestChain(vector<vector<int>>& pairs) {
    sort(pairs.begin(), pairs.end(), [](auto& a, auto& b) {
        return a[1] < b[1];
    });
    
    int count = 1, end = pairs[0][1];
    
    for (int i = 1; i < pairs.size(); i++) {
        if (pairs[i][0] > end) {
            count++;
            end = pairs[i][1];
        }
    }
    
    return count;
}


/*
PROBLEM 9: Minimum Number of Taps (LeetCode 1326)
─────────────────────────────────────────────────
Minimum taps to water garden [0, n]. Tap i waters [i-ranges[i], i+ranges[i]].

Input: n = 5, ranges = [3,4,1,1,0,0]
Output: 1 (tap 1 covers [-3, 5])

Same as video stitching with converted intervals!

Time: O(n) | Space: O(n)
*/
int minTaps(int n, vector<int>& ranges) {
    vector<int> maxReach(n + 1, 0);
    
    // maxReach[i] = furthest right we can reach starting from i
    for (int i = 0; i <= n; i++) {
        int left = max(0, i - ranges[i]);
        int right = min(n, i + ranges[i]);
        maxReach[left] = max(maxReach[left], right);
    }
    
    int taps = 0, end = 0, furthest = 0;
    
    for (int i = 0; i <= n; i++) {
        if (i > furthest) return -1;  // Gap
        
        furthest = max(furthest, maxReach[i]);
        
        if (i == end && end < n) {
            taps++;
            end = furthest;
        }
    }
    
    return taps;
}


/*
PROBLEM 10: Maximum Events (LeetCode 1353)
──────────────────────────────────────────
Attend maximum events (each event spans [start, end], takes 1 day).

Input: events = [[1,2],[2,3],[3,4]]
Output: 3

Strategy: Sort by start, use min-heap of end days

Time: O(n log n) | Space: O(n)
*/
int maxEvents(vector<vector<int>>& events) {
    sort(events.begin(), events.end());
    priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap of end days
    
    int i = 0, n = events.size(), day = 0, attended = 0;
    
    while (i < n || !pq.empty()) {
        if (pq.empty()) {
            day = events[i][0];
        }
        
        while (i < n && events[i][0] <= day) {
            pq.push(events[i][1]);
            i++;
        }
        
        while (!pq.empty() && pq.top() < day) {
            pq.pop();  // Remove expired
        }
        
        if (!pq.empty()) {
            pq.pop();
            attended++;
        }
        
        day++;
    }
    
    return attended;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Interval Scheduling ===\n\n";
    
    // 1. Max Meetings
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end = {2, 4, 6, 7, 9, 9};
    cout << "1. Max meetings: " << maxMeetings(start, end) << "\n";
    
    // 2. Non-overlapping Intervals
    vector<vector<int>> intervals = {{1,2},{2,3},{3,4},{1,3}};
    cout << "2. Remove to make non-overlapping: " << eraseOverlapIntervals(intervals) << "\n";
    
    // 3. Min Arrows
    vector<vector<int>> balloons = {{10,16},{2,8},{1,6},{7,12}};
    cout << "3. Min arrows: " << findMinArrowPoints(balloons) << "\n";
    
    // 6. Video Stitching
    vector<vector<int>> clips = {{0,2},{4,6},{8,10},{1,9},{1,5},{5,9}};
    cout << "6. Min clips to cover [0,10]: " << videoStitching(clips, 10) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem Type                  | Sort By                                        |
+───────────────────────────────+────────────────────────────────────────────────+
| Max non-overlapping           | END time (ascending)                           |
| Merge intervals               | START time (ascending)                         |
| Cover range [0, T]            | START time, track furthest reachable           |
| Minimum removals              | END time, count kept = n - answer              |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

