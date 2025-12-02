/*
================================================================================
                    LINE SWEEP - SKYLINE PROBLEMS
================================================================================

Skyline problems involve tracking maximum height while sweeping.
Key data structure: multiset or max-heap to track active heights.

Events: {x-coordinate, height, type (start/end)}
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: The Skyline Problem (LeetCode 218)
─────────────────────────────────────────────
Buildings = [left, right, height]. Return skyline key points.

Input: buildings = [[2,9,10],[3,7,15],[5,12,12],[15,20,10],[19,24,8]]
Output: [[2,10],[3,15],[7,12],[12,0],[15,10],[20,8],[24,0]]

Approach:
1. Create events: {x, -height} for start, {x, height} for end
2. Sort events (negative height ensures start processed before end at same x)
3. Use multiset to track active heights
4. When max height changes, add to result

Time: O(n log n) | Space: O(n)
*/
vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
    vector<pair<int, int>> events;  // {x, height}
    
    for (auto& b : buildings) {
        events.push_back({b[0], -b[2]});  // Start: negative height
        events.push_back({b[1], b[2]});   // End: positive height
    }
    
    // Sort by x; at same x, process starts (negative) before ends (positive)
    // Among starts, taller first (-15 < -10); among ends, shorter first (10 < 15)
    sort(events.begin(), events.end());
    
    multiset<int> activeHeights;
    activeHeights.insert(0);  // Ground level
    
    vector<vector<int>> result;
    int prevMaxHeight = 0;
    
    for (auto& [x, h] : events) {
        if (h < 0) {
            activeHeights.insert(-h);  // Building starts
        } else {
            activeHeights.erase(activeHeights.find(h));  // Building ends
        }
        
        int currMaxHeight = *activeHeights.rbegin();
        
        if (currMaxHeight != prevMaxHeight) {
            result.push_back({x, currMaxHeight});
            prevMaxHeight = currMaxHeight;
        }
    }
    
    return result;
}


/*
PROBLEM 2: Falling Squares (LeetCode 699)
─────────────────────────────────────────
Squares fall onto x-axis. Return heights after each square falls.

Input: positions = [[1,2],[2,3],[6,1]]
Output: [2,5,5]

Approach: For each square, find max height in its range, add its height

Time: O(n²) simple, O(n log n) with segment tree
*/
vector<int> fallingSquares(vector<vector<int>>& positions) {
    vector<pair<pair<int,int>, int>> intervals;  // {{left, right}, height}
    vector<int> result;
    int maxHeight = 0;
    
    for (auto& p : positions) {
        int left = p[0], side = p[1], right = left + side;
        
        // Find max height this square will land on
        int base = 0;
        for (auto& [range, h] : intervals) {
            // Check overlap
            if (range.first < right && range.second > left) {
                base = max(base, h);
            }
        }
        
        int newHeight = base + side;
        intervals.push_back({{left, right}, newHeight});
        
        maxHeight = max(maxHeight, newHeight);
        result.push_back(maxHeight);
    }
    
    return result;
}


/*
PROBLEM 3: Rectangle Area II (LeetCode 850)
───────────────────────────────────────────
Find total area covered by rectangles (count overlapping area once).

Input: rectangles = [[0,0,2,2],[1,0,2,3],[1,0,3,1]]
Output: 6

Approach: Coordinate compression + line sweep

Time: O(n² log n) | Space: O(n)
*/
int rectangleArea(vector<vector<int>>& rectangles) {
    const int MOD = 1e9 + 7;
    
    // Collect all x-coordinates
    set<int> xSet;
    for (auto& r : rectangles) {
        xSet.insert(r[0]);
        xSet.insert(r[2]);
    }
    vector<int> xs(xSet.begin(), xSet.end());
    
    // Create events: {y, type, x1, x2}
    // type: 1 = bottom edge (entering), -1 = top edge (leaving)
    vector<tuple<int, int, int, int>> events;
    for (auto& r : rectangles) {
        events.push_back({r[1], 1, r[0], r[2]});   // Bottom
        events.push_back({r[3], -1, r[0], r[2]});  // Top
    }
    sort(events.begin(), events.end());
    
    // Count array for each x segment
    int n = xs.size();
    vector<int> count(n, 0);  // count[i] = # rectangles covering segment [xs[i], xs[i+1]]
    
    long long area = 0;
    int prevY = 0;
    
    for (auto& [y, type, x1, x2] : events) {
        // Calculate width covered at previous y level
        long long width = 0;
        for (int i = 0; i + 1 < n; i++) {
            if (count[i] > 0) {
                width += xs[i + 1] - xs[i];
            }
        }
        
        // Add area
        area = (area + width * (y - prevY)) % MOD;
        prevY = y;
        
        // Update counts for x segments
        int i1 = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
        int i2 = lower_bound(xs.begin(), xs.end(), x2) - xs.begin();
        for (int i = i1; i < i2; i++) {
            count[i] += type;
        }
    }
    
    return area;
}


/*
PROBLEM 4: Perfect Rectangle (LeetCode 391)
───────────────────────────────────────────
Check if rectangles exactly cover a rectangular region without overlap.

Input: rectangles = [[1,1,3,3],[3,1,4,2],[3,2,4,4],[1,3,2,4],[2,3,3,4]]
Output: true

Approach: 
1. Check area sum equals bounding rectangle area
2. Check corners: each corner should appear odd times only at 4 outer corners

Time: O(n) | Space: O(n)
*/
bool isRectangleCover(vector<vector<int>>& rectangles) {
    set<pair<int, int>> corners;
    long long area = 0;
    int minX = INT_MAX, minY = INT_MAX, maxX = INT_MIN, maxY = INT_MIN;
    
    for (auto& r : rectangles) {
        minX = min(minX, r[0]);
        minY = min(minY, r[1]);
        maxX = max(maxX, r[2]);
        maxY = max(maxY, r[3]);
        
        area += (long long)(r[2] - r[0]) * (r[3] - r[1]);
        
        // Toggle corners (XOR logic using set)
        vector<pair<int, int>> pts = {{r[0], r[1]}, {r[0], r[3]}, 
                                       {r[2], r[1]}, {r[2], r[3]}};
        for (auto& p : pts) {
            if (corners.count(p)) corners.erase(p);
            else corners.insert(p);
        }
    }
    
    // Check area
    if (area != (long long)(maxX - minX) * (maxY - minY)) return false;
    
    // Check corners - should only have 4 corners of bounding rectangle
    if (corners.size() != 4) return false;
    if (!corners.count({minX, minY}) || !corners.count({minX, maxY}) ||
        !corners.count({maxX, minY}) || !corners.count({maxX, maxY})) {
        return false;
    }
    
    return true;
}


/*
PROBLEM 5: Maximum Building Height (LeetCode 1840)
──────────────────────────────────────────────────
Buildings with height restrictions. Adjacent buildings differ by at most 1.
Find maximum possible height.

Input: n = 5, restrictions = [[2,1],[4,1]]
Output: 2

Approach: Two passes to propagate constraints, then find max between restrictions

Time: O(m log m) | Space: O(m)
*/
int maxBuilding(int n, vector<vector<int>>& restrictions) {
    restrictions.push_back({1, 0});  // Building 1 has height 0
    restrictions.push_back({n, n - 1});  // Max possible at building n
    
    sort(restrictions.begin(), restrictions.end());
    
    // Left to right pass: propagate constraints
    for (int i = 1; i < restrictions.size(); i++) {
        int dist = restrictions[i][0] - restrictions[i - 1][0];
        restrictions[i][1] = min(restrictions[i][1], 
                                  restrictions[i - 1][1] + dist);
    }
    
    // Right to left pass
    for (int i = restrictions.size() - 2; i >= 0; i--) {
        int dist = restrictions[i + 1][0] - restrictions[i][0];
        restrictions[i][1] = min(restrictions[i][1], 
                                  restrictions[i + 1][1] + dist);
    }
    
    // Find max height between consecutive restrictions
    int maxHeight = 0;
    for (int i = 1; i < restrictions.size(); i++) {
        int x1 = restrictions[i - 1][0], h1 = restrictions[i - 1][1];
        int x2 = restrictions[i][0], h2 = restrictions[i][1];
        
        // Max height in between: go up from h1, meet going down from h2
        // h1 + k = h2 + (x2 - x1 - k) => k = (h2 - h1 + x2 - x1) / 2
        int peak = (h1 + h2 + x2 - x1) / 2;
        maxHeight = max(maxHeight, peak);
    }
    
    return maxHeight;
}


/*
PROBLEM 6: Amount of New Area Painted Each Day (LeetCode 2158 - Premium)
────────────────────────────────────────────────────────────────────────
Each day paint [start, end). Return new area painted each day.

Input: paint = [[1,4],[4,7],[5,8]]
Output: [3,3,1]

Approach: Use ordered set to track painted intervals

Time: O(n * painted) or O(n log n) with interval merging
*/
vector<int> amountPainted(vector<vector<int>>& paint) {
    map<int, int> painted;  // start -> end of painted intervals
    vector<int> result;
    
    for (auto& p : paint) {
        int start = p[0], end = p[1], area = 0;
        
        auto it = painted.upper_bound(start);
        if (it != painted.begin()) {
            --it;
            if (it->second >= start) {
                // Overlaps with previous interval
                start = max(start, it->second);
            } else {
                ++it;
            }
        }
        
        // Merge overlapping intervals and count new area
        while (it != painted.end() && it->first < end) {
            if (it->first > start) {
                area += it->first - start;
            }
            start = max(start, it->second);
            it = painted.erase(it);
        }
        
        if (start < end) {
            area += end - start;
        }
        
        // Find merge boundaries
        auto left = painted.upper_bound(p[0]);
        int newStart = p[0], newEnd = end;
        
        if (left != painted.begin()) {
            --left;
            if (left->second >= p[0]) {
                newStart = left->first;
                newEnd = max(newEnd, left->second);
                painted.erase(left);
            }
        }
        
        painted[newStart] = newEnd;
        result.push_back(area);
    }
    
    return result;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Skyline Problems ===\n\n";
    
    // 1. The Skyline Problem
    vector<vector<int>> buildings = {{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    vector<vector<int>> skyline = getSkyline(buildings);
    cout << "1. Skyline: ";
    for (auto& p : skyline) cout << "[" << p[0] << "," << p[1] << "] ";
    cout << "\n";
    
    // 2. Falling Squares
    vector<vector<int>> squares = {{1,2},{2,3},{6,1}};
    vector<int> heights = fallingSquares(squares);
    cout << "2. Falling squares: ";
    for (int h : heights) cout << h << " ";
    cout << "\n";
    
    // 4. Perfect Rectangle
    vector<vector<int>> rects = {{1,1,3,3},{3,1,4,2},{3,2,4,4},{1,3,2,4},{2,3,3,4}};
    cout << "4. Perfect rectangle: " << (isRectangleCover(rects) ? "true" : "false") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

Skyline Pattern:
1. Create events at x-coordinates (start/end of rectangles)
2. Use multiset to track active heights
3. Output when maximum height changes

Key techniques:
- Negative heights for starts (sort before ends at same x)
- Multiset for O(log n) insert/delete and O(1) max
- Coordinate compression for sparse coordinates

================================================================================
*/

