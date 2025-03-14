// https://leetcode.com/discuss/interview-question/2328651/Google-Phone-Interview-Question
// https://leetcode.com/discuss/interview-question/1678945/Google-or-Phone-or-String-Substitutor
/*
Given map {X=>123, Y=456}
Input: %X%_%Y%
Output: 123_456

Given map {USER=>admin, HOME=>/%USER%/home}
Input: I am %USER% My home is %HOME%
Output: I am admin My home is /admin/home
*/
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
using namespace std;

unordered_set<string> getWord(string& words){
    unordered_set<string> spilt;
    int i = 0;
    while(i < words.size()){
        string temp = "";
        if(words[i] == '%'){
            temp += words[++i];
            while(i < words.size() && words[i] != '%'){
                temp +=words[++i];
            }
            temp.pop_back();
            spilt.insert(temp);
        }
        i++;
    }    
    return spilt;
}

// Replace %w% to the correct word
string replace(string& w, unordered_map<string, string>& dict){    
    string temp= "";
    int i = 0, j = 0;  
    
    while(i < w.size()){
        if(w[i] == '%'){
            int l = ++i;
            while(i < w.size() && w[i] != '%'){
                i++;
            }
            string newWord = dict[w.substr(l, i-l)];
            temp += newWord;
            i++, j += newWord.size();
        }
        else{
            temp += w[i];
            i++, j++;
        }            
    }
    return temp;
}

unordered_map<string, string> replaceHelp(string& s, unordered_map<string, string>& mp){
    unordered_map<string, vector<string>> graph; //word that we lack of(may be someone's key) : key
    unordered_map<string, int> indegree; // key : numbers of replacement
    unordered_map<string, string> dict; //our final dictionary
    queue<string> q;
    
    //build graph
    for(auto it = mp.begin(); it != mp.end(); it++){
        string key = it->first, words = it->second;
        unordered_set<string> undo = getWord(words);
        
        if(undo.empty()){ //words don't depend on any key
            indegree[key] = 0;
            dict[key] = words; //We can put it in our dict directly
            q.push(key);
        }
        else{
            for(auto iter = undo.begin(); iter != undo.end(); iter++){
                indegree[key]++;
                graph[*iter].push_back(key);
            }            
        }
    }
    
    while(!q.empty()){
        string curKey = q.front(), w = mp[curKey]; 
        q.pop();
        
        //If the current key is not in out dictionary, build the dict
        if(!dict.count(curKey)){
            dict[curKey] = replace(w, dict);
        }        
        
        for(auto nextKey : graph[curKey]){ //This curKey may be others' missing words
            indegree[nextKey]--;
            if(indegree[nextKey] == 0) q.push(nextKey);
        }                      
    }
    
    return dict;    
}

string replaceWord(string& input, unordered_map<string, string>& mp){
    // First, build the final dictionary
    unordered_map<string, string> finalDict = replaceHelp(input, mp);
    
    //Second, construct the whole string by the final dictionary
    return replace(input, finalDict);
    
}

int main() {
    unordered_map<string, string> mp = {{"USER", "admin"},
                                        {"HOME1", "/%USER%/home"}, 
                                        {"HOME2", "/%USER%/USER/%USER%"}, 
                                        {"HOME3", "/%Root%/USER%HOME1%"},
                                        {"Root", "root"}};
    string input =" I am %USER% My home1 is %HOME1%, My home2 is %HOME2%, My home3 is %HOME3%";
        
    cout << replaceWord(input, mp);
}