# 📚 DSA & System Design Interview Prep

A comprehensive collection of Data Structures, Algorithms, and LeetCode patterns organized for coding interview preparation.

---

## 🗂️ Quick Navigation

| Category | Description |
|----------|-------------|
| [Sliding Window & Two Pointers](#-sliding-window--two-pointers) | Array/String optimization patterns |
| [Binary Search](#-binary-search) | Search patterns and variations |
| [Dynamic Programming](#-dynamic-programming) | 20 essential DP patterns |
| [Backtracking](#-backtracking) | Subsets, permutations, combinations |
| [Graph Theory](#-graph-theory) | BFS, DFS, shortest paths, MST |
| [Trees](#-trees) | Traversals, BST, LCA, construction |
| [Greedy](#-greedy) | Interval scheduling, heap problems |
| [Prefix Sum](#-prefix-sum) | Range queries, 2D prefix sum |
| [Line Sweep](#-line-sweep) | Interval, skyline, calendar problems |
| [Bit Manipulation](#-bit-manipulation) | XOR tricks, bitmasks |
| [Classic Algorithms](#-classic-algorithms) | Boyer-Moore, Floyd, QuickSelect |
| [Design Data Structures](#-design-data-structures) | LRU Cache, HashMap, Iterators |
| [Data Structures](#-data-structures) | Stack, Queue, LinkedList, STL |
| [Low Level Design](#-low-level-design-lld) | OOP design problems |

---

## 📁 Sliding Window & Two Pointers

Efficient O(n) techniques for array/string problems.

| File | Topics |
|------|--------|
| [00_PatternsOverview.cpp](SlidingWindowTwoPointer/00_PatternsOverview.cpp) | Pattern classification & templates |
| [01_FixedWindowSize.cpp](SlidingWindowTwoPointer/01_FixedWindowSize.cpp) | Max sum of size K, Anagrams, Permutation in String |
| [02_VariableWindowLongest.cpp](SlidingWindowTwoPointer/02_VariableWindowLongest.cpp) | Longest Substring Without Repeating, K Distinct Chars |
| [03_VariableWindowShortest.cpp](SlidingWindowTwoPointer/03_VariableWindowShortest.cpp) | Minimum Window Substring, Min Size Subarray Sum |
| [04_TwoPointersOpposite.cpp](SlidingWindowTwoPointer/04_TwoPointersOpposite.cpp) | Two Sum Sorted, Container With Most Water, 3Sum |
| [05_TwoPointersSameDirection.cpp](SlidingWindowTwoPointer/05_TwoPointersSameDirection.cpp) | Remove Duplicates, Move Zeroes, Merge Sorted |
| [06_SlidingWindowWithMap.cpp](SlidingWindowTwoPointer/06_SlidingWindowWithMap.cpp) | Frequency tracking, Subarrays with K Different |
| [07_AdvancedProblems.cpp](SlidingWindowTwoPointer/07_AdvancedProblems.cpp) | Advanced sliding window problems |

---

## 🔍 Binary Search

Search in O(log n) time with various patterns.

| File | Topics |
|------|--------|
| [00_BinarySearchOverview.cpp](BinarySearch/00_BinarySearchOverview.cpp) | Templates, when to use, common patterns |
| [01_ClassicPatterns.cpp](BinarySearch/01_ClassicPatterns.cpp) | Lower/Upper Bound, Search Insert Position |
| [02_RotatedArray.cpp](BinarySearch/02_RotatedArray.cpp) | Search in Rotated Array, Find Minimum |
| [03_SearchOnAnswer.cpp](BinarySearch/03_SearchOnAnswer.cpp) | Koko Eating Bananas, Capacity to Ship Packages |
| [04_MatrixSearch.cpp](BinarySearch/04_MatrixSearch.cpp) | Search 2D Matrix, Kth Smallest in Sorted Matrix |
| [05_AdvancedProblems.cpp](BinarySearch/05_AdvancedProblems.cpp) | Median of Two Arrays, Split Array Largest Sum |

---

## 🧩 Dynamic Programming

20 essential DP patterns for interviews.

| Pattern | File | Key Problems |
|---------|------|--------------|
| Overview | [00_DPOverview.cpp](DynamicProgramming/00_DPOverview.cpp) | Pattern guide, when to use DP |
| Fibonacci | [01_Fibonacci/](DynamicProgramming/01_Fibonacci/) | Climbing Stairs, House Robber |
| Kadane's | [02_Kadane/](DynamicProgramming/02_Kadane/) | Max Subarray, Max Product Subarray |
| 0/1 Knapsack | [03_01Knapsack/](DynamicProgramming/03_01Knapsack/) | Partition Equal Subset, Target Sum |
| Unbounded Knapsack | [04_UnboundedKnapsack/](DynamicProgramming/04_UnboundedKnapsack/) | Coin Change, Perfect Squares |
| LCS | [05_LCS/](DynamicProgramming/05_LCS/) | Longest Common Subsequence |
| LIS | [06_LIS/](DynamicProgramming/06_LIS/) | Longest Increasing Subsequence, Russian Doll |
| Palindrome | [07_Palindrome/](DynamicProgramming/07_Palindrome/) | Longest Palindromic Subsequence |
| Edit Distance | [08_EditDistance/](DynamicProgramming/08_EditDistance/) | Edit Distance, Wildcard Matching, Regex |
| Subset Sum | [09_SubsetSum/](DynamicProgramming/09_SubsetSum/) | Subset Sum, Partition Equal |
| String Partition | [10_StringPartition/](DynamicProgramming/10_StringPartition/) | Word Break, Palindrome Partitioning |
| Catalan Numbers | [11_CatalanNumbers/](DynamicProgramming/11_CatalanNumbers/) | Unique BSTs, Generate Parentheses |
| Matrix Chain | [12_MatrixChainMultiplication/](DynamicProgramming/12_MatrixChainMultiplication/) | Burst Balloons, Merge Stones |
| Count Ways | [13_CountDistinctWays/](DynamicProgramming/13_CountDistinctWays/) | Decode Ways, Count Texts |
| DP on Grids | [14_DPOnGrids/](DynamicProgramming/14_DPOnGrids/) | Unique Paths, Min Path Sum |
| DP on Trees | [15_DPOnTrees/](DynamicProgramming/15_DPOnTrees/) | House Robber III, Tree Cameras |
| DP on Graphs | [16_DPOnGraphs/](DynamicProgramming/16_DPOnGraphs/) | Cheapest Flights K Stops |
| Digit DP | [17_DigitDP/](DynamicProgramming/17_DigitDP/) | Numbers with Unique Digits |
| Bitmask DP | [18_BitmaskDP/](DynamicProgramming/18_BitmaskDP/) | TSP, Shortest Path All Nodes |
| Probability DP | [19_ProbabilityDP/](DynamicProgramming/19_ProbabilityDP/) | Knight Probability |
| State Machine | [20_StateMachineDP/](DynamicProgramming/20_StateMachineDP/) | Stock Buy Sell with Cooldown |

---

## 🔄 Backtracking

Generate all solutions by try → explore → undo.

| File | Topics |
|------|--------|
| [00_BacktrackingOverview.cpp](Backtracking/00_BacktrackingOverview.cpp) | Core template, pattern classification |
| [01_SubsetsPatterns.cpp](Backtracking/01_SubsetsPatterns.cpp) | Subsets, Subsets II, Power Set |
| [02_Permutations.cpp](Backtracking/02_Permutations.cpp) | Permutations, Permutations II |
| [03_CombinationSum.cpp](Backtracking/03_CombinationSum.cpp) | Combination Sum I/II/III/IV |
| [04_Partitioning.cpp](Backtracking/04_Partitioning.cpp) | Palindrome Partitioning, Equal Sum Partition |
| [05_GridBoard.cpp](Backtracking/05_GridBoard.cpp) | N-Queens, Sudoku Solver, Word Search |
| [06_GenerateSequences.cpp](Backtracking/06_GenerateSequences.cpp) | Generate Parentheses, Letter Combinations |

---

## 🌐 Graph Theory

BFS, DFS, shortest paths, MST, and advanced graph algorithms.

| File | Topics |
|------|--------|
| [00_GraphOverview.cpp](GraphTheory/00_GraphOverview.cpp) | Graph representations, when to use what |
| [01_bfs.cpp](GraphTheory/01_bfs.cpp) | BFS traversal, shortest path in unweighted |
| [02_dfs.cpp](GraphTheory/02_dfs.cpp) | DFS traversal, cycle detection |
| [03_union_find.cpp](GraphTheory/03_union_find.cpp) | Union-Find, connected components |
| [04_topological_sort.cpp](GraphTheory/04_topological_sort.cpp) | Kahn's algorithm, DFS topo sort |
| [05_dijkstra.cpp](GraphTheory/05_dijkstra.cpp) | Single source shortest path (positive weights) |
| [06_bellman_ford.cpp](GraphTheory/06_bellman_ford.cpp) | Shortest path with negative weights |
| [07_floyd_warshall.cpp](GraphTheory/07_floyd_warshall.cpp) | All pairs shortest path |
| [08_mst.cpp](GraphTheory/08_mst.cpp) | Prim's, Kruskal's MST |
| [09_scc.cpp](GraphTheory/09_scc.cpp) | Strongly Connected Components |
| [10_articulation_bridges.cpp](GraphTheory/10_articulation_bridges.cpp) | Cut vertices, bridges |
| [11_bipartite.cpp](GraphTheory/11_bipartite.cpp) | Bipartite check, graph coloring |

**Additional:**
- [FenwickTree/](GraphTheory/FenwickTree/) - Binary Indexed Tree
- [Trie/](GraphTheory/Trie/) - Prefix tree problems
- [ShortestPath/](GraphTheory/ShortestPath/) - More shortest path problems

---

## 🌳 Trees

Binary trees, BST, traversals, and tree algorithms.

| File | Topics |
|------|--------|
| [00_TreeOverview.cpp](Trees/00_TreeOverview.cpp) | Tree basics, representations |
| [01_Traversals.cpp](Trees/01_Traversals.cpp) | Inorder, Preorder, Postorder, Level Order |
| [02_BinaryTreeBasics.cpp](Trees/02_BinaryTreeBasics.cpp) | Max Depth, Same Tree, Invert Tree |
| [03_BST_Operations.cpp](Trees/03_BST_Operations.cpp) | Insert, Delete, Search, Validate BST |
| [04_TreeConstruction.cpp](Trees/04_TreeConstruction.cpp) | Build from Inorder+Preorder/Postorder |
| [05_LCA_Ancestors.cpp](Trees/05_LCA_Ancestors.cpp) | Lowest Common Ancestor, Kth Ancestor |
| [06_PathProblems.cpp](Trees/06_PathProblems.cpp) | Path Sum, Max Path Sum, Diameter |
| [07_TreeViews.cpp](Trees/07_TreeViews.cpp) | Left/Right/Top/Bottom View |
| [08_TreeTransformations.cpp](Trees/08_TreeTransformations.cpp) | Flatten, Serialize/Deserialize |

---

## 💰 Greedy

Make locally optimal choices for global optimum.

| File | Topics |
|------|--------|
| [00_GreedyOverview.cpp](Greedy/00_GreedyOverview.cpp) | When to use greedy, proof techniques |
| [01_IntervalScheduling.cpp](Greedy/01_IntervalScheduling.cpp) | Meeting Rooms, Non-overlapping Intervals |
| [02_ArraySequence.cpp](Greedy/02_ArraySequence.cpp) | Jump Game, Gas Station |
| [03_StringGreedy.cpp](Greedy/03_StringGreedy.cpp) | Remove K Digits, Monotonic String |
| [04_HeapGreedy.cpp](Greedy/04_HeapGreedy.cpp) | Task Scheduler, Reorganize String |
| [05_ClassicGreedy.cpp](Greedy/05_ClassicGreedy.cpp) | Fractional Knapsack, Activity Selection |

---

## ➕ Prefix Sum

Range queries in O(1) after O(n) preprocessing.

| File | Topics |
|------|--------|
| [00_PrefixSumOverview.cpp](PrefixSum/00_PrefixSumOverview.cpp) | Templates, when to use |
| [01_1DPrefixSum.cpp](PrefixSum/01_1DPrefixSum.cpp) | Range Sum Query, Subarray Sum Equals K |
| [02_2DPrefixSum.cpp](PrefixSum/02_2DPrefixSum.cpp) | Matrix Region Sum, Maximal Square |
| [03_PrefixWithHashMap.cpp](PrefixSum/03_PrefixWithHashMap.cpp) | Subarray Sum Divisible by K |
| [04_DifferenceArray.cpp](PrefixSum/04_DifferenceArray.cpp) | Range Update in O(1) |
| [05_AdvancedPrefix.cpp](PrefixSum/05_AdvancedPrefix.cpp) | XOR prefix, Product prefix |

---

## 📏 Line Sweep

Process events in sorted order.

| File | Topics |
|------|--------|
| [00_LineSweepOverview.cpp](LineSweep/00_LineSweepOverview.cpp) | Event-based processing template |
| [01_IntervalProblems.cpp](LineSweep/01_IntervalProblems.cpp) | Merge Intervals, Insert Interval |
| [02_DifferenceArray.cpp](LineSweep/02_DifferenceArray.cpp) | Range additions |
| [03_SkylineProblems.cpp](LineSweep/03_SkylineProblems.cpp) | The Skyline Problem |
| [04_CalendarProblems.cpp](LineSweep/04_CalendarProblems.cpp) | Meeting Rooms II, My Calendar |
| [05_GeometricSweep.cpp](LineSweep/05_GeometricSweep.cpp) | Rectangle overlap, coverage |

---

## 🔢 Bit Manipulation

Low-level operations for efficient solutions.

| File | Topics |
|------|--------|
| [00_BitManipOverview.cpp](BitManipulation/00_BitManipOverview.cpp) | Bit operations cheat sheet |
| [01_BasicOperations.cpp](BitManipulation/01_BasicOperations.cpp) | Set, Clear, Toggle, Check bits |
| [02_XORTricks.cpp](BitManipulation/02_XORTricks.cpp) | Single Number, Missing Number |
| [03_CountingBits.cpp](BitManipulation/03_CountingBits.cpp) | Count 1s, Power of 2, Hamming Distance |
| [04_SubsetsBitmask.cpp](BitManipulation/04_SubsetsBitmask.cpp) | Generate subsets using bitmask |
| [05_BitTricks.cpp](BitManipulation/05_BitTricks.cpp) | Swap, Reverse bits, Gray code |

---

## 🎯 Classic Algorithms

Must-know algorithms for interviews.

| File | Algorithm |
|------|-----------|
| [01_BoyerMooreMajority.cpp](ClassicAlgorithms/01_BoyerMooreMajority.cpp) | Majority Element in O(1) space |
| [02_DutchNationalFlag.cpp](ClassicAlgorithms/02_DutchNationalFlag.cpp) | Sort Colors (3-way partition) |
| [03_FloydCycleDetection.cpp](ClassicAlgorithms/03_FloydCycleDetection.cpp) | Detect cycle, find cycle start |
| [04_QuickSelect.cpp](ClassicAlgorithms/04_QuickSelect.cpp) | Kth largest in O(n) average |
| [05_ReservoirSampling.cpp](ClassicAlgorithms/05_ReservoirSampling.cpp) | Random sampling from stream |
| [06_KMPPatternMatch.cpp](ClassicAlgorithms/06_KMPPatternMatch.cpp) | String pattern matching O(n+m) |
| [07_SieveOfEratosthenes.cpp](ClassicAlgorithms/07_SieveOfEratosthenes.cpp) | Find all primes up to n |
| [08_FastExponentiation.cpp](ClassicAlgorithms/08_FastExponentiation.cpp) | Power in O(log n) |
| [09_EuclideanGCD.cpp](ClassicAlgorithms/09_EuclideanGCD.cpp) | GCD, Extended Euclidean |
| [10_FisherYatesShuffle.cpp](ClassicAlgorithms/10_FisherYatesShuffle.cpp) | Fair random shuffle |
| [11_MorrisTraversal.cpp](ClassicAlgorithms/11_MorrisTraversal.cpp) | Tree traversal O(1) space |

---

## 🏗️ Design Data Structures

Custom data structure design problems.

| File | Problems |
|------|----------|
| [00_DesignOverview.cpp](DesignDataStructures/00_DesignOverview.cpp) | Design patterns overview |
| [01_CacheDesigns.cpp](DesignDataStructures/01_CacheDesigns.cpp) | LRU Cache, LFU Cache |
| [02_HashMapDesigns.cpp](DesignDataStructures/02_HashMapDesigns.cpp) | Design HashMap, HashSet |
| [03_StackQueueDesigns.cpp](DesignDataStructures/03_StackQueueDesigns.cpp) | Min Stack, Queue using Stacks |
| [04_IteratorPatterns.cpp](DesignDataStructures/04_IteratorPatterns.cpp) | Flatten Iterator, Peeking Iterator |
| [05_TimeBasedDesigns.cpp](DesignDataStructures/05_TimeBasedDesigns.cpp) | Time-Based Key-Value Store |
| [06_AdvancedDesigns.cpp](DesignDataStructures/06_AdvancedDesigns.cpp) | Twitter, File System |
| [07_DesignSpellChecker.cpp](DesignDataStructures/07_DesignSpellChecker.cpp) | Spell Checker design |

---

## 📦 Data Structures

Fundamental data structures and STL.

### Stack
| File | Topics |
|------|--------|
| [00_StackOverview.cpp](DataStructures/Stack/00_StackOverview.cpp) | Stack basics |
| [01_BasicProblems.cpp](DataStructures/Stack/01_BasicProblems.cpp) | Valid Parentheses, Daily Temperatures |
| [02_MonotonicStack.cpp](DataStructures/Stack/02_MonotonicStack.cpp) | Next Greater Element, Largest Rectangle |
| [03_ExpressionEvaluation.cpp](DataStructures/Stack/03_ExpressionEvaluation.cpp) | Calculator, Postfix Evaluation |

### Queue
| File | Topics |
|------|--------|
| [00_QueueOverview.cpp](DataStructures/Queue/00_QueueOverview.cpp) | Queue basics |
| [01_BasicProblems.cpp](DataStructures/Queue/01_BasicProblems.cpp) | BFS applications |
| [02_MonotonicDeque.cpp](DataStructures/Queue/02_MonotonicDeque.cpp) | Sliding Window Maximum |

### Linked List
| File | Topics |
|------|--------|
| [00_LinkedListOverview.cpp](DataStructures/LinkedList/00_LinkedListOverview.cpp) | LinkedList basics |
| [01_BasicOperations.cpp](DataStructures/LinkedList/01_BasicOperations.cpp) | Insert, Delete, Reverse |
| [02_TwoPointerTechniques.cpp](DataStructures/LinkedList/02_TwoPointerTechniques.cpp) | Cycle detection, Middle node |
| [03_ReverseProblems.cpp](DataStructures/LinkedList/03_ReverseProblems.cpp) | Reverse in groups, Palindrome |
| [04_MergeSortOperations.cpp](DataStructures/LinkedList/04_MergeSortOperations.cpp) | Merge K lists, Sort list |

### Sorting Algorithms
[DataStructures/Sortings/](DataStructures/Sortings/) - Bubble, Selection, Insertion, Merge, Quick, Heap, Radix, Counting Sort

### STL Reference
| File | Topics |
|------|--------|
| [00_STLOverview.cpp](DataStructures/STL/00_STLOverview.cpp) | STL containers overview |
| [01_vector.cpp](DataStructures/STL/01_vector.cpp) | Vector operations |
| [02_string.cpp](DataStructures/STL/02_string.cpp) | String operations |
| [03_map.cpp](DataStructures/STL/03_map.cpp) | Ordered map |
| [04_unordered_map.cpp](DataStructures/STL/04_unordered_map.cpp) | Hash map |
| [05_priority_queue.cpp](DataStructures/STL/05_priority_queue.cpp) | Heap operations |
| [06_algorithms.cpp](DataStructures/STL/06_algorithms.cpp) | sort, lower_bound, etc. |

---

## 🎨 Low Level Design (LLD)

Object-oriented design problems.

| File | Problem |
|------|---------|
| [TicTakToe.cpp](LLD/TicTakToe.cpp) | Tic Tac Toe game |
| [SnakeLadder.cpp](LLD/SnakeLadder.cpp) | Snake and Ladder game |
| [event_booking_system.cpp](LLD/event_booking_system.cpp) | Event venue booking |
| [eQ_battleship.cpp](LLD/eQ_battleship.cpp) | Battleship game |

---

## ⏱️ Time Complexity Reference

See [TimeComplexities.md](TimeComplexities.md) for complexity analysis of common operations.

---

## 💡 Interview Tips

```
1. Understand the Problem → Rephrase, clarify constraints
2. Brute Force First → Explain time/space complexity
3. Optimize → Identify patterns, use appropriate DS
4. Code Cleanly → Use meaningful names, add comments
5. Test → Edge cases, dry run your solution
```

---

**⭐ Star this repo if it helps your interview prep!**
