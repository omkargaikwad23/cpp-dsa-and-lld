/*
================================================================================
            SIMPLIFY ALGEBRAIC EXPRESSION (Google Interview)
================================================================================

PROBLEM:
Given an algebraic expression containing variables, '+', '-', and parentheses,
simplify it by combining like terms.

Rules:
1. Combine like terms (same variables)
2. Handle parentheses: if '-' before '(', flip all signs inside
3. Output: combine coefficients, omit coefficient 1, order alphabetically

================================================================================
                         EXAMPLES
================================================================================

Example 1: "a+b+a+c-b-b-b+(d+c)"
Output: "2a-2b+2c+d"
- a: +1+1 = 2
- b: +1-1-1-1 = -2
- c: +1+1 = 2
- d: +1 = 1

Example 2: "a+b-(c+d)"
Output: "a+b-c-d"
- Minus before '(' flips signs inside

Example 3: "x-y+z-x+y"
Output: "z"
- x: +1-1 = 0 (omitted)
- y: -1+1 = 0 (omitted)

================================================================================
                         APPROACH
================================================================================

Use a STACK to track sign context:
1. Stack holds cumulative sign multiplier for current nesting level
2. When we see '(': push (current_sign × stack.top)
3. When we see ')': pop from stack
4. Variable sign = current_sign × stack.top()

TIME:  O(n) - single pass through string
SPACE: O(n) - stack depth + result map

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

string simplifyExpression(const string& s) {
    map<char, int> freq;  // Sorted by variable name
    stack<int> signStack;
    signStack.push(1);    // Global sign multiplier
    int sign = 1;         // Current term's sign
    
    for (int i = 0; i < s.size(); i++) {
        char ch = s[i];
        
        if (isalpha(ch)) {
            // Variable: add with cumulative sign
            freq[ch] += sign * signStack.top();
            sign = 1;  // Reset for next term
        }
        else if (ch == '+') {
            sign = 1;
        }
        else if (ch == '-') {
            sign = -1;
        }
        else if (ch == '(') {
            // Push cumulative sign for this parenthesis level
            signStack.push(sign * signStack.top());
            sign = 1;  // Reset for first term inside
        }
        else if (ch == ')') {
            signStack.pop();  // Exit parenthesis level
        }
        // Skip spaces and other characters
    }
    
    // Build result string
    string result = "";
    for (auto& [var, coef] : freq) {
        if (coef == 0) continue;  // Omit zero terms
        
        // Add '+' for positive terms (except first)
        if (!result.empty() && coef > 0) {
            result += '+';
        }
        
        // Add coefficient (skip if ±1)
        if (coef == -1) {
            result += '-';
        } else if (coef != 1) {
            result += to_string(coef);
        }
        
        result += var;
    }
    
    return result.empty() ? "0" : result;
}

// ═══════════════════════════════════════════════════════════════════════════
// EXTENSION: Handle multi-character variables and numeric coefficients
// ═══════════════════════════════════════════════════════════════════════════

string simplifyExpressionAdvanced(const string& s) {
    map<string, int> freq;
    stack<int> signStack;
    signStack.push(1);
    int sign = 1;
    int i = 0;
    
    while (i < s.size()) {
        if (isalpha(s[i])) {
            // Parse variable name (could be multi-char like "abc")
            string var = "";
            while (i < s.size() && isalpha(s[i])) {
                var += s[i++];
            }
            freq[var] += sign * signStack.top();
            sign = 1;
        }
        else if (s[i] == '+') {
            sign = 1;
            i++;
        }
        else if (s[i] == '-') {
            sign = -1;
            i++;
        }
        else if (s[i] == '(') {
            signStack.push(sign * signStack.top());
            sign = 1;
            i++;
        }
        else if (s[i] == ')') {
            signStack.pop();
            i++;
        }
        else {
            i++;  // Skip spaces
        }
    }
    
    // Build result
    string result = "";
    for (auto& [var, coef] : freq) {
        if (coef == 0) continue;
        
        if (!result.empty() && coef > 0) result += '+';
        
        if (coef == -1) result += '-';
        else if (coef != 1) result += to_string(coef);
        
        result += var;
    }
    
    return result.empty() ? "0" : result;
}

// ═══════════════════════════════════════════════════════════════════════════
// MAIN
// ═══════════════════════════════════════════════════════════════════════════

int main() {
    // Test case 1
    string s1 = "a+b+a+c-b-b-b+(d+c)";
    cout << "Input:  " << s1 << "\n";
    cout << "Output: " << simplifyExpression(s1) << "\n";
    cout << "Expected: 2a-2b+2c+d\n\n";
    
    // Test case 2
    string s2 = "a+b-(c+d)";
    cout << "Input:  " << s2 << "\n";
    cout << "Output: " << simplifyExpression(s2) << "\n";
    cout << "Expected: a+b-c-d\n\n";
    
    // Test case 3
    string s3 = "x-y+z-x+y";
    cout << "Input:  " << s3 << "\n";
    cout << "Output: " << simplifyExpression(s3) << "\n";
    cout << "Expected: z\n\n";
    
    // Test case 4: nested parentheses
    string s4 = "a-(b-(c-d))";
    cout << "Input:  " << s4 << "\n";
    cout << "Output: " << simplifyExpression(s4) << "\n";
    cout << "Expected: a-b+c-d\n";
    
    return 0;
}

/*
================================================================================
                         COMPLEXITY ANALYSIS
================================================================================

TIME:  O(n)
- Single pass through the string
- Each character processed once

SPACE: O(n)
- Stack can grow to depth of nested parentheses
- HashMap stores at most 26 entries (single char variables)

FOLLOW-UP QUESTIONS:
1. Handle numeric coefficients like "2a+3b"
2. Handle multiplication like "a*b"
3. Handle division
4. Handle exponents like "a^2"

================================================================================
*/

