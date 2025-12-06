/*
================================================================================
              LINKED LIST - TWO POINTER TECHNIQUES ⭐
================================================================================

The most important patterns for linked list interview questions!

Pattern 1: Fast-Slow Pointers (Floyd's Tortoise & Hare)
Pattern 2: N-Distance Apart Pointers
Pattern 3: Two List Pointers

================================================================================
*/

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
================================================================================
PATTERN 1: FAST-SLOW POINTERS (Floyd's Algorithm)
================================================================================

Slow moves 1 step, Fast moves 2 steps
- They meet if there's a cycle
- When fast reaches end, slow is at middle

       slow
         ↓
    1 -> 2 -> 3 -> 4 -> 5 -> NULL
              ↑
             fast
*/

// 1.1 DETECT CYCLE
// LeetCode: 141. Linked List Cycle
// Time: O(n), Space: O(1)
bool hasCycle(ListNode* head) {
    if (!head || !head->next) return false;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;          // 1 step
        fast = fast->next->next;    // 2 steps
        
        if (slow == fast) {
            return true;    // They meet → cycle exists
        }
    }
    
    return false;   // Fast reached end → no cycle
}

/*
Why does this work?
- If cycle exists, fast will "lap" slow inside the cycle
- Distance decreases by 1 each step (fast gains 1 on slow)
- Eventually distance becomes 0 (they meet)
*/


// 1.2 FIND CYCLE START POSITION
// LeetCode: 142. Linked List Cycle II
// Time: O(n), Space: O(1)
/*
MATH EXPLANATION:
─────────────────
Let's say:
- Distance from head to cycle start = a
- Distance from cycle start to meeting point = b
- Remaining cycle length = c

When they meet:
- slow traveled: a + b
- fast traveled: a + b + (b + c) = a + 2b + c

Since fast travels 2x slow's distance:
  2(a + b) = a + 2b + c
  2a + 2b = a + 2b + c
  a = c

So if we start one pointer from HEAD and one from MEETING POINT,
both moving at same speed, they'll meet at CYCLE START!
*/
ListNode* detectCycle(ListNode* head) {
    if (!head || !head->next) return nullptr;
    
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Phase 1: Detect if cycle exists
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            // Phase 2: Find cycle start
            ListNode* ptr = head;
            while (ptr != slow) {
                ptr = ptr->next;
                slow = slow->next;
            }
            return ptr;  // Cycle start
        }
    }
    
    return nullptr;  // No cycle
}


// 1.3 FIND MIDDLE OF LINKED LIST
// LeetCode: 876. Middle of the Linked List
// Time: O(n), Space: O(1)
ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;  // For even length, returns second middle
}
/*
Example 1: 1 -> 2 -> 3 -> 4 -> 5
           s         f
              s              f (f reaches end)
           → returns 3 (middle)

Example 2: 1 -> 2 -> 3 -> 4 -> 5 -> 6
           s         f
              s              f
                 s                  f (f reaches end)
           → returns 4 (second middle for even)
*/

// Get first middle (for even length lists)
ListNode* middleNodeFirst(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast->next && fast->next->next) {  // Note the difference
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;  // For even length, returns first middle
}


// 1.4 FIND CYCLE LENGTH
int cycleLength(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            // Count cycle length
            int length = 1;
            ListNode* temp = slow->next;
            while (temp != slow) {
                length++;
                temp = temp->next;
            }
            return length;
        }
    }
    
    return 0;  // No cycle
}


/*
================================================================================
PATTERN 2: N-DISTANCE APART POINTERS
================================================================================

Move first pointer N nodes ahead, then move both together.
When first reaches end, second is at Nth from end.
*/

// 2.1 REMOVE NTH NODE FROM END
// LeetCode: 19. Remove Nth Node From End of List
// Time: O(n), Space: O(1)
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    
    ListNode* first = &dummy;
    ListNode* second = &dummy;
    
    // Move first N+1 nodes ahead (to get node BEFORE target)
    for (int i = 0; i <= n; i++) {
        first = first->next;
    }
    
    // Move both until first reaches end
    while (first) {
        first = first->next;
        second = second->next;
    }
    
    // Delete the nth node
    ListNode* toDelete = second->next;
    second->next = toDelete->next;
    delete toDelete;
    
    return dummy.next;
}
/*
Example: 1 -> 2 -> 3 -> 4 -> 5, n = 2
         d    1    2    3    4    5    NULL
         s                   f              (f is n+1=3 ahead)
              s                   f
                   s                   f
                        s                   f (f reaches NULL)
         second is at 3, delete 4
         Result: 1 -> 2 -> 3 -> 5
*/


// 2.2 GET NTH NODE FROM END (without deletion)
ListNode* getNthFromEnd(ListNode* head, int n) {
    ListNode* first = head;
    ListNode* second = head;
    
    // Move first N nodes ahead
    for (int i = 0; i < n; i++) {
        if (!first) return nullptr;  // n > length
        first = first->next;
    }
    
    // Move both until first reaches end
    while (first) {
        first = first->next;
        second = second->next;
    }
    
    return second;
}


// 2.3 REORDER LIST
// LeetCode: 143. Reorder List
// L0 → L1 → ... → Ln  becomes  L0 → Ln → L1 → Ln-1 → ...
// Time: O(n), Space: O(1)
void reorderList(ListNode* head) {
    if (!head || !head->next) return;
    
    // Step 1: Find middle
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Step 2: Reverse second half
    ListNode* second = slow->next;
    slow->next = nullptr;  // Cut the list
    
    ListNode* prev = nullptr;
    while (second) {
        ListNode* next = second->next;
        second->next = prev;
        prev = second;
        second = next;
    }
    second = prev;  // Head of reversed second half
    
    // Step 3: Merge alternately
    ListNode* first = head;
    while (second) {
        ListNode* temp1 = first->next;
        ListNode* temp2 = second->next;
        
        first->next = second;
        second->next = temp1;
        
        first = temp1;
        second = temp2;
    }
}
// 1 -> 2 -> 3 -> 4 -> 5 → 1 -> 5 -> 2 -> 4 -> 3


/*
================================================================================
PATTERN 3: TWO LIST POINTERS
================================================================================
*/

// 3.1 INTERSECTION OF TWO LINKED LISTS
// LeetCode: 160. Intersection of Two Linked Lists
// Time: O(m + n), Space: O(1)
/*
BEAUTIFUL TRICK:
Traverse both lists. When one ends, continue from the OTHER list's head.
They'll meet at intersection (or both reach null if no intersection).

List A: a1 -> a2 -> c1 -> c2 -> c3
List B: b1 -> b2 -> b3 -> c1 -> c2 -> c3

ptrA path: a1 -> a2 -> c1 -> c2 -> c3 -> b1 -> b2 -> b3 -> c1 (meets ptrB)
ptrB path: b1 -> b2 -> b3 -> c1 -> c2 -> c3 -> a1 -> a2 -> c1 (meets ptrA)
*/
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (!headA || !headB) return nullptr;
    
    ListNode* ptrA = headA;
    ListNode* ptrB = headB;
    
    while (ptrA != ptrB) {
        ptrA = ptrA ? ptrA->next : headB;
        ptrB = ptrB ? ptrB->next : headA;
    }
    
    return ptrA;  // Either intersection or null
}


// 3.2 PALINDROME LINKED LIST
// LeetCode: 234. Palindrome Linked List
// Time: O(n), Space: O(1)
bool isPalindrome(ListNode* head) {
    if (!head || !head->next) return true;
    
    // Step 1: Find middle (first middle for even length)
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Step 2: Reverse second half
    ListNode* secondHalf = slow->next;
    ListNode* prev = nullptr;
    while (secondHalf) {
        ListNode* next = secondHalf->next;
        secondHalf->next = prev;
        prev = secondHalf;
        secondHalf = next;
    }
    secondHalf = prev;
    
    // Step 3: Compare both halves
    ListNode* firstHalf = head;
    while (secondHalf) {
        if (firstHalf->val != secondHalf->val) {
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }
    
    return true;
}
// 1 -> 2 -> 2 -> 1 → true
// 1 -> 2 -> 3 -> 2 -> 1 → true
// 1 -> 2 → false


// 3.3 HAPPY NUMBER (uses same fast-slow concept)
// LeetCode: 202. Happy Number
bool isHappy(int n) {
    auto getNext = [](int num) {
        int sum = 0;
        while (num > 0) {
            int digit = num % 10;
            sum += digit * digit;
            num /= 10;
        }
        return sum;
    };
    
    int slow = n;
    int fast = getNext(n);
    
    while (fast != 1 && slow != fast) {
        slow = getNext(slow);
        fast = getNext(getNext(fast));
    }
    
    return fast == 1;
}


// Utility functions
ListNode* createList(const vector<int>& arr) {
    if (arr.empty()) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* curr = head;
    for (int i = 1; i < arr.size(); i++) {
        curr->next = new ListNode(arr[i]);
        curr = curr->next;
    }
    return head;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL" << endl;
}


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Two Pointer Techniques ===\n\n";
    
    // Middle Node
    cout << "--- Find Middle ---" << endl;
    ListNode* list1 = createList({1, 2, 3, 4, 5});
    cout << "List: ";
    printList(list1);
    cout << "Middle: " << middleNode(list1)->val << endl;
    
    // Nth from End
    cout << "\n--- Nth from End ---" << endl;
    ListNode* list2 = createList({1, 2, 3, 4, 5});
    cout << "2nd from end: " << getNthFromEnd(list2, 2)->val << endl;
    
    // Remove Nth from End
    cout << "\n--- Remove Nth from End ---" << endl;
    ListNode* list3 = createList({1, 2, 3, 4, 5});
    cout << "Before: ";
    printList(list3);
    list3 = removeNthFromEnd(list3, 2);
    cout << "After remove 2nd from end: ";
    printList(list3);
    
    // Palindrome
    cout << "\n--- Palindrome Check ---" << endl;
    ListNode* palindrome = createList({1, 2, 3, 2, 1});
    cout << "1->2->3->2->1 is palindrome: " << (isPalindrome(palindrome) ? "Yes" : "No") << endl;
    
    ListNode* notPalindrome = createList({1, 2, 3, 4});
    cout << "1->2->3->4 is palindrome: " << (isPalindrome(notPalindrome) ? "Yes" : "No") << endl;
    
    // Reorder List
    cout << "\n--- Reorder List ---" << endl;
    ListNode* list4 = createList({1, 2, 3, 4, 5});
    cout << "Before: ";
    printList(list4);
    reorderList(list4);
    cout << "After reorder: ";
    printList(list4);
    
    // Cycle Detection
    cout << "\n--- Cycle Detection ---" << endl;
    ListNode* cycleList = createList({1, 2, 3, 4, 5});
    cout << "No cycle: " << (hasCycle(cycleList) ? "Has cycle" : "No cycle") << endl;
    
    // Create cycle: 5 -> 2
    ListNode* tail = cycleList;
    ListNode* cycleStart = cycleList->next;
    while (tail->next) tail = tail->next;
    tail->next = cycleStart;
    cout << "With cycle: " << (hasCycle(cycleList) ? "Has cycle" : "No cycle") << endl;
    cout << "Cycle starts at: " << detectCycle(cycleList)->val << endl;
    
    return 0;
}

/*
================================================================================
                              CHEAT SHEET
================================================================================

FAST-SLOW POINTER:
─────────────────
ListNode *slow = head, *fast = head;
while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;
}
// slow at middle, or they meet in cycle

N-APART POINTER:
─────────────────
ListNode *first = head, *second = head;
for (int i = 0; i < n; i++) first = first->next;
while (first) {
    first = first->next;
    second = second->next;
}
// second is at Nth from end

INTERSECTION:
─────────────────
while (ptrA != ptrB) {
    ptrA = ptrA ? ptrA->next : headB;
    ptrB = ptrB ? ptrB->next : headA;
}
// ptrA is intersection or null

================================================================================
*/

