/*
================================================================================
                    PRIORITY QUEUE (HEAP) - COMPLETE REFERENCE
================================================================================

Priority Queue is a container adapter that provides O(log n) insertion and 
O(1) access to the largest (or smallest) element.

Default: MAX HEAP (largest element at top)
For MIN HEAP: use greater<T> comparator

Key Operations:
- push(x)   : Insert element          - O(log n)
- pop()     : Remove top element      - O(log n)
- top()     : Access top element      - O(1)
- empty()   : Check if empty          - O(1)
- size()    : Get number of elements  - O(1)

================================================================================
                         WHEN TO USE
================================================================================

1. K-th Largest/Smallest Element
2. Top K Frequent Elements
3. Merge K Sorted Lists
4. Dijkstra's Algorithm (shortest path)
5. Huffman Coding
6. Median from Data Stream
7. Task Scheduling by Priority

================================================================================
*/

#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>
using namespace std;

/*
================================================================================
                         BASIC USAGE
================================================================================
*/

void basicUsage() {
    cout << "=== Basic Priority Queue ===" << endl;
    
    // MAX HEAP (default)
    priority_queue<int> maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    maxHeap.push(1);
    maxHeap.push(5);
    
    cout << "Max Heap (descending): ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";  // 5 4 3 1 1
        maxHeap.pop();
    }
    cout << endl;
    
    // MIN HEAP
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(4);
    minHeap.push(1);
    minHeap.push(5);
    
    cout << "Min Heap (ascending): ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";  // 1 1 3 4 5
        minHeap.pop();
    }
    cout << endl;
}


/*
================================================================================
                    CUSTOM COMPARATORS
================================================================================
*/

void customComparators() {
    cout << "\n=== Custom Comparators ===" << endl;
    
    // Using pairs - default sorts by first, then second (max)
    priority_queue<pair<int, int>> pqPair;
    pqPair.push({3, 10});
    pqPair.push({1, 20});
    pqPair.push({3, 5});
    
    cout << "Pairs (max by first, then second): ";
    while (!pqPair.empty()) {
        auto [a, b] = pqPair.top();
        cout << "(" << a << "," << b << ") ";  // (3,10) (3,5) (1,20)
        pqPair.pop();
    }
    cout << endl;
    
    // MIN heap for pairs
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minPQ;
    minPQ.push({3, 10});
    minPQ.push({1, 20});
    minPQ.push({3, 5});
    
    cout << "Pairs (min): ";
    while (!minPQ.empty()) {
        auto [a, b] = minPQ.top();
        cout << "(" << a << "," << b << ") ";  // (1,20) (3,5) (3,10)
        minPQ.pop();
    }
    cout << endl;
    
    // LAMBDA COMPARATOR
    auto cmp = [](const pair<int,string>& a, const pair<int,string>& b) {
        return a.first > b.first;  // Min heap by first element
    };
    priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(cmp)> customPQ(cmp);
    
    customPQ.push({5, "five"});
    customPQ.push({2, "two"});
    customPQ.push({8, "eight"});
    
    cout << "Custom (min by first): ";
    while (!customPQ.empty()) {
        auto [num, str] = customPQ.top();
        cout << str << "(" << num << ") ";  // two(2) five(5) eight(8)
        customPQ.pop();
    }
    cout << endl;
}


/*
================================================================================
                    STRUCT WITH CUSTOM COMPARATOR
================================================================================
*/

struct Task {
    int priority;
    string name;
};

// Method 1: Operator overloading
struct TaskComparator {
    bool operator()(const Task& a, const Task& b) {
        return a.priority < b.priority;  // Max heap by priority
    }
};

void structComparator() {
    cout << "\n=== Struct Comparator ===" << endl;
    
    priority_queue<Task, vector<Task>, TaskComparator> taskQueue;
    taskQueue.push({3, "Low"});
    taskQueue.push({7, "High"});
    taskQueue.push({5, "Medium"});
    
    cout << "Tasks by priority: ";
    while (!taskQueue.empty()) {
        cout << taskQueue.top().name << "(" << taskQueue.top().priority << ") ";
        taskQueue.pop();
    }
    cout << endl;  // High(7) Medium(5) Low(3)
}


/*
================================================================================
                    INTERVIEW PROBLEMS
================================================================================
*/

// 1. KTH LARGEST ELEMENT IN ARRAY
// LeetCode 215 - Use MIN heap of size k
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (int num : nums) {
        minHeap.push(num);
        if (minHeap.size() > k) {
            minHeap.pop();  // Remove smallest
        }
    }
    
    return minHeap.top();  // Kth largest
}
// Example: [3,2,1,5,6,4], k=2 -> 5


// 2. K CLOSEST POINTS TO ORIGIN
// LeetCode 973 - Use MAX heap of size k (store by distance)
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    auto cmp = [](vector<int>& a, vector<int>& b) {
        return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];  // Max heap
    };
    
    priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> maxHeap(cmp);
    
    for (auto& p : points) {
        maxHeap.push(p);
        if (maxHeap.size() > k) {
            maxHeap.pop();  // Remove farthest
        }
    }
    
    vector<vector<int>> result;
    while (!maxHeap.empty()) {
        result.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return result;
}


// 3. TOP K FREQUENT ELEMENTS
// LeetCode 347
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int n : nums) freq[n]++;
    
    // Min heap by frequency
    auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
        return a.second > b.second;  // Min heap by frequency
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> minHeap(cmp);
    
    for (auto& [num, count] : freq) {
        minHeap.push({num, count});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().first);
        minHeap.pop();
    }
    return result;
}


// 4. MERGE K SORTED LISTS
// LeetCode 23
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;  // Min heap
    };
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> minHeap(cmp);
    
    // Add all list heads
    for (auto list : lists) {
        if (list) minHeap.push(list);
    }
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (!minHeap.empty()) {
        ListNode* smallest = minHeap.top();
        minHeap.pop();
        
        tail->next = smallest;
        tail = tail->next;
        
        if (smallest->next) {
            minHeap.push(smallest->next);
        }
    }
    
    return dummy.next;
}


// 5. FIND MEDIAN FROM DATA STREAM
// LeetCode 295
class MedianFinder {
    priority_queue<int> maxHeap;  // Left half (smaller elements)
    priority_queue<int, vector<int>, greater<int>> minHeap;  // Right half (larger)
    
public:
    void addNum(int num) {
        maxHeap.push(num);
        minHeap.push(maxHeap.top());
        maxHeap.pop();
        
        // Balance: maxHeap can have at most 1 more element
        if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.size() > minHeap.size()) {
            return maxHeap.top();
        }
        return (maxHeap.top() + minHeap.top()) / 2.0;
    }
};


// 6. TASK SCHEDULER (Using heap simulation)
// LeetCode 621
int leastInterval(vector<char>& tasks, int n) {
    vector<int> freq(26, 0);
    for (char c : tasks) freq[c - 'A']++;
    
    priority_queue<int> maxHeap;
    for (int f : freq) {
        if (f > 0) maxHeap.push(f);
    }
    
    int time = 0;
    while (!maxHeap.empty()) {
        vector<int> temp;
        
        // Process n+1 tasks (or as many as possible)
        for (int i = 0; i <= n; i++) {
            if (!maxHeap.empty()) {
                if (maxHeap.top() > 1) {
                    temp.push_back(maxHeap.top() - 1);
                }
                maxHeap.pop();
            }
            time++;
            
            if (maxHeap.empty() && temp.empty()) break;
        }
        
        for (int f : temp) {
            maxHeap.push(f);
        }
    }
    
    return time;
}


// 7. LAST STONE WEIGHT
// LeetCode 1046
int lastStoneWeight(vector<int>& stones) {
    priority_queue<int> maxHeap(stones.begin(), stones.end());
    
    while (maxHeap.size() > 1) {
        int y = maxHeap.top(); maxHeap.pop();
        int x = maxHeap.top(); maxHeap.pop();
        
        if (y != x) {
            maxHeap.push(y - x);
        }
    }
    
    return maxHeap.empty() ? 0 : maxHeap.top();
}


// ============== MAIN - DEMO ==============
int main() {
    basicUsage();
    customComparators();
    structComparator();
    
    // Kth Largest
    cout << "\n=== Interview Problems ===" << endl;
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    cout << "Kth Largest (k=2) in [3,2,1,5,6,4]: " << findKthLargest(nums, 2) << endl;
    
    // Top K Frequent
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    vector<int> topK = topKFrequent(nums2, 2);
    cout << "Top 2 Frequent in [1,1,1,2,2,3]: ";
    for (int x : topK) cout << x << " ";
    cout << endl;
    
    // Last Stone Weight
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    cout << "Last Stone Weight [2,7,4,1,8,1]: " << lastStoneWeight(stones) << endl;
    
    // Median Finder
    cout << "\n--- Median Finder ---" << endl;
    MedianFinder mf;
    mf.addNum(1);
    mf.addNum(2);
    cout << "Median after [1,2]: " << mf.findMedian() << endl;  // 1.5
    mf.addNum(3);
    cout << "Median after [1,2,3]: " << mf.findMedian() << endl;  // 2
    
    return 0;
}

/*
================================================================================
                              CHEAT SHEET
================================================================================

MAX HEAP (default):
  priority_queue<int> maxHeap;

MIN HEAP:
  priority_queue<int, vector<int>, greater<int>> minHeap;

PAIRS (min by first):
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

CUSTOM COMPARATOR:
  auto cmp = [](T& a, T& b) { return a > b; };  // Min heap
  priority_queue<T, vector<T>, decltype(cmp)> pq(cmp);

┌─────────────────────────────────────────────────────────────────────────────┐
│ Problem Type                │ Heap Type        │ Why                        │
├─────────────────────────────┼──────────────────┼────────────────────────────┤
│ Kth Largest                 │ Min heap size k  │ Top is kth largest         │
│ Kth Smallest                │ Max heap size k  │ Top is kth smallest        │
│ Top K Frequent              │ Min heap size k  │ Keep k most frequent       │
│ K Closest Points            │ Max heap size k  │ Keep k closest             │
│ Merge K Lists               │ Min heap         │ Always pick smallest       │
│ Find Median                 │ Two heaps        │ Balance left/right halves  │
└─────────────────────────────┴──────────────────┴────────────────────────────┘

================================================================================
*/

