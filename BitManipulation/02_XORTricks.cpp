/*
================================================================================
                    BIT MANIPULATION - XOR TRICKS
================================================================================

XOR Properties:
- a ^ a = 0  (same numbers cancel)
- a ^ 0 = a  (identity)
- Commutative and Associative

Applications: Finding unique elements, swapping, parity checks.

Time: O(n) | Space: O(1)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Single Number (LeetCode 136) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────
Every element appears twice except one. Find the unique one.

Input: nums = [2,2,1]
Output: 1

Key: XOR all elements - pairs cancel, leaving unique.

Time: O(n) | Space: O(1)
*/
int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }
    return result;
}


/*
PROBLEM 2: Single Number II (LeetCode 137)
──────────────────────────────────────────
Every element appears three times except one. Find the unique one.

Input: nums = [2,2,3,2]
Output: 3

Approach: Count bits at each position mod 3.

Time: O(32n) = O(n) | Space: O(1)
*/
int singleNumberII(vector<int>& nums) {
    int result = 0;
    
    for (int i = 0; i < 32; i++) {
        int bitSum = 0;
        for (int num : nums) {
            bitSum += (num >> i) & 1;
        }
        if (bitSum % 3 != 0) {
            result |= (1 << i);
        }
    }
    
    return result;
}

// Alternative: State machine approach
int singleNumberII_StateMachine(vector<int>& nums) {
    int ones = 0, twos = 0;
    
    for (int num : nums) {
        ones = (ones ^ num) & ~twos;
        twos = (twos ^ num) & ~ones;
    }
    
    return ones;
}


/*
PROBLEM 3: Single Number III (LeetCode 260) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────
Two elements appear once, rest appear twice. Find both.

Input: nums = [1,2,1,3,2,5]
Output: [3,5]

Approach:
1. XOR all → get xorSum = a ^ b
2. Find any differing bit
3. Divide nums by that bit, XOR each group

Time: O(n) | Space: O(1)
*/
vector<int> singleNumberIII(vector<int>& nums) {
    // Step 1: XOR all numbers
    int xorSum = 0;
    for (int num : nums) {
        xorSum ^= num;
    }
    
    // Step 2: Find rightmost differing bit
    int diffBit = xorSum & (-xorSum);  // Lowest set bit
    
    // Step 3: Divide into two groups
    int a = 0, b = 0;
    for (int num : nums) {
        if (num & diffBit) {
            a ^= num;
        } else {
            b ^= num;
        }
    }
    
    return {a, b};
}


/*
PROBLEM 4: Missing Number (LeetCode 268)
────────────────────────────────────────
Array has n distinct numbers from [0, n]. Find missing one.

Input: nums = [3,0,1]
Output: 2

Approach: XOR with indices and n.

Time: O(n) | Space: O(1)
*/
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int result = n;  // Include n in XOR
    
    for (int i = 0; i < n; i++) {
        result ^= i ^ nums[i];
    }
    
    return result;
}


/*
PROBLEM 5: Find the Duplicate Number (LeetCode 287)
───────────────────────────────────────────────────
Array has n+1 numbers in range [1, n]. One duplicate. Find it.

Note: XOR doesn't work here (we don't know which number is missing).
Use Floyd's cycle detection instead.

Time: O(n) | Space: O(1)
*/
int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[0];
    
    // Phase 1: Find meeting point
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    
    // Phase 2: Find cycle start
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    
    return slow;
}


/*
PROBLEM 6: Find All Numbers Disappeared in Array (LeetCode 448)
───────────────────────────────────────────────────────────────
Array has n numbers in [1, n]. Find all missing numbers.

Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]

Approach: Mark seen numbers by negating index.

Time: O(n) | Space: O(1)
*/
vector<int> findDisappearedNumbers(vector<int>& nums) {
    // Mark indices as visited
    for (int i = 0; i < nums.size(); i++) {
        int idx = abs(nums[i]) - 1;
        if (nums[idx] > 0) {
            nums[idx] = -nums[idx];
        }
    }
    
    // Collect unvisited indices
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] > 0) {
            result.push_back(i + 1);
        }
    }
    
    return result;
}


/*
PROBLEM 7: Find All Duplicates in Array (LeetCode 442)
──────────────────────────────────────────────────────
Array has n numbers in [1, n]. Some appear twice. Find duplicates.

Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]

Time: O(n) | Space: O(1)
*/
vector<int> findDuplicates(vector<int>& nums) {
    vector<int> result;
    
    for (int num : nums) {
        int idx = abs(num) - 1;
        if (nums[idx] < 0) {
            result.push_back(abs(num));
        } else {
            nums[idx] = -nums[idx];
        }
    }
    
    return result;
}


/*
PROBLEM 8: Swap Two Numbers Without Temp
────────────────────────────────────────
Use XOR to swap without extra variable.
*/
void swapWithXOR(int& a, int& b) {
    if (&a == &b) return;  // Same address check
    a ^= b;
    b ^= a;
    a ^= b;
}


/*
PROBLEM 9: XOR Queries of a Subarray (LeetCode 1310)
────────────────────────────────────────────────────
Answer queries for XOR of arr[left..right].

Input: arr = [1,3,4,8], queries = [[0,1],[1,2],[0,3]]
Output: [2,7,14]

Approach: Prefix XOR array.

Time: O(n + q) | Space: O(n)
*/
vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    int n = arr.size();
    vector<int> prefix(n + 1, 0);
    
    // Build prefix XOR
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] ^ arr[i];
    }
    
    // Answer queries
    vector<int> result;
    for (auto& q : queries) {
        result.push_back(prefix[q[1] + 1] ^ prefix[q[0]]);
    }
    
    return result;
}


/*
PROBLEM 10: Maximum XOR of Two Numbers (LeetCode 421) ⭐ GOOGLE FAVORITE
───────────────────────────────────────────────────────────────────────
Find max XOR of any two numbers in array.

Input: nums = [3,10,5,25,2,8]
Output: 28 (5 XOR 25)

Approach: Bit-by-bit greedy with Trie or hash set.

Time: O(32n) | Space: O(n)
*/
int findMaximumXOR(vector<int>& nums) {
    int maxXOR = 0, mask = 0;
    
    // Build answer bit by bit from MSB
    for (int i = 31; i >= 0; i--) {
        mask |= (1 << i);
        
        unordered_set<int> prefixes;
        for (int num : nums) {
            prefixes.insert(num & mask);
        }
        
        // Check if we can set this bit in answer
        int candidate = maxXOR | (1 << i);
        for (int prefix : prefixes) {
            // If prefix ^ candidate exists, we can achieve candidate
            if (prefixes.count(prefix ^ candidate)) {
                maxXOR = candidate;
                break;
            }
        }
    }
    
    return maxXOR;
}


/*
PROBLEM 11: Decode XORed Array (LeetCode 1720)
──────────────────────────────────────────────
encoded[i] = arr[i] XOR arr[i+1]. Given encoded and first, find arr.

Input: encoded = [1,2,3], first = 1
Output: [1,0,2,1]

Time: O(n) | Space: O(n)
*/
vector<int> decode(vector<int>& encoded, int first) {
    vector<int> arr = {first};
    
    for (int e : encoded) {
        arr.push_back(arr.back() ^ e);
    }
    
    return arr;
}


/*
PROBLEM 12: Count Triplets That Can Form Two Arrays of Equal XOR (LeetCode 1442)
────────────────────────────────────────────────────────────────────────────────
Find triplets (i,j,k) where XOR(arr[i..j-1]) == XOR(arr[j..k]).

Key insight: This means XOR(arr[i..k]) == 0.

Time: O(n²) | Space: O(1)
*/
int countTriplets(vector<int>& arr) {
    int n = arr.size(), count = 0;
    
    for (int i = 0; i < n; i++) {
        int xorVal = 0;
        for (int k = i; k < n; k++) {
            xorVal ^= arr[k];
            // If XOR is 0, any j in (i, k] works
            if (xorVal == 0 && k > i) {
                count += k - i;  // (k - i) choices for j
            }
        }
    }
    
    return count;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== XOR Tricks ===\n\n";
    
    // Single Number
    vector<int> nums1 = {2, 2, 1};
    cout << "1. Single number in [2,2,1]: " << singleNumber(nums1) << "\n";
    
    // Single Number II
    vector<int> nums2 = {2, 2, 3, 2};
    cout << "2. Single number II in [2,2,3,2]: " << singleNumberII(nums2) << "\n";
    
    // Single Number III
    vector<int> nums3 = {1, 2, 1, 3, 2, 5};
    auto res3 = singleNumberIII(nums3);
    cout << "3. Two unique in [1,2,1,3,2,5]: " << res3[0] << ", " << res3[1] << "\n";
    
    // Missing Number
    vector<int> nums4 = {3, 0, 1};
    cout << "4. Missing in [3,0,1]: " << missingNumber(nums4) << "\n";
    
    // Maximum XOR
    vector<int> nums5 = {3, 10, 5, 25, 2, 8};
    cout << "10. Max XOR: " << findMaximumXOR(nums5) << "\n";
    
    // Swap
    int a = 5, b = 7;
    swapWithXOR(a, b);
    cout << "8. After swap: a=" << a << ", b=" << b << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | XOR Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Single Number                 | XOR all elements                               |
| Single Number II              | Count bits mod 3 or state machine             |
| Single Number III             | Divide by differing bit, XOR each group        |
| Missing Number                | XOR with indices                               |
| Maximum XOR                   | Bit-by-bit greedy with hash set                |
| Decode XORed                  | arr[i+1] = arr[i] ^ encoded[i]                 |
+───────────────────────────────+────────────────────────────────────────────────+

KEY INSIGHT: XOR cancels duplicates, leaving unique elements.

================================================================================
*/

