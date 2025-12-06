/*
================================================================================
                      LINKED LIST - OVERVIEW
================================================================================

A linked list is a linear data structure where elements are stored in nodes,
and each node points to the next node in the sequence.

Types:
1. Singly Linked List  - Each node points to next
2. Doubly Linked List  - Each node points to next AND previous
3. Circular Linked List - Last node points back to head

================================================================================
                     TIME COMPLEXITY COMPARISON
================================================================================

┌────────────────────┬──────────────┬──────────────┬──────────────────────────┐
│ Operation          │ Linked List  │ Array        │ Notes                    │
├────────────────────┼──────────────┼──────────────┼──────────────────────────┤
│ Access by index    │ O(n)         │ O(1)         │ Must traverse            │
│ Insert at head     │ O(1)         │ O(n)         │ LL wins!                 │
│ Insert at tail     │ O(n) / O(1)* │ O(1) amort   │ *O(1) with tail pointer  │
│ Insert at middle   │ O(n)         │ O(n)         │ Search + insert          │
│ Delete at head     │ O(1)         │ O(n)         │ LL wins!                 │
│ Delete at tail     │ O(n)         │ O(1)         │ Need to find prev        │
│ Search             │ O(n)         │ O(n) / O(logn)│ Array can use bin search │
│ Space overhead     │ O(n) ptrs    │ O(1)         │ Extra space for pointers │
└────────────────────┴──────────────┴──────────────┴──────────────────────────┘

================================================================================
                          NODE DEFINITION
================================================================================
*/

#include <iostream>
using namespace std;

// SINGLY LINKED LIST NODE
struct ListNode {
    int val;
    ListNode* next;
    
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// DOUBLY LINKED LIST NODE
struct DoublyNode {
    int val;
    DoublyNode* prev;
    DoublyNode* next;
    
    DoublyNode() : val(0), prev(nullptr), next(nullptr) {}
    DoublyNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};

/*
================================================================================
                     PATTERN CLASSIFICATION
================================================================================

1. BASIC OPERATIONS (01_BasicOperations.cpp)
   ─────────────────────────────────────────
   - Insert (head, tail, position)
   - Delete (head, tail, position, value)
   - Search, Length, Print
   
   Keywords: "insert", "delete", "add", "remove"

2. TWO POINTER TECHNIQUES (02_TwoPointerTechniques.cpp) ⭐
   ─────────────────────────────────────────────────────
   - Detect Cycle (Floyd's Algorithm)
   - Find Middle
   - Nth Node from End
   - Find Intersection Point
   - Palindrome Check
   
   Keywords: "cycle", "middle", "nth from end", "intersection"

3. REVERSE PROBLEMS (03_ReverseProblems.cpp) ⭐
   ─────────────────────────────────────────────
   - Reverse Linked List
   - Reverse K Group
   - Reverse Between Positions
   - Reverse in Pairs
   
   Keywords: "reverse", "swap pairs", "rotate"

4. MERGE & SORT (04_MergeSortOperations.cpp)
   ─────────────────────────────────────────────
   - Merge Two Sorted Lists
   - Merge K Sorted Lists
   - Sort Linked List (Merge Sort)
   - Partition List
   
   Keywords: "merge", "sort", "partition"

5. DOUBLY LINKED LIST (05_DoublyLinkedList.cpp)
   ─────────────────────────────────────────────
   - LRU Cache implementation
   - Insert/Delete operations
   - Browser history
   
6. CIRCULAR LINKED LIST (06_CircularLinkedList.cpp)
   ─────────────────────────────────────────────────
   - Round-robin scheduling
   - Josephus problem

================================================================================
                       COMMON PATTERNS & TIPS
================================================================================

1. DUMMY NODE TECHNIQUE
   ─────────────────────
   Use a dummy node before head to simplify edge cases:
   
   ListNode dummy(0);
   dummy.next = head;
   ListNode* prev = &dummy;
   // ... operations ...
   return dummy.next;  // New head

2. TWO POINTERS (Fast & Slow)
   ─────────────────────────
   - Slow moves 1 step, Fast moves 2 steps
   - When fast reaches end, slow is at middle
   - If they meet, there's a cycle
   
   ListNode *slow = head, *fast = head;
   while (fast && fast->next) {
       slow = slow->next;
       fast = fast->next->next;
   }

3. IN-PLACE REVERSAL
   ─────────────────────
   ListNode *prev = nullptr, *curr = head;
   while (curr) {
       ListNode* next = curr->next;
       curr->next = prev;
       prev = curr;
       curr = next;
   }
   return prev;

4. RECURSIVE THINKING
   ─────────────────────
   Many LL problems have elegant recursive solutions:
   
   ListNode* reverse(ListNode* head) {
       if (!head || !head->next) return head;
       ListNode* newHead = reverse(head->next);
       head->next->next = head;
       head->next = nullptr;
       return newHead;
   }

================================================================================
                        UTILITY FUNCTIONS
================================================================================
*/

// Create linked list from vector
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

// Print linked list
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL" << endl;
}

// Get length of linked list
int getLength(ListNode* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

// Free linked list memory
void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Main demo
int main() {
    cout << "=== Linked List Overview ===" << endl << endl;
    
    // Create list: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = createList({1, 2, 3, 4, 5});
    
    cout << "Original List: ";
    printList(head);
    
    cout << "Length: " << getLength(head) << endl;
    
    // Cleanup
    deleteList(head);
    
    return 0;
}

/*
================================================================================
                          PROBLEM INDEX
================================================================================

01_BasicOperations.cpp
  - Insert at Head/Tail/Position
  - Delete at Head/Tail/Position
  - Delete by Value
  - Search Element

02_TwoPointerTechniques.cpp ⭐ (HIGH FREQUENCY)
  - Linked List Cycle (LC 141)
  - Linked List Cycle II - Find Start (LC 142)
  - Middle of Linked List (LC 876)
  - Remove Nth from End (LC 19)
  - Intersection of Two Lists (LC 160)
  - Palindrome Linked List (LC 234)

03_ReverseProblems.cpp ⭐ (HIGH FREQUENCY)
  - Reverse Linked List (LC 206)
  - Reverse Linked List II (LC 92)
  - Reverse Nodes in k-Group (LC 25)
  - Swap Nodes in Pairs (LC 24)
  - Rotate List (LC 61)

04_MergeSortOperations.cpp
  - Merge Two Sorted Lists (LC 21)
  - Merge k Sorted Lists (LC 23)
  - Sort List (LC 148)
  - Partition List (LC 86)
  - Add Two Numbers (LC 2)

05_DoublyLinkedList.cpp
  - Implementation
  - LRU Cache (LC 146)
  - Flatten Multilevel DLL (LC 430)

06_CircularLinkedList.cpp
  - Implementation
  - Josephus Problem

================================================================================
*/

