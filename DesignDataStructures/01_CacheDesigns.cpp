/*
================================================================================
                    DESIGN - CACHE IMPLEMENTATIONS
================================================================================

Caches require O(1) access AND ordering for eviction policy.
Key insight: HashMap + Doubly Linked List

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: LRU Cache (LeetCode 146) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────
Implement Least Recently Used cache with O(1) get and put.

Design:
- HashMap: key → Node* for O(1) access
- Doubly Linked List: maintains usage order (MRU at head, LRU at tail)

Time: O(1) for both operations | Space: O(capacity)
*/
class LRUCache {
    struct Node {
        int key, val;
        Node *prev, *next;
        Node(int k, int v) : key(k), val(v), prev(nullptr), next(nullptr) {}
    };
    
    int capacity;
    unordered_map<int, Node*> cache;
    Node *head, *tail;  // Dummy nodes
    
    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }
    
    Node* removeTail() {
        Node* lru = tail->prev;
        removeNode(lru);
        return lru;
    }
    
public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) return -1;
        
        Node* node = cache[key];
        moveToHead(node);  // Mark as recently used
        return node->val;
    }
    
    void put(int key, int value) {
        if (cache.count(key)) {
            Node* node = cache[key];
            node->val = value;
            moveToHead(node);
        } else {
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToHead(newNode);
            
            if (cache.size() > capacity) {
                Node* lru = removeTail();
                cache.erase(lru->key);
                delete lru;
            }
        }
    }
};


/*
PROBLEM 2: LFU Cache (LeetCode 460) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────
Implement Least Frequently Used cache with O(1) operations.

Design:
- HashMap: key → {value, freq}
- HashMap: freq → list of keys (in LRU order)
- Track minFreq

Time: O(1) for both operations | Space: O(capacity)
*/
class LFUCache {
    int capacity, minFreq;
    unordered_map<int, pair<int, int>> keyToValFreq;  // key → {value, freq}
    unordered_map<int, list<int>> freqToKeys;         // freq → list of keys
    unordered_map<int, list<int>::iterator> keyToIter; // key → iterator in freq list
    
    void updateFreq(int key) {
        int freq = keyToValFreq[key].second;
        
        // Remove from current frequency list
        freqToKeys[freq].erase(keyToIter[key]);
        
        if (freqToKeys[freq].empty()) {
            freqToKeys.erase(freq);
            if (minFreq == freq) minFreq++;
        }
        
        // Add to next frequency list
        freq++;
        keyToValFreq[key].second = freq;
        freqToKeys[freq].push_front(key);
        keyToIter[key] = freqToKeys[freq].begin();
    }
    
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}
    
    int get(int key) {
        if (!keyToValFreq.count(key)) return -1;
        
        updateFreq(key);
        return keyToValFreq[key].first;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        
        if (keyToValFreq.count(key)) {
            keyToValFreq[key].first = value;
            updateFreq(key);
        } else {
            if (keyToValFreq.size() >= capacity) {
                // Evict LFU (and LRU among ties)
                int evictKey = freqToKeys[minFreq].back();
                freqToKeys[minFreq].pop_back();
                if (freqToKeys[minFreq].empty()) {
                    freqToKeys.erase(minFreq);
                }
                keyToValFreq.erase(evictKey);
                keyToIter.erase(evictKey);
            }
            
            // Insert new key with freq = 1
            keyToValFreq[key] = {value, 1};
            freqToKeys[1].push_front(key);
            keyToIter[key] = freqToKeys[1].begin();
            minFreq = 1;
        }
    }
};


/*
PROBLEM 3: LRU Cache with TTL (Time To Live)
────────────────────────────────────────────
Extension: entries expire after TTL seconds.

Design: Add timestamp to each entry, check on access.
*/
class LRUCacheWithTTL {
    struct Node {
        int key, val;
        long long expireTime;
        Node *prev, *next;
        Node(int k, int v, long long t) : key(k), val(v), expireTime(t), prev(nullptr), next(nullptr) {}
    };
    
    int capacity, ttlSeconds;
    unordered_map<int, Node*> cache;
    Node *head, *tail;
    
    long long getCurrentTime() {
        return chrono::duration_cast<chrono::seconds>(
            chrono::system_clock::now().time_since_epoch()).count();
    }
    
    void addToHead(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    
    void evictExpired() {
        long long now = getCurrentTime();
        Node* curr = tail->prev;
        while (curr != head && curr->expireTime <= now) {
            Node* prev = curr->prev;
            cache.erase(curr->key);
            removeNode(curr);
            delete curr;
            curr = prev;
        }
    }
    
public:
    LRUCacheWithTTL(int capacity, int ttlSeconds) 
        : capacity(capacity), ttlSeconds(ttlSeconds) {
        head = new Node(0, 0, 0);
        tail = new Node(0, 0, 0);
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        evictExpired();
        
        if (!cache.count(key)) return -1;
        
        Node* node = cache[key];
        if (node->expireTime <= getCurrentTime()) {
            cache.erase(key);
            removeNode(node);
            delete node;
            return -1;
        }
        
        removeNode(node);
        addToHead(node);
        return node->val;
    }
    
    void put(int key, int value) {
        evictExpired();
        long long expireTime = getCurrentTime() + ttlSeconds;
        
        if (cache.count(key)) {
            Node* node = cache[key];
            node->val = value;
            node->expireTime = expireTime;
            removeNode(node);
            addToHead(node);
        } else {
            if (cache.size() >= capacity) {
                Node* lru = tail->prev;
                cache.erase(lru->key);
                removeNode(lru);
                delete lru;
            }
            
            Node* newNode = new Node(key, value, expireTime);
            cache[key] = newNode;
            addToHead(newNode);
        }
    }
};


/*
PROBLEM 4: All O(1) Data Structure (LeetCode 432)
─────────────────────────────────────────────────
Support inc(key), dec(key), getMaxKey(), getMinKey() all in O(1).

Design: Doubly linked list of frequency buckets, each bucket has set of keys.
*/
class AllOne {
    struct Bucket {
        int count;
        unordered_set<string> keys;
        Bucket *prev, *next;
        Bucket(int c) : count(c), prev(nullptr), next(nullptr) {}
    };
    
    unordered_map<string, Bucket*> keyToBucket;
    Bucket *head, *tail;  // Dummy nodes
    
    Bucket* addBucketAfter(Bucket* prevBucket, int count) {
        Bucket* newBucket = new Bucket(count);
        newBucket->prev = prevBucket;
        newBucket->next = prevBucket->next;
        prevBucket->next->prev = newBucket;
        prevBucket->next = newBucket;
        return newBucket;
    }
    
    void removeBucket(Bucket* bucket) {
        bucket->prev->next = bucket->next;
        bucket->next->prev = bucket->prev;
        delete bucket;
    }
    
public:
    AllOne() {
        head = new Bucket(0);
        tail = new Bucket(INT_MAX);
        head->next = tail;
        tail->prev = head;
    }
    
    void inc(string key) {
        if (!keyToBucket.count(key)) {
            // New key with count 1
            if (head->next->count != 1) {
                addBucketAfter(head, 1);
            }
            head->next->keys.insert(key);
            keyToBucket[key] = head->next;
        } else {
            Bucket* curr = keyToBucket[key];
            int newCount = curr->count + 1;
            
            // Move to next bucket
            if (curr->next->count != newCount) {
                addBucketAfter(curr, newCount);
            }
            curr->next->keys.insert(key);
            keyToBucket[key] = curr->next;
            
            // Remove from current bucket
            curr->keys.erase(key);
            if (curr->keys.empty()) removeBucket(curr);
        }
    }
    
    void dec(string key) {
        if (!keyToBucket.count(key)) return;
        
        Bucket* curr = keyToBucket[key];
        int newCount = curr->count - 1;
        
        if (newCount == 0) {
            keyToBucket.erase(key);
        } else {
            if (curr->prev->count != newCount) {
                addBucketAfter(curr->prev, newCount);
            }
            curr->prev->keys.insert(key);
            keyToBucket[key] = curr->prev;
        }
        
        curr->keys.erase(key);
        if (curr->keys.empty()) removeBucket(curr);
    }
    
    string getMaxKey() {
        if (tail->prev == head) return "";
        return *tail->prev->keys.begin();
    }
    
    string getMinKey() {
        if (head->next == tail) return "";
        return *head->next->keys.begin();
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Cache Designs ===\n\n";
    
    // 1. LRU Cache
    LRUCache lru(2);
    lru.put(1, 1);
    lru.put(2, 2);
    cout << "1. LRU get(1): " << lru.get(1) << "\n";
    lru.put(3, 3);  // Evicts key 2
    cout << "   LRU get(2): " << lru.get(2) << " (evicted)\n";
    
    // 2. LFU Cache
    LFUCache lfu(2);
    lfu.put(1, 1);
    lfu.put(2, 2);
    cout << "2. LFU get(1): " << lfu.get(1) << "\n";
    lfu.put(3, 3);  // Evicts key 2 (least frequently used)
    cout << "   LFU get(2): " << lfu.get(2) << " (evicted)\n";
    
    // 4. All O(1)
    AllOne allOne;
    allOne.inc("hello");
    allOne.inc("hello");
    cout << "4. Max key: " << allOne.getMaxKey() << "\n";
    cout << "   Min key: " << allOne.getMinKey() << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Design                        | Data Structures Used                           |
+───────────────────────────────+────────────────────────────────────────────────+
| LRU Cache                     | HashMap + Doubly Linked List                   |
| LFU Cache                     | 2 HashMaps + Linked List per frequency         |
| LRU with TTL                  | LRU + timestamp per entry                      |
| All O(1)                      | HashMap + DLL of count buckets                 |
+───────────────────────────────+────────────────────────────────────────────────+

KEY INSIGHT: HashMap gives O(1) access, Linked List gives O(1) ordering updates.

================================================================================
*/

