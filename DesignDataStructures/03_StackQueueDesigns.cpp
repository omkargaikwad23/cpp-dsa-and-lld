/*
================================================================================
                    DESIGN - STACK & QUEUE VARIATIONS
================================================================================

Key patterns:
- Min/Max tracking: Auxiliary stack
- Convert between Stack and Queue: Two structures
- Special access patterns: Multiple stacks/queues

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Min Stack (LeetCode 155) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────
Stack that supports getMin() in O(1).

Design: Auxiliary stack storing minimum at each level.

Time: O(1) for all operations | Space: O(n)
*/
class MinStack {
    stack<int> stk;
    stack<int> minStk;
    
public:
    void push(int val) {
        stk.push(val);
        if (minStk.empty() || val <= minStk.top()) {
            minStk.push(val);
        }
    }
    
    void pop() {
        if (stk.top() == minStk.top()) {
            minStk.pop();
        }
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minStk.top();
    }
};

// Space-optimized: Store difference from min
class MinStackOptimized {
    stack<long long> stk;
    long long minVal;
    
public:
    void push(int val) {
        if (stk.empty()) {
            stk.push(0);
            minVal = val;
        } else {
            stk.push(val - minVal);
            minVal = min(minVal, (long long)val);
        }
    }
    
    void pop() {
        if (stk.top() < 0) {
            minVal = minVal - stk.top();  // Restore previous min
        }
        stk.pop();
    }
    
    int top() {
        return stk.top() < 0 ? minVal : stk.top() + minVal;
    }
    
    int getMin() {
        return minVal;
    }
};


/*
PROBLEM 2: Max Stack (LeetCode 716)
───────────────────────────────────
Stack with peekMax() and popMax().

Design: Two stacks or TreeMap + doubly linked list for O(log n) popMax

Time: O(log n) for max operations | Space: O(n)
*/
class MaxStack {
    list<int> stk;
    map<int, vector<list<int>::iterator>> maxMap;  // value → iterators
    
public:
    void push(int x) {
        stk.push_back(x);
        maxMap[x].push_back(prev(stk.end()));
    }
    
    int pop() {
        int val = stk.back();
        maxMap[val].pop_back();
        if (maxMap[val].empty()) maxMap.erase(val);
        stk.pop_back();
        return val;
    }
    
    int top() {
        return stk.back();
    }
    
    int peekMax() {
        return maxMap.rbegin()->first;
    }
    
    int popMax() {
        int maxVal = maxMap.rbegin()->first;
        auto it = maxMap[maxVal].back();
        maxMap[maxVal].pop_back();
        if (maxMap[maxVal].empty()) maxMap.erase(maxVal);
        stk.erase(it);
        return maxVal;
    }
};


/*
PROBLEM 3: Implement Queue using Stacks (LeetCode 232)
──────────────────────────────────────────────────────
FIFO queue using only two stacks.

Design: Input stack and output stack. Transfer on demand.

Time: O(1) amortized | Space: O(n)
*/
class MyQueue {
    stack<int> input, output;
    
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


/*
PROBLEM 4: Implement Stack using Queues (LeetCode 225)
──────────────────────────────────────────────────────
LIFO stack using queues.

Design: Single queue, rotate on push.

Time: O(n) push, O(1) pop | Space: O(n)
*/
class MyStack {
    queue<int> q;
    
public:
    void push(int x) {
        q.push(x);
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


/*
PROBLEM 5: Design Circular Queue (LeetCode 622)
───────────────────────────────────────────────
Fixed-size circular queue.

Time: O(1) for all operations | Space: O(k)
*/
class MyCircularQueue {
    vector<int> data;
    int head, tail, size, capacity;
    
public:
    MyCircularQueue(int k) : data(k), head(0), tail(-1), size(0), capacity(k) {}
    
    bool enQueue(int value) {
        if (isFull()) return false;
        tail = (tail + 1) % capacity;
        data[tail] = value;
        size++;
        return true;
    }
    
    bool deQueue() {
        if (isEmpty()) return false;
        head = (head + 1) % capacity;
        size--;
        return true;
    }
    
    int Front() {
        return isEmpty() ? -1 : data[head];
    }
    
    int Rear() {
        return isEmpty() ? -1 : data[tail];
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == capacity;
    }
};


/*
PROBLEM 6: Design Circular Deque (LeetCode 641)
───────────────────────────────────────────────
Double-ended circular queue.

Time: O(1) for all operations | Space: O(k)
*/
class MyCircularDeque {
    vector<int> data;
    int front, rear, size, capacity;
    
public:
    MyCircularDeque(int k) : data(k), front(0), rear(k-1), size(0), capacity(k) {}
    
    bool insertFront(int value) {
        if (isFull()) return false;
        front = (front - 1 + capacity) % capacity;
        data[front] = value;
        size++;
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) return false;
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
        return true;
    }
    
    bool deleteFront() {
        if (isEmpty()) return false;
        front = (front + 1) % capacity;
        size--;
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) return false;
        rear = (rear - 1 + capacity) % capacity;
        size--;
        return true;
    }
    
    int getFront() {
        return isEmpty() ? -1 : data[front];
    }
    
    int getRear() {
        return isEmpty() ? -1 : data[rear];
    }
    
    bool isEmpty() { return size == 0; }
    bool isFull() { return size == capacity; }
};


/*
PROBLEM 7: Design a Stack With Increment Operation (LeetCode 1381)
──────────────────────────────────────────────────────────────────
Stack with increment(k, val): Add val to bottom k elements.

Design: Lazy propagation - store increments to apply later.

Time: O(1) for all operations | Space: O(n)
*/
class CustomStack {
    vector<int> stack;
    vector<int> inc;  // Lazy increment
    int maxSize;
    
public:
    CustomStack(int maxSize) : maxSize(maxSize), inc(maxSize, 0) {}
    
    void push(int x) {
        if (stack.size() < maxSize) {
            stack.push_back(x);
        }
    }
    
    int pop() {
        if (stack.empty()) return -1;
        
        int idx = stack.size() - 1;
        int val = stack.back() + inc[idx];
        
        // Pass increment to lower element
        if (idx > 0) inc[idx - 1] += inc[idx];
        inc[idx] = 0;
        
        stack.pop_back();
        return val;
    }
    
    void increment(int k, int val) {
        int idx = min(k, (int)stack.size()) - 1;
        if (idx >= 0) inc[idx] += val;
    }
};


/*
PROBLEM 8: Dinner Plate Stacks (LeetCode 1172)
──────────────────────────────────────────────
Multiple stacks of fixed capacity. Push to leftmost, pop from rightmost.

Time: O(log n) | Space: O(n)
*/
class DinnerPlates {
    int capacity;
    vector<stack<int>> stacks;
    set<int> available;  // Indices of non-full stacks
    
public:
    DinnerPlates(int capacity) : capacity(capacity) {}
    
    void push(int val) {
        if (available.empty()) {
            stacks.push_back(stack<int>());
            available.insert(stacks.size() - 1);
        }
        
        int idx = *available.begin();
        stacks[idx].push(val);
        
        if (stacks[idx].size() == capacity) {
            available.erase(idx);
        }
    }
    
    int pop() {
        while (!stacks.empty() && stacks.back().empty()) {
            stacks.pop_back();
        }
        if (stacks.empty()) return -1;
        return popAtStack(stacks.size() - 1);
    }
    
    int popAtStack(int index) {
        if (index >= stacks.size() || stacks[index].empty()) return -1;
        
        int val = stacks[index].top();
        stacks[index].pop();
        available.insert(index);
        
        return val;
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Stack & Queue Designs ===\n\n";
    
    // 1. Min Stack
    MinStack ms;
    ms.push(-2);
    ms.push(0);
    ms.push(-3);
    cout << "1. Min Stack getMin(): " << ms.getMin() << "\n";
    ms.pop();
    cout << "   After pop, getMin(): " << ms.getMin() << "\n";
    
    // 3. Queue using Stacks
    MyQueue mq;
    mq.push(1);
    mq.push(2);
    cout << "3. Queue peek: " << mq.peek() << "\n";
    cout << "   Queue pop: " << mq.pop() << "\n";
    
    // 5. Circular Queue
    MyCircularQueue cq(3);
    cq.enQueue(1);
    cq.enQueue(2);
    cq.enQueue(3);
    cout << "5. Circular queue full: " << (cq.isFull() ? "true" : "false") << "\n";
    cout << "   Front: " << cq.Front() << ", Rear: " << cq.Rear() << "\n";
    
    // 7. Custom Stack with Increment
    CustomStack cs(3);
    cs.push(1);
    cs.push(2);
    cs.increment(5, 100);
    cout << "7. Custom stack pop: " << cs.pop() << "\n";
    cout << "   Custom stack pop: " << cs.pop() << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Design                        | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Min Stack                     | Auxiliary stack for mins                       |
| Max Stack                     | TreeMap + doubly linked list                   |
| Queue using Stacks            | Two stacks, transfer on demand                 |
| Stack using Queues            | Single queue, rotate on push                   |
| Circular Queue                | Array with head/tail pointers mod capacity     |
| Stack with Increment          | Lazy propagation of increments                 |
| Dinner Plates                 | Vector of stacks + set of available indices    |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

