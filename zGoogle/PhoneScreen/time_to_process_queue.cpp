/*
https://leetcode.com/discuss/post/2199394/google-phone-time-for-turn-by-anonymous_-c40y/

Joseph is standing at k+1th position in a queue at an insurance company's office and there are n counters at the office, ith counter takes time[i] time (minutes) to process a request. The security guard assigns a counter to the person standing in the front of the queue as soon as a counter is available or if multiple counters are available, then the security official assigns the counter with minimum id (consider id as index). What would be the time at which Joseph's request would be processed aka the ending time when Joseph leaves the office?

Example case

n = 3
times = [3,2,5]
k = 4

Person 1: assign counter 0 (available counter with minimum index)
Person 2: assign counter 1 (available counter with minimum index)
Person 3: assign counter 2 (available counter with minimum index)
Person 4: assign counter 1 (available counter with minimum index)
Person 5 (Joesph): assign counter 0 (available counter with minimum index)
*/

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

int solve(int times[], int n, int k) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;
    
    for(int i=0; i<n; i++) {
        pq.push({0, i}); // available time, counter index
    }
    int totalTime = 0;
    for(int i=1; i<=k; i++) {
        auto curr = pq.top();
        pq.pop();
        totalTime += times[curr.second];
        pq.push({curr.first + times[curr.second], curr.second});
    }
    totalTime += times[pq.top().second];
    return totalTime;
}

int main() {
    int n = 3;
    int times[3];
    times[0] = 3;
    times[1] = 2;
    times[2] = 5;
    int k = 4;

    cout << solve(times, n, k);
}