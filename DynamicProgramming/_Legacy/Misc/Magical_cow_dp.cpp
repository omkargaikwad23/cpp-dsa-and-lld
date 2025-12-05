/*
================================================================================
                    MAGICAL COWS (Kattis Problem)
================================================================================

Problem: https://open.kattis.com/problems/magicalcows

- N farms, each starts with some number of cows
- Every day, cows in each farm DOUBLE
- If a farm exceeds capacity C, it SPLITS into 2 farms (each gets half)
- Regulator visits on certain days and counts TOTAL FARMS
- Answer queries: how many farms exist on day D?

Example:
  C = 2 (max cows per farm)
  Initial: [1, 2, 1] (3 farms with 1, 2, 1 cows)
  
  Day 0: farms = 3, cows per farm = [1, 2, 1]
  Day 1: cows double → [2, 4, 2]
         Farm with 4 cows splits → [2, 2, 2, 2]
         farms = 4

Key Insight:
  - Track how many farms have exactly j cows on day i
  - dp[day][cows] = number of farms with 'cows' cows on 'day'
  
Transition:
  - If j*2 <= C: cows double, farm stays as one → dp[i+1][j*2] += dp[i][j]
  - If j*2 > C:  farm splits into 2 → dp[i+1][j] += dp[i][j] * 2

Time: O(50 × C)  |  Space: O(50 × C)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

long long countFarms(int C, vector<int>& initialCows, int queryDay) {
    // dp[day][cows] = number of farms with exactly 'cows' cows on 'day'
    vector<vector<long long>> dp(queryDay + 1, vector<long long>(C + 1, 0));
    
    // Initialize day 0 with initial farm distribution
    for (int cows : initialCows) {
        dp[0][cows]++;
    }
    
    // Simulate only up to queryDay
    for (int day = 0; day < queryDay; day++) {
        for (int cows = 1; cows <= C; cows++) {
            if (dp[day][cows] == 0) continue;
            
            if (cows * 2 <= C) {
                // Cows double, farm stays intact
                dp[day + 1][cows * 2] += dp[day][cows];
            } else {
                // Farm splits into 2 (each gets 'cows' cows after doubling)
                dp[day + 1][cows] += dp[day][cows] * 2;
            }
        }
    }
    
    // Count total farms on query day
    long long totalFarms = 0;
    for (int cows = 1; cows <= C; cows++) {
        totalFarms += dp[queryDay][cows];
    }
    return totalFarms;
}

int main() {
    cout << "=== Magical Cows ===\n\n";
    
    // Test Case: C=2, initial farms have [1, 2, 1] cows
    int C = 2;
    vector<int> initialCows = {1, 2, 1};
    
    cout << "Capacity C = " << C << "\n";
    cout << "Initial cows per farm: [1, 2, 1]\n\n";
    
    cout << "Day 0: " << countFarms(C, initialCows, 0) << " farms\n";
    cout << "Day 1: " << countFarms(C, initialCows, 1) << " farms\n";
    cout << "Day 2: " << countFarms(C, initialCows, 2) << " farms\n";
    cout << "Day 3: " << countFarms(C, initialCows, 3) << " farms\n";
    cout << "Day 5: " << countFarms(C, initialCows, 5) << " farms\n";
    
    cout << "\nExpected pattern: 3 → 4 → 8 → 16 → 64 (exponential)\n";
    
    return 0;
}

/*
================================================================================
                        DRY RUN EXAMPLE
================================================================================

Input: C=2, N=3, initial cows = [1, 2, 1]

Day 0:
  dp[0][1] = 2  (two farms with 1 cow)
  dp[0][2] = 1  (one farm with 2 cows)
  Total farms = 3

Day 1:
  Farms with 1 cow → cows double to 2, still ≤ C
    dp[1][2] += dp[0][1] = 2
  
  Farms with 2 cows → cows double to 4, exceeds C=2
    Farm splits: dp[1][2] += dp[0][1] * 2 = 2
  
  dp[1][2] = 2 + 2 = 4
  Total farms = 4

Day 2:
  Farms with 2 cows → double to 4, exceeds C=2
    dp[2][2] += dp[1][2] * 2 = 8
  Total farms = 8

Pattern: Farms grow exponentially!

================================================================================
                        KEY INSIGHTS
================================================================================

1. WHY dp[day+1][cows] += dp[day][cows] * 2 when splitting?
   - If farm has 'cows' and doubles to '2*cows' which exceeds C
   - It splits into TWO farms, each with 'cows' (half of 2*cows)
   - So we get 2x farms with same cow count

2. WHY only track up to day 50?
   - Problem constraint: queries are for days 0-50

3. WHY use long long?
   - Farms can double each day, 2^50 is huge!

================================================================================
*/
