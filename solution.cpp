#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
input: AABABCC
k = 1  (0 <= k <= K)

output:
AABABCC, k = 1

ch = A

count = 
i = 0 -> 1
i = 1 -> 2
i = 2 -> 3 ( k = 0)
i = 3 -> 4
i B =    | l = 2, k = 1

*/

int maxSubstring(string &str, int k) {
    int n = str.size();
    if(n == 0 || k >= n) return n;


    int left = 0;
    int ans = 0, counter = 0;
    char ch = str[0];

    for(int right = 0; right < n; right++) {
        if(str[right] == ch) {
            counter++;
        }
        else if(k > 0) {
            counter++;
            k--;
        }
        else { 
            while(left < right && k == 0) { // shrinking window
                if(str[left] != ch) k++;  // get back our used k operations for future use
                left++;
                counter--;
            }

            if(left == right) 
                ch = str[right];
        }

        ans = max(ans, counter);
    }

    return ans;
}

/*
print 1 to N numbers
t1 -> prints odd numbers
t2 -> prints even numbers

1,2,3,4,5,6


t1 = thread();
t2 = thread();
lock(t2);

odd_counter => 1
even_counter => 2

if(islock(t1)) {     // t1 is unlocked
    print(odd_counter);
    odd_counter += 2;
    unlock(t2);
    lock(t1);
}
else {      // t2 is unlocked
    print(even_counter);
    even_counter += 2;
    unlock(t1);
    lock(t2);
}




*/

int main() {
    string str1 = "ACDABBBBB";
    string str2 = "AABA";
    string str3 = "ABCD";
    string str4 = "";

    cout << maxSubstring(str1, 3) << endl; // 4
    // cout << maxSubstring(str2, 1) << endl; // 4
    // cout << maxSubstring(str3, 2) << endl; // 3
    // cout << maxSubstring(str4, 0) << endl; // 0

}

/*
g++ -o solution solution.cpp && ./solution
*/