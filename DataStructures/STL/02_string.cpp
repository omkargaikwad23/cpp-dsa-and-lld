#include <string>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

/*
 * STRING STL - Complete Reference for Interviews
 * ===============================================
 * 
 * string is a container class for sequences of characters.
 * Provides many useful methods for string manipulation.
 * 
 * Key Properties:
 * - Dynamic size (can grow/shrink)
 * - Mutable (can modify characters)
 * - Random access (like array)
 * - Many built-in methods for common operations
 * 
 * Time Complexity Notes:
 * - Most operations are O(1) or O(N) where N is string length
 * - Concatenation can be O(N) or O(N+M) depending on operation
 */

int main() {
    // ============================================
    // 1. CONSTRUCTORS
    // ============================================
    string s1;                          // Empty string
    string s2("hello");                 // From C-string
    string s3(5, 'a');                  // 5 copies of 'a': "aaaaa"
    string s4(s2);                      // Copy constructor
    string s5(s2, 1, 3);                // Substring: "ell" (from index 1, length 3)
    string s6{'h', 'e', 'l', 'l', 'o'}; // Initializer list (C++11)
    
    // ============================================
    // 2. ASSIGNMENT AND CONCATENATION
    // ============================================
    string str = "hello";
    
    // Assignment
    str = "world";                      // O(N)
    str.assign("hello");                // O(N)
    str.assign(5, 'x');                 // "xxxxx": O(N)
    str.assign(s2, 1, 3);               // "ell": O(N)
    
    // Concatenation
    str = "hello";
    str += " world";                    // O(N) where N is length of appended string
    str += '!';                         // Append single character: O(1) amortized
    str.append(" there");               // O(N)
    str.append(3, '!');                 // Append 3 copies of '!': O(N)
    str.append(s2, 1, 3);               // Append substring: O(N)
    str.push_back('?');                 // Append single character: O(1) amortized
    
    // Using + operator (creates new string)
    string s7 = str + " new";           // O(N+M)
    string s8 = "prefix " + str;        // O(N+M)
    
    // ============================================
    // 3. ELEMENT ACCESS (O(1))
    // ============================================
    string s = "hello";
    
    char ch1 = s[0];                    // 'h': O(1) - No bounds check
    char ch2 = s.at(1);                 // 'e': O(1) - With bounds check (throws if out of range)
    char ch3 = s.front();               // 'h': O(1) - First character
    char ch4 = s.back();                // 'o': O(1) - Last character
    
    // Modify characters
    s[0] = 'H';                         // O(1)
    s.at(1) = 'E';                      // O(1)
    
    // Get C-string
    const char* cstr = s.c_str();       // O(1) - Returns null-terminated C-string
    const char* data_ptr = s.data();    // O(1) - Returns pointer to internal array
    
    // ============================================
    // 4. CAPACITY METHODS (O(1))
    // ============================================
    string s9 = "hello";
    
    int len = s9.length();              // O(1) - Same as size()
    int size = s9.size();               // O(1) - Number of characters
    bool empty = s9.empty();            // O(1) - Check if empty
    size_t max_size = s9.max_size();    // O(1) - Maximum possible size
    size_t capacity = s9.capacity();    // O(1) - Current capacity
    
    s9.reserve(100);                    // Reserve capacity: O(N) if reallocation needed
    s9.shrink_to_fit();                 // Reduce capacity to fit size: O(N)
    
    // ============================================
    // 5. MODIFIERS - INSERTION (O(N))
    // ============================================
    string s10 = "hello";
    
    s10.insert(2, "XX");                // Insert at position 2: "heXXllo"
    s10.insert(2, 3, 'Y');              // Insert 3 copies of 'Y' at position 2
    s10.insert(2, s2, 1, 2);            // Insert substring from s2
    
    // Insert using iterator
    s10.insert(s10.begin() + 2, 'Z');  // Insert single character
    s10.insert(s10.begin() + 2, 3, 'W'); // Insert 3 copies
    
    // ============================================
    // 6. MODIFIERS - DELETION (O(N))
    // ============================================
    string s11 = "hello world";
    
    s11.erase(5, 6);                    // Erase 6 characters starting at position 5
    s11.erase(5);                       // Erase from position 5 to end
    s11.erase(s11.begin() + 2);        // Erase single character at iterator
    s11.erase(s11.begin() + 1, s11.begin() + 3); // Erase range [1, 3)
    
    s11.clear();                        // Remove all characters: O(1)
    s11.pop_back();                     // Remove last character: O(1)
    
    // ============================================
    // 7. SUBSTRING AND REPLACE (O(N))
    // ============================================
    string s12 = "hello world";
    
    // substring(pos, len) - Returns new string
    string sub1 = s12.substr(0, 5);    // "hello": O(N)
    string sub2 = s12.substr(6);       // "world": O(N) - from position 6 to end
    string sub3 = s12.substr(6, 3);    // "wor": O(N)
    
    // replace(pos, len, str) - Modifies original string
    s12.replace(0, 5, "Hi");           // "Hi world": O(N+M)
    s12.replace(3, 5, "there");        // "Hi there": O(N+M)
    s12.replace(3, 5, 3, 'X');         // Replace with 3 copies of 'X': O(N)
    
    // Replace using iterators
    s12.replace(s12.begin(), s12.begin() + 2, "Hello"); // O(N+M)
    
    // ============================================
    // 8. SEARCH METHODS (O(N) or O(N*M))
    // ============================================
    string s13 = "hello world hello";
    
    // find() - Returns position or string::npos if not found
    size_t pos1 = s13.find("world");    // Returns 6: O(N*M) where M is pattern length
    size_t pos2 = s13.find("hello");    // Returns 0 (first occurrence)
    size_t pos3 = s13.find("hello", 1); // Start search from position 1: Returns 12
    size_t pos4 = s13.find('o');        // Find single character: O(N)
    size_t pos5 = s13.find("xyz");      // Returns string::npos (not found)
    
    // rfind() - Find last occurrence (reverse find)
    size_t pos6 = s13.rfind("hello");   // Returns 12 (last occurrence): O(N*M)
    
    // find_first_of() - Find first occurrence of any character in set
    size_t pos7 = s13.find_first_of("aeiou"); // Returns 1 ('e'): O(N*M)
    
    // find_last_of() - Find last occurrence of any character in set
    size_t pos8 = s13.find_last_of("aeiou");  // Returns 15 ('o'): O(N*M)
    
    // find_first_not_of() - Find first character not in set
    size_t pos9 = s13.find_first_not_of("helo "); // Returns 5 ('w'): O(N*M)
    
    // find_last_not_of() - Find last character not in set
    size_t pos10 = s13.find_last_not_of("helo "); // Returns 5 ('w'): O(N*M)
    
    // ============================================
    // 9. COMPARISON METHODS (O(N))
    // ============================================
    string s14 = "hello";
    string s15 = "world";
    string s16 = "hello";
    
    // compare() - Returns 0 if equal, <0 if less, >0 if greater
    int cmp1 = s14.compare(s15);        // < 0 ("hello" < "world"): O(N)
    int cmp2 = s14.compare(s16);       // 0 (equal): O(N)
    int cmp3 = s14.compare(0, 2, s15, 0, 2); // Compare substrings: O(N)
    
    // Comparison operators
    bool eq = (s14 == s16);             // true: O(N)
    bool ne = (s14 != s15);             // true: O(N)
    bool lt = (s14 < s15);              // true: O(N)
    bool le = (s14 <= s16);             // true: O(N)
    bool gt = (s15 > s14);              // true: O(N)
    bool ge = (s16 >= s14);             // true: O(N)
    
    // ============================================
    // 10. ITERATION METHODS
    // ============================================
    string s17 = "hello";
    
    // Range-based for loop (C++11)
    for (char c : s17) {
        // Process each character
    }
    
    // Iterator
    for (auto it = s17.begin(); it != s17.end(); ++it) {
        char c = *it;
    }
    
    // Reverse iterator
    for (auto it = s17.rbegin(); it != s17.rend(); ++it) {
        char c = *it;
    }
    
    // Index-based loop
    for (size_t i = 0; i < s17.length(); i++) {
        char c = s17[i];
    }
    
    // ============================================
    // 11. STRING STREAM (Very Useful!)
    // ============================================
    
    // String to number conversion
    string num_str = "12345";
    int num = stoi(num_str);            // String to int: O(N)
    long num_long = stol(num_str);      // String to long: O(N)
    double num_double = stod("123.45"); // String to double: O(N)
    
    // Number to string conversion
    string str1 = to_string(12345);     // Int to string: O(N)
    string str2 = to_string(123.45);    // Double to string: O(N)
    
    // Using stringstream for parsing
    string data = "apple 5 3.14";
    istringstream iss(data);
    string word;
    int num_count;
    double value;
    iss >> word >> num_count >> value;      // Parse: word="apple", num_count=5, value=3.14
    
    // Using stringstream for formatting
    ostringstream oss;
    oss << "Number: " << 42 << " Value: " << 3.14;
    string formatted = oss.str();       // "Number: 42 Value: 3.14"
    
    // ============================================
    // 12. COMMON INTERVIEW PATTERNS
    // ============================================
    
    // Pattern 1: Check if string contains substring
    string text = "hello world";
    string pattern = "world";
    bool contains = (text.find(pattern) != string::npos); // true: O(N*M)
    
    // Pattern 2: Split string by delimiter
    string input = "apple,banana,cherry";
    vector<string> tokens;
    stringstream ss(input);
    string token;
    while (getline(ss, token, ',')) {
        tokens.push_back(token);        // ["apple", "banana", "cherry"]
    }
    
    // Pattern 3: Reverse string
    string s18 = "hello";
    reverse(s18.begin(), s18.end());    // "olleh": O(N)
    
    // Pattern 4: Remove whitespace
    string s19 = "  hello  world  ";
    s19.erase(0, s19.find_first_not_of(" "));  // Remove leading spaces
    s19.erase(s19.find_last_not_of(" ") + 1);  // Remove trailing spaces
    
    // Pattern 5: Check if palindrome
    string s20 = "racecar";
    string reversed = s20;
    reverse(reversed.begin(), reversed.end());
    bool is_palindrome = (s20 == reversed);     // true: O(N)
    
    // Pattern 6: Count occurrences of substring
    string s21 = "hello hello world hello";
    string sub = "hello";
    int occurrence_count = 0;
    size_t pos = 0;
    while ((pos = s21.find(sub, pos)) != string::npos) {
        occurrence_count++;
        pos += sub.length();
    }
    // occurrence_count = 3: O(N*M)
    
    // Pattern 7: Convert to lowercase/uppercase
    string s22 = "Hello World";
    transform(s22.begin(), s22.end(), s22.begin(), ::tolower); // "hello world": O(N)
    transform(s22.begin(), s22.end(), s22.begin(), ::toupper); // "HELLO WORLD": O(N)
    
    // Pattern 8: Remove duplicates
    string s23 = "aabbcc";
    s23.erase(unique(s23.begin(), s23.end()), s23.end()); // "abc": O(N)
    
    // Pattern 9: Check if string starts/ends with substring
    string s24 = "hello world";
    bool starts_with = (s24.substr(0, 5) == "hello");     // true: O(N)
    bool ends_with = (s24.substr(s24.length() - 5) == "world"); // true: O(N)
    
    // Pattern 10: Replace all occurrences
    string s25 = "hello hello world";
    size_t pos_replace = 0;
    while ((pos_replace = s25.find("hello", pos_replace)) != string::npos) {
        s25.replace(pos_replace, 5, "hi");
        pos_replace += 2;  // Move past replacement
    }
    // Result: "hi hi world": O(N*M)
    
    // ============================================
    // 13. TIME COMPLEXITY SUMMARY
    // ============================================
    /*
     * Operation              | Time Complexity
     * -----------------------|----------------
     * Constructor            | O(N)
     * operator=              | O(N)
     * operator[]             | O(1)
     * at()                   | O(1)
     * front()/back()         | O(1)
     * length()/size()        | O(1)
     * empty()                | O(1)
     * reserve()              | O(N) if reallocation
     * push_back()            | O(1) amortized
     * pop_back()             | O(1)
     * insert()               | O(N)
     * erase()                | O(N)
     * replace()              | O(N+M)
     * substr()               | O(N)
     * find()                 | O(N*M) where M is pattern length
     * rfind()                | O(N*M)
     * compare()              | O(N)
     * operator==, <, etc.    | O(N)
     * reverse()              | O(N)
     * transform()            | O(N)
     * 
     * Note: N is the length of the string
     *       M is the length of pattern/substring
     */
    
    // ============================================
    // 14. USEFUL ALGORITHM FUNCTIONS WITH STRINGS
    // ============================================
    string s26 = "hello";
    
    // Sort characters
    sort(s26.begin(), s26.end());       // "ehllo": O(N log N)
    
    // Reverse
    reverse(s26.begin(), s26.end());   // "ollhe": O(N)
    
    // Count characters
    int count_a = count(s26.begin(), s26.end(), 'l'); // Count 'l': O(N)
    
    // Find character
    auto it = find(s26.begin(), s26.end(), 'e'); // Find first 'e': O(N)
    
    // Remove characters
    s26.erase(remove(s26.begin(), s26.end(), 'l'), s26.end()); // Remove all 'l': O(N)
    
    return 0;
}

