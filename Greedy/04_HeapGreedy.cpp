/*
================================================================================
                    GREEDY - HEAP / PRIORITY QUEUE BASED
================================================================================

Use priority queue to always pick the optimal element at each step.

Time: Usually O(n log n) | Space: O(n)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Minimum Cost to Connect Sticks (LeetCode 1167)
─────────────────────────────────────────────────────────
Cost to connect two sticks = sum of lengths. Minimize total cost.

Input: sticks = [2,4,3]
Output: 14 (2+3=5, cost 5; 5+4=9, cost 9; total 14)

Strategy: Always connect two smallest sticks (Huffman-like)

Time: O(n log n) | Space: O(n)
*/
int connectSticks(vector<int>& sticks) {
    priority_queue<int, vector<int>, greater<int>> pq(sticks.begin(), sticks.end());
    
    int totalCost = 0;
    
    while (pq.size() > 1) {
        int first = pq.top(); pq.pop();
        int second = pq.top(); pq.pop();
        
        int cost = first + second;
        totalCost += cost;
        pq.push(cost);
    }
    
    return totalCost;
}


/*
PROBLEM 2: Last Stone Weight (LeetCode 1046)
────────────────────────────────────────────
Smash two heaviest stones. Remaining = difference. Return last stone weight.

Input: stones = [2,7,4,1,8,1]
Output: 1

Time: O(n log n) | Space: O(n)
*/
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> pq(stones.begin(), stones.end());
    
    while (pq.size() > 1) {
        int y = pq.top(); pq.pop();
        int x = pq.top(); pq.pop();
        
        if (y != x) {
            pq.push(y - x);
        }
    }
    
    return pq.empty() ? 0 : pq.top();
}


/*
PROBLEM 3: Task Scheduler (LeetCode 621)
────────────────────────────────────────
Schedule tasks with cooldown n between same tasks.

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8

Strategy: Greedy with math formula

Time: O(m) where m = tasks | Space: O(1)
*/
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char c : tasks) freq[c - 'A']++;
    
    int maxFreq = *max_element(freq.begin(), freq.end());
    int maxCount = count(freq.begin(), freq.end(), maxFreq);
    
    // (maxFreq - 1) gaps of size (n + 1), plus final batch
    int result = (maxFreq - 1) * (n + 1) + maxCount;
    
    return max(result, (int)tasks.size());
}


/*
PROBLEM 4: IPO (LeetCode 502)
─────────────────────────────
Maximize capital after k projects. Each project has profit and capital requirement.

Input: k = 2, w = 0, profits = [1,2,3], capital = [0,1,1]
Output: 4 (project 0: w=1, project 2: w=4)

Strategy: Sort by capital, use max-heap for affordable projects

Time: O(n log n) | Space: O(n)
*/
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
    int n = profits.size();
    vector<pair<int, int>> projects;  // {capital, profit}
    
    for (int i = 0; i < n; i++) {
        projects.push_back({capital[i], profits[i]});
    }
    
    sort(projects.begin(), projects.end());
    
    priority_queue<int> pq;  // Max-heap of profits
    int i = 0;
    
    while (k--) {
        // Add all affordable projects
        while (i < n && projects[i].first <= w) {
            pq.push(projects[i].second);
            i++;
        }
        
        if (pq.empty()) break;
        
        w += pq.top();
        pq.pop();
    }
    
    return w;
}


/*
PROBLEM 5: Maximum Performance of a Team (LeetCode 1383)
────────────────────────────────────────────────────────
Choose at most k engineers. Performance = sum(speed) * min(efficiency).

Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
Output: 60

Strategy: Sort by efficiency desc, use min-heap to track top k speeds

Time: O(n log n) | Space: O(k)
*/
int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
    vector<pair<int, int>> engineers;  // {efficiency, speed}
    for (int i = 0; i < n; i++) {
        engineers.push_back({efficiency[i], speed[i]});
    }
    
    sort(engineers.rbegin(), engineers.rend());  // Sort by efficiency desc
    
    priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap of speeds
    long long speedSum = 0, maxPerf = 0;
    const int MOD = 1e9 + 7;
    
    for (auto& [eff, spd] : engineers) {
        pq.push(spd);
        speedSum += spd;
        
        if (pq.size() > k) {
            speedSum -= pq.top();
            pq.pop();
        }
        
        maxPerf = max(maxPerf, speedSum * eff);
    }
    
    return maxPerf % MOD;
}


/*
PROBLEM 6: Furthest Building You Can Reach (LeetCode 1642)
──────────────────────────────────────────────────────────
Climb buildings with bricks and ladders. Ladder skips any height, brick for exact.

Input: heights = [4,2,7,6,9,14,12], bricks = 5, ladders = 1
Output: 4

Strategy: Use ladders for biggest jumps (track with min-heap)

Time: O(n log n) | Space: O(ladders)
*/
int furthestBuilding(vector<int>& heights, int bricks, int ladders) {
    priority_queue<int, vector<int>, greater<int>> pq;  // Min-heap of ladder jumps
    
    for (int i = 0; i < heights.size() - 1; i++) {
        int diff = heights[i + 1] - heights[i];
        
        if (diff <= 0) continue;
        
        pq.push(diff);  // Use ladder
        
        if (pq.size() > ladders) {
            // Replace smallest ladder usage with bricks
            bricks -= pq.top();
            pq.pop();
            
            if (bricks < 0) return i;
        }
    }
    
    return heights.size() - 1;
}


/*
PROBLEM 7: Single-Threaded CPU (LeetCode 1834)
──────────────────────────────────────────────
Process tasks in order of shortest processing time.

Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]

Time: O(n log n) | Space: O(n)
*/
vector<int> getOrder(vector<vector<int>>& tasks) {
    int n = tasks.size();
    vector<array<int, 3>> indexed;  // {enqueueTime, processingTime, index}
    
    for (int i = 0; i < n; i++) {
        indexed.push_back({tasks[i][0], tasks[i][1], i});
    }
    
    sort(indexed.begin(), indexed.end());
    
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;  // {processing, index}
    
    vector<int> result;
    long long time = 0;
    int i = 0;
    
    while (i < n || !pq.empty()) {
        if (pq.empty() && time < indexed[i][0]) {
            time = indexed[i][0];
        }
        
        while (i < n && indexed[i][0] <= time) {
            pq.push({indexed[i][1], indexed[i][2]});
            i++;
        }
        
        auto [proc, idx] = pq.top();
        pq.pop();
        time += proc;
        result.push_back(idx);
    }
    
    return result;
}


/*
PROBLEM 8: Meeting Rooms III (LeetCode 2402)
────────────────────────────────────────────
n rooms, meetings go to lowest available room. Count meetings per room.

Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
Output: 0 (room 0 holds most meetings)

Time: O(m log m + m log n) | Space: O(n + m)
*/
int mostBooked(int n, vector<vector<int>>& meetings) {
    sort(meetings.begin(), meetings.end());
    
    vector<int> count(n, 0);
    priority_queue<int, vector<int>, greater<int>> available;  // Available room numbers
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> busy;  // {endTime, room}
    
    for (int i = 0; i < n; i++) available.push(i);
    
    for (auto& m : meetings) {
        long long start = m[0], end = m[1];
        
        // Free up rooms that have finished
        while (!busy.empty() && busy.top().first <= start) {
            available.push(busy.top().second);
            busy.pop();
        }
        
        if (available.empty()) {
            // Wait for earliest room
            auto [freeTime, room] = busy.top();
            busy.pop();
            end = freeTime + (end - start);
            available.push(room);
        }
        
        int room = available.top();
        available.pop();
        count[room]++;
        busy.push({end, room});
    }
    
    return max_element(count.begin(), count.end()) - count.begin();
}


/*
PROBLEM 9: Find Median from Data Stream (LeetCode 295)
──────────────────────────────────────────────────────
Support addNum and findMedian operations.

Strategy: Two heaps - max-heap for lower half, min-heap for upper half

Time: O(log n) add, O(1) median | Space: O(n)
*/
class MedianFinder {
    priority_queue<int> lo;  // Max-heap for lower half
    priority_queue<int, vector<int>, greater<int>> hi;  // Min-heap for upper half
    
public:
    void addNum(int num) {
        lo.push(num);
        hi.push(lo.top());
        lo.pop();
        
        if (hi.size() > lo.size()) {
            lo.push(hi.top());
            hi.pop();
        }
    }
    
    double findMedian() {
        if (lo.size() > hi.size()) return lo.top();
        return (lo.top() + hi.top()) / 2.0;
    }
};


/*
PROBLEM 10: Smallest Range Covering Elements from K Lists (LeetCode 632)
────────────────────────────────────────────────────────────────────────
Find smallest range that includes at least one number from each list.

Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]

Time: O(n log k) | Space: O(k)
*/
vector<int> smallestRange(vector<vector<int>>& nums) {
    // Min-heap: {value, list_index, element_index}
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
    
    int maxVal = INT_MIN;
    for (int i = 0; i < nums.size(); i++) {
        pq.push({nums[i][0], i, 0});
        maxVal = max(maxVal, nums[i][0]);
    }
    
    int rangeStart = 0, rangeEnd = INT_MAX;
    
    while (true) {
        auto [minVal, listIdx, elemIdx] = pq.top();
        pq.pop();
        
        if (maxVal - minVal < rangeEnd - rangeStart) {
            rangeStart = minVal;
            rangeEnd = maxVal;
        }
        
        if (elemIdx + 1 == nums[listIdx].size()) break;
        
        int next = nums[listIdx][elemIdx + 1];
        pq.push({next, listIdx, elemIdx + 1});
        maxVal = max(maxVal, next);
    }
    
    return {rangeStart, rangeEnd};
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Heap-Based Greedy ===\n\n";
    
    // 1. Connect Sticks
    vector<int> sticks = {2, 4, 3};
    cout << "1. Min cost to connect: " << connectSticks(sticks) << "\n";
    
    // 2. Last Stone Weight
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << "2. Last stone weight: " << lastStoneWeight(stones) << "\n";
    
    // 3. Task Scheduler
    vector<char> tasks = {'A','A','A','B','B','B'};
    cout << "3. Min intervals: " << leastInterval(tasks, 2) << "\n";
    
    // 6. Furthest Building
    vector<int> heights = {4, 2, 7, 6, 9, 14, 12};
    cout << "6. Furthest building: " << furthestBuilding(heights, 5, 1) << "\n";
    
    // 9. Median Finder
    MedianFinder mf;
    mf.addNum(1); mf.addNum(2);
    cout << "9. Median of [1,2]: " << mf.findMedian() << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Heap Type & Strategy                           |
+───────────────────────────────+────────────────────────────────────────────────+
| Connect Sticks                | Min-heap, always combine two smallest          |
| Last Stone Weight             | Max-heap, smash two largest                    |
| Task Scheduler                | Math formula (can also use heap)               |
| IPO                           | Sort by capital, max-heap for profits          |
| Max Performance               | Sort by efficiency, min-heap for top k speeds  |
| Furthest Building             | Min-heap to track ladder usage                 |
| Single-Threaded CPU           | Min-heap by {processing, index}                |
| Meeting Rooms III             | Two heaps: available rooms, busy rooms         |
| Median Finder                 | Two heaps: max for lower, min for upper        |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

