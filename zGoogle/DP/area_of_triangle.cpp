#include <bits/stdc++.h>
using namespace std;

int maxTriangleArea(vector<vector<int>> &grid) {
    if(grid.size() == 0) return 0;
    int n = grid.size(), m = grid[0].size();
    // store x & y direction prefix sum
    vector<vector<pair<int, int>>> prefixSum(n + 2, vector<pair<int, int>>(m + 2, {0, 0}));
        
    int maxArea = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = m; j > 0; j--) {
            if(grid[i - 1][j - 1] == 1) {
                prefixSum[i][j].first = prefixSum[i][j + 1].first + 1;
                prefixSum[i][j].second = prefixSum[i - 1][j].second + 1;
            }
            int maxLen = min(prefixSum[i][j].first, prefixSum[i][j].second);
            int curArea = maxLen * (maxLen + 1) / 2;
            maxArea = max(maxArea, curArea);
        }
    }
    return maxArea;
}

int main() {
    vector<vector<int>> grid1 = {
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {0, 1, 1, 0}
    };
    vector<vector<int>> grid2 = {
        {0, 1, 0, 1, 0},
        {0, 1, 1, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 1, 1, 1, 1}
    };
    vector<vector<int>> grid3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    vector<vector<int>> grid4 = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    vector<vector<int>> grid5 = {
        {1}
    };
    
    cout << "Grid 1: " << maxTriangleArea(grid1) << endl;
    cout << "Grid 2: " << maxTriangleArea(grid2) << endl;
    cout << "Grid 3: " << maxTriangleArea(grid3) << endl;
    cout << "Grid 4: " << maxTriangleArea(grid4) << endl;
    cout << "Grid 5: " << maxTriangleArea(grid5) << endl;

    return 0;
}

/*
Grid 1: 6
Grid 2: 10
Grid 3: 0
Grid 4: 6
Grid 5: 1
*/