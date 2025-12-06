/*
================================================================================
                    LINKED LIST - BASIC OPERATIONS
================================================================================

All fundamental operations on singly linked list.

Pattern 1: Insert Operations
Pattern 2: Delete Operations
Pattern 3: Search & Get Operations
Pattern 4: Utility Operations

================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

// Node Definition
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/*
================================================================================
PATTERN 1: INSERT OPERATIONS
================================================================================
*/

// 1.1 INSERT AT HEAD - O(1)
ListNode* insertAtHead(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    newNode->next = head;
    return newNode;
}
// 1 -> 2 -> 3, insert 0 at head → 0 -> 1 -> 2 -> 3

// 1.2 INSERT AT TAIL - O(n)
ListNode* insertAtTail(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    
    if (!head) return newNode;
    
    ListNode* curr = head;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = newNode;
    return head;
}
// 1 -> 2 -> 3, insert 4 at tail → 1 -> 2 -> 3 -> 4

// 1.3 INSERT AT POSITION (0-indexed) - O(n)
ListNode* insertAtPosition(ListNode* head, int val, int pos) {
    if (pos == 0) return insertAtHead(head, val);
    
    ListNode* newNode = new ListNode(val);
    ListNode* curr = head;
    
    // Move to position (pos - 1)
    for (int i = 0; i < pos - 1 && curr; i++) {
        curr = curr->next;
    }
    
    if (!curr) return head;  // Invalid position
    
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}
// 1 -> 2 -> 4, insert 3 at pos 2 → 1 -> 2 -> 3 -> 4

// 1.4 INSERT IN SORTED LIST - O(n)
ListNode* insertSorted(ListNode* head, int val) {
    ListNode* newNode = new ListNode(val);
    
    // Insert at beginning
    if (!head || val < head->val) {
        newNode->next = head;
        return newNode;
    }
    
    // Find position to insert
    ListNode* curr = head;
    while (curr->next && curr->next->val < val) {
        curr = curr->next;
    }
    
    newNode->next = curr->next;
    curr->next = newNode;
    return head;
}
// 1 -> 3 -> 5, insert 4 → 1 -> 3 -> 4 -> 5


/*
================================================================================
PATTERN 2: DELETE OPERATIONS
================================================================================
*/

// 2.1 DELETE HEAD - O(1)
ListNode* deleteHead(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* newHead = head->next;
    delete head;
    return newHead;
}
// 1 -> 2 -> 3 → 2 -> 3

// 2.2 DELETE TAIL - O(n)
ListNode* deleteTail(ListNode* head) {
    if (!head || !head->next) {
        delete head;
        return nullptr;
    }
    
    ListNode* curr = head;
    while (curr->next->next) {
        curr = curr->next;
    }
    
    delete curr->next;
    curr->next = nullptr;
    return head;
}
// 1 -> 2 -> 3 → 1 -> 2

// 2.3 DELETE AT POSITION (0-indexed) - O(n)
ListNode* deleteAtPosition(ListNode* head, int pos) {
    if (!head) return nullptr;
    if (pos == 0) return deleteHead(head);
    
    ListNode* curr = head;
    for (int i = 0; i < pos - 1 && curr->next; i++) {
        curr = curr->next;
    }
    
    if (!curr->next) return head;  // Invalid position
    
    ListNode* toDelete = curr->next;
    curr->next = toDelete->next;
    delete toDelete;
    return head;
}
// 1 -> 2 -> 3 -> 4, delete pos 2 → 1 -> 2 -> 4

// 2.4 DELETE BY VALUE (first occurrence) - O(n)
// LeetCode: 203. Remove Linked List Elements (modified)
ListNode* deleteByValue(ListNode* head, int val) {
    // Handle head nodes with matching value
    while (head && head->val == val) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
    
    if (!head) return nullptr;
    
    ListNode* curr = head;
    while (curr->next) {
        if (curr->next->val == val) {
            ListNode* toDelete = curr->next;
            curr->next = toDelete->next;
            delete toDelete;
            return head;  // Remove first occurrence only
        }
        curr = curr->next;
    }
    
    return head;
}

// 2.5 DELETE ALL OCCURRENCES - O(n)
// LeetCode: 203. Remove Linked List Elements
ListNode* removeElements(ListNode* head, int val) {
    // Use dummy node to handle head deletion
    ListNode dummy(0);
    dummy.next = head;
    ListNode* curr = &dummy;
    
    while (curr->next) {
        if (curr->next->val == val) {
            ListNode* toDelete = curr->next;
            curr->next = toDelete->next;
            delete toDelete;
        } else {
            curr = curr->next;
        }
    }
    
    return dummy.next;
}
// 1 -> 2 -> 6 -> 3 -> 6, remove 6 → 1 -> 2 -> 3

// 2.6 REMOVE DUPLICATES FROM SORTED LIST - O(n)
// LeetCode: 83. Remove Duplicates from Sorted List
ListNode* deleteDuplicates(ListNode* head) {
    ListNode* curr = head;
    
    while (curr && curr->next) {
        if (curr->val == curr->next->val) {
            ListNode* toDelete = curr->next;
            curr->next = toDelete->next;
            delete toDelete;
        } else {
            curr = curr->next;
        }
    }
    
    return head;
}
// 1 -> 1 -> 2 -> 3 -> 3 → 1 -> 2 -> 3

// 2.7 REMOVE ALL DUPLICATES (keep none) - O(n)
// LeetCode: 82. Remove Duplicates from Sorted List II
ListNode* deleteDuplicatesII(ListNode* head) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* prev = &dummy;
    
    while (head) {
        // Check if current node has duplicates
        if (head->next && head->val == head->next->val) {
            // Skip all nodes with same value
            while (head->next && head->val == head->next->val) {
                head = head->next;
            }
            // Skip the last duplicate too
            prev->next = head->next;
        } else {
            prev = prev->next;
        }
        head = head->next;
    }
    
    return dummy.next;
}
// 1 -> 2 -> 3 -> 3 -> 4 -> 4 -> 5 → 1 -> 2 -> 5


/*
================================================================================
PATTERN 3: SEARCH & GET OPERATIONS
================================================================================
*/

// 3.1 SEARCH ELEMENT - O(n)
bool search(ListNode* head, int val) {
    while (head) {
        if (head->val == val) return true;
        head = head->next;
    }
    return false;
}

// 3.2 GET ELEMENT AT INDEX - O(n)
int getAtIndex(ListNode* head, int index) {
    int i = 0;
    while (head) {
        if (i == index) return head->val;
        head = head->next;
        i++;
    }
    return -1;  // Invalid index
}

// 3.3 GET LENGTH - O(n)
int getLength(ListNode* head) {
    int len = 0;
    while (head) {
        len++;
        head = head->next;
    }
    return len;
}

// 3.4 GET LAST NODE - O(n)
ListNode* getLastNode(ListNode* head) {
    if (!head) return nullptr;
    while (head->next) {
        head = head->next;
    }
    return head;
}


/*
================================================================================
PATTERN 4: UTILITY OPERATIONS
================================================================================
*/

// 4.1 PRINT LIST
void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << " -> NULL" << endl;
}

// 4.2 CREATE LIST FROM ARRAY
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

// 4.3 CONVERT LIST TO VECTOR
vector<int> listToVector(ListNode* head) {
    vector<int> result;
    while (head) {
        result.push_back(head->val);
        head = head->next;
    }
    return result;
}

// 4.4 COPY LIST (Deep Copy)
ListNode* copyList(ListNode* head) {
    if (!head) return nullptr;
    
    ListNode* newHead = new ListNode(head->val);
    ListNode* curr = newHead;
    head = head->next;
    
    while (head) {
        curr->next = new ListNode(head->val);
        curr = curr->next;
        head = head->next;
    }
    
    return newHead;
}

// 4.5 FREE LIST MEMORY
void deleteList(ListNode* head) {
    while (head) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Linked List Basic Operations ===\n\n";
    
    // Create initial list: 1 -> 2 -> 3 -> 4 -> 5
    ListNode* head = createList({1, 2, 3, 4, 5});
    cout << "Initial List: ";
    printList(head);
    
    // Insert operations
    cout << "\n--- Insert Operations ---" << endl;
    head = insertAtHead(head, 0);
    cout << "After insertAtHead(0): ";
    printList(head);
    
    head = insertAtTail(head, 6);
    cout << "After insertAtTail(6): ";
    printList(head);
    
    head = insertAtPosition(head, 99, 3);
    cout << "After insertAtPosition(99, 3): ";
    printList(head);
    
    // Delete operations
    cout << "\n--- Delete Operations ---" << endl;
    head = deleteHead(head);
    cout << "After deleteHead(): ";
    printList(head);
    
    head = deleteTail(head);
    cout << "After deleteTail(): ";
    printList(head);
    
    head = deleteAtPosition(head, 2);
    cout << "After deleteAtPosition(2): ";
    printList(head);
    
    // Search
    cout << "\n--- Search Operations ---" << endl;
    cout << "Search(3): " << (search(head, 3) ? "Found" : "Not Found") << endl;
    cout << "Search(100): " << (search(head, 100) ? "Found" : "Not Found") << endl;
    cout << "Length: " << getLength(head) << endl;
    
    // Remove duplicates demo
    cout << "\n--- Remove Duplicates ---" << endl;
    ListNode* dupList = createList({1, 1, 2, 3, 3, 3, 4});
    cout << "Before: ";
    printList(dupList);
    dupList = deleteDuplicates(dupList);
    cout << "After deleteDuplicates: ";
    printList(dupList);
    
    // Cleanup
    deleteList(head);
    deleteList(dupList);
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

┌─────────────────────┬────────────────┬───────────────────────────────────────┐
│ Operation           │ Time           │ Key Technique                         │
├─────────────────────┼────────────────┼───────────────────────────────────────┤
│ Insert at head      │ O(1)           │ newNode->next = head; head = newNode  │
│ Insert at tail      │ O(n)           │ Traverse to end, curr->next = newNode │
│ Insert at position  │ O(n)           │ Traverse to pos-1, insert after       │
│ Delete head         │ O(1)           │ head = head->next                     │
│ Delete tail         │ O(n)           │ Traverse to second-last               │
│ Delete at position  │ O(n)           │ Traverse to pos-1, skip target        │
│ Search              │ O(n)           │ Linear traversal                      │
└─────────────────────┴────────────────┴───────────────────────────────────────┘

DUMMY NODE TIP:
Use dummy node when head might change (deletion/insertion at head)
    ListNode dummy(0);
    dummy.next = head;
    // ... operations ...
    return dummy.next;

================================================================================
*/

