/*
https://leetcode.com/discuss/post/6582615/google-phone-screen-by-ashokkumarmula422-qjfm/

 * Problem: Check if input string with parentheses and digits is balanced.
 * 
 * Example Test Cases:
 * 1. inp = "(()1(1))" --> True
 * 2. inp = ")1()" --> True
 * 3. inp = ")(1))" --> False
 *
 * Algorithm: Use a stack-like approach with a counter, adjusting counts with each digit.
 */

 #include <iostream>
 #include <string>
 using namespace std;
 
 bool isBalanced(const string &inp) {
     int openCount = 0; // Counter for open parentheses
 
     for (char ch : inp) {
         if (ch == '(') {
             ++openCount;
         } else if (ch == ')') {
             if (openCount > 0) {
                 --openCount;
             } else {
                 // More closing parentheses than opening ones
                 return false;
             }
         } else if (isdigit(ch)) {
             // Remove this many parentheses from the left
             int num = ch - '0';
             openCount = max(0, openCount - num);
         }
     }
     
     // Check for balanced parentheses
     return openCount == 0;
 }
 
 int main() {
     string test1 = "(()1(1))";
     string test2 = ")1()";
     string test3 = ")(1))";
     
     cout << "Is balanced (test1): " << (isBalanced(test1) ? "True" : "False") << endl;
     cout << "Is balanced (test2): " << (isBalanced(test2) ? "True" : "False") << endl;
     cout << "Is balanced (test3): " << (isBalanced(test3) ? "True" : "False") << endl;
     
     return 0;
 }