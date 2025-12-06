# 🎯 Google Interview Questions - Quick Reference

## 📊 By Pattern

### Arrays / Two Pointers
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Piano Hand Raises | `01_Arrays/01_piano_hand_raises.cpp` | Two Pointers, Greedy | O(n) | O(1) |
| Triplets with Distance D | `01_Arrays/02_triplets_distance.cpp` | Three Pointers | O(n) | O(1) |
| Subarray Sum AP (diff ±1) | `01_Arrays/03_subarray_sum_ap.cpp` | Sliding Window | O(n) | O(1) |
| Ruby Diamond Cut | `01_Arrays/04_ruby_diamond_cut.cpp` | Two Pointers | O(n) | O(1) |
| Watchtower Profit | `01_Arrays/05_watchtower_profit.cpp` | Sorting + Greedy | O(n log n) | O(n) |

### Strings
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Simplify Algebraic Expression | `02_Strings/01_simplify_expression.cpp` | Stack + HashMap | O(n) | O(n) |
| Ambigram Words | `02_Strings/02_ambigram_words.cpp` | Two Pointers | O(n×m) | O(1) |
| Top K Frequent Words | `02_Strings/03_top_k_frequent.cpp` | HashMap + Heap | O(n log k) | O(n) |

### Dynamic Programming
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Boat Energy Travel | `03_DP/01_boat_energy.cpp` | 2D Memoization | O(n×k) | O(n×k) |
| Bank Transactions | `03_DP/02_bank_transactions.cpp` | Sliding Window / Prefix | O(n) | O(1) |
| Grid Paths with Coins | `03_DP/03_paths_with_coins.cpp` | 3D DP | O(n×m×c) | O(n×m×c) |
| Cake Vertical Cut | `03_DP/04_cake_vertical_cut.cpp` | Sweep Line | O(n×m) | O(m) |
| Max Triangle Area | `03_DP/05_max_triangle_area.cpp` | Prefix Sum | O(n×m) | O(n×m) |
| Power of 2 Knapsack | `03_DP/06_power2_knapsack.cpp` | Modified Knapsack | O(n log W) | O(log W) |

### Graphs
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Blocked Node Reachability | `04_Graphs/01_blocked_reachability.cpp` | BFS | O(V+E) | O(V) |
| Similar Movies | `04_Graphs/02_similar_movies.cpp` | DFS + Sorting | O(V+E + V log V) | O(V) |
| File System Size | `04_Graphs/03_file_system_size.cpp` | DFS Tree | O(n) | O(n) |
| Flight Itinerary | `04_Graphs/04_flight_itinerary.cpp` | DFS/Euler Path | O(E log E) | O(E) |
| Folder to Gmail Labels | `04_Graphs/05_folder_gmail_labels.cpp` | Tree DFS | O(n) | O(n) |

### Trees
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Family Next Birthday | `05_Trees/01_family_birthday.cpp` | DFS + Binary Search | O(n log n) | O(n) |
| Chess Player Ranking | `05_Trees/02_chess_ranking.cpp` | Graph BFS | O(V²) | O(V) |
| Tree Children Cost | `05_Trees/03_tree_children_cost.cpp` | DFS | O(n) | O(h) |
| Random Leaf Node | `05_Trees/04_random_leaf.cpp` | DFS + Random | O(n) | O(h) |

### Design / OOP
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Phone Log System | `06_Design/01_phone_log.cpp` | HashMap + Query | O(n×m) | O(n×m) |
| Worker Schedule (Intervals) | `06_Design/02_worker_schedule.cpp` | Line Sweep | O(n log n) | O(n) |
| Garage Parking System | `06_Design/03_garage_parking.cpp` | HashMap + Events | O(n log n) | O(n) |
| Triplet Distance Stream | `06_Design/04_triplet_stream.cpp` | Multiset | O(log n) per add | O(n) |
| Intern Room Assignment | `06_Design/05_intern_rooms.cpp` | Greedy | O(n log n) | O(n) |
| RPC Timeout Detection | `06_Design/06_rpc_timeout.cpp` | Queue + HashMap | O(n) | O(n) |

### Line Sweep / Intervals
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Max Cars in Garage | `07_LineSweep/01_max_cars_garage.cpp` | Event Sorting | O(n log n) | O(n) |

### Backtracking
| Problem | File | Pattern | Time | Space |
|---------|------|---------|------|-------|
| Valid Musical Notes | `08_Backtracking/01_musical_notes.cpp` | Backtracking | O(3^n) | O(n) |

---

## 🔥 Must-Know Patterns for Google

1. **Line Sweep / Events** - Worker schedules, meeting rooms, max overlap
2. **Graph Traversal** - BFS/DFS with state, blocked nodes, similarity
3. **DP with State** - Grid paths, energy constraints, collecting items
4. **Design Problems** - System design with optimal data structures
5. **Two/Three Pointers** - Sorted arrays, triplets, distance constraints

---

## 📝 Quick Tips

- Always clarify edge cases before coding
- State time/space complexity before implementation
- Think about follow-up questions (streaming, multiple queries, optimization)
- Google loves problems with multiple parts/follow-ups

