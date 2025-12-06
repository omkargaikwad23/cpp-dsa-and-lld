/*
================================================================================
                LINKED LIST - MERGE & SORT OPERATIONS
================================================================================

Pattern 1: Merge Two Sorted Lists
Pattern 2: Merge K Sorted Lists
Pattern 3: Sort Linked List (Merge Sort)
Pattern 4: Partition List
Pattern 5: Add Numbers

================================================================================
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
================================================================================
PATTERN 1: MERGE TWO SORTED LISTS
================================================================================
LeetCode: 21. Merge Two Sorted Lists
Time: O(m + n), Space: O(1)
*/

// ITERATIVE
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    // Attach remaining nodes
    tail->next = l1 ? l1 : l2;
    
    return dummy.next;
}
/*
Example: l1 = 1 -> 3 -> 5
         l2 = 2 -> 4 -> 6
Result:  1 -> 2 -> 3 -> 4 -> 5 -> 6
*/

// RECURSIVE
ListNode* mergeTwoListsRecursive(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    if (l1->val <= l2->val) {
        l1->next = mergeTwoListsRecursive(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoListsRecursive(l1, l2->next);
        return l2;
    }
}


/*
================================================================================
PATTERN 2: MERGE K SORTED LISTS
================================================================================
LeetCode: 23. Merge k Sorted Lists
*/

// Approach 1: Priority Queue (Min Heap)
// Time: O(N log k) where N = total nodes, k = number of lists
// Space: O(k)
ListNode* mergeKListsHeap(vector<ListNode*>& lists) {
    // Custom comparator for min heap
    auto cmp = [](ListNode* a, ListNode* b) {
        return a->val > b->val;  // Min heap
    };
    
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);
    
    // Add head of each list to heap
    for (ListNode* list : lists) {
        if (list) pq.push(list);
    }
    
    ListNode dummy(0);
    ListNode* tail = &dummy;
    
    while (!pq.empty()) {
        ListNode* smallest = pq.top();
        pq.pop();
        
        tail->next = smallest;
        tail = tail->next;
        
        if (smallest->next) {
            pq.push(smallest->next);
        }
    }
    
    return dummy.next;
}

// Approach 2: Divide and Conquer
// Time: O(N log k), Space: O(log k) for recursion
ListNode* mergeKListsDC(vector<ListNode*>& lists, int left, int right) {
    if (left > right) return nullptr;
    if (left == right) return lists[left];
    
    int mid = left + (right - left) / 2;
    ListNode* l1 = mergeKListsDC(lists, left, mid);
    ListNode* l2 = mergeKListsDC(lists, mid + 1, right);
    
    return mergeTwoLists(l1, l2);
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    return mergeKListsDC(lists, 0, lists.size() - 1);
}


/*
================================================================================
PATTERN 3: SORT LINKED LIST (Merge Sort)
================================================================================
LeetCode: 148. Sort List
Time: O(n log n), Space: O(log n) for recursion
*/
ListNode* sortList(ListNode* head) {
    // Base case: empty or single node
    if (!head || !head->next) return head;
    
    // Find middle (slow ends at first middle for even length)
    ListNode* slow = head;
    ListNode* fast = head->next;  // Start fast one ahead
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // Split into two halves
    ListNode* mid = slow->next;
    slow->next = nullptr;
    
    // Recursively sort both halves
    ListNode* left = sortList(head);
    ListNode* right = sortList(mid);
    
    // Merge sorted halves
    return mergeTwoLists(left, right);
}
/*
Example: 4 -> 2 -> 1 -> 3
- Split: [4, 2] and [1, 3]
- Sort [4, 2]: Split [4] [2] → merge → [2, 4]
- Sort [1, 3]: Split [1] [3] → merge → [1, 3]
- Merge [2,4] and [1,3] → [1, 2, 3, 4]
*/


// Bottom-up Merge Sort (iterative) - O(1) space
ListNode* sortListIterative(ListNode* head) {
    if (!head || !head->next) return head;
    
    // Get length
    int len = 0;
    ListNode* curr = head;
    while (curr) {
        len++;
        curr = curr->next;
    }
    
    ListNode dummy(0);
    dummy.next = head;
    
    // Merge sublists of size 1, 2, 4, 8, ...
    for (int size = 1; size < len; size *= 2) {
        ListNode* prev = &dummy;
        curr = dummy.next;
        
        while (curr) {
            // Get first sublist of 'size'
            ListNode* left = curr;
            for (int i = 1; i < size && curr->next; i++) {
                curr = curr->next;
            }
            
            // Get second sublist of 'size'
            ListNode* right = curr->next;
            curr->next = nullptr;  // End first sublist
            curr = right;
            
            for (int i = 1; i < size && curr; i++) {
                curr = curr->next;
            }
            
            ListNode* next = nullptr;
            if (curr) {
                next = curr->next;
                curr->next = nullptr;  // End second sublist
            }
            
            // Merge and attach
            prev->next = mergeTwoLists(left, right);
            while (prev->next) prev = prev->next;
            
            curr = next;
        }
    }
    
    return dummy.next;
}


/*
================================================================================
PATTERN 4: PARTITION LIST
================================================================================
LeetCode: 86. Partition List
Keep relative order within each partition
Time: O(n), Space: O(1)
*/
ListNode* partition(ListNode* head, int x) {
    // Two dummy heads for two partitions
    ListNode lessHead(0), greaterHead(0);
    ListNode* less = &lessHead;
    ListNode* greater = &greaterHead;
    
    while (head) {
        if (head->val < x) {
            less->next = head;
            less = less->next;
        } else {
            greater->next = head;
            greater = greater->next;
        }
        head = head->next;
    }
    
    // Connect partitions
    greater->next = nullptr;  // Important! Avoid cycle
    less->next = greaterHead.next;
    
    return lessHead.next;
}
/*
Example: 1 -> 4 -> 3 -> 2 -> 5 -> 2, x = 3
- Less than 3: 1 -> 2 -> 2
- Greater or equal: 4 -> 3 -> 5
Result: 1 -> 2 -> 2 -> 4 -> 3 -> 5
*/


/*
================================================================================
PATTERN 5: ADD NUMBERS
================================================================================
*/

// 5.1 ADD TWO NUMBERS (digits in reverse order)
// LeetCode: 2. Add Two Numbers
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* curr = &dummy;
    int carry = 0;
    
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->val;
            l2 = l2->next;
        }
        
        carry = sum / 10;
        curr->next = new ListNode(sum % 10);
        curr = curr->next;
    }
    
    return dummy.next;
}
/*
Example: 342 + 465 = 807
l1: 2 -> 4 -> 3  (represents 342)
l2: 5 -> 6 -> 4  (represents 465)
Result: 7 -> 0 -> 8  (represents 807)
*/


// 5.2 ADD TWO NUMBERS II (digits in normal order)
// LeetCode: 445. Add Two Numbers II
// Use stack to process from right to left
ListNode* addTwoNumbersII(ListNode* l1, ListNode* l2) {
    vector<int> s1, s2;
    
    while (l1) {
        s1.push_back(l1->val);
        l1 = l1->next;
    }
    while (l2) {
        s2.push_back(l2->val);
        l2 = l2->next;
    }
    
    ListNode* head = nullptr;
    int carry = 0;
    
    while (!s1.empty() || !s2.empty() || carry) {
        int sum = carry;
        if (!s1.empty()) {
            sum += s1.back();
            s1.pop_back();
        }
        if (!s2.empty()) {
            sum += s2.back();
            s2.pop_back();
        }
        
        carry = sum / 10;
        ListNode* node = new ListNode(sum % 10);
        node->next = head;  // Prepend
        head = node;
    }
    
    return head;
}


/*
================================================================================
PATTERN 6: INSERTION SORT LIST
================================================================================
LeetCode: 147. Insertion Sort List
Time: O(n²), Space: O(1)
*/
ListNode* insertionSortList(ListNode* head) {
    ListNode dummy(0);
    
    while (head) {
        ListNode* next = head->next;
        
        // Find insertion position
        ListNode* prev = &dummy;
        while (prev->next && prev->next->val < head->val) {
            prev = prev->next;
        }
        
        // Insert
        head->next = prev->next;
        prev->next = head;
        
        head = next;
    }
    
    return dummy.next;
}


/*
================================================================================
PATTERN 7: ODD EVEN LINKED LIST
================================================================================
LeetCode: 328. Odd Even Linked List
Group all odd-indexed nodes followed by even-indexed nodes
Time: O(n), Space: O(1)
*/
ListNode* oddEvenList(ListNode* head) {
    if (!head || !head->next) return head;
    
    ListNode* odd = head;
    ListNode* even = head->next;
    ListNode* evenHead = even;
    
    while (even && even->next) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    
    odd->next = evenHead;
    return head;
}
// 1 -> 2 -> 3 -> 4 -> 5 → 1 -> 3 -> 5 -> 2 -> 4


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
    cout << "=== Merge & Sort Operations ===\n\n";
    
    // Merge Two Lists
    cout << "--- Merge Two Sorted Lists ---" << endl;
    ListNode* l1 = createList({1, 3, 5});
    ListNode* l2 = createList({2, 4, 6});
    cout << "List 1: ";
    printList(l1);
    cout << "List 2: ";
    printList(l2);
    ListNode* merged = mergeTwoLists(l1, l2);
    cout << "Merged: ";
    printList(merged);
    
    // Sort List
    cout << "\n--- Sort Linked List ---" << endl;
    ListNode* unsorted = createList({4, 2, 1, 3, 5});
    cout << "Unsorted: ";
    printList(unsorted);
    ListNode* sorted = sortList(unsorted);
    cout << "Sorted: ";
    printList(sorted);
    
    // Partition List
    cout << "\n--- Partition List ---" << endl;
    ListNode* partList = createList({1, 4, 3, 2, 5, 2});
    cout << "Original: ";
    printList(partList);
    ListNode* partitioned = partition(partList, 3);
    cout << "Partition by 3: ";
    printList(partitioned);
    
    // Add Two Numbers
    cout << "\n--- Add Two Numbers ---" << endl;
    ListNode* num1 = createList({2, 4, 3});  // 342
    ListNode* num2 = createList({5, 6, 4});  // 465
    cout << "342 + 465 = ";
    ListNode* sum = addTwoNumbers(num1, num2);
    printList(sum);
    
    // Odd Even List
    cout << "\n--- Odd Even List ---" << endl;
    ListNode* oeList = createList({1, 2, 3, 4, 5});
    cout << "Original: ";
    printList(oeList);
    oeList = oddEvenList(oeList);
    cout << "Odd-Even: ";
    printList(oeList);
    
    // Merge K Lists
    cout << "\n--- Merge K Lists ---" << endl;
    vector<ListNode*> lists = {
        createList({1, 4, 7}),
        createList({2, 5, 8}),
        createList({3, 6, 9})
    };
    ListNode* mergedK = mergeKLists(lists);
    cout << "Merged K lists: ";
    printList(mergedK);
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

┌──────────────────────────┬───────────────┬─────────────────────────────────┐
│ Problem                  │ Time          │ Technique                       │
├──────────────────────────┼───────────────┼─────────────────────────────────┤
│ Merge Two Sorted         │ O(m+n)        │ Two pointers, dummy head        │
│ Merge K Sorted           │ O(N log k)    │ Min heap OR divide & conquer    │
│ Sort List                │ O(n log n)    │ Merge sort (find mid, split)    │
│ Partition                │ O(n)          │ Two dummy lists, connect        │
│ Add Numbers              │ O(max(m,n))   │ Carry propagation               │
│ Odd Even                 │ O(n)          │ Separate odd/even, connect      │
└──────────────────────────┴───────────────┴─────────────────────────────────┘

KEY TECHNIQUE: Use dummy head when building new list!

================================================================================
*/

