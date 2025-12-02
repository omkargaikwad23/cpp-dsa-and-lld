#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

/*
 * STRINGSTREAM STL - Complete Reference for Interviews
 * ====================================================
 * 
 * stringstream provides string-based input/output operations.
 * Useful for parsing strings, converting between strings and numbers, formatting.
 * 
 * Types:
 * - istringstream: Input string stream (read from string)
 * - ostringstream: Output string stream (write to string)
 * - stringstream: Bidirectional (both input and output)
 * 
 * Common Use Cases:
 * - Parse space-separated values from string
 * - Convert numbers to strings
 * - Format strings with variables
 * - Split strings by delimiter
 */

int main() {
    // ============================================
    // 1. ISTREAMSTRING - Reading from String
    // ============================================
    
    // Parse space-separated values
    string input1 = "10 20 30";
    istringstream iss1(input1);
    int a, b, c;
    iss1 >> a >> b >> c;              // a=10, b=20, c=30
    
    // Parse mixed types
    string input2 = "Alice 25 95.5";
    istringstream iss2(input2);
    string name;
    int age;
    double score;
    iss2 >> name >> age >> score;     // name="Alice", age=25, score=95.5
    
    // Parse until end of stream
    string input3 = "1 2 3 4 5";
    istringstream iss3(input3);
    vector<int> numbers;
    int num;
    while (iss3 >> num) {             // Read until end
        numbers.push_back(num);       // [1, 2, 3, 4, 5]
    }
    
    // Check if extraction succeeded
    string input4 = "123 abc";
    istringstream iss4(input4);
    int value;
    if (iss4 >> value) {
        // Successfully read integer
    }
    
    // ============================================
    // 2. OSTREAMSTRING - Writing to String
    // ============================================
    
    // Format string with variables
    ostringstream oss1;
    oss1 << "Name: " << "John" << " Age: " << 30;
    string result1 = oss1.str();      // "Name: John Age: 30"
    
    // Convert number to string
    int num_val = 42;
    ostringstream oss2;
    oss2 << num_val;
    string num_str = oss2.str();      // "42"
    
    // Format with precision
    double pi = 3.14159;
    ostringstream oss3;
    oss3.precision(2);
    oss3 << fixed << pi;
    string pi_str = oss3.str();       // "3.14"
    
    // Clear and reuse
    ostringstream oss4;
    oss4 << "First";
    string s1 = oss4.str();           // "First"
    oss4.str("");                     // Clear content
    oss4 << "Second";
    string s2 = oss4.str();           // "Second"
    
    // ============================================
    // 3. STRINGSTREAM - Bidirectional
    // ============================================
    
    // Read and write
    stringstream ss1;
    ss1 << "100 200";
    int x, y;
    ss1 >> x >> y;                    // x=100, y=200
    
    // Modify and read back
    stringstream ss2;
    ss2 << "Hello";
    string word;
    ss2 >> word;                      // word="Hello"
    ss2.str("");                      // Clear
    ss2 << "World";
    ss2 >> word;                      // word="World"
    
    // ============================================
    // 4. COMMON INTERVIEW PATTERNS
    // ============================================
    
    // Pattern 1: Split string by space
    string text1 = "apple banana cherry";
    istringstream iss5(text1);
    vector<string> words;
    string word1;
    while (iss5 >> word1) {
        words.push_back(word1);        // ["apple", "banana", "cherry"]
    }
    
    // Pattern 2: Split by custom delimiter (using getline)
    string text2 = "apple,banana,cherry";
    istringstream iss6(text2);
    vector<string> tokens;
    string token;
    while (getline(iss6, token, ',')) {
        tokens.push_back(token);      // ["apple", "banana", "cherry"]
    }
    
    // Pattern 3: Convert number to string
    int number = 12345;
    ostringstream oss5;
    oss5 << number;
    string num_string = oss5.str();  // "12345"
    // Alternative: string num_string = to_string(number);
    
    // Pattern 4: Convert string to number
    string num_str2 = "12345";
    istringstream iss7(num_str2);
    int number2;
    iss7 >> number2;                 // 12345
    // Alternative: int number2 = stoi(num_str2);
    
    // Pattern 5: Format complex string
    string name2 = "Alice";
    int score2 = 95;
    double avg = 92.5;
    ostringstream oss6;
    oss6 << name2 << " scored " << score2 << " with average " << fixed << setprecision(1) << avg;
    string formatted = oss6.str();    // "Alice scored 95 with average 92.5"
    
    // Pattern 6: Parse CSV-like data
    string csv = "John,25,Engineer\nJane,30,Doctor";
    istringstream iss8(csv);
    string line;
    while (getline(iss8, line)) {    // Read line by line
        istringstream line_stream(line);
        string name, age, profession;
        getline(line_stream, name, ',');
        getline(line_stream, age, ',');
        getline(line_stream, profession, ',');
        // Process: name="John", age="25", profession="Engineer"
    }
    
    // Pattern 7: Check if string is numeric
    string test = "12345";
    istringstream iss9(test);
    int test_num;
    if (iss9 >> test_num && iss9.eof()) {
        // String is purely numeric
    }
    
    // Pattern 8: Extract words ignoring punctuation
    string text3 = "Hello, world! How are you?";
    istringstream iss10(text3);
    vector<string> clean_words;
    string w;
    while (iss10 >> w) {
        // Remove punctuation if needed
        clean_words.push_back(w);     // ["Hello,", "world!", "How", "are", "you?"]
    }
    
    // Pattern 9: Build string incrementally
    ostringstream oss7;
    for (int i = 1; i <= 5; i++) {
        oss7 << i;
        if (i < 5) oss7 << ", ";
    }
    string sequence = oss7.str();     // "1, 2, 3, 4, 5"
    
    // Pattern 10: Parse with error handling
    string input5 = "10 abc 20";
    istringstream iss11(input5);
    int val1, val2;
    if (iss11 >> val1) {
        // Successfully read first number
    }
    string temp;
    iss11 >> temp;                    // Skip "abc"
    if (iss11 >> val2) {
        // Successfully read second number
    }
    
    // ============================================
    // 5. USEFUL METHODS
    // ============================================
    
    // str() - Get/Set string content
    stringstream ss3;
    ss3 << "Hello";
    string content = ss3.str();       // Get: "Hello"
    ss3.str("World");                 // Set: Replace with "World"
    
    // clear() - Clear error flags (doesn't clear content)
    stringstream ss4;
    ss4 << "123";
    int val;
    ss4 >> val;                       // val = 123
    ss4 >> val;                       // Fails (end of stream)
    ss4.clear();                      // Clear error flags
    ss4.str("456");                   // Set new content
    ss4 >> val;                       // val = 456
    
    // eof() - Check if end of stream reached
    stringstream ss5("10 20");
    int v1, v2, v3;
    ss5 >> v1 >> v2;                  // v1=10, v2=20
    bool is_eof = ss5.eof();          // true
    ss5 >> v3;                        // Fails (eof reached)
    
    // fail() - Check if operation failed
    stringstream ss6("abc");
    int invalid;
    ss6 >> invalid;                   // Fails (can't convert "abc" to int)
    bool failed = ss6.fail();         // true
    
    // good() - Check if stream is in good state
    stringstream ss7("123");
    bool is_good = ss7.good();        // true
    int v;
    ss7 >> v;                         // v = 123
    is_good = ss7.good();             // true (if more data available)
    
    // ============================================
    // 6. TIME COMPLEXITY SUMMARY
    // ============================================
    /*
     * Operation          | Time Complexity
     * -------------------|----------------
     * Constructor        | O(1)
     * operator<<         | O(N) where N is length of data
     * operator>>         | O(N) where N is length of data
     * str()              | O(N) where N is string length
     * str(string)        | O(N) where N is string length
     * clear()            | O(1)
     * eof()/fail()/good()| O(1)
     * 
     * Note: stringstream operations are generally O(N) where N is the
     *       length of the string being processed
     */
    
    // ============================================
    // 7. ALTERNATIVES TO STRINGSTREAM
    // ============================================
    /*
     * For simple conversions:
     * - Number to string: to_string() - Faster, simpler
     * - String to number: stoi(), stol(), stod() - Faster, simpler
     * 
     * For complex parsing:
     * - Use stringstream when you need to parse multiple values
     * - Use stringstream when you need to format complex strings
     * - Use stringstream when you need to split by delimiter
     */
    
    return 0;
}

