#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int>vi;
typedef vector<ll>vl;
typedef vector<bool>vb;
#define TEST ll tt; cin>>tt; while(tt--)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);


/*
Q: count number of child nodes of each node in a given tree

INPUT:
5
1 1 2 3    (parent's of n-1 nodes from 2 to n)

OUTPUT: 
4 1 1 0 0

explanation: 
Number of nodes in the given tree 5.

1 is root of the tree.
node at 2st position has parent 1,
node at 3nd position has parent 2...

        1
       / \
      2   3
     /     \
    4       5

Number of children of node 1 are 4
*/

void dfs(int src, int par, vector<int>& dp, vector<int> tree[]){
    int count = 0;
    for(auto child : tree[src]){
        if(child != par){
            dfs(child, src, dp, tree);
            count += (1 + dp[child]);   //no of children child node has + the child node itself
        }
    }
    dp[src] = count;
}

void solve(){
    int n; cin >> n;
    vector<int> tree[n+1];
    
    int parent;
    for(int child=2; child<=n; child++){
        cin >> parent;
        tree[parent].push_back(child);
        tree[child].push_back(parent);
    }

    vector<int> dp(n+1, 0);
    dfs(1, -1, dp, tree);

    for(int i=1; i<=n; i++) cout << dp[i] << " ";
    cout << "\n";
}

int main()
{
    IOS
    solve();
    return 0;
}