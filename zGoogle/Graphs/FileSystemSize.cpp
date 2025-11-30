/*
You have a file system represented as a Python dictionary. Each node is either a file or a directory. Directories can contain other directories or files as children. For example:
fs = { 
    1: { type=directory, name=“root", children=[2, 3] }, 
    2: { type=directory, name=“dir", children=[4, 5] }, 
    4: { type=file, name=“file1", size=100 }, 
    5: { type=file, name=“file2", size=200 }, 
    3: { type=file, name=“file3", size=300 } 
}
Tasks:
Write a function get_size() that returns the total size of for a key
How to optimise the size calculation with caching if needed
Discussion about what is expected from a typical filesystem. I could come up with the following -
No cycles: a directory cannot include itself directly or indirectly
Every file belongs to at least one directory
No two directories share the same child
No directory contains a non-existent child key

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <stack>
#include <string>

using namespace std;


int get_size(unordered_map<int, pair<string, vector<int>>> &fs, int key) {
    if(fs[key].first == "file") {
        return fs[key].second[0];
    }
    int size = 0;
    for(int child : fs[key].second) {
        size += get_size(fs, child);
    }
    return size;
}

int main() {
    unordered_map<int, pair<string, vector<int>>> fs = {
        {1, {"directory", {2, 3}}},
        {2, {"directory", {4, 5}}},
        {4, {"file", {100}}},
        {5, {"file", {200}}},
        {3, {"file", {300}}},
    };
    cout << get_size(fs, 1) << endl;
    return 0;
}