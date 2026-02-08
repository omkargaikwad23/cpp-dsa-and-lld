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
#define printarr(a)     for(auto i : a) cout<<i<<' '; cout<<endl;

// max ways to form a given string from given string of an array
// repetition of substrings is allowed

// m = target length
// n = wordBank length

// Brute force
// time : O(n^m*m)
// space : O(m^2)

//memoized
//time : O(n*m^2)
// space : O(m^2)

// omkar [omk, ar, om, kar, omkar] => output:"3"

unordered_map<string, int>memo;

int count_form(string target, string str[], int n){
  if(target=="") return 1;
  
  if(memo.find(target)!=memo.end()) return memo[target];

  int ways = 0;

  // iterate over given n substrings
  for(int i=0; i<n; i++){
    int len = str[i].length();
    
    // iterate over target string
    bool flag = true;
    for(int j=0; j<len; j++) {
      if(str[i][j]!=target[j] || str[i].length()>target.length()){
        flag = false;
      }
    }

    if(flag){
      string suffix = target.substr(str[i].length());
      int x  =  count_form(suffix, str, n);
      ways += x;
    }
  }
  memo[target] = ways;
  return ways;
}


int main()
{
  string target;
  cin >> target;
  int n;
  cin >> n;
  string arr[n];
  loop(i, 0, n) cin >> arr[i];
  int res = count_form(target, arr, n);

  cout << res << endl;
  return 0;
}
