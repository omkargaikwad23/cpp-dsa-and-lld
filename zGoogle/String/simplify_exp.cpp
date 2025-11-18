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
    // Map to store coefficient for each variable
    map<char, int> freq;
    
    // Track if we're inside parentheses with a minus sign before it
    bool isMinus = false;
    
    // Track current sign (true = positive, false = negative)
    bool isPlus = true;

    for(int i = 0; i < s.size(); i++) {
        char ch = s[i];
        
        // If it's a variable (alphanumeric), update its frequency
        if(isalnum(ch)) {
            bool currentSign = isPlus;
            // If inside parentheses with minus, all variables should be negated
            if(isMinus) {
                if(i > 0 && s[i-1] == '(') {
                    // First variable after '(': treat as positive (implicit +) then negate
                    // because of the '-' before parentheses
                    currentSign = false;  // Always negative
                }
                // For subsequent variables, isPlus already reflects the flipped operator signs
            }
            freq[ch] += currentSign ? 1 : -1;
        }
        else {
            // Handle parentheses: check if minus sign is before '('
            if(ch == '(') {
                if(i != 0 && s[i-1] == '-') {
                    isMinus = true;  // Mark that we need to flip signs inside
                }
            }
            else if(ch == ')') {
                isMinus = false;  // Reset when closing parentheses
            }
            // Handle operators
            else if(ch == '+') {
                isPlus = true;
                // If inside parentheses with minus, flip the sign
                if(isMinus) {
                    isPlus = false;  // '+' becomes '-' when negated
                }
            }
            else if(ch == '-') {
                isPlus = false;
                // If inside parentheses with minus, flip the sign
                if(isMinus) {
                    isPlus = true;  // '-' becomes '+' when negated
                }
            }
        }
    }
    
    // Build the simplified expression string
    string ans = "";
    for(auto itr : freq) {
        char ch = itr.first;
        int num = itr.second;
        
        // Skip variables with zero coefficient
        if(num == 0) continue;

        // Add sign
        if(num < 0) {
            ans += '-';
        }
        else {
            ans += '+';
        }
        
        // Remove leading '+' sign
        if(ans.size() == 1 && ans.back() == '+') {
            ans.pop_back();
        }
        
        // Add coefficient if it's not 1 or -1
        if(abs(num) > 1) {
            ans += to_string(abs(num));
        }
        
        // Add the variable
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
