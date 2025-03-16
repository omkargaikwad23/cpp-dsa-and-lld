/*
There's this text log file (single file) that contains a chat transcript of a chat room (can have multiple people talking).
Something like the following -

10:00 <alice> Hi! What's up?
10:01 <bob> Hey
10:03 <alice> Dinner?
10:04 <john> I'm down! But only if it isn't vegan.
.
.
.... could be more entries

You have to parse this file. And store data into a DS of your choice. Furthermore, we want to know the top n number of most talkative people. You would return that in a DS of your choice again, which must contain the top n people's usernames and the number of words they have typed out per the transcript.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to count words in a message using stringstream
int countWords(const string& message) {
    stringstream ss(message);
    string word;
    int count = 0;
    while (ss >> word) {
        count++;
    }
    return count;
}

// Comparator to sort users based on word count, descending
bool compareByWordCount(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}

vector<pair<string, int>> findTopTalkativeUsers(const string& filePath, int n) {
    ifstream chatFile(filePath);
    if (!chatFile.is_open()) {
        cerr << "Error opening file: " << filePath << endl;
        return {};
    }

    unordered_map<string, int> wordCounts;
    string line;

    while (getline(chatFile, line)) {
        size_t userStartPos = line.find('<') + 1;
        size_t userEndPos = line.find('>');

        if (userStartPos == string::npos || userEndPos == string::npos || userStartPos >= userEndPos) {
            continue;
        }

        string username = line.substr(userStartPos, userEndPos - userStartPos);
        string message = line.substr(userEndPos + 1);
        wordCounts[username] += countWords(message);
    }
    chatFile.close();

    // Convert map to vector for sorting
    vector<pair<string, int>> sortedUsers(wordCounts.begin(), wordCounts.end());

    // Sort users by word count in descending order and take the top n users
    partial_sort(sortedUsers.begin(), sortedUsers.begin() + n, sortedUsers.end(), compareByWordCount);

    // If fewer users than n, resize accordingly
    if (n < sortedUsers.size()) {
        sortedUsers.resize(n);
    }

    return sortedUsers;
}

int main() {
    string filePath = "chat_log.txt"; // Path to your large chat log file
    int topN = 2; // Example: Find top 2 talkative users

    vector<pair<string, int>> topUsers = findTopTalkativeUsers(filePath, topN);

    // Print result
    cout << "Top " << topN << " talkative users:" << endl;
    for (const auto& user : topUsers) {
        cout << user.first << ": " << user.second << " words" << endl;
    }

    return 0;
}