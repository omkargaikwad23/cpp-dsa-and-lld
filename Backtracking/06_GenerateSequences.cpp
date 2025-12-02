/*
================================================================================
                    BACKTRACKING - GENERATE SEQUENCES
================================================================================

Build strings/sequences satisfying specific constraints.
Time: Varies | Space: O(n)
================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
PROBLEM 1: Generate Parentheses (LeetCode 22)
─────────────────────────────────────────────
Generate all valid combinations of n pairs of parentheses.

Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Time: O(4^n / sqrt(n)) | Space: O(n)
*/
class GenerateParentheses {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        backtrack("", 0, 0, n, result);
        return result;
    }
    
private:
    void backtrack(string current, int open, int close, int n,
                   vector<string>& result) {
        if (current.size() == 2 * n) {
            result.push_back(current);
            return;
        }
        
        if (open < n) {
            backtrack(current + "(", open + 1, close, n, result);
        }
        if (close < open) {
            backtrack(current + ")", open, close + 1, n, result);
        }
    }
};


/*
PROBLEM 2: Letter Combinations of Phone Number (LeetCode 17)
────────────────────────────────────────────────────────────
Return all letter combinations from phone digits.

Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Time: O(4^n * n) | Space: O(n)
*/
class LetterCombinations {
    vector<string> mapping = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> result;
        backtrack(digits, 0, "", result);
        return result;
    }
    
private:
    void backtrack(const string& digits, int index, string current,
                   vector<string>& result) {
        if (index == digits.size()) {
            result.push_back(current);
            return;
        }
        
        for (char c : mapping[digits[index] - '0']) {
            backtrack(digits, index + 1, current + c, result);
        }
    }
};


/*
PROBLEM 3: Different Ways to Add Parentheses (LeetCode 241)
───────────────────────────────────────────────────────────
Compute all possible results from grouping expressions.

Input: expression = "2-1-1"
Output: [0,2] ((2-1)-1 = 0, 2-(1-1) = 2)

Time: O(n * 2^n) | Space: O(2^n)
*/
class DiffWaysParentheses {
public:
    vector<int> diffWaysToCompute(string expression) {
        unordered_map<string, vector<int>> memo;
        return compute(expression, memo);
    }
    
private:
    vector<int> compute(const string& expr, unordered_map<string, vector<int>>& memo) {
        if (memo.count(expr)) return memo[expr];
        
        vector<int> result;
        
        for (int i = 0; i < expr.size(); i++) {
            char c = expr[i];
            if (c == '+' || c == '-' || c == '*') {
                vector<int> left = compute(expr.substr(0, i), memo);
                vector<int> right = compute(expr.substr(i + 1), memo);
                
                for (int l : left) {
                    for (int r : right) {
                        if (c == '+') result.push_back(l + r);
                        else if (c == '-') result.push_back(l - r);
                        else result.push_back(l * r);
                    }
                }
            }
        }
        
        if (result.empty()) result.push_back(stoi(expr));  // Base: just a number
        
        memo[expr] = result;
        return result;
    }
};


/*
PROBLEM 4: Generalized Abbreviation (LeetCode 320)
──────────────────────────────────────────────────
Generate all abbreviations by replacing substrings with their lengths.

Input: word = "word"
Output: ["word","1ord","w1rd","wo1d","wor1","2rd","w2d","wo2","1o1d",...,"4"]

Time: O(n * 2^n) | Space: O(n)
*/
class GeneralizedAbbreviation {
public:
    vector<string> generateAbbreviations(string word) {
        vector<string> result;
        backtrack(word, 0, "", 0, result);
        return result;
    }
    
private:
    void backtrack(const string& word, int index, string current, int count,
                   vector<string>& result) {
        if (index == word.size()) {
            if (count > 0) current += to_string(count);
            result.push_back(current);
            return;
        }
        
        // Abbreviate current character (increment count)
        backtrack(word, index + 1, current, count + 1, result);
        
        // Keep current character (flush count first)
        string prefix = count > 0 ? current + to_string(count) : current;
        backtrack(word, index + 1, prefix + word[index], 0, result);
    }
};


/*
PROBLEM 5: Binary Watch (LeetCode 401)
──────────────────────────────────────
Return all possible times with n LEDs turned on.

Input: turnedOn = 1
Output: ["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]

Time: O(12 * 60) = O(1) | Space: O(1)
*/
vector<string> readBinaryWatch(int turnedOn) {
    vector<string> result;
    
    for (int h = 0; h < 12; h++) {
        for (int m = 0; m < 60; m++) {
            if (__builtin_popcount(h) + __builtin_popcount(m) == turnedOn) {
                result.push_back(to_string(h) + ":" + (m < 10 ? "0" : "") + to_string(m));
            }
        }
    }
    
    return result;
}


/*
PROBLEM 6: Count Numbers with Unique Digits (LeetCode 357)
──────────────────────────────────────────────────────────
Count numbers with unique digits in range [0, 10^n).

Input: n = 2
Output: 91 (0-99 excluding 11,22,33,44,55,66,77,88,99)

Approach: Math / DP is better, but backtracking works
*/
int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1;
    
    int total = 10;  // Single digit
    int available = 9, current = 9;
    
    for (int i = 2; i <= n && available > 0; i++) {
        current *= available;
        total += current;
        available--;
    }
    
    return total;
}


/*
PROBLEM 7: Generate All Binary Strings of Length N
──────────────────────────────────────────────────
Input: n = 2
Output: ["00","01","10","11"]
*/
void generateBinaryStrings(int n, string current, vector<string>& result) {
    if (current.size() == n) {
        result.push_back(current);
        return;
    }
    
    generateBinaryStrings(n, current + "0", result);
    generateBinaryStrings(n, current + "1", result);
}


/*
PROBLEM 8: Print All Paths in a Tree
────────────────────────────────────
Print all root-to-leaf paths.
*/
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class TreePaths {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> result;
        if (root) backtrack(root, "", result);
        return result;
    }
    
private:
    void backtrack(TreeNode* node, string path, vector<string>& result) {
        path += to_string(node->val);
        
        if (!node->left && !node->right) {
            result.push_back(path);
            return;
        }
        
        if (node->left) backtrack(node->left, path + "->", result);
        if (node->right) backtrack(node->right, path + "->", result);
    }
};


// ============================================================================
// MAIN
// ============================================================================

int main() {
    cout << "=== Generate Sequences ===\n\n";
    
    // 1. Generate Parentheses
    GenerateParentheses sol1;
    auto res1 = sol1.generateParenthesis(3);
    cout << "1. Valid parentheses (n=3): " << res1.size() << " combinations\n";
    
    // 2. Letter Combinations
    LetterCombinations sol2;
    auto res2 = sol2.letterCombinations("23");
    cout << "2. Letter combinations of '23': " << res2.size() << " combinations\n";
    
    // 3. Different Ways to Add Parentheses
    DiffWaysParentheses sol3;
    auto res3 = sol3.diffWaysToCompute("2-1-1");
    cout << "3. Ways to compute '2-1-1': ";
    for (int r : res3) cout << r << " ";
    cout << "\n";
    
    // 4. Generalized Abbreviation
    GeneralizedAbbreviation sol4;
    auto res4 = sol4.generateAbbreviations("word");
    cout << "4. Abbreviations of 'word': " << res4.size() << " abbreviations\n";
    
    return 0;
}

/*
================================================================================
                              SUMMARY
================================================================================

+────────────────────────────────+───────────────────────────────────────────────+
| Problem                        | Key Constraint                                |
+────────────────────────────────+───────────────────────────────────────────────+
| Generate Parentheses           | open <= n, close <= open                      |
| Letter Combinations            | Map digit to letters, try each                |
| Different Ways to Parenthesize | Split at each operator, combine results       |
| Generalized Abbreviation       | Either abbreviate (count) or keep character   |
| Binary Watch                   | Count bits in hours and minutes               |
+────────────────────────────────+───────────────────────────────────────────────+

================================================================================
*/

