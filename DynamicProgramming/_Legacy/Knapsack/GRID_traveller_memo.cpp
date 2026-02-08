#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

// memoization technique
map<pair<int, int>, ll>mp;

ll gridTraveler(int m, int n){
  if(m==0 || n==0) return 0;
  if(m==1 && n==1) return 1;

  map<pair<int, int>, ll>::iterator itr;
  itr = mp.find(make_pair(m, n));
  if(itr!=mp.end()){
    return itr->second;
  }
  
  ll temp1 = gridTraveler(m-1, n) + gridTraveler(m, n-1); 
  mp.insert({make_pair(m, n), temp1});
  return temp1;
}

// tabulation 
// space : O(m*n)
// time : O(m*n)
ll gridTraveler_Tabu(int m, int n){
  ll arr[m+1][n+1];
  
  for(int i=0; i<=m; i++){
    for(int j=0; j<=n; j++){
      arr[i][j] = 0;
    }
    //cout << endl;
  }
  arr[1][1] = 1;

  for(int i=0; i<=m; i++){
    for(int j=0; j<=n; j++){
      ll current = arr[i][j];
      if(j+1<=n) arr[i][j+1]+=current;
      if(i+1<=m) arr[i+1][j]+=current;
    }
  }
  // for(int i=0; i<m; i++){
  //   for(int j=0; j<n; j++){
  //     cout << arr[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  return arr[m][n];
}

int main(){
  int m, n;
  cin >> m >> n;

  ll ans = gridTraveler_Tabu(m, n);

  cout << ans << endl;
}