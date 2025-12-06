/*
================================================================================
                  LINKED LIST - REVERSE PROBLEMS ⭐
================================================================================

Reversal is one of the most common operations in linked list problems.
Master the basic pattern and variations!

Pattern 1: Basic Reversal (Iterative & Recursive)
Pattern 2: Reverse Between Positions
Pattern 3: Reverse in Groups
Pattern 4: Rotate List

================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
================================================================================
PATTERN 1: BASIC REVERSAL
================================================================================
*/

// 1.1 ITERATIVE REVERSAL - O(n) time, O(1) space
// LeetCode: 206. Reverse Linked List
/*
VISUALIZATION:
─────────────
NULL  1 -> 2 -> 3 -> 4 -> NULL
 ↑    ↑    ↑
prev curr next

Step 1: next = curr->next (save)
Step 2: curr->next = prev (reverse)
Step 3: prev = curr (move prev)
Step 4: curr = next (move curr)

NULL <- 1    2 -> 3 -> 4 -> NULL
        ↑    ↑    ↑
       prev curr next

... continue until curr is NULL
*/
ListNode* reverseListIterative(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    
    while (curr) {
        ListNode* next = curr->next;  // Save
        curr->next = prev;            // Reverse
        prev = curr;                  // Move prev
        curr = next;                  // Move curr
    }
    
    return prev;
}

// 1.2 RECURSIVE REVERSAL - O(n) time, O(n) space (call stack)
/*
VISUALIZATION:
─────────────
reverse(1 -> 2 -> 3 -> NULL)
    reverse(2 -> 3 -> NULL)
        reverse(3 -> NULL)
            return 3 (base case)
        2->next->next = 2 means 3->next = 2
        2->next = NULL
        return 3
    1->next->next = 1 means 2->next = 1
    1->next = NULL
    return 3

Result: 3 -> 2 -> 1 -> NULL
*/
ListNode* reverseListRecursive(ListNode* head) {
    // Base case: empty or single node
    if (!head || !head->next) return head;
    
    // Reverse the rest
    ListNode* newHead = reverseListRecursive(head->next);
    
    // Current node's next should point back to current
    head->next->next = head;
    head->next = nullptr;
    
    return newHead;
}


/*
================================================================================
PATTERN 2: REVERSE BETWEEN POSITIONS
================================================================================
*/

// 2.1 REVERSE BETWEEN LEFT AND RIGHT (1-indexed)
// LeetCode: 92. Reverse Linked List II
// Time: O(n), Space: O(1)
/*
Example: 1 -> 2 -> 3 -> 4 -> 5, left=2, right=4
Result:  1 -> 4 -> 3 -> 2 -> 5
*/
ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (!head || left == right) return head;
    
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    
    // Move to position before 'left'
    for (int i = 1; i < left; i++) {
        prev = prev->next;
    }
    
    // 'curr' is at position 'left'
    ListNode* curr = prev->next;
    
    // Reverse from left to right (one node at a time)
    for (int i = left; i < right; i++) {
        ListNode* next = curr->next;
        curr->next = next->next;
        next->next = prev->next;
        prev->next = next;
    }
    
    return dummy.next;
}
/*
VISUALIZATION: reverse between 2 and 4
─────────────
dummy -> 1 -> 2 -> 3 -> 4 -> 5
         ↑    ↑    ↑
        prev curr next

Step 1: Move 3 to front of sublist
dummy -> 1 -> 3 -> 2 -> 4 -> 5
         ↑         ↑    ↑
        prev      curr next

Step 2: Move 4 to front of sublist
dummy -> 1 -> 4 -> 3 -> 2 -> 5
         ↑              ↑
        prev           curr
*/


// 2.2 REVERSE FIRST K NODES
ListNode* reverseFirstK(ListNode* head, int k) {
    return reverseBetween(head, 1, k);
}


/*
================================================================================
PATTERN 3: REVERSE IN GROUPS
================================================================================
*/

// 3.1 REVERSE NODES IN K-GROUP
// LeetCode: 25. Reverse Nodes in k-Group (Hard)
// Time: O(n), Space: O(1)
ListNode* reverseKGroup(ListNode* head, int k) {
    // Count total nodes
    int count = 0;
    ListNode* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prevGroupEnd = &dummy;
    
    while (count >= k) {
        ListNode* groupStart = prevGroupEnd->next;
        ListNode* curr = groupStart;
        ListNode* prev = nullptr;
        
        // Reverse k nodes
        for (int i = 0; i < k; i++) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        
        // Connect with previous and next groups
        prevGroupEnd->next = prev;       // prev is new head of group
        groupStart->next = curr;         // groupStart is now at end
        prevGroupEnd = groupStart;       // Move to end of this group
        
        count -= k;
    }
    
    return dummy.next;
}
/*
Example: 1 -> 2 -> 3 -> 4 -> 5, k=3
- Reverse first 3: 3 -> 2 -> 1
- Remaining 4,5 (less than k, don't reverse)
Result: 3 -> 2 -> 1 -> 4 -> 5
*/


// 3.2 SWAP NODES IN PAIRS
// LeetCode: 24. Swap Nodes in Pairs
// Time: O(n), Space: O(1)
ListNode* swapPairs(ListNode* head) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    
    while (prev->next && prev->next->next) {
        ListNode* first = prev->next;
        ListNode* second = prev->next->next;
        
        // Swap
        first->next = second->next;
        second->next = first;
        prev->next = second;
        
        // Move to next pair
        prev = first;
    }
    
    return dummy.next;
}
/*
Example: 1 -> 2 -> 3 -> 4
Result:  2 -> 1 -> 4 -> 3

VISUALIZATION:
dummy -> 1 -> 2 -> 3 -> 4
  ↑      ↑    ↑
 prev  first second

After swap:
dummy -> 2 -> 1 -> 3 -> 4
              ↑    ↑    ↑
             prev first second
*/


// Recursive version
ListNode* swapPairsRecursive(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode* second = head->next;
    head->next = swapPairsRecursive(second->next);
    second->next = head;
    
    return second;
}


// 3.3 REVERSE ALTERNATING K-GROUP
// Reverse first k, skip k, reverse k, skip k, ...
ListNode* reverseAlternateKGroup(ListNode* head, int k) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prevGroupEnd = &dummy;
    bool shouldReverse = true;
    
    while (prevGroupEnd->next) {
        // Count k nodes
        ListNode* curr = prevGroupEnd;
        for (int i = 0; i < k && curr->next; i++) {
            curr = curr->next;
        }
        
        if (shouldReverse) {
            // Reverse k nodes
            ListNode* groupStart = prevGroupEnd->next;
            ListNode* p = groupStart;
            ListNode* prev = nullptr;
            
            for (int i = 0; i < k && p; i++) {
                ListNode* next = p->next;
                p->next = prev;
                prev = p;
                p = next;
            }
            
            prevGroupEnd->next = prev;
            groupStart->next = p;
            prevGroupEnd = groupStart;
        } else {
            // Skip k nodes
            for (int i = 0; i < k && prevGroupEnd->next; i++) {
                prevGroupEnd = prevGroupEnd->next;
            }
        }
        
        shouldReverse = !shouldReverse;
    }
    
    return dummy.next;
}


/*
================================================================================
PATTERN 4: ROTATE LIST
================================================================================
*/

// 4.1 ROTATE LIST RIGHT BY K POSITIONS
// LeetCode: 61. Rotate List
// Time: O(n), Space: O(1)
ListNode* rotateRight(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    
    // Get length and last node
    int len = 1;
    ListNode* tail = head;
    while (tail->next) {
        len++;
        tail = tail->next;
    }
    
    // Optimize k
    k = k % len;
    if (k == 0) return head;
    
    // Find new tail: (len - k - 1)th node from start
    ListNode* newTail = head;
    for (int i = 0; i < len - k - 1; i++) {
        newTail = newTail->next;
    }
    
    // Rotate
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;
    
    return newHead;
}
/*
Example: 1 -> 2 -> 3 -> 4 -> 5, k=2
- Length = 5, k = 2
- New tail at position 5-2-1 = 2 (node 3)
- New head = node 4
Result: 4 -> 5 -> 1 -> 2 -> 3
*/


// 4.2 ROTATE LEFT BY K POSITIONS
ListNode* rotateLeft(ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    
    int len = 1;
    ListNode* tail = head;
    while (tail->next) {
        len++;
        tail = tail->next;
    }
    
    k = k % len;
    if (k == 0) return head;
    
    // For left rotation, new tail is (k-1)th node
    ListNode* newTail = head;
    for (int i = 0; i < k - 1; i++) {
        newTail = newTail->next;
    }
    
    ListNode* newHead = newTail->next;
    newTail->next = nullptr;
    tail->next = head;
    
    return newHead;
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
    cout << "=== Reverse Problems ===\n\n";
    
    // Basic Reversal
    cout << "--- Basic Reversal ---" << endl;
    ListNode* list1 = createList({1, 2, 3, 4, 5});
    cout << "Original: ";
    printList(list1);
    list1 = reverseListIterative(list1);
    cout << "Reversed (iterative): ";
    printList(list1);
    
    ListNode* list2 = createList({1, 2, 3, 4, 5});
    list2 = reverseListRecursive(list2);
    cout << "Reversed (recursive): ";
    printList(list2);
    
    // Reverse Between
    cout << "\n--- Reverse Between ---" << endl;
    ListNode* list3 = createList({1, 2, 3, 4, 5});
    cout << "Original: ";
    printList(list3);
    list3 = reverseBetween(list3, 2, 4);
    cout << "Reverse between 2 and 4: ";
    printList(list3);
    
    // Reverse K-Group
    cout << "\n--- Reverse K-Group ---" << endl;
    ListNode* list4 = createList({1, 2, 3, 4, 5});
    cout << "Original: ";
    printList(list4);
    list4 = reverseKGroup(list4, 3);
    cout << "Reverse in groups of 3: ";
    printList(list4);
    
    // Swap Pairs
    cout << "\n--- Swap Pairs ---" << endl;
    ListNode* list5 = createList({1, 2, 3, 4});
    cout << "Original: ";
    printList(list5);
    list5 = swapPairs(list5);
    cout << "Swap pairs: ";
    printList(list5);
    
    // Rotate Right
    cout << "\n--- Rotate Right ---" << endl;
    ListNode* list6 = createList({1, 2, 3, 4, 5});
    cout << "Original: ";
    printList(list6);
    list6 = rotateRight(list6, 2);
    cout << "Rotate right by 2: ";
    printList(list6);
    
    return 0;
}

/*
================================================================================
                              CHEAT SHEET
================================================================================

BASIC REVERSAL (memorize this!):
────────────────────────────────
ListNode *prev = nullptr, *curr = head;
while (curr) {
    ListNode* next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
}
return prev;

REVERSE BETWEEN:
────────────────────────────────
Move to position before left
For each position from left to right:
    Move next node to front of sublist

REVERSE K-GROUP:
────────────────────────────────
While we have k nodes:
    Reverse k nodes
    Connect groups
    Move to next group

ROTATE:
────────────────────────────────
- Make circular (tail->next = head)
- Find new tail at (len - k) position
- Break circle at new position

================================================================================
*/

