#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> getDoorUsageTimes(vector<int>& arrival, vector<int>& state) {
    int n = arrival.size();
    vector<int> result(n, -1);  // Store the times at which each person crosses the door

    queue<int> entryQueue, exitQueue;
    int currentTime = 0;
    int lastState = -1;  // -1 means door was not used before
    int lastTime = -1;    // Keeps track of when the door was last used

    int i = 0;  // Pointer to iterate through the arrival list

    while (i < n || !entryQueue.empty() || !exitQueue.empty()) {
        // If there are still people in the queue, advance time if needed
        if (entryQueue.empty() && exitQueue.empty() && i < n) {
            currentTime = max(currentTime, arrival[i]);
        }

        // Add people arriving at currentTime to their respective queues
        while (i < n && arrival[i] == currentTime) {
            if (state[i] == 0)
                entryQueue.push(i);
            else
                exitQueue.push(i);
            i++;
        }

        // Decide who will use the door
        if (!exitQueue.empty() && (lastState == 1 || lastTime < currentTime || entryQueue.empty())) {
            // Person exits if:
            // - Door was last used for exiting
            // - Door was not used last second
            // - No one is waiting to enter
            int person = exitQueue.front();
            exitQueue.pop();
            result[person] = currentTime;
            lastState = 1;
        } else if (!entryQueue.empty()) {
            // Otherwise, a person enters
            int person = entryQueue.front();
            entryQueue.pop();
            result[person] = currentTime;
            lastState = 0;
        }

        lastTime = currentTime;  // Update last time the door was used
        currentTime++;  // Move to the next second
    }

    return result;
}

int main() {
    vector<int> arrival = {0,1,1,2,4};
    vector<int> state = {0,1,0,0,1};

    vector<int> result = getDoorUsageTimes(arrival, state);
    for (int time : result) {
        cout << time << " ";
    }
    cout << endl;

    return 0;
}
