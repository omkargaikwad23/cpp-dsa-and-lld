/*
================================================================================
              SLIDING WINDOW WITH HASHMAP / FREQUENCY COUNTING
================================================================================

Track element frequencies within the window using HashMap/array.
Essential for problems involving:
- Distinct characters/elements
- Anagram matching
- Substring conditions

Time: O(n) | Space: O(k) where k = unique elements
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Subarrays with K Different Integers (LeetCode 992)
─────────────────────────────────────────────────────────────
Count subarrays with exactly k distinct integers.

Input: nums = [1,2,1,2,3], k = 2
Output: 7 ([1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2])

Key Insight: exactly(k) = atMost(k) - atMost(k-1)

Time: O(n) | Space: O(k)
*/
int atMostKDistinct(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    int left = 0, count = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        freq[nums[right]]++;
        
        while (freq.size() > k) {
            freq[nums[left]]--;
            if (freq[nums[left]] == 0) freq.erase(nums[left]);
            left++;
        }
        
        // All subarrays ending at right with at most k distinct
        count += right - left + 1;
    }
    return count;
}

int subarraysWithKDistinct(vector<int>& nums, int k) {
    return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
}


/*
PROBLEM 2: Count Number of Nice Subarrays (LeetCode 1248)
─────────────────────────────────────────────────────────
Count subarrays with exactly k odd numbers.

Input: nums = [1,1,2,1,1], k = 3
Output: 2

Approach: Same as above - exactly(k) = atMost(k) - atMost(k-1)

Time: O(n) | Space: O(1)
*/
int atMostKOdd(vector<int>& nums, int k) {
    int left = 0, count = 0, oddCount = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        if (nums[right] % 2 == 1) oddCount++;
        
        while (oddCount > k) {
            if (nums[left] % 2 == 1) oddCount--;
            left++;
        }
        
        count += right - left + 1;
    }
    return count;
}

int numberOfSubarrays(vector<int>& nums, int k) {
    return atMostKOdd(nums, k) - atMostKOdd(nums, k - 1);
}


/*
PROBLEM 3: Longest Substring with At Least K Repeating Chars (LeetCode 395)
───────────────────────────────────────────────────────────────────────────
Find longest substring where every character appears at least k times.

Input: s = "aaabb", k = 3
Output: 3 ("aaa")

Approach: Try each unique character count (1 to 26) and find longest

Time: O(26 * n) = O(n) | Space: O(26) = O(1)
*/
int longestSubstring(string s, int k) {
    int maxLen = 0;
    
    // Try each number of unique characters
    for (int uniqueTarget = 1; uniqueTarget <= 26; uniqueTarget++) {
        vector<int> freq(26, 0);
        int left = 0, uniqueCount = 0, countAtLeastK = 0;
        
        for (int right = 0; right < s.size(); right++) {
            int idx = s[right] - 'a';
            
            if (freq[idx] == 0) uniqueCount++;
            freq[idx]++;
            if (freq[idx] == k) countAtLeastK++;
            
            // Shrink while more unique than target
            while (uniqueCount > uniqueTarget) {
                int leftIdx = s[left] - 'a';
                if (freq[leftIdx] == k) countAtLeastK--;
                freq[leftIdx]--;
                if (freq[leftIdx] == 0) uniqueCount--;
                left++;
            }
            
            // All unique chars appear at least k times
            if (uniqueCount == uniqueTarget && countAtLeastK == uniqueCount) {
                maxLen = max(maxLen, right - left + 1);
            }
        }
    }
    return maxLen;
}


/*
PROBLEM 4: Frequency of Most Frequent Element (LeetCode 1838)
─────────────────────────────────────────────────────────────
You can increment elements. Return max frequency achievable with k increments.

Input: nums = [1,2,4], k = 5
Output: 3 (increment 1,2 to 4)

Approach: Sort, slide window, check if can make all equal to rightmost

Time: O(n log n) | Space: O(1)
*/
int maxFrequency(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int left = 0, maxFreq = 0;
    long long sum = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        sum += nums[right];
        
        // Cost to make all elements = nums[right]
        // Cost = nums[right] * windowSize - sum
        while ((long long)nums[right] * (right - left + 1) - sum > k) {
            sum -= nums[left];
            left++;
        }
        
        maxFreq = max(maxFreq, right - left + 1);
    }
    return maxFreq;
}


/*
PROBLEM 5: Maximum Number of Occurrences of Substring (LeetCode 1297)
─────────────────────────────────────────────────────────────────────
Find max occurrences of any substring with:
- Length between minSize and maxSize
- At most maxLetters distinct letters

Key Insight: Only need to check minSize (larger has <= occurrences)

Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
Output: 2 ("aab" appears 2 times)

Time: O(n * minSize) | Space: O(n)
*/
int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
    unordered_map<string, int> count;
    unordered_map<char, int> freq;
    int maxOccur = 0;
    
    for (int i = 0; i < s.size(); i++) {
        freq[s[i]]++;
        
        if (i >= minSize) {
            freq[s[i - minSize]]--;
            if (freq[s[i - minSize]] == 0) freq.erase(s[i - minSize]);
        }
        
        if (i >= minSize - 1 && freq.size() <= maxLetters) {
            string sub = s.substr(i - minSize + 1, minSize);
            count[sub]++;
            maxOccur = max(maxOccur, count[sub]);
        }
    }
    return maxOccur;
}


/*
PROBLEM 6: K-Beauty of a Number (LeetCode 2269)
───────────────────────────────────────────────
Count divisors of n from its substrings of length k.

Input: num = 240, k = 2
Output: 2 (24 and 40 divide 240)

Time: O(n) where n = digits | Space: O(1)
*/
int divisorSubstrings(int num, int k) {
    string s = to_string(num);
    int count = 0;
    
    for (int i = 0; i <= (int)s.size() - k; i++) {
        int sub = stoi(s.substr(i, k));
        if (sub != 0 && num % sub == 0) count++;
    }
    return count;
}


/*
PROBLEM 7: Distinct Numbers in Each Subarray (Count subarrays)
──────────────────────────────────────────────────────────────
Count subarrays where all elements are distinct.

Approach: For each right, find leftmost left where all distinct.
Count = sum of (right - left + 1) for each right

Time: O(n) | Space: O(n)
*/
long long countDistinctSubarrays(vector<int>& nums) {
    unordered_map<int, int> lastSeen;
    long long count = 0;
    int left = 0;
    
    for (int right = 0; right < nums.size(); right++) {
        if (lastSeen.count(nums[right]) && lastSeen[nums[right]] >= left) {
            left = lastSeen[nums[right]] + 1;
        }
        lastSeen[nums[right]] = right;
        count += right - left + 1;
    }
    return count;
}


/*
PROBLEM 8: Substring with Concatenation of All Words (LeetCode 30)
──────────────────────────────────────────────────────────────────
Find starting indices of substrings that are concatenation of all words.

Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0, 9]

Time: O(n * wordLen) | Space: O(words.size())
*/
vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> result;
    if (words.empty() || s.empty()) return result;
    
    int wordLen = words[0].size();
    int wordCount = words.size();
    int totalLen = wordLen * wordCount;
    
    unordered_map<string, int> wordFreq;
    for (const string& w : words) wordFreq[w]++;
    
    // Start at each position within wordLen
    for (int i = 0; i < wordLen; i++) {
        unordered_map<string, int> seen;
        int left = i, count = 0;
        
        for (int right = i; right <= (int)s.size() - wordLen; right += wordLen) {
            string word = s.substr(right, wordLen);
            
            if (wordFreq.count(word)) {
                seen[word]++;
                count++;
                
                while (seen[word] > wordFreq[word]) {
                    string leftWord = s.substr(left, wordLen);
                    seen[leftWord]--;
                    count--;
                    left += wordLen;
                }
                
                if (count == wordCount) {
                    result.push_back(left);
                }
            } else {
                seen.clear();
                count = 0;
                left = right + wordLen;
            }
        }
    }
    return result;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Sliding Window with HashMap ===\n\n";
    
    // 1. Subarrays with K Different Integers
    vector<int> arr1 = {1,2,1,2,3};
    cout << "1. Subarrays with 2 distinct: " << subarraysWithKDistinct(arr1, 2) << "\n";
    
    // 2. Nice Subarrays
    vector<int> arr2 = {1,1,2,1,1};
    cout << "2. Nice subarrays (k=3): " << numberOfSubarrays(arr2, 3) << "\n";
    
    // 3. Longest Substring with K Repeating
    cout << "3. Longest with >= 3 repeat: " << longestSubstring("aaabb", 3) << "\n";
    
    // 4. Max Frequency
    vector<int> arr4 = {1,2,4};
    cout << "4. Max frequency (k=5): " << maxFrequency(arr4, 5) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

Key Technique: exactly(k) = atMost(k) - atMost(k-1)

This is useful when finding subarrays with EXACTLY some property.
Convert to "at most" which is easier to solve with sliding window.

Common patterns:
1. Track frequency map as window slides
2. Track count of elements satisfying some property
3. Use two pointers with hash map for constraint checking
================================================================================
*/

