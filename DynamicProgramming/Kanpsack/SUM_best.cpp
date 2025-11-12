#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long long int lli;
typedef long double ld;
#define pii pair<int, int>
#define ff first
#define ss second
#define mp make_pair
#define pb push_back
#define loop(i, a, b) for (int i = a; i < b; i++)

// m = target sum
// n = array size

// brute force
// time : O(n^m*m)
// space : O(m^2)

// Memoized
// time : O(m^2*n)
// space : O(m^2)

// best_sum(100, [4, 10, 20, 25], 4) ==> [25, 25, 25, 25]

map<ll, vector<int>>mymp;

pair<vector<int>, bool> best_sum(int sum, int arr[], int n){
  auto itr = mymp.find(sum);
 
  if(itr!=mymp.end()) 
    return {itr->second, true};

  if(sum==0) {
    vector<int>v; 
    return {v, true};
  }

  if(sum<0) { 
    vector<int>v; 
    return {v, false};
  }

  vector<int>shortestCombination;

  for(int i=0; i<n; i++){
    int remain = sum - arr[i];
    pair<vector<int>, bool> temp = best_sum(remain, arr, n);
    
    if(temp.second == true){
      temp.first.push_back(arr[i]);
      if((shortestCombination.size() == 0 || shortestCombination.size() > temp.first.size())){
        shortestCombination = temp.first;
      }
    }
  }
  mymp[sum] = shortestCombination;
  return {shortestCombination, true};
}

int main()
{
  int t, sum;
  cin >> t;
  int arr[t];
  loop(i, 0, t) cin >> arr[i];
  cin >> sum;

  pair<vector<int>, bool> res = best_sum(sum, arr, t);

  if(res.first.size() == 0){
    cout << "NOT POSSIBLE" << endl;
  }else{
    for(auto i : res.first){
      cout << i << " " ;
    }
  }
  return 0;
}