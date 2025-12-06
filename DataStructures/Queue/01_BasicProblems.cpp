/*
================================================================================
                    QUEUE - BASIC PROBLEMS
================================================================================

Pattern 1: Queue Design Problems
Pattern 2: Simulation Problems
Pattern 3: Stream/Window Problems

================================================================================
*/

#include <iostream>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <unordered_map>
using namespace std;

/*
================================================================================
PATTERN 1: QUEUE DESIGN PROBLEMS
================================================================================
*/

// 1.1 IMPLEMENT STACK USING QUEUES
// LeetCode: 225. Implement Stack using Queues
class MyStack {
private:
    queue<int> q;
    
public:
    void push(int x) {
        q.push(x);
        // Rotate to make new element at front
        for (int i = 0; i < q.size() - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};
// Push: O(n), Pop/Top: O(1)


// 1.2 IMPLEMENT QUEUE USING STACKS
// LeetCode: 232. Implement Queue using Stacks
class MyQueue {
private:
    stack<int> input;   // For push
    stack<int> output;  // For pop/peek
    
    void transfer() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
    }
    
public:
    void push(int x) {
        input.push(x);
    }
    
    int pop() {
        transfer();
        int val = output.top();
        output.pop();
        return val;
    }
    
    int peek() {
        transfer();
        return output.top();
    }
    
    bool empty() {
        return input.empty() && output.empty();
    }
};
// Amortized O(1) for all operations


// 1.3 DESIGN HIT COUNTER
// LeetCode: 362. Design Hit Counter (Premium)
// Count hits in the last 5 minutes (300 seconds)
class HitCounter {
private:
    queue<int> hits;
    
public:
    void hit(int timestamp) {
        hits.push(timestamp);
    }
    
    int getHits(int timestamp) {
        // Remove old hits
        while (!hits.empty() && hits.front() <= timestamp - 300) {
            hits.pop();
        }
        return hits.size();
    }
};

// Follow-up: Handle high volume (many hits per second)
class HitCounterOptimized {
private:
    int times[300];   // Circular array of timestamps
    int hits[300];    // Hit counts
    
public:
    HitCounterOptimized() {
        fill(times, times + 300, 0);
        fill(hits, hits + 300, 0);
    }
    
    void hit(int timestamp) {
        int idx = timestamp % 300;
        if (times[idx] != timestamp) {
            times[idx] = timestamp;
            hits[idx] = 1;
        } else {
            hits[idx]++;
        }
    }
    
    int getHits(int timestamp) {
        int count = 0;
        for (int i = 0; i < 300; i++) {
            if (timestamp - times[i] < 300) {
                count += hits[i];
            }
        }
        return count;
    }
};


/*
================================================================================
PATTERN 2: SIMULATION PROBLEMS
================================================================================
*/

// 2.1 NUMBER OF RECENT CALLS
// LeetCode: 933. Number of Recent Calls
class RecentCounter {
private:
    queue<int> requests;
    
public:
    int ping(int t) {
        requests.push(t);
        // Remove requests older than 3000ms
        while (requests.front() < t - 3000) {
            requests.pop();
        }
        return requests.size();
    }
};
// Returns count of requests in [t-3000, t]


// 2.2 TASK SCHEDULER
// LeetCode: 621. Task Scheduler
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char task : tasks) {
        freq[task - 'A']++;
    }
    
    // Max frequency
    int maxFreq = *max_element(freq.begin(), freq.end());
    
    // Count tasks with max frequency
    int maxCount = count(freq.begin(), freq.end(), maxFreq);
    
    // Formula: (maxFreq - 1) * (n + 1) + maxCount
    // Minimum slots needed
    int minSlots = (maxFreq - 1) * (n + 1) + maxCount;
    
    return max((int)tasks.size(), minSlots);
}
/*
Example: tasks = ["A","A","A","B","B","B"], n = 2
A _ _ A _ _ A
A B _ A B _ A B
Answer: 8

Formula explanation:
- Need (maxFreq - 1) full cycles of (n+1) slots
- Plus one last round for tasks with max frequency
*/


// 2.3 DOTA2 SENATE
// LeetCode: 649. Dota2 Senate
string predictPartyVictory(string senate) {
    queue<int> radiant, dire;
    int n = senate.size();
    
    for (int i = 0; i < n; i++) {
        if (senate[i] == 'R') radiant.push(i);
        else dire.push(i);
    }
    
    while (!radiant.empty() && !dire.empty()) {
        int r = radiant.front(); radiant.pop();
        int d = dire.front(); dire.pop();
        
        // Senator with smaller index bans the other
        // Winner rejoins the queue for next round
        if (r < d) {
            radiant.push(r + n);  // Add n to maintain order
        } else {
            dire.push(d + n);
        }
    }
    
    return radiant.empty() ? "Dire" : "Radiant";
}


// 2.4 TIME NEEDED TO BUY TICKETS
// LeetCode: 2073. Time Needed to Buy Tickets
int timeRequiredToBuy(vector<int>& tickets, int k) {
    int time = 0;
    
    for (int i = 0; i < tickets.size(); i++) {
        if (i <= k) {
            // People before k (inclusive) can buy min(tickets[i], tickets[k]) times
            time += min(tickets[i], tickets[k]);
        } else {
            // People after k can buy min(tickets[i], tickets[k] - 1) times
            time += min(tickets[i], tickets[k] - 1);
        }
    }
    
    return time;
}


/*
================================================================================
PATTERN 3: STREAM / WINDOW PROBLEMS
================================================================================
*/

// 3.1 MOVING AVERAGE FROM DATA STREAM
// LeetCode: 346. Moving Average from Data Stream (Premium)
class MovingAverage {
private:
    queue<int> window;
    int maxSize;
    double sum;
    
public:
    MovingAverage(int size) : maxSize(size), sum(0) {}
    
    double next(int val) {
        window.push(val);
        sum += val;
        
        if (window.size() > maxSize) {
            sum -= window.front();
            window.pop();
        }
        
        return sum / window.size();
    }
};


// 3.2 FIRST UNIQUE CHARACTER IN STREAM
// Characters come one by one, find first unique at any point
class FirstUnique {
private:
    queue<int> candidates;
    unordered_map<int, int> count;
    
public:
    FirstUnique(vector<int>& nums) {
        for (int num : nums) {
            add(num);
        }
    }
    
    int showFirstUnique() {
        while (!candidates.empty()) {
            if (count[candidates.front()] == 1) {
                return candidates.front();
            }
            candidates.pop();
        }
        return -1;
    }
    
    void add(int value) {
        count[value]++;
        if (count[value] == 1) {
            candidates.push(value);
        }
    }
};


// 3.3 REVEAL CARDS IN INCREASING ORDER
// LeetCode: 950. Reveal Cards In Increasing Order
vector<int> deckRevealedIncreasing(vector<int>& deck) {
    int n = deck.size();
    sort(deck.begin(), deck.end());
    
    // Simulate the process in reverse using deque
    deque<int> result;
    
    for (int i = n - 1; i >= 0; i--) {
        if (!result.empty()) {
            // Move last to front (reverse of "move top to bottom")
            result.push_front(result.back());
            result.pop_back();
        }
        result.push_front(deck[i]);
    }
    
    return vector<int>(result.begin(), result.end());
}
// Order deck so revealing gives sorted order


// 3.4 GAS STATION (Can use circular queue concept)
// LeetCode: 134. Gas Station
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalSurplus = 0;
    int currentSurplus = 0;
    int startStation = 0;
    
    for (int i = 0; i < gas.size(); i++) {
        int surplus = gas[i] - cost[i];
        totalSurplus += surplus;
        currentSurplus += surplus;
        
        if (currentSurplus < 0) {
            // Can't start from any station before i
            startStation = i + 1;
            currentSurplus = 0;
        }
    }
    
    return totalSurplus >= 0 ? startStation : -1;
}


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Queue Basic Problems ===\n\n";
    
    // Stack using Queues
    cout << "--- Stack using Queues ---" << endl;
    MyStack stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    cout << "Top: " << stk.top() << endl;  // 3
    cout << "Pop: " << stk.pop() << endl;  // 3
    cout << "Top: " << stk.top() << endl;  // 2
    
    // Queue using Stacks
    cout << "\n--- Queue using Stacks ---" << endl;
    MyQueue que;
    que.push(1);
    que.push(2);
    que.push(3);
    cout << "Peek: " << que.peek() << endl;  // 1
    cout << "Pop: " << que.pop() << endl;    // 1
    cout << "Peek: " << que.peek() << endl;  // 2
    
    // Recent Counter
    cout << "\n--- Recent Counter ---" << endl;
    RecentCounter rc;
    cout << "ping(1): " << rc.ping(1) << endl;      // 1
    cout << "ping(100): " << rc.ping(100) << endl;  // 2
    cout << "ping(3001): " << rc.ping(3001) << endl; // 3
    cout << "ping(3002): " << rc.ping(3002) << endl; // 3
    
    // Task Scheduler
    cout << "\n--- Task Scheduler ---" << endl;
    vector<char> tasks = {'A', 'A', 'A', 'B', 'B', 'B'};
    cout << "Least interval (n=2): " << leastInterval(tasks, 2) << endl;  // 8
    
    // Moving Average
    cout << "\n--- Moving Average ---" << endl;
    MovingAverage ma(3);
    cout << "next(1): " << ma.next(1) << endl;  // 1.0
    cout << "next(10): " << ma.next(10) << endl; // 5.5
    cout << "next(3): " << ma.next(3) << endl;  // 4.67
    cout << "next(5): " << ma.next(5) << endl;  // 6.0 (window is [10,3,5])
    
    // Dota2 Senate
    cout << "\n--- Dota2 Senate ---" << endl;
    cout << "RD: " << predictPartyVictory("RD") << endl;    // Radiant
    cout << "RDD: " << predictPartyVictory("RDD") << endl;  // Dire
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

┌───────────────────────────────┬─────────────────────────────────────────────┐
│ Pattern                       │ Key Technique                               │
├───────────────────────────────┼─────────────────────────────────────────────┤
│ Stack using Queues            │ Rotate after each push                      │
│ Queue using Stacks            │ Two stacks: input + output (lazy transfer)  │
│ Hit Counter                   │ Queue for simple, circular array for volume │
│ Task Scheduler                │ Formula: (maxFreq-1)*(n+1) + maxCount       │
│ Moving Average                │ Queue as sliding window + running sum       │
│ Reveal Cards                  │ Simulate reverse with deque                 │
└───────────────────────────────┴─────────────────────────────────────────────┘

================================================================================
*/

