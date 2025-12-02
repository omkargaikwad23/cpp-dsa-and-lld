/*
================================================================================
                    PATTERN 18: BITMASK DP
================================================================================

When to use:
- Problems involving subsets or combinations
- Small number of elements (typically <= 20)
- Need to track visited/selected states efficiently
- Assignment problems, TSP

LeetCode Problems:
- 1986. Minimum Number of Work Sessions
- 2305. Fair Distribution of Cookies
- 847. Shortest Path Visiting All Nodes

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Traveling Salesman Problem (Classic) ⭐
─────────────────────────────────────────────────
Visit all cities exactly once, minimize total distance.

dp[mask][i] = min cost to visit cities in mask, ending at city i

Time: O(n² * 2^n) | Space: O(n * 2^n)
*/
int tsp(vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    
    // Start from city 0
    dp[1][0] = 0;
    
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int last = 0; last < n; last++) {
            if (!(mask & (1 << last))) continue;
            if (dp[mask][last] == INT_MAX) continue;
            
            for (int next = 0; next < n; next++) {
                if (mask & (1 << next)) continue;
                int newMask = mask | (1 << next);
                dp[newMask][next] = min(dp[newMask][next],
                                       dp[mask][last] + dist[last][next]);
            }
        }
    }
    
    // Return to start
    int result = INT_MAX;
    int fullMask = (1 << n) - 1;
    for (int i = 1; i < n; i++) {
        if (dp[fullMask][i] != INT_MAX) {
            result = min(result, dp[fullMask][i] + dist[i][0]);
        }
    }
    
    return result;
}


/*
PROBLEM 2: Shortest Path Visiting All Nodes (LeetCode 847) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────────
Find shortest path visiting all nodes (can revisit nodes).

BFS with state = (current_node, visited_mask)

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
PROBLEM 3: Partition to K Equal Sum Subsets (LeetCode 698)
──────────────────────────────────────────────────────────
Can array be partitioned into k subsets with equal sum?

dp[mask] = remaining capacity in current subset

Time: O(n * 2^n) | Space: O(2^n)
*/
bool canPartitionKSubsets(vector<int>& nums, int k) {
    int n = nums.size();
    int sum = 0;
    for (int num : nums) sum += num;
    
    if (sum % k != 0) return false;
    int target = sum / k;
    
    sort(nums.rbegin(), nums.rend());
    if (nums[0] > target) return false;
    
    vector<int> dp(1 << n, -1);
    dp[0] = 0;
    
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask] == -1) continue;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            if (dp[mask] + nums[i] <= target) {
                int newMask = mask | (1 << i);
                dp[newMask] = (dp[mask] + nums[i]) % target;
            }
        }
    }
    
    return dp[(1 << n) - 1] == 0;
}


/*
PROBLEM 4: Fair Distribution of Cookies (LeetCode 2305)
───────────────────────────────────────────────────────
Distribute cookies to k children, minimize max sum.

Try all subsets for each child.

Time: O(k * 3^n) | Space: O(k * 2^n)
*/
int distributeCookies(vector<int>& cookies, int k) {
    int n = cookies.size();
    
    // Precompute subset sums
    vector<int> subsetSum(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subsetSum[mask] += cookies[i];
            }
        }
    }
    
    // dp[i][mask] = min max sum distributing mask to first i children
    vector<vector<int>> dp(k + 1, vector<int>(1 << n, INT_MAX));
    dp[0][0] = 0;
    
    for (int child = 0; child < k; child++) {
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[child][mask] == INT_MAX) continue;
            
            int remaining = ((1 << n) - 1) ^ mask;
            for (int sub = remaining; sub > 0; sub = (sub - 1) & remaining) {
                int newMask = mask | sub;
                dp[child + 1][newMask] = min(dp[child + 1][newMask],
                                            max(dp[child][mask], subsetSum[sub]));
            }
        }
    }
    
    return dp[k][(1 << n) - 1];
}


/*
PROBLEM 5: Minimum Number of Work Sessions (LeetCode 1986)
──────────────────────────────────────────────────────────
Complete tasks in sessions of max sessionTime. Minimize sessions.

dp[mask] = min {sessions, remaining time in last session}

Time: O(n * 2^n) | Space: O(2^n)
*/
int minSessions(vector<int>& tasks, int sessionTime) {
    int n = tasks.size();
    
    // dp[mask] = {sessions, remaining time}
    vector<pair<int, int>> dp(1 << n, {INT_MAX, 0});
    dp[0] = {0, sessionTime};
    
    for (int mask = 0; mask < (1 << n); mask++) {
        if (dp[mask].first == INT_MAX) continue;
        
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) continue;
            
            int newMask = mask | (1 << i);
            pair<int, int> newState;
            
            if (tasks[i] <= dp[mask].second) {
                newState = {dp[mask].first, dp[mask].second - tasks[i]};
            } else {
                newState = {dp[mask].first + 1, sessionTime - tasks[i]};
            }
            
            dp[newMask] = min(dp[newMask], newState);
        }
    }
    
    return dp[(1 << n) - 1].first + 1;
}


/*
PROBLEM 6: Maximum Students Taking Exam (LeetCode 1349)
───────────────────────────────────────────────────────
Place students in grid, no one can cheat (see adjacent).

Row-by-row bitmask DP.

Time: O(m * 4^n) | Space: O(2^n)
*/
int maxStudents(vector<vector<char>>& seats) {
    int m = seats.size(), n = seats[0].size();
    
    // Valid seats mask for each row
    vector<int> validSeats(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (seats[i][j] == '.') {
                validSeats[i] |= (1 << j);
            }
        }
    }
    
    auto canSit = [&](int mask) {
        return (mask & (mask >> 1)) == 0;  // No adjacent
    };
    
    vector<int> dp(1 << n, -1);
    dp[0] = 0;
    
    for (int row = 0; row < m; row++) {
        vector<int> newDp(1 << n, -1);
        
        for (int prevMask = 0; prevMask < (1 << n); prevMask++) {
            if (dp[prevMask] == -1) continue;
            
            for (int mask = 0; mask < (1 << n); mask++) {
                // Check valid seat
                if ((mask & validSeats[row]) != mask) continue;
                // No adjacent in same row
                if (!canSit(mask)) continue;
                // No diagonal with previous row
                if ((mask & (prevMask >> 1)) || (mask & (prevMask << 1))) continue;
                
                int students = __builtin_popcount(mask);
                newDp[mask] = max(newDp[mask], dp[prevMask] + students);
            }
        }
        
        dp = newDp;
    }
    
    return *max_element(dp.begin(), dp.end());
}


/*
PROBLEM 7: Find Minimum Time to Finish All Jobs (LeetCode 1723)
───────────────────────────────────────────────────────────────
Assign jobs to k workers, minimize max working time.

Binary search + bitmask DP validation.

Time: O(n * 3^n * log(sum)) | Space: O(2^n)
*/
int minimumTimeRequired(vector<int>& jobs, int k) {
    int n = jobs.size();
    
    vector<int> subsetSum(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subsetSum[mask] += jobs[i];
            }
        }
    }
    
    auto canFinish = [&](int maxTime) {
        vector<int> dp(1 << n, k + 1);
        dp[0] = 0;
        
        for (int mask = 0; mask < (1 << n); mask++) {
            if (dp[mask] > k) continue;
            
            int remaining = ((1 << n) - 1) ^ mask;
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
    cout << "=== Bitmask DP ===\n\n";
    
    // TSP
    vector<vector<int>> dist = {{0,10,15,20},{10,0,35,25},{15,35,0,30},{20,25,30,0}};
    cout << "1. TSP min cost: " << tsp(dist) << "\n";
    
    // Shortest Path All Nodes
    vector<vector<int>> graph = {{1,2,3},{0},{0},{0}};
    cout << "2. Shortest path visiting all: " << shortestPathLength(graph) << "\n";
    
    // Partition K Subsets
    vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
    cout << "3. Can partition into 4: " << (canPartitionKSubsets(nums, 4) ? "Yes" : "No") << "\n";
    
    // Cookie Distribution
    vector<int> cookies = {8, 15, 10, 20, 8};
    cout << "4. Fair cookie distribution: " << distributeCookies(cookies, 2) << "\n";
    
    // Work Sessions
    vector<int> tasks = {1, 2, 3};
    cout << "5. Min sessions (time=3): " << minSessions(tasks, 3) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

BITMASK DP TEMPLATE:
    dp[mask] = optimal value for subset represented by mask
    
    for mask = 0 to (1 << n) - 1:
        for i = 0 to n - 1:
            if mask has bit i:
                dp[mask] = f(dp[mask without bit i], ...)

ENUMERATE SUBSETS:
    for sub = mask; sub > 0; sub = (sub - 1) & mask

TIME COMPLEXITY:
    - Iterate all masks: O(2^n)
    - Iterate all subsets of all masks: O(3^n)
    - TSP style: O(n² * 2^n)

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | State                                          |
+───────────────────────────────+────────────────────────────────────────────────+
| TSP                           | dp[mask][last] = min cost ending at last       |
| Shortest Path All Nodes       | BFS with (node, visited mask)                  |
| Partition K Subsets           | dp[mask] = remaining capacity                  |
| Assignment Problems           | Binary search + dp validation                  |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

