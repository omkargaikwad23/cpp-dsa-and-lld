/*
https://leetcode.com/discuss/post/1717614/google-phone-screen-swe-l3-gmail-label-s-hho8/

Question: Convert an array of email folder objects to an array of Gmail label strings.

// Sample input:

folders = [
    {id: 27, parentId: 15, name: 'projects'},
    {id: 81, parentId: 27, name: 'novel'},
    {id: 15, parentId: 0, name: 'personal'}, // a parentId of 0 means root
    {id: 35, parentId: 27, name: 'blog'},
]

1. create adj list
2. start bfs/dfs from 0

// Sample output:

labels = [
    'personal/projects', 0 -> 27
    'personal/projects/novel', 0 -> 27 -> 81
    'personal', -> 0
    'personal/projects/blog', 0 -> 27 -> 35
]
*/

#include <iostream>
#include <iterator>
#include <map>

using namespace std;

class Solution {


    
};