/**
 * Given an array of size n and an integer k where k << n, and for each element, 
 * the absolute difference b/w its current position and sorted position is <= k. 
 * We have to sort the array.
 *
 * Example Test Cases:
 * Input: arr = [3, 2, 1, 5, 4], k = 2
 * Output: 1 2 3 4 5
 * 
 * Input: arr = [1, 2, 3, 4, 5], k = 1
 * Output: 1 2 3 4 5
 *
 * Input: arr = [1, 3, 2], k = 1
 * Output: 1 2 3
 *
 * Algorithm: Min-Heap
 */

 #include <iostream>
 #include <vector>
 #include <queue>
 
 using namespace std;
 
 void sortNearlySortedArray(vector<int>& arr, int k) {
     // Min-heap to store the nearby elements
     priority_queue<int, vector<int>, greater<int>> minHeap;
     
     // Build the initial heap with the first (k+1) elements
     for (int i = 0; i <= k && i < arr.size(); ++i) {
         minHeap.push(arr[i]);
     }
     
     int index = 0;
     // Iterate over the elements from index (k+1) to (n-1)
     for (int i = k + 1; i < arr.size(); ++i) {
         arr[index] = minHeap.top(); // Place the smallest element in the sorted position
         minHeap.pop();
         minHeap.push(arr[i]); // Push the next element from the array
         index++;
     }
     
     // Extract the remaining elements from the heap and place them into the array
     while (!minHeap.empty()) {
         arr[index] = minHeap.top();
         minHeap.pop();
         index++;
     }
 }
 
 int main() {
     vector<int> arr = {3, 2, 1, 5, 4}; // Example array
     int k = 2;
     
     sortNearlySortedArray(arr, k);
     
     for (int num : arr) {
         cout << num << " ";
     }
     cout << endl;
     
     return 0;
 }