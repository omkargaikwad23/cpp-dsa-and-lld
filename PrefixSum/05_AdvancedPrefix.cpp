/*
================================================================================
                    ADVANCED PREFIX SUM APPLICATIONS
================================================================================

Advanced applications: XOR prefix, product prefix, prefix with binary search,
and complex multi-dimensional problems.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: XOR Queries of a Subarray (LeetCode 1310)
────────────────────────────────────────────────────
Answer XOR queries for subarray [l, r].

prefix[i] = XOR of arr[0..i-1]
XOR [l, r] = prefix[r+1] ^ prefix[l]

Time: O(n + q) | Space: O(n)
*/
vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
    int n = arr.size();
    vector<int> prefix(n + 1, 0);
    
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] ^ arr[i];
    }
    
    vector<int> result;
    for (auto& q : queries) {
        result.push_back(prefix[q[1] + 1] ^ prefix[q[0]]);
    }
    
    return result;
}


/*
PROBLEM 2: Can Make Palindrome from Substring (LeetCode 1177)
─────────────────────────────────────────────────────────────
Check if substring can be rearranged to palindrome with at most k changes.

Key: Palindrome needs at most 1 odd frequency character.
     Use bitmask prefix XOR for character frequencies.

Time: O(n + q) | Space: O(n)
*/
vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
    int n = s.size();
    vector<int> prefix(n + 1, 0);  // Bitmask of odd frequency chars
    
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] ^ (1 << (s[i] - 'a'));
    }
    
    vector<bool> result;
    for (auto& q : queries) {
        int left = q[0], right = q[1], k = q[2];
        int oddCount = __builtin_popcount(prefix[right + 1] ^ prefix[left]);
        // Need to change (oddCount / 2) characters
        result.push_back(oddCount / 2 <= k);
    }
    
    return result;
}


/*
PROBLEM 3: Maximum Sum Obtained of Any Permutation (LeetCode 1589)
─────────────────────────────────────────────────────────────────
Permute array to maximize sum of queried ranges.

Approach: Count frequency of each index, sort both arrays.

Time: O(n log n) | Space: O(n)
*/
int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
    const int MOD = 1e9 + 7;
    int n = nums.size();
    
    // Count frequency using difference array
    vector<long long> freq(n + 1, 0);
    for (auto& req : requests) {
        freq[req[0]]++;
        freq[req[1] + 1]--;
    }
    
    // Convert to actual frequencies
    for (int i = 1; i < n; i++) {
        freq[i] += freq[i - 1];
    }
    
    // Sort both arrays
    sort(nums.begin(), nums.end());
    sort(freq.begin(), freq.begin() + n);
    
    // Multiply largest nums with highest frequencies
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum = (sum + (long long)nums[i] * freq[i]) % MOD;
    }
    
    return sum;
}


/*
PROBLEM 4: Minimum Moves to Make Array Complementary (LeetCode 1674)
────────────────────────────────────────────────────────────────────
Make array[i] + array[n-1-i] equal for all i.

Use difference array to track cost changes at different target sums.

Time: O(n + limit) | Space: O(limit)
*/
int minMoves(vector<int>& nums, int limit) {
    int n = nums.size();
    vector<int> diff(2 * limit + 2, 0);
    
    for (int i = 0; i < n / 2; i++) {
        int a = nums[i], b = nums[n - 1 - i];
        
        // For sum T:
        // - T < min(a,b) + 1 or T > max(a,b) + limit: 2 moves
        // - T in [min+1, max+limit] but T != a+b: 1 move
        // - T == a + b: 0 moves
        
        int lo = min(a, b) + 1;
        int hi = max(a, b) + limit;
        
        diff[2] += 2;              // Base: all need 2 moves
        diff[lo] -= 1;             // Reduce to 1 move
        diff[a + b] -= 1;          // Reduce to 0 moves
        diff[a + b + 1] += 1;      // Back to 1 move
        diff[hi + 1] += 1;         // Back to 2 moves
    }
    
    int minMoves = n, current = 0;
    for (int t = 2; t <= 2 * limit; t++) {
        current += diff[t];
        minMoves = min(minMoves, current);
    }
    
    return minMoves;
}


/*
PROBLEM 5: Count Vowel Substrings of a String (LeetCode 2063)
─────────────────────────────────────────────────────────────
Count substrings containing all 5 vowels and only vowels.

Time: O(n) | Space: O(1)
*/
int countVowelSubstrings(string word) {
    auto isVowel = [](char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };
    
    int count = 0, n = word.size();
    
    for (int start = 0; start < n; start++) {
        if (!isVowel(word[start])) continue;
        
        unordered_map<char, int> freq;
        for (int end = start; end < n && isVowel(word[end]); end++) {
            freq[word[end]]++;
            if (freq.size() == 5) count++;
        }
    }
    
    return count;
}


/*
PROBLEM 6: Find Good Days to Rob the Bank (LeetCode 2100)
─────────────────────────────────────────────────────────
Day i is good if:
- security[i-k..i] is non-increasing
- security[i..i+k] is non-decreasing

Build prefix arrays for consecutive non-increasing and non-decreasing days.

Time: O(n) | Space: O(n)
*/
vector<int> goodDaysToRobBank(vector<int>& security, int time) {
    int n = security.size();
    
    // left[i] = consecutive non-increasing days ending at i
    vector<int> left(n, 0);
    for (int i = 1; i < n; i++) {
        if (security[i] <= security[i - 1]) {
            left[i] = left[i - 1] + 1;
        }
    }
    
    // right[i] = consecutive non-decreasing days starting at i
    vector<int> right(n, 0);
    for (int i = n - 2; i >= 0; i--) {
        if (security[i] <= security[i + 1]) {
            right[i] = right[i + 1] + 1;
        }
    }
    
    vector<int> result;
    for (int i = time; i < n - time; i++) {
        if (left[i] >= time && right[i] >= time) {
            result.push_back(i);
        }
    }
    
    return result;
}


/*
PROBLEM 7: Ways to Split Array Into Three Subarrays (LeetCode 1712)
───────────────────────────────────────────────────────────────────
Count ways to split into 3 parts where sum(left) <= sum(mid) <= sum(right).

Use prefix sum + binary search.

Time: O(n log n) | Space: O(n)
*/
int waysToSplit(vector<int>& nums) {
    const int MOD = 1e9 + 7;
    int n = nums.size();
    
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    
    long long count = 0;
    
    for (int i = 1; i < n - 1; i++) {  // End of first part
        long long leftSum = prefix[i];
        
        // leftSum <= midSum <= rightSum
        // leftSum <= prefix[j] - prefix[i] <= prefix[n] - prefix[j]
        
        // Find min j: prefix[j] >= 2 * prefix[i]
        int minJ = lower_bound(prefix.begin() + i + 1, prefix.begin() + n,
                              2 * leftSum) - prefix.begin();
        
        // Find max j: prefix[j] <= (prefix[n] + prefix[i]) / 2
        int maxJ = upper_bound(prefix.begin() + i + 1, prefix.begin() + n,
                              (prefix[n] + prefix[i]) / 2) - prefix.begin() - 1;
        
        if (minJ <= maxJ && minJ < n) {
            count = (count + maxJ - minJ + 1) % MOD;
        }
    }
    
    return count;
}


/*
PROBLEM 8: Sum of Floored Pairs (LeetCode 1862)
───────────────────────────────────────────────
Sum of floor(nums[i] / nums[j]) for all pairs.

Use frequency prefix and contribution counting.

Time: O(n + max * log(max)) | Space: O(max)
*/
int sumOfFlooredPairs(vector<int>& nums) {
    const int MOD = 1e9 + 7;
    int maxVal = *max_element(nums.begin(), nums.end());
    
    // Count frequency
    vector<int> freq(maxVal + 1, 0);
    for (int num : nums) freq[num]++;
    
    // Build prefix sum of frequencies
    vector<long long> prefix(maxVal + 2, 0);
    for (int i = 1; i <= maxVal; i++) {
        prefix[i] = prefix[i - 1] + freq[i];
    }
    
    long long sum = 0;
    
    for (int d = 1; d <= maxVal; d++) {  // Divisor
        if (freq[d] == 0) continue;
        
        // Count pairs where floor(x/d) = q for each quotient q
        for (int q = 1; q * d <= maxVal; q++) {
            int lo = q * d;
            int hi = min((long long)(q + 1) * d - 1, (long long)maxVal);
            
            long long countInRange = prefix[hi] - prefix[lo - 1];
            sum = (sum + (long long)freq[d] * q * countInRange) % MOD;
        }
    }
    
    return sum;
}


/*
PROBLEM 9: Maximum Fruits Harvested After at Most K Steps (LeetCode 2106)
─────────────────────────────────────────────────────────────────────────
Collect max fruits walking at most k steps from startPos.

Use prefix sum + sliding window.

Time: O(n) | Space: O(n)
*/
int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
    // Convert to position-indexed array using prefix sum
    int maxPos = max(startPos + k, fruits.back()[0]) + 1;
    vector<int> amount(maxPos + 1, 0);
    
    for (auto& f : fruits) {
        if (f[0] <= startPos + k) {
            amount[f[0]] = f[1];
        }
    }
    
    // Build prefix sum
    vector<long long> prefix(maxPos + 2, 0);
    for (int i = 0; i <= maxPos; i++) {
        prefix[i + 1] = prefix[i] + amount[i];
    }
    
    int maxFruits = 0;
    
    // Try all possible left boundaries
    for (int left = max(0, startPos - k); left <= startPos; left++) {
        int stepsLeft = startPos - left;
        int remaining = k - stepsLeft;
        
        // Go right first, then left
        int right1 = min(startPos + remaining, maxPos);
        // Go left first, then right
        int right2 = min(startPos + (remaining - stepsLeft), maxPos);
        
        int right = max(right1, right2);
        right = max(right, startPos);  // At least reach start
        right = min(right, maxPos);
        
        maxFruits = max(maxFruits, (int)(prefix[right + 1] - prefix[left]));
    }
    
    // Try going right first
    for (int right = startPos; right <= min(startPos + k, maxPos); right++) {
        int stepsRight = right - startPos;
        int remaining = k - stepsRight;
        int left = max(0, startPos - (remaining - stepsRight));
        left = max(left, 0);
        
        maxFruits = max(maxFruits, (int)(prefix[right + 1] - prefix[left]));
    }
    
    return maxFruits;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Advanced Prefix Sum ===\n\n";
    
    // XOR Queries
    vector<int> arr1 = {1, 3, 4, 8};
    vector<vector<int>> queries1 = {{0,1}, {1,2}, {0,3}};
    auto xorRes = xorQueries(arr1, queries1);
    cout << "1. XOR queries: ";
    for (int x : xorRes) cout << x << " ";
    cout << "\n";
    
    // Palindrome Queries
    vector<vector<int>> queries2 = {{0,4,1}, {0,3,0}};
    auto paliRes = canMakePaliQueries("abcda", queries2);
    cout << "2. Can make palindrome: ";
    for (bool b : paliRes) cout << (b ? "T" : "F") << " ";
    cout << "\n";
    
    // Good Days to Rob Bank
    vector<int> security = {5,3,3,3,5,6,2};
    auto goodDays = goodDaysToRobBank(security, 2);
    cout << "6. Good days: ";
    for (int d : goodDays) cout << d << " ";
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

ADVANCED PREFIX PATTERNS:
─────────────────────────

1. XOR PREFIX: prefix[i] = XOR(arr[0..i-1])
   - Query [l,r] = prefix[r+1] ^ prefix[l]

2. BITMASK PREFIX: Track odd/even character frequencies
   - Palindrome checks in O(1)

3. PREFIX + BINARY SEARCH: For optimization problems
   - Find boundaries efficiently

4. PREFIX + DIFFERENCE ARRAY: Combined techniques
   - Complex range query + update problems

+───────────────────────────────+────────────────────────────────────────────────+
| Application                   | Technique                                      |
+───────────────────────────────+────────────────────────────────────────────────+
| XOR range queries             | XOR prefix sum                                 |
| Palindrome substring          | Bitmask XOR prefix for frequencies             |
| Optimize permutation          | Frequency counting + sorting                   |
| Multi-range optimization      | Prefix + binary search                         |
| Character parity              | Bit manipulation + prefix XOR                  |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

