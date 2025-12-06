/*
================================================================================
                      DOUBLY LINKED LIST
================================================================================

Each node has pointers to both NEXT and PREVIOUS nodes.
Allows O(1) deletion when you have the node reference.

Use Cases:
- LRU Cache (most important!)
- Browser history (back/forward)
- Undo/Redo operations
- Deque implementation

================================================================================
*/

#include <iostream>
#include <unordered_map>
using namespace std;

/*
================================================================================
                         NODE DEFINITION
================================================================================
*/
struct DLLNode {
    int val;
    DLLNode* prev;
    DLLNode* next;
    
    DLLNode() : val(0), prev(nullptr), next(nullptr) {}
    DLLNode(int x) : val(x), prev(nullptr), next(nullptr) {}
};


/*
================================================================================
                    DOUBLY LINKED LIST CLASS
================================================================================
*/
class DoublyLinkedList {
public:
    DLLNode* head;
    DLLNode* tail;
    int size;
    
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // INSERT AT HEAD - O(1)
    void insertHead(int val) {
        DLLNode* node = new DLLNode(val);
        
        if (!head) {
            head = tail = node;
        } else {
            node->next = head;
            head->prev = node;
            head = node;
        }
        size++;
    }
    
    // INSERT AT TAIL - O(1)
    void insertTail(int val) {
        DLLNode* node = new DLLNode(val);
        
        if (!tail) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        size++;
    }
    
    // INSERT AFTER NODE - O(1)
    void insertAfter(DLLNode* node, int val) {
        if (!node) return;
        
        DLLNode* newNode = new DLLNode(val);
        newNode->next = node->next;
        newNode->prev = node;
        
        if (node->next) {
            node->next->prev = newNode;
        } else {
            tail = newNode;  // node was tail
        }
        node->next = newNode;
        size++;
    }
    
    // DELETE NODE - O(1) when you have the node reference!
    void deleteNode(DLLNode* node) {
        if (!node) return;
        
        if (node->prev) {
            node->prev->next = node->next;
        } else {
            head = node->next;  // node was head
        }
        
        if (node->next) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;  // node was tail
        }
        
        delete node;
        size--;
    }
    
    // DELETE HEAD - O(1)
    void deleteHead() {
        deleteNode(head);
    }
    
    // DELETE TAIL - O(1)
    void deleteTail() {
        deleteNode(tail);
    }
    
    // MOVE NODE TO HEAD - O(1)
    void moveToHead(DLLNode* node) {
        if (!node || node == head) return;
        
        // Remove from current position
        if (node->prev) node->prev->next = node->next;
        if (node->next) node->next->prev = node->prev;
        if (node == tail) tail = node->prev;
        
        // Insert at head
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;
    }
    
    // PRINT LIST
    void print() {
        DLLNode* curr = head;
        cout << "NULL <-> ";
        while (curr) {
            cout << curr->val;
            if (curr->next) cout << " <-> ";
            curr = curr->next;
        }
        cout << " <-> NULL" << endl;
    }
    
    // PRINT REVERSE
    void printReverse() {
        DLLNode* curr = tail;
        cout << "NULL <-> ";
        while (curr) {
            cout << curr->val;
            if (curr->prev) cout << " <-> ";
            curr = curr->prev;
        }
        cout << " <-> NULL" << endl;
    }
    
    int getSize() { return size; }
    bool isEmpty() { return size == 0; }
};


/*
================================================================================
              LRU CACHE - Most Important DLL Application! ⭐
================================================================================
LeetCode: 146. LRU Cache

Design:
- HashMap: key → DLLNode* for O(1) lookup
- DLL: Most recently used at HEAD, Least recently used at TAIL
- Get: Move accessed node to head
- Put: Add new node at head, evict tail if capacity exceeded

Time: O(1) for both get and put
Space: O(capacity)
*/
class LRUCache {
private:
    int capacity;
    unordered_map<int, DLLNode*> cache;  // key → node
    DLLNode* head;  // Dummy head
    DLLNode* tail;  // Dummy tail
    
    // Add node right after head
    void addToHead(DLLNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    // Remove a node from list
    void removeNode(DLLNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    // Move existing node to head (mark as recently used)
    void moveToHead(DLLNode* node) {
        removeNode(node);
        addToHead(node);
    }
    
    // Remove tail node (least recently used)
    DLLNode* removeTail() {
        DLLNode* lru = tail->prev;
        removeNode(lru);
        return lru;
    }
    
public:
    // Extended node to store key-value
    struct CacheNode : DLLNode {
        int key;
        CacheNode(int k, int v) : DLLNode(v), key(k) {}
    };
    
    LRUCache(int cap) : capacity(cap) {
        head = new DLLNode();
        tail = new DLLNode();
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        }
        
        DLLNode* node = cache[key];
        moveToHead(node);  // Mark as recently used
        return node->val;
    }
    
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Update existing
            DLLNode* node = cache[key];
            node->val = value;
            moveToHead(node);
        } else {
            // Add new
            CacheNode* node = new CacheNode(key, value);
            cache[key] = node;
            addToHead(node);
            
            if (cache.size() > capacity) {
                // Evict LRU
                CacheNode* lru = static_cast<CacheNode*>(removeTail());
                cache.erase(lru->key);
                delete lru;
            }
        }
    }
};

/*
VISUALIZATION:
─────────────
capacity = 3

put(1, 1): [1]
put(2, 2): [2, 1]
put(3, 3): [3, 2, 1]
get(1):    [1, 3, 2]  (move 1 to front)
put(4, 4): [4, 1, 3]  (evict 2, add 4)
get(2):    -1         (was evicted)

           HEAD <-> 4 <-> 1 <-> 3 <-> TAIL
            ↑                          ↑
        most recent              least recent
*/


/*
================================================================================
             FLATTEN MULTILEVEL DOUBLY LINKED LIST
================================================================================
LeetCode: 430. Flatten a Multilevel Doubly Linked List

Some nodes have a 'child' pointer to another doubly linked list.
Flatten all levels into a single-level doubly linked list.
*/
struct MultiNode {
    int val;
    MultiNode* prev;
    MultiNode* next;
    MultiNode* child;
    MultiNode(int x) : val(x), prev(nullptr), next(nullptr), child(nullptr) {}
};

MultiNode* flatten(MultiNode* head) {
    if (!head) return head;
    
    MultiNode* curr = head;
    
    while (curr) {
        if (curr->child) {
            MultiNode* next = curr->next;
            MultiNode* child = curr->child;
            
            // Connect curr to child
            curr->next = child;
            child->prev = curr;
            curr->child = nullptr;
            
            // Find end of child list
            MultiNode* childEnd = child;
            while (childEnd->next) {
                childEnd = childEnd->next;
            }
            
            // Connect child end to next
            childEnd->next = next;
            if (next) next->prev = childEnd;
        }
        
        curr = curr->next;
    }
    
    return head;
}


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Doubly Linked List ===\n\n";
    
    // Basic DLL operations
    cout << "--- Basic Operations ---" << endl;
    DoublyLinkedList dll;
    dll.insertTail(1);
    dll.insertTail(2);
    dll.insertTail(3);
    dll.insertHead(0);
    cout << "List: ";
    dll.print();
    cout << "Reverse: ";
    dll.printReverse();
    
    dll.deleteHead();
    cout << "After delete head: ";
    dll.print();
    
    dll.deleteTail();
    cout << "After delete tail: ";
    dll.print();
    
    // LRU Cache demo
    cout << "\n--- LRU Cache Demo ---" << endl;
    LRUCache cache(2);
    
    cache.put(1, 1);
    cout << "put(1, 1)" << endl;
    
    cache.put(2, 2);
    cout << "put(2, 2)" << endl;
    
    cout << "get(1): " << cache.get(1) << endl;  // returns 1
    
    cache.put(3, 3);  // evicts key 2
    cout << "put(3, 3) - evicts 2" << endl;
    
    cout << "get(2): " << cache.get(2) << endl;  // returns -1 (not found)
    
    cache.put(4, 4);  // evicts key 1
    cout << "put(4, 4) - evicts 1" << endl;
    
    cout << "get(1): " << cache.get(1) << endl;  // returns -1 (not found)
    cout << "get(3): " << cache.get(3) << endl;  // returns 3
    cout << "get(4): " << cache.get(4) << endl;  // returns 4
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

ADVANTAGES OF DOUBLY LINKED LIST:
1. O(1) deletion when you have node reference (vs O(n) in singly LL)
2. Bidirectional traversal
3. O(1) insert before a given node

DISADVANTAGES:
1. Extra space for prev pointer
2. More complex to maintain

KEY APPLICATIONS:
1. LRU Cache - HashMap + DLL
2. Browser history - Back/Forward navigation
3. Undo/Redo - Maintain operation history
4. Deque - Double-ended queue

DUMMY NODES TIP:
Use dummy head and tail to simplify edge cases:
    head <-> node1 <-> node2 <-> ... <-> tail
This way, actual first node is head->next and last is tail->prev

================================================================================
*/

