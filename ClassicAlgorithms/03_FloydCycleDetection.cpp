/*
================================================================================
                    FLOYD'S CYCLE DETECTION (Tortoise and Hare)
================================================================================

PROBLEM: Detect if a linked list has a cycle, and find cycle start point.

KEY INSIGHT: Use two pointers moving at different speeds:
  - Slow (tortoise): moves 1 step at a time
  - Fast (hare): moves 2 steps at a time

If there's a cycle, they WILL meet inside the cycle.

ALGORITHM:
1. Phase 1 - Detect cycle: Move slow by 1, fast by 2 until they meet
2. Phase 2 - Find start: Reset slow to head, move both by 1 until they meet

TIME:  O(n)
SPACE: O(1)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// ═══════════════════════════════════════════════════════════════════════════
// DETECT CYCLE (LC 141)
// ═══════════════════════════════════════════════════════════════════════════

bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            return true;  // Cycle detected
        }
    }
    
    return false;  // Fast reached end, no cycle
}

// ═══════════════════════════════════════════════════════════════════════════
// FIND CYCLE START (LC 142)
// ═══════════════════════════════════════════════════════════════════════════

ListNode* detectCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Phase 1: Find meeting point inside cycle
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            // Phase 2: Find cycle start
            // Reset slow to head, move both by 1
            slow = head;
            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }
            return slow;  // Cycle start node
        }
    }
    
    return nullptr;  // No cycle
}

// ═══════════════════════════════════════════════════════════════════════════
// FIND DUPLICATE NUMBER (LC 287) - Array as implicit linked list
// ═══════════════════════════════════════════════════════════════════════════

int findDuplicate(vector<int>& nums) {
    // Treat array as linked list: index → nums[index]
    // nums = [1,3,4,2,2] means: 0→1→3→2→4→2→4→2... (cycle!)
    
    int slow = nums[0];
    int fast = nums[0];
    
    // Phase 1: Find meeting point
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while (slow != fast);
    
    // Phase 2: Find cycle start (the duplicate)
    slow = nums[0];
    while (slow != fast) {
        slow = nums[slow];
        fast = nums[fast];
    }
    
    return slow;
}

// ═══════════════════════════════════════════════════════════════════════════
// FIND CYCLE LENGTH
// ═══════════════════════════════════════════════════════════════════════════

int cycleLength(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    
    // Find meeting point
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

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test Find Duplicate
    vector<int> nums = {1, 3, 4, 2, 2};
    cout << "Array: [1,3,4,2,2]\n";
    cout << "Duplicate: " << findDuplicate(nums) << "\n\n";
    
    // Create linked list with cycle for testing
    // 1 → 2 → 3 → 4 → 5
    //         ↑       ↓
    //         └───────┘
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);
    head->next->next->next->next = new ListNode(5);
    head->next->next->next->next->next = head->next->next;  // Cycle to node 3
    
    cout << "Linked list: 1→2→3→4→5→(back to 3)\n";
    cout << "Has cycle: " << (hasCycle(head) ? "Yes" : "No") << "\n";
    
    ListNode* cycleStart = detectCycle(head);
    cout << "Cycle starts at node with value: " << cycleStart->val << "\n";
    cout << "Cycle length: " << cycleLength(head) << "\n";
    
    return 0;
}

/*
================================================================================
                         WHY PHASE 2 WORKS
================================================================================

Let:
  - L = distance from head to cycle start
  - C = cycle length
  - K = distance from cycle start to meeting point

When slow and fast meet:
  - Slow traveled: L + K
  - Fast traveled: L + K + nC (n full cycles)

Since fast travels 2x slow:
  2(L + K) = L + K + nC
  L + K = nC
  L = nC - K
  L = (n-1)C + (C - K)

This means: distance from HEAD to cycle start (L)
          = distance from MEETING POINT to cycle start (C - K) + some full cycles

So if we reset one pointer to head and move both by 1,
they meet exactly at cycle start!

RELATED PROBLEMS:
- LC 141: Linked List Cycle
- LC 142: Linked List Cycle II
- LC 287: Find the Duplicate Number
- LC 202: Happy Number (cycle in number transformation)

================================================================================
*/

