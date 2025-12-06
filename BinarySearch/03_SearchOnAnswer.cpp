/*
================================================================================
          BINARY SEARCH ON ANSWER - THE MOST IMPORTANT PATTERN!
================================================================================

Instead of searching IN an array, we search FOR the answer in a range.

The Idea:
1. Define a search space [min_answer, max_answer]
2. For each candidate answer, check if it's FEASIBLE
3. Binary search to find optimal feasible answer

When to Use:
- "Minimum X such that condition is satisfied"
- "Maximum X such that condition is satisfied"  
- "Minimize the maximum..."
- "Maximize the minimum..."
- Problems with monotonic feasibility (if X works, X+1 also works, or vice versa)

Pattern 1: Koko Eating Bananas
Pattern 2: Capacity to Ship Packages
Pattern 3: Split Array Largest Sum
Pattern 4: Minimum Days to Make Bouquets
Pattern 5: Magnetic Force Between Two Balls
Pattern 6: Allocate Minimum Pages
Pattern 7: Minimize Max Distance to Gas Station
Pattern 8: Painters Partition Problem

================================================================================
                        GENERAL TEMPLATE
================================================================================

int binarySearchOnAnswer(/* problem specific params */) {
    int left = minimum_possible_answer;
    int right = maximum_possible_answer;
    int result = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (isFeasible(mid)) {
            result = mid;       // Valid answer, save it
            right = mid - 1;    // Try smaller (if minimizing)
            // left = mid + 1;  // Try larger (if maximizing)
        } else {
            left = mid + 1;     // Need larger value
            // right = mid - 1; // Need smaller value
        }
    }
    
    return result;
}

================================================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>
using namespace std;

/*
================================================================================
PATTERN 1: KOKO EATING BANANAS ⭐
================================================================================
LeetCode: 875. Koko Eating Bananas

Problem: Koko has n piles of bananas. She can eat at most k bananas/hour.
         Find minimum k to eat all bananas within h hours.
         
Key Insight: 
- If speed k works, any speed > k also works (monotonic!)
- Search space: [1, max(piles)]
- Check: can we finish in h hours at speed mid?

Time: O(n * log(max(piles))), Space: O(1)
*/
class KokoEatingBananas {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1;                                    // Min speed
        int right = *max_element(piles.begin(), piles.end());  // Max speed
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canFinish(piles, mid, h)) {
                result = mid;       // This speed works
                right = mid - 1;    // Try slower
            } else {
                left = mid + 1;     // Need faster
            }
        }
        
        return result;
    }
    
private:
    bool canFinish(vector<int>& piles, int speed, int h) {
        long long hours = 0;
        for (int pile : piles) {
            hours += (pile + speed - 1) / speed;  // Ceiling division
            // Equivalent: hours += ceil((double)pile / speed);
        }
        return hours <= h;
    }
};
/*
Example: piles = [3,6,7,11], h = 8
- max = 11, search [1, 11]
- mid=6: hours = 1+1+2+2 = 6 <= 8 ✓, try smaller
- mid=3: hours = 1+2+3+4 = 10 > 8 ✗, need larger
- mid=4: hours = 1+2+2+3 = 8 <= 8 ✓
Answer: 4
*/


/*
================================================================================
PATTERN 2: CAPACITY TO SHIP PACKAGES ⭐
================================================================================
LeetCode: 1011. Capacity To Ship Packages Within D Days

Problem: Ship all packages in order within D days.
         Find minimum ship capacity.

Key Insight:
- Search space: [max(weights), sum(weights)]
- If capacity works, any larger capacity also works

Time: O(n * log(sum - max)), Space: O(1)
*/
class ShipPackages {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        int left = *max_element(weights.begin(), weights.end());  // Must fit largest
        int right = accumulate(weights.begin(), weights.end(), 0); // Ship all at once
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canShip(weights, mid, days)) {
                result = mid;
                right = mid - 1;    // Try smaller capacity
            } else {
                left = mid + 1;     // Need larger capacity
            }
        }
        
        return result;
    }
    
private:
    bool canShip(vector<int>& weights, int capacity, int days) {
        int daysNeeded = 1;
        int currentLoad = 0;
        
        for (int w : weights) {
            if (currentLoad + w > capacity) {
                daysNeeded++;       // Need new day
                currentLoad = w;
            } else {
                currentLoad += w;
            }
        }
        
        return daysNeeded <= days;
    }
};
/*
Example: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
- Search [10, 55]
- Answer: 15 (ship as [1,2,3,4,5], [6,7], [8], [9], [10])
*/


/*
================================================================================
PATTERN 3: SPLIT ARRAY LARGEST SUM ⭐⭐
================================================================================
LeetCode: 410. Split Array Largest Sum

Problem: Split array into m subarrays.
         Minimize the largest sum among subarrays.

Key Insight:
- Same as shipping packages where we minimize max load!
- Search space: [max(nums), sum(nums)]
- If max_sum works, any larger max_sum also works

Time: O(n * log(sum - max)), Space: O(1)
*/
class SplitArrayLargestSum {
public:
    int splitArray(vector<int>& nums, int m) {
        int left = *max_element(nums.begin(), nums.end());
        int right = accumulate(nums.begin(), nums.end(), 0);
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canSplit(nums, mid, m)) {
                result = mid;
                right = mid - 1;    // Try smaller max sum
            } else {
                left = mid + 1;     // Need larger max sum
            }
        }
        
        return result;
    }
    
private:
    bool canSplit(vector<int>& nums, int maxSum, int m) {
        int subarrays = 1;
        int currentSum = 0;
        
        for (int num : nums) {
            if (currentSum + num > maxSum) {
                subarrays++;
                currentSum = num;
            } else {
                currentSum += num;
            }
        }
        
        return subarrays <= m;
    }
};
// Example: nums = [7,2,5,10,8], m = 2 → Answer: 18 ([7,2,5] and [10,8])


/*
================================================================================
PATTERN 4: MINIMUM DAYS TO MAKE M BOUQUETS
================================================================================
LeetCode: 1482. Minimum Number of Days to Make m Bouquets

Problem: n flowers bloom on specific days. Need m bouquets.
         Each bouquet needs k ADJACENT flowers.
         Find minimum days to make m bouquets.

Key Insight:
- Search space: [min(bloomDay), max(bloomDay)]
- If day D works, day D+1 also works

Time: O(n * log(max - min)), Space: O(1)
*/
class MakeBouquets {
public:
    int minDays(vector<int>& bloomDay, int m, int k) {
        long long needed = (long long)m * k;
        if (needed > bloomDay.size()) return -1;  // Impossible
        
        int left = *min_element(bloomDay.begin(), bloomDay.end());
        int right = *max_element(bloomDay.begin(), bloomDay.end());
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canMake(bloomDay, mid, m, k)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
private:
    bool canMake(vector<int>& bloomDay, int day, int m, int k) {
        int bouquets = 0;
        int consecutive = 0;
        
        for (int bloom : bloomDay) {
            if (bloom <= day) {
                consecutive++;
                if (consecutive == k) {
                    bouquets++;
                    consecutive = 0;
                }
            } else {
                consecutive = 0;  // Reset streak
            }
        }
        
        return bouquets >= m;
    }
};
// Example: bloomDay = [1,10,3,10,2], m = 3, k = 1 → Answer: 3


/*
================================================================================
PATTERN 5: MAGNETIC FORCE BETWEEN TWO BALLS
================================================================================
LeetCode: 1552. Magnetic Force Between Two Balls (Aggressive Cows)

Problem: Place m balls in n positions.
         MAXIMIZE the minimum distance between any two balls.

Key Insight:
- This is "Maximize the Minimum" pattern!
- Search space: [1, (max - min) / (m - 1)]
- If distance D works, any smaller distance also works

Time: O(n log n + n * log(range)), Space: O(1)
*/
class MagneticForce {
public:
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());
        
        int left = 1;
        int right = (position.back() - position.front()) / (m - 1);
        int result = 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canPlace(position, mid, m)) {
                result = mid;
                left = mid + 1;     // Try LARGER distance (maximizing)
            } else {
                right = mid - 1;    // Need smaller distance
            }
        }
        
        return result;
    }
    
private:
    bool canPlace(vector<int>& position, int minDist, int m) {
        int count = 1;          // Place first ball at position[0]
        int lastPos = position[0];
        
        for (int i = 1; i < position.size(); i++) {
            if (position[i] - lastPos >= minDist) {
                count++;
                lastPos = position[i];
            }
        }
        
        return count >= m;
    }
};
/*
Example: position = [1,2,3,4,7], m = 3
- Place at positions 1, 4, 7 → distances 3, 3 → min = 3
*/


/*
================================================================================
PATTERN 6: ALLOCATE MINIMUM PAGES (Classic!)
================================================================================
Problem: n books with pages[i] pages each. Allocate to m students.
         Each student gets contiguous books.
         Minimize the maximum pages any student reads.

Same logic as Split Array Largest Sum!
*/
class AllocatePages {
public:
    int allocate(vector<int>& pages, int m) {
        if (m > pages.size()) return -1;  // More students than books
        
        int left = *max_element(pages.begin(), pages.end());
        int right = accumulate(pages.begin(), pages.end(), 0);
        int result = right;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (canAllocate(pages, mid, m)) {
                result = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return result;
    }
    
private:
    bool canAllocate(vector<int>& pages, int maxPages, int m) {
        int students = 1;
        int currentPages = 0;
        
        for (int p : pages) {
            if (currentPages + p > maxPages) {
                students++;
                currentPages = p;
            } else {
                currentPages += p;
            }
        }
        
        return students <= m;
    }
};
// Example: pages = [12, 34, 67, 90], m = 2 → Answer: 113 ([12,34,67] [90])


/*
================================================================================
PATTERN 7: MINIMIZE MAX DISTANCE TO GAS STATION
================================================================================
LeetCode: 774. Minimize Max Distance to Gas Station (Premium)

Problem: Add K gas stations to minimize max distance between any two.

Key: Use real-number binary search with precision!
*/
class MinimizeGasStation {
public:
    double minmaxGasDist(vector<int>& stations, int k) {
        double left = 0, right = 1e8;
        
        while (right - left > 1e-6) {  // Precision
            double mid = (left + right) / 2;
            
            if (canPlace(stations, mid, k)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        
        return left;
    }
    
private:
    bool canPlace(vector<int>& stations, double maxDist, int k) {
        int needed = 0;
        for (int i = 1; i < stations.size(); i++) {
            double gap = stations[i] - stations[i-1];
            needed += (int)(gap / maxDist);  // Stations needed in this gap
        }
        return needed <= k;
    }
};


/*
================================================================================
PATTERN 8: PAINTERS PARTITION (Classic Competitive Programming)
================================================================================
Problem: n boards with lengths. k painters, each takes 1 unit time per length.
         Painters can only paint contiguous boards.
         Minimize total time (= minimize max painter workload).

Same as Split Array / Allocate Pages!
*/
class PaintersPartition {
public:
    int minTime(vector<int>& boards, int k) {
        if (k > boards.size()) k = boards.size();
        
        int left = *max_element(boards.begin(), boards.end());
        int right = accumulate(boards.begin(), boards.end(), 0);
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (paintersNeeded(boards, mid) <= k) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
private:
    int paintersNeeded(vector<int>& boards, int maxLength) {
        int painters = 1;
        int current = 0;
        
        for (int len : boards) {
            if (current + len > maxLength) {
                painters++;
                current = len;
            } else {
                current += len;
            }
        }
        
        return painters;
    }
};


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Binary Search on Answer ===\n\n";
    
    // Pattern 1: Koko Eating Bananas
    vector<int> piles = {3, 6, 7, 11};
    KokoEatingBananas koko;
    cout << "1. Koko Bananas [3,6,7,11], h=8: " << koko.minEatingSpeed(piles, 8) << endl;
    
    // Pattern 2: Ship Packages
    vector<int> weights = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ShipPackages ship;
    cout << "2. Ship Packages [1-10], days=5: " << ship.shipWithinDays(weights, 5) << endl;
    
    // Pattern 3: Split Array
    vector<int> nums = {7, 2, 5, 10, 8};
    SplitArrayLargestSum split;
    cout << "3. Split Array [7,2,5,10,8], m=2: " << split.splitArray(nums, 2) << endl;
    
    // Pattern 4: Make Bouquets
    vector<int> bloom = {1, 10, 3, 10, 2};
    MakeBouquets bouquet;
    cout << "4. Make Bouquets [1,10,3,10,2], m=3, k=1: " << bouquet.minDays(bloom, 3, 1) << endl;
    
    // Pattern 5: Magnetic Force (Aggressive Cows)
    vector<int> positions = {1, 2, 3, 4, 7};
    MagneticForce force;
    cout << "5. Magnetic Force [1,2,3,4,7], balls=3: " << force.maxDistance(positions, 3) << endl;
    
    // Pattern 6: Allocate Pages
    vector<int> pages = {12, 34, 67, 90};
    AllocatePages alloc;
    cout << "6. Allocate Pages [12,34,67,90], m=2: " << alloc.allocate(pages, 2) << endl;
    
    return 0;
}

/*
================================================================================
                          CHEAT SHEET
================================================================================

┌──────────────────────────────────────────────────────────────────────────────┐
│ Problem Type                │ Search Space        │ Feasibility Check        │
├──────────────────────────────────────────────────────────────────────────────┤
│ Koko Eating Bananas         │ [1, max(piles)]     │ Can finish in H hours?   │
│ Ship Packages               │ [max, sum]          │ Can ship in D days?      │
│ Split Array                 │ [max, sum]          │ Can split into ≤ m parts?│
│ Make Bouquets               │ [min, max day]      │ Can make m bouquets?     │
│ Aggressive Cows             │ [1, range/(m-1)]    │ Can place m balls?       │
│ Allocate Pages              │ [max, sum]          │ Students ≤ m?            │
└──────────────────────────────────────────────────────────────────────────────┘

MINIMIZE vs MAXIMIZE:
- MINIMIZE answer: when feasible, try smaller (right = mid - 1)
- MAXIMIZE answer: when feasible, try larger (left = mid + 1)

KEY FORMULA:
- Ceiling division: (a + b - 1) / b
- Days/hours needed: sum of ceil(pile[i] / speed)

================================================================================
                      IDENTIFICATION KEYWORDS
================================================================================

"minimum speed/capacity/time such that..."
"maximum distance/gap such that..."
"minimize the maximum..."
"maximize the minimum..."
"at most K operations/days/hours"
"allocate/distribute to M groups"
"split into M parts"

================================================================================
*/

