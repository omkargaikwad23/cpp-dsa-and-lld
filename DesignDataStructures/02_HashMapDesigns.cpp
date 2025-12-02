/*
================================================================================
                    DESIGN - HASHMAP & RANDOMIZED STRUCTURES
================================================================================

Key patterns:
- HashMap implementation: Array of buckets with chaining
- Random O(1): Array + HashMap (swap with last on delete)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Design HashMap (LeetCode 706)
────────────────────────────────────────
Implement HashMap without built-in hash table libraries.

Design: Array of buckets, each bucket is a list for collision handling.

Time: O(n/k) average, O(n) worst | Space: O(k + n)
*/
class MyHashMap {
    static const int SIZE = 10007;  // Prime number for better distribution
    vector<list<pair<int, int>>> buckets;
    
    int hash(int key) {
        return key % SIZE;
    }
    
public:
    MyHashMap() : buckets(SIZE) {}
    
    void put(int key, int value) {
        int idx = hash(key);
        for (auto& [k, v] : buckets[idx]) {
            if (k == key) {
                v = value;
                return;
            }
        }
        buckets[idx].push_back({key, value});
    }
    
    int get(int key) {
        int idx = hash(key);
        for (auto& [k, v] : buckets[idx]) {
            if (k == key) return v;
        }
        return -1;
    }
    
    void remove(int key) {
        int idx = hash(key);
        buckets[idx].remove_if([key](auto& p) { return p.first == key; });
    }
};


/*
PROBLEM 2: Design HashSet (LeetCode 705)
────────────────────────────────────────
Implement HashSet without built-in hash set libraries.

Time: O(n/k) average | Space: O(k + n)
*/
class MyHashSet {
    static const int SIZE = 10007;
    vector<list<int>> buckets;
    
public:
    MyHashSet() : buckets(SIZE) {}
    
    void add(int key) {
        int idx = key % SIZE;
        for (int k : buckets[idx]) {
            if (k == key) return;
        }
        buckets[idx].push_back(key);
    }
    
    void remove(int key) {
        int idx = key % SIZE;
        buckets[idx].remove(key);
    }
    
    bool contains(int key) {
        int idx = key % SIZE;
        for (int k : buckets[idx]) {
            if (k == key) return true;
        }
        return false;
    }
};


/*
PROBLEM 3: Insert Delete GetRandom O(1) (LeetCode 380) ⭐ GOOGLE FAVORITE
─────────────────────────────────────────────────────────────────────────
Support insert, remove, getRandom all in O(1).

Design: 
- Array to store elements (for random access)
- HashMap: value → index in array
- On delete: swap with last element, then pop

Time: O(1) for all operations | Space: O(n)
*/
class RandomizedSet {
    vector<int> nums;
    unordered_map<int, int> valToIdx;
    
public:
    bool insert(int val) {
        if (valToIdx.count(val)) return false;
        
        valToIdx[val] = nums.size();
        nums.push_back(val);
        return true;
    }
    
    bool remove(int val) {
        if (!valToIdx.count(val)) return false;
        
        int idx = valToIdx[val];
        int lastVal = nums.back();
        
        // Swap with last
        nums[idx] = lastVal;
        valToIdx[lastVal] = idx;
        
        // Remove last
        nums.pop_back();
        valToIdx.erase(val);
        
        return true;
    }
    
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};


/*
PROBLEM 4: Insert Delete GetRandom O(1) - Duplicates Allowed (LeetCode 381)
───────────────────────────────────────────────────────────────────────────
Same as above but allow duplicates.

Design: HashMap: value → set of indices

Time: O(1) average | Space: O(n)
*/
class RandomizedCollection {
    vector<int> nums;
    unordered_map<int, unordered_set<int>> valToIndices;
    
public:
    bool insert(int val) {
        bool notPresent = valToIndices[val].empty();
        valToIndices[val].insert(nums.size());
        nums.push_back(val);
        return notPresent;
    }
    
    bool remove(int val) {
        if (valToIndices[val].empty()) return false;
        
        int idx = *valToIndices[val].begin();
        valToIndices[val].erase(idx);
        
        int lastVal = nums.back();
        
        if (idx != nums.size() - 1) {
            nums[idx] = lastVal;
            valToIndices[lastVal].erase(nums.size() - 1);
            valToIndices[lastVal].insert(idx);
        }
        
        nums.pop_back();
        return true;
    }
    
    int getRandom() {
        return nums[rand() % nums.size()];
    }
};


/*
PROBLEM 5: Design Underground System (LeetCode 1396)
────────────────────────────────────────────────────
Track passenger journeys and calculate average travel times.

Time: O(1) for all operations | Space: O(n)
*/
class UndergroundSystem {
    unordered_map<int, pair<string, int>> checkIns;  // id → {station, time}
    unordered_map<string, pair<long long, int>> journeys;  // route → {totalTime, count}
    
    string getRoute(const string& start, const string& end) {
        return start + "->" + end;
    }
    
public:
    void checkIn(int id, string stationName, int t) {
        checkIns[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) {
        auto& [startStation, startTime] = checkIns[id];
        string route = getRoute(startStation, stationName);
        journeys[route].first += t - startTime;
        journeys[route].second++;
        checkIns.erase(id);
    }
    
    double getAverageTime(string startStation, string endStation) {
        string route = getRoute(startStation, endStation);
        auto& [totalTime, count] = journeys[route];
        return (double)totalTime / count;
    }
};


/*
PROBLEM 6: Design a Number Container System (LeetCode 2349)
───────────────────────────────────────────────────────────
change(index, number): Set container at index to number.
find(number): Return smallest index with this number.

Time: O(log n) | Space: O(n)
*/
class NumberContainers {
    unordered_map<int, int> indexToNum;
    unordered_map<int, set<int>> numToIndices;
    
public:
    void change(int index, int number) {
        if (indexToNum.count(index)) {
            int oldNum = indexToNum[index];
            numToIndices[oldNum].erase(index);
            if (numToIndices[oldNum].empty()) {
                numToIndices.erase(oldNum);
            }
        }
        indexToNum[index] = number;
        numToIndices[number].insert(index);
    }
    
    int find(int number) {
        if (!numToIndices.count(number) || numToIndices[number].empty()) {
            return -1;
        }
        return *numToIndices[number].begin();
    }
};


/*
PROBLEM 7: First Unique Number (LeetCode 1429)
──────────────────────────────────────────────
Queue-like structure that returns first unique number.

Design: LinkedHashSet-like structure (maintains insertion order)
*/
class FirstUnique {
    list<int> uniqueList;
    unordered_map<int, list<int>::iterator> numToIter;
    unordered_set<int> duplicates;
    
public:
    FirstUnique(vector<int>& nums) {
        for (int num : nums) add(num);
    }
    
    int showFirstUnique() {
        return uniqueList.empty() ? -1 : uniqueList.front();
    }
    
    void add(int value) {
        if (duplicates.count(value)) return;
        
        if (numToIter.count(value)) {
            uniqueList.erase(numToIter[value]);
            numToIter.erase(value);
            duplicates.insert(value);
        } else {
            uniqueList.push_back(value);
            numToIter[value] = prev(uniqueList.end());
        }
    }
};


/*
PROBLEM 8: Design a Food Rating System (LeetCode 2353)
──────────────────────────────────────────────────────
changeRating(food, newRating), highestRated(cuisine)

Time: O(log n) | Space: O(n)
*/
class FoodRatings {
    unordered_map<string, pair<string, int>> foodInfo;  // food → {cuisine, rating}
    unordered_map<string, set<pair<int, string>>> cuisineRatings;  // cuisine → {(-rating, food)}
    
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for (int i = 0; i < foods.size(); i++) {
            foodInfo[foods[i]] = {cuisines[i], ratings[i]};
            cuisineRatings[cuisines[i]].insert({-ratings[i], foods[i]});
        }
    }
    
    void changeRating(string food, int newRating) {
        auto& [cuisine, oldRating] = foodInfo[food];
        cuisineRatings[cuisine].erase({-oldRating, food});
        cuisineRatings[cuisine].insert({-newRating, food});
        oldRating = newRating;
    }
    
    string highestRated(string cuisine) {
        return cuisineRatings[cuisine].begin()->second;
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== HashMap & Randomized Designs ===\n\n";
    
    // 1. HashMap
    MyHashMap hm;
    hm.put(1, 1);
    hm.put(2, 2);
    cout << "1. HashMap get(1): " << hm.get(1) << "\n";
    hm.remove(2);
    cout << "   HashMap get(2): " << hm.get(2) << " (removed)\n";
    
    // 3. RandomizedSet
    RandomizedSet rs;
    rs.insert(1);
    rs.insert(2);
    rs.insert(3);
    cout << "3. Random element: " << rs.getRandom() << "\n";
    rs.remove(2);
    cout << "   After removing 2, random: " << rs.getRandom() << "\n";
    
    // 5. Underground System
    UndergroundSystem us;
    us.checkIn(1, "A", 0);
    us.checkOut(1, "B", 10);
    us.checkIn(2, "A", 5);
    us.checkOut(2, "B", 15);
    cout << "5. Average A->B: " << us.getAverageTime("A", "B") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Design                        | Key Technique                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| HashMap                       | Array of buckets + chaining                    |
| RandomizedSet                 | Array + HashMap (swap with last on delete)     |
| RandomizedSet (dups)          | Array + HashMap<val, set<indices>>             |
| Underground System            | Two HashMaps (checkins, journey stats)         |
| Number Container              | HashMap + ordered set per number               |
| First Unique                  | List + HashMap to iterator                     |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

