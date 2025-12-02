/*
================================================================================
                    DIFFERENCE ARRAY
================================================================================

Difference array enables O(1) range updates and O(n) final array construction.

For range update [l, r] += val:
    diff[l] += val
    diff[r + 1] -= val

Final array = prefix sum of difference array.

Time: O(1) per update, O(n) to build result | Space: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Corporate Flight Bookings (LeetCode 1109)
────────────────────────────────────────────────────
n flights, bookings[i] = [first, last, seats].
Return total seats booked for each flight.

Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Output: [10,55,45,25,25]

Time: O(n + bookings) | Space: O(n)
*/
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n + 2, 0);  // Extra space for r+1
    
    for (auto& booking : bookings) {
        int first = booking[0], last = booking[1], seats = booking[2];
        diff[first] += seats;
        diff[last + 1] -= seats;
    }
    
    // Convert to prefix sum
    vector<int> result(n);
    result[0] = diff[1];
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] + diff[i + 1];
    }
    
    return result;
}


/*
PROBLEM 2: Car Pooling (LeetCode 1094)
──────────────────────────────────────
Check if car with capacity can complete all trips.

trips[i] = [numPassengers, from, to]

Time: O(n + trips) | Space: O(max_distance)
*/
bool carPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> diff(1001, 0);  // Max distance is 1000
    
    for (auto& trip : trips) {
        int passengers = trip[0], from = trip[1], to = trip[2];
        diff[from] += passengers;
        diff[to] -= passengers;  // Passengers leave at 'to'
    }
    
    int current = 0;
    for (int i = 0; i < 1001; i++) {
        current += diff[i];
        if (current > capacity) return false;
    }
    
    return true;
}


/*
PROBLEM 3: Range Addition (LeetCode 370) - Premium
──────────────────────────────────────────────────
Apply multiple range updates: [start, end, val].

Time: O(n + k) where k = number of updates | Space: O(n)
*/
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> diff(length + 1, 0);
    
    for (auto& update : updates) {
        int start = update[0], end = update[1], val = update[2];
        diff[start] += val;
        diff[end + 1] -= val;
    }
    
    vector<int> result(length);
    result[0] = diff[0];
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] + diff[i];
    }
    
    return result;
}


/*
PROBLEM 4: My Calendar III (LeetCode 732)
─────────────────────────────────────────
Track maximum concurrent bookings at any time.

Time: O(n²) naive, O(n log n) with sorting | Space: O(n)
*/
class MyCalendarThree {
    map<int, int> diff;  // Ordered map for time points
    
public:
    int book(int start, int end) {
        diff[start]++;
        diff[end]--;
        
        int maxConcurrent = 0, current = 0;
        for (auto& [time, delta] : diff) {
            current += delta;
            maxConcurrent = max(maxConcurrent, current);
        }
        
        return maxConcurrent;
    }
};


/*
PROBLEM 5: Minimum Number of Arrows to Burst Balloons (LeetCode 452)
────────────────────────────────────────────────────────────────────
Minimum arrows to burst all balloons (intervals).

Note: This is actually greedy, but related to interval problems.

Time: O(n log n) | Space: O(1)
*/
int findMinArrowPoints(vector<vector<int>>& points) {
    if (points.empty()) return 0;
    
    sort(points.begin(), points.end(), [](auto& a, auto& b) {
        return a[1] < b[1];  // Sort by end point
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
PROBLEM 6: Describe the Painting (LeetCode 1943)
────────────────────────────────────────────────
Merge overlapping paint segments by color sum.

Time: O(n log n) | Space: O(n)
*/
vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
    map<int, long long> diff;
    
    for (auto& seg : segments) {
        diff[seg[0]] += seg[2];
        diff[seg[1]] -= seg[2];
    }
    
    vector<vector<long long>> result;
    long long colorSum = 0;
    int prevPoint = -1;
    
    for (auto& [point, delta] : diff) {
        if (colorSum > 0 && prevPoint != -1) {
            result.push_back({prevPoint, point, colorSum});
        }
        colorSum += delta;
        prevPoint = point;
    }
    
    return result;
}


/*
PROBLEM 7: Brightest Position on Street (LeetCode 2021) - Premium
─────────────────────────────────────────────────────────────────
Find position with maximum total light intensity.

Time: O(n log n) | Space: O(n)
*/
int brightestPosition(vector<vector<int>>& lights) {
    map<int, int> diff;
    
    for (auto& light : lights) {
        int pos = light[0], range = light[1];
        diff[pos - range]++;
        diff[pos + range + 1]--;
    }
    
    int maxBrightness = 0, currentBrightness = 0;
    int brightestPos = 0;
    
    for (auto& [pos, delta] : diff) {
        currentBrightness += delta;
        if (currentBrightness > maxBrightness) {
            maxBrightness = currentBrightness;
            brightestPos = pos;
        }
    }
    
    return brightestPos;
}


/*
PROBLEM 8: Shifting Letters II (LeetCode 2381)
──────────────────────────────────────────────
Apply shifts to string ranges.

shift[i] = [start, end, direction]
direction: 0 = backward, 1 = forward

Time: O(n + k) | Space: O(n)
*/
string shiftingLetters(string s, vector<vector<int>>& shifts) {
    int n = s.size();
    vector<int> diff(n + 1, 0);
    
    for (auto& shift : shifts) {
        int start = shift[0], end = shift[1], dir = shift[2];
        int delta = (dir == 1) ? 1 : -1;
        diff[start] += delta;
        diff[end + 1] -= delta;
    }
    
    // Apply shifts
    int cumShift = 0;
    for (int i = 0; i < n; i++) {
        cumShift += diff[i];
        int newChar = ((s[i] - 'a') + cumShift % 26 + 26) % 26;
        s[i] = 'a' + newChar;
    }
    
    return s;
}


/*
PROBLEM 9: Longest Continuous Subarray With Absolute Diff <= Limit (LeetCode 1438)
──────────────────────────────────────────────────────────────────────────────────
Find longest subarray where max - min <= limit.

Note: Uses monotonic deques, not difference array.

Time: O(n) | Space: O(n)
*/
int longestSubarray(vector<int>& nums, int limit) {
    deque<int> maxDeq, minDeq;
    int left = 0, maxLen = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        while (!maxDeq.empty() && nums[maxDeq.back()] < nums[right]) {
            maxDeq.pop_back();
        }
        maxDeq.push_back(right);
        
        while (!minDeq.empty() && nums[minDeq.back()] > nums[right]) {
            minDeq.pop_back();
        }
        minDeq.push_back(right);
        
        while (nums[maxDeq.front()] - nums[minDeq.front()] > limit) {
            if (maxDeq.front() == left) maxDeq.pop_front();
            if (minDeq.front() == left) minDeq.pop_front();
            left++;
        }
        
        maxLen = max(maxLen, right - left + 1);
    }
    
    return maxLen;
}


/*
PROBLEM 10: 2D Range Update (Template)
──────────────────────────────────────
Apply 2D range updates efficiently.

For update (r1, c1) to (r2, c2) += val:
    diff[r1][c1] += val
    diff[r1][c2+1] -= val
    diff[r2+1][c1] -= val
    diff[r2+1][c2+1] += val

Then compute 2D prefix sum.
*/
class RangeUpdate2D {
    vector<vector<int>> diff;
    int m, n;
    
public:
    RangeUpdate2D(int rows, int cols) : m(rows), n(cols) {
        diff.resize(m + 2, vector<int>(n + 2, 0));
    }
    
    void update(int r1, int c1, int r2, int c2, int val) {
        diff[r1][c1] += val;
        diff[r1][c2 + 1] -= val;
        diff[r2 + 1][c1] -= val;
        diff[r2 + 1][c2 + 1] += val;
    }
    
    vector<vector<int>> getResult() {
        vector<vector<int>> result(m, vector<int>(n, 0));
        
        // Row prefix
        for (int i = 0; i < m; i++) {
            for (int j = 1; j < n; j++) {
                diff[i][j] += diff[i][j - 1];
            }
        }
        
        // Column prefix
        for (int j = 0; j < n; j++) {
            for (int i = 1; i < m; i++) {
                diff[i][j] += diff[i - 1][j];
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = diff[i][j];
            }
        }
        
        return result;
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Difference Array ===\n\n";
    
    // Flight Bookings
    vector<vector<int>> bookings = {{1,2,10}, {2,3,20}, {2,5,25}};
    auto seats = corpFlightBookings(bookings, 5);
    cout << "1. Flight bookings: ";
    for (int s : seats) cout << s << " ";
    cout << "\n";
    
    // Car Pooling
    vector<vector<int>> trips = {{2,1,5}, {3,3,7}};
    cout << "2. Car pooling (capacity 4): " 
         << (carPooling(trips, 4) ? "Yes" : "No") << "\n";
    
    // Range Addition
    vector<vector<int>> updates = {{1,3,2}, {2,4,3}, {0,2,-2}};
    auto modified = getModifiedArray(5, updates);
    cout << "3. After range updates: ";
    for (int v : modified) cout << v << " ";
    cout << "\n";
    
    // Shifting Letters
    vector<vector<int>> shifts = {{0,1,0}, {1,2,1}, {0,2,1}};
    cout << "8. Shifted 'abc': " << shiftingLetters("abc", shifts) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

DIFFERENCE ARRAY TEMPLATE:
──────────────────────────
1D Update [l, r] += val:
    diff[l] += val
    diff[r + 1] -= val

2D Update (r1,c1) to (r2,c2) += val:
    diff[r1][c1] += val
    diff[r1][c2+1] -= val
    diff[r2+1][c1] -= val
    diff[r2+1][c2+1] += val

Then compute prefix sum.

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Insight                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Flight Bookings               | Range [first, last] += seats                   |
| Car Pooling                   | +passengers at from, -passengers at to         |
| Calendar III                  | Track overlaps with ordered map                |
| Painting                      | Merge by color sum using events                |
+───────────────────────────────+────────────────────────────────────────────────+

USE CASES:
- Multiple range updates, single query for final state
- Event processing (start/end events)
- Scheduling conflicts
- Brightness/intensity calculations

================================================================================
*/

