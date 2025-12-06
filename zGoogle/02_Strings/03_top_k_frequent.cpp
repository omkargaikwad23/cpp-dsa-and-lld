/*
================================================================================
                TOP K FREQUENT WORDS (Google Interview)
================================================================================

PROBLEM:
Given a document parsed as an array of strings, find the top K most frequent words.

Example:
Input: ["Google", "Bike", "Pencil", "Google", "Bike", "Google"], K = 2
Output: ["Google", "Bike"]

================================================================================
                         FOLLOW-UPS
================================================================================

Follow-up 1: What if input is a STREAM instead of array?
- Use HashMap + Min-Heap of size K
- Time: O(n log k) for n words

Follow-up 2: What if K = 0?
- Return empty array
- Handle edge case explicitly

================================================================================
                         APPROACH
================================================================================

1. Build frequency map: O(n)
2. Use min-heap of size K: O(n log k)
3. Extract and reverse: O(k log k)

Alternative: Quick Select for O(n) average

TIME:  O(n log k) for heap approach
SPACE: O(n) for frequency map

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// APPROACH 1: Array Input - HashMap + Heap
// ═══════════════════════════════════════════════════════════════════════════

vector<string> topKFrequent(vector<string>& words, int k) {
    if (k == 0) return {};  // Handle K = 0 edge case
    
    // Step 1: Build frequency map
    unordered_map<string, int> freq;
    for (const string& word : words) {
        freq[word]++;
    }
    
    // Step 2: Min-heap of size K
    // We want LOWEST frequency at TOP (so it gets popped when heap exceeds K)
    // Comparator returns true if 'a' should be BELOW 'b' in the heap
    auto cmp = [](const pair<int, string>& a, const pair<int, string>& b) {
        if (a.first == b.first) return a.second < b.second;  // Tie: larger word goes below (popped first)
        return a.first > b.first;  // Higher freq goes below (lower freq at top, popped first)
    };
    priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(cmp)> minHeap(cmp);
    
    for (auto& [word, count] : freq) {
        minHeap.push({count, word});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
    }
    
    // Step 3: Extract results (in reverse order)
    vector<string> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    reverse(result.begin(), result.end());
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// APPROACH 2: Stream Input - Real-time Top K
// ═══════════════════════════════════════════════════════════════════════════

class TopKStream {
private:
    int k;
    unordered_map<string, int> freq;
    
public:
    TopKStream(int k) : k(k) {}
    
    void addWord(const string& word) {
        freq[word]++;
    }
    
    vector<string> getTopK() {
        if (k == 0) return {};
        
        // Rebuild heap for current state
        auto cmp = [](const pair<int, string>& a, const pair<int, string>& b) {
            if (a.first == b.first) return a.second < b.second;
            return a.first > b.first;
        };
        priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(cmp)> minHeap(cmp);
        
        for (auto& [word, count] : freq) {
            minHeap.push({count, word});
            if (minHeap.size() > k) minHeap.pop();
        }
        
        vector<string> result;
        while (!minHeap.empty()) {
            result.push_back(minHeap.top().second);
            minHeap.pop();
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test array approach
    vector<string> words = {"Google", "Bike", "Pencil", "Google", "Bike", "Google"};
    int k = 2;
    
    cout << "=== Array Approach ===\n";
    cout << "Words: ";
    for (const string& w : words) cout << w << " ";
    cout << "\nK = " << k << "\n";
    
    vector<string> result = topKFrequent(words, k);
    cout << "Top " << k << " frequent: ";
    for (const string& w : result) cout << w << " ";
    cout << "\n\n";
    
    // Test stream approach
    cout << "=== Stream Approach ===\n";
    TopKStream stream(2);
    for (const string& word : words) {
        stream.addWord(word);
        cout << "After adding '" << word << "': ";
        vector<string> topK = stream.getTopK();
        for (const string& w : topK) cout << w << " ";
        cout << "\n";
    }
    
    // Test K = 0 edge case
    cout << "\n=== Edge Case: K = 0 ===\n";
    vector<string> emptyResult = topKFrequent(words, 0);
    cout << "Result size: " << emptyResult.size() << " (expected: 0)\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

ARRAY APPROACH:
- Build freq map: O(n)
- Maintain heap of size K: O(n log k)
- Extract results: O(k log k)
- Total: O(n log k)
- Space: O(n) for freq map + O(k) for heap

STREAM APPROACH:
- addWord: O(1) amortized
- getTopK: O(n log k) where n = unique words so far
- For real-time stream, consider using Lossy Counting or Count-Min Sketch

================================================================================
*/

