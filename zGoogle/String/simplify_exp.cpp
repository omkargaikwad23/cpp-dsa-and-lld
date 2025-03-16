

#include <iostream>
#include <map>
using namespace std;

//a+b+a+c-b-b-b+(d+c) => 2a-2b+2c+d


void solve(string &s) {
    
    map<char, int> freq;
    int isMinus = false;
    bool isPlus = true;

    for(int i=0; i<s.size(); i++) {
        char ch = s[i];
        if(isalnum(ch)) {
            freq[ch] += isPlus ? 1 : -1;
        }
        else {
            if(ch == '(') {
                if(i!=0 && s[i-1] == '-')
                    isMinus = true;
            }
            else if(ch == ')') {
                isMinus = false;
            }
            else if(ch == '+') {
                isPlus = true;
            }
            else {
                isPlus = false;
            }
            if(isMinus) isPlus = !isPlus;
        }
    }
    string ans = "";
    for(auto itr : freq) {
        char ch = itr.first;
        int num = itr.second;

        if(num < 0) {
            ans += '-';
        }
        else {
            ans += '+';
        }
        if(ans.size() == 1 && ans.back() == '+') ans.pop_back(); //remove if first char is '+'
        if(abs(num) > 1)
            ans += to_string(abs(num));
        ans += ch;
    }

    cout << ans << endl;
}

int main(){
    string s = "a+b+a+c-b-b-b+(d+c)";
    solve(s);
}
/*
To run:
omkar@L1819 System-Design-DSA % g++ -std=c++11 code.cpp -o code  
omkar@L1819 System-Design-DSA % ./code   
*/
