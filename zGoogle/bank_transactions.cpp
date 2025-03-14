#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<int>& transactions, int money) {
	int max_cust = 0;
	int left = 0, prefix_sum = money;
    
	for(int i=0; i<transactions.size(); i++) {
		prefix_sum += transactions[i];
        if(prefix_sum < 0) {
            left = i+1;
            prefix_sum = money;
            continue;
        }
        int cur_max = i - left + 1;
        max_cust = max(max_cust, cur_max);
    }
    return max_cust;
}

int main() {
   vector<int> arr = {1, -2, 3, 4, -10, 5, 6};
   cout << solve(arr, 1) << endl;
}


