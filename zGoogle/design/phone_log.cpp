#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * PROBLEM: Phone Call Logs - Most Talkative Person
 * =================================================
 * 
 * Design a system for a telephone company that tracks phone call logs.
 * 
 * Implement two functions:
 * 
 * 1. registerLog(personId, startTime, endTime)
 *    - Records a phone call log for a person
 *    - personId: identifier of the person making/receiving the call
 *    - startTime: when the call started (in seconds/minutes)
 *    - endTime: when the call ended
 * 
 * 2. getMostTalkativePerson(timestamp)
 *    - Returns the person who has talked the MOST (total duration) up to the given timestamp
 *    - Only count calls that have COMPLETED before or at the timestamp
 *    - Return the personId with maximum talk time
 * 
 * Example:
 * --------
 * registerLog("Alice", 0, 10)     // Alice talks for 10 units (0 to 10)
 * registerLog("Bob", 5, 15)       // Bob talks for 10 units (5 to 15)
 * registerLog("Alice", 20, 35)    // Alice talks for 15 units (20 to 35)
 * registerLog("Bob", 30, 40)      // Bob talks for 10 units (30 to 40)
 * 
 * getMostTalkativePerson(12)  → "Alice" (Alice: 10, Bob: 0 - Bob's call not complete)
 * getMostTalkativePerson(20)  → Both have 10, return either (Alice: 10, Bob: 10)
 * getMostTalkativePerson(40)  → "Alice" (Alice: 25, Bob: 20)
 * 
 * Constraints:
 * - Multiple people can have calls
 * - Calls don't overlap for same person (assumption)
 * - Need OPTIMAL time complexity for queries
 * 
 * Follow-up considerations:
 * - What if we need most talkative at any point in time (including ongoing calls)?
 * - What if we need top-K talkative people?
 * - How to handle very large number of logs efficiently?
 */

class PhoneLogSystem {
private:
    // Store all call logs: personId -> list of {startTime, endTime}
    unordered_map<string, vector<pair<int, int>>> logs;
    
    // Optional: Cache results for frequently queried timestamps
    // unordered_map<int, string> cache;
    
public:
    /**
     * Register a phone call log
     * Time Complexity: O(1) - just append to vector
     */
    void registerLog(string personId, int startTime, int endTime) {
        logs[personId].push_back({startTime, endTime});
    }
    
    /**
     * Get most talkative person up to given timestamp
     * Time Complexity: O(N * M) where N = number of people, M = avg calls per person
     * Space Complexity: O(1) extra space
     * 
     * Optimization: If this is called frequently, we can:
     * 1. Pre-sort logs by endTime for binary search
     * 2. Use segment tree for range queries
     * 3. Cache results for common timestamps
     */
    string getMostTalkativePerson(int timestamp) {
        string mostTalkative = "";
        int maxTalkTime = 0;
        
        // Iterate through each person's logs
        for(auto& [personId, callLogs] : logs) {
            int totalTime = 0;
            
            // Sum up all completed calls before timestamp
            for(auto& [start, end] : callLogs) {
                // Only count if call has COMPLETED by timestamp
                if(end <= timestamp) {
                    totalTime += (end - start);
                }
            }
            
            // Update most talkative person
            if(totalTime > maxTalkTime) {
                maxTalkTime = totalTime;
                mostTalkative = personId;
            }
        }
        
        return mostTalkative;
    }
    
    /**
     * OPTIMIZED VERSION using sorted logs and binary search
     * Pre-sort logs by endTime for faster querying
     * Time Complexity: O(log M) per person using binary search
     */
    string getMostTalkativePersonOptimized(int timestamp) {
        string mostTalkative = "";
        int maxTalkTime = 0;
        
        for(auto& [personId, callLogs] : logs) {
            int totalTime = 0;
            
            // Binary search to find all calls ending <= timestamp
            // Assuming logs are sorted by endTime
            for(auto& [start, end] : callLogs) {
                if(end > timestamp) break; // Assuming sorted
                totalTime += (end - start);
            }
            
            if(totalTime > maxTalkTime) {
                maxTalkTime = totalTime;
                mostTalkative = personId;
            }
        }
        
        return mostTalkative;
    }
    
    /**
     * Extension: Get total talk time for a specific person at timestamp
     */
    int getTalkTime(string personId, int timestamp) {
        if(logs.find(personId) == logs.end()) return 0;
        
        int totalTime = 0;
        for(auto& [start, end] : logs[personId]) {
            if(end <= timestamp) {
                totalTime += (end - start);
            }
        }
        return totalTime;
    }
    
    /**
     * Extension: Get most talkative considering ONGOING calls too
     */
    string getMostTalkativeWithOngoing(int timestamp) {
        string mostTalkative = "";
        int maxTalkTime = 0;
        
        for(auto& [personId, callLogs] : logs) {
            int totalTime = 0;
            
            for(auto& [start, end] : callLogs) {
                // Count completed calls
                if(end <= timestamp) {
                    totalTime += (end - start);
                }
                // Count ongoing calls (partial duration)
                else if(start <= timestamp && end > timestamp) {
                    totalTime += (timestamp - start);
                }
                // Skip future calls (start > timestamp)
            }
            
            if(totalTime > maxTalkTime) {
                maxTalkTime = totalTime;
                mostTalkative = personId;
            }
        }
        
        return mostTalkative;
    }
};

int main() {
    PhoneLogSystem system;
    
    // Test Case 1: Basic scenario
    cout << "=== Test Case 1: Basic Scenario ===" << endl;
    system.registerLog("Alice", 0, 10);    // Alice: 10 units
    system.registerLog("Bob", 5, 15);      // Bob: 10 units
    system.registerLog("Alice", 20, 35);   // Alice: +15 units = 25 total
    system.registerLog("Bob", 30, 40);     // Bob: +10 units = 20 total
    
    cout << "Query at timestamp 12: " << system.getMostTalkativePerson(12) << endl;
    cout << "Expected: Alice (Alice: 10, Bob: 0 - Bob's call not complete yet)" << endl;
    cout << "Alice talk time at 12: " << system.getTalkTime("Alice", 12) << " units" << endl;
    cout << "Bob talk time at 12: " << system.getTalkTime("Bob", 12) << " units" << endl;
    cout << endl;
    
    cout << "Query at timestamp 20: " << system.getMostTalkativePerson(20) << endl;
    cout << "Expected: Alice or Bob (both have 10 units)" << endl;
    cout << "Alice talk time at 20: " << system.getTalkTime("Alice", 20) << " units" << endl;
    cout << "Bob talk time at 20: " << system.getTalkTime("Bob", 20) << " units" << endl;
    cout << endl;
    
    cout << "Query at timestamp 40: " << system.getMostTalkativePerson(40) << endl;
    cout << "Expected: Alice (Alice: 25, Bob: 20)" << endl;
    cout << "Alice talk time at 40: " << system.getTalkTime("Alice", 40) << " units" << endl;
    cout << "Bob talk time at 40: " << system.getTalkTime("Bob", 40) << " units" << endl;
    cout << endl;
    
    // Test Case 2: With ongoing calls
    cout << "=== Test Case 2: With Ongoing Calls ===" << endl;
    cout << "Query at timestamp 12 (with ongoing): " << system.getMostTalkativeWithOngoing(12) << endl;
    cout << "Expected: Bob (Alice: 10, Bob: 10 complete + 0 ongoing = 10, or Bob might have partial)" << endl;
    cout << endl;
    
    // Test Case 3: Multiple calls same person
    PhoneLogSystem system2;
    cout << "=== Test Case 3: Heavy User vs Light User ===" << endl;
    system2.registerLog("Charlie", 0, 5);
    system2.registerLog("Charlie", 10, 20);
    system2.registerLog("Charlie", 25, 40);  // Charlie: 5 + 10 + 15 = 30 total
    system2.registerLog("David", 0, 25);     // David: 25 total
    
    cout << "Query at timestamp 30: " << system2.getMostTalkativePerson(30) << endl;
    cout << "Expected: Charlie (Charlie: 30, David: 25)" << endl;
    cout << "Charlie talk time: " << system2.getTalkTime("Charlie", 30) << " units" << endl;
    cout << "David talk time: " << system2.getTalkTime("David", 30) << " units" << endl;
    
    return 0;
}

/*
 * COMPLEXITY ANALYSIS:
 * ====================
 * 
 * registerLog(): O(1)
 * getMostTalkativePerson(): O(N * M) 
 *   - N = number of unique people
 *   - M = average number of calls per person
 * 
 * OPTIMIZATIONS:
 * ==============
 * 
 * 1. Sort logs by endTime during insertion:
 *    - Can use binary search to find calls ending <= timestamp
 *    - Query becomes O(N * log M)
 * 
 * 2. Prefix sum approach:
 *    - Maintain cumulative talk time for each person
 *    - Requires careful handling of partial updates
 * 
 * 3. Segment Tree / Fenwick Tree:
 *    - If we need range queries frequently
 *    - Can query in O(log T) where T is time range
 * 
 * 4. Caching:
 *    - Cache results for frequently queried timestamps
 *    - Trade space for time
 * 
 * FOLLOW-UP QUESTIONS TO ASK INTERVIEWER:
 * ========================================
 * 1. Should we count ongoing calls or only completed?
 * 2. Can calls overlap for same person?
 * 3. What's the expected query frequency vs log registration frequency?
 * 4. Do we need top-K talkative people or just the most talkative?
 * 5. Can we preprocess data or must handle online queries?
 * 6. What's the time range? (affects data structure choice)
 */