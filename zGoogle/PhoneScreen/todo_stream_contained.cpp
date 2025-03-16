/*
Given a stream of numbers which are sorted. Same integer is/can be repeated itself any number of times.
When dividing this stream into strings/smaller arrays of size k find out numbers which are contained.
Concept of contained goes like this, contained number is a number which is not part of any other divided subtrings/sub arrays.

For example -
1122 - 1 is contained
2233 - none, as 2 and 3 both spill in the next array
3333 - none as 3 was a part of prev array
4556 - 4, 5 are contained
6777 - 7 is contained
8888 - 8 is contained, we can say this till we get one more input in the stream.
*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Function to find contained numbers in a given chunk of size 'k'
vector<int> findContainedNumbers(const vector<int>& chunk, const unordered_set<int>& prevChunkNumbers) {
    unordered_map<int, int> countMap; // Count occurrences in the current chunk
    unordered_set<int> containedNumbers;

    // Count occurrences of each number in the chunk
    for (int num : chunk) {
        countMap[num]++;
    }

    // Check if the numbers are contained
    for (auto& entry : countMap) {
        int num = entry.first;
        if (prevChunkNumbers.find(num) == prevChunkNumbers.end()) { // Should not be in previous chunk
            containedNumbers.insert(num);
        }
    }

    // Convert to vector for returning
    return vector<int>(containedNumbers.begin(), containedNumbers.end());
}

int main() {
    vector<int> stream = {1, 1, 2, 2,  2, 3, 3,  3, 3,  4, 5, 5, 6,  6, 7, 7, 7,  8, 8, 8, 8}; 
    int k = 4;  // Size of each chunk

    unordered_set<int> prevChunkNumbers; // Store numbers from the previous chunk

    // Process stream in chunks of size k
    for (size_t i = 0; i < stream.size(); i += k) {
        vector<int> chunk;
        unordered_set<int> currentChunkNumbers; // Numbers in current chunk

        // Extract the chunk
        for (size_t j = i; j < i + k && j < stream.size(); j++) {
            chunk.push_back(stream[j]);
            currentChunkNumbers.insert(stream[j]);
        }

        // Find contained numbers in this chunk
        vector<int> contained = findContainedNumbers(chunk, prevChunkNumbers);

        // Print the contained numbers for this chunk
        cout << "Chunk: ";
        for (int num : chunk) cout << num << " ";
        cout << "\nContained Numbers: ";
        for (int num : contained) cout << num << " ";
        cout << "\n\n";

        // Update prevChunkNumbers for next iteration
        prevChunkNumbers = currentChunkNumbers;
    }

    return 0;
}
