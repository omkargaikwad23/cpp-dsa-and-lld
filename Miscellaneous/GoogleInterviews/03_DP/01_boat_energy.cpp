/*
================================================================================
                    BOAT ENERGY TRAVEL (Google Interview)
================================================================================

PROBLEM:
You have maximum initial energy K (K < 1000) and array A of length N 
representing wind speed on N days.

You're stuck on a boat. Each day you can either:
1. TRAVEL: Move ahead A[i] distance, energy decreases by 1
2. REST: Stay put, energy increases by 1 (cannot exceed K)

Find the MAXIMUM DISTANCE you can travel without energy dropping to negative.

================================================================================
                         EXAMPLES
================================================================================

Example: A = [2, 3, 4, 5], K = 1
- Day 0: Rest (energy 1→1, can't exceed K)
- Day 1: Travel 3 (energy 1→0, distance = 3)
- Day 2: Rest (energy 0→1)
- Day 3: Travel 5 (energy 1→0, distance = 8)
Output: 8

================================================================================
                         APPROACH
================================================================================

DP STATE: dp[i][e] = max distance achievable at day i with energy e

TRANSITIONS:
1. Travel: dp[i+1][e-1] = dp[i][e] + A[i]  (if e > 0)
2. Rest:   dp[i+1][min(e+1, K)] = dp[i][e]

BASE CASE: dp[0][K] = 0

OPTIMIZATION: If K >= N, we can travel every day, so answer = sum(A)

TIME:  O(N × K)
SPACE: O(N × K), can be optimized to O(K)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// APPROACH 1: Top-Down Memoization
// ═══════════════════════════════════════════════════════════════════════════

class Solution {
private:
    vector<vector<int>> memo;
    
    int solve(vector<int>& A, int index, int energy, int maxEnergy) {
        // Base case: no more days
        if (index == A.size()) return 0;
        
        // Check memo
        if (memo[index][energy] != -1) return memo[index][energy];
        
        // Option 1: Rest (gain energy, capped at maxEnergy)
        int restoredEnergy = min(energy + 1, maxEnergy);
        int restDistance = solve(A, index + 1, restoredEnergy, maxEnergy);
        
        // Option 2: Travel (if energy > 0)
        int travelDistance = 0;
        if (energy > 0) {
            travelDistance = A[index] + solve(A, index + 1, energy - 1, maxEnergy);
        }
        
        return memo[index][energy] = max(restDistance, travelDistance);
    }
    
public:
    int maxDistance(vector<int>& A, int K) {
        int n = A.size();
        
        // Optimization: if we have enough energy for all days
        if (K >= n) {
            int total = 0;
            for (int x : A) total += x;
            return total;
        }
        
        memo.assign(n, vector<int>(K + 1, -1));
        return solve(A, 0, K, K);
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// APPROACH 2: Bottom-Up DP
// ═══════════════════════════════════════════════════════════════════════════

int maxDistanceBottomUp(vector<int>& A, int K) {
    int n = A.size();
    
    if (K >= n) {
        return accumulate(A.begin(), A.end(), 0);
    }
    
    // dp[e] = max distance achievable with energy e at current day
    vector<int> dp(K + 1, 0);
    
    for (int i = 0; i < n; i++) {
        vector<int> newDp(K + 1, 0);
        
        for (int e = 0; e <= K; e++) {
            // Option 1: Rest
            int newEnergy = min(e + 1, K);
            newDp[newEnergy] = max(newDp[newEnergy], dp[e]);
            
            // Option 2: Travel (if e > 0)
            if (e > 0) {
                newDp[e - 1] = max(newDp[e - 1], dp[e] + A[i]);
            }
        }
        
        dp = newDp;
    }
    
    return *max_element(dp.begin(), dp.end());
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    Solution sol;
    
    // Test case 1
    vector<int> A1 = {2, 3, 4, 5};
    int K1 = 1;
    cout << "Test 1: A = [2,3,4,5], K = " << K1 << "\n";
    cout << "Top-Down: " << sol.maxDistance(A1, K1) << "\n";
    cout << "Bottom-Up: " << maxDistanceBottomUp(A1, K1) << "\n\n";
    
    // Test case 2: More energy than days
    vector<int> A2 = {1, 2, 3};
    int K2 = 5;
    cout << "Test 2: A = [1,2,3], K = " << K2 << " (K >= N)\n";
    cout << "Result: " << sol.maxDistance(A2, K2) << " (should be 6)\n\n";
    
    // Test case 3
    vector<int> A3 = {10, 1, 1, 1, 10};
    int K3 = 2;
    cout << "Test 3: A = [10,1,1,1,10], K = " << K3 << "\n";
    cout << "Top-Down: " << sol.maxDistance(A3, K3) << "\n";
    cout << "Bottom-Up: " << maxDistanceBottomUp(A3, K3) << "\n";
    
    return 0;
}

/*
================================================================================
                         FOLLOW-UP QUESTIONS
================================================================================

1. Can wind speed be negative (headwind)?
   → Allow negative A[i], same logic applies

2. What if traveling costs variable energy based on wind?
   → Modify transition: energy -= cost[i] instead of energy -= 1

3. What if we can only rest limited times?
   → Add another dimension: dp[day][energy][rests_remaining]

================================================================================
*/

