/*
================================================================================
                    STACK - BASIC PROBLEMS
================================================================================

Pattern 1: Matching / Validation
Pattern 2: Design Problems (Min Stack, etc.)
Pattern 3: String Processing
Pattern 4: Simulation Problems

================================================================================
*/

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
using namespace std;

/*
================================================================================
PATTERN 1: MATCHING / VALIDATION
================================================================================
*/

// 1.1 VALID PARENTHESES
// LeetCode: 20. Valid Parentheses
// Time: O(n), Space: O(n)
bool isValid(string s) {
    stack<char> stk;
    unordered_map<char, char> pairs = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };
    
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            stk.push(c);
        } else {
            if (stk.empty() || stk.top() != pairs[c]) {
                return false;
            }
            stk.pop();
        }
    }
    
    return stk.empty();
}
// "()" -> true, "()[]{}" -> true, "(]" -> false


// 1.2 MINIMUM ADD TO MAKE PARENTHESES VALID
// LeetCode: 921. Minimum Add to Make Parentheses Valid
int minAddToMakeValid(string s) {
    int open = 0;   // Unmatched '('
    int close = 0;  // Unmatched ')'
    
    for (char c : s) {
        if (c == '(') {
            open++;
        } else {
            if (open > 0) {
                open--;  // Match with open
            } else {
                close++;  // Unmatched close
            }
        }
    }
    
    return open + close;
}
// "())" -> 1, "(((" -> 3, "()" -> 0


// 1.3 REMOVE INVALID PARENTHESES (Simplified - remove minimum)
// LeetCode: 1249. Minimum Remove to Make Valid Parentheses
string minRemoveToMakeValid(string s) {
    stack<int> stk;  // Indices of '('
    vector<bool> toRemove(s.size(), false);
    
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            stk.push(i);
        } else if (s[i] == ')') {
            if (stk.empty()) {
                toRemove[i] = true;  // Unmatched ')'
            } else {
                stk.pop();
            }
        }
    }
    
    // Mark unmatched '('
    while (!stk.empty()) {
        toRemove[stk.top()] = true;
        stk.pop();
    }
    
    string result;
    for (int i = 0; i < s.size(); i++) {
        if (!toRemove[i]) {
            result += s[i];
        }
    }
    
    return result;
}


// 1.4 SCORE OF PARENTHESES
// LeetCode: 856. Score of Parentheses
// () = 1, (A) = 2*A, AB = A + B
int scoreOfParentheses(string s) {
    stack<int> stk;
    stk.push(0);  // Current score at this level
    
    for (char c : s) {
        if (c == '(') {
            stk.push(0);  // New level
        } else {
            int inner = stk.top(); stk.pop();
            int outer = stk.top(); stk.pop();
            // () = 1, or (A) = 2*A
            stk.push(outer + max(2 * inner, 1));
        }
    }
    
    return stk.top();
}
// "()" -> 1, "(())" -> 2, "()()" -> 2, "(()(()))" -> 6


/*
================================================================================
PATTERN 2: DESIGN PROBLEMS
================================================================================
*/

// 2.1 MIN STACK
// LeetCode: 155. Min Stack
// All operations in O(1)
class MinStack {
private:
    stack<int> stk;
    stack<int> minStk;  // Track minimums
    
public:
    MinStack() {}
    
    void push(int val) {
        stk.push(val);
        if (minStk.empty() || val <= minStk.top()) {
            minStk.push(val);
        }
    }
    
    void pop() {
        if (stk.top() == minStk.top()) {
            minStk.pop();
        }
        stk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return minStk.top();
    }
};

// Alternative: Store pair of (value, min_at_this_point)
class MinStack2 {
private:
    stack<pair<int, int>> stk;  // {value, current_min}
    
public:
    void push(int val) {
        int newMin = stk.empty() ? val : min(val, stk.top().second);
        stk.push({val, newMin});
    }
    
    void pop() { stk.pop(); }
    int top() { return stk.top().first; }
    int getMin() { return stk.top().second; }
};


// 2.2 MAX STACK
// LeetCode: 716. Max Stack (Premium)
class MaxStack {
private:
    stack<int> stk;
    stack<int> maxStk;
    
public:
    void push(int val) {
        stk.push(val);
        int newMax = maxStk.empty() ? val : max(val, maxStk.top());
        maxStk.push(newMax);
    }
    
    int pop() {
        int val = stk.top();
        stk.pop();
        maxStk.pop();
        return val;
    }
    
    int top() { return stk.top(); }
    int peekMax() { return maxStk.top(); }
    
    // popMax() is more complex - requires different approach
};


// 2.3 IMPLEMENT QUEUE USING STACKS
// LeetCode: 232. Implement Queue using Stacks
class MyQueue {
private:
    stack<int> input;   // For push
    stack<int> output;  // For pop/peek
    
    void transfer() {
        if (output.empty()) {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
    }
    
public:
    void push(int x) {
        input.push(x);
    }
    
    int pop() {
        transfer();
        int val = output.top();
        output.pop();
        return val;
    }
    
    int peek() {
        transfer();
        return output.top();
    }
    
    bool empty() {
        return input.empty() && output.empty();
    }
};
// Amortized O(1) for all operations


// 2.4 IMPLEMENT STACK USING QUEUES
// LeetCode: 225. Implement Stack using Queues
class MyStack {
private:
    queue<int> q;
    
public:
    void push(int x) {
        q.push(x);
        // Rotate to make new element at front
        for (int i = 0; i < q.size() - 1; i++) {
            q.push(q.front());
            q.pop();
        }
    }
    
    int pop() {
        int val = q.front();
        q.pop();
        return val;
    }
    
    int top() {
        return q.front();
    }
    
    bool empty() {
        return q.empty();
    }
};
// Push: O(n), Pop/Top: O(1)


/*
================================================================================
PATTERN 3: STRING PROCESSING
================================================================================
*/

// 3.1 DECODE STRING
// LeetCode: 394. Decode String
// "3[a2[c]]" -> "accaccacc"
string decodeString(string s) {
    stack<int> countStack;
    stack<string> stringStack;
    string current = "";
    int k = 0;
    
    for (char c : s) {
        if (isdigit(c)) {
            k = k * 10 + (c - '0');
        } else if (c == '[') {
            countStack.push(k);
            stringStack.push(current);
            current = "";
            k = 0;
        } else if (c == ']') {
            string temp = current;
            current = stringStack.top(); stringStack.pop();
            int count = countStack.top(); countStack.pop();
            for (int i = 0; i < count; i++) {
                current += temp;
            }
        } else {
            current += c;
        }
    }
    
    return current;
}


// 3.2 REMOVE ALL ADJACENT DUPLICATES
// LeetCode: 1047. Remove All Adjacent Duplicates In String
string removeDuplicates(string s) {
    string result;  // Use string as stack
    
    for (char c : s) {
        if (!result.empty() && result.back() == c) {
            result.pop_back();
        } else {
            result.push_back(c);
        }
    }
    
    return result;
}
// "abbaca" -> "ca"


// 3.3 REMOVE ALL ADJACENT DUPLICATES II
// LeetCode: 1209. Remove All Adjacent Duplicates in String II
string removeDuplicates(string s, int k) {
    stack<pair<char, int>> stk;  // {char, count}
    
    for (char c : s) {
        if (!stk.empty() && stk.top().first == c) {
            stk.top().second++;
            if (stk.top().second == k) {
                stk.pop();
            }
        } else {
            stk.push({c, 1});
        }
    }
    
    string result;
    while (!stk.empty()) {
        result = string(stk.top().second, stk.top().first) + result;
        stk.pop();
    }
    
    return result;
}
// "deeedbbcccbdaa", k=3 -> "aa"


// 3.4 SIMPLIFY PATH
// LeetCode: 71. Simplify Path
string simplifyPath(string path) {
    stack<string> stk;
    stringstream ss(path);
    string token;
    
    while (getline(ss, token, '/')) {
        if (token == "" || token == ".") {
            continue;  // Ignore
        } else if (token == "..") {
            if (!stk.empty()) stk.pop();
        } else {
            stk.push(token);
        }
    }
    
    string result;
    while (!stk.empty()) {
        result = "/" + stk.top() + result;
        stk.pop();
    }
    
    return result.empty() ? "/" : result;
}
// "/a/./b/../../c/" -> "/c"


/*
================================================================================
PATTERN 4: SIMULATION PROBLEMS
================================================================================
*/

// 4.1 BASEBALL GAME
// LeetCode: 682. Baseball Game
int calPoints(vector<string>& operations) {
    stack<int> stk;
    
    for (const string& op : operations) {
        if (op == "+") {
            int top = stk.top(); stk.pop();
            int newTop = top + stk.top();
            stk.push(top);
            stk.push(newTop);
        } else if (op == "D") {
            stk.push(2 * stk.top());
        } else if (op == "C") {
            stk.pop();
        } else {
            stk.push(stoi(op));
        }
    }
    
    int sum = 0;
    while (!stk.empty()) {
        sum += stk.top();
        stk.pop();
    }
    return sum;
}


// 4.2 ASTEROID COLLISION
// LeetCode: 735. Asteroid Collision
// Positive = moving right, Negative = moving left
vector<int> asteroidCollision(vector<int>& asteroids) {
    stack<int> stk;
    
    for (int asteroid : asteroids) {
        bool destroyed = false;
        
        // Collision happens when: stack has right-moving (+) and current is left-moving (-)
        while (!stk.empty() && stk.top() > 0 && asteroid < 0) {
            if (stk.top() < -asteroid) {
                stk.pop();  // Stack asteroid destroyed
                continue;
            } else if (stk.top() == -asteroid) {
                stk.pop();  // Both destroyed
            }
            destroyed = true;
            break;
        }
        
        if (!destroyed) {
            stk.push(asteroid);
        }
    }
    
    vector<int> result(stk.size());
    for (int i = stk.size() - 1; i >= 0; i--) {
        result[i] = stk.top();
        stk.pop();
    }
    
    return result;
}
// [5, 10, -5] -> [5, 10]
// [8, -8] -> []
// [10, 2, -5] -> [10]


// 4.3 BACKSPACE STRING COMPARE
// LeetCode: 844. Backspace String Compare
bool backspaceCompare(string s, string t) {
    auto process = [](const string& str) {
        string result;
        for (char c : str) {
            if (c == '#') {
                if (!result.empty()) result.pop_back();
            } else {
                result.push_back(c);
            }
        }
        return result;
    };
    
    return process(s) == process(t);
}
// "ab#c", "ad#c" -> true (both become "ac")


// ============== MAIN - DEMO ==============
int main() {
    cout << "=== Stack Basic Problems ===\n\n";
    
    // Valid Parentheses
    cout << "--- Valid Parentheses ---" << endl;
    cout << "\"()[]{}\" is valid: " << (isValid("()[]{}") ? "Yes" : "No") << endl;
    cout << "\"(]\" is valid: " << (isValid("(]") ? "Yes" : "No") << endl;
    
    // Min Stack
    cout << "\n--- Min Stack ---" << endl;
    MinStack minStk;
    minStk.push(-2);
    minStk.push(0);
    minStk.push(-3);
    cout << "Min: " << minStk.getMin() << endl;  // -3
    minStk.pop();
    cout << "Top: " << minStk.top() << endl;      // 0
    cout << "Min: " << minStk.getMin() << endl;  // -2
    
    // Decode String
    cout << "\n--- Decode String ---" << endl;
    cout << "\"3[a2[c]]\" -> " << decodeString("3[a2[c]]") << endl;
    
    // Remove Duplicates
    cout << "\n--- Remove Duplicates ---" << endl;
    cout << "\"abbaca\" -> " << removeDuplicates("abbaca") << endl;
    
    // Score of Parentheses
    cout << "\n--- Score of Parentheses ---" << endl;
    cout << "\"(()(()))\" -> " << scoreOfParentheses("(()(()))") << endl;
    
    // Simplify Path
    cout << "\n--- Simplify Path ---" << endl;
    cout << "\"/a/./b/../../c/\" -> " << simplifyPath("/a/./b/../../c/") << endl;
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

┌───────────────────────────────┬─────────────────────────────────────────────┐
│ Pattern                       │ Key Technique                               │
├───────────────────────────────┼─────────────────────────────────────────────┤
│ Parentheses Matching          │ Push open, pop on close, check match        │
│ Min/Max Stack                 │ Secondary stack for extremes                │
│ Queue using Stacks            │ Two stacks: input + output                  │
│ Decode String                 │ Stack for counts & strings at each level    │
│ Remove Duplicates             │ Compare with stack top                      │
│ Asteroid Collision            │ Process collisions with stack top           │
└───────────────────────────────┴─────────────────────────────────────────────┘

TIP: Many string problems can use the string itself as a stack (push_back/pop_back)!

================================================================================
*/

