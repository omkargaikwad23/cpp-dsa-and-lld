/*
================================================================================
                WATCHTOWER MAX PROFIT (Google Interview)
================================================================================

PROBLEM:
A town is building a watchtower at origin (0, 0).
- Each unit height of the watchtower costs H
- The watchtower covers horizontal distance = its height (circular coverage)
- Each house that comes under surveillance pays cost C

Given N houses at (x, y) coordinates, find the MAXIMUM PROFIT.

Profit = (houses covered × C) - (height × H)

================================================================================
                         EXAMPLES
================================================================================

Example: houses = [(3,4), (6,8), (1,1)], H = 2, C = 10
Distances from origin: [5, 10, √2 ≈ 1.41]

If height = 5: covers 2 houses → profit = 2*10 - 5*2 = 10
If height = 10: covers 3 houses → profit = 3*10 - 10*2 = 10
If height = 1.41: covers 1 house → profit = 1*10 - 1.41*2 = 7.18

Maximum profit = 10

================================================================================
                         APPROACH
================================================================================

1. Calculate Euclidean distance of each house from origin
2. Sort distances in ascending order
3. For each possible height (= distance to some house):
   - Houses covered = all houses with distance ≤ height
   - Profit = (count × C) - (height × H)
4. Return maximum profit

KEY INSIGHT: Optimal height is always exactly at some house's distance
             (no benefit to going slightly higher)

TIME:  O(n log n) - sorting distances
SPACE: O(n) - storing distances

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

double maxProfit(vector<pair<double, double>>& houses, double H, double C) {
    // Calculate distances from origin
    vector<double> distances;
    for (auto& house : houses) {
        double d = sqrt(house.first * house.first + house.second * house.second);
        distances.push_back(d);
    }
    
    // Sort distances
    sort(distances.begin(), distances.end());
    
    double maxProfit = 0;  // Can always choose height 0 for profit 0
    
    // Try each house's distance as the tower height
    for (int i = 0; i < distances.size(); i++) {
        double height = distances[i];
        int housesCovered = i + 1;  // All houses up to index i are covered
        double profit = housesCovered * C - height * H;
        maxProfit = max(maxProfit, profit);
    }
    
    return maxProfit;
}

// Follow-up: Watchtower at arbitrary location (tx, ty)
double maxProfitAtLocation(vector<pair<double, double>>& houses, 
                            double tx, double ty, double H, double C) {
    vector<double> distances;
    for (auto& house : houses) {
        double dx = house.first - tx;
        double dy = house.second - ty;
        distances.push_back(sqrt(dx * dx + dy * dy));
    }
    
    sort(distances.begin(), distances.end());
    
    double maxProfit = 0;
    for (int i = 0; i < distances.size(); i++) {
        double height = distances[i];
        int housesCovered = i + 1;
        double profit = housesCovered * C - height * H;
        maxProfit = max(maxProfit, profit);
    }
    
    return maxProfit;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    vector<pair<double, double>> houses = {
        {3.0, 4.0},   // distance = 5
        {6.0, 8.0},   // distance = 10
        {1.0, 0.0}    // distance = 1
    };
    
    double H = 2.0;  // Cost per unit height
    double C = 10.0; // Revenue per house
    
    cout << "Houses: (3,4), (6,8), (1,0)\n";
    cout << "Height cost H = " << H << ", House revenue C = " << C << "\n\n";
    
    double result = maxProfit(houses, H, C);
    cout << "Maximum Profit: " << result << "\n\n";
    
    // Trace through decisions
    cout << "Decision Analysis:\n";
    vector<double> dists = {1.0, 5.0, 10.0};
    for (int i = 0; i < 3; i++) {
        double profit = (i + 1) * C - dists[i] * H;
        cout << "Height=" << dists[i] << ", Houses=" << (i+1) 
             << ", Profit=" << profit << "\n";
    }
    
    return 0;
}

/*
================================================================================
                         FOLLOW-UP QUESTIONS
================================================================================

1. What if watchtower location is given (not at origin)?
   → Modify distance calculation: d = sqrt((x-tx)² + (y-ty)²)

2. What if houses can have different revenue values?
   → Sort by distance, but track cumulative revenue instead of count

3. What if we can build multiple watchtowers?
   → Becomes a covering problem, potentially use greedy or DP

4. What if heights can only be integers?
   → Ceiling of each house distance becomes candidate heights

================================================================================
*/

