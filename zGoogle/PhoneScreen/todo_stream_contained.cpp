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
#include <climits>

using namespace std;

class DataStream {
private:
    int counter, lastProcessedNumber, k;
    vector<int> result;  // Store the "contained" numbers

public:
    // Constructor to initialize the DataStream with size k
    DataStream(int k) {
        this->k = k;
        this->counter = 0;
        this->lastProcessedNumber = INT_MIN;  // C++ equivalent for Integer.MIN_VALUE
    }

    // Add a number to the current contained numbers if applicable
    void addToContainedNumbers(int streamInput) {
        counter = (counter + 1) % (k + 1);
        
        if (counter == 0) {
            // If the last processed number is the same as the current stream input, remove it
            if (!result.empty() && result.back() == streamInput) {
                result.pop_back();
            }
            counter++;  // Increment counter for next iteration
        }

        // If the current stream input is greater than the last processed number, add it to the result
        if (streamInput > lastProcessedNumber) {
            lastProcessedNumber = streamInput;
            result.push_back(streamInput);
        }
    }

    // Print the current contained numbers
    void printCurrentContainedNumbers() {
        cout << "Contained numbers up to current data stream: ";
        for (int num : result) {
            cout << num << " ";
        }
        cout << endl;
    }
};

int main() {
    DataStream ds(4);  // Initialize DataStream with k = 4
    int input[] = {1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4, 5, 5, 6, 6, 7, 7, 7, 8, 8, 8, 8};
    int size = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < size; ++i) {
        ds.addToContainedNumbers(input[i]);
    }
    ds.printCurrentContainedNumbers();

    return 0;
}