/*
You are given a distance d and a stream of float numbers (i.e., numbers are given one at a time). Your task is to write a method that takes this number as an input, and checks for a group of three numbers, where each number is within a distance 'd' of other two.
If found, remove them from your collection and return.

Lets say for a group of 3 numbers found, a, b and c, the following condition holds:

|a - b| <= d and |b - c| <= d and |c - a| <= d
Example:
for a distance d = 1,
input = 1.1, action => None
input = 2.1, action => None
input = 3.1, action => None
input = 1.5, action => Remove and return {1.1, 2.1, 1.5} as an output.

Clarifying questions that I remember asking:

Is d inclusive for distance between two number? -> Yes
What if the new number received leads to formation of multiple such triplets? -> We decided that smallest three numbers we would remove.
Any desired order of output values? -> No.

*/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

multiset<float> nums;

vector<float> addNumber(float x, float d) {
    nums.insert(x);  // O(log n)
    
    // Check ALL consecutive triplets to find smallest valid one
    // Since multiset is sorted, first valid triplet = smallest
    if (nums.size() < 3) return {};
    
    auto it = nums.begin();
    while (it != nums.end()) {
        auto a = it;
        auto b = next(a);
        if (b == nums.end()) break;
        
        auto c = next(b);
        if (c == nums.end()) break;
        
        // In sorted order: if |c - a| <= d, then all conditions hold
        if (*c - *a <= d) {
            vector<float> result = {*a, *b, *c};
            // Erase in reverse to avoid iterator invalidation
            nums.erase(c);
            nums.erase(b);
            nums.erase(a);
            return result;
        }
        ++it;
    }
    return {};  // No triplet found
}

int main() {
    float d = 1;
    vector<float> numbers = {1.1, 2.1, 3.1, 1.5};
    for(float num : numbers) {
        vector<float> result = addNumber(num, d);
        if(!result.empty()) {
            cout << "Removed triplet: ";
            for(float val : result) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
    return 0;
}