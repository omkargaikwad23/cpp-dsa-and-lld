/*
================================================================================
                    BIT MANIPULATION - SUBSETS & BITMASK DP
================================================================================

Use bits to represent subsets:
- Bit i = 1 means element i is included
- Iterate 0 to (1 << n) - 1 for all subsets
- Enumerate subsets of a mask efficiently

Applications: Subset enumeration, state compression DP, assignment problems.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Subsets (LeetCode 78) - Bitmask Approach
───────────────────────────────────────────────────
Generate all subsets using bitmask.

Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Time: O(n * 2^n) | Space: O(n * 2^n)
*/
vector<vector<int>> subsetsBitmask(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        result.push_back(subset);
    }
    
    return result;
}


/*
PROBLEM 2: Enumerate All Subsets of a Given Mask
────────────────────────────────────────────────
Efficiently iterate through all subsets of a bitmask.

For mask = 5 (101): subsets are 5, 4, 1, 0

Time: O(2^k) where k = set bits | Space: O(1)
*/
void enumerateSubsets(int mask) {
    cout << "Subsets of " << mask << ": ";
    for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
        cout << sub << " ";
    }
    cout << "0\n";
}


/*
PROBLEM 3: Partition to K Equal Sum Subsets (LeetCode 698) - Bitmask DP
───────────────────────────────────────────────────────────────────────
Can array be partitioned into k subsets with equal sum?

Time: O(n * 2^n) | Space: O(2^n)
*/
bool canPartitionKSubsets(vector<int>& nums, int k) {
    int n = nums.size();
    int sum = 0;
    for (int num : nums) sum += num;
    
    if (sum % k != 0) return false;
    int target = sum / k;
    
    sort(nums.rbegin(), nums.rend());  // Optimization
    if (nums[0] > target) return false;
    
    vector<int> dp(1 << n, -1);
    dp[0] = 0;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == -1) continue;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;  // Already used
            
            if (dp[mask] + nums[i] <= target) {
                int newMask = mask | (1 << i);
                dp[newMask] = (dp[mask] + nums[i]) % target;
            }
        }
    }
    
    return dp[(1 << n) - 1] == 0;
}


/*
PROBLEM 4: Shortest Path Visiting All Nodes (LeetCode 847) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────────
Shortest path that visits all nodes (can revisit).

State: (current_node, visited_mask)
BFS from all nodes simultaneously.

Time: O(n * 2^n) | Space: O(n * 2^n)
*/
int shortestPathLength(vector<vector<int>>& graph) {
    int n = graph.size();
    int target = (1 << n) - 1;
    
    queue<tuple<int, int, int>> q;  // {node, mask, dist}
    set<pair<int, int>> visited;
    
    // Start BFS from all nodes
    for (int i = 0; i < n; i++) {
        q.push({i, 1 << i, 0});
        visited.insert({i, 1 << i});
    }
    
    while (!q.empty()) {
        auto [node, mask, dist] = q.front();
        q.pop();
        
        if (mask == target) return dist;
        
        for (int next : graph[node]) {
            int newMask = mask | (1 << next);
            if (!visited.count({next, newMask})) {
                visited.insert({next, newMask});
                q.push({next, newMask, dist + 1});
            }
        }
    }
    
    return -1;
}


/*
PROBLEM 5: Minimum Number of Work Sessions (LeetCode 1986)
──────────────────────────────────────────────────────────
Complete tasks in sessions of max sessionTime. Minimize sessions.

State: dp[mask] = min remaining time in last session

Time: O(n * 2^n) | Space: O(2^n)
*/
int minSessions(vector<int>& tasks, int sessionTime) {
    int n = tasks.size();
    
    // Precompute valid subsets that fit in one session
    vector<int> subsetSum(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subsetSum[mask] += tasks[i];
            }
        }
    }
    
    // dp[mask] = {sessions, remaining time}
    vector<pair<int, int>> dp(1 << n, {INT_MAX, 0});
    dp[0] = {0, sessionTime};  // 0 sessions, full time available
    
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask].first == INT_MAX) continue;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            
            int newMask = mask | (1 << i);
            pair<int, int> newState;
            
            if (tasks[i] <= dp[mask].second) {
                // Fit in current session
                newState = {dp[mask].first, dp[mask].second - tasks[i]};
            } else {
                // Need new session
                newState = {dp[mask].first + 1, sessionTime - tasks[i]};
            }
            
            dp[newMask] = min(dp[newMask], newState);
        }
    }
    
    return dp[(1 << n) - 1].first + 1;
}


/*
PROBLEM 6: Maximum Score Words Formed (LeetCode 1255)
─────────────────────────────────────────────────────
Select words to maximize score using limited letters.

Time: O(2^n * total_chars) | Space: O(26)
*/
int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
    int n = words.size();
    
    // Count available letters
    vector<int> available(26, 0);
    for (char c : letters) available[c - 'a']++;
    
    int maxScore = 0;
    
    // Try all subsets
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> used(26, 0);
        int totalScore = 0;
        bool valid = true;
        
        for (int i = 0; i < n && valid; i++) {
            if (mask & (1 << i)) {
                for (char c : words[i]) {
                    used[c - 'a']++;
                    totalScore += score[c - 'a'];
                    if (used[c - 'a'] > available[c - 'a']) {
                        valid = false;
                        break;
                    }
                }
            }
        }
        
        if (valid) {
            maxScore = max(maxScore, totalScore);
        }
    }
    
    return maxScore;
}


/*
PROBLEM 7: Parallel Courses II (LeetCode 1494)
──────────────────────────────────────────────
Take at most k courses per semester with prerequisites.

Time: O(3^n) | Space: O(2^n)
*/
int minNumberOfSemesters(int n, vector<vector<int>>& relations, int k) {
    // Precompute prerequisites for each course
    vector<int> prereq(n, 0);
    for (auto& r : relations) {
        prereq[r[1] - 1] |= (1 << (r[0] - 1));
    }
    
    vector<int> dp(1 << n, n + 1);
    dp[0] = 0;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == n + 1) continue;
        
        // Find courses we can take (prereqs satisfied)
        int canTake = 0;
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i)) && (prereq[i] & mask) == prereq[i]) {
                canTake |= (1 << i);
            }
        }
        
        // Enumerate subsets of canTake with at most k bits
        for (int sub = canTake; sub > 0; sub = (sub - 1) & canTake) {
            if (__builtin_popcount(sub) <= k) {
                dp[mask | sub] = min(dp[mask | sub], dp[mask] + 1);
            }
        }
    }
    
    return dp[(1 << n) - 1];
}


/*
PROBLEM 8: Find Minimum Time to Finish All Jobs (LeetCode 1723)
───────────────────────────────────────────────────────────────
Assign jobs to k workers, minimize maximum working time.

Binary search + bitmask DP

Time: O(n * 3^n * log(sum)) | Space: O(2^n)
*/
int minimumTimeRequired(vector<int>& jobs, int k) {
    int n = jobs.size();
    
    // Precompute subset sums
    vector<int> subsetSum(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subsetSum[mask] += jobs[i];
            }
        }
    }
    
    auto canFinish = [&](int maxTime) -> bool {
        vector<int> dp(1 << n, k + 1);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] > k) continue;
            
            int remaining = ((1 << n) - 1) ^ mask;  // Unassigned jobs
            for (int sub = remaining; sub > 0; sub = (sub - 1) & remaining) {
                if (subsetSum[sub] <= maxTime) {
                    dp[mask | sub] = min(dp[mask | sub], dp[mask] + 1);
                }
            }
        }
        
        return dp[(1 << n) - 1] <= k;
    };
    
    int left = *max_element(jobs.begin(), jobs.end());
    int right = accumulate(jobs.begin(), jobs.end(), 0);
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canFinish(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Subsets & Bitmask DP ===\n\n";
    
    // Subsets
    vector<int> nums = {1, 2, 3};
    auto subsets = subsetsBitmask(nums);
    cout << "1. Subsets of [1,2,3]: " << subsets.size() << " subsets\n";
    
    // Enumerate subsets
    cout << "2. ";
    enumerateSubsets(5);
    
    // Partition K Subsets
    vector<int> nums3 = {4, 3, 2, 3, 5, 2, 1};
    cout << "3. Can partition into 4 equal subsets: " 
         << (canPartitionKSubsets(nums3, 4) ? "Yes" : "No") << "\n";
    
    // Shortest Path All Nodes
    vector<vector<int>> graph = {{1,2,3},{0},{0},{0}};
    cout << "4. Shortest path visiting all: " << shortestPathLength(graph) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

SUBSET ENUMERATION:
  for (int mask = 0; mask < (1 << n); mask++) {
      // mask represents a subset
  }

ENUMERATE SUBSETS OF MASK:
  for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
      // sub is a subset of mask
  }

BITMASK DP PATTERNS:
+───────────────────────────────+────────────────────────────────────────────────+
| Problem Type                  | State Definition                               |
+───────────────────────────────+────────────────────────────────────────────────+
| Partition problems            | dp[mask] = min/max value for subset mask       |
| Shortest path (visit all)     | dp[node][mask] = min distance                  |
| Assignment problems           | dp[mask] = feasibility or optimal value        |
| Traveling Salesman            | dp[node][visited_mask] = min cost              |
+───────────────────────────────+────────────────────────────────────────────────+

TIME COMPLEXITY:
- Iterating all subsets: O(2^n)
- Iterating all subsets of all masks: O(3^n)
- Proof: Sum over k of C(n,k) * 2^k = 3^n

================================================================================
*/

