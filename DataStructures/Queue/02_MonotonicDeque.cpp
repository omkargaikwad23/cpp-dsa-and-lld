/*
================================================================================
                    MONOTONIC DEQUE ⭐
================================================================================

A Monotonic Deque maintains elements in sorted order (increasing or decreasing)
from front to back. Used primarily for sliding window problems.

Key Operations:
- Push: Remove elements that violate monotonic property, then add
- Pop: Remove front if it's outside window
- Query: Front element is the answer (max or min)

Time: O(n) for n elements (amortized O(1) per operation)

================================================================================
                     WHEN TO USE
================================================================================

1. Sliding Window Maximum/Minimum
2. Finding max/min in range queries
3. Constrained optimization problems
4. Problems with "at most" or "at least" constraints

================================================================================
*/

#include <iostream>
#include <deque>
#include <vector>
#include <climits>
using namespace std;

/*
================================================================================
PATTERN 1: SLIDING WINDOW MAXIMUM
================================================================================
LeetCode: 239. Sliding Window Maximum

Maintain a DECREASING deque (front is maximum).
When new element comes:
1. Remove elements smaller than it from back (they'll never be max)
2. Remove front if it's outside window
3. Add new element to back
4. Front is the maximum

Time: O(n), Space: O(k)
*/
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // Store INDICES (not values)
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements outside window from front
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove smaller elements from back (maintain decreasing order)
        while (!dq.empty() && nums[dq.back()] < nums[i]) {
            dq.pop_back();
        }
        
        // Add current index
        dq.push_back(i);
        
        // Window is full, record the maximum
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}
/*
Example: nums = [1,3,-1,-3,5,3,6,7], k = 3

i=0: dq=[0]              nums[0]=1
i=1: dq=[1]              nums[1]=3 > nums[0], remove 0
i=2: dq=[1,2]            nums[2]=-1, add. Window [1,3,-1], max=3
i=3: dq=[1,3]            nums[3]=-3, add. Window [3,-1,-3], max=3
i=4: dq=[4]              nums[4]=5 > all, clear. Window [-1,-3,5], max=5
i=5: dq=[4,5]            nums[5]=3, add. Window [-3,5,3], max=5
i=6: dq=[6]              nums[6]=6 > all. Window [5,3,6], max=6
i=7: dq=[7]              nums[7]=7 > all. Window [3,6,7], max=7

Result: [3,3,5,5,6,7]
*/


/*
================================================================================
PATTERN 2: SLIDING WINDOW MINIMUM
================================================================================

Same as maximum, but maintain INCREASING deque (front is minimum).
*/
vector<int> minSlidingWindow(vector<int>& nums, int k) {
    deque<int> dq;  // Store indices, increasing order of values
    vector<int> result;
    
    for (int i = 0; i < nums.size(); i++) {
        // Remove elements outside window
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        
        // Remove LARGER elements from back (maintain increasing order)
        while (!dq.empty() && nums[dq.back()] > nums[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        if (i >= k - 1) {
            result.push_back(nums[dq.front()]);
        }
    }
    
    return result;
}


/*
================================================================================
PATTERN 3: SHORTEST SUBARRAY WITH SUM >= K
================================================================================
LeetCode: 862. Shortest Subarray with Sum at Least K

This problem has NEGATIVE numbers, so sliding window doesn't work directly.
Use prefix sums + monotonic deque.

Key insight:
- prefix[j] - prefix[i] >= K means subarray [i+1, j] has sum >= K
- For fixed j, we want smallest j - i where prefix[j] - prefix[i] >= K
- We want prefix[i] to be as large as possible (larger subtraction = smaller result)
- Maintain increasing deque of prefix sums

Time: O(n), Space: O(n)
*/
int shortestSubarray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<long long> prefix(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    
    deque<int> dq;  // Increasing deque of indices
    int minLen = INT_MAX;
    
    for (int j = 0; j <= n; j++) {
        // Check if current prefix - front prefix >= k
        while (!dq.empty() && prefix[j] - prefix[dq.front()] >= k) {
            minLen = min(minLen, j - dq.front());
            dq.pop_front();  // Won't give shorter subarray
        }
        
        // Maintain increasing order
        while (!dq.empty() && prefix[j] <= prefix[dq.back()]) {
            dq.pop_back();
        }
        
        dq.push_back(j);
    }
    
    return minLen == INT_MAX ? -1 : minLen;
}
/*
Example: nums = [2,-1,2], k = 3
prefix = [0, 2, 1, 3]

j=0: dq=[0], prefix[0]=0
j=1: dq=[0,1], prefix[1]=2
j=2: dq=[0,2], prefix[2]=1 < prefix[1], remove 1
j=3: prefix[3]-prefix[0]=3>=3, minLen=3, remove 0
     prefix[3]-prefix[2]=2<3
     dq=[2,3]

Answer: 3
*/


/*
================================================================================
PATTERN 4: JUMP GAME VI
================================================================================
LeetCode: 1696. Jump Game VI

Start at index 0, jump 1 to k steps, maximize score.
score[i] = nums[i] + max(score[i-k], ..., score[i-1])

Use sliding window maximum with monotonic deque!

Time: O(n), Space: O(k)
*/
int maxResult(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];
    
    deque<int> dq;  // Decreasing deque of indices (max dp at front)
    dq.push_back(0);
    
    for (int i = 1; i < n; i++) {
        // Remove elements outside window [i-k, i-1]
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        // dp[i] = nums[i] + max dp in window
        dp[i] = nums[i] + dp[dq.front()];
        
        // Maintain decreasing order
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return dp[n - 1];
}
// Example: nums = [1,-1,-2,4,-7,3], k = 2 -> Output: 7 (path: 1->-1->4->3)


/*
================================================================================
PATTERN 5: CONSTRAINED SUBSEQUENCE SUM
================================================================================
LeetCode: 1425. Constrained Subsequence Sum

Max sum of subsequence where adjacent elements are at most k indices apart.
Similar to Jump Game VI.

Time: O(n), Space: O(k)
*/
int constrainedSubsetSum(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];
    int result = dp[0];
    
    deque<int> dq;
    dq.push_back(0);
    
    for (int i = 1; i < n; i++) {
        // Remove outside window
        while (!dq.empty() && dq.front() < i - k) {
            dq.pop_front();
        }
        
        // dp[i] = nums[i] + max(0, max dp in window)
        dp[i] = nums[i] + max(0, dp[dq.front()]);
        result = max(result, dp[i]);
        
        // Maintain decreasing
        while (!dq.empty() && dp[dq.back()] <= dp[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    return result;
}


/*
================================================================================
PATTERN 6: MAX VALUE OF EQUATION
================================================================================
LeetCode: 1499. Max Value of Equation

Given points, find max yi + yj + |xi - xj| where i < j and |xi - xj| <= k.
Since i < j and points sorted by x: yi + yj + xj - xi = (yi - xi) + (yj + xj)

For fixed j, maximize (yi - xi) where xj - xi <= k.
Use monotonic deque to track max (y - x) values.

Time: O(n), Space: O(n)
*/
int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
    deque<pair<int, int>> dq;  // {yi - xi, xi}
    int result = INT_MIN;
    
    for (auto& p : points) {
        int x = p[0], y = p[1];
        
        // Remove points outside window (xj - xi > k)
        while (!dq.empty() && x - dq.front().second > k) {
            dq.pop_front();
        }
        
        // Update result with best previous point
        if (!dq.empty()) {
            result = max(result, dq.front().first + y + x);
        }
        
        // Maintain decreasing order of (y - x)
        while (!dq.empty() && dq.back().first <= y - x) {
            dq.pop_back();
        }
        
        dq.push_back({y - x, x});
    }
    
    return result;
}


/*
================================================================================
PATTERN 7: LONGEST CONTINUOUS SUBARRAY WITH DIFF <= LIMIT
================================================================================
LeetCode: 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

Use TWO deques: one for max, one for min.
Expand window, shrink when max - min > limit.

Time: O(n), Space: O(n)
*/
int longestSubarray(vector<int>& nums, int limit) {
    deque<int> maxDq, minDq;  // Indices
    int left = 0, result = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        // Maintain max deque (decreasing)
        while (!maxDq.empty() && nums[maxDq.back()] < nums[right]) {
            maxDq.pop_back();
        }
        maxDq.push_back(right);
        
        // Maintain min deque (increasing)
        while (!minDq.empty() && nums[minDq.back()] > nums[right]) {
            minDq.pop_back();
        }
        minDq.push_back(right);
        
        // Shrink window if diff > limit
        while (nums[maxDq.front()] - nums[minDq.front()] > limit) {
            left++;
            if (maxDq.front() < left) maxDq.pop_front();
            if (minDq.front() < left) minDq.pop_front();
        }
        
        result = max(result, right - left + 1);
    }
    
    return result;
}
// Example: nums = [8,2,4,7], limit = 4 -> Output: 2 (subarray [2,4])


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Monotonic Deque ===\n\n";
    
    // Sliding Window Maximum
    cout << "--- Sliding Window Maximum ---" << endl;
    vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> maxWindow = maxSlidingWindow(nums1, k);
    cout << "nums = [1,3,-1,-3,5,3,6,7], k = 3" << endl;
    cout << "Result: ";
    for (int x : maxWindow) cout << x << " ";
    cout << endl;  // 3 3 5 5 6 7
    
    // Sliding Window Minimum
    cout << "\n--- Sliding Window Minimum ---" << endl;
    vector<int> minWindow = minSlidingWindow(nums1, k);
    cout << "Result: ";
    for (int x : minWindow) cout << x << " ";
    cout << endl;  // -1 -3 -3 -3 3 3
    
    // Shortest Subarray with Sum >= K
    cout << "\n--- Shortest Subarray Sum >= K ---" << endl;
    vector<int> nums2 = {2, -1, 2};
    cout << "nums = [2,-1,2], k = 3: " << shortestSubarray(nums2, 3) << endl;  // 3
    
    // Jump Game VI
    cout << "\n--- Jump Game VI ---" << endl;
    vector<int> nums3 = {1, -1, -2, 4, -7, 3};
    cout << "nums = [1,-1,-2,4,-7,3], k = 2: " << maxResult(nums3, 2) << endl;  // 7
    
    // Longest Subarray with Diff <= Limit
    cout << "\n--- Longest Subarray Diff <= Limit ---" << endl;
    vector<int> nums4 = {8, 2, 4, 7};
    cout << "nums = [8,2,4,7], limit = 4: " << longestSubarray(nums4, 4) << endl;  // 2
    
    return 0;
}

/*
================================================================================
                              CHEAT SHEET
================================================================================

MONOTONIC DEQUE TEMPLATE (for sliding window max):
─────────────────────────────────────────────────
deque<int> dq;  // Store indices
for (int i = 0; i < n; i++) {
    // 1. Remove out-of-window elements from FRONT
    while (!dq.empty() && dq.front() <= i - k) {
        dq.pop_front();
    }
    
    // 2. Remove smaller elements from BACK (maintain decreasing)
    while (!dq.empty() && nums[dq.back()] < nums[i]) {
        dq.pop_back();
    }
    
    // 3. Add current index
    dq.push_back(i);
    
    // 4. Answer is at FRONT
    if (i >= k - 1) {
        result.push_back(nums[dq.front()]);
    }
}

┌─────────────────────────────┬───────────────────────────────────────────────┐
│ Problem                     │ Deque Type                                    │
├─────────────────────────────┼───────────────────────────────────────────────┤
│ Sliding Window Maximum      │ Decreasing (front = max)                      │
│ Sliding Window Minimum      │ Increasing (front = min)                      │
│ Shortest Subarray Sum >= K  │ Increasing prefix sums                        │
│ Jump Game VI                │ Decreasing dp values                          │
│ Max-Min <= Limit            │ Two deques: one max, one min                  │
└─────────────────────────────┴───────────────────────────────────────────────┘

KEY INSIGHT:
- Store INDICES, not values (to check window bounds)
- Elements behind current that are "worse" will never be chosen
- Each element pushed and popped at most once -> O(n) total

================================================================================
*/

