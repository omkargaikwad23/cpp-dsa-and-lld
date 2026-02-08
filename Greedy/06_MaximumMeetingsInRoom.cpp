#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1

/*
You are given timings of n meetings in the form of (start[i], end[i]) where start[i] is the start time of meeting i and end[i] is the finish time of meeting i. Return the maximum number of meetings that can be accommodated in a single meeting room, when only one meeting can be held in the meeting room at a particular time. 

Note: The start time of one chosen meeting can't be equal to the end time of the other chosen meeting.

Examples :

Input: start[] = [1, 3, 0, 5, 8, 5], end[] =  [2, 4, 6, 7, 9, 9]
Output: 4
Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2), (3, 4), (5,7) and (8,9)


*/


int maxMeetings(vector<int>& start, vector<int>& end) {
    vector<pair<int,int>> slots;
    int n = start.size();
    
    // keep start, end
    for(int i=0; i<n; i++){
        slots.push_back({start[i], end[i]});
    }
    
    auto comparePair = [](const pair<int, int>& p1, const pair<int, int>& p2) {
        if (p1.second != p2.second) return p1.second < p2.second;
        return p1.first < p2.first;
    };

    sort(slots.begin(), slots.end(), comparePair);
    
   
    int ans = 0, lastEnd = -1;
    for(int i=0; i<n; i++){
        if(lastEnd < slots[i].first){ 
            ans++;
            lastEnd = slots[i].second;
        }
        
    }
    return ans;
}

int main(){

}