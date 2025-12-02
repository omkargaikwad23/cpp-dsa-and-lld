/*
================================================================================
                    LINE SWEEP - DIFFERENCE ARRAY
================================================================================

Difference Array is a technique for efficient range update operations.
Instead of updating every element in range, we mark start (+val) and end (-val).

For range [l, r] add value v:
  diff[l] += v
  diff[r + 1] -= v

Prefix sum of diff gives actual values.

Time: O(1) per update, O(n) to reconstruct
Space: O(n)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Range Addition (LeetCode 370 - Premium)
──────────────────────────────────────────────────
Apply multiple range updates, return final array.

Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
Output: [-2,0,3,5,3]

Updates: [1,3,2] means add 2 to indices 1-3

Time: O(n + k) | Space: O(n)
*/
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
    vector<int> diff(length + 1, 0);
    
    for (auto& update : updates) {
        int start = update[0], end = update[1], val = update[2];
        diff[start] += val;
        diff[end + 1] -= val;
    }
    
    // Prefix sum to get actual values
    vector<int> result(length);
    result[0] = diff[0];
    for (int i = 1; i < length; i++) {
        result[i] = result[i - 1] + diff[i];
    }
    
    return result;
}


/*
PROBLEM 2: Corporate Flight Bookings (LeetCode 1109)
────────────────────────────────────────────────────
n flights, bookings[i] = [first, last, seats].
Return seats reserved on each flight.

Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
Output: [10,55,45,25,25]

Time: O(n + m) | Space: O(n)
*/
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> diff(n + 2, 0);  // 1-indexed
    
    for (auto& b : bookings) {
        int first = b[0], last = b[1], seats = b[2];
        diff[first] += seats;
        diff[last + 1] -= seats;
    }
    
    vector<int> result(n);
    result[0] = diff[1];
    for (int i = 1; i < n; i++) {
        result[i] = result[i - 1] + diff[i + 1];
    }
    
    return result;
}


/*
PROBLEM 3: Car Pooling (LeetCode 1094)
──────────────────────────────────────
Can car with capacity pick up and drop all passengers?

trips[i] = [numPassengers, from, to]
Input: trips = [[2,1,5],[3,3,7]], capacity = 4
Output: false

Time: O(n + max_location) | Space: O(max_location)
*/
bool carPooling(vector<vector<int>>& trips, int capacity) {
    vector<int> diff(1001, 0);  // Locations up to 1000
    
    for (auto& trip : trips) {
        int passengers = trip[0], from = trip[1], to = trip[2];
        diff[from] += passengers;
        diff[to] -= passengers;  // Note: to is exclusive (passenger gets off)
    }
    
    int current = 0;
    for (int i = 0; i < 1001; i++) {
        current += diff[i];
        if (current > capacity) return false;
    }
    
    return true;
}

// Alternative using map (for sparse locations)
bool carPoolingMap(vector<vector<int>>& trips, int capacity) {
    map<int, int> timeline;
    
    for (auto& trip : trips) {
        timeline[trip[1]] += trip[0];  // Pick up
        timeline[trip[2]] -= trip[0];  // Drop off
    }
    
    int passengers = 0;
    for (auto& [location, delta] : timeline) {
        passengers += delta;
        if (passengers > capacity) return false;
    }
    
    return true;
}


/*
PROBLEM 4: Brightest Position on Street (LeetCode 2021 - Premium)
─────────────────────────────────────────────────────────────────
Each light at position[i] illuminates [position[i] - range[i], position[i] + range[i]].
Find brightest position (smallest if tie).

Input: lights = [[-3,2],[1,2],[3,3]]
Output: -1

Time: O(n log n) | Space: O(n)
*/
int brightestPosition(vector<vector<int>>& lights) {
    map<int, int> diff;
    
    for (auto& light : lights) {
        int pos = light[0], range = light[1];
        diff[pos - range]++;
        diff[pos + range + 1]--;
    }
    
    int brightness = 0, maxBrightness = 0, result = 0;
    
    for (auto& [pos, delta] : diff) {
        brightness += delta;
        if (brightness > maxBrightness) {
            maxBrightness = brightness;
            result = pos;
        }
    }
    
    return result;
}


/*
PROBLEM 5: Maximum Population Year (LeetCode 1854)
──────────────────────────────────────────────────
Find year with maximum population alive.

Input: logs = [[1993,1999],[2000,2010]]
Output: 1993

Time: O(n + range) | Space: O(range)
*/
int maximumPopulation(vector<vector<int>>& logs) {
    vector<int> diff(101, 0);  // Years 1950-2050 → indices 0-100
    
    for (auto& log : logs) {
        diff[log[0] - 1950]++;
        diff[log[1] - 1950]--;  // Death year is exclusive
    }
    
    int maxPop = 0, maxYear = 1950, population = 0;
    
    for (int i = 0; i < 101; i++) {
        population += diff[i];
        if (population > maxPop) {
            maxPop = population;
            maxYear = 1950 + i;
        }
    }
    
    return maxYear;
}


/*
PROBLEM 6: Shifting Letters II (LeetCode 2381)
──────────────────────────────────────────────
Apply shifts to string. shifts[i] = [start, end, direction]
direction: 1 = forward, 0 = backward

Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
Output: "ace"

Time: O(n + k) | Space: O(n)
*/
string shiftingLetters(string s, vector<vector<int>>& shifts) {
    int n = s.size();
    vector<int> diff(n + 1, 0);
    
    for (auto& shift : shifts) {
        int start = shift[0], end = shift[1], dir = shift[2];
        int val = (dir == 1) ? 1 : -1;
        diff[start] += val;
        diff[end + 1] -= val;
    }
    
    int shift = 0;
    for (int i = 0; i < n; i++) {
        shift += diff[i];
        int newChar = ((s[i] - 'a') + shift % 26 + 26) % 26;
        s[i] = 'a' + newChar;
    }
    
    return s;
}


/*
PROBLEM 7: Describe the Painting (LeetCode 1943)
────────────────────────────────────────────────
Segments with colors, find non-overlapping segments with summed colors.

Input: segments = [[1,4,5],[4,7,7],[1,7,9]]
Output: [[1,4,14],[4,7,16]]

Time: O(n log n) | Space: O(n)
*/
vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
    map<int, long long> diff;
    
    for (auto& seg : segments) {
        diff[seg[0]] += seg[2];
        diff[seg[1]] -= seg[2];
    }
    
    vector<vector<long long>> result;
    long long color = 0;
    int prevPos = -1;
    
    for (auto& [pos, delta] : diff) {
        if (color > 0 && prevPos != -1) {
            result.push_back({prevPos, pos, color});
        }
        color += delta;
        prevPos = pos;
    }
    
    return result;
}


/*
PROBLEM 8: Number of Flowers in Full Bloom (LeetCode 2251)
──────────────────────────────────────────────────────────
flowers[i] = [start, end], for each person arrival time, count blooming flowers.

Input: flowers = [[1,6],[3,7],[9,12],[4,13]], persons = [2,3,7,11]
Output: [1,2,2,2]

Approach: Sort events and people, sweep together

Time: O((n + m) log(n + m)) | Space: O(n)
*/
vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& persons) {
    map<int, int> diff;
    
    for (auto& f : flowers) {
        diff[f[0]]++;
        diff[f[1] + 1]--;
    }
    
    // Build prefix sum
    vector<pair<int, int>> prefix;  // {time, count}
    int count = 0;
    for (auto& [time, delta] : diff) {
        count += delta;
        prefix.push_back({time, count});
    }
    
    vector<int> result;
    for (int p : persons) {
        // Binary search for largest time <= p
        auto it = upper_bound(prefix.begin(), prefix.end(), make_pair(p, INT_MAX));
        if (it == prefix.begin()) {
            result.push_back(0);
        } else {
            --it;
            result.push_back(it->second);
        }
    }
    
    return result;
}


/*
PROBLEM 9: My Calendar III (using Difference Array approach)
────────────────────────────────────────────────────────────
Track maximum overlapping bookings at any time.

Time: O(n) per book | Space: O(n)
*/
class MyCalendarThree {
    map<int, int> timeline;
    
public:
    int book(int start, int end) {
        timeline[start]++;
        timeline[end]--;
        
        int ongoing = 0, maxOverlap = 0;
        for (auto& [time, delta] : timeline) {
            ongoing += delta;
            maxOverlap = max(maxOverlap, ongoing);
        }
        
        return maxOverlap;
    }
};


/*
PROBLEM 10: Points Covered by Intervals
───────────────────────────────────────
Given intervals and points, count how many intervals cover each point.

Time: O(n log n + m log m) | Space: O(n + m)
*/
vector<int> pointsCoveredByIntervals(vector<vector<int>>& intervals, vector<int>& points) {
    map<int, int> diff;
    
    for (auto& interval : intervals) {
        diff[interval[0]]++;
        diff[interval[1] + 1]--;
    }
    
    // Build prefix events
    vector<pair<int, int>> events;
    int count = 0;
    for (auto& [pos, delta] : diff) {
        count += delta;
        events.push_back({pos, count});
    }
    
    vector<int> result;
    for (int p : points) {
        auto it = upper_bound(events.begin(), events.end(), make_pair(p, INT_MAX));
        if (it == events.begin()) {
            result.push_back(0);
        } else {
            result.push_back(prev(it)->second);
        }
    }
    
    return result;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Difference Array Problems ===\n\n";
    
    // 2. Corporate Flight Bookings
    vector<vector<int>> bookings = {{1,2,10},{2,3,20},{2,5,25}};
    vector<int> seats = corpFlightBookings(bookings, 5);
    cout << "2. Flight seats: ";
    for (int s : seats) cout << s << " ";
    cout << "\n";
    
    // 3. Car Pooling
    vector<vector<int>> trips = {{2,1,5},{3,3,7}};
    cout << "3. Car pooling (cap=4): " << (carPooling(trips, 4) ? "true" : "false") << "\n";
    cout << "   Car pooling (cap=5): " << (carPooling(trips, 5) ? "true" : "false") << "\n";
    
    // 5. Maximum Population Year
    vector<vector<int>> logs = {{1993,1999},{2000,2010}};
    cout << "5. Max population year: " << maximumPopulation(logs) << "\n";
    
    // 6. Shifting Letters II
    vector<vector<int>> shifts = {{0,1,0},{1,2,1},{0,2,1}};
    cout << "6. Shifted 'abc': " << shiftingLetters("abc", shifts) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

Difference Array Pattern:
1. diff[start] += value
2. diff[end + 1] -= value
3. Prefix sum gives actual values

When to use:
- Multiple range update queries
- Need final state after all updates
- Counting overlaps at positions

Variants:
- Fixed array: When range is small and known
- Map-based: When range is large or sparse
- Combined with binary search: For point queries after building prefix

================================================================================
*/

