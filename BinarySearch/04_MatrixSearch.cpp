/*
================================================================================
                    BINARY SEARCH IN MATRICES
================================================================================

Different types of sorted matrices and how to search in them.

Matrix Types:
1. Fully Sorted (row-wise + column-wise in sequence)
2. Row-wise and Column-wise Sorted (Young Tableau)
3. Each Row Sorted Independently

Pattern 1: Search in 2D Matrix (Fully Sorted)
Pattern 2: Search in 2D Matrix II (Row & Column Sorted)
Pattern 3: Kth Smallest in Sorted Matrix
Pattern 4: Count Negatives in Sorted Matrix
Pattern 5: Find Peak Element in 2D
Pattern 6: Median in Row-wise Sorted Matrix

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

/*
================================================================================
PATTERN 1: SEARCH IN 2D MATRIX (Fully Sorted)
================================================================================
LeetCode: 74. Search a 2D Matrix

Matrix property: 
- Each row is sorted
- First element of each row > last element of previous row
- Essentially a sorted array in matrix form!

Approach: Treat as 1D array, use single binary search
Time: O(log(m*n)), Space: O(1)
*/
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    int left = 0, right = m * n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        // Convert 1D index to 2D coordinates
        int row = mid / n;
        int col = mid % n;
        int value = matrix[row][col];
        
        if (value == target) {
            return true;
        } else if (value < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return false;
}
/*
Matrix:
[1,  3,  5,  7]     1D view: [1,3,5,7,10,11,23,30,34,60]
[10, 11, 23, 30]    Index 5 → row=5/4=1, col=5%4=1 → matrix[1][1]=11
[34, 50, 60, 70]
*/


/*
================================================================================
PATTERN 2: SEARCH IN 2D MATRIX II (Row & Column Sorted)
================================================================================
LeetCode: 240. Search a 2D Matrix II

Matrix property:
- Each row is sorted left to right
- Each column is sorted top to bottom
- NOT a linear sorted array!

Approach: Start from TOP-RIGHT (or bottom-left) corner
Time: O(m + n), Space: O(1)
*/
bool searchMatrixII(vector<vector<int>>& matrix, int target) {
    int m = matrix.size(), n = matrix[0].size();
    
    // Start from top-right corner
    int row = 0, col = n - 1;
    
    while (row < m && col >= 0) {
        if (matrix[row][col] == target) {
            return true;
        } else if (matrix[row][col] > target) {
            col--;      // Too big, go left
        } else {
            row++;      // Too small, go down
        }
    }
    
    return false;
}
/*
Matrix:           Target = 14
[1,   4,  7, 11]
[2,   5,  8, 12]   Start at 15 (top-right)
[3,   6,  9, 16]   15 > 14 → go left
[10, 13, 14, 17]   11 < 14 → go down... → 14 found!

Why top-right works:
- If current > target: eliminate current column (all below are larger)
- If current < target: eliminate current row (all left are smaller)
*/


/*
================================================================================
PATTERN 3: KTH SMALLEST IN SORTED MATRIX
================================================================================
LeetCode: 378. Kth Smallest Element in a Sorted Matrix

Two Approaches:
A) Min-Heap: O(k log n)
B) Binary Search on Value: O(n * log(max - min))

Using Binary Search on the VALUE (not index!)
*/

// Approach A: Min-Heap (good for small k)
int kthSmallestHeap(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    
    // Min heap: {value, row, col}
    priority_queue<tuple<int,int,int>, 
                   vector<tuple<int,int,int>>, 
                   greater<>> minHeap;
    
    // Add first element of each row
    for (int i = 0; i < min(n, k); i++) {
        minHeap.push({matrix[i][0], i, 0});
    }
    
    int result = 0;
    for (int i = 0; i < k; i++) {
        auto [val, row, col] = minHeap.top();
        minHeap.pop();
        result = val;
        
        // Add next element from same row
        if (col + 1 < n) {
            minHeap.push({matrix[row][col + 1], row, col + 1});
        }
    }
    
    return result;
}

// Approach B: Binary Search on Value (better for large k)
int kthSmallestBinarySearch(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    int left = matrix[0][0];                // Minimum
    int right = matrix[n-1][n-1];           // Maximum
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Count elements <= mid
        int count = 0;
        int col = n - 1;
        
        for (int row = 0; row < n; row++) {
            while (col >= 0 && matrix[row][col] > mid) {
                col--;
            }
            count += (col + 1);
        }
        
        if (count < k) {
            left = mid + 1;     // Need larger value
        } else {
            right = mid;        // This or smaller
        }
    }
    
    return left;
}
/*
Matrix:
[1,  5,  9]
[10, 11, 13]    k = 5
[12, 13, 15]

Binary search values [1, 15]
mid = 8: count elements <= 8 → only {1,5} → 2 < 5, need larger
mid = 11: count <= 11 → {1,5,9,10,11} → 5 = k ✓
*/


/*
================================================================================
PATTERN 4: COUNT NEGATIVES IN SORTED MATRIX
================================================================================
LeetCode: 1351. Count Negative Numbers in a Sorted Matrix

Matrix property: Sorted in non-increasing order (row & column)

Approach: Start from top-right, use staircase pattern
Time: O(m + n), Space: O(1)
*/
int countNegatives(vector<vector<int>>& grid) {
    int m = grid.size(), n = grid[0].size();
    int count = 0;
    
    int row = 0, col = n - 1;
    
    while (row < m && col >= 0) {
        if (grid[row][col] < 0) {
            // All elements below in this column are also negative
            count += (m - row);
            col--;
        } else {
            row++;
        }
    }
    
    return count;
}
/*
Matrix:
[4,  3,  2, -1]
[3,  2,  1, -1]    Start at -1 (col 3)
[1,  1, -1, -2]    Negative → count += 4 (all below), go left
[-1, -1, -2, -3]   2 → positive, go down... etc.
*/


/*
================================================================================
PATTERN 5: FIND PEAK ELEMENT IN 2D MATRIX
================================================================================
LeetCode: 1901. Find a Peak Element II

Peak: Element greater than all 4 neighbors

Approach: Binary search on columns, find max in middle column
Time: O(m * log n) or O(n * log m), Space: O(1)
*/
vector<int> findPeakGrid(vector<vector<int>>& mat) {
    int m = mat.size(), n = mat[0].size();
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int midCol = left + (right - left) / 2;
        
        // Find max element in this column
        int maxRow = 0;
        for (int i = 0; i < m; i++) {
            if (mat[i][midCol] > mat[maxRow][midCol]) {
                maxRow = i;
            }
        }
        
        // Check if it's a peak (only need to check left/right neighbors)
        bool leftBigger = (midCol > 0 && mat[maxRow][midCol - 1] > mat[maxRow][midCol]);
        bool rightBigger = (midCol < n - 1 && mat[maxRow][midCol + 1] > mat[maxRow][midCol]);
        
        if (!leftBigger && !rightBigger) {
            return {maxRow, midCol};
        } else if (leftBigger) {
            right = midCol - 1;
        } else {
            left = midCol + 1;
        }
    }
    
    return {-1, -1};
}


/*
================================================================================
PATTERN 6: MEDIAN IN ROW-WISE SORTED MATRIX
================================================================================
Problem: Find median of matrix where each row is sorted (odd total elements)

Approach: Binary search on value, count elements less than mid
Time: O(32 * n * log(m)) or O(n * log(max - min) * log m), Space: O(1)
*/
int matrixMedian(vector<vector<int>>& matrix) {
    int m = matrix.size(), n = matrix[0].size();
    int total = m * n;
    int desired = total / 2;  // We need more than this many elements below median
    
    int left = INT_MAX, right = INT_MIN;
    
    // Find range
    for (int i = 0; i < m; i++) {
        left = min(left, matrix[i][0]);
        right = max(right, matrix[i][n - 1]);
    }
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // Count elements <= mid
        int count = 0;
        for (int i = 0; i < m; i++) {
            count += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
        }
        
        if (count <= desired) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}


/*
================================================================================
PATTERN 7: BINARY SEARCH IN EACH ROW
================================================================================
Problem: Count elements in matrix less than or equal to target
         Each row is sorted independently

Time: O(m * log n), Space: O(1)
*/
int countLessEqual(vector<vector<int>>& matrix, int target) {
    int count = 0;
    for (auto& row : matrix) {
        // Upper bound gives count of elements <= target
        count += upper_bound(row.begin(), row.end(), target) - row.begin();
    }
    return count;
}


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Matrix Binary Search ===\n\n";
    
    // Pattern 1: Fully Sorted Matrix
    vector<vector<int>> matrix1 = {
        {1, 3, 5, 7},
        {10, 11, 16, 20},
        {23, 30, 34, 60}
    };
    cout << "1. Search 3 in fully sorted matrix: " 
         << (searchMatrix(matrix1, 3) ? "Found" : "Not Found") << endl;
    
    // Pattern 2: Row & Column Sorted
    vector<vector<int>> matrix2 = {
        {1, 4, 7, 11, 15},
        {2, 5, 8, 12, 19},
        {3, 6, 9, 16, 22},
        {10, 13, 14, 17, 24}
    };
    cout << "2. Search 14 in row-col sorted matrix: "
         << (searchMatrixII(matrix2, 14) ? "Found" : "Not Found") << endl;
    
    // Pattern 3: Kth Smallest
    vector<vector<int>> matrix3 = {
        {1, 5, 9},
        {10, 11, 13},
        {12, 13, 15}
    };
    cout << "3. 5th smallest element: " << kthSmallestBinarySearch(matrix3, 5) << endl;
    cout << "   (using heap): " << kthSmallestHeap(matrix3, 5) << endl;
    
    // Pattern 4: Count Negatives
    vector<vector<int>> matrix4 = {
        {4, 3, 2, -1},
        {3, 2, 1, -1},
        {1, 1, -1, -2},
        {-1, -1, -2, -3}
    };
    cout << "4. Count negatives: " << countNegatives(matrix4) << endl;
    
    // Pattern 5: Peak in 2D
    vector<vector<int>> matrix5 = {
        {10, 20, 15},
        {21, 30, 14},
        {7, 16, 32}
    };
    auto peak = findPeakGrid(matrix5);
    cout << "5. Peak element at: [" << peak[0] << "," << peak[1] << "]" << endl;
    
    // Pattern 6: Matrix Median
    vector<vector<int>> matrix6 = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };
    cout << "6. Matrix median: " << matrixMedian(matrix6) << endl;
    
    return 0;
}

/*
================================================================================
                              CHEAT SHEET
================================================================================

┌──────────────────────────────────────────────────────────────────────────────┐
│ Matrix Type                 │ Approach                │ Time Complexity      │
├──────────────────────────────────────────────────────────────────────────────┤
│ Fully sorted (row then col) │ Treat as 1D array       │ O(log(m*n))          │
│ Row & Col sorted            │ Start from corner       │ O(m + n)             │
│ Kth smallest                │ Binary search on value  │ O(n * log(range))    │
│ Count elements              │ Binary search each row  │ O(m * log n)         │
│ Peak element                │ Binary search columns   │ O(m * log n)         │
└──────────────────────────────────────────────────────────────────────────────┘

KEY CONVERSIONS:
- 1D index to 2D: row = idx / cols, col = idx % cols
- 2D to 1D index: idx = row * cols + col

CORNER APPROACH (for row & col sorted):
- Top-right: go left if too big, down if too small
- Bottom-left: go right if too small, up if too big

================================================================================
*/

