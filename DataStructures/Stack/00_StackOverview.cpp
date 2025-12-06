/*
================================================================================
                          STACK - OVERVIEW
================================================================================

LIFO (Last In, First Out) data structure.
Think of a stack of plates - you can only add/remove from the top.

Operations:
- push(x)   : Add element to top      - O(1)
- pop()     : Remove top element      - O(1)
- top/peek(): View top element        - O(1)
- isEmpty() : Check if empty          - O(1)
- size()    : Get number of elements  - O(1)

================================================================================
                     WHEN TO USE STACK
================================================================================

1. MATCHING PROBLEMS
   - Valid parentheses, brackets
   - HTML/XML tag matching
   
2. REVERSAL PROBLEMS
   - Reverse a string/array
   - Undo operations
   
3. EXPRESSION EVALUATION
   - Infix to postfix conversion
   - Evaluate postfix/prefix
   - Calculator problems
   
4. MONOTONIC STACK (see 02_MonotonicStack.cpp)
   - Next greater/smaller element
   - Largest rectangle in histogram
   - Daily temperatures
   
5. FUNCTION CALL SIMULATION
   - DFS (recursion uses stack internally)
   - Backtracking

================================================================================
                         C++ STL STACK
================================================================================
*/

#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

void stlStackDemo() {
    stack<int> stk;
    
    // Push elements
    stk.push(10);
    stk.push(20);
    stk.push(30);
    
    // Top element
    cout << "Top: " << stk.top() << endl;  // 30
    
    // Size
    cout << "Size: " << stk.size() << endl;  // 3
    
    // Pop
    stk.pop();
    cout << "After pop, Top: " << stk.top() << endl;  // 20
    
    // Check empty
    cout << "Empty? " << (stk.empty() ? "Yes" : "No") << endl;
    
    // Iterate (pop all)
    cout << "All elements: ";
    while (!stk.empty()) {
        cout << stk.top() << " ";
        stk.pop();
    }
    cout << endl;
}

/*
================================================================================
                    STACK IMPLEMENTATIONS
================================================================================
*/

// 1. ARRAY-BASED STACK (Fixed Size)
class ArrayStack {
private:
    int* arr;
    int topIdx;
    int capacity;
    
public:
    ArrayStack(int size = 100) {
        capacity = size;
        arr = new int[capacity];
        topIdx = -1;
    }
    
    ~ArrayStack() { delete[] arr; }
    
    void push(int val) {
        if (topIdx >= capacity - 1) {
            cout << "Stack Overflow!" << endl;
            return;
        }
        arr[++topIdx] = val;
    }
    
    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return -1;
        }
        return arr[topIdx--];
    }
    
    int top() {
        if (isEmpty()) return -1;
        return arr[topIdx];
    }
    
    bool isEmpty() { return topIdx == -1; }
    int size() { return topIdx + 1; }
};


// 2. DYNAMIC ARRAY STACK (Vector-based)
class DynamicStack {
private:
    vector<int> arr;
    
public:
    void push(int val) {
        arr.push_back(val);
    }
    
    int pop() {
        if (isEmpty()) return -1;
        int val = arr.back();
        arr.pop_back();
        return val;
    }
    
    int top() {
        if (isEmpty()) return -1;
        return arr.back();
    }
    
    bool isEmpty() { return arr.empty(); }
    int size() { return arr.size(); }
};


// 3. LINKED LIST STACK
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class LinkedStack {
private:
    ListNode* head;
    int count;
    
public:
    LinkedStack() : head(nullptr), count(0) {}
    
    ~LinkedStack() {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void push(int val) {
        ListNode* node = new ListNode(val);
        node->next = head;
        head = node;
        count++;
    }
    
    int pop() {
        if (isEmpty()) return -1;
        int val = head->val;
        ListNode* temp = head;
        head = head->next;
        delete temp;
        count--;
        return val;
    }
    
    int top() {
        if (isEmpty()) return -1;
        return head->val;
    }
    
    bool isEmpty() { return head == nullptr; }
    int size() { return count; }
};

/*
================================================================================
                     PATTERN CLASSIFICATION
================================================================================

1. BASIC STACK PROBLEMS (01_BasicProblems.cpp)
   ─────────────────────────────────────────────
   - Valid Parentheses (LC 20)
   - Min Stack (LC 155)
   - Implement Queue using Stacks (LC 232)
   - Implement Stack using Queues (LC 225)
   - Simplify Path (LC 71)
   - Decode String (LC 394)
   - Remove All Adjacent Duplicates (LC 1047)
   - Baseball Game (LC 682)

2. MONOTONIC STACK (02_MonotonicStack.cpp) ⭐
   ─────────────────────────────────────────────
   - Next Greater Element (LC 496, 503)
   - Daily Temperatures (LC 739)
   - Stock Span (LC 901)
   - Largest Rectangle in Histogram (LC 84)
   - Trapping Rain Water (LC 42)
   - Sum of Subarray Minimums (LC 907)
   - Remove K Digits (LC 402)

3. EXPRESSION EVALUATION (03_ExpressionEvaluation.cpp)
   ─────────────────────────────────────────────────────
   - Evaluate Reverse Polish Notation (LC 150)
   - Basic Calculator (LC 224)
   - Basic Calculator II (LC 227)
   - Infix to Postfix Conversion
   - Expression with Parentheses

================================================================================
*/

int main() {
    cout << "=== Stack Overview ===" << endl << endl;
    
    // STL Stack Demo
    cout << "--- STL Stack Demo ---" << endl;
    stlStackDemo();
    
    // Array Stack Demo
    cout << "\n--- Array Stack Demo ---" << endl;
    ArrayStack arrStk(10);
    arrStk.push(1);
    arrStk.push(2);
    arrStk.push(3);
    cout << "Top: " << arrStk.top() << endl;
    cout << "Pop: " << arrStk.pop() << endl;
    cout << "Size: " << arrStk.size() << endl;
    
    // Linked Stack Demo
    cout << "\n--- Linked Stack Demo ---" << endl;
    LinkedStack linkStk;
    linkStk.push(10);
    linkStk.push(20);
    linkStk.push(30);
    cout << "Top: " << linkStk.top() << endl;
    cout << "Pop: " << linkStk.pop() << endl;
    cout << "Size: " << linkStk.size() << endl;
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

┌────────────────────┬────────────────┬────────────────────────────────────────┐
│ Implementation     │ Pros           │ Cons                                   │
├────────────────────┼────────────────┼────────────────────────────────────────┤
│ Array (fixed)      │ Simple, fast   │ Fixed size, overflow possible          │
│ Vector (dynamic)   │ Auto-resize    │ Occasional O(n) resize                 │
│ Linked List        │ True O(1)      │ Extra memory for pointers              │
└────────────────────┴────────────────┴────────────────────────────────────────┘

In interviews, just use stack<int> stk; from STL!

COMMON MISTAKES:
1. Forgetting to check empty() before top()/pop()
2. Off-by-one errors in index-based implementation
3. Not handling stack overflow in fixed-size array

================================================================================
*/

