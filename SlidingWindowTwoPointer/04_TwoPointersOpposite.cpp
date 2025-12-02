/*
================================================================================
                TWO POINTERS - OPPOSITE DIRECTION (CONVERGING)
================================================================================

Two pointers start from both ends and move towards each other.
Used for: Sorted arrays, palindromes, pair finding, container problems.

Key Template:
  int left = 0, right = n - 1;
  while (left < right) {
      if ( condition met ) {
          // Process answer
      } else if ( need smaller values ) {
          right--;
      } else {
          left++;
      }
  }

Time: Usually O(n) or O(n²) for k-sum problems
Space: Usually O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Two Sum II - Sorted Array (LeetCode 167)
───────────────────────────────────────────────────
Find two numbers that add up to target in sorted array.

Input: numbers = [2,7,11,15], target = 9
Output: [1,2] (1-indexed)

Time: O(n) | Space: O(1)
*/
vector<int> twoSumSorted(vector<int>& numbers, int target) {
    int left = 0, right = numbers.size() - 1;
    
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        
        if (sum == target) {
            return {left + 1, right + 1};  // 1-indexed
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    return {};  // No solution found
}


/*
PROBLEM 2: Three Sum (LeetCode 15)
──────────────────────────────────
Find all unique triplets that sum to zero.

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]

Approach: Sort, fix one number, use two pointers for remaining

Time: O(n²) | Space: O(1) excluding output
*/
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    int n = nums.size();
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 2; i++) {
        // Skip duplicates for first number
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        // Early termination
        if (nums[i] > 0) break;  // Can't sum to 0 if smallest > 0
        
        int left = i + 1, right = n - 1;
        int target = -nums[i];
        
        while (left < right) {
            int sum = nums[left] + nums[right];
            
            if (sum == target) {
                result.push_back({nums[i], nums[left], nums[right]});
                
                // Skip duplicates
                while (left < right && nums[left] == nums[left + 1]) left++;
                while (left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}


/*
PROBLEM 3: Three Sum Closest (LeetCode 16)
──────────────────────────────────────────
Find three integers with sum closest to target.

Input: nums = [-1,2,1,-4], target = 1
Output: 2 ((-1) + 2 + 1 = 2)

Time: O(n²) | Space: O(1)
*/
int threeSumClosest(vector<int>& nums, int target) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int closest = nums[0] + nums[1] + nums[2];
    
    for (int i = 0; i < n - 2; i++) {
        int left = i + 1, right = n - 1;
        
        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if (abs(sum - target) < abs(closest - target)) {
                closest = sum;
            }
            
            if (sum == target) {
                return sum;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return closest;
}


/*
PROBLEM 4: Four Sum (LeetCode 18)
─────────────────────────────────
Find all unique quadruplets that sum to target.

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Time: O(n³) | Space: O(1) excluding output
*/
vector<vector<int>> fourSum(vector<int>& nums, int target) {
    vector<vector<int>> result;
    int n = nums.size();
    if (n < 4) return result;
    
    sort(nums.begin(), nums.end());
    
    for (int i = 0; i < n - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        for (int j = i + 1; j < n - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            
            int left = j + 1, right = n - 1;
            long long remaining = (long long)target - nums[i] - nums[j];
            
            while (left < right) {
                long long sum = nums[left] + nums[right];
                
                if (sum == remaining) {
                    result.push_back({nums[i], nums[j], nums[left], nums[right]});
                    
                    while (left < right && nums[left] == nums[left + 1]) left++;
                    while (left < right && nums[right] == nums[right - 1]) right--;
                    
                    left++;
                    right--;
                } else if (sum < remaining) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }
    
    return result;
}


/*
PROBLEM 5: Container With Most Water (LeetCode 11)
──────────────────────────────────────────────────
Find two lines that together with x-axis form max water container.

Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49 (between index 1 and 8)

Key Insight: Move the pointer with smaller height (can only improve)

Time: O(n) | Space: O(1)
*/
int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxWater = 0;
    
    while (left < right) {
        int width = right - left;
        int h = min(height[left], height[right]);
        maxWater = max(maxWater, width * h);
        
        // Move pointer with smaller height
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    
    return maxWater;
}


/*
PROBLEM 6: Trapping Rain Water (LeetCode 42)
────────────────────────────────────────────
Calculate trapped water between bars.

Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6

Approach: Two pointers with left_max and right_max tracking

Time: O(n) | Space: O(1)
*/
int trap(vector<int>& height) {
    int n = height.size();
    if (n == 0) return 0;
    
    int left = 0, right = n - 1;
    int leftMax = 0, rightMax = 0;
    int water = 0;
    
    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            left++;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            right--;
        }
    }
    
    return water;
}


/*
PROBLEM 7: Valid Palindrome (LeetCode 125)
──────────────────────────────────────────
Check if string is palindrome (ignore non-alphanumeric, case-insensitive).

Input: s = "A man, a plan, a canal: Panama"
Output: true

Time: O(n) | Space: O(1)
*/
bool isPalindrome(string s) {
    int left = 0, right = s.size() - 1;
    
    while (left < right) {
        // Skip non-alphanumeric
        while (left < right && !isalnum(s[left])) left++;
        while (left < right && !isalnum(s[right])) right--;
        
        if (tolower(s[left]) != tolower(s[right])) {
            return false;
        }
        
        left++;
        right--;
    }
    
    return true;
}


/*
PROBLEM 8: Valid Palindrome II (LeetCode 680)
─────────────────────────────────────────────
Check if string can be palindrome by deleting at most one character.

Input: s = "abca"
Output: true (remove 'c' or 'b')

Time: O(n) | Space: O(1)
*/
bool validPalindromeII(string s) {
    auto isPalin = [&](int l, int r) {
        while (l < r) {
            if (s[l] != s[r]) return false;
            l++; r--;
        }
        return true;
    };
    
    int left = 0, right = s.size() - 1;
    
    while (left < right) {
        if (s[left] != s[right]) {
            // Try skipping either left or right
            return isPalin(left + 1, right) || isPalin(left, right - 1);
        }
        left++;
        right--;
    }
    
    return true;
}


/*
PROBLEM 9: Reverse String (LeetCode 344)
────────────────────────────────────────
Reverse array of characters in-place.

Input: s = ['h','e','l','l','o']
Output: ['o','l','l','e','h']

Time: O(n) | Space: O(1)
*/
void reverseString(vector<char>& s) {
    int left = 0, right = s.size() - 1;
    
    while (left < right) {
        swap(s[left], s[right]);
        left++;
        right--;
    }
}


/*
PROBLEM 10: Reverse Vowels of a String (LeetCode 345)
─────────────────────────────────────────────────────
Reverse only the vowels in the string.

Input: s = "hello"
Output: "holle"

Time: O(n) | Space: O(1)
*/
string reverseVowels(string s) {
    unordered_set<char> vowels = {'a','e','i','o','u','A','E','I','O','U'};
    int left = 0, right = s.size() - 1;
    
    while (left < right) {
        while (left < right && !vowels.count(s[left])) left++;
        while (left < right && !vowels.count(s[right])) right--;
        
        swap(s[left], s[right]);
        left++;
        right--;
    }
    
    return s;
}


/*
PROBLEM 11: Sort Colors - Dutch National Flag (LeetCode 75)
───────────────────────────────────────────────────────────
Sort array with 0, 1, 2 in one pass.

Input: nums = [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]

Three pointers: low, mid, high

Time: O(n) | Space: O(1)
*/
void sortColors(vector<int>& nums) {
    int low = 0, mid = 0, high = nums.size() - 1;
    
    while (mid <= high) {
        if (nums[mid] == 0) {
            swap(nums[low], nums[mid]);
            low++;
            mid++;
        } else if (nums[mid] == 1) {
            mid++;
        } else {  // nums[mid] == 2
            swap(nums[mid], nums[high]);
            high--;
            // Don't increment mid, need to check swapped value
        }
    }
}


/*
PROBLEM 12: Squares of a Sorted Array (LeetCode 977)
────────────────────────────────────────────────────
Given sorted array, return squares in sorted order.

Input: nums = [-4,-1,0,3,10]
Output: [0,1,9,16,100]

Approach: Two pointers from ends, larger abs value goes to result end

Time: O(n) | Space: O(n)
*/
vector<int> sortedSquares(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n);
    int left = 0, right = n - 1;
    int pos = n - 1;  // Fill from end
    
    while (left <= right) {
        int leftSq = nums[left] * nums[left];
        int rightSq = nums[right] * nums[right];
        
        if (leftSq > rightSq) {
            result[pos] = leftSq;
            left++;
        } else {
            result[pos] = rightSq;
            right--;
        }
        pos--;
    }
    
    return result;
}


/*
PROBLEM 13: Boats to Save People (LeetCode 881)
───────────────────────────────────────────────
Each boat carries at most 2 people with weight limit.
Find minimum boats needed.

Input: people = [3,2,2,1], limit = 3
Output: 3 ([1,2], [2], [3])

Approach: Sort, pair heaviest with lightest if possible

Time: O(n log n) | Space: O(1)
*/
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    int left = 0, right = people.size() - 1;
    int boats = 0;
    
    while (left <= right) {
        // Heaviest person always takes a boat
        if (people[left] + people[right] <= limit) {
            left++;  // Lightest can join
        }
        right--;  // Heaviest used boat
        boats++;
    }
    
    return boats;
}


/*
PROBLEM 14: Two Sum Less Than K (LeetCode 1099 - Premium)
─────────────────────────────────────────────────────────
Find maximum sum of two numbers less than k.

Input: nums = [34,23,1,24,75,33,54,8], k = 60
Output: 58 (23 + 34)

Time: O(n log n) | Space: O(1)
*/
int twoSumLessThanK(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    int left = 0, right = nums.size() - 1;
    int maxSum = -1;
    
    while (left < right) {
        int sum = nums[left] + nums[right];
        
        if (sum < k) {
            maxSum = max(maxSum, sum);
            left++;
        } else {
            right--;
        }
    }
    
    return maxSum;
}


/*
PROBLEM 15: Partition Labels (LeetCode 763)
───────────────────────────────────────────
Partition string so each letter appears in at most one part.

Input: s = "ababcbacadefegdehijhklij"
Output: [9,7,8]

Approach: Track last occurrence, extend partition to include all occurrences

Time: O(n) | Space: O(1)
*/
vector<int> partitionLabels(string s) {
    vector<int> lastIndex(26, 0);
    for (int i = 0; i < s.size(); i++) {
        lastIndex[s[i] - 'a'] = i;
    }
    
    vector<int> result;
    int start = 0, end = 0;
    
    for (int i = 0; i < s.size(); i++) {
        end = max(end, lastIndex[s[i] - 'a']);
        
        if (i == end) {
            result.push_back(end - start + 1);
            start = i + 1;
        }
    }
    
    return result;
}


// ============================================================================
// MAIN - Demo all functions
// ============================================================================

int main() {
    cout << "=== Two Pointers - Opposite Direction ===\n\n";
    
    // 1. Two Sum Sorted
    vector<int> nums1 = {2,7,11,15};
    vector<int> res1 = twoSumSorted(nums1, 9);
    cout << "1. Two Sum Sorted: [" << res1[0] << "," << res1[1] << "]\n";
    
    // 2. Three Sum
    vector<int> nums2 = {-1,0,1,2,-1,-4};
    vector<vector<int>> res2 = threeSum(nums2);
    cout << "2. Three Sum count: " << res2.size() << " triplets\n";
    
    // 5. Container With Most Water
    vector<int> heights = {1,8,6,2,5,4,8,3,7};
    cout << "5. Max Water: " << maxArea(heights) << "\n";
    
    // 6. Trapping Rain Water
    vector<int> bars = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "6. Trapped Water: " << trap(bars) << "\n";
    
    // 7. Valid Palindrome
    cout << "7. Is Palindrome: " << (isPalindrome("A man, a plan, a canal: Panama") ? "true" : "false") << "\n";
    
    // 11. Sort Colors
    vector<int> colors = {2,0,2,1,1,0};
    sortColors(colors);
    cout << "11. Sorted Colors: ";
    for (int c : colors) cout << c << " ";
    cout << "\n";
    
    // 12. Sorted Squares
    vector<int> arr = {-4,-1,0,3,10};
    vector<int> squares = sortedSquares(arr);
    cout << "12. Sorted Squares: ";
    for (int s : squares) cout << s << " ";
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY TABLE
================================================================================

+────────────────────────────────+───────────────────────────────────────────────+
| Problem                        | Key Decision Logic                            |
+────────────────────────────────+───────────────────────────────────────────────+
| Two Sum (sorted)               | sum < target → left++, else right--           |
| Three/Four Sum                 | Fix elements, use two pointers for rest       |
| Container With Most Water      | Move pointer with smaller height              |
| Trapping Rain Water            | Process smaller height side, track max        |
| Valid Palindrome               | Move both inward, skip non-alphanumeric       |
| Sort Colors                    | Three pointers: low, mid, high                |
| Squares of Sorted Array        | Compare absolute values, fill from end        |
| Boats to Save People           | Pair heaviest with lightest if possible       |
+────────────────────────────────+───────────────────────────────────────────────+

KEY INSIGHT: Converging pointers work when:
1. Array is sorted (or can be sorted)
2. We need to find pairs/triplets satisfying some condition
3. We can decide which pointer to move based on current state

================================================================================
*/

