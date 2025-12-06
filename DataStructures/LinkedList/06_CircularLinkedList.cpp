/*
================================================================================
                      CIRCULAR LINKED LIST
================================================================================

Last node points back to the first node (or any other node, creating a cycle).

Types:
1. Circular Singly Linked List - last->next = first
2. Circular Doubly Linked List - last->next = first, first->prev = last

Use Cases:
- Round-robin scheduling
- Circular buffers
- Josephus problem
- Playlist loop (music players)

================================================================================
*/

#include <iostream>
#include <vector>
using namespace std;

/*
================================================================================
                   CIRCULAR SINGLY LINKED LIST
================================================================================
*/
struct CNode {
    int val;
    CNode* next;
    CNode(int x) : val(x), next(nullptr) {}
};

class CircularLinkedList {
public:
    CNode* tail;  // Keep tail pointer (head = tail->next)
    int size;
    
    CircularLinkedList() : tail(nullptr), size(0) {}
    
    CNode* getHead() {
        return tail ? tail->next : nullptr;
    }
    
    // INSERT AT HEAD - O(1)
    void insertHead(int val) {
        CNode* node = new CNode(val);
        
        if (!tail) {
            tail = node;
            node->next = node;  // Points to itself
        } else {
            node->next = tail->next;  // New node points to old head
            tail->next = node;        // Tail points to new head
        }
        size++;
    }
    
    // INSERT AT TAIL - O(1)
    void insertTail(int val) {
        insertHead(val);      // Add at head position
        tail = tail->next;    // Move tail to new node
    }
    
    // DELETE HEAD - O(1)
    void deleteHead() {
        if (!tail) return;
        
        CNode* head = tail->next;
        
        if (head == tail) {
            // Only one node
            tail = nullptr;
        } else {
            tail->next = head->next;
        }
        
        delete head;
        size--;
    }
    
    // DELETE TAIL - O(n) - Need to find second-last
    void deleteTail() {
        if (!tail) return;
        
        CNode* head = tail->next;
        
        if (head == tail) {
            // Only one node
            delete tail;
            tail = nullptr;
        } else {
            // Find second-last node
            CNode* prev = head;
            while (prev->next != tail) {
                prev = prev->next;
            }
            prev->next = head;
            delete tail;
            tail = prev;
        }
        size--;
    }
    
    // DELETE BY VALUE
    void deleteByValue(int val) {
        if (!tail) return;
        
        CNode* head = tail->next;
        
        // Check if head needs to be deleted
        if (head->val == val) {
            deleteHead();
            return;
        }
        
        // Find node before target
        CNode* prev = head;
        while (prev->next != head && prev->next->val != val) {
            prev = prev->next;
        }
        
        if (prev->next != head) {
            CNode* toDelete = prev->next;
            if (toDelete == tail) tail = prev;
            prev->next = toDelete->next;
            delete toDelete;
            size--;
        }
    }
    
    // PRINT LIST
    void print() {
        if (!tail) {
            cout << "Empty" << endl;
            return;
        }
        
        CNode* curr = tail->next;  // Start from head
        do {
            cout << curr->val;
            if (curr->next != tail->next) cout << " -> ";
            curr = curr->next;
        } while (curr != tail->next);
        
        cout << " -> (back to " << tail->next->val << ")" << endl;
    }
    
    int getSize() { return size; }
    bool isEmpty() { return size == 0; }
};


/*
================================================================================
                     JOSEPHUS PROBLEM ⭐
================================================================================

N people stand in a circle. Starting from a given position, every Kth person
is eliminated until only one person remains. Find the position of survivor.

Example: N=7, K=3
Circle: 1 2 3 4 5 6 7 (0-indexed: 0 1 2 3 4 5 6)
Elimination order: 2, 5, 1, 6, 4, 0
Survivor: 3 (0-indexed)
*/

// Approach 1: Simulation with Circular List - O(n*k)
int josephusSimulation(int n, int k) {
    // Build circular list
    CNode* head = new CNode(0);
    CNode* curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = new CNode(i);
        curr = curr->next;
    }
    curr->next = head;  // Make circular
    
    // Elimination
    CNode* prev = curr;  // prev points to last node
    curr = head;
    
    while (curr->next != curr) {  // More than one node
        // Move k-1 steps
        for (int i = 1; i < k; i++) {
            prev = curr;
            curr = curr->next;
        }
        
        // Eliminate curr
        prev->next = curr->next;
        delete curr;
        curr = prev->next;
    }
    
    int survivor = curr->val;
    delete curr;
    return survivor;
}

// Approach 2: Mathematical (Recursive) - O(n)
// J(n, k) = (J(n-1, k) + k) % n, with J(1, k) = 0
int josephusMath(int n, int k) {
    int survivor = 0;  // Base case: J(1, k) = 0
    
    for (int i = 2; i <= n; i++) {
        survivor = (survivor + k) % i;
    }
    
    return survivor;
}
/*
Why does this work?
- After first elimination, we have n-1 people
- But the numbering starts from position k (after eliminated person)
- J(n, k) = (J(n-1, k) + k) % n adjusts for this shift
*/


/*
================================================================================
                    SPLIT CIRCULAR LIST INTO TWO HALVES
================================================================================
*/
pair<CNode*, CNode*> splitCircular(CNode* head) {
    if (!head || head->next == head) {
        return {head, nullptr};  // Can't split single element
    }
    
    // Find middle using slow-fast pointers
    CNode* slow = head;
    CNode* fast = head;
    
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // If even number of nodes, move fast one more
    if (fast->next->next == head) {
        fast = fast->next;
    }
    
    // Split
    CNode* head2 = slow->next;
    slow->next = head;       // End first half
    fast->next = head2;      // End second half
    
    return {head, head2};
}


/*
================================================================================
                    CHECK IF LINKED LIST IS CIRCULAR
================================================================================
*/
bool isCircular(CNode* head) {
    if (!head) return true;  // Empty is considered circular
    
    CNode* curr = head->next;
    while (curr && curr != head) {
        curr = curr->next;
    }
    
    return curr == head;
}


/*
================================================================================
                    CIRCULAR LINKED LIST CYCLE LENGTH
================================================================================
*/
int circularLength(CNode* head) {
    if (!head) return 0;
    
    int count = 1;
    CNode* curr = head->next;
    
    while (curr != head) {
        count++;
        curr = curr->next;
    }
    
    return count;
}


/*
================================================================================
               CIRCULAR DOUBLY LINKED LIST
================================================================================
*/
struct CDLLNode {
    int val;
    CDLLNode* prev;
    CDLLNode* next;
    CDLLNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};

class CircularDoublyLinkedList {
public:
    CDLLNode* head;
    int size;
    
    CircularDoublyLinkedList() : head(nullptr), size(0) {}
    
    void insertHead(int val) {
        CDLLNode* node = new CDLLNode(val);
        
        if (!head) {
            head = node;
            node->next = node;
            node->prev = node;
        } else {
            CDLLNode* tail = head->prev;
            
            node->next = head;
            node->prev = tail;
            tail->next = node;
            head->prev = node;
            head = node;
        }
        size++;
    }
    
    void insertTail(int val) {
        if (!head) {
            insertHead(val);
            return;
        }
        
        CDLLNode* node = new CDLLNode(val);
        CDLLNode* tail = head->prev;
        
        node->next = head;
        node->prev = tail;
        tail->next = node;
        head->prev = node;
        size++;
    }
    
    void deleteNode(CDLLNode* node) {
        if (!node) return;
        
        if (node->next == node) {
            // Only one node
            head = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
            if (node == head) head = node->next;
        }
        
        delete node;
        size--;
    }
    
    void print() {
        if (!head) {
            cout << "Empty" << endl;
            return;
        }
        
        CDLLNode* curr = head;
        cout << "... <-> ";
        do {
            cout << curr->val << " <-> ";
            curr = curr->next;
        } while (curr != head);
        cout << "..." << endl;
    }
};


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Circular Linked List ===\n\n";
    
    // Basic operations
    cout << "--- Basic Operations ---" << endl;
    CircularLinkedList cll;
    cll.insertTail(1);
    cll.insertTail(2);
    cll.insertTail(3);
    cll.insertTail(4);
    cout << "List: ";
    cll.print();
    
    cll.deleteHead();
    cout << "After delete head: ";
    cll.print();
    
    cll.deleteTail();
    cout << "After delete tail: ";
    cll.print();
    
    // Josephus Problem
    cout << "\n--- Josephus Problem ---" << endl;
    int n = 7, k = 3;
    cout << "N=" << n << ", K=" << k << endl;
    cout << "Survivor (simulation): " << josephusSimulation(n, k) << endl;
    cout << "Survivor (math): " << josephusMath(n, k) << endl;
    
    // Different N, K values
    cout << "\nJosephus results:" << endl;
    cout << "J(5, 2) = " << josephusMath(5, 2) << endl;
    cout << "J(10, 3) = " << josephusMath(10, 3) << endl;
    cout << "J(41, 3) = " << josephusMath(41, 3) << " (famous problem!)" << endl;
    
    // Circular Doubly Linked List
    cout << "\n--- Circular Doubly Linked List ---" << endl;
    CircularDoublyLinkedList cdll;
    cdll.insertTail(1);
    cdll.insertTail(2);
    cdll.insertTail(3);
    cdll.insertHead(0);
    cout << "List: ";
    cdll.print();
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

CIRCULAR SINGLY LINKED LIST:
- Keep TAIL pointer (head = tail->next)
- Insert at head/tail: O(1)
- Delete head: O(1)
- Delete tail: O(n) - need to find second-last

CIRCULAR DOUBLY LINKED LIST:
- All operations O(1)
- More memory (two pointers per node)

KEY APPLICATIONS:
1. Round-robin scheduling (CPU scheduling)
2. Circular buffers (streaming data)
3. Josephus problem
4. Playlist repeat/shuffle

JOSEPHUS FORMULA:
J(n, k) = (J(n-1, k) + k) % n
J(1, k) = 0

================================================================================
*/

