
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
#define mod 1000000007

/*https://cses.fi/problemset/task/1639
The edit distance between two strings is the minimum number of operations required
to transform one string into the other.
Input:
LOVE
MOVIE

Output:
2
*/

int dp[5001][5001]; 
int min_distance(int i, int j ,string &str1, string &str2){
    if(i==(int)str1.length() || j==(int)str2.length()){
        return max(str2.length()-j, str1.length()-i);
    }
    if(dp[i][j]!=-1) return dp[i][j];

    int ans;
    if(str1[i]==str2[j]){
        ans = min_distance(i+1, j+1, str1, str2);        //if string chars are equal then move ahead
    }
    else{
        int op1 = 1+min_distance(i, j+1, str1, str2);    //add char, i remains and j gets matched
        int op2 = 1+min_distance(i+1, j, str1, str2);    //remove a char from str1
        int op3 = 1+min_distance(i+1, j+1, str1, str2);  //replace a char = both strings first char will match
        ans = min(op1, min(op2, op3));
    }
    return dp[i][j] = ans;
}

int main()
{
    int T = 1;
    // cin >> T;
    while (T--)
    {
        string str1, str2;
        cin >> str1;
        cin >> str2;
        memset(dp, -1, sizeof dp);  //filling array with -1
        cout << min_distance(0, 0, str1, str2);
    }
    return 0;
}