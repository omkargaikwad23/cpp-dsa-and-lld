/*
================================================================================
                  STACK - EXPRESSION EVALUATION
================================================================================

Pattern 1: Evaluate Postfix (Reverse Polish Notation)
Pattern 2: Infix to Postfix Conversion
Pattern 3: Basic Calculator Problems
Pattern 4: Evaluate Expression with Variables

================================================================================
                        EXPRESSION NOTATIONS
================================================================================

INFIX:    a + b * c       (operators between operands) - Human readable
PREFIX:   + a * b c       (operators before operands)  - Polish Notation
POSTFIX:  a b c * +       (operators after operands)   - Reverse Polish

Why Postfix?
- No parentheses needed
- No operator precedence issues
- Easy to evaluate with stack (computers prefer this!)

================================================================================
*/

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <cctype>
using namespace std;

/*
================================================================================
PATTERN 1: EVALUATE POSTFIX (Reverse Polish Notation)
================================================================================
LeetCode: 150. Evaluate Reverse Polish Notation

Algorithm:
1. For each token:
   - If operand: push to stack
   - If operator: pop two operands, apply operator, push result

Time: O(n), Space: O(n)
*/
int evalRPN(vector<string>& tokens) {
    stack<long long> stk;
    
    for (const string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            long long b = stk.top(); stk.pop();
            long long a = stk.top(); stk.pop();
            
            if (token == "+") stk.push(a + b);
            else if (token == "-") stk.push(a - b);
            else if (token == "*") stk.push(a * b);
            else stk.push(a / b);  // Truncate towards zero
        } else {
            stk.push(stoll(token));
        }
    }
    
    return stk.top();
}
/*
Example: ["2", "1", "+", "3", "*"]
Stack:  [2] -> [2,1] -> [3] -> [3,3] -> [9]
Explanation: ((2 + 1) * 3) = 9
*/


/*
================================================================================
PATTERN 2: INFIX TO POSTFIX CONVERSION
================================================================================

Algorithm (Shunting Yard):
1. Scan left to right
2. If operand: add to output
3. If '(': push to stack
4. If ')': pop to output until '('
5. If operator:
   - Pop higher/equal precedence operators to output
   - Push current operator
6. Pop remaining operators to output

Operator Precedence:
  ^     : 3 (highest, right associative)
  * /   : 2
  + -   : 1
  ( )   : 0 (lowest)
*/
int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isRightAssociative(char op) {
    return op == '^';
}

string infixToPostfix(string infix) {
    stack<char> stk;
    string postfix;
    
    for (char c : infix) {
        // Operand
        if (isalnum(c)) {
            postfix += c;
        }
        // Left parenthesis
        else if (c == '(') {
            stk.push(c);
        }
        // Right parenthesis
        else if (c == ')') {
            while (!stk.empty() && stk.top() != '(') {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();  // Remove '('
        }
        // Operator
        else {
            while (!stk.empty() && stk.top() != '(' &&
                   (precedence(stk.top()) > precedence(c) ||
                    (precedence(stk.top()) == precedence(c) && !isRightAssociative(c)))) {
                postfix += stk.top();
                stk.pop();
            }
            stk.push(c);
        }
    }
    
    // Pop remaining operators
    while (!stk.empty()) {
        postfix += stk.top();
        stk.pop();
    }
    
    return postfix;
}
/*
Example: "a+b*(c^d-e)^(f+g*h)-i"
Postfix: "abcd^e-fgh*+^*+i-"
*/


/*
================================================================================
PATTERN 3: BASIC CALCULATOR PROBLEMS
================================================================================
*/

// 3.1 BASIC CALCULATOR II (No parentheses, + - * /)
// LeetCode: 227. Basic Calculator II
int calculate2(string s) {
    stack<long long> stk;
    long long num = 0;
    char op = '+';
    
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }
        
        // Process when we hit an operator or end of string
        if ((!isdigit(c) && c != ' ') || i == s.size() - 1) {
            if (op == '+') stk.push(num);
            else if (op == '-') stk.push(-num);
            else if (op == '*') {
                long long top = stk.top(); stk.pop();
                stk.push(top * num);
            }
            else if (op == '/') {
                long long top = stk.top(); stk.pop();
                stk.push(top / num);
            }
            
            op = c;
            num = 0;
        }
    }
    
    // Sum up all values
    long long result = 0;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }
    
    return result;
}
// "3+2*2" -> 7, " 3/2 " -> 1, " 3+5 / 2 " -> 5


// 3.2 BASIC CALCULATOR (With parentheses, + - only)
// LeetCode: 224. Basic Calculator
int calculate(string s) {
    stack<int> nums;    // Store results before parenthesis
    stack<int> signs;   // Store signs before parenthesis
    
    int result = 0;
    int num = 0;
    int sign = 1;
    
    for (char c : s) {
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }
        else if (c == '+') {
            result += sign * num;
            num = 0;
            sign = 1;
        }
        else if (c == '-') {
            result += sign * num;
            num = 0;
            sign = -1;
        }
        else if (c == '(') {
            // Save current state
            nums.push(result);
            signs.push(sign);
            result = 0;
            sign = 1;
        }
        else if (c == ')') {
            result += sign * num;
            num = 0;
            // Restore previous state
            result = nums.top() + signs.top() * result;
            nums.pop();
            signs.pop();
        }
    }
    
    result += sign * num;
    return result;
}
// "(1+(4+5+2)-3)+(6+8)" -> 23


// 3.3 BASIC CALCULATOR III (Full: parentheses + all operators)
// LeetCode: 772. Basic Calculator III (Premium)
int calculate3(string s) {
    int i = 0;
    return parseExpr(s, i);
}

int parseExpr(string& s, int& i) {
    stack<long long> stk;
    long long num = 0;
    char op = '+';
    
    while (i < s.size()) {
        char c = s[i];
        
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }
        else if (c == '(') {
            i++;  // Skip '('
            num = parseExpr(s, i);  // Recursively evaluate
        }
        
        if ((!isdigit(c) && c != ' ' && c != '(') || i == s.size() - 1) {
            if (op == '+') stk.push(num);
            else if (op == '-') stk.push(-num);
            else if (op == '*') {
                long long top = stk.top(); stk.pop();
                stk.push(top * num);
            }
            else if (op == '/') {
                long long top = stk.top(); stk.pop();
                stk.push(top / num);
            }
            
            op = c;
            num = 0;
            
            if (c == ')') {
                break;  // Return to caller
            }
        }
        
        i++;
    }
    
    long long result = 0;
    while (!stk.empty()) {
        result += stk.top();
        stk.pop();
    }
    
    return result;
}


/*
================================================================================
PATTERN 4: EVALUATE WITH VARIABLES / CUSTOM OPERATORS
================================================================================
*/

// 4.1 EVALUATE EXPRESSION (Given variable values)
int evaluateExpression(string expr, unordered_map<char, int>& vars) {
    // First convert to postfix
    string postfix = infixToPostfix(expr);
    
    // Then evaluate
    stack<int> stk;
    
    for (char c : postfix) {
        if (isalpha(c)) {
            stk.push(vars[c]);
        }
        else if (isdigit(c)) {
            stk.push(c - '0');
        }
        else {
            int b = stk.top(); stk.pop();
            int a = stk.top(); stk.pop();
            
            if (c == '+') stk.push(a + b);
            else if (c == '-') stk.push(a - b);
            else if (c == '*') stk.push(a * b);
            else if (c == '/') stk.push(a / b);
            else if (c == '^') stk.push(pow(a, b));
        }
    }
    
    return stk.top();
}


// 4.2 CHECK IF EXPRESSION IS VALID
bool isValidExpression(string s) {
    int balance = 0;
    bool lastWasOperator = true;  // Expression starts like after operator
    
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        
        if (c == ' ') continue;
        
        if (c == '(') {
            balance++;
            lastWasOperator = true;
        }
        else if (c == ')') {
            balance--;
            if (balance < 0 || lastWasOperator) return false;
            lastWasOperator = false;
        }
        else if (isdigit(c) || isalpha(c)) {
            lastWasOperator = false;
            // Skip remaining digits
            while (i + 1 < s.size() && (isdigit(s[i+1]) || isalpha(s[i+1]))) {
                i++;
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (lastWasOperator && c != '-' && c != '+') return false;  // Allow unary +/-
            lastWasOperator = true;
        }
    }
    
    return balance == 0 && !lastWasOperator;
}


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Expression Evaluation ===\n\n";
    
    // Evaluate RPN
    cout << "--- Evaluate Postfix (RPN) ---" << endl;
    vector<string> rpn = {"2", "1", "+", "3", "*"};
    cout << "[2,1,+,3,*] = " << evalRPN(rpn) << endl;  // 9
    
    rpn = {"4", "13", "5", "/", "+"};
    cout << "[4,13,5,/,+] = " << evalRPN(rpn) << endl;  // 6
    
    // Infix to Postfix
    cout << "\n--- Infix to Postfix ---" << endl;
    cout << "a+b*c -> " << infixToPostfix("a+b*c") << endl;  // abc*+
    cout << "(a+b)*c -> " << infixToPostfix("(a+b)*c") << endl;  // ab+c*
    cout << "a+b*(c^d-e) -> " << infixToPostfix("a+b*(c^d-e)") << endl;
    
    // Basic Calculator II
    cout << "\n--- Basic Calculator II ---" << endl;
    cout << "\"3+2*2\" = " << calculate2("3+2*2") << endl;  // 7
    cout << "\" 3/2 \" = " << calculate2(" 3/2 ") << endl;  // 1
    cout << "\" 3+5 / 2 \" = " << calculate2(" 3+5 / 2 ") << endl;  // 5
    
    // Basic Calculator
    cout << "\n--- Basic Calculator ---" << endl;
    cout << "\"(1+(4+5+2)-3)+(6+8)\" = " << calculate("(1+(4+5+2)-3)+(6+8)") << endl;  // 23
    cout << "\" 2-1 + 2 \" = " << calculate(" 2-1 + 2 ") << endl;  // 3
    
    // Evaluate with variables
    cout << "\n--- Evaluate with Variables ---" << endl;
    unordered_map<char, int> vars = {{'a', 2}, {'b', 3}, {'c', 4}};
    cout << "a+b*c (a=2, b=3, c=4) = " << evaluateExpression("a+b*c", vars) << endl;  // 14
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

EXPRESSION EVALUATION STRATEGY:
1. Infix (human) -> Postfix (computer-friendly) using Shunting Yard
2. Evaluate Postfix using stack

CALCULATOR PROBLEMS APPROACH:
- Use stack to handle order of operations
- For parentheses: save state, process inner, restore state
- Handle operators by precedence: process *, / immediately

┌─────────────────────────────┬───────────────────────────────────────────────┐
│ Problem                     │ Key Approach                                  │
├─────────────────────────────┼───────────────────────────────────────────────┤
│ Evaluate RPN                │ Push nums, pop 2 on operator, push result     │
│ Infix to Postfix            │ Shunting Yard algorithm                       │
│ Calculator II (no parens)   │ Handle *, / immediately, save +, -            │
│ Calculator (with parens)    │ Save/restore state at parentheses             │
│ Calculator III              │ Recursive for parentheses + operator handling │
└─────────────────────────────┴───────────────────────────────────────────────┘

================================================================================
*/

