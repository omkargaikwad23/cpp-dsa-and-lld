/*
Q1) you are given maximum initial energy k (k<1000) and array A of length n denoting wind speed on n days. he is stuck on a boat and each day he can either choose to move or stay put.. each day he decides to travel he will move ahead A[i] Dist and his energy decreases by 1 and if he decides to stay put his energy increases by 1.

What is the maximum distance he can travel without dropping his energy to negative after n days.
//Clarification questions i asked- what if energy is k and he decides to rest only- would energy go beyond maximum? answer=No, it will remain k

//can the wind speed be negative as well, denoting wind flowing in other direction? answer= No (initially)
*/

/*
1. if K >= N return sum of the given array
2. dp[i][k]

base:
k < 0 return 0;

2 options:
1. stay -> k+1, should not cross original k
if(k > 0)
    2. move -> k-1 and add dist travelled


Time: O(n * k)
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> memo;

int getMaxDistance(vector<int> &A, int index, int energy, int maxEnergy) {
    // Base case: If we have processed all days or energy is depleted
    if (index == A.size() || energy < 0) return 0;
    if (memo[index][energy] != -1) return memo[index][energy];

    // Case 1: Move forward, consume 1 energy, and add current day's wind speed to the distance
    int moveDistance = A[index] + getMaxDistance(A, index + 1, energy - 1, maxEnergy);

    // Case 2: Stay put, regain 1 energy (but not exceeding maxEnergy)
    int restoredEnergy = min(energy + 1, maxEnergy);
    int stayDistance = getMaxDistance(A, index + 1, restoredEnergy, maxEnergy);

    // Return the maximum of both choices
    return memo[index][energy] = max(moveDistance, stayDistance);
}

int main() {
    int n = 5;
    vector<int> A = {2, 3, 4, 5, 3};
    int k = 3; // Maximum initial energy
    
    memo.assign(n, vector<int>(k+1, -1));

    int maxDistance = getMaxDistance(A, 0, k, k);
   
    cout << "Maximum distance traveled: " << maxDistance << endl;
}


