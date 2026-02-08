/*
================================================================================
                BANK TRANSACTIONS (Google Interview)
================================================================================

PROBLEM:
A bank starts with initial money M. Given an array of customer transactions
where positive = deposit, negative = withdrawal.

Bank can:
1. Choose which customer to START serving
2. Refuse any number of customers before starting
3. Once started, MUST serve consecutively until impossible (balance < 0)

Find the MAXIMUM number of consecutive customers the bank can serve.

================================================================================
                         EXAMPLES
================================================================================

Example: transactions = [1, -3, 5, -2, 1], M = 1
- Start at index 2 (deposit 5): 1+5=6, 6-2=4, 4+1=5 → serves 3 customers
- Start at index 0: 1+1=2, 2-3=-1 → can only serve 1 customer
Output: 3

================================================================================
                         APPROACH
================================================================================

SLIDING WINDOW approach:
1. Use two pointers: left (start) and right (current)
2. Maintain running sum = M + sum of transactions[left...right]
3. If sum goes negative, move left pointer forward

KEY INSIGHT: This is similar to "longest subarray with sum >= 0"
where we start with initial value M.

TIME:  O(n) - each element visited at most twice
SPACE: O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// O(n^2) approach
int maxCustomers(vector<int>& transactions, int money) {
    int maxCust = 0;
    int left = 0;
    int balance = money;
    
    for (int i = 0; i < transactions.size(); i++) {
        balance += transactions[i];
        
        // If balance goes negative, shrink window from left
        while (balance < 0 && left <= i) {
            balance -= transactions[left];
            left++;
            balance = money;  // Reset to initial money at new start
            
            // Recalculate balance from new left to i
            for (int j = left; j <= i; j++) {
                balance += transactions[j];
                if (balance < 0) {
                    left = j + 1;
                    balance = money;
                }
            }
        }
        
        if (balance >= 0) {
            maxCust = max(maxCust, i - left + 1);
        }
    }
    
    return maxCust;
}

// Cleaner O(n) approach
int maxCustomersOptimized(vector<int>& transactions, int money) {
    int maxCust = 0;
    int n = transactions.size();
    
    // Try each starting position
    int left = 0;
    int balance = money;
    
    for (int right = 0; right < n; right++) {
        balance += transactions[right];
        
        // If balance goes negative, reset
        if (balance < 0) {
            left = right + 1;
            balance = money;
            continue;
        }
        
        maxCust = max(maxCust, right - left + 1);
    }
    
    return maxCust;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test case 1
    vector<int> t1 = {1, -3, 5, -2, 1};
    int m1 = 1;
    cout << "Test 1: transactions = [1, -3, 5, -2, 1], M = " << m1 << "\n";
    cout << "Max customers: " << maxCustomersOptimized(t1, m1) << "\n";
    cout << "Expected: 3 (start at 5, serve 5, -2, 1)\n\n";
    
    // Test case 2
    vector<int> t2 = {1, -2, 3, 4, -10, 5, 6};
    int m2 = 1;
    cout << "Test 2: transactions = [1, -2, 3, 4, -10, 5, 6], M = " << m2 << "\n";
    cout << "Max customers: " << maxCustomersOptimized(t2, m2) << "\n\n";
    
    // Test case 3: All deposits
    vector<int> t3 = {1, 2, 3, 4, 5};
    int m3 = 0;
    cout << "Test 3: transactions = [1, 2, 3, 4, 5], M = " << m3 << "\n";
    cout << "Max customers: " << maxCustomersOptimized(t3, m3) << "\n";
    cout << "Expected: 5 (all deposits)\n\n";
    
    // Test case 4: Impossible to serve anyone
    vector<int> t4 = {-5, -10, -3};
    int m4 = 2;
    cout << "Test 4: transactions = [-5, -10, -3], M = " << m4 << "\n";
    cout << "Max customers: " << maxCustomersOptimized(t4, m4) << "\n";
    cout << "Expected: 0\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

TIME:  O(n)
- Single pass through transactions
- Left pointer only moves forward

SPACE: O(1)
- Only tracking pointers and balance

EDGE CASES:
1. All transactions are negative → return 0
2. Initial money is 0 → first transaction must be positive
3. Single transaction → return 1 if M + t[0] >= 0

================================================================================
*/

