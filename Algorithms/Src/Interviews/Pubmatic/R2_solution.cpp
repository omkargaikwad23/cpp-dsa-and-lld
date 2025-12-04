#include <bits/stdc++.h>
using namespace std;

/*
iiidd 
1 2 5 4 3

print mini

eg: ddii
3 2 5 6


n - [1, 9]

1) solution1 : backtracking
try all possible combinations
use space to track which digit is used

2) Solution2: 

iiidd

vis = [1, 2, 3]
ans = [1, 2, 3]

val = 0;

index = 0 -> 'i'
index = 1 -> 'i' 
index = 2 -> 'i' val += 1 -> 3

index = 3 -> 'd' val-- -> 2
                 val-- -> 1

ans = [1, 2]
vis = [1, 2]

ans = [1]
vis = [1]

val += 
ans = [2]
vis = [2]
*/

void rec(string& str, int index, vector<bool>& seen, vector<int>& ans, int val){
    if(index == str.size()) return;
    
    if(str[index] == 'i'){

        while(seen[val] != false && val < 10){
            val++;
        }
        seen[val] = true;
        ans.push_back(val);

        rec(str, index+1, seen, ans, val);
    }
    else{
        while(seen[val] != false && val >= 0){
            val--;
        }
        seen[val] = true;
        ans.push_back(val);

        rec(str, index+1, seen, ans, val);
    }

}

void solve(string str){
    int n = str.size();
    vector<bool> seen(10, false);
    vector<int> ans;
    
    int val = 0;

    rec(str, 0, seen, ans, val);

}

int main()
{
    string str = "iiidd";
    solve(str);
    return 0;
}