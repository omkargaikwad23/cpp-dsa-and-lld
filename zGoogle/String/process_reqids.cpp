/*
https://leetcode.com/discuss/post/5386347/google-phone-screen-l3-l4-by-anonymous_u-a6cm/

You have a series of log entries indicating the start and finish times of various requests. Each log entry consists of a time and a request ID. For instance:


01234567 
Start(1, req1)
Finish(2, req1)
Start(3, req2)
Start(4, req3)
Start(5, req4)
Finish(6, req4)
Finish(7, req3)
Finish(8, req2)

Your task is to process these log entries and produce an output string that indicates the start and end times for each request. The output should be sorted by the finish times of the requests. The format should be:

omkar@L1819 design % g++ -std=c++11 process_reqids.cpp -o process_reqids
omkar@L1819 design % ./process_reqids                                   
req1 started at 1 and ended at 2
req4 started at 5 and ended at 6
req3 started at 4 and ended at 7
req2 started at 3 and ended at 8
*/
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Log {
    int endTime;
    int startTime;
    string reqId;
};

class ProcessLogRequests {
    map<string, int> reqLog;  // Map to store start times temporarily
    vector<Log> logs;         // Vector to store completed logs

public:
    void processLogs(const string &filepath) {
        ifstream inFile(filepath);
        if (!inFile.is_open()) {
            cerr << "Failed to open file: " << filepath << endl;
            return;
        }

        string line;
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            size_t openIndex = line.find('(');
            size_t commaIndex = line.find(',');

            int timestamp = stoi(line.substr(openIndex + 1, commaIndex - openIndex - 1));
            string reqId = line.substr(commaIndex + 2);
            reqId.pop_back();  // Remove closing bracket

            if (line[0] == 'S') {  // line represents Start
                reqLog[reqId] = timestamp;
            } else if (line[0] == 'F') {  // line represents Finish
                int startTime = reqLog[reqId];
                int endTime = timestamp;
                logs.push_back(Log{endTime, startTime, reqId});
            }
        }
        inFile.close();
    }

    void printLogs() {
        sort(logs.begin(), logs.end(), [](const Log &l1, const Log &l2) {
            return l1.endTime < l2.endTime;
        });

        for (const auto &log : logs) {
            cout << log.reqId << " started at " << log.startTime << " and ended at " << log.endTime << endl;
        }
    }
};

int main() {
    string path = "/Users/omkar/Dropbox/System-Design-DSA/zGoogle/design/requestid_logs.txt";
    ProcessLogRequests plr;
    plr.processLogs(path);
    plr.printLogs();
}