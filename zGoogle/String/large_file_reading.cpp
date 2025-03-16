#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>

using namespace std;

// Function to load banned words into a hash set
unordered_set<string> loadBannedWords(const string &bannedFile) {
    unordered_set<string> bannedWords;
    ifstream inFile(bannedFile);
    string word;

    while (inFile >> word) {
        bannedWords.insert(word);
    }
    
    inFile.close();
    return bannedWords;
}

// Function to process the input file and replace banned words
void processFile(const string &inputFile, const string &bannedFile, const string &outputFile) {
    unordered_set<string> bannedWords = loadBannedWords(bannedFile);
    
    ifstream inFile(inputFile);
    ofstream outFile(outputFile);
    
    string line, word;

    while (getline(inFile, line)) {  // Read file line by line
        stringstream ss(line);
        string modifiedLine;
        
        while (ss >> word) {  // Read word by word
            if (bannedWords.find(word) != bannedWords.end()) {
                word = "Banned";  // Replace banned word
            }
            if (!modifiedLine.empty()) modifiedLine += " ";
            modifiedLine += word;
        }
        
        outFile << modifiedLine << "\n";  // Write to output file
    }

    inFile.close();
    outFile.close();
}

// Main function
int main() {
    string inputFile = "input.txt";
    string bannedFile = "banned_words.txt";
    string outputFile = "output.txt";

    processFile(inputFile, bannedFile, outputFile);

    cout << "Processing complete. Check " << outputFile << " for results.\n";
    return 0;
}
