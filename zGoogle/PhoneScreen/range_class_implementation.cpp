#include <iostream>
#include <set>

using namespace std;

class RangeTracker {
private:
    set<pair<int, int>> ranges;

public:
    void addRanges(int start, int end) {
        auto it = ranges.lower_bound({start, end});
        
        // Check for merging with existing ranges
        if (it != ranges.begin() && prev(it)->second >= start - 1) {
            --it;
        }

        // Merge overlapping or adjacent ranges
        while (it != ranges.end() && it->first <= end + 1) {
            start = min(start, it->first);
            end = max(end, it->second);
            it = ranges.erase(it);
        }
        
        ranges.insert({start, end});
    }

    bool isPointInRanges(int point) {
        auto it = ranges.upper_bound({point, INT_MAX});
        if (it == ranges.begin()) return false;
        --it;
        return it->first <= point && point <= it->second;
    }
};

// Driver Code
int main() {
    RangeTracker rt;
    rt.addRanges(1, 5);
    cout << rt.isPointInRanges(3) << endl; // true
    cout << rt.isPointInRanges(6) << endl; // false
    rt.addRanges(7, 10);
    cout << rt.isPointInRanges(8) << endl; // true
    rt.addRanges(4, 8); // Should merge intervals to [1,10]
    cout << rt.isPointInRanges(6) << endl; // true
    return 0;
}
