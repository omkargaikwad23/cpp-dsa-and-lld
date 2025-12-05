# Google L3 Interview Questions (2024-2025)

> Compiled from LeetCode discussions, Reddit, and other sources. Last updated: December 2025

---

## Table of Contents
- [Arrays \& Strings](#1-arrays--strings)
- [Sliding Window \& Two Pointers](#2-sliding-window--two-pointers)
- [HashMap \& Data Structure Design](#3-hashmap--data-structure-design)
- [Graph Algorithms (BFS/DFS)](#4-graph-algorithms-bfsdfs)
- [Dynamic Programming](#5-dynamic-programming)
- [Trees](#6-trees)
- [Queue/Stack Problems](#7-queuestack-problems)
- [String/Trie Problems](#8-stringtrie-problems)
- [Key Reference Posts](#key-reference-posts)
- [Onsite Interview Insights](#onsite-interview-insights-2024-2025)

---

## 1. Arrays & Strings

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Given two arrays A and B, remove duplicates from A present in B while maintaining order | Medium | [LeetCode Discussion](https://leetcode.com/discuss/interview-question/5743212/Google-L3%28USA%29-Early-career-Interview-questions/) |
| Merge overlapping intervals | Medium | [LeetCode Discussion](https://leetcode.com/discuss/post/6339257/Google-or-L4-or-Interview-Experience-or-Offer/) |
| Text Justification | Hard | [LeetCode Discussion](https://leetcode.com/discuss/interview-question/6089176/Google-Interview-L3-or-Questions-or-Result-or-Nov-2024/) |
| Read N Characters Given Read4 | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |
| Rectangle Area (overlapping rectangles) | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |

### Sample Problem: Remove Duplicates Maintaining Order
```cpp
// Given arrays A and B, remove elements from A that exist in B
// Maintain original order in A
vector<int> removeDuplicates(vector<int>& A, vector<int>& B) {
    unordered_set<int> setB(B.begin(), B.end());
    vector<int> result;
    for (int x : A) {
        if (setB.find(x) == setB.end()) {
            result.push_back(x);
        }
    }
    return result;
}
// Follow-up: Return in reverse order
// Follow-up: What if B is very large? (Use bloom filter)
```

---

## 2. Sliding Window & Two Pointers

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Find number of subarrays with sum equal to target | Medium | [Interview Experience - Offer](https://leetcode.com/discuss/interview-experience/6352916/Interview-Experience-Got-an-Offer-from-Google-as-Software-Engineer%21/) |
| Medium sliding window problem with follow-ups | Medium | [Interview Experience - Offer](https://leetcode.com/discuss/interview-experience/6352916/Interview-Experience-Got-an-Offer-from-Google-as-Software-Engineer%21/) |
| Longest Increasing Subsequence II | Hard | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |

### Common Follow-ups Asked
- Optimize space complexity
- Handle negative numbers
- Return the actual subarray, not just count/length
- What if the array is a stream?

---

## 3. HashMap & Data Structure Design

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Design data structure with insert, delete, getRandom in O(1) | Medium | [Interview Experience - Offer](https://leetcode.com/discuss/interview-experience/6352916/Interview-Experience-Got-an-Offer-from-Google-as-Software-Engineer%21/) |
| Finding MK Average | Hard | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |
| Employee Free Time (interval merging) | Hard | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |
| HashMap problem with follow-up on internal working | Medium | [Interview Experience](https://leetcode.com/discuss/interview-experience/5484676/) |

### Important: Know Internal Workings!
Interviewers frequently ask:
- How does HashMap work internally?
- What's the time complexity of HashMap operations? (Average vs Worst case)
- How does Priority Queue work internally?
- What's the complexity of Binary Tree operations?

---

## 4. Graph Algorithms (BFS/DFS)

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Shortest path in matrix with teleportation (S→F with capital letters as portals) | Medium-Hard | [L3 Early Career Questions](https://leetcode.com/discuss/interview-question/5743212/Google-L3%28USA%29-Early-career-Interview-questions/) |
| Find minimum path between nodes with non-visitable nodes | Medium | [L3 Bengaluru - Selected](https://leetcode.com/discuss/interview-question/4859465/Google-or-Software-Engineer-or-Bengaluru-or-L3-or-SELECTED) |

| Max Size of Islands in a Tree | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |



### Sample Problem: Matrix with Teleportation
```cpp
// Matrix values: S (start), F (finish), 0 (passable), 1 (blocked)
// Capital letters (A-Z) are teleportation points - can jump between same letters
// Find shortest path from S to F

int shortestPath(vector<vector<char>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    
    // Build teleportation map
    unordered_map<char, vector<pair<int,int>>> portals;
    pair<int,int> start, finish;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c = matrix[i][j];
            if (c == 'S') start = {i, j};
            else if (c == 'F') finish = {i, j};
            else if (isupper(c)) portals[c].push_back({i, j});
        }
    }
    
    // BFS with teleportation
    queue<tuple<int,int,int>> q; // {row, col, distance}
    set<pair<int,int>> visited;
    q.push({start.first, start.second, 0});
    
    int dirs[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    
    while (!q.empty()) {
        auto [r, c, dist] = q.front(); q.pop();
        
        if (r == finish.first && c == finish.second) return dist;
        if (visited.count({r, c})) continue;
        visited.insert({r, c});
        
        // Regular moves
        for (auto& d : dirs) {
            int nr = r + d[0], nc = c + d[1];
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && 
                matrix[nr][nc] != '1' && !visited.count({nr, nc})) {
                q.push({nr, nc, dist + 1});
            }
        }
        
        // Teleportation
        char curr = matrix[r][c];
        if (isupper(curr)) {
            for (auto& [pr, pc] : portals[curr]) {
                if (!visited.count({pr, pc})) {
                    q.push({pr, pc, dist + 1});
                }
            }
        }
    }
    return -1;
}
// Follow-up: Return the actual path, not just length
```

---

## 5. Dynamic Programming

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Buy and Sell Stocks variant | Medium-Hard | [L3 Bengaluru - Selected](https://leetcode.com/discuss/interview-question/4859465/Google-or-Software-Engineer-or-Bengaluru-or-L3-or-SELECTED) |
| Shortest Common Supersequence | Hard | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |
| Find All Possible Recipes from Given Supplies | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |

### Key DP Patterns to Master
1. **Stock Problems** - State machine DP
2. **Grid DP** - Path finding with constraints
3. **String DP** - LCS, Edit Distance variants
4. **Interval DP** - Matrix chain multiplication style

---

## 6. Trees

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Maximum Ancestor for Leaves | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |
| Recursively Delete Leaf Nodes in Multi-Tree | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |

---

## 7. Queue/Stack Problems

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Queue problem with Priority Queue complexity follow-up | Medium | [Interview Experience](https://leetcode.com/discuss/interview-experience/5484676/) |
| Implement Queue using Two Stacks | Easy | [Interview Experience](https://leetcode.com/discuss/interview-experience/5484676/) |

---

## 8. String/Trie Problems

| Problem | Difficulty | Reference |
|---------|-----------|-----------|
| Design Spell Checker with corrections | Medium-Hard | [Interview Experience](https://leetcode.com/discuss/interview-experience/5867960) |
| Crossword Search | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |
| Decode String | Medium | [2024 Google Compilation](https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/) |

### Sample: Spell Checker Follow-ups
- What if the dictionary is very large?
- How to handle case sensitivity?
- How to suggest multiple corrections ranked by likelihood?
- What if input has numbers or special characters?

---

## Key Reference Posts

| Post Title | Link |
|------------|------|
| 2024 Google Interview Questions Compilation | https://leetcode.com/discuss/post/6185127/2024-google-interview-questions-compilat-mjrf/ |
| Google Interview Experiences Compilation | https://leetcode.com/discuss/post/6459307/google-interview-experiences-compilation-u3cz/ |
| Recent Google Interview Questions L3/L4 | https://leetcode.com/discuss/interview-question/5092478/Recent-Google-Interview-Questions-L3L4/ |
| L3 USA Early Career Questions | https://leetcode.com/discuss/interview-question/5743212/Google-L3%28USA%29-Early-career-Interview-questions/ |
| Interview Experience - Got an Offer! | https://leetcode.com/discuss/interview-experience/6352916/Interview-Experience-Got-an-Offer-from-Google-as-Software-Engineer%21/ |
| Google L3 Bengaluru - Selected | https://leetcode.com/discuss/interview-question/4859465/Google-or-Software-Engineer-or-Bengaluru-or-L3-or-SELECTED |
| Google Interview L3 Nov 2024 | https://leetcode.com/discuss/interview-question/6089176/Google-Interview-L3-or-Questions-or-Result-or-Nov-2024/ |

---

## Onsite Interview Insights (2024-2025)

### Recent Changes in 2025

> **Important**: Google CEO Sundar Pichai announced that Google is reintroducing **in-person interviews** to combat AI-assisted cheating. At least one round is now conducted face-to-face.

Source: [Axios Report](https://www.axios.com/2025/08/12/in-person-job-interview-artificial-intelligence)



#### Common Follow-up Areas
- Time/Space optimization
- Edge cases handling
- Different input variations
- Internal workings explanation

---


https://leetcode.com/discuss/post/7323449/google-l3-interview-experience-by-anonym-2ggr/


Team Fit:
https://leetcode.com/discuss/post/7228375/the-google-dream-by-anonymous_user-ebxl/

