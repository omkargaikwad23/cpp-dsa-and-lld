/*
================================================================================
                    GREEDY - ARRAY & SEQUENCE PROBLEMS
================================================================================

Make optimal local decisions while traversing arrays.
Often involves tracking "reachability" or "cumulative" state.

Time: Usually O(n) | Space: Usually O(1)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Jump Game (LeetCode 55)
──────────────────────────────────
Can you reach the last index?

Input: nums = [2,3,1,1,4]
Output: true

Strategy: Track maximum reachable index

Time: O(n) | Space: O(1)
*/
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    
    for (int i = 0; i < nums.size(); i++) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
        if (maxReach >= nums.size() - 1) return true;
    }
    
    return true;
}


/*
PROBLEM 2: Jump Game II (LeetCode 45)
─────────────────────────────────────
Minimum jumps to reach last index.

Input: nums = [2,3,1,1,4]
Output: 2 (0 -> 1 -> 4)

Strategy: BFS-like, track current range and next furthest

Time: O(n) | Space: O(1)
*/
int jump(vector<int>& nums) {
    int n = nums.size();
    if (n <= 1) return 0;
    
    int jumps = 0, end = 0, furthest = 0;
    
    for (int i = 0; i < n - 1; i++) {
        furthest = max(furthest, i + nums[i]);
        
        if (i == end) {  // Must jump
            jumps++;
            end = furthest;
            
            if (end >= n - 1) break;
        }
    }
    
    return jumps;
}


/*
PROBLEM 3: Gas Station (LeetCode 134)
─────────────────────────────────────
Circular gas stations. Can complete circle from some start?

Input: gas = [1,2,3,4,5], cost = [3,4,5,1,2]
Output: 3

Key Insight: If total gas >= total cost, solution exists.
Start from index after where running sum is minimum.

Time: O(n) | Space: O(1)
*/
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int totalTank = 0, currTank = 0, start = 0;
    
    for (int i = 0; i < gas.size(); i++) {
        int diff = gas[i] - cost[i];
        totalTank += diff;
        currTank += diff;
        
        if (currTank < 0) {
            start = i + 1;
            currTank = 0;
        }
    }
    
    return totalTank >= 0 ? start : -1;
}


/*
PROBLEM 4: Candy (LeetCode 135)
──────────────────────────────
Each child gets candy based on rating. Higher rating than neighbor = more candy.

Input: ratings = [1,0,2]
Output: 5 (candies: [2,1,2])

Strategy: Two passes - left to right, then right to left

Time: O(n) | Space: O(n)
*/
int candy(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candies(n, 1);
    
    // Left to right: if rating > left neighbor, get more
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }
    
    // Right to left: if rating > right neighbor, get more
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = max(candies[i], candies[i + 1] + 1);
        }
    }
    
    int total = 0;
    for (int c : candies) total += c;
    return total;
}


/*
PROBLEM 5: Assign Cookies (LeetCode 455)
────────────────────────────────────────
Maximize children satisfied. Child i satisfied if cookie size >= greed[i].

Input: g = [1,2,3], s = [1,1]
Output: 1

Strategy: Sort both, match smallest cookie to least greedy child

Time: O(n log n) | Space: O(1)
*/
int findContentChildren(vector<int>& g, vector<int>& s) {
    sort(g.begin(), g.end());
    sort(s.begin(), s.end());
    
    int child = 0;
    for (int i = 0; i < s.size() && child < g.size(); i++) {
        if (s[i] >= g[child]) {
            child++;
        }
    }
    
    return child;
}


/*
PROBLEM 6: Best Time to Buy and Sell Stock II (LeetCode 122)
────────────────────────────────────────────────────────────
Max profit with unlimited transactions.

Input: prices = [7,1,5,3,6,4]
Output: 7 (buy at 1, sell at 5; buy at 3, sell at 6)

Strategy: Capture every upward movement

Time: O(n) | Space: O(1)
*/
int maxProfit(vector<int>& prices) {
    int profit = 0;
    
    for (int i = 1; i < prices.size(); i++) {
        if (prices[i] > prices[i - 1]) {
            profit += prices[i] - prices[i - 1];
        }
    }
    
    return profit;
}


/*
PROBLEM 7: Maximum Subarray (Kadane's Algorithm)
────────────────────────────────────────────────
Find contiguous subarray with maximum sum.

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6 ([4,-1,2,1])

Time: O(n) | Space: O(1)
*/
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0], currSum = nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        currSum = max(nums[i], currSum + nums[i]);
        maxSum = max(maxSum, currSum);
    }
    
    return maxSum;
}


/*
PROBLEM 8: Partition Labels (LeetCode 763)
──────────────────────────────────────────
Partition string so each letter appears in at most one part.

Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]

Strategy: Track last occurrence, extend partition

Time: O(n) | Space: O(1)
*/
vector<int> partitionLabels(string s) {
    vector<int> lastIndex(26, 0);
    for (int i = 0; i < s.size(); i++) {
        lastIndex[s[i] - 'a'] = i;
    }
    
    vector<int> result;
    int start = 0, end = 0;
    
    for (int i = 0; i < s.size(); i++) {
        end = max(end, lastIndex[s[i] - 'a']);
        
        if (i == end) {
            result.push_back(end - start + 1);
            start = i + 1;
        }
    }
    
    return result;
}


/*
PROBLEM 9: Wiggle Subsequence (LeetCode 376)
────────────────────────────────────────────
Find longest subsequence with alternating differences.

Input: nums = [1,7,4,9,2,5]
Output: 6 (entire array)

Time: O(n) | Space: O(1)
*/
int wiggleMaxLength(vector<int>& nums) {
    if (nums.size() < 2) return nums.size();
    
    int up = 1, down = 1;
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > nums[i - 1]) {
            up = down + 1;
        } else if (nums[i] < nums[i - 1]) {
            down = up + 1;
        }
    }
    
    return max(up, down);
}


/*
PROBLEM 10: Monotone Increasing Digits (LeetCode 738)
─────────────────────────────────────────────────────
Largest number <= n with monotone increasing digits.

Input: n = 332
Output: 299

Strategy: Find first decreasing digit, set all after to 9

Time: O(d) where d = digits | Space: O(d)
*/
int monotoneIncreasingDigits(int n) {
    string s = to_string(n);
    int mark = s.size();  // Position to set 9s from
    
    for (int i = s.size() - 1; i > 0; i--) {
        if (s[i] < s[i - 1]) {
            mark = i;
            s[i - 1]--;
        }
    }
    
    for (int i = mark; i < s.size(); i++) {
        s[i] = '9';
    }
    
    return stoi(s);
}


/*
PROBLEM 11: Minimum Increment to Make Array Unique (LeetCode 945)
─────────────────────────────────────────────────────────────────
Increment elements to make all unique. Return min increments.

Input: nums = [3,2,1,2,1,7]
Output: 6 (-> [3,4,1,2,5,7])

Time: O(n log n) | Space: O(1)
*/
int minIncrementForUnique(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    
    int moves = 0;
    
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] <= nums[i - 1]) {
            int target = nums[i - 1] + 1;
            moves += target - nums[i];
            nums[i] = target;
        }
    }
    
    return moves;
}


/*
PROBLEM 12: Queue Reconstruction by Height (LeetCode 406)
─────────────────────────────────────────────────────────
Reconstruct queue from [height, # of taller people in front].

Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]

Strategy: Sort by height desc, then by k asc. Insert at index k.

Time: O(n²) | Space: O(n)
*/
vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    // Sort: taller first, same height -> smaller k first
    sort(people.begin(), people.end(), [](auto& a, auto& b) {
        if (a[0] != b[0]) return a[0] > b[0];
        return a[1] < b[1];
    });
    
    vector<vector<int>> result;
    for (auto& p : people) {
        result.insert(result.begin() + p[1], p);
    }
    
    return result;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Array/Sequence Greedy ===\n\n";
    
    // 1. Jump Game
    vector<int> jump1 = {2, 3, 1, 1, 4};
    cout << "1. Can jump: " << (canJump(jump1) ? "true" : "false") << "\n";
    
    // 2. Jump Game II
    cout << "2. Min jumps: " << jump(jump1) << "\n";
    
    // 3. Gas Station
    vector<int> gas = {1, 2, 3, 4, 5}, cost = {3, 4, 5, 1, 2};
    cout << "3. Start station: " << canCompleteCircuit(gas, cost) << "\n";
    
    // 4. Candy
    vector<int> ratings = {1, 0, 2};
    cout << "4. Min candies: " << candy(ratings) << "\n";
    
    // 6. Stock Profit
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "6. Max profit: " << maxProfit(prices) << "\n";
    
    // 8. Partition Labels
    vector<int> parts = partitionLabels("ababcbacadefegdehijhklij");
    cout << "8. Partitions: ";
    for (int p : parts) cout << p << " ";
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Greedy Choice                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Jump Game                     | Track max reachable index                      |
| Jump Game II                  | Jump when reaching current boundary            |
| Gas Station                   | Reset start when tank goes negative            |
| Candy                         | Two passes: left-to-right, right-to-left       |
| Assign Cookies                | Match smallest cookie to least greedy child    |
| Stock Profit II               | Capture every price increase                   |
| Kadane's                      | Extend or restart at each element              |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

