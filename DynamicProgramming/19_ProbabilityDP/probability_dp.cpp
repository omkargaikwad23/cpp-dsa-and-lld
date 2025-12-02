/*
================================================================================
                    PATTERN 19: PROBABILITY DP
================================================================================

When to use:
- Probability calculations
- Expected value problems
- Random processes or games

LeetCode Problems:
- 688. Knight Probability in Chessboard
- 808. Soup Servings
- 837. New 21 Game

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Knight Probability in Chessboard (LeetCode 688) ⭐
─────────────────────────────────────────────────────────────
Probability that knight stays on board after k moves.

dp[k][i][j] = probability at (i,j) after k moves

Time: O(k * n²) | Space: O(n²)
*/
double knightProbability(int n, int k, int row, int column) {
    vector<pair<int,int>> moves = {{-2,-1},{-2,1},{-1,-2},{-1,2},
                                   {1,-2},{1,2},{2,-1},{2,1}};
    
    vector<vector<double>> dp(n, vector<double>(n, 0));
    dp[row][column] = 1;
    
    for (int step = 0; step < k; step++) {
        vector<vector<double>> newDp(n, vector<double>(n, 0));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dp[i][j] > 0) {
                    for (auto& [di, dj] : moves) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                            newDp[ni][nj] += dp[i][j] / 8.0;
                        }
                    }
                }
            }
        }
        
        dp = newDp;
    }
    
    double prob = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            prob += dp[i][j];
        }
    }
    
    return prob;
}


/*
PROBLEM 2: Soup Servings (LeetCode 808)
───────────────────────────────────────
Serve soup with 4 options. Find P(A empty first) + 0.5 * P(both empty).

When n is large, probability approaches 1.

Time: O(n²) but bounded | Space: O(n²)
*/
double soupServings(int n) {
    if (n >= 4800) return 1.0;  // Probability very close to 1
    
    n = (n + 24) / 25;  // Scale down
    
    vector<vector<double>> memo(n + 1, vector<double>(n + 1, -1));
    
    function<double(int, int)> dp = [&](int a, int b) -> double {
        if (a <= 0 && b <= 0) return 0.5;
        if (a <= 0) return 1.0;
        if (b <= 0) return 0.0;
        
        if (memo[a][b] >= 0) return memo[a][b];
        
        return memo[a][b] = 0.25 * (
            dp(a - 4, b) +
            dp(a - 3, b - 1) +
            dp(a - 2, b - 2) +
            dp(a - 1, b - 3)
        );
    };
    
    return dp(n, n);
}


/*
PROBLEM 3: New 21 Game (LeetCode 837)
─────────────────────────────────────
Draw cards 1 to maxPts until >= k. Find P(score <= n).

dp[i] = probability of reaching score i
Use sliding window for efficiency.

Time: O(n + maxPts) | Space: O(n)
*/
double new21Game(int n, int k, int maxPts) {
    if (k == 0 || n >= k + maxPts) return 1.0;
    
    vector<double> dp(n + 1, 0);
    dp[0] = 1;
    
    double windowSum = 1;  // Sum of dp[i-maxPts..i-1]
    double result = 0;
    
    for (int i = 1; i <= n; i++) {
        dp[i] = windowSum / maxPts;
        
        if (i < k) {
            windowSum += dp[i];
        } else {
            result += dp[i];
        }
        
        if (i >= maxPts) {
            windowSum -= dp[i - maxPts];
        }
    }
    
    return result;
}


/*
PROBLEM 4: Toss Strange Coins (LeetCode 1230)
─────────────────────────────────────────────
Coins with different probabilities. P(exactly target heads).

Time: O(n * target) | Space: O(target)
*/
double probabilityOfHeads(vector<double>& prob, int target) {
    int n = prob.size();
    vector<double> dp(target + 1, 0);
    dp[0] = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = min(i + 1, target); j >= 0; j--) {
            dp[j] = dp[j] * (1 - prob[i]);  // Tail
            if (j > 0) dp[j] += dp[j-1] * prob[i];  // Head
        }
    }
    
    return dp[target];
}


/*
PROBLEM 5: Probability of a Two Boxes Having Same Balls (LeetCode 1467)
───────────────────────────────────────────────────────────────────────
Distribute balls into two boxes. P(same number of distinct colors).

Time: O(2^n * total * colors) | Space: O(total * colors)
*/
class Solution1467 {
    vector<int> balls;
    int total;
    double validWays, totalWays;
    
    double factorial(int n) {
        double result = 1;
        for (int i = 2; i <= n; i++) result *= i;
        return result;
    }
    
    double multinomial(vector<int>& counts) {
        double result = factorial(total / 2);
        for (int c : counts) result /= factorial(c);
        return result;
    }
    
    void backtrack(int idx, int sum1, int colors1, int colors2, 
                   vector<int>& box1, vector<int>& box2) {
        if (idx == balls.size()) {
            if (sum1 != total / 2) return;
            
            double ways = multinomial(box1) * multinomial(box2);
            totalWays += ways;
            if (colors1 == colors2) validWays += ways;
            return;
        }
        
        for (int i = 0; i <= balls[idx]; i++) {
            box1.push_back(i);
            box2.push_back(balls[idx] - i);
            
            int newColors1 = colors1 + (i > 0 ? 1 : 0);
            int newColors2 = colors2 + (balls[idx] - i > 0 ? 1 : 0);
            
            backtrack(idx + 1, sum1 + i, newColors1, newColors2, box1, box2);
            
            box1.pop_back();
            box2.pop_back();
        }
    }
    
public:
    double getProbability(vector<int>& balls) {
        this->balls = balls;
        total = 0;
        for (int b : balls) total += b;
        validWays = totalWays = 0;
        
        vector<int> box1, box2;
        backtrack(0, 0, 0, 0, box1, box2);
        
        return validWays / totalWays;
    }
};


/*
PROBLEM 6: Random Point in Non-overlapping Rectangles (LeetCode 497)
────────────────────────────────────────────────────────────────────
Pick random point uniformly from union of rectangles.

Weighted random selection by area.

Time: O(log n) per pick | Space: O(n)
*/
class Solution497 {
    vector<vector<int>> rects;
    vector<int> prefixArea;
    int totalArea;
    
public:
    Solution497(vector<vector<int>>& rects) : rects(rects) {
        totalArea = 0;
        for (auto& r : rects) {
            totalArea += (r[2] - r[0] + 1) * (r[3] - r[1] + 1);
            prefixArea.push_back(totalArea);
        }
    }
    
    vector<int> pick() {
        int target = rand() % totalArea;
        int idx = upper_bound(prefixArea.begin(), prefixArea.end(), target) - prefixArea.begin();
        
        auto& r = rects[idx];
        int width = r[2] - r[0] + 1;
        int height = r[3] - r[1] + 1;
        int offset = target - (idx > 0 ? prefixArea[idx-1] : 0);
        
        return {r[0] + offset % width, r[1] + offset / width};
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Probability DP ===\n\n";
    
    // Knight Probability
    cout << "1. Knight prob (n=3, k=2, row=0, col=0): " 
         << knightProbability(3, 2, 0, 0) << "\n";
    
    // Soup Servings
    cout << "2. Soup servings (n=50): " << soupServings(50) << "\n";
    
    // New 21 Game
    cout << "3. New 21 (n=10, k=1, maxPts=10): " << new21Game(10, 1, 10) << "\n";
    
    // Toss Coins
    vector<double> probs = {0.4, 0.5, 0.6};
    cout << "4. P(2 heads): " << probabilityOfHeads(probs, 2) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

PROBABILITY DP PATTERNS:
    - State: (position, some condition)
    - Transition: Sum of probabilities from all sources
    - Base: Usually probability 1 at starting state

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Key Insight                                    |
+───────────────────────────────+────────────────────────────────────────────────+
| Knight Probability            | Each move has 1/8 probability                  |
| Soup Servings                 | Large n → prob approaches 1                    |
| New 21 Game                   | Sliding window for efficiency                  |
| Coin Toss                     | Standard probability DP                        |
+───────────────────────────────+────────────────────────────────────────────────+

EXPECTED VALUE:
    E[X] = Σ (value * probability)
    
Useful for optimization problems with random elements.

================================================================================
*/

