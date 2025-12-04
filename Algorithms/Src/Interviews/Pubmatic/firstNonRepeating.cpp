#include <bits/stdc++.h>
using namespace std;

// class obj = new ClassName();
// delete obj;

// first non repeating character

/*
1) Method1 : brute force
time: O(n^2) 
space: O(1)

abcdab
a - bcdab -> a is repeating
for(i=0; i<n-1; i++){
    for(int j=i+1; j<n; j++){
        if()
    }
}

1) Method2 
int seen[26] = {0};

//time: O(N)
space : O(1)
*/

char findFirstNonrepeasting(string word){
    vector<int> seen(26, 0); // no characters are visited

    int N = word.size();
    for(int i=0; i<N; i++){
        int index = word[i] - 'a'; //  will get index [0, 25]
        seen[index] += 1;
    }

    for(int i=0; i<N; i++){
        int index = word[i] - 'a';
        if(seen[index] == 1){
            return word[i];
        }
    }
    return '#';
}

int main(){
    string word = "abcdab";  // ans: c

    char ans = findFirstNonrepeasting(word);
    cout << ans << endl;

}