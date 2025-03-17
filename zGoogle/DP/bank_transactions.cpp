
/*
Consider a bank with some intial amount of money. Consider an array which represents list of transactions which are going to come through customers. + means deposit - means withdrawl. Bank can choose from which customer they want to start serving the customers and they can refuse any number of customers. But once they start they have to serve till the time its impossible to serve the customers. Maximize the total customers bank can serve.

Example :
Bank has 1 unit of money intially.
Customer transactions : [1, -3, 5, -2, 1]
answer = 3

Bank starts with customer with deposit of 5
1+ 5 = 6
6 - 2 = 4
4 + 1 =5

If bank starts at in index 0 can only serve 1 customer
1+1 =2
2-3 = -1 not possible
*/

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
            left = i + 1;
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


