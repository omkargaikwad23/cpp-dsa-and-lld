
/*
Calculate the no of distinct paths from the bottomost left corner to bottomost right corner, given that we can go only 3 ways:
upward right position
downward right position 
direct right.


Followup question: Let's say we add coins in the grid. Find the total number of ways such that we are able to collect all coins, starting from bottom left and reaching bottom right and following the same allowed directions as in question 1.

*/

#include <iostream>
#include <vector>
using namespace std;

int solve(int n, int m){
    vector<vector<int> > dp(n, vector<int>(m, 0));

    dp[n-1][0] = 1; //bottom left corner

    for(int j = 1; j < m; j++) { // Iterate columns first
        for(int i = 0; i < n; i++) { // Then iterate rows
            dp[i][j] = dp[i][j-1]; // Move right
            if(i > 0)
                dp[i][j] += dp[i-1][j-1]; // Up-right
            if(i+1 < n)
                dp[i][j] += dp[i+1][j-1]; // Down-right
        }
    }
    return dp[n-1][m-1];
}

// Function to find the number of ways to reach bottom-right while collecting all coins
int countWaysToCollectCoins(vector<vector<int>>& grid) {
    int n = grid.size();    // Number of rows
    int m = grid[0].size(); // Number of columns

    // Count total coins in the grid
    int totalCoins = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            totalCoins += grid[i][j]; 
        }
    }

    // 3D DP table: dp[i][j][c] → number of ways to reach (i, j) with exactly 'c' coins collected
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(totalCoins + 1, 0)));

    // Start at the bottom-left corner (n-1, 0)
    dp[n-1][0][grid[n-1][0]] = 1;

    // Iterate through the grid column by column
    for (int j = 1; j < m; j++) {
        for (int i = 0; i < n; i++) {
            for (int c = 0; c <= totalCoins; c++) {
                if (dp[i][j-1][c] > 0) {
                    int newC = c + grid[i][j]; // If current cell has a coin, increase the count
                    dp[i][j][newC] += dp[i][j-1][c]; // Move from left
                }
                if (i > 0 && dp[i-1][j-1][c] > 0) {
                    int newC = c + grid[i][j];
                    dp[i][j][newC] += dp[i-1][j-1][c]; // Move from top-left
                }
                if (i+1 < n && dp[i+1][j-1][c] > 0) {
                    int newC = c + grid[i][j];
                    dp[i][j][newC] += dp[i+1][j-1][c]; // Move from bottom-left
                }
            }
        }
    }

    // The final answer is the number of ways to reach (n-1, m-1) while collecting all coins
    return dp[n-1][m-1][totalCoins];
}

// Driver function
int main() {
    vector<vector<int>> grid = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 0, 1, 1, 0},
        {1, 0, 0, 0, 1}
    };

    cout << "Number of ways to collect all coins: " << countWaysToCollectCoins(grid) << endl;
    
    return 0;

    cout << solve(4, 5) << endl;
    cout << solve(1, 1) << endl;
    cout << solve(2,3) << endl;
    cout << solve(2,3) << endl;
    
}




