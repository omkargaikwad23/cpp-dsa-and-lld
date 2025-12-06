#include <bits/stdc++.h>
using namespace std;

/*
================================================================================
                        MONOTONIC STACK CONCEPTS
================================================================================

A Monotonic Stack is a stack that maintains elements in either:
  - Strictly Increasing order (from bottom to top)
  - Strictly Decreasing order (from bottom to top) -> pop smaller/equal elements
monotonic decreasing stack

================================================================================
1. MONOTONIC DECREASING STACK (Elements decrease from bottom to top)
================================================================================

Stack maintains: bottom [...larger...smaller...] top

USE CASES:
- Next Greater Element (to the right)
- Previous Greater Element (to the left)
- Find how many elements to the right are smaller
- Maximum rectangle in histogram (combined with increasing)
- Stock Span Problem

TEMPLATE:
    stack<int> stk;  // stores indices
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && arr[stk.top()] <= arr[i]) {
            stk.pop();  // pop smaller or equal elements
        }
        // stk.top() is the index of previous greater element (if exists)
        stk.push(i);
    }

PROBLEMS SOLVED:
1. Next Greater Element I & II (LeetCode 496, 503)
2. Daily Temperatures (LeetCode 739)
3. Stock Span Problem (LeetCode 901)
4. Online Stock Span
5. Number of Visible People in a Queue (LeetCode 1944)

================================================================================
2. MONOTONIC INCREASING STACK (Elements increase from bottom to top)
================================================================================

Stack maintains: bottom [...smaller...larger...] top

USE CASES:
- Next Smaller Element (to the right)
- Previous Smaller Element (to the left)
- Find how many elements to the right are greater
- Largest Rectangle in Histogram
- Trapping Rain Water
- Remove K Digits

TEMPLATE:
    stack<int> stk;  // stores indices
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) {
            stk.pop();  // pop larger or equal elements
        }
        // stk.top() is the index of previous smaller element (if exists)
        stk.push(i);
    }

PROBLEMS SOLVED:
1. Next Smaller Element
2. Largest Rectangle in Histogram (LeetCode 84)
3. Maximal Rectangle (LeetCode 85)
4. Trapping Rain Water (LeetCode 42)
5. Remove K Digits (LeetCode 402)
6. Sum of Subarray Minimums (LeetCode 907)
7. Sum of Subarray Ranges (LeetCode 2104)

================================================================================
*/


// ============================================================================
// MONOTONIC DECREASING STACK EXAMPLES
// ============================================================================

/*
PROBLEM 1: Next Greater Element (Circular Array)
------------------------------------------------
Input: nums = [1,2,3,4,3]
Output: [2,3,4,-1,4]

For circular: nums = [1,2,1]
Output: [2,-1,2]
*/
vector<int> nextGreaterElementCircular(vector<int>& nums) {
    int n = nums.size();
    stack<int> stk;  // monotonic decreasing (stores indices)
    vector<int> ans(n, -1);
    
    // First pass: push all indices (simulates circular nature)
    for (int i = n - 1; i >= 0; i--) 
        stk.push(i);
    
    // Second pass: find next greater for each element
    for (int i = n - 1; i >= 0; i--) {
        // Pop elements that are smaller or equal (maintain decreasing order)
        while (!stk.empty() && nums[stk.top()] <= nums[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            ans[i] = nums[stk.top()];
        }
        stk.push(i);
    }
    return ans;
}


/*
PROBLEM 2: Next Greater Element (Non-circular, Left to Right approach)
----------------------------------------------------------------------
Input: nums = [2,1,2,4,3]
Output: [4,2,4,-1,-1]
*/
vector<int> nextGreaterElement(vector<int>& nums) {
    int n = nums.size();
    stack<int> stk;  // monotonic decreasing (stores indices)
    vector<int> ans(n, -1);
    
    for (int i = 0; i < n; i++) {
        // For all elements in stack that are smaller than current
        // current element is their next greater element
        while (!stk.empty() && nums[stk.top()] < nums[i]) {
            ans[stk.top()] = nums[i];
            stk.pop();
        }
        stk.push(i);
    }
    return ans;
}


/*
PROBLEM 3: Daily Temperatures (LeetCode 739)
--------------------------------------------
Given temperatures, return array where ans[i] = number of days 
until a warmer temperature.

Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]
*/
vector<int> dailyTemperatures(vector<int>& temperatures) {
    int n = temperatures.size();
    stack<int> stk;  // monotonic decreasing
    vector<int> ans(n, 0);
    
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && temperatures[stk.top()] < temperatures[i]) {
            int idx = stk.top();
            stk.pop();
            ans[idx] = i - idx;  // number of days to wait
        }
        stk.push(i);
    }
    return ans;
}


/*
PROBLEM 4: Stock Span Problem (LeetCode 901)
--------------------------------------------
Span = number of consecutive days before (including today) 
where price was <= today's price.

Input: prices = [100, 80, 60, 70, 60, 75, 85]
Output: [1, 1, 1, 2, 1, 4, 6]
*/
vector<int> stockSpan(vector<int>& prices) {
    int n = prices.size();
    stack<int> stk;  // monotonic decreasing (stores indices)
    vector<int> span(n);
    
    for (int i = 0; i < n; i++) {
        // Pop all prices smaller than or equal to current
        while (!stk.empty() && prices[stk.top()] <= prices[i]) {
            stk.pop();
        }
        // Span = distance from previous greater element (or start)
        span[i] = stk.empty() ? (i + 1) : (i - stk.top());
        stk.push(i);
    }
    return span;
}


// ============================================================================
// MONOTONIC INCREASING STACK EXAMPLES
// ============================================================================

/*
PROBLEM 5: Next Smaller Element
-------------------------------
Input: nums = [4, 8, 5, 2, 25]
Output: [2, 5, 2, -1, -1]
*/
vector<int> nextSmallerElement(vector<int>& nums) {
    int n = nums.size();
    stack<int> stk;  // monotonic increasing (stores indices)
    vector<int> ans(n, -1);
    
    for (int i = 0; i < n; i++) {
        // For all elements in stack that are greater than current
        // current element is their next smaller element
        while (!stk.empty() && nums[stk.top()] > nums[i]) {
            ans[stk.top()] = nums[i];
            stk.pop();
        }
        stk.push(i);
    }
    return ans;
}


/*
PROBLEM 6: Previous Smaller Element
-----------------------------------
Input: nums = [4, 5, 2, 10, 8]
Output: [-1, 4, -1, 2, 2]
*/
vector<int> previousSmallerElement(vector<int>& nums) {
    int n = nums.size();
    stack<int> stk;  // monotonic increasing
    vector<int> ans(n, -1);
    
    for (int i = 0; i < n; i++) {
        // Pop all elements >= current (maintain increasing order)
        while (!stk.empty() && nums[stk.top()] >= nums[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            ans[i] = nums[stk.top()];
        }
        stk.push(i);
    }
    return ans;
}


/*
PROBLEM 7: Largest Rectangle in Histogram (LeetCode 84)
-------------------------------------------------------
Find the largest rectangular area in a histogram.

Input: heights = [2,1,5,6,2,3]
Output: 10 (rectangle with height 5, width 2)

Approach: For each bar, find:
- Previous smaller element (left boundary)
- Next smaller element (right boundary)
- Width = right - left - 1
- Area = height * width
*/
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    stack<int> stk;  // monotonic increasing
    int maxArea = 0;
    
    for (int i = 0; i <= n; i++) {
        int currHeight = (i == n) ? 0 : heights[i];
        
        // pop larger/equal elements
        while (!stk.empty() && heights[stk.top()] > currHeight) {
            int height = heights[stk.top()];
            stk.pop();
            int width = stk.empty() ? i : (i - stk.top() - 1);
            maxArea = max(maxArea, height * width);
        }
        stk.push(i);
    }
    return maxArea;
}


/*
PROBLEM 8: Trapping Rain Water (LeetCode 42)
--------------------------------------------
Given elevation map, compute trapped water after rain.

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6

Stack approach: Find water trapped between bars.
*/
int trap(vector<int>& height) {
    int n = height.size();
    stack<int> stk;  // monotonic increasing (sort of)
    int water = 0;
    
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && height[stk.top()] < height[i]) {
            int bottom = stk.top();
            stk.pop();
            if (stk.empty()) break;
            
            int width = i - stk.top() - 1;
            int boundedHeight = min(height[i], height[stk.top()]) - height[bottom];
            water += width * boundedHeight;
        }
        stk.push(i);
    }
    return water;
}


/*
PROBLEM 9: Sum of Subarray Minimums (LeetCode 907)
--------------------------------------------------
Return sum of min(subarray) for all subarrays, mod 10^9+7.

Input: arr = [3,1,2,4]
Output: 17
Subarrays: [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]
Minimums:   3    1    2    4    1      1      2      1        1        1
Sum = 17

Key insight: For each element, count how many subarrays have it as minimum.
- Find previous smaller element (left boundary)
- Find next smaller element (right boundary)
- Count = (i - left) * (right - i)
*/
int sumSubarrayMins(vector<int>& arr) {
    const int MOD = 1e9 + 7;
    int n = arr.size();
    
    vector<int> left(n), right(n);
    stack<int> stk;
    
    // Previous smaller element
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && arr[stk.top()] >= arr[i]) {
            stk.pop();
        }
        left[i] = stk.empty() ? -1 : stk.top();
        stk.push(i);
    }
    
    while (!stk.empty()) stk.pop();
    
    // Next smaller element
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && arr[stk.top()] > arr[i]) {
            stk.pop();
        }
        right[i] = stk.empty() ? n : stk.top();
        stk.push(i);
    }
    
    // Calculate contribution of each element
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long leftCount = i - left[i];
        long long rightCount = right[i] - i;
        ans = (ans + (long long)arr[i] * leftCount % MOD * rightCount % MOD) % MOD;
    }
    return ans;
}


/*
PROBLEM 10: Remove K Digits (LeetCode 402)
------------------------------------------
Remove k digits to make the smallest possible number.

Input: num = "1432219", k = 3
Output: "1219"
Remove: 4, 3, 2 -> "1219"

Approach: Use monotonic increasing stack.
Remove larger digits when a smaller digit comes.
*/
string removeKdigits(string num, int k) {
    stack<char> stk;  // monotonic increasing
    
    for (char digit : num) {
        // Remove larger digits from stack if we can
        while (!stk.empty() && k > 0 && stk.top() > digit) {
            stk.pop();
            k--;
        }
        stk.push(digit);
    }
    
    // Remove remaining k digits from end
    while (k > 0 && !stk.empty()) {
        stk.pop();
        k--;
    }
    
    // Build result
    string result = "";
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }
    reverse(result.begin(), result.end());
    
    // Remove leading zeros
    int start = 0;
    while (start < result.size() && result[start] == '0') {
        start++;
    }
    
    result = result.substr(start);
    return result.empty() ? "0" : result;
}


// ============================================================================
// SUMMARY TABLE
// ============================================================================
/*
+---------------------------+------------------------+------------------------+
| Problem Pattern           | Stack Type             | What Stack Stores      |
+---------------------------+------------------------+------------------------+
| Next Greater Element      | Monotonic Decreasing   | Indices of elements    |
| Previous Greater Element  | Monotonic Decreasing   | Indices of elements    |
| Daily Temperatures        | Monotonic Decreasing   | Indices of days        |
| Stock Span               | Monotonic Decreasing   | Indices of prices      |
+---------------------------+------------------------+------------------------+
| Next Smaller Element      | Monotonic Increasing   | Indices of elements    |
| Previous Smaller Element  | Monotonic Increasing   | Indices of elements    |
| Largest Rectangle Hist    | Monotonic Increasing   | Indices of heights     |
| Trapping Rain Water       | Monotonic Increasing   | Indices of heights     |
| Sum of Subarray Minimums  | Monotonic Increasing   | Indices of elements    |
| Remove K Digits           | Monotonic Increasing   | Digit characters       |
+---------------------------+------------------------+------------------------+

KEY INSIGHTS:
1. Decreasing Stack -> Looking for GREATER elements
2. Increasing Stack -> Looking for SMALLER elements
3. Usually store INDICES (not values) to calculate distances
4. Iterate left-to-right OR right-to-left based on "next" vs "previous"
5. Time Complexity: O(n) - each element pushed and popped at most once
6. Space Complexity: O(n) - stack size
*/


int main() {
    // Example: Next Greater Element (Circular)
    vector<int> nums1 = {1, 2, 3, 4, 3};
    vector<int> result1 = nextGreaterElementCircular(nums1);
    // Expected: [2, 3, 4, -1, 4]
    
    // Example: Daily Temperatures
    vector<int> temps = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result2 = dailyTemperatures(temps);
    // Expected: [1, 1, 4, 2, 1, 1, 0, 0]
    
    // Example: Largest Rectangle in Histogram
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    int maxArea = largestRectangleArea(heights);
    // Expected: 10
    
    // Example: Remove K Digits
    string smallest = removeKdigits("1432219", 3);
    // Expected: "1219"
    
    return 0;
}

