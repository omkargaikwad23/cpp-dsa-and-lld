/*
================================================================================
                    LINE SWEEP - GEOMETRIC PROBLEMS
================================================================================

Geometric sweep line problems in 2D plane.
Sweep along one axis while maintaining state for the other axis.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Maximum Number of Points from Grid Queries (LeetCode 2503)
─────────────────────────────────────────────────────────────────────
For each query, start from (0,0), count reachable cells with value < query.

Approach: Sort queries, use BFS/priority queue to expand reachable cells

Time: O(mn log(mn) + k log k) | Space: O(mn + k)
*/
vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
    int m = grid.size(), n = grid[0].size();
    int k = queries.size();
    
    // Sort queries with original indices
    vector<pair<int, int>> sortedQ(k);
    for (int i = 0; i < k; i++) {
        sortedQ[i] = {queries[i], i};
    }
    sort(sortedQ.begin(), sortedQ.end());
    
    // Min-heap: {value, row, col}
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    pq.push({grid[0][0], 0, 0});
    
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    visited[0][0] = true;
    
    int dirs[] = {0, 1, 0, -1, 0};
    int count = 0;
    vector<int> result(k);
    
    for (auto& [q, idx] : sortedQ) {
        // Expand to all cells with value < q
        while (!pq.empty() && get<0>(pq.top()) < q) {
            auto [val, r, c] = pq.top();
            pq.pop();
            count++;
            
            for (int d = 0; d < 4; d++) {
                int nr = r + dirs[d], nc = c + dirs[d + 1];
                if (nr >= 0 && nr < m && nc >= 0 && nc < n && !visited[nr][nc]) {
                    visited[nr][nc] = true;
                    pq.push({grid[nr][nc], nr, nc});
                }
            }
        }
        result[idx] = count;
    }
    
    return result;
}


/*
PROBLEM 2: Count Lattice Points Inside a Circle (LeetCode 2249)
───────────────────────────────────────────────────────────────
Count integer points inside or on at least one circle.

Input: circles = [[2,2,1]]
Output: 5

Time: O(n * r²) | Space: O(points)
*/
int countLatticePoints(vector<vector<int>>& circles) {
    set<pair<int, int>> points;
    
    for (auto& c : circles) {
        int x = c[0], y = c[1], r = c[2];
        
        for (int i = x - r; i <= x + r; i++) {
            for (int j = y - r; j <= y + r; j++) {
                if ((i - x) * (i - x) + (j - y) * (j - y) <= r * r) {
                    points.insert({i, j});
                }
            }
        }
    }
    
    return points.size();
}


/*
PROBLEM 3: Detect Squares (LeetCode 2013)
─────────────────────────────────────────
Add points, count axis-aligned squares with query point as one corner.

Time: O(1) add, O(n) count | Space: O(n)
*/
class DetectSquares {
    map<pair<int,int>, int> points;
    
public:
    void add(vector<int> point) {
        points[{point[0], point[1]}]++;
    }
    
    int count(vector<int> point) {
        int x1 = point[0], y1 = point[1];
        int result = 0;
        
        for (auto& [pt, cnt] : points) {
            int x2 = pt.first, y2 = pt.second;
            
            // Need diagonal point with equal dx and dy
            if (abs(x1 - x2) != abs(y1 - y2) || x1 == x2) continue;
            
            int side = abs(x1 - x2);
            
            // Check for the other two corners
            result += cnt * points[{x1, y2}] * points[{x2, y1}];
        }
        
        return result;
    }
};


/*
PROBLEM 4: Number of Rectangles Containing Each Point (LeetCode 2250)
─────────────────────────────────────────────────────────────────────
rectangles[i] = [length, height] at origin. Count rectangles containing each point.

Approach: Group rectangles by height, sort by length, binary search

Time: O((n + m) log n) | Space: O(n)
*/
vector<int> countRectangles(vector<vector<int>>& rectangles, vector<vector<int>>& points) {
    // Group rectangles by height
    vector<vector<int>> byHeight(101);  // height 1-100
    for (auto& r : rectangles) {
        byHeight[r[1]].push_back(r[0]);  // Store lengths
    }
    
    // Sort lengths for binary search
    for (int h = 1; h <= 100; h++) {
        sort(byHeight[h].begin(), byHeight[h].end());
    }
    
    vector<int> result;
    for (auto& p : points) {
        int x = p[0], y = p[1];
        int count = 0;
        
        // Check all heights >= y
        for (int h = y; h <= 100; h++) {
            // Count rectangles with length >= x
            auto& lengths = byHeight[h];
            count += lengths.end() - lower_bound(lengths.begin(), lengths.end(), x);
        }
        
        result.push_back(count);
    }
    
    return result;
}


/*
PROBLEM 5: Count Positions on Street With Required Brightness (LeetCode 2237)
─────────────────────────────────────────────────────────────────────────────
Each light at position covers [pos - range, pos + range].
Count positions where at least 'requirement[i]' lights shine.

Approach: Difference array on brightness

Time: O(n + m + max_pos) | Space: O(max_pos)
*/
int meetRequirement(int n, vector<vector<int>>& lights, vector<int>& requirement) {
    vector<int> diff(n + 1, 0);
    
    for (auto& light : lights) {
        int pos = light[0], range = light[1];
        diff[max(0, pos - range)]++;
        diff[min(n, pos + range + 1)]--;
    }
    
    int brightness = 0, count = 0;
    for (int i = 0; i < n; i++) {
        brightness += diff[i];
        if (brightness >= requirement[i]) count++;
    }
    
    return count;
}


/*
PROBLEM 6: Range Module (LeetCode 715)
──────────────────────────────────────
Track ranges efficiently with add, remove, query operations.

Time: O(n) per operation | Space: O(n)
*/
class RangeModule {
    map<int, int> intervals;  // start -> end
    
public:
    void addRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it != intervals.begin() && prev(it)->second >= left) {
            --it;
        }
        
        while (it != intervals.end() && it->first <= right) {
            left = min(left, it->first);
            right = max(right, it->second);
            it = intervals.erase(it);
        }
        
        intervals[left] = right;
    }
    
    bool queryRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it == intervals.begin()) return false;
        --it;
        return it->second >= right;
    }
    
    void removeRange(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it != intervals.begin() && prev(it)->second > left) {
            --it;
        }
        
        vector<pair<int,int>> toAdd;
        
        while (it != intervals.end() && it->first < right) {
            if (it->first < left) {
                toAdd.push_back({it->first, left});
            }
            if (it->second > right) {
                toAdd.push_back({right, it->second});
            }
            it = intervals.erase(it);
        }
        
        for (auto& [s, e] : toAdd) {
            intervals[s] = e;
        }
    }
};


/*
PROBLEM 7: Count Integers in Intervals (LeetCode 2276)
──────────────────────────────────────────────────────
Maintain set of intervals, return total integers covered.

Time: O(n log n) amortized | Space: O(n)
*/
class CountIntervals {
    map<int, int> intervals;  // start -> end
    int total = 0;
    
public:
    void add(int left, int right) {
        auto it = intervals.upper_bound(left);
        if (it != intervals.begin() && prev(it)->second >= left) {
            --it;
        }
        
        while (it != intervals.end() && it->first <= right) {
            left = min(left, it->first);
            right = max(right, it->second);
            total -= it->second - it->first;  // Remove old count
            it = intervals.erase(it);
        }
        
        intervals[left] = right;
        total += right - left;
    }
    
    int count() {
        return total;
    }
};


/*
PROBLEM 8: Minimum Lines to Represent a Line Chart (LeetCode 2280)
──────────────────────────────────────────────────────────────────
Find minimum lines to connect all stock price points.

Approach: Count slope changes (use cross product to avoid division)

Time: O(n log n) | Space: O(1)
*/
int minimumLines(vector<vector<int>>& stockPrices) {
    int n = stockPrices.size();
    if (n <= 1) return 0;
    
    sort(stockPrices.begin(), stockPrices.end());
    
    int lines = 1;
    for (int i = 2; i < n; i++) {
        // Compare slopes using cross product to avoid precision issues
        // (y2-y1)/(x2-x1) != (y3-y2)/(x3-x2)
        // (y2-y1)*(x3-x2) != (y3-y2)*(x2-x1)
        long long dx1 = stockPrices[i-1][0] - stockPrices[i-2][0];
        long long dy1 = stockPrices[i-1][1] - stockPrices[i-2][1];
        long long dx2 = stockPrices[i][0] - stockPrices[i-1][0];
        long long dy2 = stockPrices[i][1] - stockPrices[i-1][1];
        
        if (dy1 * dx2 != dy2 * dx1) {
            lines++;
        }
    }
    
    return lines;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Geometric Sweep Problems ===\n\n";
    
    // 3. Detect Squares
    DetectSquares ds;
    ds.add({3, 10});
    ds.add({11, 2});
    ds.add({3, 2});
    cout << "3. Detect squares count: " << ds.count({11, 10}) << "\n";
    
    // 6. Range Module
    RangeModule rm;
    rm.addRange(10, 20);
    rm.removeRange(14, 16);
    cout << "6. Range query [10,14): " << rm.queryRange(10, 14) << "\n";
    cout << "   Range query [13,15): " << rm.queryRange(13, 15) << "\n";
    
    // 8. Minimum Lines
    vector<vector<int>> stocks = {{1,7},{2,6},{3,5},{4,4},{5,4},{6,3},{7,2},{8,1}};
    cout << "8. Minimum lines: " << minimumLines(stocks) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

Geometric Sweep Techniques:
1. Sort events by one dimension, process with data structure for other
2. Coordinate compression for sparse coordinates
3. Binary search for counting in sorted groups
4. Interval merging with ordered map

Common patterns:
- Group by one attribute, sort/search by another
- Use set/map for dynamic interval management
- Cross product for slope comparison (avoid floating point)

================================================================================
*/

