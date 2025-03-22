/*
https://leetcode.com/discuss/post/5676823/google-l4-swe3-phone-screen-by-swatsam29-rvsi/

Problem: Write a function to determine if it's possible to make a single vertical cut through a rectangular cake with non-overlapping toppings such that:

The cut does not intersect or destroy any of the toppings.
After the cut, both resulting pieces of the cake each contain at least one topping.

List of toppings with their positions [topping (start_x, end_x, start_y, end_y) ]
Output:
True/False
Example:
Input :
a (0,6,0, 1); b (7,8,0,4); c(0, 1,2,4) ;

Explanation:
012345678
0 aaaaaaabb
1 aaaaaaabb
2 cc.........bb
3 cc.........bb
4 cc.........bb

It can cut between column 6 and 7 vertically, After the cut, the left piece has topping a, c; right piece has topping b.
*/

/*
To determine if it's possible to make a single vertical cut in the cake such that the cut does not intersect any toppings and both resulting pieces of the cake contain at least one topping, we can follow these steps:

Thought Process:
Extract Topping Positions:
First, identify all the unique x-positions where the toppings start and end. This will help determine possible cut positions.
Determine Potential Cut Positions:
Sort the unique x-positions and consider the space between each pair of consecutive positions as possible cut positions.
Verify Each Possible Cut:
For each potential cut position (between two consecutive unique x-positions), check:
If there is no topping crossing the potential cut line.
That the segments of the cake on both sides of the cut contain at least one topping.

Steps in Detail:
Finding the Unique X-Positions:
Extract the start and end x-positions of each topping.
Sort these positions to determine distinct potential cut locations.
Checking Possible Cuts:
For each gap between consecutive x-positions, verify if a vertical cut there would have:
No topping spanning across the cut.
At least one topping on both sides.
Time and Space Complexity:
Time Complexity: O(n * m), where n is the number of toppings and m is the number of unique x-positions. Sorting the positions takes O(m log m) and checking across all toppings takes O(n).
Space Complexity: O(m), where m is the number of unique x-positions stored.
*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool canCutCake(const vector<vector<int>>& toppings) {
    set<int> xPositions;
    for (const auto& topping : toppings) {
        xPositions.insert(topping[0]); // start_x
        xPositions.insert(topping[1]); // end_x
    }

    auto it = xPositions.begin();
    int previous = *it;
    ++it;

    while (it != xPositions.end()) {
        int current = *it;
        
        // Check a possible cut between 'previous' and 'current'
        bool hasLeftTopping = false, hasRightTopping = false, canCut = true;
        
        for (const auto& topping : toppings) {
            int start_x = topping[0];
            int end_x = topping[1];
            
            if (start_x <= previous && end_x >= current) {
                canCut = false;
                break;
            }
            
            if (end_x <= previous) {
                hasLeftTopping = true;
            }
            
            if (start_x >= current) {
                hasRightTopping = true;
            }
        }
        
        if (canCut && hasLeftTopping && hasRightTopping) {
            return true;
        }
        
        previous = current;
        ++it;
    }
    
    return false;
}

int main() {
    vector<vector<int>> toppings1 = {
        {0, 6, 0, 1},
        {7, 8, 0, 4},
        {0, 1, 2, 4}
    };
    
    if (canCutCake(toppings1)) {
        cout << "True. It's possible to make the cut." << endl;
    } else {
        cout << "False. It's not possible to make the cut." << endl;
    }
    
    return 0;
}