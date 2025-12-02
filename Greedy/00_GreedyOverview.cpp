/*
================================================================================
                        GREEDY ALGORITHMS - OVERVIEW
================================================================================

Greedy algorithms make locally optimal choices at each step, hoping to find
a global optimum. They work when the problem has:

1. GREEDY CHOICE PROPERTY: A local optimum leads to global optimum
2. OPTIMAL SUBSTRUCTURE: Optimal solution contains optimal solutions to subproblems

Key Question: "What's the best choice RIGHT NOW?"

Time: Usually O(n log n) due to sorting | Space: Usually O(1) or O(n)

================================================================================
                           PATTERN CLASSIFICATION
================================================================================

1. INTERVAL SCHEDULING
   ────────────────────
   Choose intervals/activities to maximize count or minimize conflicts.
   
   Key Insight: Sort by END time, greedily pick non-overlapping.
   
   Problems:
   - Activity Selection / Max Meetings
   - Non-overlapping Intervals
   - Minimum Platforms
   - Merge Intervals
   - Insert Interval

2. ARRAY/SEQUENCE GREEDY
   ──────────────────────
   Process arrays by making local best decisions.
   
   Problems:
   - Jump Game I & II
   - Gas Station
   - Candy Distribution
   - Task Scheduler
   - Assign Cookies
   - Best Time to Buy/Sell Stock II

3. STRING GREEDY
   ──────────────
   Build or modify strings character by character.
   
   Problems:
   - Remove K Digits
   - Remove Duplicate Letters
   - Reorganize String
   - Smallest Subsequence of Distinct Characters

4. TWO POINTERS GREEDY
   ────────────────────
   Use two pointers with greedy choices.
   
   Problems:
   - Container With Most Water
   - Trapping Rain Water
   - Boats to Save People
   - Two City Scheduling

5. HEAP-BASED GREEDY
   ──────────────────
   Use priority queue to always pick best option.
   
   Problems:
   - Merge K Sorted Lists
   - Minimum Cost to Connect Sticks
   - IPO (Capital)
   - Meeting Rooms III
   - Huffman Encoding

6. GRAPH GREEDY
   ─────────────
   MST algorithms, shortest paths with special properties.
   
   Problems:
   - Kruskal's MST
   - Prim's MST
   - Dijkstra's Shortest Path

================================================================================
                           PROVING GREEDY WORKS
================================================================================

1. EXCHANGE ARGUMENT
   - Assume optimal solution differs from greedy
   - Show we can exchange to match greedy without losing optimality

2. GREEDY STAYS AHEAD
   - Show greedy solution is always ≥ any other partial solution
   - By induction, greedy is optimal at the end

3. STRUCTURAL ARGUMENT  
   - Show problem has optimal substructure
   - Show greedy choice is always part of some optimal solution

================================================================================
                           COMMON GREEDY STRATEGIES
================================================================================

1. SORT BY END TIME - Interval scheduling
2. SORT BY START TIME - Merging intervals
3. SORT BY RATIO - Fractional knapsack
4. SORT BY DIFFERENCE - Task assignment
5. ALWAYS PICK MIN/MAX - Heap-based problems
6. EXPAND GREEDILY - Jump game

================================================================================
                           FILE ORGANIZATION
================================================================================

01_IntervalScheduling.cpp   - Activity selection, meeting problems
02_ArraySequence.cpp        - Jump game, gas station, candy
03_StringGreedy.cpp         - Remove digits, reorganize string
04_HeapGreedy.cpp           - Priority queue based greedy
05_TwoPointerGreedy.cpp     - Two pointers with greedy
06_ClassicGreedy.cpp        - Huffman, fractional knapsack, job sequencing

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Quick verification: Does greedy work?
// 1. Can you make a locally optimal choice?
// 2. Does that choice lead to a subproblem of the same type?
// 3. Can you prove exchange argument or greedy-stays-ahead?

int main() {
    cout << "=== Greedy Algorithm Patterns ===" << endl;
    cout << "See individual files for implementations." << endl;
    return 0;
}

