#include <iostream>
#include <map>
#include <stack>
using namespace std;



void solve(string s) {
    map<char, int> freq;
    stack<int> signStack;
    int currentSign = 1;  // 1 for '+', -1 for '-'
    
    signStack.push(1);  // Base sign outside any parentheses

    for(int i = 0; i < s.size(); i++) {
        char ch = s[i];

        if (isalnum(ch)) {  
            freq[ch] += currentSign;
        } 
        else if (ch == '(') {
            // Push current sign into stack
            signStack.push(currentSign);
        } 
        else if (ch == ')') {
            // Pop out the sign when closing parentheses
            signStack.pop();
        } 
        else if (ch == '+') {
            currentSign = signStack.top();  // Keep current sign
        } 
        else if (ch == '-') {
            currentSign = -signStack.top();  // Flip sign based on stack
        }
    }

    string ans = "";
    for(auto itr : freq) {
        char ch = itr.first;
        int num = itr.second;

        if(num == 0) continue;  // Skip variables with zero coefficient

        if(!ans.empty() && num > 0) ans += "+"; // Add `+` only after the first term
        if(num == -1) ans += '-';
        if(abs(num) > 1) ans += to_string(abs(num));
        ans += ch;
    }

    cout << ans << endl;
}

int main() {


    solve("a+b+a+c-b-b-b+(d+c)");  // Expected Output: "2a-2b+2c+d"
    solve("a+(a-(b+a))");
}
