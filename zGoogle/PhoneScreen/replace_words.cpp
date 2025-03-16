/*
Replace words encoded in % with their corresponding value in the map.
Input
String = "hello %username%,this is %product name%,Regards %service%."
maps<string,string>={username=xyz,product name=google,service=mail}
output
String value
hello xyz,this is google,Regards mail.

*/

#include <iostream>
#include <map>

using namespace std;

void solve(string &str, map<string, string> &mp) {
    string ans = "";
    int prev = -1;

    for (int i = 0; i < str.size(); i++) {
        char ch = str[i];

        if (ch == '%') {
            if (prev == -1) {
                prev = i + 1;  // Start of the key
            } else {
                int len = i - prev; // Extract key
                string key = str.substr(prev, len);

                // Replace with mapped value if exists, otherwise keep original
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += "%" + key + "%";  // Keep the original if not found
                }
                prev = -1;
            }
        } 
        else if (prev == -1) {
            ans += ch;  // Append characters outside placeholders
        }
    }
    
    cout << ans << endl;
}

int main() {
    string str = "hello %username%,this is %product name%,Regards %service%.";
    
    map<string, string> mp;
    mp["username"] = "xyz";
    mp["product name"] = "google";
    mp["service"] = "mail";

    solve(str, mp);
    return 0;
}
