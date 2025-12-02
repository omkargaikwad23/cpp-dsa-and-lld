/*
================================================================================
                    DESIGN - TIME-BASED & VERSIONED STRUCTURES
================================================================================

Track historical values, support queries at specific times/versions.
Key insight: Binary search on sorted timestamps.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Time Based Key-Value Store (LeetCode 981) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────────────────────
set(key, value, timestamp), get(key, timestamp) returns value at or before timestamp.

Time: O(log n) | Space: O(n)
*/
class TimeMap {
    unordered_map<string, vector<pair<int, string>>> store;  // key → [(timestamp, value)]
    
public:
    void set(string key, string value, int timestamp) {
        store[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        if (!store.count(key)) return "";
        
        auto& vals = store[key];
        
        // Binary search for largest timestamp <= given timestamp
        int left = 0, right = vals.size() - 1, result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (vals[mid].first <= timestamp) {
                result = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result == -1 ? "" : vals[result].second;
    }
};


/*
PROBLEM 2: Snapshot Array (LeetCode 1146) ⭐ GOOGLE FAVORITE
────────────────────────────────────────────────────────────
set(index, val), snap(), get(index, snap_id)

Design: For each index, store list of (snap_id, value).

Time: O(log S) get, O(1) set/snap | Space: O(n * S)
*/
class SnapshotArray {
    vector<vector<pair<int, int>>> data;  // For each index: [(snap_id, value)]
    int snapId;
    
public:
    SnapshotArray(int length) : data(length), snapId(0) {
        for (int i = 0; i < length; i++) {
            data[i].push_back({0, 0});  // Initial value
        }
    }
    
    void set(int index, int val) {
        if (data[index].back().first == snapId) {
            data[index].back().second = val;
        } else {
            data[index].push_back({snapId, val});
        }
    }
    
    int snap() {
        return snapId++;
    }
    
    int get(int index, int snap_id) {
        auto& snaps = data[index];
        
        // Binary search for largest snap_id <= given snap_id
        int left = 0, right = snaps.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (snaps[mid].first <= snap_id) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        
        return snaps[left].second;
    }
};


/*
PROBLEM 3: Design Hit Counter (LeetCode 362)
────────────────────────────────────────────
Count hits in past 5 minutes (300 seconds).

Design: Queue or circular array.

Time: O(1) amortized | Space: O(300)
*/
class HitCounter {
    queue<int> hits;
    
    void cleanup(int timestamp) {
        while (!hits.empty() && hits.front() <= timestamp - 300) {
            hits.pop();
        }
    }
    
public:
    void hit(int timestamp) {
        hits.push(timestamp);
    }
    
    int getHits(int timestamp) {
        cleanup(timestamp);
        return hits.size();
    }
};

// Space-optimized using circular array
class HitCounterOptimized {
    vector<int> times;
    vector<int> counts;
    
public:
    HitCounterOptimized() : times(300, 0), counts(300, 0) {}
    
    void hit(int timestamp) {
        int idx = timestamp % 300;
        if (times[idx] != timestamp) {
            times[idx] = timestamp;
            counts[idx] = 1;
        } else {
            counts[idx]++;
        }
    }
    
    int getHits(int timestamp) {
        int total = 0;
        for (int i = 0; i < 300; i++) {
            if (timestamp - times[i] < 300) {
                total += counts[i];
            }
        }
        return total;
    }
};


/*
PROBLEM 4: Design Rate Limiter
──────────────────────────────
Allow at most k requests per user in time window.

Time: O(1) amortized | Space: O(users * window)
*/
class RateLimiter {
    int maxRequests;
    int windowSeconds;
    unordered_map<string, queue<int>> userRequests;
    
public:
    RateLimiter(int maxRequests, int windowSeconds) 
        : maxRequests(maxRequests), windowSeconds(windowSeconds) {}
    
    bool allowRequest(string userId, int timestamp) {
        auto& q = userRequests[userId];
        
        // Remove expired requests
        while (!q.empty() && q.front() <= timestamp - windowSeconds) {
            q.pop();
        }
        
        if (q.size() < maxRequests) {
            q.push(timestamp);
            return true;
        }
        
        return false;
    }
};


/*
PROBLEM 5: Stock Price Fluctuation (LeetCode 2034)
──────────────────────────────────────────────────
update(timestamp, price), current(), max(), min()

Time: O(log n) | Space: O(n)
*/
class StockPrice {
    unordered_map<int, int> timestampToPrice;
    map<int, int> priceCount;  // price → count
    int latestTime;
    
public:
    StockPrice() : latestTime(0) {}
    
    void update(int timestamp, int price) {
        if (timestampToPrice.count(timestamp)) {
            int oldPrice = timestampToPrice[timestamp];
            priceCount[oldPrice]--;
            if (priceCount[oldPrice] == 0) {
                priceCount.erase(oldPrice);
            }
        }
        
        timestampToPrice[timestamp] = price;
        priceCount[price]++;
        latestTime = max(latestTime, timestamp);
    }
    
    int current() {
        return timestampToPrice[latestTime];
    }
    
    int maximum() {
        return priceCount.rbegin()->first;
    }
    
    int minimum() {
        return priceCount.begin()->first;
    }
};


/*
PROBLEM 6: Logger Rate Limiter (LeetCode 359)
─────────────────────────────────────────────
Print message only if not printed in last 10 seconds.

Time: O(1) | Space: O(messages)
*/
class Logger {
    unordered_map<string, int> lastPrinted;
    
public:
    bool shouldPrintMessage(int timestamp, string message) {
        if (!lastPrinted.count(message) || timestamp - lastPrinted[message] >= 10) {
            lastPrinted[message] = timestamp;
            return true;
        }
        return false;
    }
};


/*
PROBLEM 7: Moving Average from Data Stream (LeetCode 346)
─────────────────────────────────────────────────────────
Sliding window average.

Time: O(1) | Space: O(size)
*/
class MovingAverage {
    queue<int> q;
    int maxSize;
    double sum;
    
public:
    MovingAverage(int size) : maxSize(size), sum(0) {}
    
    double next(int val) {
        q.push(val);
        sum += val;
        
        if (q.size() > maxSize) {
            sum -= q.front();
            q.pop();
        }
        
        return sum / q.size();
    }
};


/*
PROBLEM 8: Design Most Recently Used Queue (LeetCode 1756)
──────────────────────────────────────────────────────────
fetch(k): Move k-th element to end, return it.

Design: Sqrt decomposition or BIT for O(sqrt n) or O(log n).

Simplified O(n) version:
*/
class MRUQueue {
    vector<int> data;
    
public:
    MRUQueue(int n) {
        for (int i = 1; i <= n; i++) {
            data.push_back(i);
        }
    }
    
    int fetch(int k) {
        int val = data[k - 1];
        data.erase(data.begin() + k - 1);
        data.push_back(val);
        return val;
    }
};


/*
PROBLEM 9: Design Leaderboard (LeetCode 1244)
─────────────────────────────────────────────
addScore(playerId, score), top(K), reset(playerId)

Time: O(n log n) for top | Space: O(n)
*/
class Leaderboard {
    unordered_map<int, int> scores;
    
public:
    void addScore(int playerId, int score) {
        scores[playerId] += score;
    }
    
    int top(int K) {
        vector<int> vals;
        for (auto& [id, score] : scores) {
            vals.push_back(score);
        }
        
        // Partial sort for top K
        partial_sort(vals.begin(), vals.begin() + min(K, (int)vals.size()), 
                     vals.end(), greater<int>());
        
        int sum = 0;
        for (int i = 0; i < K && i < vals.size(); i++) {
            sum += vals[i];
        }
        return sum;
    }
    
    void reset(int playerId) {
        scores.erase(playerId);
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Time-Based Designs ===\n\n";
    
    // 1. TimeMap
    TimeMap tm;
    tm.set("foo", "bar", 1);
    cout << "1. TimeMap get(foo, 1): " << tm.get("foo", 1) << "\n";
    cout << "   TimeMap get(foo, 3): " << tm.get("foo", 3) << "\n";
    tm.set("foo", "bar2", 4);
    cout << "   TimeMap get(foo, 4): " << tm.get("foo", 4) << "\n";
    cout << "   TimeMap get(foo, 5): " << tm.get("foo", 5) << "\n";
    
    // 2. Snapshot Array
    SnapshotArray sa(3);
    sa.set(0, 5);
    int snap0 = sa.snap();
    sa.set(0, 6);
    cout << "2. Snapshot get(0, " << snap0 << "): " << sa.get(0, snap0) << "\n";
    
    // 5. Stock Price
    StockPrice sp;
    sp.update(1, 10);
    sp.update(2, 5);
    cout << "5. Stock current: " << sp.current() << "\n";
    cout << "   Stock max: " << sp.maximum() << "\n";
    cout << "   Stock min: " << sp.minimum() << "\n";
    
    // 7. Moving Average
    MovingAverage ma(3);
    cout << "7. Moving avg: " << ma.next(1) << " ";
    cout << ma.next(10) << " ";
    cout << ma.next(3) << " ";
    cout << ma.next(5) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Design                        | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| TimeMap                       | HashMap + binary search on timestamps          |
| Snapshot Array                | Per-index list of (snap_id, value)             |
| Hit Counter                   | Queue or circular array (mod 300)              |
| Rate Limiter                  | Per-user queue of timestamps                   |
| Stock Price                   | HashMap + TreeMap for price counts             |
| Logger                        | HashMap of last printed time                   |
| Moving Average                | Queue + running sum                            |
| Leaderboard                   | HashMap + partial sort for top K               |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

