/*
================================================================================
                    GREEDY - STRING PROBLEMS
================================================================================

Build or modify strings by making locally optimal character choices.
Often uses monotonic stack for "smallest/largest" string construction.

Time: Usually O(n) | Space: O(n)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Remove K Digits (LeetCode 402)
─────────────────────────────────────────
Remove k digits to get smallest possible number.

Input: num = "1432219", k = 3
Output: "1219"

Strategy: Monotonic increasing stack - remove larger digits

Time: O(n) | Space: O(n)
*/
string removeKdigits(string num, int k) {
    string result;  // Use as stack
    
    for (char c : num) {
        while (!result.empty() && k > 0 && result.back() > c) {
            result.pop_back();
            k--;
        }
        result.push_back(c);
    }
    
    // Remove remaining k digits from end
    while (k > 0) {
        result.pop_back();
        k--;
    }
    
    // Remove leading zeros
    int start = 0;
    while (start < result.size() && result[start] == '0') {
        start++;
    }
    
    result = result.substr(start);
    return result.empty() ? "0" : result;
}


/*
PROBLEM 2: Remove Duplicate Letters (LeetCode 316)
──────────────────────────────────────────────────
Remove duplicates so each letter appears once. Return smallest result.

Input: s = "cbacdcbc"
Output: "acdb"

Strategy: Monotonic stack with last occurrence tracking

Time: O(n) | Space: O(1) - 26 letters
*/
string removeDuplicateLetters(string s) {
    vector<int> lastIndex(26, 0);
    vector<bool> inStack(26, false);
    
    for (int i = 0; i < s.size(); i++) {
        lastIndex[s[i] - 'a'] = i;
    }
    
    string result;
    
    for (int i = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        
        if (inStack[c]) continue;
        
        // Remove larger chars if they appear later
        while (!result.empty() && result.back() > s[i] && 
               lastIndex[result.back() - 'a'] > i) {
            inStack[result.back() - 'a'] = false;
            result.pop_back();
        }
        
        result.push_back(s[i]);
        inStack[c] = true;
    }
    
    return result;
}


/*
PROBLEM 3: Create Maximum Number (LeetCode 321)
───────────────────────────────────────────────
Pick k digits from two arrays to form largest number.

Input: nums1 = [3,4,6,5], nums2 = [9,1,2,5,8,3], k = 5
Output: [9,8,6,5,3]

Strategy: Try all splits, get max from each array, merge

Time: O(k * (m + n + k)) | Space: O(k)
*/
class CreateMaxNumber {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        vector<int> result(k, 0);
        
        // Try taking i from nums1, k-i from nums2
        for (int i = max(0, k - n); i <= min(k, m); i++) {
            vector<int> max1 = maxFromArray(nums1, i);
            vector<int> max2 = maxFromArray(nums2, k - i);
            vector<int> merged = merge(max1, max2);
            
            if (greater(merged, 0, result, 0)) {
                result = merged;
            }
        }
        
        return result;
    }
    
private:
    // Get largest number with len digits from array
    vector<int> maxFromArray(vector<int>& nums, int len) {
        vector<int> result;
        int drop = nums.size() - len;
        
        for (int num : nums) {
            while (!result.empty() && drop > 0 && result.back() < num) {
                result.pop_back();
                drop--;
            }
            result.push_back(num);
        }
        
        result.resize(len);
        return result;
    }
    
    // Merge two arrays to form largest
    vector<int> merge(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result;
        int i = 0, j = 0;
        
        while (i < nums1.size() || j < nums2.size()) {
            if (greater(nums1, i, nums2, j)) {
                result.push_back(nums1[i++]);
            } else {
                result.push_back(nums2[j++]);
            }
        }
        
        return result;
    }
    
    bool greater(vector<int>& nums1, int i, vector<int>& nums2, int j) {
        while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
            i++;
            j++;
        }
        return j == nums2.size() || (i < nums1.size() && nums1[i] > nums2[j]);
    }
};


/*
PROBLEM 4: Reorganize String (LeetCode 767)
───────────────────────────────────────────
Rearrange string so no adjacent characters are same.

Input: s = "aab"
Output: "aba"

Strategy: Use max-heap, always pick most frequent that differs from last

Time: O(n log 26) = O(n) | Space: O(26) = O(1)
*/
string reorganizeString(string s) {
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;
    
    priority_queue<pair<int, char>> pq;  // {count, char}
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            if (freq[i] > (s.size() + 1) / 2) return "";  // Impossible
            pq.push({freq[i], 'a' + i});
        }
    }
    
    string result;
    
    while (pq.size() >= 2) {
        auto [cnt1, c1] = pq.top(); pq.pop();
        auto [cnt2, c2] = pq.top(); pq.pop();
        
        result += c1;
        result += c2;
        
        if (cnt1 > 1) pq.push({cnt1 - 1, c1});
        if (cnt2 > 1) pq.push({cnt2 - 1, c2});
    }
    
    if (!pq.empty()) {
        result += pq.top().second;
    }
    
    return result;
}


/*
PROBLEM 5: Smallest Subsequence of Distinct Characters (LeetCode 1081)
──────────────────────────────────────────────────────────────────────
Same as Remove Duplicate Letters.
*/
string smallestSubsequence(string s) {
    return removeDuplicateLetters(s);
}


/*
PROBLEM 6: Largest Number (LeetCode 179)
────────────────────────────────────────
Arrange numbers to form largest number.

Input: nums = [3,30,34,5,9]
Output: "9534330"

Strategy: Custom comparator - compare concatenations

Time: O(n log n * k) | Space: O(n * k) where k = avg digit length
*/
string largestNumber(vector<int>& nums) {
    vector<string> strs;
    for (int num : nums) strs.push_back(to_string(num));
    
    sort(strs.begin(), strs.end(), [](const string& a, const string& b) {
        return a + b > b + a;
    });
    
    if (strs[0] == "0") return "0";
    
    string result;
    for (const string& s : strs) result += s;
    
    return result;
}


/*
PROBLEM 7: Valid Parenthesis String (LeetCode 678)
──────────────────────────────────────────────────
'(' , ')' , '*' (can be '(' or ')' or empty). Check if valid.

Input: s = "(*))"
Output: true

Strategy: Track range of possible open counts [lo, hi]

Time: O(n) | Space: O(1)
*/
bool checkValidString(string s) {
    int lo = 0, hi = 0;  // Range of possible open count
    
    for (char c : s) {
        if (c == '(') {
            lo++;
            hi++;
        } else if (c == ')') {
            lo = max(0, lo - 1);
            hi--;
        } else {  // '*'
            lo = max(0, lo - 1);  // Treat as ')' or empty
            hi++;                  // Treat as '('
        }
        
        if (hi < 0) return false;  // Too many ')'
    }
    
    return lo == 0;
}


/*
PROBLEM 8: Minimum Deletions to Make Character Frequencies Unique (LeetCode 1647)
─────────────────────────────────────────────────────────────────────────────────
Delete minimum characters so no two letters have same frequency.

Input: s = "aaabbbcc"
Output: 2

Time: O(n + 26 log 26) | Space: O(26)
*/
int minDeletions(string s) {
    vector<int> freq(26, 0);
    for (char c : s) freq[c - 'a']++;
    
    sort(freq.rbegin(), freq.rend());
    
    int deletions = 0;
    int maxAllowed = freq[0];
    
    for (int f : freq) {
        if (f > maxAllowed) {
            deletions += f - maxAllowed;
            f = maxAllowed;
        }
        maxAllowed = max(0, f - 1);
    }
    
    return deletions;
}


/*
PROBLEM 9: Minimum Add to Make Parentheses Valid (LeetCode 921)
───────────────────────────────────────────────────────────────
Minimum insertions to make parentheses valid.

Input: s = "())"
Output: 1 (add '(' at start)

Time: O(n) | Space: O(1)
*/
int minAddToMakeValid(string s) {
    int open = 0, close = 0;
    
    for (char c : s) {
        if (c == '(') {
            open++;
        } else {
            if (open > 0) open--;
            else close++;
        }
    }
    
    return open + close;
}


/*
PROBLEM 10: Break a Palindrome (LeetCode 1328)
──────────────────────────────────────────────
Change one character to make non-palindrome with smallest lexicographic order.

Input: palindrome = "abccba"
Output: "aaccba"

Time: O(n) | Space: O(n)
*/
string breakPalindrome(string s) {
    int n = s.size();
    if (n == 1) return "";
    
    // Find first non-'a' in first half and change to 'a'
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != 'a') {
            s[i] = 'a';
            return s;
        }
    }
    
    // All 'a's in first half - change last char to 'b'
    s[n - 1] = 'b';
    return s;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== String Greedy ===\n\n";
    
    // 1. Remove K Digits
    cout << "1. Remove 3 from '1432219': " << removeKdigits("1432219", 3) << "\n";
    
    // 2. Remove Duplicate Letters
    cout << "2. Remove duplicates 'cbacdcbc': " << removeDuplicateLetters("cbacdcbc") << "\n";
    
    // 4. Reorganize String
    cout << "4. Reorganize 'aab': " << reorganizeString("aab") << "\n";
    
    // 6. Largest Number
    vector<int> nums = {3, 30, 34, 5, 9};
    cout << "6. Largest number: " << largestNumber(nums) << "\n";
    
    // 7. Valid Parenthesis String
    cout << "7. Valid '(*)': " << (checkValidString("(*)") ? "true" : "false") << "\n";
    
    // 10. Break Palindrome
    cout << "10. Break 'abccba': " << breakPalindrome("abccba") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Greedy Technique                               |
+───────────────────────────────+────────────────────────────────────────────────+
| Remove K Digits               | Monotonic increasing stack                     |
| Remove Duplicate Letters      | Stack + last occurrence tracking               |
| Reorganize String             | Max-heap, alternate most frequent              |
| Largest Number                | Custom sort by a+b > b+a                       |
| Valid Parenthesis String      | Track range [lo, hi] of open counts            |
| Break Palindrome              | Change first non-'a' to 'a', or last to 'b'    |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

