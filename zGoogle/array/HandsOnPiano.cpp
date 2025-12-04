/*
You have a piano keyboard and one hand.

You place your hand such that your five fingers cover five consecutive keys:

[finger1 finger2 finger3 finger4 finger5]
covers → [key, key+1, key+2, key+3, key+4]

You can press any of these 5 keys without moving the hand.
BUT
If the next key to play is outside these 5 keys, you must lift your hand and reposition it.
This counts as one hand raise.

Your task:

Given the sequence of keys to play, find the minimum number of hand raises needed to play them in order.


Follow up:
return the list of thumb positions you actually use—so you can see exactly where your thumb goes for each segment


Solution:

1. use two pointers to track the left and rightmost keys covered by the hand.
2. if the next key is within the range of the hand, move the right pointer to the next key.
3. if the next key is outside the range of the hand, move the left pointer to the next key and increment the count of hand raises.
4. return the count of hand raises.

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>

using namespace std;


int minHandRaises(vector<int> &keys) {
    if (keys.empty()) return 0;
    
    int raises = 0;
    int lo = keys[0], hi = keys[0];  // Current hand range [lo, hi]
    
    for (int key : keys) {
        if (key > lo + 4 || key < hi - 4) {  // Can't reach this key
            raises++;
            lo = hi = key;  // Reset hand position
        } else {
            lo = min(lo, key);  // Extend range if needed
            hi = max(hi, key);
        }
    }
    
    return raises;
}

// Helper to run testcases
void runTest(vector<int> input, int expected) {
    int result = minHandRaises(input);
    cout << "Input: ";
    for (int x : input) cout << x << " ";
    cout << "\nExpected = " << expected 
         << ", Got = " << result;

    if (result == expected) cout << "   ✔ PASS\n\n";
    else cout << "   ✘ FAIL\n\n";
}


// Main test runner
int main() {
    
    runTest({10,11,12,13,14}, 0);
    runTest({5,4,3,2,1}, 0);
    runTest({10,11,12,20}, 1);
    runTest({5,7,10,11,20,22}, 2);
    runTest({1,100,101,102,50,51,55}, 3);
    runTest({7,7,7,7}, 0);
    runTest({10,20,11,21,12,22}, 5);
    runTest({1,2,3,4,5,6}, 1);
    runTest({50,51,52,1000,1001,1002,1003,2000}, 2);
    runTest({3,10,11,4,5,6,20,21}, 3);
    runTest({5,1,9}, 1);

    return 0;
}