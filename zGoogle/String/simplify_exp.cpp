#include <iostream>
#include <map>
#include <cctype>
using namespace std;

/*
 * PROBLEM: Simplify Algebraic Expression
 * =======================================
 * 
 * Given an algebraic expression string containing variables, '+' and '-' operators,
 * and parentheses, simplify it by combining like terms.
 * 
 * Rules:
 * 1. Combine like terms (same variables)
 * 2. Handle parentheses: if there's a '-' before '(', flip all signs inside parentheses
 * 3. Output format: combine coefficients, omit coefficient 1, order alphabetically
 * 
 * Examples:
 * 
 * Input:  "a+b+a+c-b-b-b+(d+c)"
 * Output: "2a-2b+2c+d"
 * Explanation:
 *   - a appears twice: +a +a = 2a
 *   - b appears four times: +b -b -b -b = -2b
 *   - c appears twice: +c +c = 2c (inside parentheses, but no minus before it)
 *   - d appears once: +d = d
 * 
 * Input:  "a+b-(c+d)"
 * Output: "a+b-c-d"
 * Explanation:
 *   - Minus before parentheses flips signs: -(c+d) becomes -c-d
 * 
 * Input:  "x-y+z-x+y"
 * Output: "z"
 * Explanation:
 *   - x: +x -x = 0 (omitted)
 *   - y: -y +y = 0 (omitted)
 *   - z: +z = z
 * 
 * Algorithm:
 * 1. Track sign (positive/negative) as we traverse the string
 * 2. If '-' appears before '(', flip signs inside parentheses
 * 3. Count frequency of each variable with appropriate sign
 * 4. Format output: combine coefficients, sort alphabetically
 */

 void solve(string &s) {
    map<char, int> freq;
    stack<int> signStack; // stack to track the sign of the current term
    signStack.push(1);  // Global sign multiplier
    int sign = 1;       // Current term's sign
    
    for(int i = 0; i < s.size(); i++) {
        char ch = s[i];
        
        // if the character is a variable, add it to the frequency map with the sign of the current term
        if(isalnum(ch)) {
            // Add variable with sign = current sign × stack top
            freq[ch] += sign * signStack.top();
            sign = 1;  // Reset for next term
        }
        else if(ch == '+') {
            sign = 1;
        }
        else if(ch == '-') {
            sign = -1;
        }
        else if(ch == '(') {
            // Push cumulative sign effect for this parenthesis level
            signStack.push(sign * signStack.top());
            sign = 1;  // Reset for first term in parentheses
        }
        else if(ch == ')') {
            signStack.pop();  // Exit this parenthesis level
        }
    }
    
    // Build result
    string ans = "";
    for(auto [ch, num] : freq) {
        if(num == 0) continue;
        
        // Add '+' for positive terms (except first)
        if(!ans.empty() && num > 0) {
            ans += '+';
        }
        
        // Add coefficient (skip if ±1)
        if(num == -1) {
            ans += '-';
        } else if(num != 1) {
            ans += to_string(num);
        }
        
        ans += ch;
    }
    
    cout << ans << endl;
}

int main() {
    // Test case 1: Basic combination with parentheses
    string s1 = "a+b+a+c-b-b-b+(d+c)";
    cout << "Input:  " << s1 << endl;
    cout << "Output: ";
    solve(s1);
    cout << "Expected: 2a-2b+2c+d\n" << endl;
    
    // Test case 2: Minus before parentheses (signs flip)
    string s2 = "a+b-(c+d)";
    cout << "Input:  " << s2 << endl;
    cout << "Output: ";
    solve(s2);
    cout << "Expected: a+b-c-d\n" << endl;
    
    // Test case 3: Terms cancel out
    string s3 = "x-y+z-x+y";
    cout << "Input:  " << s3 << endl;
    cout << "Output: ";
    solve(s3);
    cout << "Expected: z\n" << endl;
    
    return 0;
}
