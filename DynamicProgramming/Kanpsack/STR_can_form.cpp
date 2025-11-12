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
#define iterate(x) for(auto itr=x.begin(); itr != x.end(); ++itr)
bool isPrime(ll n){if(n <= 1)return false;if(n <= 3)return true;if(n%2 == 0 || n%3 == 0)return false;for(ll i=5; i*i<=n; i=i+6)if(n%i == 0 || n%(i+2) == 0)return false;return true;}
ll nextPrime(ll N){if(N<=1)return 2;ll prime = N;bool found = false;while(!found){prime++;if(isPrime(prime))found=true;}return prime;}
#define printarr(a)     for(auto i : a) cout<<i<<' ';cout<<endl;

// m = target length
// n = wordBank length

// Brute force
// time : O(n^m*m)
// space : O(m^2)

// memoized
// time : O(n*m^2)
// space : O(m^2)

// "abcdef" from [nab, abc, cd, def, abcd] => YES

unordered_map<string, bool>memo;

bool can_form(string target, string str[], int n){
  if(target=="") 
    return true;
  
  if(memo.find(target)!=memo.end()) 
    return memo[target];

  for(int i=0; i<n; i++){
    int len = str[i].length();
    
    bool flag = true;
    for(int j=0; j<len; j++){
      if(str[i][j]!=target[j] || str[i].length()>target.length()){
        flag = false;
      }
    }
    if(flag){
      string suffix = target.substr(str[i].length());
      if(can_form(suffix, str, n)){
        memo[target] = true;
        return true;
      }
    }
  }
  memo[target] = false;
  return false;
}


int main()
{
  string target;
  cin >> target;
  int n;
  cin >> n;
  string arr[n];
  loop(i, 0, n) cin >> arr[i];
  bool res = can_form(target, arr, n);

  res ? printf("YES") : printf("NO");
  return 0;
}
