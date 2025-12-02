/*
================================================================================
                    GREEDY - CLASSIC ALGORITHMS
================================================================================

Classic greedy algorithms and miscellaneous problems.

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Fractional Knapsack
──────────────────────────────
Items have weight and value. Maximize value with capacity W. Can take fractions.

Strategy: Sort by value/weight ratio, take greedily

Time: O(n log n) | Space: O(1)
*/
double fractionalKnapsack(int W, vector<pair<int, int>>& items) {  // {value, weight}
    // Sort by value/weight ratio descending
    sort(items.begin(), items.end(), [](auto& a, auto& b) {
        return (double)a.first / a.second > (double)b.first / b.second;
    });
    
    double totalValue = 0.0;
    
    for (auto& [value, weight] : items) {
        if (W >= weight) {
            totalValue += value;
            W -= weight;
        } else {
            totalValue += (double)value * W / weight;
            break;
        }
    }
    
    return totalValue;
}


/*
PROBLEM 2: Job Sequencing Problem
─────────────────────────────────
Jobs have deadlines and profits. Each job takes 1 unit time. Maximize profit.

Strategy: Sort by profit desc, schedule in latest available slot

Time: O(n²) or O(n log n) with Union-Find | Space: O(maxDeadline)
*/
pair<int, int> jobSequencing(vector<array<int, 3>>& jobs) {  // {id, deadline, profit}
    // Sort by profit descending
    sort(jobs.begin(), jobs.end(), [](auto& a, auto& b) {
        return a[2] > b[2];
    });
    
    int maxDeadline = 0;
    for (auto& job : jobs) maxDeadline = max(maxDeadline, job[1]);
    
    vector<int> slot(maxDeadline + 1, -1);  // slot[i] = job scheduled at time i
    
    int count = 0, profit = 0;
    
    for (auto& job : jobs) {
        // Find latest free slot <= deadline
        for (int j = job[1]; j > 0; j--) {
            if (slot[j] == -1) {
                slot[j] = job[0];
                count++;
                profit += job[2];
                break;
            }
        }
    }
    
    return {count, profit};
}


/*
PROBLEM 3: Huffman Encoding
───────────────────────────
Build optimal prefix-free encoding for characters based on frequency.

Strategy: Build tree by repeatedly combining two smallest frequencies

Time: O(n log n) | Space: O(n)
*/
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left, *right;
    
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

void printCodes(HuffmanNode* root, string code) {
    if (!root) return;
    
    if (root->ch != '$') {
        cout << root->ch << ": " << code << "\n";
    }
    
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void huffmanCoding(vector<pair<char, int>>& data) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    
    for (auto& [ch, freq] : data) {
        pq.push(new HuffmanNode(ch, freq));
    }
    
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        
        HuffmanNode* internal = new HuffmanNode('$', left->freq + right->freq);
        internal->left = left;
        internal->right = right;
        
        pq.push(internal);
    }
    
    printCodes(pq.top(), "");
}


/*
PROBLEM 4: Minimum Spanning Tree - Kruskal's Algorithm
──────────────────────────────────────────────────────
Find MST by picking smallest edges that don't form cycle.

Time: O(E log E) | Space: O(V)
*/
class UnionFind {
    vector<int> parent, rank_;
public:
    UnionFind(int n) : parent(n), rank_(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank_[px] < rank_[py]) swap(px, py);
        parent[py] = px;
        if (rank_[px] == rank_[py]) rank_[px]++;
        
        return true;
    }
};

int kruskalMST(int n, vector<array<int, 3>>& edges) {  // {weight, u, v}
    sort(edges.begin(), edges.end());
    
    UnionFind uf(n);
    int mstWeight = 0, edgesUsed = 0;
    
    for (auto& [w, u, v] : edges) {
        if (uf.unite(u, v)) {
            mstWeight += w;
            edgesUsed++;
            if (edgesUsed == n - 1) break;
        }
    }
    
    return mstWeight;
}


/*
PROBLEM 5: Two City Scheduling (LeetCode 1029)
──────────────────────────────────────────────
Send n people to city A and n to city B. Minimize total cost.
costs[i] = [costA, costB]

Strategy: Sort by (costA - costB), send first half to A

Time: O(n log n) | Space: O(1)
*/
int twoCitySchedCost(vector<vector<int>>& costs) {
    // Sort by how much more expensive A is than B
    sort(costs.begin(), costs.end(), [](auto& a, auto& b) {
        return (a[0] - a[1]) < (b[0] - b[1]);
    });
    
    int total = 0, n = costs.size() / 2;
    
    for (int i = 0; i < n; i++) {
        total += costs[i][0];          // First half to A
        total += costs[i + n][1];      // Second half to B
    }
    
    return total;
}


/*
PROBLEM 6: Boats to Save People (LeetCode 881)
──────────────────────────────────────────────
Each boat holds at most 2 people with weight limit.

Strategy: Sort, pair heaviest with lightest if possible

Time: O(n log n) | Space: O(1)
*/
int numRescueBoats(vector<int>& people, int limit) {
    sort(people.begin(), people.end());
    
    int left = 0, right = people.size() - 1;
    int boats = 0;
    
    while (left <= right) {
        if (people[left] + people[right] <= limit) {
            left++;
        }
        right--;
        boats++;
    }
    
    return boats;
}


/*
PROBLEM 7: Minimum Number of Refueling Stops (LeetCode 871)
───────────────────────────────────────────────────────────
Car with startFuel, stations[i] = [position, fuel]. Reach target.

Strategy: Pass stations, use max-heap to pick best station when needed

Time: O(n log n) | Space: O(n)
*/
int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
    priority_queue<int> pq;  // Max-heap of fuel amounts passed
    
    int fuel = startFuel, pos = 0, stops = 0, i = 0;
    
    while (pos + fuel < target) {
        // Add all stations we can reach
        while (i < stations.size() && stations[i][0] <= pos + fuel) {
            pq.push(stations[i][1]);
            i++;
        }
        
        if (pq.empty()) return -1;  // Can't reach next station or target
        
        // Use best available station
        fuel -= (pq.empty() ? 0 : 0);  // Consume fuel to reach current position
        fuel += pq.top();
        pq.pop();
        stops++;
    }
    
    return stops;
}


/*
PROBLEM 8: Reduce Array Size to The Half (LeetCode 1338)
────────────────────────────────────────────────────────
Remove elements to reduce array to half size. Minimize distinct elements removed.

Strategy: Remove most frequent elements first

Time: O(n log n) | Space: O(n)
*/
int minSetSize(vector<int>& arr) {
    unordered_map<int, int> freq;
    for (int x : arr) freq[x]++;
    
    vector<int> counts;
    for (auto& [_, f] : freq) counts.push_back(f);
    
    sort(counts.rbegin(), counts.rend());
    
    int removed = 0, target = arr.size() / 2;
    int count = 0;
    
    for (int f : counts) {
        removed += f;
        count++;
        if (removed >= target) break;
    }
    
    return count;
}


/*
PROBLEM 9: Minimum Deletions to Make Array Beautiful (LeetCode 2216)
────────────────────────────────────────────────────────────────────
Array is beautiful if length is even and nums[i] != nums[i+1] for even i.

Time: O(n) | Space: O(1)
*/
int minDeletion(vector<int>& nums) {
    int deletions = 0;
    
    for (int i = 0; i < nums.size() - 1; i++) {
        // At even index (after deletions), can't equal next
        if ((i - deletions) % 2 == 0 && nums[i] == nums[i + 1]) {
            deletions++;
        }
    }
    
    // If final length is odd, delete one more
    if ((nums.size() - deletions) % 2 == 1) {
        deletions++;
    }
    
    return deletions;
}


/*
PROBLEM 10: Maximum Units on a Truck (LeetCode 1710)
────────────────────────────────────────────────────
Load boxes on truck (capacity = truckSize boxes). Maximize units.

Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
Output: 8 (1 box with 3 units + 2 boxes with 2 units + 1 box with 1 unit)

Time: O(n log n) | Space: O(1)
*/
int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
    // Sort by units per box descending
    sort(boxTypes.begin(), boxTypes.end(), [](auto& a, auto& b) {
        return a[1] > b[1];
    });
    
    int units = 0;
    
    for (auto& box : boxTypes) {
        int take = min(truckSize, box[0]);
        units += take * box[1];
        truckSize -= take;
        
        if (truckSize == 0) break;
    }
    
    return units;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Classic Greedy ===\n\n";
    
    // 1. Fractional Knapsack
    vector<pair<int, int>> items = {{60, 10}, {100, 20}, {120, 30}};
    cout << "1. Fractional knapsack (W=50): " << fractionalKnapsack(50, items) << "\n";
    
    // 3. Huffman Encoding
    vector<pair<char, int>> chars = {{'a', 5}, {'b', 9}, {'c', 12}, {'d', 13}, {'e', 16}, {'f', 45}};
    cout << "3. Huffman codes:\n";
    huffmanCoding(chars);
    
    // 5. Two City Scheduling
    vector<vector<int>> costs = {{10,20},{30,200},{400,50},{30,20}};
    cout << "5. Min cost: " << twoCitySchedCost(costs) << "\n";
    
    // 6. Boats to Save People
    vector<int> people = {3, 2, 2, 1};
    cout << "6. Min boats: " << numRescueBoats(people, 3) << "\n";
    
    // 10. Maximum Units
    vector<vector<int>> boxes = {{1,3},{2,2},{3,1}};
    cout << "10. Max units: " << maximumUnits(boxes, 4) << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+───────────────────────────────+────────────────────────────────────────────────+
| Algorithm                     | Greedy Choice                                  |
+───────────────────────────────+────────────────────────────────────────────────+
| Fractional Knapsack           | Sort by value/weight ratio                     |
| Job Sequencing                | Sort by profit, schedule in latest slot        |
| Huffman Encoding              | Combine two smallest frequencies               |
| Kruskal's MST                 | Pick smallest edge that doesn't form cycle     |
| Two City Scheduling           | Sort by (costA - costB)                        |
| Boats to Save People          | Pair heaviest with lightest                    |
| Refueling Stops               | Use max-heap, pick best station when needed    |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

