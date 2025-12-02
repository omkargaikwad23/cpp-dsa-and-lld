/*
================================================================================
                    PATTERN 11: CATALAN NUMBERS
================================================================================

When to use:
- Counting valid parentheses
- Counting BSTs with n nodes
- Polygon triangulation
- Non-crossing partitions

Catalan: C(n) = C(0)*C(n-1) + C(1)*C(n-2) + ... + C(n-1)*C(0)
Formula: C(n) = (2n)! / ((n+1)! * n!)

LeetCode Problems:
- 96. Unique Binary Search Trees
- 22. Generate Parentheses

================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
CATALAN NUMBERS SEQUENCE
─────────────────────────
C(0) = 1
C(1) = 1
C(2) = 2
C(3) = 5
C(4) = 14
C(5) = 42
C(6) = 132
...

Applications:
- Number of BSTs with n nodes
- Number of valid parentheses with n pairs
- Number of ways to triangulate n+2 sided polygon
- Number of paths in n x n grid staying below diagonal
*/

// Generate Catalan numbers
vector<long long> generateCatalan(int n) {
    vector<long long> catalan(n + 1);
    catalan[0] = catalan[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += catalan[j] * catalan[i - 1 - j];
        }
    }
    
    return catalan;
}


/*
PROBLEM 1: Unique Binary Search Trees (LeetCode 96) ⭐
─────────────────────────────────────────────────────
Count structurally unique BSTs with nodes 1 to n.

G(n) = Σ G(i-1) * G(n-i) for i = 1 to n
This is the Catalan number!

Time: O(n²) | Space: O(n)
*/
int numTrees(int n) {
    vector<int> dp(n + 1, 0);
    dp[0] = dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] += dp[j - 1] * dp[i - j];
        }
    }
    
    return dp[n];
}


/*
PROBLEM 2: Unique Binary Search Trees II (LeetCode 95)
──────────────────────────────────────────────────────
Generate all structurally unique BSTs.

Time: O(n * C(n)) | Space: O(n * C(n))
*/
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<TreeNode*> generateTrees(int n) {
    if (n == 0) return {};
    
    function<vector<TreeNode*>(int, int)> build = [&](int lo, int hi) -> vector<TreeNode*> {
        if (lo > hi) return {nullptr};
        
        vector<TreeNode*> result;
        
        for (int i = lo; i <= hi; i++) {
            for (TreeNode* left : build(lo, i - 1)) {
                for (TreeNode* right : build(i + 1, hi)) {
                    TreeNode* root = new TreeNode(i);
                    root->left = left;
                    root->right = right;
                    result.push_back(root);
                }
            }
        }
        
        return result;
    };
    
    return build(1, n);
}


/*
PROBLEM 3: Generate Parentheses (LeetCode 22) ⭐ CLASSIC
───────────────────────────────────────────────────────
Generate all valid combinations of n pairs of parentheses.

Backtracking with open/close count tracking.

Time: O(4^n / sqrt(n)) ~ C(n) | Space: O(n)
*/
vector<string> generateParenthesis(int n) {
    vector<string> result;
    
    function<void(string&, int, int)> backtrack = [&](string& curr, int open, int close) {
        if (curr.size() == 2 * n) {
            result.push_back(curr);
            return;
        }
        
        if (open < n) {
            curr.push_back('(');
            backtrack(curr, open + 1, close);
            curr.pop_back();
        }
        
        if (close < open) {
            curr.push_back(')');
            backtrack(curr, open, close + 1);
            curr.pop_back();
        }
    };
    
    string s;
    backtrack(s, 0, 0);
    return result;
}


/*
PROBLEM 4: Different Ways to Add Parentheses (LeetCode 241)
───────────────────────────────────────────────────────────
Compute all possible results from expression with different groupings.

Time: O(C(n) * n) | Space: O(C(n))
*/
vector<int> diffWaysToCompute(string expression) {
    unordered_map<string, vector<int>> memo;
    
    function<vector<int>(string)> compute = [&](string expr) -> vector<int> {
        if (memo.count(expr)) return memo[expr];
        
        vector<int> result;
        
        for (int i = 0; i < expr.size(); i++) {
            char c = expr[i];
            if (c == '+' || c == '-' || c == '*') {
                vector<int> left = compute(expr.substr(0, i));
                vector<int> right = compute(expr.substr(i + 1));
                
                for (int l : left) {
                    for (int r : right) {
                        if (c == '+') result.push_back(l + r);
                        else if (c == '-') result.push_back(l - r);
                        else result.push_back(l * r);
                    }
                }
            }
        }
        
        if (result.empty()) {
            result.push_back(stoi(expr));
        }
        
        return memo[expr] = result;
    };
    
    return compute(expression);
}


/*
PROBLEM 5: Valid Parenthesis String (LeetCode 678)
──────────────────────────────────────────────────
'*' can be '(', ')', or empty. Check if valid.

Time: O(n) | Space: O(1)
*/
bool checkValidString(string s) {
    int minOpen = 0, maxOpen = 0;
    
    for (char c : s) {
        if (c == '(') {
            minOpen++;
            maxOpen++;
        } else if (c == ')') {
            minOpen = max(0, minOpen - 1);
            maxOpen--;
        } else {  // '*'
            minOpen = max(0, minOpen - 1);
            maxOpen++;
        }
        
        if (maxOpen < 0) return false;
    }
    
    return minOpen == 0;
}


/*
PROBLEM 6: Score of Parentheses (LeetCode 856)
──────────────────────────────────────────────
() = 1, AB = A + B, (A) = 2 * A

Time: O(n) | Space: O(n)
*/
int scoreOfParentheses(string s) {
    stack<int> stk;
    stk.push(0);
    
    for (char c : s) {
        if (c == '(') {
            stk.push(0);
        } else {
            int inner = stk.top(); stk.pop();
            int outer = stk.top(); stk.pop();
            stk.push(outer + max(1, 2 * inner));
        }
    }
    
    return stk.top();
}


/*
PROBLEM 7: Remove Invalid Parentheses (LeetCode 301)
────────────────────────────────────────────────────
Remove minimum parentheses to make valid.

BFS level by level.

Time: O(2^n) | Space: O(2^n)
*/
vector<string> removeInvalidParentheses(string s) {
    auto isValid = [](const string& str) {
        int count = 0;
        for (char c : str) {
            if (c == '(') count++;
            else if (c == ')') count--;
            if (count < 0) return false;
        }
        return count == 0;
    };
    
    vector<string> result;
    unordered_set<string> visited;
    queue<string> q;
    
    q.push(s);
    visited.insert(s);
    bool found = false;
    
    while (!q.empty()) {
        string curr = q.front();
        q.pop();
        
        if (isValid(curr)) {
            result.push_back(curr);
            found = true;
        }
        
        if (found) continue;  // Only need shortest removals
        
        for (int i = 0; i < curr.size(); i++) {
            if (curr[i] != '(' && curr[i] != ')') continue;
            
            string next = curr.substr(0, i) + curr.substr(i + 1);
            if (!visited.count(next)) {
                visited.insert(next);
                q.push(next);
            }
        }
    }
    
    return result;
}


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Catalan Numbers ===\n\n";
    
    // Catalan sequence
    auto catalan = generateCatalan(10);
    cout << "Catalan numbers: ";
    for (int i = 0; i <= 10; i++) cout << catalan[i] << " ";
    cout << "\n\n";
    
    // Unique BSTs
    cout << "1. Unique BSTs (n=3): " << numTrees(3) << "\n";
    
    // Generate Parentheses
    auto parens = generateParenthesis(3);
    cout << "3. Parentheses (n=3): " << parens.size() << " combinations\n";
    
    // Different Ways
    auto ways = diffWaysToCompute("2*3-4*5");
    cout << "4. Ways to compute '2*3-4*5': " << ways.size() << " results\n";
    
    // Valid Parenthesis String
    cout << "5. '(*)' valid: " << (checkValidString("(*)") ? "Yes" : "No") << "\n";
    
    // Score of Parentheses
    cout << "6. Score of '(()(()))': " << scoreOfParentheses("(()(()))") << "\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

CATALAN NUMBER: C(n) = Σ C(i) * C(n-1-i) for i = 0 to n-1

APPLICATIONS:
+───────────────────────────────+────────────────────────────────────────────────+
| Problem                       | Connection to Catalan                          |
+───────────────────────────────+────────────────────────────────────────────────+
| Unique BSTs                   | C(n) = trees with n nodes                      |
| Valid Parentheses             | C(n) = valid strings with n pairs              |
| Polygon Triangulation         | C(n-2) = ways to triangulate n-gon             |
| Grid Paths Below Diagonal     | C(n) = monotonic paths                         |
| Non-crossing Partitions       | C(n) = non-crossing partitions                 |
+───────────────────────────────+────────────────────────────────────────────────+

================================================================================
*/

