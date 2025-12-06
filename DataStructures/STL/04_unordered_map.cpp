#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

/*
 * UNORDERED_MAP STL - Complete Reference for Interviews
 * =====================================================
 * 
 * unordered_map is a hash table-based associative container.
 * Stores key-value pairs with O(1) average time complexity for operations.
 * 
 * Key Properties:
 * - Keys are unique (no duplicates)
 * - Unordered (no specific order)
 * - Fast lookup, insertion, deletion: O(1) average, O(N) worst case
 * - Uses hash function internally
 */

int main() {
    // ============================================
    // 1. CONSTRUCTORS
    // ============================================
    unordered_map<int, string> mp1;                    // Empty map
    unordered_map<int, string> mp2{{1, "one"}, {2, "two"}, {3, "three"}};  // Initializer list
    
    // ============================================
    // 2. INSERTION METHODS (O(1) average)
    // ============================================
    unordered_map<int, string> mp;
    
    // Method 1: operator[] - Most commonly used in interviews
    mp[1] = "one";                    // Insert or update: O(1)
    mp[2] = "two";
    mp[3] = "three";
    
    // Method 2: insert() - Returns pair<iterator, bool>
    auto result = mp.insert({4, "four"});  // O(1)
    // result.second is true if inserted, false if key already exists
    
    result = mp.insert({1, "ONE"});  // Won't insert (key exists)
    // result.second will be false
    
    // Method 3: emplace() - Constructs in place (C++11)
    mp.emplace(5, "five");            // O(1)
    
    // Method 4: insert with iterator range
    unordered_map<int, string> temp{{10, "ten"}, {20, "twenty"}};
    mp.insert(temp.begin(), temp.end());  // O(N) where N is range size
    
    // ============================================
    // 3. ACCESS METHODS (O(1) average)
    // ============================================
    
    // Method 1: operator[] - Creates key if doesn't exist
    string value1 = mp[1];            // O(1)
    string value2 = mp[99];           // Creates {99, ""} if doesn't exist: O(1)
    int size = mp.size();             // Size increases if new key created
    
    // Method 2: at() - Throws exception if key doesn't exist
    string value3 = mp.at(2);         // O(1)
    // string value4 = mp.at(100);    // Would throw std::out_of_range
    
    // Method 3: find() - Returns iterator, end() if not found
    auto it = mp.find(3);             // O(1)
    if (it != mp.end()) {
        int key = it->first;
        string val = it->second;
    }
    
    it = mp.find(1000);               // Returns mp.end() if not found
    if (it == mp.end()) {
        // Key doesn't exist
    }
    
    // ============================================
    // 4. DELETION METHODS (O(1) average)
    // ============================================
    unordered_map<int, string> mp3{{1, "a"}, {2, "b"}, {3, "c"}, {4, "d"}, {5, "e"}};
    
    mp3.erase(2);                     // Erase by key: O(1)
    
    auto it2 = mp3.find(3);
    if (it2 != mp3.end()) {
        mp3.erase(it2);               // Erase by iterator: O(1)
    }
    
    mp3.erase(mp3.begin(), next(mp3.begin(), 2));  // Erase range: O(N)
    
    mp3.clear();                      // Remove all: O(N)
    int size_after_clear = mp3.size();  // Will be 0
    
    // ============================================
    // 5. CAPACITY METHODS (O(1))
    // ============================================
    unordered_map<int, string> mp4{{1, "x"}, {2, "y"}};
    int map_size = mp4.size();        // O(1)
    bool is_empty = mp4.empty();      // O(1)
    size_t max_size = mp4.max_size(); // O(1)
    
    // ============================================
    // 6. LOOKUP METHODS (O(1) average)
    // ============================================
    unordered_map<int, string> mp5{{1, "one"}, {2, "two"}, {3, "three"}};
    
    // count() - Returns 1 if key exists, 0 otherwise
    int count1 = mp5.count(2);        // Returns 1 (exists): O(1)
    int count2 = mp5.count(99);      // Returns 0 (doesn't exist): O(1)
    
    // contains() - C++20 feature (returns bool)
    // bool exists = mp5.contains(2);  // C++20
    
    // ============================================
    // 7. ITERATION METHODS
    // ============================================
    unordered_map<int, string> mp6{{1, "a"}, {2, "b"}, {3, "c"}};
    
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
    
    // Method 3: Structured bindings (C++17)
    for (const auto& [key, value] : mp6) {
        // Use key and value directly
    }
    
    // ============================================
    // 8. COMMON INTERVIEW PATTERNS
    // ============================================
    
    // Pattern 1: Count frequency of elements
    vector<int> arr = {2, 3, 3, 2, 5, 6, 2};
    unordered_map<int, int> freq;
    
    for (int num : arr) {
        freq[num]++;  // O(1) per operation
    }
    // Result: freq[2] = 3, freq[3] = 2, freq[5] = 1, freq[6] = 1
    
    // Pattern 2: Check if key exists before accessing
    unordered_map<string, int> scores{{"Alice", 95}, {"Bob", 87}};
    
    // Safe way: Use find()
    if (scores.find("Alice") != scores.end()) {
        int alice_score = scores["Alice"];
    }
    
    // Safe way: Use count()
    if (scores.count("Bob") > 0) {
        int bob_score = scores["Bob"];
    }
    
    // Pattern 3: Group elements by key
    vector<pair<string, int>> data = {{"A", 1}, {"B", 2}, {"A", 3}, {"B", 4}};
    unordered_map<string, vector<int>> groups;
    
    for (const auto& [key, value] : data) {
        groups[key].push_back(value);  // O(1)
    }
    // Result: groups["A"] = [1, 3], groups["B"] = [2, 4]
    
    // ============================================
    // 9. TIME COMPLEXITY SUMMARY
    // ============================================
    /*
     * Operation          | Average Case | Worst Case
     * -------------------|--------------|------------
     * operator[]         | O(1)         | O(N)
     * at()               | O(1)         | O(N)
     * insert()           | O(1)         | O(N)
     * emplace()          | O(1)         | O(N)
     * erase(key)         | O(1)         | O(N)
     * erase(iterator)    | O(1)         | O(N)
     * find()             | O(1)         | O(N)
     * count()             | O(1)         | O(N)
     * size()              | O(1)         | O(1)
     * empty()             | O(1)         | O(1)
     * clear()             | O(N)         | O(N)
     * 
     * Note: Worst case O(N) occurs due to hash collisions
     *       In practice, average case O(1) is achieved
     */
    
    return 0;
}