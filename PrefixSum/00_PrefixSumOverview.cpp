/*
================================================================================
                    PREFIX SUM - OVERVIEW
================================================================================

Prefix sum enables O(1) range queries after O(n) preprocessing.
Essential pattern for Google interviews!

================================================================================
                           1D PREFIX SUM
================================================================================

Array:     [a₀, a₁, a₂, a₃, a₄]
Prefix:    [0, a₀, a₀+a₁, a₀+a₁+a₂, ...]

Range Sum [i, j] = prefix[j+1] - prefix[i]

TEMPLATE:
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + arr[i];
    }
    // Sum [l, r] = prefix[r + 1] - prefix[l]

================================================================================
                           2D PREFIX SUM
================================================================================

For matrix M, prefix[i][j] = sum of rectangle (0,0) to (i-1,j-1)

Build:
    prefix[i][j] = M[i-1][j-1] + prefix[i-1][j] + prefix[i][j-1] - prefix[i-1][j-1]

Query (r1,c1) to (r2,c2):
    sum = prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]

================================================================================
                           DIFFERENCE ARRAY
================================================================================

For range updates: add val to range [l, r]
    diff[l] += val
    diff[r + 1] -= val
    
Final array = prefix sum of diff array

================================================================================
                           PREFIX + HASHMAP
================================================================================

For "subarray sum = k" problems:
- Store prefix sum frequencies in map
- At each index, check if (currentSum - k) exists

================================================================================
                           FILE ORGANIZATION
================================================================================

01_1DPrefixSum.cpp       - Basic 1D prefix sum problems
02_2DPrefixSum.cpp       - Matrix region sum problems
03_PrefixWithHashMap.cpp - Subarray sum problems with hashmap
04_DifferenceArray.cpp   - Range update operations
05_AdvancedPrefix.cpp    - Product, XOR prefix, and advanced applications

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// Quick template reference
class PrefixSumTemplates {
public:
    // 1D Prefix Sum
    static vector<long long> build1D(vector<int>& arr) {
        int n = arr.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + arr[i];
        }
        return prefix;
    }
    
    static long long rangeSum1D(vector<long long>& prefix, int l, int r) {
        return prefix[r + 1] - prefix[l];
    }
    
    // 2D Prefix Sum
    static vector<vector<long long>> build2D(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};
        int m = matrix.size(), n = matrix[0].size();
        vector<vector<long long>> prefix(m + 1, vector<long long>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                prefix[i][j] = matrix[i-1][j-1] + prefix[i-1][j] 
                             + prefix[i][j-1] - prefix[i-1][j-1];
            }
        }
        return prefix;
    }
    
    static long long rangeSum2D(vector<vector<long long>>& prefix, 
                                int r1, int c1, int r2, int c2) {
        return prefix[r2+1][c2+1] - prefix[r1][c2+1] 
             - prefix[r2+1][c1] + prefix[r1][c1];
    }
};

int main() {
    cout << "=== Prefix Sum Patterns ===" << endl;
    
    // 1D Example
    vector<int> arr = {1, 2, 3, 4, 5};
    auto prefix1D = PrefixSumTemplates::build1D(arr);
    cout << "Sum [1,3] = " << PrefixSumTemplates::rangeSum1D(prefix1D, 1, 3) << "\n";
    
    // 2D Example
    vector<vector<int>> matrix = {{1,2,3}, {4,5,6}, {7,8,9}};
    auto prefix2D = PrefixSumTemplates::build2D(matrix);
    cout << "Sum (0,0)-(1,1) = " << PrefixSumTemplates::rangeSum2D(prefix2D, 0, 0, 1, 1) << "\n";
    
    return 0;
}

