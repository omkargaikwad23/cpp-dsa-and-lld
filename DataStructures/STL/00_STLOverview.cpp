/*
================================================================================
                    C++ STL - OVERVIEW & QUICK REFERENCE
================================================================================

STL (Standard Template Library) provides:
1. CONTAINERS - Store data (vector, map, set, etc.)
2. ALGORITHMS - Operations on data (sort, find, etc.)
3. ITERATORS - Connect containers and algorithms

================================================================================
                         CONTAINER SUMMARY
================================================================================

┌─────────────────────────────────────────────────────────────────────────────┐
│                         SEQUENCE CONTAINERS                                 │
├──────────────┬──────────────┬───────────────────────────────────────────────┤
│ Container    │ Insert/Delete│ Access          │ Use Case                   │
├──────────────┼──────────────┼─────────────────┼────────────────────────────┤
│ vector       │ O(1) end     │ O(1) random     │ Default choice, dynamic arr│
│ deque        │ O(1) both    │ O(1) random     │ Need front insertion       │
│ list         │ O(1) anywhere│ O(n) sequential │ Frequent mid insertions    │
│ array        │ Fixed size   │ O(1) random     │ Fixed size, stack alloc    │
└──────────────┴──────────────┴─────────────────┴────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────┐
│                       ASSOCIATIVE CONTAINERS                                │
├──────────────────┬─────────────┬───────────────────────────────────────────┤
│ Container        │ Complexity  │ Use Case                                  │
├──────────────────┼─────────────┼───────────────────────────────────────────┤
│ set              │ O(log n)    │ Unique sorted elements                    │
│ multiset         │ O(log n)    │ Sorted with duplicates                    │
│ map              │ O(log n)    │ Key-value, sorted keys, range queries     │
│ multimap         │ O(log n)    │ Key-value with duplicate keys             │
├──────────────────┼─────────────┼───────────────────────────────────────────┤
│ unordered_set    │ O(1) avg    │ Fast unique lookup                        │
│ unordered_map    │ O(1) avg    │ Fast key-value lookup (most common!)      │
└──────────────────┴─────────────┴───────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────┐
│                       CONTAINER ADAPTERS                                    │
├──────────────────┬─────────────┬───────────────────────────────────────────┤
│ Container        │ Complexity  │ Use Case                                  │
├──────────────────┼─────────────┼───────────────────────────────────────────┤
│ stack            │ O(1)        │ LIFO - DFS, expression evaluation         │
│ queue            │ O(1)        │ FIFO - BFS, level order                   │
│ priority_queue   │ O(log n)    │ Heap - K largest, merge K lists           │
└──────────────────┴─────────────┴───────────────────────────────────────────┘

================================================================================
                     MOST USED IN INTERVIEWS
================================================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
using namespace std;

/*
================================================================================
                    INTERVIEW ESSENTIALS - QUICK REFERENCE
================================================================================
*/

void vectorEssentials() {
    // === VECTOR ===
    vector<int> v = {3, 1, 4, 1, 5};
    
    // Size & access
    int n = v.size();           // 5
    int first = v[0];           // 3
    int last = v.back();        // 5
    
    // Add/remove
    v.push_back(9);             // Add to end
    v.pop_back();               // Remove from end
    v.insert(v.begin() + 2, 99);// Insert at index 2
    v.erase(v.begin() + 2);     // Remove at index 2
    
    // 2D vector
    vector<vector<int>> grid(3, vector<int>(4, 0));  // 3x4 matrix of zeros
    
    // Common algorithms
    sort(v.begin(), v.end());                    // Sort ascending
    sort(v.begin(), v.end(), greater<int>());    // Sort descending
    reverse(v.begin(), v.end());                 // Reverse
    int sum = accumulate(v.begin(), v.end(), 0); // Sum all
    int maxVal = *max_element(v.begin(), v.end());
    int minVal = *min_element(v.begin(), v.end());
}

void mapEssentials() {
    // === UNORDERED_MAP (most common) ===
    unordered_map<string, int> freq;
    
    // Insert/update
    freq["apple"] = 5;
    freq["banana"]++;          // Creates with 0, then increments
    
    // Check existence
    if (freq.count("apple"))   // Returns 1 if exists, 0 otherwise
    if (freq.find("apple") != freq.end())  // Alternative
    
    // Iterate
    for (auto& [key, val] : freq) {
        cout << key << ": " << val << endl;
    }
    
    // === MAP (sorted) ===
    map<int, string> sorted_map;
    sorted_map[3] = "three";
    sorted_map[1] = "one";
    // Iteration gives: 1->one, 3->three (sorted!)
    
    // Range queries (map only)
    auto it = sorted_map.lower_bound(2);  // First >= 2
    auto it2 = sorted_map.upper_bound(2); // First > 2
}

void setEssentials() {
    // === UNORDERED_SET ===
    unordered_set<int> seen;
    
    seen.insert(5);
    if (seen.count(5))         // Check if exists
    seen.erase(5);             // Remove
    
    // === SET (sorted) ===
    set<int> sorted_set = {3, 1, 4};
    // Contains: 1, 3, 4 (sorted!)
    
    int smallest = *sorted_set.begin();
    int largest = *sorted_set.rbegin();
}

void heapEssentials() {
    // === PRIORITY QUEUE ===
    
    // Max heap (default)
    priority_queue<int> maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    int largest = maxHeap.top();  // 4
    maxHeap.pop();
    
    // Min heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    int smallest = minHeap.top();  // 1
    
    // Custom comparator (for pairs, objects)
    auto cmp = [](pair<int,int>& a, pair<int,int>& b) {
        return a.first > b.first;  // Min heap by first element
    };
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
}

void stackQueueEssentials() {
    // === STACK ===
    stack<int> stk;
    stk.push(1);
    stk.push(2);
    int top = stk.top();   // 2
    stk.pop();
    bool empty = stk.empty();
    
    // === QUEUE ===
    queue<int> q;
    q.push(1);
    q.push(2);
    int front = q.front(); // 1
    q.pop();
}

void stringEssentials() {
    string s = "hello";
    
    // Access
    char first = s[0];
    char last = s.back();
    int len = s.length();  // or s.size()
    
    // Modify
    s += " world";         // Append
    s.push_back('!');      // Append char
    s.pop_back();          // Remove last char
    
    // Substring
    string sub = s.substr(0, 5);  // "hello"
    
    // Find
    size_t pos = s.find("world");
    if (pos != string::npos) { /* found */ }
    
    // Convert
    int num = stoi("123");
    string str = to_string(456);
    
    // Common operations
    reverse(s.begin(), s.end());
    sort(s.begin(), s.end());
    transform(s.begin(), s.end(), s.begin(), ::tolower);
}

/*
================================================================================
                         ALGORITHM CHEAT SHEET
================================================================================

SORTING:
  sort(v.begin(), v.end());                    // Ascending
  sort(v.begin(), v.end(), greater<int>());    // Descending
  sort(v.begin(), v.end(), [](int a, int b) { return a > b; }); // Custom

SEARCHING:
  binary_search(v.begin(), v.end(), x);        // Returns bool
  lower_bound(v.begin(), v.end(), x);          // First >= x
  upper_bound(v.begin(), v.end(), x);          // First > x
  find(v.begin(), v.end(), x);                 // Returns iterator

COUNTING:
  count(v.begin(), v.end(), x);                // Count occurrences
  count_if(v.begin(), v.end(), predicate);     // Count if condition

MIN/MAX:
  *min_element(v.begin(), v.end());
  *max_element(v.begin(), v.end());
  min(a, b), max(a, b);
  minmax_element(v.begin(), v.end());          // Returns pair of iterators

MANIPULATION:
  reverse(v.begin(), v.end());
  rotate(v.begin(), v.begin() + k, v.end());   // Rotate left by k
  unique(v.begin(), v.end());                  // Remove adjacent duplicates
  fill(v.begin(), v.end(), val);               // Fill with value

NUMERIC:
  accumulate(v.begin(), v.end(), 0);           // Sum
  partial_sum(v.begin(), v.end(), out.begin());// Prefix sum
  iota(v.begin(), v.end(), 0);                 // Fill 0,1,2,3...

================================================================================
*/

int main() {
    cout << "=== STL Quick Reference ===" << endl << endl;
    
    // Demo vector
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    
    cout << "Original: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    
    sort(nums.begin(), nums.end());
    cout << "Sorted: ";
    for (int x : nums) cout << x << " ";
    cout << endl;
    
    cout << "Sum: " << accumulate(nums.begin(), nums.end(), 0) << endl;
    cout << "Max: " << *max_element(nums.begin(), nums.end()) << endl;
    cout << "Min: " << *min_element(nums.begin(), nums.end()) << endl;
    
    // Demo map
    cout << "\n--- Frequency Map ---" << endl;
    unordered_map<int, int> freq;
    for (int x : nums) freq[x]++;
    for (auto& [k, v] : freq) {
        cout << k << " appears " << v << " times" << endl;
    }
    
    return 0;
}

/*
================================================================================
                           FILE INDEX
================================================================================

01_vector.cpp          - Dynamic array, 2D vectors
02_string.cpp          - String operations, conversions
03_map_unordered_map.cpp - Hash tables, sorted maps
04_set_unordered_set.cpp - Hash sets, sorted sets
05_priority_queue.cpp  - Heaps, custom comparators
06_algorithms.cpp      - Sort, search, manipulate
07_pair_tuple.cpp      - Pair, tuple, structured bindings
08_stringstream.cpp    - Parsing, formatting strings

================================================================================
*/

