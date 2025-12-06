/*
================================================================================
                          QUEUE - OVERVIEW
================================================================================

FIFO (First In, First Out) data structure.
Think of a line at a ticket counter - first person in line is served first.

Operations:
- push/enqueue(x) : Add element to back     - O(1)
- pop/dequeue()   : Remove front element    - O(1)
- front()         : View front element      - O(1)
- back()          : View back element       - O(1)
- isEmpty()       : Check if empty          - O(1)
- size()          : Get number of elements  - O(1)

================================================================================
                     QUEUE TYPES
================================================================================

1. SIMPLE QUEUE
   - Basic FIFO queue
   - Insert at rear, remove from front

2. CIRCULAR QUEUE
   - Fixed size, wraps around
   - Efficient use of array space

3. DEQUE (Double-Ended Queue)
   - Insert/remove from both ends
   - Used in Sliding Window Maximum

4. PRIORITY QUEUE
   - Elements ordered by priority
   - Implemented with heap (see Heap folder)

================================================================================
                     WHEN TO USE QUEUE
================================================================================

1. BFS (Breadth-First Search)
   - Level-order traversal
   - Shortest path in unweighted graph

2. SLIDING WINDOW PROBLEMS
   - Sliding Window Maximum (monotonic deque)
   - Moving Average

3. TASK SCHEDULING
   - Round-robin scheduling
   - Process queue

4. CACHING
   - LRU Cache (with doubly linked list)
   - FIFO Cache

5. RATE LIMITING
   - Fixed window counter
   - Sliding window log

================================================================================
                         C++ STL QUEUE
================================================================================
*/

#include <iostream>
#include <queue>
#include <deque>
#include <vector>
using namespace std;

void stlQueueDemo() {
    // Basic Queue
    queue<int> q;
    
    q.push(10);
    q.push(20);
    q.push(30);
    
    cout << "Front: " << q.front() << endl;  // 10
    cout << "Back: " << q.back() << endl;    // 30
    cout << "Size: " << q.size() << endl;    // 3
    
    q.pop();  // Remove 10
    cout << "After pop, Front: " << q.front() << endl;  // 20
    
    // Deque (Double-ended queue)
    deque<int> dq;
    
    dq.push_back(1);   // [1]
    dq.push_front(2);  // [2, 1]
    dq.push_back(3);   // [2, 1, 3]
    
    cout << "\nDeque front: " << dq.front() << endl;  // 2
    cout << "Deque back: " << dq.back() << endl;      // 3
    
    dq.pop_front();  // [1, 3]
    dq.pop_back();   // [1]
}

/*
================================================================================
                    QUEUE IMPLEMENTATIONS
================================================================================
*/

// 1. ARRAY-BASED QUEUE (Simple, not circular)
class SimpleQueue {
private:
    int* arr;
    int frontIdx, rearIdx;
    int capacity;
    
public:
    SimpleQueue(int size = 100) {
        capacity = size;
        arr = new int[capacity];
        frontIdx = 0;
        rearIdx = -1;
    }
    
    ~SimpleQueue() { delete[] arr; }
    
    void push(int val) {
        if (rearIdx >= capacity - 1) {
            cout << "Queue Overflow!" << endl;
            return;
        }
        arr[++rearIdx] = val;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Queue Underflow!" << endl;
            return -1;
        }
        return arr[frontIdx++];
    }
    
    int front() {
        if (isEmpty()) return -1;
        return arr[frontIdx];
    }
    
    bool isEmpty() { return frontIdx > rearIdx; }
    int size() { return rearIdx - frontIdx + 1; }
};


// 2. CIRCULAR QUEUE
// LeetCode: 622. Design Circular Queue
class MyCircularQueue {
private:
    vector<int> arr;
    int frontIdx, rearIdx;
    int count, capacity;
    
public:
    MyCircularQueue(int k) {
        arr.resize(k);
        capacity = k;
        frontIdx = 0;
        rearIdx = -1;
        count = 0;
    }
    
    bool enQueue(int value) {
        if (isFull()) return false;
        rearIdx = (rearIdx + 1) % capacity;  // Wrap around
        arr[rearIdx] = value;
        count++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        frontIdx = (frontIdx + 1) % capacity;  // Wrap around
        count--;
        return true;
    }
    
    int Front() {
        if (isEmpty()) return -1;
        return arr[frontIdx];
    }
    
    int Rear() {
        if (isEmpty()) return -1;
        return arr[rearIdx];
    }
    
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
};


// 3. LINKED LIST QUEUE
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedQueue {
private:
    ListNode* head;  // Front
    ListNode* tail;  // Rear
    int count;
    
public:
    LinkedQueue() : head(nullptr), tail(nullptr), count(0) {}
    
    ~LinkedQueue() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void push(int val) {
        ListNode* node = new ListNode(val);
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        count++;
    }
    
    int pop() {
        if (isEmpty()) return -1;
        int val = head->val;
        ListNode* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        count--;
        return val;
    }
    
    int front() {
        if (isEmpty()) return -1;
        return head->val;
    }
    
    int back() {
        if (isEmpty()) return -1;
        return tail->val;
    }
    
    bool isEmpty() { return count == 0; }
    int size() { return count; }
};


// 4. CIRCULAR DEQUE
// LeetCode: 641. Design Circular Deque
class MyCircularDeque {
private:
    vector<int> arr;
    int frontIdx, rearIdx;
    int count, capacity;
    
public:
    MyCircularDeque(int k) {
        arr.resize(k);
        capacity = k;
        frontIdx = 0;
        rearIdx = k - 1;
        count = 0;
    }
    
    bool insertFront(int value) {
        if (isFull()) return false;
        frontIdx = (frontIdx - 1 + capacity) % capacity;
        arr[frontIdx] = value;
        count++;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        rearIdx = (rearIdx + 1) % capacity;
        arr[rearIdx] = value;
        count++;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;
        frontIdx = (frontIdx + 1) % capacity;
        count--;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        rearIdx = (rearIdx - 1 + capacity) % capacity;
        count--;
        return true;
    }
    
    int getFront() {
        if (isEmpty()) return -1;
        return arr[frontIdx];
    }
    
    int getRear() {
        if (isEmpty()) return -1;
        return arr[rearIdx];
    }
    
    bool isEmpty() { return count == 0; }
    bool isFull() { return count == capacity; }
};


/*
================================================================================
                     PATTERN CLASSIFICATION
================================================================================

1. BASIC PROBLEMS (01_BasicProblems.cpp)
   ─────────────────────────────────────────
   - Implement Stack using Queues (LC 225)
   - Implement Queue using Stacks (LC 232)
   - Moving Average from Data Stream (LC 346)
   - Recent Counter (LC 933)
   - Number of Recent Calls

2. MONOTONIC DEQUE (02_MonotonicDeque.cpp) ⭐
   ─────────────────────────────────────────────
   - Sliding Window Maximum (LC 239)
   - Shortest Subarray with Sum >= K (LC 862)
   - Jump Game VI (LC 1696)
   - Constrained Subsequence Sum (LC 1425)

3. BFS PATTERNS (see GraphTheory/01_bfs.cpp)
   ─────────────────────────────────────────────
   - Level Order Traversal
   - Shortest Path
   - Rotting Oranges (LC 994)
   - Word Ladder (LC 127)

================================================================================
*/

int main() {
    cout << "=== Queue Overview ===" << endl << endl;
    
    // STL Queue Demo
    cout << "--- STL Queue Demo ---" << endl;
    stlQueueDemo();
    
    // Circular Queue Demo
    cout << "\n--- Circular Queue Demo ---" << endl;
    MyCircularQueue cq(3);
    cout << "Enqueue 1: " << cq.enQueue(1) << endl;
    cout << "Enqueue 2: " << cq.enQueue(2) << endl;
    cout << "Enqueue 3: " << cq.enQueue(3) << endl;
    cout << "Enqueue 4 (full): " << cq.enQueue(4) << endl;
    cout << "Rear: " << cq.Rear() << endl;
    cout << "Is Full: " << cq.isFull() << endl;
    cout << "Dequeue: " << cq.deQueue() << endl;
    cout << "Enqueue 4: " << cq.enQueue(4) << endl;
    cout << "Rear: " << cq.Rear() << endl;
    
    // Linked Queue Demo
    cout << "\n--- Linked Queue Demo ---" << endl;
    LinkedQueue lq;
    lq.push(10);
    lq.push(20);
    lq.push(30);
    cout << "Front: " << lq.front() << endl;
    cout << "Back: " << lq.back() << endl;
    cout << "Pop: " << lq.pop() << endl;
    cout << "Front after pop: " << lq.front() << endl;
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

┌────────────────────┬───────────────┬─────────────────────────────────────────┐
│ Type               │ Operations    │ Use Case                                │
├────────────────────┼───────────────┼─────────────────────────────────────────┤
│ Simple Queue       │ FIFO          │ BFS, task scheduling                    │
│ Circular Queue     │ FIFO (wrap)   │ Fixed-size buffer, round-robin          │
│ Deque              │ Both ends     │ Sliding window max, palindrome check    │
│ Priority Queue     │ By priority   │ Dijkstra, K largest, merge K lists      │
└────────────────────┴───────────────┴─────────────────────────────────────────┘

CIRCULAR QUEUE INDEX FORMULAS:
- Next index: (i + 1) % capacity
- Previous index: (i - 1 + capacity) % capacity

================================================================================
*/

