/*
================================================================================
                    RESERVOIR SAMPLING
================================================================================

PROBLEM: Randomly select k items from a stream of unknown/infinite size,
         where each item has equal probability of being selected.

KEY INSIGHT: For each new item at position i (1-indexed):
  - Keep it with probability k/i
  - If keeping, replace a random item in reservoir

WHY IT WORKS: After seeing n items, each has k/n probability of being in reservoir.

ALGORITHM (for k=1):
1. Keep first item
2. For item i: replace with probability 1/i

TIME:  O(n)
SPACE: O(k)

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

// ═══════════════════════════════════════════════════════════════════════════
// SINGLE ITEM SAMPLING (k=1) - LC 382: Linked List Random Node
// ═══════════════════════════════════════════════════════════════════════════

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution382 {
    ListNode* head;
    
public:
    Solution382(ListNode* head) : head(head) {
        srand(time(0));
    }
    
    int getRandom() {
        ListNode* curr = head;
        int result = curr->val;
        int i = 1;
        
        while (curr) {
            // Keep current with probability 1/i
            if (rand() % i == 0) {
                result = curr->val;
            }
            i++;
            curr = curr->next;
        }
        
        return result;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// K ITEMS SAMPLING - General Reservoir Sampling
// ═══════════════════════════════════════════════════════════════════════════

vector<int> reservoirSample(vector<int>& stream, int k) {
    vector<int> reservoir(k);
    
    // Fill reservoir with first k items
    for (int i = 0; i < k; i++) {
        reservoir[i] = stream[i];
    }
    
    // Process remaining items
    for (int i = k; i < stream.size(); i++) {
        // Generate random index in [0, i]
        int j = rand() % (i + 1);
        
        // If j < k, replace reservoir[j] with stream[i]
        if (j < k) {
            reservoir[j] = stream[i];
        }
    }
    
    return reservoir;
}

// ═══════════════════════════════════════════════════════════════════════════
// RANDOM PICK INDEX (LC 398) - Pick random index of target value
// ═══════════════════════════════════════════════════════════════════════════

class Solution398 {
    vector<int> nums;
    
public:
    Solution398(vector<int>& nums) : nums(nums) {
        srand(time(0));
    }
    
    int pick(int target) {
        int result = -1;
        int count = 0;
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == target) {
                count++;
                // Keep index i with probability 1/count
                if (rand() % count == 0) {
                    result = i;
                }
            }
        }
        
        return result;
    }
};

// ═══════════════════════════════════════════════════════════════════════════
// WEIGHTED RESERVOIR SAMPLING
// ═══════════════════════════════════════════════════════════════════════════

// For weighted sampling, use Algorithm A-ES:
// Key = random() ^ (1/weight)  → keep items with highest keys
vector<int> weightedReservoirSample(vector<pair<int, double>>& items, int k) {
    // items[i] = {value, weight}
    priority_queue<pair<double, int>> pq;  // {key, value}
    
    for (auto& [val, weight] : items) {
        double key = pow((double)rand() / RAND_MAX, 1.0 / weight);
        pq.push({key, val});
        
        // This approach is simplified; full A-ES is more complex
    }
    
    vector<int> result;
    while (result.size() < k && !pq.empty()) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    
    return result;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    srand(time(0));
    
    // Test basic reservoir sampling
    vector<int> stream = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 3;
    
    cout << "Stream: [1..10], k=" << k << "\n";
    cout << "10 samples:\n";
    
    for (int t = 0; t < 10; t++) {
        vector<int> sample = reservoirSample(stream, k);
        cout << "  [";
        for (int i = 0; i < k; i++) {
            cout << sample[i];
            if (i < k - 1) cout << ", ";
        }
        cout << "]\n";
    }
    
    // Test LC 398
    cout << "\n=== Random Pick Index ===\n";
    vector<int> nums = {1, 2, 3, 3, 3};
    Solution398 sol(nums);
    
    cout << "Array: [1, 2, 3, 3, 3]\n";
    cout << "Pick index of 3 (10 times): ";
    for (int i = 0; i < 10; i++) {
        cout << sol.pick(3) << " ";
    }
    cout << "\n";
    
    return 0;
}

/*
================================================================================
                         PROBABILITY PROOF (k=1)
================================================================================

Claim: After n items, each item has 1/n probability of being selected.

Proof by induction:
- Base: Item 1 has probability 1/1 = 1 of being selected.
- Inductive step: Assume true for n items.
  - Item n+1: selected with probability 1/(n+1) ✓
  - Item i (i ≤ n): 
    - Was selected after n items with probability 1/n
    - Survives (not replaced) with probability n/(n+1)
    - Final probability: (1/n) × (n/(n+1)) = 1/(n+1) ✓

RELATED PROBLEMS:
- LC 382: Linked List Random Node
- LC 398: Random Pick Index
- LC 384: Shuffle an Array (uses similar randomization)

================================================================================
*/

