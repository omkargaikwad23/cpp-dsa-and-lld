/*
================================================================================
                    BOYER-MOORE MAJORITY VOTE ALGORITHM
================================================================================

PROBLEM: Find the majority element (appears more than n/2 times)

KEY INSIGHT: If we cancel out each occurrence of an element e with all other 
elements that are different from e, then e will exist till the end if it's 
a majority element.

ALGORITHM:
1. Initialize candidate and count = 0
2. For each element:
   - If count == 0, set current element as candidate
   - If element == candidate, increment count
   - Else decrement count
3. Verify candidate is actually majority (optional second pass)

TIME:  O(n)
SPACE: O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// BASIC: Find majority element (guaranteed to exist) - LC 169
// ═══════════════════════════════════════════════════════════════════════════

int majorityElement(vector<int>& nums) {
    int candidate = 0;
    int count = 0;
    
    for (int num : nums) {
        if (count == 0) {
            candidate = num;  // New candidate
        }
        count += (num == candidate) ? 1 : -1;
    }
    
    return candidate;  // Guaranteed to be majority
}

// ═══════════════════════════════════════════════════════════════════════════
// WITH VERIFICATION: When majority may not exist
// ═══════════════════════════════════════════════════════════════════════════

int majorityElementWithVerify(vector<int>& nums) {
    int candidate = 0;
    int count = 0;
    
    // Phase 1: Find candidate
    for (int num : nums) {
        if (count == 0) {
            candidate = num;
        }
        count += (num == candidate) ? 1 : -1;
    }
    
    // Phase 2: Verify candidate
    count = 0;
    for (int num : nums) {
        if (num == candidate) count++;
    }
    
    return (count > nums.size() / 2) ? candidate : -1;
}

// ═══════════════════════════════════════════════════════════════════════════
// EXTENDED: Find all elements appearing > n/3 times - LC 229
// At most 2 such elements can exist
// ═══════════════════════════════════════════════════════════════════════════

vector<int> majorityElementII(vector<int>& nums) {
    int candidate1 = 0, candidate2 = 1;  // Different initial values
    int count1 = 0, count2 = 0;
    
    // Phase 1: Find up to 2 candidates
    for (int num : nums) {
        if (num == candidate1) {
            count1++;
        } else if (num == candidate2) {
            count2++;
        } else if (count1 == 0) {
            candidate1 = num;
            count1 = 1;
        } else if (count2 == 0) {
            candidate2 = num;
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }
    
    // Phase 2: Verify candidates
    count1 = count2 = 0;
    for (int num : nums) {
        if (num == candidate1) count1++;
        else if (num == candidate2) count2++;
    }
    
    vector<int> result;
    int n = nums.size();
    if (count1 > n / 3) result.push_back(candidate1);
    if (count2 > n / 3) result.push_back(candidate2);
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test LC 169
    vector<int> nums1 = {3, 2, 3};
    cout << "Majority in [3,2,3]: " << majorityElement(nums1) << "\n";
    
    vector<int> nums2 = {2, 2, 1, 1, 1, 2, 2};
    cout << "Majority in [2,2,1,1,1,2,2]: " << majorityElement(nums2) << "\n";
    
    // Test LC 229
    vector<int> nums3 = {3, 2, 3};
    cout << "\nElements > n/3 in [3,2,3]: ";
    for (int x : majorityElementII(nums3)) cout << x << " ";
    cout << "\n";
    
    vector<int> nums4 = {1, 2, 3, 1, 1, 2, 2};
    cout << "Elements > n/3 in [1,2,3,1,1,2,2]: ";
    for (int x : majorityElementII(nums4)) cout << x << " ";
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                         WHY IT WORKS
================================================================================

Intuition: Imagine a "battle" where:
- Same elements team up (+1)
- Different elements cancel out (-1)

If majority exists (> n/2), even after canceling with ALL others,
at least one "soldier" survives → that's our candidate.

For n/3 majority: At most 2 elements can appear > n/3 times
(since 3 × (n/3) = n, and we need > n/3 each)

RELATED PROBLEMS:
- LC 169: Majority Element
- LC 229: Majority Element II
- LC 1150: Check If a Number Is Majority Element in a Sorted Array

================================================================================
*/

