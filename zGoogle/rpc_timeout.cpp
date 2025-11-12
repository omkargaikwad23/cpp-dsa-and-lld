#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// https://leetcode.com/discuss/interview-question/924141/google-phone-screen-new-grad

/*
You have a stream of rpc requests coming in. Each log is of the form {id, timestamp, type(start/end)}. Given a timeout T, you need to figure out at the earliest possible time if a request has timed out.
Eg :
id - time - type
0 - 0 - Start
1 - 1 - Start
0 - 2 - End
2 - 6 - Start
1 - 7 - End

Timeout = 3

Ans : {1, 6} ( figured out id 1 had timed out at time 6 )
(Only 1 request (id=1) times out at time 6.)


it only checks when new log coming in.
there is no log coming in between 2-6, so first time found id 1 expired are at timestamp 6.
*/



struct Request {
    int id;
    int time;
    string type;

    Request(int _id, int _time, string _type) {
        id = _id;
        time = _time;
        type = _type;
    }
};

vector<pair<int, int>> requestTimeout(vector<Request> &logs, int timeout) {
    unordered_map<int, int> startTimes; // id -> start time
    queue<int> q; // order of starts
    vector<pair<int, int>> ans; // store all (id, timeout detected time)

    for (auto &log : logs) {
        // Before processing new log, check if any request has timed out
        while (!q.empty() && (log.time - startTimes[q.front()] > timeout)) {
            ans.push_back({q.front(), log.time});
            startTimes.erase(q.front());
            q.pop();
        }

        if (log.type == "Start") {
            startTimes[log.id] = log.time;
            q.push(log.id);
        } else if (log.type == "End") {
            if (startTimes.count(log.id)) {
                if (!q.empty() && q.front() == log.id) {
                    q.pop();
                }
                startTimes.erase(log.id);
            }
        }
    }

    // After all logs processed, check remaining pending starts
    // (Use final time + timeout or decide policy based on interview context. Here, no extra timeout check.)

    return ans;
}

int main() {
    vector<Request> logs = {
        {0, 0, "Start"},
        {1, 1, "Start"},
        {0, 2, "End"},
        {2, 6, "Start"},
        {1, 7, "End"}
    };

    int timeout = 3;
    auto ans = requestTimeout(logs, timeout);

    for (auto &p : ans) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}
