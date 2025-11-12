#include <bits/stdc++.h>
using namespace std;

#define loop(i, a, b) for (int i = a; i < b; i++)



set<int>result;
void solve(int arr[], int i, int n, int sum){
  if(sum!=0)
    result.insert(sum);
  if(i==n) return;
  solve(arr, i+1, n, sum+arr[i]);
  solve(arr, i+1, n, sum);
}

vector<int>dp;
void tabular_method(int arr[], int n){
  dp[0] = 1;  //sum 0 can be made 
  for(int i=0; i<n; i++){
    int ele = arr[i];
    for(int j=100000; j-ele>=0; j--){
      if(dp[j-ele]!=0) {
        dp[j] = 1;
      }
    }
  }
  return ;
}




int main()
{
  int T = 1, m, n;
  // cin >> T;
  while (T--)
  {
    cin >> n;
    int arr[n];
    int maxSum = 0;
    loop(i, 0, n) {cin >> arr[i]; maxSum+=arr[i];}
    // solve(arr, 0, n, 0);
    // cout << result.size() << endl;
    // for(auto i: result){
    //   cout << i << " ";
    // }

    dp.resize(100001, 0);
    tabular_method(arr, n);
    vector<int>answer;
    for(int i=1; i<100001; i++){
      if(dp[i]!=0){
        answer.push_back(i);
      }
    }
    cout << answer.size() << endl;
    for(auto itr: answer)
      cout << itr << " ";
  } 
  return 0;
}


/*
# TESTCASE
Input:
4
4 2 5 2

Output:
9
2 4 5 6 7 8 9 11 13

# TESTCASE
INPUT:
10
4 1 2 4 2 1 1 5 2 3

OUTPUT:
25
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
*/