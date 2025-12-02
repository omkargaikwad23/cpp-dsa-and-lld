/*
================================================================================
             TWO POINTERS - SAME DIRECTION (FAST & SLOW)
================================================================================

Both pointers start from same position, move at different speeds or conditions.
Used for: In-place array modification, cycle detection, linked list problems.

Key Template:
  int slow = 0;
  for (int fast = 0; fast < n; fast++) {
      if ( condition ) {
          arr[slow] = arr[fast];  // or swap/process
          slow++;
      }
  }

Time: O(n) | Space: O(1)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Remove Duplicates from Sorted Array (LeetCode 26)
────────────────────────────────────────────────────────────
Remove duplicates in-place, return new length.

Input: nums = [0,0,1,1,1,2,2,3,3,4]
Output: 5 (nums = [0,1,2,3,4,...])

Time: O(n) | Space: O(1)
*/
int removeDuplicates(vector<int>& nums) {
    if (nums.empty()) return 0;
    
    int slow = 1;  // First element always stays
    for (int fast = 1; fast < nums.size(); fast++) {
        if (nums[fast] != nums[fast - 1]) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow;
}


/*
PROBLEM 2: Remove Duplicates II - Allow at most 2 (LeetCode 80)
───────────────────────────────────────────────────────────────
Allow each element to appear at most twice.

Input: nums = [1,1,1,2,2,3]
Output: 5 (nums = [1,1,2,2,3])

Time: O(n) | Space: O(1)
*/
int removeDuplicatesII(vector<int>& nums) {
    if (nums.size() <= 2) return nums.size();
    
    int slow = 2;  // First two elements always stay
    for (int fast = 2; fast < nums.size(); fast++) {
        if (nums[fast] != nums[slow - 2]) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow;
}


/*
PROBLEM 3: Remove Element (LeetCode 27)
───────────────────────────────────────
Remove all occurrences of val in-place.

Input: nums = [3,2,2,3], val = 3
Output: 2 (nums = [2,2,...])

Time: O(n) | Space: O(1)
*/
int removeElement(vector<int>& nums, int val) {
    int slow = 0;
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
    }
    return slow;
}


/*
PROBLEM 4: Move Zeros (LeetCode 283)
────────────────────────────────────
Move all zeros to end while maintaining order of non-zeros.

Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]

Time: O(n) | Space: O(1)
*/
void moveZeroes(vector<int>& nums) {
    int slow = 0;
    for (int fast = 0; fast < nums.size(); fast++) {
        if (nums[fast] != 0) {
            swap(nums[slow], nums[fast]);
            slow++;
        }
    }
}


/*
PROBLEM 5: Merge Sorted Array (LeetCode 88)
───────────────────────────────────────────
Merge nums2 into nums1 (nums1 has extra space).

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]

Approach: Fill from end to avoid overwriting

Time: O(m + n) | Space: O(1)
*/
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    
    while (i >= 0 && j >= 0) {
        if (nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
    
    // Copy remaining elements from nums2
    while (j >= 0) {
        nums1[k--] = nums2[j--];
    }
}


/*
PROBLEM 6: Linked List Cycle Detection (Floyd's Algorithm)
──────────────────────────────────────────────────────────
Detect if linked list has a cycle.

Approach: Slow moves 1 step, fast moves 2 steps. If they meet, cycle exists.

Time: O(n) | Space: O(1)
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

bool hasCycle(ListNode *head) {
    if (!head || !head->next) return false;
    
    ListNode *slow = head, *fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) return true;
    }
    
    return false;
}


/*
PROBLEM 7: Find Cycle Start (LeetCode 142)
──────────────────────────────────────────
Find the node where cycle begins.

Approach: After detection, reset one pointer to head. Move both at same speed.

Time: O(n) | Space: O(1)
*/
ListNode* detectCycle(ListNode *head) {
    if (!head || !head->next) return nullptr;
    
    ListNode *slow = head, *fast = head;
    
    // Find meeting point
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) break;
    }
    
    if (!fast || !fast->next) return nullptr;  // No cycle
    
    // Reset slow to head, move both at same speed
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    
    return slow;
}


/*
PROBLEM 8: Find Middle of Linked List (LeetCode 876)
────────────────────────────────────────────────────
Return middle node (second middle if two middle nodes).

Time: O(n) | Space: O(1)
*/
ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}


/*
PROBLEM 9: Happy Number (LeetCode 202)
──────────────────────────────────────
A number is happy if sum of squares of digits eventually equals 1.

Input: n = 19
Output: true (1² + 9² = 82 → 8² + 2² = 68 → ... → 1)

Approach: Use Floyd's cycle detection (if not happy, will cycle)

Time: O(log n) | Space: O(1)
*/
int getNext(int n) {
    int sum = 0;
    while (n > 0) {
        int d = n % 10;
        sum += d * d;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    int slow = n, fast = getNext(n);
    
    while (fast != 1 && slow != fast) {
        slow = getNext(slow);
        fast = getNext(getNext(fast));
    }
    
    return fast == 1;
}


/*
PROBLEM 10: Find Duplicate Number (LeetCode 287)
────────────────────────────────────────────────
Array has n+1 integers in [1, n]. Find the duplicate.

Input: nums = [1,3,4,2,2]
Output: 2

Approach: Treat as linked list cycle detection (index → value → next index)

Time: O(n) | Space: O(1)
*/
int findDuplicate(vector<int>& nums) {
    int slow = nums[0], fast = nums[0];
    
    // Find meeting point
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    
    // Find cycle start
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    
    return slow;
}


/*
PROBLEM 11: Partition Array (QuickSort Partition)
─────────────────────────────────────────────────
Partition array around pivot (elements < pivot on left).

Time: O(n) | Space: O(1)
*/
int partition(vector<int>& nums, int low, int high) {
    int pivot = nums[high];
    int slow = low;
    
    for (int fast = low; fast < high; fast++) {
        if (nums[fast] < pivot) {
            swap(nums[slow], nums[fast]);
            slow++;
        }
    }
    
    swap(nums[slow], nums[high]);
    return slow;
}


/*
PROBLEM 12: Intersection of Two Linked Lists (LeetCode 160)
───────────────────────────────────────────────────────────
Find node where two lists intersect.

Approach: Traverse both, when end reached switch to other list head.

Time: O(m + n) | Space: O(1)
*/
ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (!headA || !headB) return nullptr;
    
    ListNode *pA = headA, *pB = headB;
    
    while (pA != pB) {
        pA = pA ? pA->next : headB;
        pB = pB ? pB->next : headA;
    }
    
    return pA;
}


/*
PROBLEM 13: String Compression (LeetCode 443)
─────────────────────────────────────────────
Compress ["a","a","b","b","c","c","c"] to ["a","2","b","2","c","3"]

Time: O(n) | Space: O(1)
*/
int compress(vector<char>& chars) {
    int write = 0, read = 0;
    
    while (read < chars.size()) {
        char current = chars[read];
        int count = 0;
        
        // Count consecutive same chars
        while (read < chars.size() && chars[read] == current) {
            read++;
            count++;
        }
        
        // Write character
        chars[write++] = current;
        
        // Write count if > 1
        if (count > 1) {
            string countStr = to_string(count);
            for (char c : countStr) {
                chars[write++] = c;
            }
        }
    }
    
    return write;
}


// ============================================================================
// MAIN - Demo
// ============================================================================

int main() {
    cout << "=== Two Pointers - Same Direction ===\n\n";
    
    // 1. Remove Duplicates
    vector<int> arr1 = {0,0,1,1,1,2,2,3,3,4};
    int len1 = removeDuplicates(arr1);
    cout << "1. Remove Duplicates: " << len1 << " elements\n";
    
    // 3. Remove Element
    vector<int> arr3 = {3,2,2,3};
    cout << "3. Remove 3s: " << removeElement(arr3, 3) << " elements\n";
    
    // 4. Move Zeros
    vector<int> arr4 = {0,1,0,3,12};
    moveZeroes(arr4);
    cout << "4. Move Zeros: ";
    for (int x : arr4) cout << x << " ";
    cout << "\n";
    
    // 9. Happy Number
    cout << "9. Is 19 happy? " << (isHappy(19) ? "true" : "false") << "\n";
    
    // 10. Find Duplicate
    vector<int> arr10 = {1,3,4,2,2};
    cout << "10. Duplicate: " << findDuplicate(arr10) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================
+──────────────────────────────+─────────────────────────────────────────────────+
| Problem                      | Slow/Fast Behavior                              |
+──────────────────────────────+─────────────────────────────────────────────────+
| Remove Duplicates            | Slow = write position, Fast = scan              |
| Move Zeros                   | Slow = non-zero position, Fast = scan           |
| Cycle Detection              | Slow = 1 step, Fast = 2 steps                   |
| Find Middle                  | Slow = 1 step, Fast = 2 steps                   |
| Happy Number                 | Floyd's on digit square sum sequence            |
| Find Duplicate               | Treat array as linked list with cycle           |
+──────────────────────────────+─────────────────────────────────────────────────+
================================================================================
*/

