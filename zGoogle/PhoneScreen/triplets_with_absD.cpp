/*
given 3 sorted arrays (A,B,C) each of size n;
and an integer D;

you have to find number of tuples (i,j,k)
such that:-
|A[i]-B[j]|<=D
|B[j]-C[k]|<=D
|A[i]-C[k]|<=D


provided time complexity of N2logN
but interviewer told that O(N),O(NlogN) solutions were also possible

PS : duplicates are possible
*/

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int countValidTuples(vector<int>& A, vector<int>& B, vector<int>& C, int D) {
    int i = 0, j = 0, k = 0; 
    int count = 0;
    int n = A.size();  // Size of arrays (assuming all are of size n)

    while (i < n && j < n && k < n) {
        // Check if the current triplet (A[i], B[j], C[k]) satisfies the conditions
        if (abs(A[i] - B[j]) <= D &&
            abs(B[j] - C[k]) <= D &&
            abs(A[i] - C[k]) <= D) {
            count++;  // Valid triplet found
            cout << A[i] << " " << B[j] << " " << C[k] << endl;
        } 

        // Move the pointer of the smallest value to try to reduce the difference
        if (A[i] < B[j]) i++;
        else if (B[j] < C[k]) j++;
        else k++;
    }
    
    return count;
}

int main() {
    vector<int> A(3);
    A[0] = 1; A[1] = 3; A[2] = 5;
    vector<int> B(3);
    B[0] = 2; B[1] = 4; B[2] = 6;
    vector<int> C(3);
    C[0] = 3; C[1] = 5; C[2] = 7;
    int D = 2;

    int result = countValidTuples(A, B, C, D);
    cout << "Number of valid tuples: " << result << endl;

    return 0;
}
