#include <map>
#include <vector>
#include <string>
using namespace std;

/*
 * MAP STL - Complete Reference for Interviews
 * ============================================
 * 
 * map is a sorted associative container implemented as balanced BST (usually red-black tree).
 * Stores key-value pairs in sorted order by key.
 * 
 * Key Properties:
 * - Keys are unique (no duplicates)
 * - Sorted by key (ascending order by default)
 * - Self-balancing BST: O(log N) time complexity for operations
 * - Slower than unordered_map but maintains order
 * 
 * When to use map vs unordered_map:
 * - Use map: Need sorted order, range queries (lower_bound, upper_bound)
 * - Use unordered_map: Need O(1) average, don't care about order
 */

int main() {
    // ============================================
    // 1. CONSTRUCTORS
    // ============================================
    map<int, string> mp1;                    // Empty map
    map<int, string> mp2{{3, "three"}, {1, "one"}, {2, "two"}};  // Initializer list
    // Note: Elements will be sorted: {1:"one"}, {2:"two"}, {3:"three"}
    
    // ============================================
    // 2. INSERTION METHODS (O(log N))
    // ============================================
    map<int, string> mp;
    
    // Method 1: operator[] - Most commonly used in interviews
    mp[1] = "one";                    // Insert or update: O(log N)
    mp[3] = "three";
    mp[2] = "two";
    // Elements are automatically sorted: {1:"one"}, {2:"two"}, {3:"three"}
    
    // Method 2: insert() - Returns pair<iterator, bool>
    auto result = mp.insert({4, "four"});  // O(log N)
    // result.second is true if inserted, false if key already exists
    
    result = mp.insert({1, "ONE"});  // Won't insert (key exists)
    // result.second will be false, value remains "one"
    
    // Method 3: emplace() - Constructs in place (C++11)
    mp.emplace(5, "five");            // O(log N)
    
    // Method 4: insert with iterator range
    map<int, string> temp{{10, "ten"}, {20, "twenty"}};
    mp.insert(temp.begin(), temp.end());  // O(N log N) where N is range size
    
    // Method 5: insert with hint (for optimization)
    auto hint = mp.find(5);
    mp.insert(hint, {6, "six"});     // O(1) amortized if hint is correct
    
    // ============================================
    // 3. ACCESS METHODS (O(log N))
    // ============================================
    
    // Method 1: operator[] - Creates key if doesn't exist
    string value1 = mp[1];            // O(log N)
    string value2 = mp[99];           // Creates {99, ""} if doesn't exist: O(log N)
    int size = mp.size();             // Size increases if new key created
    
    // Method 2: at() - Throws exception if key doesn't exist
    string value3 = mp.at(2);         // O(log N)
    // string value4 = mp.at(100);    // Would throw std::out_of_range
    
    // Method 3: find() - Returns iterator, end() if not found
    auto it = mp.find(3);             // O(log N)
    if (it != mp.end()) {
        int key = it->first;
        string val = it->second;
    }
    
    it = mp.find(1000);               // Returns mp.end() if not found
    if (it == mp.end()) {
        // Key doesn't exist
    }
    
    // ============================================
    // 4. DELETION METHODS (O(log N))
    // ============================================
    map<int, string> mp3{{1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {5, "e"}};
    
    mp3.erase(2);                     // Erase by key: O(log N)
    
    auto it2 = mp3.find(3);
    if (it2 != mp3.end()) {
        mp3.erase(it2);               // Erase by iterator: O(1) amortized
    }
    
    mp3.erase(mp3.begin(), mp3.find(4));  // Erase range: O(N) where N is range size
    
    mp3.clear();                      // Remove all: O(N)
    int size_after_clear = mp3.size();  // Will be 0
    
    // ============================================
    // 5. CAPACITY METHODS (O(1))
    // ============================================
    map<int, string> mp4{{1, "x"}, {2, "y"}};
    int map_size = mp4.size();        // O(1)
    bool is_empty = mp4.empty();      // O(1)
    size_t max_size = mp4.max_size(); // O(1)
    
    // ============================================
    // 6. LOOKUP METHODS (O(log N))
    // ============================================
    map<int, string> mp5{{1, "one"}, {2, "two"}, {3, "three"}};
    
    // count() - Returns 1 if key exists, 0 otherwise
    int count1 = mp5.count(2);        // Returns 1 (exists): O(log N)
    int count2 = mp5.count(99);       // Returns 0 (doesn't exist): O(log N)
    
    // contains() - C++20 feature (returns bool)
    // bool exists = mp5.contains(2);  // C++20
    
    // ============================================
    // 7. ITERATION METHODS
    // ============================================
    map<int, string> mp6{{3, "c"}, {1, "a"}, {2, "b"}};
    // Note: Iteration will be in sorted order: 1, 2, 3
    
    // Method 1: Range-based for loop (Most common in interviews)
    for (const auto& pair : mp6) {
        int key = pair.first;
        string value = pair.second;
    }
    
    // Method 2: Iterator
    for (auto it = mp6.begin(); it != mp6.end(); ++it) {
        int key = it->first;
        string value = it->second;
    }
    
    // Method 3: Reverse iterator (iterate in descending order)
    for (auto it = mp6.rbegin(); it != mp6.rend(); ++it) {
        int key = it->first;
        string value = it->second;
    }
    
    // Method 4: Structured bindings (C++17)
    for (const auto& [key, value] : mp6) {
        // Use key and value directly
    }
    
    // ============================================
    // 8. BOUND METHODS (Unique to map - Very Important!)
    // ============================================
    map<int, string> mp7{{1, "a"}, {3, "c"}, {5, "e"}, {7, "g"}, {9, "i"}};
    
    // lower_bound(key) - Returns iterator to first element >= key
    auto lb = mp7.lower_bound(5);     // Points to {5, "e"}: O(log N)
    // If key doesn't exist, returns iterator to first element > key
    
    // upper_bound(key) - Returns iterator to first element > key
    auto ub = mp7.upper_bound(5);     // Points to {7, "g"}: O(log N)
    
    // equal_range(key) - Returns pair of iterators [lower_bound, upper_bound)
    auto range = mp7.equal_range(5);   // O(log N)
    // range.first = lower_bound(5), range.second = upper_bound(5)
    
    // Example: Find all elements with key >= 3 and < 7
    auto start = mp7.lower_bound(3);   // {3, "c"}
    auto end = mp7.upper_bound(6);     // {7, "g"}
    for (auto it = start; it != end; ++it) {
        // Process elements: {3, "c"}, {5, "e"}
    }
    
    // ============================================
    // 9. COMMON INTERVIEW PATTERNS
    // ============================================
    
    // Pattern 1: Count frequency (maintains sorted order)
    vector<int> arr = {2, 3, 3, 2, 5, 6, 2};
    map<int, int> freq;
    
    for (int num : arr) {
        freq[num]++;  // O(log N) per operation
    }
    // Result: freq = {2:3, 3:2, 5:1, 6:1} (sorted by key)
    
    // Pattern 2: Check if key exists before accessing
    map<string, int> scores{{"Alice", 95}, {"Bob", 87}};
    
    // Safe way: Use find()
    if (scores.find("Alice") != scores.end()) {
        int alice_score = scores["Alice"];
    }
    
    // Safe way: Use count()
    if (scores.count("Bob") > 0) {
        int bob_score = scores["Bob"];
    }
    
    // Pattern 3: Get first/last element (smallest/largest key)
    map<int, string> mp8{{5, "five"}, {1, "one"}, {9, "nine"}};
    auto first_key = mp8.begin()->first;      // 1 (smallest key)
    auto first_value = mp8.begin()->second;   // "one"
    auto last_key = mp8.rbegin()->first;      // 9 (largest key)
    auto last_value = mp8.rbegin()->second;   // "nine"
    
    // Pattern 4: Range queries (very common in interviews)
    map<int, int> mp9{{1, 10}, {3, 30}, {5, 50}, {7, 70}, {9, 90}};
    
    // Find all keys in range [3, 7]
    auto start_it = mp9.lower_bound(3);  // >= 3
    auto end_it = mp9.upper_bound(7);    // > 7
    for (auto it = start_it; it != end_it; ++it) {
        // Process: {3, 30}, {5, 50}, {7, 70}
    }
    
    // Pattern 5: Custom comparator (descending order)
    map<int, string, greater<int>> descending_map;
    descending_map[3] = "three";
    descending_map[1] = "one";
    descending_map[2] = "two";
    // Elements: {3:"three"}, {2:"two"}, {1:"one"} (descending order)
    
    // ============================================
    // 10. TIME COMPLEXITY SUMMARY
    // ============================================
    /*
     * Operation          | Time Complexity
     * -------------------|----------------
     * operator[]         | O(log N)
     * at()               | O(log N)
     * insert()           | O(log N)
     * emplace()          | O(log N)
     * erase(key)         | O(log N)
     * erase(iterator)    | O(1) amortized
     * find()             | O(log N)
     * count()            | O(log N)
     * lower_bound()      | O(log N)
     * upper_bound()      | O(log N)
     * equal_range()      | O(log N)
     * size()             | O(1)
     * empty()            | O(1)
     * clear()            | O(N)
     * begin()/end()      | O(1)
     * 
     * Note: All operations are O(log N) due to balanced BST structure
     *       N is the number of elements in the map
     */
    
    // ============================================
    // 11. MAP vs UNORDERED_MAP COMPARISON
    // ============================================
    /*
     * Feature              | map              | unordered_map
     * ---------------------|------------------|------------------
     * Implementation      | Balanced BST     | Hash Table
     * Order                | Sorted           | Unordered
     * Insert/Lookup       | O(log N)         | O(1) average
     * Range queries       | Yes (lower_bound) | No
     * Memory overhead      | Lower            | Higher
     * Use when            | Need sorted order| Need fast lookup
     *                      | Range queries    | Don't care order
     */
    
    return 0;
}
