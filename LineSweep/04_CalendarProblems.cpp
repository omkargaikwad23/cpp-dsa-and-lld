/*
================================================================================
                    LINE SWEEP - CALENDAR / BOOKING PROBLEMS
================================================================================

Calendar problems track bookings/events and check for conflicts or count overlaps.
Common data structures: ordered map, balanced BST, segment tree.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: My Calendar I (LeetCode 729)
───────────────────────────────────────
Implement calendar that rejects double bookings.

Approach: Store intervals, check overlap before inserting

Time: O(n) per booking | Space: O(n)
*/
class MyCalendarI {
    vector<pair<int, int>> bookings;
    
public:
    bool book(int start, int end) {
        for (auto& [s, e] : bookings) {
            // Overlap if: start < e && end > s
            if (start < e && end > s) {
                return false;
            }
        }
        bookings.push_back({start, end});
        return true;
    }
};

// Optimized with ordered map (O(log n) per booking)
class MyCalendarI_Optimized {
    map<int, int> bookings;  // start -> end
    
public:
    bool book(int start, int end) {
        auto it = bookings.upper_bound(start);
        
        // Check if overlaps with previous booking
        if (it != bookings.begin()) {
            auto prev = std::prev(it);
            if (prev->second > start) return false;
        }
        
        // Check if overlaps with next booking
        if (it != bookings.end()) {
            if (it->first < end) return false;
        }
        
        bookings[start] = end;
        return true;
    }
};


/*
PROBLEM 2: My Calendar II (LeetCode 731)
────────────────────────────────────────
Allow double bookings but reject triple bookings.

Approach: Track single bookings and double bookings separately

Time: O(n) per booking | Space: O(n)
*/
class MyCalendarII {
    vector<pair<int, int>> bookings;
    vector<pair<int, int>> overlaps;  // Double-booked regions
    
public:
    bool book(int start, int end) {
        // Check triple booking with existing overlaps
        for (auto& [s, e] : overlaps) {
            if (start < e && end > s) {
                return false;  // Would create triple booking
            }
        }
        
        // Add overlap with existing bookings
        for (auto& [s, e] : bookings) {
            if (start < e && end > s) {
                overlaps.push_back({max(start, s), min(end, e)});
            }
        }
        
        bookings.push_back({start, end});
        return true;
    }
};


/*
PROBLEM 3: My Calendar III (LeetCode 732)
─────────────────────────────────────────
Return max concurrent bookings (K-booking).

Approach: Use difference array with ordered map

Time: O(n) per booking | Space: O(n)
*/
class MyCalendarIII {
    map<int, int> timeline;
    
public:
    int book(int start, int end) {
        timeline[start]++;
        timeline[end]--;
        
        int ongoing = 0, maxK = 0;
        for (auto& [time, delta] : timeline) {
            ongoing += delta;
            maxK = max(maxK, ongoing);
        }
        
        return maxK;
    }
};


/*
PROBLEM 4: Meeting Scheduler (LeetCode 1229 - Premium)
──────────────────────────────────────────────────────
Find earliest common free slot of duration >= dur.

Input: slots1 = [[10,50],[60,120],[140,210]]
       slots2 = [[0,15],[60,70]]
       duration = 8
Output: [60,68]

Time: O(m log m + n log n) | Space: O(1)
*/
vector<int> minAvailableDuration(vector<vector<int>>& slots1, 
                                  vector<vector<int>>& slots2, int duration) {
    sort(slots1.begin(), slots1.end());
    sort(slots2.begin(), slots2.end());
    
    int i = 0, j = 0;
    
    while (i < slots1.size() && j < slots2.size()) {
        int start = max(slots1[i][0], slots2[j][0]);
        int end = min(slots1[i][1], slots2[j][1]);
        
        if (end - start >= duration) {
            return {start, start + duration};
        }
        
        // Advance the slot that ends earlier
        if (slots1[i][1] < slots2[j][1]) i++;
        else j++;
    }
    
    return {};
}


/*
PROBLEM 5: Process Tasks Using Servers (LeetCode 1882)
──────────────────────────────────────────────────────
Assign tasks to servers. Each server has weight, pick smallest weight (then index).

Input: servers = [3,3,2], tasks = [1,2,3,2,1,2]
Output: [2,2,0,2,1,2]

Time: O((n + m) log n) | Space: O(n)
*/
vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
    // Available servers: {weight, index}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> available;
    // Busy servers: {free_time, weight, index}
    priority_queue<tuple<long long,int,int>, vector<tuple<long long,int,int>>, greater<>> busy;
    
    for (int i = 0; i < servers.size(); i++) {
        available.push({servers[i], i});
    }
    
    vector<int> result;
    long long time = 0;
    
    for (int t = 0; t < tasks.size(); t++) {
        time = max(time, (long long)t);
        
        // Move servers that become free by time
        while (!busy.empty() && get<0>(busy.top()) <= time) {
            auto [freeTime, weight, idx] = busy.top();
            busy.pop();
            available.push({weight, idx});
        }
        
        // If no server available, wait for earliest
        if (available.empty()) {
            auto [freeTime, weight, idx] = busy.top();
            busy.pop();
            time = freeTime;
            available.push({weight, idx});
            
            // Move all servers that become free at this time
            while (!busy.empty() && get<0>(busy.top()) <= time) {
                auto [ft, w, i] = busy.top();
                busy.pop();
                available.push({w, i});
            }
        }
        
        // Assign task to best available server
        auto [weight, idx] = available.top();
        available.pop();
        result.push_back(idx);
        busy.push({time + tasks[t], weight, idx});
    }
    
    return result;
}


/*
PROBLEM 6: Task Scheduler (LeetCode 621)
────────────────────────────────────────
Schedule tasks with cooldown n between same tasks. Find min time.

Input: tasks = ["A","A","A","B","B","B"], n = 2
Output: 8 (A->B->idle->A->B->idle->A->B)

─────────────────────────────────────────────────────────────────
FORMULA: (maxFreq - 1) * (n + 1) + maxCount
─────────────────────────────────────────────────────────────────

Visual: Arrange most frequent task first, leaving n gaps:

    A _ _ | A _ _ | A        (n=2, so each slot has n+1=3 positions)
    └─────┘ └─────┘
     slot    slot    final

Fill gaps with other tasks:

    A B _ | A B _ | A B
    └─────┘ └─────┘ └───┘
     slot1   slot2   final

Formula breakdown:
┌──────────────┬────────────────────────────────────────────────────┐
│ (maxFreq - 1)│ Number of COMPLETE slots (last one is partial)    │
│ (n + 1)      │ Size of each slot (1 task + n cooldown positions) │
│ maxCount     │ Tasks in final slot (all tasks with max frequency)│
└──────────────┴────────────────────────────────────────────────────┘

Example: maxFreq=3, maxCount=2, n=2
         = (3-1) * (2+1) + 2 = 2 * 3 + 2 = 8

Edge case: If many diverse tasks exist, no idle time needed
           → answer = max(formula, tasks.size())
─────────────────────────────────────────────────────────────────

Dry Run:
tasks = ["A","A","A","B","B","B"], n = 2
freq = [3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
maxFreq = 3
maxCount = 2
result = (maxFreq - 1) * (n + 1) + maxCount = 8
return max(result, (int)tasks.size()) = 8


Time: O(m) | Space: O(1)
*/
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char c : tasks) freq[c - 'A']++;
    
    int maxFreq = *max_element(freq.begin(), freq.end());
    int maxCount = count(freq.begin(), freq.end(), maxFreq);
    
    // Formula: (maxFreq - 1) * (n + 1) + maxCount
    // But if tasks.size() > this, answer is tasks.size()
    int result = (maxFreq - 1) * (n + 1) + maxCount;
    return max(result, (int)tasks.size());
}


/*
PROBLEM 7: Single-Threaded CPU (LeetCode 1834)
──────────────────────────────────────────────
Process tasks on CPU. Pick shortest available task (smallest index on tie).

Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]

Time: O(n log n) | Space: O(n)
*/
vector<int> getOrder(vector<vector<int>>& tasks) {
    int n = tasks.size();
    vector<array<int, 3>> indexed(n);  // {enqueueTime, processingTime, index}
    
    for (int i = 0; i < n; i++) {
        indexed[i] = {tasks[i][0], tasks[i][1], i};
    }
    
    sort(indexed.begin(), indexed.end());
    
    // Min-heap: {processingTime, index}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    
    vector<int> result;
    long long time = 0;
    int i = 0;
    
    while (i < n || !pq.empty()) {
        if (pq.empty() && time < indexed[i][0]) {
            time = indexed[i][0];
        }
        
        // Add all tasks that have arrived
        while (i < n && indexed[i][0] <= time) {
            pq.push({indexed[i][1], indexed[i][2]});
            i++;
        }
        
        auto [procTime, idx] = pq.top();
        pq.pop();
        time += procTime;
        result.push_back(idx);
    }
    
    return result;
}


/*
PROBLEM 8: Booking Concert Tickets in Groups (LeetCode 2286)
────────────────────────────────────────────────────────────
Book k consecutive seats or k seats scattered in first maxRow rows.

Approach: Segment tree for range max and range sum queries

(Simplified version - full implementation would use segment tree)
*/
class BookMyShow {
    int n, m;
    vector<long long> rowSeats;  // Available seats in each row
    
public:
    BookMyShow(int n, int m) : n(n), m(m), rowSeats(n, m) {}
    
    vector<int> gather(int k, int maxRow) {
        // Find first row with k consecutive seats
        for (int i = 0; i <= maxRow; i++) {
            if (rowSeats[i] >= k) {
                int col = m - rowSeats[i];
                rowSeats[i] -= k;
                return {i, col};
            }
        }
        return {};
    }
    
    bool scatter(int k, int maxRow) {
        // Check if total seats in rows 0..maxRow >= k
        long long total = 0;
        for (int i = 0; i <= maxRow; i++) {
            total += rowSeats[i];
        }
        
        if (total < k) return false;
        
        // Allocate seats
        for (int i = 0; i <= maxRow && k > 0; i++) {
            int take = min((long long)k, rowSeats[i]);
            rowSeats[i] -= take;
            k -= take;
        }
        
        return true;
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Calendar & Booking Problems ===\n\n";
    
    // 1. My Calendar I
    MyCalendarI_Optimized cal1;
    cout << "1. Calendar I: "
         << cal1.book(10, 20) << " "
         << cal1.book(15, 25) << " "
         << cal1.book(20, 30) << "\n";
    
    // 3. My Calendar III
    MyCalendarIII cal3;
    cout << "3. Calendar III: "
         << cal3.book(10, 20) << " "
         << cal3.book(50, 60) << " "
         << cal3.book(10, 40) << " "
         << cal3.book(5, 15) << "\n";
    
    // 6. Task Scheduler
    vector<char> tasks = {'A','A','A','B','B','B'};
    cout << "6. Task scheduler: " << leastInterval(tasks, 2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

Calendar Problem Patterns:
1. My Calendar I: Check overlap with existing bookings
2. My Calendar II: Track single and double bookings separately
3. My Calendar III: Use difference array / ordered map for counting

Key data structures:
- ordered map: For efficient range queries and updates
- priority_queue: For scheduling tasks by priority
- segment tree: For complex range queries (max, sum)

================================================================================
*/

